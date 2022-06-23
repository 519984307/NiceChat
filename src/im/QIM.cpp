#include "QIM.h"

QIM::QIM(QObject *parent)
    : QObject{parent}
{
    socket = new QWebSocket();

    connect(socket,&QWebSocket::connected,[]{
        qDebug()<<"connected";
    });

    connect(socket,&QWebSocket::disconnected,[]{
        qDebug()<<"disconnected";
    });

    connect(socket,&QWebSocket::stateChanged,this,[this](QAbstractSocket::SocketState state){
        qDebug()<<"stateChanged:"<<state;
        switch (state) {
        case QAbstractSocket::UnconnectedState:
            setState(0);
            break;
        case QAbstractSocket::HostLookupState:
            setState(1);
            break;
        case QAbstractSocket::ConnectingState:
            setState(2);
            break;
        case QAbstractSocket::ConnectedState:
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
        sh::ByteBuf buf(frame.toStdString());
        auto commandId = buf.readChar();
        if(commandId == 0x00){
            im::proto::Result result;
            result.ParseFromString(buf.readBytes(frame.size()-1).data());
            if(result.command_id() == 0x03){
                if(result.success()){
                    Q_EMIT loginSuccess();
                }else{
                    Q_EMIT loginFail();
                }
            }
        }else if(commandId == 0x04){
            im::proto::User user;
            user.ParseFromString(buf.readBytes(frame.size()-1).data());
            std::string json;
            google::protobuf::util::MessageToJsonString(user,&json);
            setUserInfo(QString::fromStdString(json));
//            qDebug()<<"123456:"<<QString::fromStdString(json);
        }

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

    connect(socket,&QWebSocket::bytesWritten,this,[](qint64 bytes){
        qDebug()<<"bytesWritten"<<bytes;
    });


    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),this,
            [=](QAbstractSocket::SocketError error){
        qDebug()<<"binaryFrameReceived";
        //        Q_EMIT errorMessage(QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error));
    });

}

QIM::~QIM()
{
    socket->close();
    delete socket;
}

void QIM::login(const QString& url,const QString& accid,const QString& token){
    socket->open(url+"?accid="+accid+"&token="+token);
}
