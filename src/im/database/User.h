#ifndef USER_H
#define USER_H

#include "precompiled.h"

class QX_IM_DLL_EXPORT User {
public:

    User() : m_accid("0") { ; }

    User(const User &) = default;

    User &operator=(const User &) = default;

    ~User() = default;

    QString m_accid;

    [[nodiscard]] QString getAccid() const { return m_accid; };

    void setAccid(const QString &val) { m_accid = val; };

    QString m_name;

    [[nodiscard]] QString getName() const { return m_name; };

    void setName(const QString &val) { m_name = val; };

    QString m_icon;

    [[nodiscard]] QString getIcon() const { return m_icon; };

    void setIcon(const QString &val) { m_icon = val; };

    QString m_sign;

    [[nodiscard]] QString getSign() const { return m_sign; };

    void setSign(const QString &val) { m_sign = val; };

    QString m_birth;

    [[nodiscard]] QString getBirth() const { return m_birth; };

    void setBirth(const QString &val) { m_birth = val; };

    QString m_mobile;

    [[nodiscard]] QString getMobile() const { return m_mobile; };

    void setMobile(const QString &val) { m_mobile = val; };

    int m_gender;

    [[nodiscard]] int getGender() const { return m_gender; };

    void setGender(const int &val) { m_gender = val; };

    QString m_ex;

    [[nodiscard]] QString getEx() const { return m_ex; };

    void setEx(const QString &val) { m_ex = val; };

};

QX_REGISTER_PRIMARY_KEY(User, QString)
QX_REGISTER_HPP_QX_IM (User, qx::trait::no_base_class_defined, 1)

#endif // USER_H
