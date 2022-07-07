#include "MessageController.h"

MessageController::MessageController(QObject *parent)
    : QObject{parent}
{
    connect(QIM::instance(),&QIM::receiveMessage,this,[this](const Message &message){
        if(m_currentId==message.getSessionId()){
            m_messageModel.addOrUpdateData(message);
        }
    });
}


MessageController::~MessageController(){

}

void MessageController::loadMessageData(const QString &accid){
    const QList<Message> &list = QIM::instance()->getMessageListById(accid);
    m_messageModel.setNewData(list);
}
