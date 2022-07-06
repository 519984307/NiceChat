#include "SessionController.h"

SessionController::SessionController(QObject *parent)
        : QObject{parent} {
    loadSessionModel();
}


SessionController::~SessionController() {

}

void SessionController::loadSessionModel() {
    const QList<Session> &list = QIM::instance()->getSessionList();
    m_sessionModel.setNewData(list);
}
