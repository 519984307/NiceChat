#include "MessageController.h"

MessageController::MessageController(QObject *parent)
    : QObject{parent}
{
    connect(QIM::instance(),&QIM::receiveMessage,this,[this](const Message &message){
        QList<Message> list;
        list.append(message);
        m_messageModel.addData(list);
    });
}


MessageController::~MessageController(){

}

void MessageController::loadMessageData(const QString &accid){
    const QList<Message> &list = IM->getMessageListById(accid);
    m_messageModel.setData(list);
}
