#include "QIM.h"

#include <QtNut/sqlitegenerator.h>

Q_GLOBAL_STATIC(QIM, qim)

QIM *QIM::instance() {
    return qim();
}

QIM::QIM(QObject *parent)
        : QObject{parent} {

    socket = new QWebSocket();

    m_timer_heart = new QTimer();
    connect(m_timer_heart, &QTimer::timeout, this, &QIM::heartBeat);

    m_timer_heart_count = new QTimer();
    connect(m_timer_heart_count, &QTimer::timeout, this, &QIM::heartBeatCount);

    m_timer_reconnect = new QTimer();
    connect(m_timer_reconnect, &QTimer::timeout, this, &QIM::reconnect);

    m_timer_resend_msg = new QTimer();
    connect(m_timer_resend_msg, &QTimer::timeout, this, &QIM::resendMsg);

    connect(socket, &QWebSocket::stateChanged, this, [this](QAbstractSocket::SocketState state) {
        switch (state) {
            case QAbstractSocket::UnconnectedState:
                if (!m_userInfo.isEmpty()) {
                    m_timer_reconnect->start(2000);
                }
                setState(0);
                break;
            case QAbstractSocket::HostLookupState:
                setState(1);
                break;
            case QAbstractSocket::ConnectingState:
                setState(2);
                break;
            case QAbstractSocket::ConnectedState:
                m_heart_count = 0;
                m_timer_reconnect->stop();
                setState(3);
                break;
            case QAbstractSocket::BoundState:
                setState(4);
                break;
            case QAbstractSocket::ClosingState:
                setState(5);
                break;
            case QAbstractSocket::ListeningState:
                setState(6);
                break;
            default:
                setState(-1);
                break;
        }
    });

    connect(socket, &QWebSocket::binaryMessageReceived, this, [this](const QByteArray &frame) {
        im::protocol::Packet packet;
        packet.ParseFromString(frame.toStdString());
        auto type = packet.type();
        if (type == im::protocol::Login_rsp_) {
            if (packet.login_rsp().result().success()) {
                startHeartBeat();
                getFriends();
                getProfile();
                initDataBase(m_login_accid);
                Q_EMIT loginSuccess();
            } else {
                Q_EMIT loginFail();
            }
        } else if (type == im::protocol::Heart_rsp_) {
            if (packet.heart_rsp().result().success()) {
                m_heart_count = 0;
            }
        } else if (type == im::protocol::GetFriends_rsp_) {
            if (packet.getfriends_rsp().result().success()) {
                std::string json;
                google::protobuf::util::MessageToJsonString(packet.getfriends_rsp(), &json);
                setFriends(QString::fromStdString(json));
            }
        } else if (type == im::protocol::GetProfile_rsp_) {
            if (packet.getprofile_rsp().result().success()) {
                std::string json;
                google::protobuf::util::MessageToJsonString(packet.getprofile_rsp().user(), &json);
                setUserInfo(QString::fromStdString(json));
            }
        } else if (type == im::protocol::SyncMsg_rsp_) {
            if (packet.syncmsg_rsp().result().success()) {
                std::string json;
                google::protobuf::util::MessageToJsonString(packet.syncmsg_rsp(), &json);
                qDebug() << QString::fromStdString(json);
                IMDataBase::syncMessage(packet.syncmsg_rsp().messages());
            }
        } else if (type == im::protocol::SendMsg_rsp_) {
            if (packet.sendmsg_rsp().result().success()) {
                const im::protocol::Message &msg = packet.sendmsg_rsp().message();
                const QSqlError &error = IMDataBase::saveOrUpdateMsg(msg);
                if (error.type() == QSqlError::NoError) {
                    const Message &message = m_db.getMsgByUuid(QString::fromStdString(msg.uuid()));
                    handleMessageBuf(message);
                    Q_EMIT receiveMessage(message);
                }
            }
        }
    });

    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this,
            [=](QAbstractSocket::SocketError error) {
                Q_EMIT errorMessage(QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error));
            });

}

