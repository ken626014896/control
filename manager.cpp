#include "manager.h"
#include <QDebug>
manager::manager(data_model *test,QObject *parent) : QObject(parent),
    m_model_test(test)
{
     test_data();
}

void manager::test_data()
{
    for (int i=0;i<=10;i++) {

        QSharedPointer<data_info> dev(new data_info);
        dev->set_name("test---"+QString::number(i));
        qDebug()<<"index"<<i;
        m_model_test->append(dev);
    }
}
