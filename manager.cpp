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

        QSharedPointer<data_info> dev(new http_info);
        dev->set_name("test---"+QString::number(i));
        qDebug()<<"index"<<i;
        m_model_test->append(dev);
    }
   start_by_switch(m_model_test->get_data_list());

}

void manager::stop_by_switch(QList<QSharedPointer<data_info> > list)
{
    foreach(QSharedPointer<data_info> info, list) {
        if(info.isNull()) {
            continue;
        }
        info->stop();
    }
}

void manager::stop_by_switch(QSharedPointer<data_info> val)
{
       val->stop();
}

void manager::start_by_switch(QList<QSharedPointer<data_info> > list)
{
    foreach(QSharedPointer<data_info> info, list) {
        if(info.isNull()) {
            continue;
        }
        info->start();
    }
}

void manager::start_by_switch(QSharedPointer<data_info> val)
{
    val->start();
}
