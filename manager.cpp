#include "manager.h"
#include <QDebug>
#include "camera_info.h"
#include "sy_utils.h"

manager::manager(data_model *test,data_model *video,data_model *camera,QObject *parent) : QObject(parent),
    m_model_test(test),
    m_model_video(video),
  m_model_camera(camera)
{
     test_data();//测试数据
     begain();//开始获取摄像机数据
}

void manager::test_data()
{
    for (int i=0;i<=0;i++) {

        QSharedPointer<data_info> http(new http_info);
        http->set_id(getUuid());
        http->set_name("test---"+QString::number(i));
        m_model_test->append(http);


    }

}

void manager::begain()
{

        QSharedPointer<data_info> http(new http_info);
        http->set_id(getUuid());
        http->set_name("admin");
        http->setIp_address("192.168.200.62");
        http->setPort(8000);
        http_list.append(http);
        connect(http.data(), &data_info::camera_get_finish_signal, this, &manager::camera_get_finish_slot);
        start_by_switch(http);

}

QVariantList manager::get_group_childs()
{

    if(http_list.length()<=0)
        return QVariantList();
    QSharedPointer<data_info> http=http_list.at(0);
//    qDebug()<<dev<<dev->getList_camera().length()<<dev->getList_catalogue().length();
    QVariantList list = http->get_group_childs();//信号分组列表

    foreach (QVariant v, list) {
        if(v.isNull()) {
            continue;
        }
        QVariantMap map = v.toMap();
    }
    return list;
}

void manager::start_play_video(QString id)
{
   if(id=="")
       return;
   QSharedPointer<data_info> camera=m_model_camera->get_data_by_id(id);

   if(camera.isNull())
       return;
   QSharedPointer<data_info> video(new camera_info);

   video->set_id(id);
   video->setUrl(camera->getUrl());
   video->setType("PLAY-VIDEO");
   video->set_name("videoddd");


   m_model_video->append(video);

   start_by_switch(video);

}

void manager::pause_play_video(QString id)
{
    if(id=="")
        return;
    QSharedPointer<data_info> video=m_model_video->get_data_by_id(id);
    if(video.isNull())
        return;
//    video->send_pause_video_signal();
    video->setIsPause(!video->getIsPause());
}

void manager::stop_play_video(QString id)
{
    if(id=="")
        return;
    QSharedPointer<data_info> video=m_model_video->get_data_by_id(id);
    if(video.isNull())
        return;
//    video->send_stop_video_signal();
    video->setIsStop(true);

    stop_by_switch(video);
    m_model_video->clear();

}

void manager::camera_get_finish_slot(QString id) //获取摄像机的播放地址
{
    QSharedPointer<data_info> http=http_list.at(0);
    m_model_camera->append(http->getList_camera());
    start_by_switch(m_model_camera->get_data_list());
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
