#include "Convert.h"

Convert::Convert(QObject *parent)
    : QObject{parent}
{

}

Message Convert::proto2message(const im::protocol::Message &it) {
    Message obj;
    obj.m_id = QString::fromStdString(it.uuid());
    obj.m_from_accid = QString::fromStdString(it.from());
    obj.m_to_accid = QString::fromStdString(it.to());
    obj.m_scene = it.scene();
    obj.m_type = it.type();
    obj.m_body = QString::fromStdString(it.body());
    obj.m_time = QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    obj.m_read_accids = QString::fromStdString(it.readaccids());
    obj.m_session_id = QString::fromStdString(it.sessionid());
    return obj;
}

Session Convert::message2Session(const Message &it) {
    Session session;
    session.m_id = it.m_session_id;
    session.m_body = it.m_body;
    session.m_scene = it.m_scene;
    session.m_status = it.m_status;
    session.m_time = it.m_time;
    session.m_type = it.m_type;
    return session;
}