void QIM::handleMessageBuf(const Message &message) {
    for (int i = 0; i < m_msg_buf.size(); ++i) {
        auto &item = const_cast<Message &>(m_msg_buf.at(i));
        if (item.getId() == message.getId()) {
            m_msg_buf.removeAt(i);
            return;
        }
    }
}

QIM::~QIM() {
    socket->close();
    m_timer_heart->stop();
    m_timer_heart_count->stop();
    m_timer_reconnect->stop();
    m_timer_resend_msg->stop();
    delete socket;
    delete m_timer_heart;
    delete m_timer_heart_count;
    delete m_timer_reconnect;
    delete m_timer_resend_msg;
}

void QIM::login(const QString &url, const QString &accid, const QString &token) {
    m_ws = url + "?accid=" + accid + "&token=" + token;
    setLoginAccid(accid);
    m_login_token = token;
    qDebug() << "start login";
    socket->open(m_ws);
}

void QIM::heartBeat() {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::Heart_req_);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::reconnect() {
    socket->open(m_ws);
}

void QIM::heartBeatCount() {
    m_heart_count = m_heart_count + 1;
    if (m_heart_count > 13) {
        socket->close();
    }
}

void QIM::startHeartBeat() {
    m_timer_heart_count->start(1000);
    m_timer_heart->start(9000);
}

void QIM::stopHeartBeat() {
    m_timer_heart->stop();
    m_timer_heart_count->stop();
}

void QIM::resendMsg() {
    if (m_msg_buf.count() == 0) {
        m_timer_resend_msg->stop();
        return;
    }
    qDebug() << "resendMsg---------------:" << m_msg_buf.count();
    for (int i = 0; i < m_msg_buf.size(); ++i) {
        auto item = m_msg_buf.at(i);
        if (QDateTime::currentDateTimeUtc().toMSecsSinceEpoch() > item.getTime().toULongLong() + 30000) {
            item.setStatus(2);
            const QSqlError &error = IMDataBase::saveOrUpdateMsg(item);
            if (error.type() == QSqlError::NoError) {
                m_msg_buf.removeAt(i);
                Q_EMIT receiveMessage(item);
            }
        }
    }
}

void QIM::sendTextMessage(const QString &from, const QString &to, const QString &text) {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::SendMsg_req_);
    auto *msg_req = new im::protocol::SendMsg_req();
    auto *msg = new im::protocol::Message();
    msg->set_uuid(QUuid::createUuid().toString().remove("{").remove("}").toStdString());
    msg->set_body(text.toStdString());
    msg->set_from(from.toStdString());
    msg->set_to(to.toStdString());
    msg->set_sessionid(to.toStdString());
    msg->set_scene(0);
    msg->set_type(0);
    msg_req->set_allocated_message(msg);
    packet.set_allocated_sendmsg_req(msg_req);
    const QSqlError &error = IMDataBase::insertMsg(*msg);
    if (error.type() == QSqlError::NoError) {
        const Message &message = m_db.getMsgByUuid(QString::fromStdString(msg->uuid()));
        m_msg_buf.append(message);
        m_timer_resend_msg->start(1000);
        Q_EMIT receiveMessage(message);
    }

    qDebug() << "socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString())):"
             << socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    qDebug() << "socket->flush():" << socket->flush();
}

void QIM::initDataBase(const QString &text) {
    QString name = text.toUtf8().toBase64();
    IMDataBase::initDb(name);
    sendSyncMessage();
}

void QIM::sendSyncMessage() {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::SyncMsg_req_);
    auto *req = new im::protocol::SyncMsg_req();
    req->set_lastmsgtime(IMDataBase::getMsgLastTime());
    packet.set_allocated_syncmsg_req(req);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::getFriends() {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::GetFriends_req_);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::getProfile() {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::GetProfile_req_);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::updateMessageModel(const QString &accid) {

}

void QIM::test() {
    qDebug() << "m_msg_buf.count()-----------------" << m_msg_buf.count();
}

QList<Message> QIM::getMessageListById(const QString &accid) {
    const QList<Message> &list = m_db.getMessageListById(accid);
    return list;
}

QList<Session> QIM::getSessionList() {
    return m_db.getSessionList();
}
