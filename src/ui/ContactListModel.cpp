#include "ContactListModel.h"

ContactListModel::ContactListModel(QObject *parent) : QAbstractListModel(parent) {


}

ContactListModel::~ContactListModel(){

}

int ContactListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_users.count();
}

QVariant ContactListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_users.count())
        return {};
    const User &user = m_users[index.row()];
    if (role == Id)
        return user.getAccid();
    else if (role == Name)
        return user.getName();
    else if (role == Icon)
        return user.getIcon();
    else if (role == Sign)
        return user.getSign();
    else if (role == Birth)
        return user.getBirth();
    else if (role == Mobile)
        return user.getMobile();
    else if (role == Gender)
        return user.getGender();
    else if (role == Ex)
        return user.getEx();
    return {};
}

QHash<int, QByteArray> ContactListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Id] = "id";
    roles[Name] = "name";
    roles[Icon] = "icon";
    roles[Sign] = "sign";
    roles[Birth] = "birth";
    roles[Mobile] = "mobile";
    roles[Gender] = "gender";
    roles[Ex] = "ex";
    return roles;
}

void ContactListModel::addData(const QList<User> &list) {
    if(list.count() > 0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_users.append(list);
        endInsertRows();
    }
}

void ContactListModel::setNewData(const QList<User> &list) {
    if(rowCount()>0){
        beginRemoveRows(QModelIndex(),0,rowCount()-1);
        m_users.clear();
        endRemoveRows();
    }
    if(list.count()>0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_users.append(list);
        endInsertRows();
    }
}

void ContactListModel::addOrUpdateData(const User &user){
    for (int i = 0; i < m_users.size(); ++i)
    {
        auto &item = const_cast<class User &>(m_users.at(i));
        if (item.getAccid() == user.getAccid()){
            item.setName(user.getName());
            item.setIcon(user.getIcon());
            item.setSign(user.getSign());
            item.setBirth(user.getBirth());
            item.setMobile(user.getMobile());
            item.setGender(user.getGender());
            item.setEx(user.getEx());
            Q_EMIT dataChanged(this->index(i),this->index(i));
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_users.append(user);
    endInsertRows();
}

int ContactListModel::count(){
    return m_users.count();
}

QJsonObject ContactListModel::getItem(int index){
    const QString &json = qx::serialization::json::to_string(m_users.at(index));
    return QJsonDocument::fromJson(json.toUtf8()).object();
}


int ContactListModel::getIndexByAccid(const QString& accid){
    for (int i = 0; i < m_users.size(); ++i)
    {
        auto &item = const_cast<class User &>(m_users.at(i));
        if (item.getAccid() == accid){
            return i;
        }
    }
    return -1;
}
