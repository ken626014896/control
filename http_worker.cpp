#include "http_worker.h"
#include <QThread>
#include <QDebug>
http_worker::http_worker(data_info *data, QObject *parent):QObject(parent),
    m_data_info(data)
{

}

void http_worker::start()
{
    qDebug()<<QThread::currentThreadId();
}

void http_worker::stop()
{

}
