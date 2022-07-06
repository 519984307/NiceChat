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
public:
    explicit MessageController(QObject *parent = nullptr);
    ~MessageController() override;


    [[nodiscard]] MessageListModel* messageModel(){
        return &m_messageModel;
    }

    Q_INVOKABLE void loadMessageData(const QString &accid);

private:
    MessageListModel m_messageModel;
};

#endif // MESSAGECONTROLLER_H
