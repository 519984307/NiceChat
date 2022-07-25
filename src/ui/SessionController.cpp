#include "SessionController.h"

SessionController::SessionController(QObject *parent)
    : QObject{parent} {
    connect(QIM::instance(),&QIM::updateSessionCompleted,this,[this](Session &session){
        session.handleContent();
        m_sessionModel.addOrUpdateData(session);
    });
    connect(QIM::instance(),&QIM::syncMessageCompleted,this,[this](){
        loadSessionModel();
    });
    connect(QIM::instance(),&QIM::deleteSessionCompleted,this,[this](const QString &accid){
        m_sessionModel.removeDataById(accid);
    });
}


SessionController::~SessionController() {

}

void SessionController::loadSessionModel() {
    const QList<Session> &list = QIM::instance()->getSessionList();
    for (int i = 0; i < list.size(); ++i) {
        auto &item = const_cast<Session &>(list.at(i));
        item.handleContent();
    }
    m_sessionModel.setNewData(list);
}

void SessionController::jumpSession(const QString& accid){
    int index = m_sessionModel.getIndexById(accid);
    if(index>=0){
        setCurrent(index);
        return;
    }
    Session session;
    session.setId(accid);
    session.setTime(QString::number(QUIHelper::instance()->currentTimeMillis()));
    m_sessionModel.addOrUpdateData(session);
    index = m_sessionModel.getIndexById(accid);
    setCurrent(index);
}

void SessionController::loadFileList(const QVariant& var){
    QList<QFileInfo> list;
    const QList<QUrl> &data = var.value<QList<QUrl>>();
    foreach (const QUrl &item, data)
    {
        list.append(QFileInfo(item.toLocalFile()));
    }
    m_fileModel.setNewData(list);
}

void SessionController::sendSelectedFile(const QString& sessionId,int scene){
    foreach (const QFileInfo &item, m_fileModel.getData())
    {
        if(QUIHelper::instance()->isImage(item.suffix())){
            QIM::instance()->sendImageMessage(sessionId,scene,item.absoluteFilePath());
        }else{
            QIM::instance()->sendFileMessage(sessionId,scene,item.absoluteFilePath());
        }
    }
}
