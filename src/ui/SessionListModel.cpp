﻿#include "SessionListModel.h"

SessionListModel::SessionListModel(QObject *parent) : QAbstractListModel(parent) {


}

SessionListModel::~SessionListModel(){

}

int SessionListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_Sessions.count();
}

QVariant SessionListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_Sessions.count())
        return {};
    const Session &Session = m_Sessions[index.row()];
    if (role == Id)
        return Session.getId();
    else if (role == Body)
        return Session.getBody();
    else if (role == Scene)
        return Session.getScene();
    else if (role == Type)
        return Session.getType();
    else if (role == Ex)
        return Session.getEx();
    else if (role == Time)
        return Session.getTime();
    else if (role == Status)
        return Session.getStatus();
    else if (role == UnRead)
        return Session.getUnread();
    return {};
}

QHash<int, QByteArray> SessionListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Id] = "id";
    roles[Body] = "body";
    roles[Scene] = "scene";
    roles[Type] = "type";
    roles[Ex] = "ex";
    roles[Time] = "time";
    roles[UnRead] = "unread";
    return roles;
}

void SessionListModel::addData(const QList<Session> &list) {
    if(list.count() > 0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_Sessions.append(list);
        endInsertRows();
    }
}

void SessionListModel::setNewData(const QList<Session> &list) {
    if(rowCount()>0){
        beginRemoveRows(QModelIndex(),0,rowCount()-1);
        m_Sessions.clear();
        endRemoveRows();
    }
    if(list.count()>0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_Sessions.append(list);
        endInsertRows();
    }
}

void SessionListModel::addOrUpdateData(const Session &session){
    for (int i = 0; i < m_Sessions.size(); ++i)
    {
        auto &item = const_cast<class Session &>(m_Sessions.at(i));
        if (item.getId() == session.getId()){
            item.setTime(session.getTime());
            item.setStatus(session.getStatus());
            item.setBody(session.getBody());
            item.setEx(session.getEx());
            item.setScene(session.getScene());
            item.setType(session.getType());
            item.setUnread(session.getUnread());
            Q_EMIT dataChanged(this->index(i),this->index(i));
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Sessions.append(session);
    endInsertRows();
}

int SessionListModel::count(){
    return m_Sessions.count();
}

QJsonObject SessionListModel::getItem(int index){
    const QString &json = qx::serialization::json::to_string(m_Sessions.at(index));
    return QJsonDocument::fromJson(json.toUtf8()).object();
}

int SessionListModel::getIndexByAccid(const QString& accid){
    for (int i = 0; i < m_Sessions.size(); ++i)
    {
        auto &item = const_cast<class Session &>(m_Sessions.at(i));
        if (item.getId() == accid){
            return i;
        }
    }
    return -1;
}
