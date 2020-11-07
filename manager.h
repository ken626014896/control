#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "data_model.h"
#include <QSharedPointer>
#include "data_info.h"

class manager : public QObject
{
    Q_OBJECT
public:
    explicit manager(data_model *test,QObject *parent = nullptr);
    void test_data();//测试添加数据
signals:

public slots:


private:
    data_model *m_model_test;
};

#endif // MANAGER_H
