#include "SessionController.h"

SessionController::SessionController(QObject *parent)
    : QObject{parent} {
    connect(QIM::instance(),&QIM::updateSession,this,[this](const Session &session){
        m_sessionModel.addOrUpdateData(session);
    });
    connect(QIM::instance(),&QIM::syncMessageCompleted,this,[this](){
        loadSessionModel();
    });
}


SessionController::~SessionController() {

}

void SessionController::loadSessionModel() {
    const QList<Session> &list = QIM::instance()->getSessionList();
    m_sessionModel.setNewData(list);
}

void SessionController::jumpSession(const QString& accid){
    int index = m_sessionModel.getIndexByAccid(accid);
    if(index>=0){
        Q_EMIT sessionIndexSelected(index);
        return;
    }
    Session session;
    session.setId(accid);
    session.setTime(QString::number(QUIHelper::instance()->currentTimeMillis()));
    m_sessionModel.addOrUpdateData(session);
    Q_EMIT sessionIndexSelected(m_sessionModel.count()-1);
}
