#include "SessionDo.h"

QX_REGISTER_CPP_QX_BLOG(session)

namespace qx {
    template <> void register_class(QxClass<session> & t)
    {
        t.id(& session::m_id, "id");
        t.data(& session::m_body, "body");
        t.data(& session::m_from_accid, "from_accid");
        t.data(& session::m_to_accid, "to_accod");
        t.data(& session::m_sence, "sence");
        t.data(& session::m_type, "type");
        t.data(& session::m_ex, "ex");
        t.data(& session::m_time, "time");
    }
}
