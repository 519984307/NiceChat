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
        t.data(&Session::m_top, "top");
    }
}

void Session::handleContent(){
    QJsonDocument doc = QJsonDocument::fromJson(getBody().toUtf8());
    QJsonObject obj = doc.object();
    switch(getType()){
    case 0:
        setContent(obj["msg"].toString());
        break;
    case 1:
        setContent("[图片]");
        break;
    case 2:
        setContent("[文件]");
        break;
    }
}
