#ifndef SESSION_H
#define SESSION_H

#include "precompiled.h"

class QX_IM_DLL_EXPORT Session {
public:

    Session() : m_id("0"), m_scene(0), m_type(0), m_unread(0),m_time("0"),m_status(0) ,m_top(false){ ; }

    Session(const Session &) = default;

    Session &operator=(const Session &) = default;

    ~Session() = default;

    QString m_id;

    [[nodiscard]] QString getId() const { return m_id; };

    void setId(const QString &val) { m_id = val; };

    QString m_body;

    [[nodiscard]] QString getBody() const { return m_body; };

    void setBody(const QString &val) { m_body = val; };

    int m_scene;

    [[nodiscard]] int getScene() const { return m_scene; };

    void setScene(const int &val) { m_scene = val; };

    int m_type;

    [[nodiscard]] int getType() const { return m_type; };

    void setType(const int &val) { m_type = val; };

    int m_unread;

    [[nodiscard]] int getUnread() const { return m_unread; };

    void setUnread(const int &val) { m_unread = val; };

    QString m_ex;

    [[nodiscard]] QString getEx() const { return m_ex; };

    void setEx(const QString &val) { m_ex = val; };

    QString m_time;

    [[nodiscard]] QString getTime() const { return m_time; };

    void setTime(const QString &val) { m_time = val; };

    int m_status;

    [[nodiscard]] int getStatus() const { return m_status; };

    void setStatus(const int &val) { m_status = val; };

    bool m_top;

    [[nodiscard]] bool getTop() const { return m_top; };

    void setTop(const bool &val) { m_top = val; };

    QString m_content;

    [[nodiscard]] QString getContent() const { return m_content; };

    void setContent(const QString &val) { m_content = val; };

    void handleContent();

};

QX_REGISTER_PRIMARY_KEY(Session, QString)
QX_REGISTER_HPP_QX_IM (Session, qx::trait::no_base_class_defined, 1)

#endif // SESSION_H
