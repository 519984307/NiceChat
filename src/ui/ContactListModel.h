#ifndef CONTACTLISTMODEL_H
#define CONTACTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QJsonDocument>
#include "database/User.h"

class ContactListModel: public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        Id,
        Name,
        Icon,
        Sign,
        Birth,
        Mobile,
        Gender,
        Ex,
    };

    explicit ContactListModel(QObject *parent = nullptr);
    ~ContactListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role =Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addData(const QList<User> &list);

    void setNewData(const QList<User> &list);

    void addOrUpdateData(const User &session);

    Q_INVOKABLE int count();

    Q_INVOKABLE QJsonObject getItem(int index);

    Q_INVOKABLE int getIndexByAccid(const QString& accid);


private:
    QList<User> m_users;
};


#endif // CONTACTLISTMODEL_H
