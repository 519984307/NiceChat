#ifndef SESSIONDO_H
#define SESSIONDO_H

#include "./../precompiled.h"

class QX_BLOG_DLL_EXPORT session
{
public:

    session() : m_id("0"),m_sence(0),m_type(0),m_time("0") { ; }
    virtual ~session() { ; }

    QString m_id;
    QString getsession_id() const{return m_id;};
    void setsession_id(const QString & val){m_id=val;};

    QString m_body;
    QString getbody() const{return m_body;};
    void setbody(const QString & val){m_body=val;};

    QString m_from_accid;
    QString getfrom_accid() const{return m_from_accid;};
    void setfrom_accid(const QString & val){m_from_accid=val;};

    QString m_to_accid;
    QString getto_accod() const{return m_to_accid;};
    void setto_accod(const QString & val){m_to_accid=val;};

    int m_sence;
    int getsence() const{return m_sence;};
    void setsence(const int & val){m_sence=val;};

    int m_type;
    int gettype() const{return m_type;};
    void settype(const int & val){m_type=val;};

    QString m_ex;
    QString getm_ex() const{return m_ex;};
    void setm_ex(const QString & val){m_ex=val;};

    QString m_time;
    QString gettime() const{return m_time;};
    void settime(const QString & val){m_time=val;};

};

QX_REGISTER_PRIMARY_KEY(session, QString)
QX_REGISTER_HPP_QX_BLOG(session, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<session> session_ptr;
typedef qx::QxCollection<QString, session_ptr> list_session;

#endif // SESSIONDO_H
