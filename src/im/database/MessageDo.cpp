#include "MessageDo.h"

QX_REGISTER_CPP_QX_BLOG(message)

namespace qx {
    template <> void register_class(QxClass<message> & t)
    {
        t.id(& message::m_id, "id");
        t.data(& message::m_body, "body");
        t.data(& message::m_from_accid, "from_accid");
        t.data(& message::m_to_accid, "to_accod");
        t.data(& message::m_sence, "sence");
        t.data(& message::m_type, "type");
        t.data(& message::m_ex, "ex");
        t.data(& message::m_time, "time");
    }
}
