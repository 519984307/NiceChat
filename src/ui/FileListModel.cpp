#include "FileListModel.h"


FileListModel::FileListModel(QObject *parent) : QAbstractListModel(parent) {


}

FileListModel::~FileListModel(){

}

int FileListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_files.count();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_files.count())
        return {};
    const QFileInfo &file = m_files[index.row()];
    if (role == Name)
        return file.fileName();
    else if (role == Path)
        return file.absoluteFilePath();
    else if (role == Icon){
        if(QUIHelper::instance()->isImage(file.suffix())){
            return "file:///"+file.absoluteFilePath();
        }
        return QUIHelper::instance()->getFileIcon(file.suffix());
    }
    else if (role == Size)
        return file.size();
    return {};
}

QHash<int, QByteArray> FileListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Path] = "path";
    roles[Icon] = "icon";
    roles[Size] = "size";
    return roles;
}

void FileListModel::addData(const QList<QFileInfo> &list) {
    if(list.count() > 0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_files.append(list);
        endInsertRows();
    }
}

void FileListModel::setNewData(const QList<QFileInfo> &list) {
    if(rowCount()>0){
        beginRemoveRows(QModelIndex(),0,rowCount()-1);
        m_files.clear();
        endRemoveRows();
    }
    if(list.count()>0){
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.count() - 1);
        m_files.append(list);
        endInsertRows();
    }
}

QVariantMap FileListModel::getItem(int index){
    auto file = m_files.at(index);
    QVariantMap map;
    map.insert("path",file.absoluteFilePath());
    return map;
}
