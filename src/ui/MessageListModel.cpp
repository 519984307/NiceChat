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
        return message.getMessageId();
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
    roles[SessionId] = "sessionId";
    return roles;
}

void MessageListModel::addData(const QList<Message> &list) {
    if(list.count() > 0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_messages.append(list);
        endInsertRows();
    }
}

void MessageListModel::setData(const QList<Message> &list) {
    if(rowCount()>0){
        beginRemoveRows(QModelIndex(),0,rowCount()-1);
        m_messages.clear();
        endRemoveRows();
    }
    if(list.count()>0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_messages.append(list);
        endInsertRows();
    }
}

int MessageListModel::count(){
    return m_messages.count();
}
