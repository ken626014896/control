#include "manager.h"
#include <QDebug>
#include "sy_utils.h"

manager::manager(data_model *test,QObject *parent) : QObject(parent),
    m_model_test(test)
{
     test_data();
}

void manager::test_data()
{
    for (int i=0;i<=0;i++) {

        QSharedPointer<data_info> http(new http_info);
        http->set_id(getUuid());
        http->set_name("test---"+QString::number(i));
        qDebug()<<"index"<<i;
        m_model_test->append(http);

        connect(http.data(), &data_info::camera_get_finish_signal, this, &manager::camera_get_finish_slot);

    }
   start_by_switch(m_model_test->get_data_list());

}

QVariantList manager::get_group_childs()
{
    QSharedPointer<data_info> dev=m_model_test->get_data_by_index(0);
//    qDebug()<<dev<<dev->getList_camera().length()<<dev->getList_catalogue().length();
    QVariantList list = dev->get_group_childs();//信号分组列表

    foreach (QVariant v, list) {
        if(v.isNull()) {
            continue;
        }
        QVariantMap map = v.toMap();
    }
    return list;
}

void manager::camera_get_finish_slot(QString id)
{
    QSharedPointer<data_info> http = m_model_test->get_data_by_id(id);
    qDebug()<<http->get_name();

    start_by_switch(http->getList_camera());
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
