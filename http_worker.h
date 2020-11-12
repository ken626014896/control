#ifndef HTTP_WORKER_H
#define HTTP_WORKER_H
#include <QObject>
#include "data_info.h"
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
class http_worker: public QObject
{
    Q_OBJECT
public:
    explicit http_worker(data_info *data, QObject *parent = nullptr);
    void start();
    void stop();



private:
    data_info *m_data_info;
    QNetworkAccessManager networkManager;//网络管理
    QNetworkReply *reply;   //网络响应
};

#endif // HTTP_WORKER_H
