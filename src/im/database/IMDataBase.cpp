#include "IMDataBase.h"

IMDataBase::IMDataBase(QObject *parent) : QObject{parent} {

}

IMDataBase::~IMDataBase() = default;

void IMDataBase::initDb(const QString &base64) {
    qDebug() << "开始初始化数据库：" << base64;
    QFile::remove(QString::fromStdString("./%1.sqlite").arg(base64));
    qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName(QString::fromStdString("./%1.sqlite").arg(base64));
    qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
    qx::QxSqlDatabase::getSingleton()->setUserName("root");
    qx::QxSqlDatabase::getSingleton()->setPassword("");

    // Only for debug purpose : assert if invalid offset detected fetching a relation
    qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);
    QSqlError daoError = qx::dao::create_table<Message>();
    daoError = qx::dao::create_table<Session>();
    initMessageStatus();
}

void IMDataBase::initMessageStatus() {
    qx::QxSqlQuery query(QString("WHERE Message.status = %1").arg(1));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    for (int i = 0; i < list.size(); ++i) {
        auto &item = const_cast<Message &>(list.at(i));
        item.setStatus(2);
    }
    qx::dao::save(list);
}

QSqlError IMDataBase::insertMessage(const Message &it) {
    Message message = it;
    return qx::dao::insert(message);
}

QSqlError IMDataBase::saveOrUpdateMessage(const Message &it) {
    Message message = it;
    return qx::dao::save(message);
}

QSqlError IMDataBase::saveOrUpdateSession(const Session &it){
    Session session = it;
    return qx::dao::save(session);
}

uint64_t IMDataBase::getMessageLastTime() {
    Message message;
    qx_query query;
    query.orderDesc("Message.time");
    query.limit(1);
    qx::dao::fetch_by_query(query, message);
    return message.getTime().toULongLong();
}

Message IMDataBase::getMsgByUuid(const QString &uuid) {
    Message message;
    message.m_id = uuid;
    qx::dao::fetch_by_id<Message>(message);
    return message;
}

QList<Message> IMDataBase::getMessageListById(const QString &accid) {
    qx::QxSqlQuery query(QString("WHERE Message.session_id = '%1'").arg(accid));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    return list;
}

Session IMDataBase::getSessionById(const QString &id){
    Session session;
    session.m_id = id;
    qx::dao::fetch_by_id<Session>(session);
    return session;
}

QList<Session> IMDataBase::getSessionList() {
    QList<Session> list;
    qx::dao::fetch_all(list);
    return list;
}

QList<Message> IMDataBase::getUnreadMessageList(const QString &sessionId,const QString &accid){
    qx::QxSqlQuery query(QString("where session_id = '%1' and from_accid != '%2'").arg(sessionId).arg(accid));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    QList<Message> data;
    for (int i = 0; i < list.size(); ++i) {
        auto &item = const_cast<Message &>(list.at(i));
        if (!item.m_read_accids.contains(accid)) {
            data.append(item);
        }
    }
    return data;
}
