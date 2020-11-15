#include "data_model.h"
#include <QtDebug>
#include <QCoreApplication>
#include <QDir>
#include <QString>
data_model::data_model(QObject *parent) : QAbstractListModel(parent),
    m_current_index(-1)
{

}

int data_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list_data.count();
}

QVariant data_model::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_list_data.count()) {
        return QVariant();
    }
    QSharedPointer<data_info> data = m_list_data.value(row);
    if(data.isNull()){
        return QVariant();
    }
    QVariant rv = QVariant();
    switch (role) {
    case NameRole:
        rv =data->get_name();
        break;
    case UrlRole:
        rv =data->getUrl();
        break;
    case CamerNameRole:
        rv =data->getCameraname();
        break;

    default:
        rv = QVariant();
        break;
    }

    return rv;
}
void data_model::insert(int index, const QSharedPointer<data_info> &data)
{
    if(index < 0 || index > m_list_data.count()) {
        return;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    m_list_data.insert(index, data);
    emit endInsertRows();
}

void data_model::remove(int index)
{
    if(index < 0 || index >= m_list_data.count()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_list_data.removeAt(index);
    endRemoveRows();
}



void data_model::append(const QSharedPointer<data_info> &val)
{
    if(val.isNull()){
        return;
    }
    insert(m_list_data.count(), val);
}





void data_model::append(const QList<QSharedPointer<data_info> > &val)
{
    clear();
    for (int i=0; i<val.count(); i++) {
        insert(i, val.at(i));
    }
}

void data_model::clear()
{
    while(m_list_data.count() > 0){
        remove(0);
    }
    m_list_data.clear();
}

int data_model::count() const
{
    return rowCount(QModelIndex());
}
void data_model::data_changed_slot(int index)
{
    if(index < 0 || index >= m_list_data.count()){

        return;
    }
//    qDebug() << "data_changed_slot:" << index;
    emit dataChanged(this->index(index), this->index(index));  //内置信号  如果改变的是roleNames其中的值时一定要发出这个信号   为什么？？？
//    emit display_position_changed();
}
int data_model::get_current_index()
{
    return m_current_index;
}

void data_model::set_current_index(int val)
{
    if(m_current_index == val){
        return;
    }
    m_current_index = val;
    emit index_changed();
}
QHash<int, QByteArray> data_model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "dmName";
    roles[UrlRole] = "dmUrl";
    roles[CamerNameRole] = "dmCamerName";

    return roles;
}
QList<QSharedPointer<data_info> > data_model::get_data_list()
{
    return m_list_data;
}

QSharedPointer<data_info> data_model::get_data_by_index(int index)
{
    return  m_list_data.at(index);
}

QSharedPointer<data_info> data_model::get_data_by_id(QString id)
{
    for (int i=0; i < m_list_data.count(); i++) {
        QSharedPointer<data_info> info = m_list_data.at(i);
        if(info.isNull() || info->get_id() != id){
            continue;
        }
        return info;
    }
    return QSharedPointer<data_info>();
}
