#include "User.h"

QX_REGISTER_CPP_QX_IM(User)

namespace qx {
    template<>
    void register_class(QxClass<User> &t) {
        t.id(&User::m_accid, "id");
        t.data(&User::m_name, "name");
        t.data(&User::m_icon, "icon");
        t.data(&User::m_sign, "sign");
        t.data(&User::m_birth, "birth");
        t.data(&User::m_mobile, "mobile");
        t.data(&User::m_gender, "gender");
        t.data(&User::m_ex, "ex");
    }
}
