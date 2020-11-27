#ifndef CAMERA_WORKER_H
#define CAMERA_WORKER_H
#include <QObject>
#include "data_info.h"
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
class camera_worker: public QObject
{
    Q_OBJECT
public:
    explicit camera_worker(data_info *data, QObject *parent = nullptr);
    void start();
    void stop();

    void get_camera_url();
    void test();

public slots:
    void get_reply();
    void ptz_control(QString cmd,QString status,int speed1,int speed2);

private:
    data_info *m_data_info;
    QNetworkAccessManager networkManager;//网络管理
    QNetworkReply *reply;   //网络响应
    int action_hint;
    void hanlder_camera_url(QByteArray bytes);

    void hanlder_camera_ptz(QByteArray bytes);
};

#endif // CAMERA_WORKER_H
