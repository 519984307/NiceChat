#include "QIM.h"

QIM::QIM(QObject *parent)
    : QObject{parent}
{
    socket = new QWebSocket();
    m_timer_heart =new QTimer();

    setMessageModel(new qx::QxModel<message>());

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
        }


        //        auto commandId = buf.readUnsignedChar();
        //        qDebug()<<"--------------binaryMessageReceived-------------commandId:"<<commandId;
        //        if(commandId == 0x00){
        //            im::proto::Result result;
        //            result.ParseFromString(buf.readBytes(frame.size()-1).data());
        //            if(result.command_id() == 0x03){
        //                if(result.success()){
        //                    initDataBase(m_login_accid);
        //                    startHeartBeat();
        //                    Q_EMIT loginSuccess();
        //                }else{
        //                    Q_EMIT loginFail();
        //                }
        //            }
        //        }else if(commandId == 0x04){
        //            im::proto::User user;
        //            user.ParseFromString(buf.readBytes(frame.size()-1).data());
        //            std::string json;
        //            google::protobuf::util::MessageToJsonString(user,&json);
        //            setUserInfo(QString::fromStdString(json));
        //        }else if(commandId == 0xFF){
        //            m_heart_count = 0;
        //        }else if(commandId == 0x05){
        //            im::proto::Friends friends;
        //            friends.ParseFromString(buf.readBytes(frame.size()-1).data());
        //            std::string json;
        //            google::protobuf::util::MessageToJsonString(friends,&json);
        //            setFriends(QString::fromStdString(json));
        //        }else if(commandId == 0x01){
        //            im::proto::Message message;
        //            message.ParseFromString(buf.readBytes(frame.size()-1).data());
        //            qDebug()<<QString::fromStdString(message.body());
        //        }else if(commandId == 0x07){
        //            im::proto::MessageList messageList;
        //            messageList.ParseFromString(buf.readBytes(frame.size()-1).data());
        //            m_databse.syncMessage(messageList);
        //            m_messageModel->qxFetchAll();
        //        }

        //        if((unsigned char)frame[0] == 0x1){
        //            QByteArray data = frame.sliced(1,frame.size()-1);
        //            im::proto::Message message;
        //            message.ParseFromString(data.toStdString());
        //            Q_EMIT textMessageReceived(QString::fromStdString(message.body()));
        //        }else if((unsigned char)frame[0] == 0x2){
        //            QByteArray data = frame.sliced(1,frame.size()-1);
        //            im::proto::Online online;
        //            online.ParseFromString(data.toStdString());
        //            std::string json;
        //            google::protobuf::util::MessageToJsonString(online,&json);
        //            Q_EMIT lineStatusChanged(QString::fromStdString(json));
        //        }
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
    im::protocol::SendMsg_req *msg = new im::protocol::SendMsg_req();
    msg->set_uuid(QUuid::createUuid().toString().remove("{").remove("}").toStdString());
    msg->set_body(text.toStdString());
    msg->set_from(from.toStdString());
    msg->set_to(to.toStdString());
    msg->set_scene(0);
    msg->set_type(0);
    packet.set_allocated_sendmsg_req(msg);
//    packet.unsafe_arena_set_allocated_sendmsg_req(&message);
    socket->sendBinaryMessage(QByteArray::fromStdString(packet.SerializeAsString()));
}

void QIM::initDataBase(const QString &text){
    m_databse.init(text.toUtf8().toBase64());
    sendSyncMessage();
}

void QIM::sendSyncMessage(){
    sh::ByteBuf buf;
    buf.writeChar(0x06);
    socket->sendBinaryMessage(QByteArray::fromStdString(buf.data()));
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

void QIM::test(){

}
