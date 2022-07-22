#include "MessageController.h"

MessageController::MessageController(QObject *parent)
    : QObject{parent}
{
    connect(QIM::instance(),&QIM::receiveMessage,this,[this](Message &message){
        if(m_currentId==message.getSessionId()){
            message.handleAttachment();
            m_messageModel.addOrUpdateData(message);
        }
    });
}


MessageController::~MessageController(){

}

void MessageController::loadMessageData(){
    if(m_loadStatus != 0)
        return;
    setLoadStatus(1);
    const QList<Message> &list = QIM::instance()->getMessageList(m_currentId,m_anchor);
    for (int i = 0; i < list.size(); ++i) {
        auto &item = const_cast<Message &>(list.at(i));
        item.handleAttachment();
    }
    if(m_anchor == nullptr){
        m_messageModel.setNewData(list);
    }else{
        m_messageModel.addData(list);
    }
    setLoadStatus(0);
    if(list.count() < 20){
        setLoadStatus(2);
    }
    m_anchor =  m_messageModel.getFirstMessage();
}
