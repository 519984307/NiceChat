#include "IMDataBase.h"

#include <memory>

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

void IMDataBase::syncMessage(const google::protobuf::RepeatedPtrField<im::protocol::Message> &messages) {
    QList<Message> messageList;
    QMap<QString, Message> map;
    for (int i = 0; i < messages.size(); ++i) {
        const im::protocol::Message &item = messages.Get(i);
        const Message &message = proto2message(item);
        map.insert(message.getSessionId(), message);
        messageList.append(message);
    }
    QList<Session> sessionList;
    for (const auto &item: map) {
        const Session &session = message2Session(item);
        sessionList.append(session);
    }
    qx::dao::insert(messageList);
    qx::dao::insert(sessionList);
}

Session IMDataBase::message2Session(const Message &it) {
    Session session;
    session.m_id = it.m_session_id;
    session.m_body = it.m_body;
    session.m_scene = it.m_scene;
    session.m_status = it.m_status;
    session.m_time = it.m_time;
    session.m_type = it.m_type;
    return session;
}

QSqlError IMDataBase::insertMsg(const im::protocol::Message &it) {
    Message message = proto2message(it);
    message.setStatus(1);
    return qx::dao::insert(message);
}

QSqlError IMDataBase::saveOrUpdateMsg(const im::protocol::Message &it) {
    Message message = proto2message(it);
    message.setStatus(0);
    return qx::dao::save(message);
}

QSqlError IMDataBase::saveOrUpdateMsg(const Message &it) {
    Message msg = it;
    return qx::dao::save(msg);
}

uint64_t IMDataBase::getMsgLastTime() {
    Message msg;
    qx_query query;
    query.orderDesc("message.time");
    query.limit(1);
    qx::dao::fetch_by_query(query, msg);
    return msg.getTime().toULongLong();
}

Message IMDataBase::proto2message(const im::protocol::Message &it) {
    Message obj;
    obj.m_id = QString::fromStdString(it.uuid());
    obj.m_from_accid = QString::fromStdString(it.from());
    obj.m_to_accid = QString::fromStdString(it.to());
    obj.m_scene = it.scene();
    obj.m_type = it.type();
    obj.m_body = QString::fromStdString(it.body());
    obj.m_time = QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    obj.m_session_id = QString::fromStdString(it.to());
    return obj;
}

Message IMDataBase::getMsgByUuid(const QString &uuid) {
    Message message;
    message.m_id = uuid;
    qx::dao::fetch_by_id<Message>(message);
    return message;
}

QList<Message> IMDataBase::getMessageListById(const QString &accid) {
    qx::QxSqlQuery query(QString("WHERE Message.from_accid = '%1' or Message.to_accid='%1'").arg(accid));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    return list;
}

QList<Session> IMDataBase::getSessionList() {
    QList<Session> list;
    qx::dao::fetch_all(list);
    return list;
}
