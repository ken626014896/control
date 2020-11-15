#include "camera_thread.h"
#include "sy_logger.h"
#include "camera_worker.h"
camera_thread::camera_thread(data_info *data, QObject *parent):
    QThread(parent),
    m_data_info(data)
{

}

void camera_thread::run()
{
    camera_worker work(m_data_info);
    //主线程传递信号给线程    发送指令的信号



    //线程传递信号给主线程    发送完信号的回调操作信号


    work.start();
    this->exec();
    work.stop();
}
