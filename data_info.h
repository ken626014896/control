﻿#ifndef DATA_INFO_H
#define DATA_INFO_H

#include <QObject>
#include <QList>
class data_info : public QObject
{
    Q_OBJECT
public:
    explicit data_info(QObject *parent = nullptr);
    QString get_name();
    void set_name(QString val);

    int get_index();
    void set_index(int val);

    QString get_id();
    void set_id(QString val);


    virtual void start();
    virtual void stop();
signals:

public slots:


protected:
    QString m_name;
    QString m_id;
    int m_index;//设备索引
};

#endif // DATA_INFO_H
