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
}

void IMDataBase::syncMessage(im::proto::MessageList messages){
    ptrf *data = messages.mutable_messages();
    list_message messageX;
    for (ptrf::iterator it = data->begin(); it != data->end(); ++it)
    {
        message_ptr obj; obj.reset(new message());
        obj->m_id = QString::number(it->id());
        obj->m_from_accid = QString::fromStdString(it-> from());
        obj->m_to_accid = QString::fromStdString(it-> to());
        obj->m_sence = it->scene();
        obj->m_type = it->type();
        obj->m_body = QString::fromStdString(it->body());
        obj->m_time= QString::number(it->time());
        messageX.insert(obj->m_id,obj);
    }
    qx::dao::insert(messageX);
}
