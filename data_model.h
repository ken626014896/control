#ifndef DATA_MODEL_H
#define DATA_MODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QSharedPointer>
#include "data_info.h"
class data_model : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit data_model(QObject *parent = nullptr);
    enum DataRoles{
        NameRole = Qt::UserRole + 1,

    };
    Q_PROPERTY(int current_index READ get_current_index WRITE set_current_index NOTIFY index_changed)


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void insert(int index,const QSharedPointer<data_info> &data) ;

    Q_INVOKABLE void remove(int index);
    void append(const QSharedPointer<data_info> &val);
    void append(const QList<QSharedPointer<data_info>> &val);
    void clear();
    Q_INVOKABLE int count() const;


    Q_INVOKABLE int get_current_index();
    Q_INVOKABLE void set_current_index(int val);
    QList<QSharedPointer<data_info>> get_data_list();
signals:
    void index_changed();

public slots:
    Q_INVOKABLE void data_changed_slot(int index);

protected:
    virtual QHash<int, QByteArray> roleNames() const;
private:
    QList<QSharedPointer<data_info>> m_list_data;
    int m_current_index;
    QString m_current_id;

};

#endif // DATA_MODEL_H
