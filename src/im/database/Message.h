#ifndef MESSAGE_H
#define MESSAGE_H

#include "precompiled.h"

class QX_IM_DLL_EXPORT message {
public:

    message() : m_id("0"), m_scene(0), m_type(0), m_time("0") { ; }

    virtual ~message() = default;

    QString m_id;

    [[nodiscard]] QString getMessageId() const { return m_id; };

    void setMessageId(const QString &val) { m_id = val; };

    QString m_body;

    [[nodiscard]] QString getBody() const { return m_body; };

    void setBody(const QString &val) { m_body = val; };

    QString m_from_accid;

    [[nodiscard]] QString getFromAccid() const { return m_from_accid; };

    void setFromAccid(const QString &val) { m_from_accid = val; };

    QString m_to_accid;

    [[nodiscard]] QString getToAccid() const { return m_to_accid; };

    void setToAccid(const QString &val) { m_to_accid = val; };

    int m_scene;

    [[nodiscard]] int getScene() const { return m_scene; };

    void setScene(const int &val) { m_scene = val; };

    int m_type;

    [[nodiscard]] int getType() const { return m_type; };

    void setType(const int &val) { m_type = val; };

    QString m_ex;

    [[nodiscard]] QString getEx() const { return m_ex; };

    void setEx(const QString &val) { m_ex = val; };

    QString m_time;

    [[nodiscard]] QString getTime() const { return m_time; };

    void setTime(const QString &val) { m_time = val; };

    QString m_session_id;

    [[nodiscard]] QString getSessionId() const { return m_session_id; };

    void setSessionId(const QString &val) { m_session_id = val; };
};

QX_REGISTER_PRIMARY_KEY(message, QString)
QX_REGISTER_HPP_QX_IM (message, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<message> message_ptr;
typedef qx::QxCollection<QString, message_ptr> list_message;


#endif // MESSAGE_H
