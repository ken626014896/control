#ifndef HTTP_INFO_H
#define HTTP_INFO_H
#include "sy_logger.h"
#include <QObject>
#include  "data_info.h"
#include  "http_thread.h"
#include <QThread>
class http_info : public data_info
{
    Q_OBJECT
public:
    explicit http_info(QObject *parent = nullptr);
    ~http_info();
    void start();
    void stop();
signals:

private:
    http_thread *m_http_thread;
public slots:
};

#endif // HTTP_INFO_H
