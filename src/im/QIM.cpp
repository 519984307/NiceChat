#include "QIM.h"

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
            if (!m_profile.isEmpty()) {
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
                syncFriends(packet.getfriends_rsp().friends());
            }
        } else if (type == im::protocol::GetProfile_rsp_) {
            if (packet.getprofile_rsp().result().success()) {
                syncProfile(packet.getprofile_rsp().user());
                //                std::string json;
                //                google::protobuf::util::MessageToJsonString(packet.getprofile_rsp().user(), &json);
                //                setUserInfo(QString::fromStdString(json));
            }
        } else if (type == im::protocol::SyncMsg_rsp_) {
            if (packet.syncmsg_rsp().result().success()) {
                syncMessage(packet.syncmsg_rsp().messages());
            }
        } else if (type == im::protocol::SendMsg_rsp_) {
            if (packet.sendmsg_rsp().result().success()) {
                const im::protocol::Message &msg = packet.sendmsg_rsp().message();
                Message message = Convert::proto2message(msg);
                message.setStatus(0);
                const QSqlError &error = IMDataBase::saveOrUpdateMessage(message);
                if (error.type() == QSqlError::NoError) {
                    handleMessageBuf(message);
                    Q_EMIT receiveMessage(message);
                    updateSessionByMessage(message);
                }
            }
        }
    });

    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this,
            [=](QAbstractSocket::SocketError error) {
        Q_EMIT errorMessage(QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error));
    });

}

void QIM::syncFriends(const google::protobuf::RepeatedPtrField<im::protocol::User> &friends) {
    QList<User> userList;
    for (int i = 0; i < friends.size(); ++i) {
        const im::protocol::User &item = friends.Get(i);
        const User &user = Convert::proto2user(item);
        m_user_cache.insert(user.getAccid(), user);
        userList.append(user);
    }
    qx::dao::save(userList);
    Q_EMIT syncFriendCompleted();
}

void QIM::syncProfile(const im::protocol::User &profile) {
    const User &user = Convert::proto2user(profile);
    m_user_cache.insert(user.getAccid(), user);
    setProfile(user);
}

void QIM::syncMessage(const google::protobuf::RepeatedPtrField<im::protocol::Message> &messages) {
    QList<Message> messageList;
    QMap<QString, Message> map;
    QMap<QString, int> mapUnread;
    for (int i = 0; i < messages.size(); ++i) {
        const im::protocol::Message &item = messages.Get(i);
        const Message &message = Convert::proto2message(item);
        if (message.m_from_accid != m_login_accid) {
            //别人发的消息
            if (!message.getReadAccids().contains(m_login_accid)) {
                int unread = mapUnread.value(message.getSessionId()) + 1;
                mapUnread.insert(message.getSessionId(), unread);
            }
        }
        map.insert(message.getSessionId(), message);
        messageList.append(message);
    }
    QList<Session> sessionList;
    for (const auto &item: map) {
        Session session = Convert::message2session(item);
        int unread = mapUnread.value(session.getId());
        session.setUnread(unread);
        sessionList.append(session);
    }
    qx::dao::save(messageList);
    qx::dao::save(sessionList);
    Q_EMIT syncMessageCompleted();
}

void QIM::updateSessionByMessage(const Message &message) {
    Session session = Convert::message2session(message);
    Session it = IMDataBase::getSessionById(message.getSessionId());
    if (it.m_id == message.getSessionId()) {
        //db中有该会话
        session.setUnread(it.getUnread());
        session.setEx(it.getEx());
    }
    if (message.m_from_accid != m_login_accid) {
        //我接收到别人发的消息
        if (!message.getReadAccids().contains(m_login_accid)) {
            session.setUnread(session.getUnread() + 1);
        }
    }
    const QSqlError &error = IMDataBase::saveOrUpdateSession(session);
    if (error.type() == QSqlError::NoError) {
        Q_EMIT updateSessionCompleted(session);
    }
}

