#include "ContactController.h"

ContactController::ContactController(QObject *parent)
    : QObject{parent} {
    connect(QIM::instance(),&QIM::syncFriendCompleted,this,[this](){
        loadContactModel();
    });
}


ContactController::~ContactController() {

}

void ContactController::loadContactModel() {
    const QList<User> &list = QIM::instance()->getFriendList();
    m_contactModel.setNewData(list);
}

void ContactController::jumpContact(const QString& accid){
    int index = m_contactModel.getIndexByAccid(accid);
    if(index>=0){
        setCurrent(index);
    }
}
