#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "database/Message.h"

class MessageListModel: public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        Uuid,
        Body,
        FromAccid,
        ToAccid,
        Scene,
        Type,
        Ex,
        Time,
        Status,
        SessionId,
        Attachment
    };

    explicit MessageListModel(QObject *parent = nullptr);
    ~MessageListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role =Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addData(const QList<Message> &list);

    void setNewData(const QList<Message> &list);

    void addOrUpdateData(const Message &message);

    Message* getFirstMessage();

    Q_INVOKABLE int count();

    Q_SIGNAL void viewToBottom();
    Q_SIGNAL void viewToPosition(int position);

private:
    QList<Message> m_messages;
};

#endif // MESSAGELISTMODEL_H
