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
    // 0:可加载更多 1：正在加载 2：所有数据加载完成
    Q_PROPERTY(int loadStatus READ loadStatus WRITE setLoadStatus NOTIFY loadStatusChanged)
public:
    explicit MessageController(QObject *parent = nullptr);
    ~MessageController() override;


    Q_SIGNAL void currentIdChanged();
    void setCurrentId(QString const& accid){
        m_currentId = accid;
        m_anchor = nullptr;
        setLoadStatus(0);
        Q_EMIT currentIdChanged();
    }
    [[nodiscard]] QString currentId() const{
        return m_currentId;
    }

    Q_SIGNAL void loadStatusChanged();
    void setLoadStatus(int loadStatus){
        m_loadStatus = loadStatus;
        Q_EMIT loadStatusChanged();
    }
    [[nodiscard]] int loadStatus() const{
        return m_loadStatus;
    }


    [[nodiscard]] MessageListModel* messageModel(){
        return &m_messageModel;
    }

    Q_INVOKABLE void loadMessageData();

private:
    MessageListModel m_messageModel;
    Message* m_anchor = nullptr;
    int m_loadStatus = 0;
    QString m_currentId;
};

#endif // MESSAGECONTROLLER_H
