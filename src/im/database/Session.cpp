#include "Session.h"

QX_REGISTER_CPP_QX_IM(Session)

namespace qx {
    template<>
    void register_class(QxClass<Session> &t) {
        t.id(&Session::m_id, "id");
        t.data(&Session::m_body, "body");
        t.data(&Session::m_scene, "scene");
        t.data(&Session::m_type, "type");
        t.data(&Session::m_ex, "ex");
        t.data(&Session::m_time, "time");
        t.data(&Session::m_unread, "unread");
        t.data(&Session::m_status, "status");
    }
}
