#include "SessionListModel.h"

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
    const Session &session = m_Sessions[index.row()];
    if (role == Id)
        return session.getId();
    else if (role == Body)
        return session.getBody();
    else if (role == Scene)
        return session.getScene();
    else if (role == Type)
        return session.getType();
    else if (role == Ex)
        return session.getEx();
    else if (role == Time)
        return session.getTime();
    else if (role == Status)
        return session.getStatus();
    else if (role == UnRead)
        return session.getUnread();
    else if (role == Top)
        return session.getTop();
    else if (role == Content)
        return session.getContent();
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
    roles[Top] = "top";
    roles[Content] = "content";
    return roles;
}

void SessionListModel::addData(const QList<Session> &list) {
    if(list.count() > 0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_Sessions.append(list);
        endInsertRows();
        sortByTime();
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
        sortByTime();
    }
}

void SessionListModel::removeDataById(const QString& id){
    int index = getIndexById(id);
    if(index != -1){
        beginRemoveRows(QModelIndex(),index,index);
        m_Sessions.removeAt(index);
        endRemoveRows();
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
            item.setTop(session.getTop());
            item.setContent(session.getContent());
            Q_EMIT dataChanged(this->index(i),this->index(i));
            sortByTime();
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Sessions.append(session);
    endInsertRows();
    sortByTime();
}

int SessionListModel::count(){
    return m_Sessions.count();
}

QJsonObject SessionListModel::getItem(int index){
    const QString &json = qx::serialization::json::to_string(m_Sessions.at(index));
    return QJsonDocument::fromJson(json.toUtf8()).object();
}

void SessionListModel::sortByTime(){
    qSort(m_Sessions.begin(),m_Sessions.end(),[](const Session &left,const Session &right){
        if(left.getTop() && !right.getTop()){
            return true;
        }else if(!left.getTop() && right.getTop()){
            return false;
        }else{
            return left.getTime().toULongLong()>right.getTime().toULongLong();
        }
    });
    Q_EMIT dataChanged(this->index(0),this->index(rowCount()-1));
}

int SessionListModel::getIndexById(const QString& id){
    for (int i = 0; i < m_Sessions.size(); ++i)
    {
        auto &item = const_cast<class Session &>(m_Sessions.at(i));
        if (item.getId() == id){
            return i;
        }
    }
    return -1;
}
