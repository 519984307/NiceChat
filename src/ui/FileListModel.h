#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QJsonDocument>
#include "QUIHelper.h"
#include "database/Session.h"

class FileListModel: public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        Name,
        Path,
        Icon,
        Size,
    };

    explicit FileListModel(QObject *parent = nullptr);
    ~FileListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role =Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addData(const QList<QFileInfo> &list);

    void setNewData(const QList<QFileInfo> &list);

    const QList<QFileInfo>& getData();

private:
    QList<QFileInfo> m_files;
};

#endif // FILELISTMODEL_H
