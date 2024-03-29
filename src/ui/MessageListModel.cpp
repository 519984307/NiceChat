﻿#include "MessageListModel.h"

MessageListModel::MessageListModel(QObject *parent) : QAbstractListModel(parent) {


}

MessageListModel::~MessageListModel(){

}

int MessageListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_messages.count();
}

Message* MessageListModel::getFirstMessage(){
    if(m_messages.isEmpty())
        return nullptr;
    return &m_messages.first();
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
    else if (role == Attachment)
        return message.getAttachment();
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
    roles[Attachment] = "attachment";
    return roles;
}

void MessageListModel::addData(const QList<Message> &list) {
    if(list.count() > 0){
        beginInsertRows(QModelIndex(), 0, list.count() - 1);
        for (int i = 0; i < list.size(); ++i)
        {
            const Message &item = list.at(i);
            m_messages.insert(0,item);
        }
        endInsertRows();
    }
    Q_EMIT viewToPosition(list.count());
}

void MessageListModel::setNewData(const QList<Message> &list) {
    if(rowCount()>0){
        beginRemoveRows(QModelIndex(),0,rowCount()-1);
        m_messages.clear();
        endRemoveRows();
    }
    if(list.count()>0){
        beginInsertRows(QModelIndex(), 0, list.count() - 1);
        for (int i = 0; i < list.size(); ++i)
        {
            const Message &item = list.at(i);
            m_messages.insert(0,item);
        }
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
            item.setBody(message.getBody());
            item.setAttachment(message.getAttachment());
            item.setLocalEx(message.getLocalEx());
            item.setEx(message.getEx());
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
