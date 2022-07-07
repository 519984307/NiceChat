#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include <QObject>
#include <GlobalStatic.h>
#include "MessageListModel.h"
#include "QIM.h"

class MessageController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MessageListModel* messageModel READ messageModel)
    Q_PROPERTY(QString currentId READ currentId WRITE setCurrentId NOTIFY currentIdChanged)
public:
    explicit MessageController(QObject *parent = nullptr);
    ~MessageController() override;


    Q_SIGNAL void currentIdChanged();
    void setCurrentId(QString const& accid){
        m_currentId = accid;
        Q_EMIT currentIdChanged();
    }
    [[nodiscard]] QString currentId() const{
        return m_currentId;
    }


    [[nodiscard]] MessageListModel* messageModel(){
        return &m_messageModel;
    }

    Q_INVOKABLE void loadMessageData(const QString &accid);

private:
    MessageListModel m_messageModel;
    QString m_currentId;
};

#endif // MESSAGECONTROLLER_H
