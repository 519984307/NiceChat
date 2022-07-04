#include "Message.h"

Message::Message(QObject *parent) : Table(parent),
    m_id(0),
    m_uuid(""),
    m_from_accid(""),
    m_to_accid(""),
    m_body(""),
    m_ex(""),
    m_time(""),
    m_scene(0),
    m_type(0)
{

}
