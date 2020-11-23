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

    void get_camera_tree();//获取摄像机目录树

    void get_camera_list();//获取摄像机列表

    void get_camera_url(); //获取实时视频 URI

    void test(); //测试数据
public slots:
    void get_reply();
private:
    data_info *m_data_info;
    QNetworkAccessManager networkManager;//网络管理
    QNetworkReply *reply;   //网络响应
    int action_hint;

    void hanlder_camera_tree(QByteArray bytes);
    void hanlder_camera_list(QByteArray bytes);


    QList<QString> get_all_list(QString val);


};

#endif // HTTP_WORKER_H
