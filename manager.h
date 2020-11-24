#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "data_model.h"
#include <QSharedPointer>
#include "data_info.h"
#include "http_info.h"
class manager : public QObject
{
    Q_OBJECT
public:
    explicit manager(data_model *test,
                     data_model *video,
                     data_model *camera,
                     QObject*parent = nullptr);
    void test_data();//测试添加数据
    void begain();//测试添加数据
    Q_INVOKABLE QVariantList get_group_childs();


    Q_INVOKABLE  void start_play_video(QString id);
    Q_INVOKABLE  void pause_play_video(QString id);
    Q_INVOKABLE  void stop_play_video(QString id);
signals:

public slots:
    void camera_get_finish_slot(QString id);

private:
    data_model *m_model_test;
    data_model *m_model_video;
    data_model *m_model_camera;
    void stop_by_switch(QList<QSharedPointer<data_info> > list);
    void stop_by_switch(QSharedPointer<data_info> val);
    void start_by_switch(QList<QSharedPointer<data_info> > list);
    void start_by_switch(QSharedPointer<data_info>  val);
    QList<QSharedPointer<data_info>>  http_list;




};

#endif // MANAGER_H
