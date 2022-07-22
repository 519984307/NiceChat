#ifndef CONTACTCONTROLLER_H
#define CONTACTCONTROLLER_H

#include <QObject>
#include "ContactListModel.h"
#include "QUIHelper.h"
#include "QIM.h"

class ContactController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ContactListModel* contactModel READ contactModel)
    Q_PROPERTY(QJsonObject current READ current NOTIFY currentChanged)

public:
    explicit ContactController(QObject *parent = nullptr);
    ~ContactController() override;

    Q_SIGNAL void currentChanged();
    Q_INVOKABLE void setCurrent(int index){
        m_current = m_contactModel.getItem(index);
        Q_EMIT currentChanged();
    }
    [[nodiscard]] QJsonObject current() const{
        return m_current;
    }

    [[nodiscard]] ContactListModel* contactModel(){
        return &m_contactModel;
    }

    Q_INVOKABLE void loadContactModel();

    Q_INVOKABLE void jumpContact(const QString& accid);

private:
    ContactListModel m_contactModel;
    QJsonObject m_current;
};


#endif // CONTACTCONTROLLER_H
