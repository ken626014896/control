#include "camera_info.h"

camera_info::camera_info(QObject *parent) : data_info(parent),
    m_camera_thread(nullptr)
{

}

camera_info::~camera_info()
{

}

void camera_info::start()
{
    if(m_camera_thread != nullptr) {
            return;
        }

        m_camera_thread = new camera_thread((data_info *)this);


        m_camera_thread->start();
}

void camera_info::stop()
{
    if(m_camera_thread != nullptr) {
        m_camera_thread->quit();
        m_camera_thread->wait();
        delete m_camera_thread;
        m_camera_thread = nullptr;
    }
    data_info::stop();
}
