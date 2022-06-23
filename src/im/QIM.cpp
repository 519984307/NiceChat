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
            updateState(0);
            break;
        case QAbstractSocket::HostLookupState:
            updateState(1);
            break;
        case QAbstractSocket::ConnectingState:
            updateState(2);
            break;
        case QAbstractSocket::ConnectedState:
            updateState(3);
            break;
        case QAbstractSocket::BoundState:
            updateState(4);
            break;
        case QAbstractSocket::ClosingState:
            updateState(5);
            break;
        case QAbstractSocket::ListeningState:
            updateState(6);
            break;
        default:
            updateState(-1);
            break;
        }
    });

    connect(socket,&QWebSocket::binaryMessageReceived,this,[this](const QByteArray &frame){
        sh::ByteBuf buf(frame.toStdString());
        switch (buf.readChar()) {
        case 0x00:
            im::proto::Result result;
            qDebug()<<QString::fromStdString(buf.toHexString());
            result.ParseFromString(buf.readBytes(frame.size()-1).data());
            if(result.command_id() == 0x03){
                if(result.success()){
                    Q_EMIT loginSuccess();
                }else{
                    Q_EMIT loginFail();
                }
            }
            break;
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
