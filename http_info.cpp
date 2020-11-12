#include "http_info.h"

http_info::http_info(QObject *parent) : data_info(parent),
    m_http_thread(nullptr)
{

}

http_info::~http_info()
{

}

void http_info::start()
{
    if(m_http_thread != nullptr) {
            return;
        }

        m_http_thread = new http_thread((data_info *)this);


        m_http_thread->start();
}

void http_info::stop()
{
    if(m_http_thread != nullptr) {
        m_http_thread->quit();
        m_http_thread->wait();
        delete m_http_thread;
        m_http_thread = nullptr;
    }
    data_info::stop();
}
