#include "IMDataBase.h"

#include "Message.h"

IMDataBase::IMDataBase(): Nut::Database()
  , m_message(new Nut::TableSet<Message>(this))
{

}
