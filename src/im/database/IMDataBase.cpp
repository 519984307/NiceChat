#include "IMDataBase.h"

IMDataBase::IMDataBase(QObject *parent) : QObject{parent}
{



}

IMDataBase::~IMDataBase(){


}

void IMDataBase::init(const QString& base64){
    qDebug()<<"开始初始化数据库："<<base64;
    QFile::remove(QString::fromStdString("./%1.sqlite").arg(base64));
    qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName(QString::fromStdString("./%1.sqlite").arg(base64));
    qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
    qx::QxSqlDatabase::getSingleton()->setUserName("root");
    qx::QxSqlDatabase::getSingleton()->setPassword("");

    // Only for debug purpose : assert if invalid offset detected fetching a relation
    qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);
    QSqlError daoError = qx::dao::create_table<message>();
    daoError = qx::dao::create_table<session>();
}

void IMDataBase::syncMessage(const ptrf &messages){
    list_message messageX;
    for (auto it = messages.begin(); it != messages.end(); ++it)
    {
        message_ptr obj; obj.reset(new message());
        obj->m_id = QString::fromStdString(it->uuid());
        obj->m_from_accid = QString::fromStdString(it-> from());
        obj->m_to_accid = QString::fromStdString(it-> to());
        obj->m_sence = it->scene();
        obj->m_type = it->type();
        obj->m_body = QString::fromStdString(it->body());
        obj->m_time= QString::number(it->time());
        obj->m_session_id = QString::fromStdString(it->sessionid());
        saveSession(obj);
        messageX.insert(obj->m_id,obj);
    }
    qx::dao::insert(messageX);
}

void IMDataBase::saveSession(message_ptr it){
    session_ptr obj; obj.reset(new session());
    obj->m_id = it->m_session_id;
    obj->m_from_accid = it->m_from_accid;
    obj->m_to_accid = it->m_to_accid;
    obj->m_type = it->m_type;
    obj->m_body = it->m_body;
    obj->m_time = it->m_time;
    obj->m_sence = it->m_sence;
    qx::dao::save(obj);
}

void IMDataBase::saveSession(const QString& accid){
    session_ptr obj; obj.reset(new session());
    obj->m_id = accid;
    obj->m_time = QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    qx::dao::insert(obj);
}

void IMDataBase::insertMsg(im::protocol::Message *it){
    list_message messageX;
    message_ptr obj; obj.reset(new message());
    obj->m_id = QString::fromStdString(it->uuid());
    obj->m_from_accid = QString::fromStdString(it-> from());
    obj->m_to_accid = QString::fromStdString(it-> to());
    obj->m_sence = it->scene();
    obj->m_type = it->type();
    obj->m_body = QString::fromStdString(it->body());
    obj->m_time= QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    obj->m_session_id = QString::fromStdString(it->to());
    saveSession(obj);
    messageX.insert(obj->m_id,obj);
    qx::dao::insert(messageX);
}

uint64_t IMDataBase::getMsgLastTime(){
    message msg;
    qx_query query;
    query.orderDesc("message.time");
    query.limit(1);
    qx::dao::fetch_by_query(query,msg);
    return msg.gettime().toULongLong();
}