void QIM::handleMessageBuf(const Message &message) {
    foreach(const QString id,m_msg_buf.keys())
    {
        const Message& item = m_msg_buf.value(id);
        if (item.getId() == message.getId()) {
            m_msg_buf.remove(id);
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

    foreach(const QString id,m_msg_buf.keys())
    {
        Message item = m_msg_buf.value(id);
        if (QDateTime::currentDateTimeUtc().toMSecsSinceEpoch() > item.getTime().toULongLong() + 30000) {
            item.setStatus(2);
            const QSqlError &error = IMDataBase::saveOrUpdateMessage(item);
            if (error.type() == QSqlError::NoError) {
                m_msg_buf.remove(id);
                Q_EMIT receiveMessage(item);
                updateSessionByMessage(item);
            }
        }
    }

}

void QIM::sendTextMessage(const QString &sessionId, int scene, const QString &text) {
    Message message = buildMessage(sessionId, scene, 0, buildTextBody(text));
    sendMessageToLocal(message);
    sendMessage(message);
}

void QIM::sendImageMessage(const QString &sessionId, int scene, const QString &path) {
    Message message = buildMessage(sessionId, scene, 1, buildImageBody(path));
    sendMessageToLocal(message);
    HttpClient &client = *HttpClient::instance();
    client.post("http://127.0.0.1:8889/api/storage/upload")
            .bodyWithFile("file", path)
            .onUploadProgress([](qint64 bytesSent, qint64 bytesTotal) {
        qDebug() << "lambda bytes sent: " << bytesSent
                 << "bytes total: " << bytesTotal;
    })
    .onSuccess([this,message,sessionId,path](QString result) mutable {
        QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
        QJsonObject obj = doc.object();
        if(obj["success"].toBool() == true){
            message.setBody(buildImageBody(path,obj["data"].toString()));
            sendMessageToLocal(message);
            sendMessage(message);
            qDebug() << "result: " << result.left(100);
        }
    }).onFailed([](QString error) {
        qDebug() << "error: " << error;
    })
    .exec();
}

void QIM::sendFileMessage(const QString &sessionId, int scene, const QString &path) {
    Message message = buildMessage(sessionId, scene, 2, buildFileBody(path));
    sendMessageToLocal(message);
    sendMessage(message);
}

void QIM::sendReadMessageByUuids(const QString &uuids) {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::ReadMsg_req_);
    auto *request = new im::protocol::ReadMsg_req();
    request->set_uuids(uuids.toStdString());
    packet.set_allocated_readmsg_req(request);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::initDataBase(const QString &text) {
    QString name = text.toUtf8().toBase64();
    IMDataBase::initDb(name);
    sendSyncProfile();
    sendSyncFriend();
    sendSyncMessage();
}

void QIM::sendSyncMessage() {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::SyncMsg_req_);
    auto *req = new im::protocol::SyncMsg_req();
    req->set_lastmsgtime(IMDataBase::getMessageLastTime());
    packet.set_allocated_syncmsg_req(req);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::sendSyncFriend() {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::GetFriends_req_);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::sendSyncProfile() {
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
    getMessageList(accid, nullptr);
    return list;
}

QList<Message> QIM::getMessageList(const QString &sessionId, const Message *anchor) {
    qulonglong anchorTime = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    if (anchor != nullptr) {
        anchorTime = anchor->getTime().toULongLong();
    }
    qx::QxSqlQuery query(
                QString("WHERE Message.session_id = '%1' and Message.time < %2 order by Message.time desc limit %3").arg(
                    sessionId).arg(anchorTime).arg(20));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    //    for(int k=0, s=list.size(), max=(s/2); k<max; k++) list.swap(k,s-(1+k));
    return list;
}

QList<Session> QIM::getSessionList() {
    return IMDataBase::getSessionList();
}

QList<User> QIM::getFriendList() {
    return IMDataBase::getFriendList();
}

void QIM::clearUnreadCount(const QString &sessionId) {
    QList<Message> data = IMDataBase::getUnreadMessageList(sessionId, m_login_accid);
    if (data.count() == 0)
        return;
    QString uuids;
    for (int i = 0; i < data.size(); ++i) {
        auto &item = const_cast<Message &>(data.at(i));
        const QString &accids = item.getReadAccids();
        if (accids.isEmpty()) {
            item.setReadAccids(m_login_accid);
        } else {
            item.setReadAccids(accids + "," + m_login_accid);
        }
        uuids.append(item.getId()).append(",");
    }
    uuids.chop(1);
    qx::dao::save(data);
    Session session = IMDataBase::getSessionById(sessionId);
    session.setUnread(0);
    IMDataBase::saveOrUpdateSession(session);
    Q_EMIT updateSessionCompleted(session);
    sendReadMessageByUuids(uuids);
}

QString QIM::getUserName(const QString &accid) {
    const User &user = m_user_cache.value(accid);
    return user.getName();
}

QJsonObject QIM::getUserObject(const QString &accid) {
    const User &user = m_user_cache.value(accid);
    const QString &json = qx::serialization::json::to_string(user);
    return QJsonDocument::fromJson(json.toUtf8()).object();
}

void QIM::topSession(const QString &accid, bool top) {
    Session session = IMDataBase::getSessionById(accid);
    session.setTop(top);
    const QSqlError &error = IMDataBase::saveOrUpdateSession(session);
    if (error.type() == QSqlError::NoError) {
        Q_EMIT updateSessionCompleted(session);
    }
}

void QIM::deleteSession(const QString &accid) {
    Session session;
    session.setId(accid);
    const QSqlError &error = qx::dao::delete_by_id(session);
    if (error.type() == QSqlError::NoError) {
        Q_EMIT deleteSessionCompleted(accid);
    }
}

Message QIM::buildMessage(const QString &sessionId, int scene, int type, const QString &body){
    Message message;
    message.setId(QUuid::createUuid().toString().remove("{").remove("}"));
    message.setBody(body);
    message.setFromAccid(m_login_accid);
    message.setToAccid(sessionId);
    message.setSessionId(sessionId);
    message.setScene(scene);
    message.setType(type);
    message.setTime(QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()));
    message.setStatus(1);
    return message;
}

QString QIM::buildTextBody(const QString &text) {
    QJsonObject obj;
    obj["msg"] = text;
    QJsonDocument doc(obj);
    return QString(doc.toJson(QJsonDocument::Compact));
}

QString QIM::buildImageBody(const QString &path,const QString& url) {
    QFile file(path);
    const QFileInfo &fileInfo = QFileInfo(file);
    QJsonObject obj;
    obj["name"] = fileInfo.fileName();
    obj["ext"] = fileInfo.suffix();
    obj["size"] = fileInfo.size();
    QImage img;
    img.load(path);
    obj["w"] = img.width();
    obj["h"] = img.height();
    obj["url"] = url;
    if (file.open(QIODevice::ReadOnly)) {
        obj["md5"] = QString(QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex());
    }
    QJsonDocument doc(obj);
    return QString(doc.toJson(QJsonDocument::Compact));
}

QString QIM::buildFileBody(const QString &path) {
    QFile file(path);
    const QFileInfo &fileInfo = QFileInfo(file);
    QJsonObject obj;
    obj["name"] = fileInfo.fileName();
    obj["ext"] = fileInfo.suffix();
    obj["size"] = fileInfo.size();
    if (file.open(QIODevice::ReadOnly)) {
        obj["md5"] = QString(QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex());
    }
    QJsonDocument doc(obj);
    return QString(doc.toJson(QJsonDocument::Compact));
}

void QIM::sendMessage(const Message &message) {
    im::protocol::Packet packet;
    packet.set_type(im::protocol::SendMsg_req_);
    auto *msg_req = new im::protocol::SendMsg_req();
    auto *msg = Convert::message2proto(message);
    msg_req->set_allocated_message(msg);
    packet.set_allocated_sendmsg_req(msg_req);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::sendMessageToLocal(Message &message) {
    IMDataBase::saveOrUpdateMessage(message);
    Q_EMIT receiveMessage(message);
    updateSessionByMessage(message);
    m_msg_buf.insert(message.getId(),message);
    m_timer_resend_msg->start(1000);
}

