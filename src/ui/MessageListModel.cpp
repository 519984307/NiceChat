#include "MessageListModel.h"

MessageListModel::MessageListModel(QObject *parent) : QAbstractListModel(parent) {


}

MessageListModel::~MessageListModel(){

}

int MessageListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_messages.count();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_messages.count())
        return {};
    const Message &message = m_messages[index.row()];
    if (role == Uuid)
        return message.getId();
    else if (role == Body)
        return message.getBody();
    else if (role == FromAccid)
        return message.getFromAccid();
    else if (role == ToAccid)
        return message.getToAccid();
    else if (role == Scene)
        return message.getScene();
    else if (role == Type)
        return message.getType();
    else if (role == Ex)
        return message.getEx();
    else if (role == Time)
        return message.getTime();
    else if (role == Status)
        return message.getStatus();
    else if (role == SessionId)
        return message.getSessionId();
    return {};
}

QHash<int, QByteArray> MessageListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Uuid] = "uuid";
    roles[Body] = "body";
    roles[FromAccid] = "fromAccid";
    roles[ToAccid] = "toAccid";
    roles[Scene] = "scene";
    roles[Type] = "type";
    roles[Ex] = "ex";
    roles[Time] = "time";
    roles[Status] = "status";
    roles[SessionId] = "sessionId";
    return roles;
}

void MessageListModel::addData(const QList<Message> &list) {
    if(list.count() > 0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_messages.append(list);
        endInsertRows();
        Q_EMIT viewToBottom();
    }
}

void MessageListModel::setNewData(const QList<Message> &list) {
    if(rowCount()>0){
        beginRemoveRows(QModelIndex(),0,rowCount()-1);
        m_messages.clear();
        endRemoveRows();
    }
    if(list.count()>0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_messages.append(list);
        endInsertRows();
        Q_EMIT viewToBottom();
    }
}

void MessageListModel::addOrUpdateData(const Message &message){
    for (int i = 0; i < m_messages.size(); ++i)
    {
        auto &item = const_cast<Message &>(m_messages.at(i));
        if (item.getId() == message.getId()){
            item.setTime(message.getTime());
            item.setStatus(message.getStatus());
            Q_EMIT dataChanged(this->index(i),this->index(i));
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_messages.append(message);
    endInsertRows();
    Q_EMIT viewToBottom();
}

int MessageListModel::count(){
    return m_messages.count();
}
