#include "QIM.h"

#include <QtNut/sqlitegenerator.h>
#include <QtNut/sqlservergenerator.h>

QIM::QIM(QObject *parent)
    : QObject{parent}
{

    REGISTER(Message);
    REGISTER(IMDataBase);

    socket = new QWebSocket();
    m_timer_heart =new QTimer();
    connect(m_timer_heart,&QTimer::timeout,this,&QIM::heartBeat);
    m_timer_heart_count =new QTimer();
    connect(m_timer_heart_count,&QTimer::timeout,this,&QIM::heartBeatCount);
    m_timer_reconnect = new QTimer();
    connect(m_timer_reconnect,&QTimer::timeout,this,&QIM::reconnect);
    connect(socket,&QWebSocket::stateChanged,this,[this](QAbstractSocket::SocketState state){
        switch (state) {
        case QAbstractSocket::UnconnectedState:
            if(!m_userInfo.isEmpty()){
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

    connect(socket,&QWebSocket::binaryMessageReceived,this,[this](const QByteArray &frame){
        im::protocol::Packet packet;
        packet.ParseFromString(frame.toStdString());
        auto type = packet.type();
        if(type == im::protocol::Login_rsp_){
            if(packet.login_rsp().result().success()){
                startHeartBeat();
                getFriends();
                getProfile();
                initDataBase(m_login_accid);
                Q_EMIT loginSuccess();
            }else{
                Q_EMIT loginFail();
            }
        } else if(type == im::protocol::Heart_rsp_){
            if(packet.heart_rsp().result().success()){
                m_heart_count = 0;
            }
        } else if(type == im::protocol::GetFriends_rsp_){
            if(packet.getfriends_rsp().result().success()){
                std::string json;
                google::protobuf::util::MessageToJsonString(packet.getfriends_rsp(),&json);
                setFriends(QString::fromStdString(json));
            }
        } else if(type == im::protocol::GetProfile_rsp_){
            if(packet.getprofile_rsp().result().success()){
                std::string json;
                google::protobuf::util::MessageToJsonString(packet.getprofile_rsp().user(),&json);
                setUserInfo(QString::fromStdString(json));
            }
        } else if(type == im::protocol::SyncMsg_rsp_){
            if(packet.syncmsg_rsp().result().success()){
                std::string json;
                google::protobuf::util::MessageToJsonString(packet.syncmsg_rsp(),&json);
                qDebug()<<QString::fromStdString(json);
            }
        }
    });

    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),this,
            [=](QAbstractSocket::SocketError error){
        Q_EMIT errorMessage(QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error));
    });

}

QIM::~QIM()
{
    socket->close();
    m_timer_heart->stop();
    m_timer_heart_count->stop();
    m_timer_reconnect->stop();
    delete socket;
    delete m_timer_heart;
    delete m_timer_heart_count;
    delete m_timer_reconnect;
}

void QIM::login(const QString& url,const QString& accid,const QString& token){
    m_ws = url+"?accid="+accid+"&token="+token;
    m_login_accid = accid;
    m_login_token = token;
    qDebug()<<"start login";
    socket->open(m_ws);
}

void QIM::heartBeat(){
    im::protocol::Packet packet;
    packet.set_type(im::protocol::Heart_req_);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
    socket->flush();
}

void QIM::reconnect(){
    socket->open(m_ws);
}

void QIM::heartBeatCount(){
    m_heart_count = m_heart_count + 1;
    if(m_heart_count>13){
        socket->close();
    }
}

void QIM::startHeartBeat(){
    m_timer_heart_count->start(1000);
    m_timer_heart->start(9000);
}

void QIM::stopHeartBeat(){
    m_timer_heart->stop();
    m_timer_heart_count->stop();
}

void QIM::sendTextMessage(const QString& from,const QString& to,const QString& text){
    im::protocol::Packet packet;
    packet.set_type(im::protocol::SendMsg_req_);
    im::protocol::SendMsg_req *msg_req = new im::protocol::SendMsg_req();
    im::protocol::Message *msg = new im::protocol::Message();
    msg->set_uuid(QUuid::createUuid().toString().remove("{").remove("}").toStdString());
    msg->set_body(text.toStdString());
    msg->set_from(from.toStdString());
    msg->set_to(to.toStdString());
    msg->set_sessionid(to.toStdString());
    msg->set_scene(0);
    msg->set_type(0);
    msg_req->set_allocated_message(msg);

    //    auto message = create<Message>();
    //    message->setUuid(QString::fromStdString(msg->uuid()));
    //    message->setFromAccid(QString::fromStdString(msg->from()));
    //    message->setToAccid(QString::fromStdString(msg->to()));
    //    message->setTime(QString::number(msg->time()));
    //    message->setBody(QString::fromStdString(msg->body()));
    //    message->setScene(msg->scene());
    //    message->setType(msg->type());
    //    m_db.message()->append(message);
    //    m_db.saveChanges();

    packet.set_allocated_sendmsg_req(msg_req);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
}

void QIM::initDataBase(const QString &text){
    sendSyncMessage();
    QString name = text.toUtf8().toBase64();
    m_db.setDriver(DRIVER);
    m_db.setHostName(HOST);
    m_db.setDatabaseName(DATABASE(name));
    m_db.setUserName(USERNAME);
    m_db.setPassword(PASSWORD);

    m_db.open();

    auto query = m_db.message()->query();
    query->remove();

    auto message = Nut::create<Message>();
    message->setUuid("5e6b53c9-f1a4-411e-9f77-1ff4398db958");
    message->setFromAccid("admin");
    message->setToAccid("shaheshang");
    message->setTime("1656514235131");
    message->setBody("撒地方阿迪斯");
    message->setScene(0);
    message->setType(0);
    m_db.message()->append(message);
    int row = m_db.saveChanges();
    qDebug()<<"aaaaaaaaaaaaaaaaaa:"<<row;
}

void QIM::sendSyncMessage(){
    im::protocol::Packet packet;
    packet.set_type(im::protocol::SyncMsg_req_);
    im::protocol::SyncMsg_req *req = new im::protocol::SyncMsg_req();
    req->set_lastmsgtime(0);
    packet.set_allocated_syncmsg_req(req);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
}

void QIM::getFriends(){
    im::protocol::Packet packet;
    packet.set_type(im::protocol::GetFriends_req_);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
}

void QIM::getProfile(){
    im::protocol::Packet packet;
    packet.set_type(im::protocol::GetProfile_req_);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
}

void QIM::saveSession(const QString& accid){

}

void QIM::updateMessageModel(const QString& accid){

}

void QIM::test(){

}
