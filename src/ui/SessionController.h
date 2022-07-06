#ifndef SESSIONCONTROLLER_H
#define SESSIONCONTROLLER_H

#include <QObject>
#include "SessionListModel.h"
#include "QIM.h"

class SessionController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SessionListModel* sessionModel READ sessionModel)
    Q_PROPERTY(QJsonObject current READ current NOTIFY currentChanged)
public:
    explicit SessionController(QObject *parent = nullptr);
    ~SessionController() override;

    Q_SIGNAL void currentChanged();
    Q_INVOKABLE void setCurrent(int index){
        m_current = m_sessionModel.getItem(index);
        Q_EMIT currentChanged();
    }
    [[nodiscard]] QJsonObject current() const{
        return m_current;
    }


    [[nodiscard]] SessionListModel* sessionModel(){
        return &m_sessionModel;
    }

    Q_INVOKABLE void loadSessionModel();

private:
    SessionListModel m_sessionModel;
    QJsonObject m_current;
};


#endif // SESSIONCONTROLLER_H
