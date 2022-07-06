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
}

void IMDataBase::syncMessage(const ptrf &messages) {
    list_message messageX;
    for (const auto &it: messages) {
        const std::shared_ptr<Message> &obj = proto2message(it);
        messageX.insert(obj->m_id, obj);
    }
    qx::dao::insert(messageX);
}

QSqlError IMDataBase::insertMsg(const im::protocol::Message &it) {
    list_message messageX;
    const std::shared_ptr<Message> &obj = proto2message(it);
    obj->setStatus(1);
    messageX.insert(obj->m_id, obj);
    return qx::dao::insert(messageX);
}

QSqlError IMDataBase::saveOrUpdateMsg(const im::protocol::Message &it){
    const std::shared_ptr<Message> &obj = proto2message(it);
    obj->setStatus(0);
    return qx::dao::save(obj);
}

uint64_t IMDataBase::getMsgLastTime() {
    Message msg;
    qx_query query;
    query.orderDesc("message.time");
    query.limit(1);
    qx::dao::fetch_by_query(query, msg);
    return msg.getTime().toULongLong();
}

std::shared_ptr<Message> IMDataBase::proto2message(const im::protocol::Message &it) {
    message_ptr obj;
    obj = std::make_shared<Message>();
    obj->m_id = QString::fromStdString(it.uuid());
    obj->m_from_accid = QString::fromStdString(it.from());
    obj->m_to_accid = QString::fromStdString(it.to());
    obj->m_scene = it.scene();
    obj->m_type = it.type();
    obj->m_body = QString::fromStdString(it.body());
    obj->m_time = QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    obj->m_session_id = QString::fromStdString(it.to());
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
