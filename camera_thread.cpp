#include "camera_thread.h"
#include "sy_logger.h"
#include "camera_worker.h"
#include "camera_worker_play.h"
camera_thread::camera_thread(data_info *data, QObject *parent):
    QThread(parent),
    m_data_info(data)
{

}

void camera_thread::run()
{
    if(m_data_info->getType()=="GET-URL"){
        camera_worker work(m_data_info);
        work.start();
        this->exec();
        work.stop();
    }

    else if (m_data_info->getType()=="PLAY-VIDEO") {
        camera_worker_play work(m_data_info);
        work.start();
        this->exec();
        work.stop();
    }


    //主线程传递信号给线程    发送指令的信号


    //线程传递信号给主线程    发送完信号的回调操作信号



}
