#include "http_worker.h"
#include <QThread>
#include <QDebug>
#include "camera_info.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>

#include "sy_utils.h"
http_worker::http_worker(data_info *data, QObject *parent):QObject(parent),
    m_data_info(data),
    action_hint(-1)  //0 获取摄像机目录树  1 获取摄像机
{

}

void http_worker::start()
{

#if 1
    test();

#endif

#if 0
    get_camera_tree();

#endif


}

void http_worker::stop()
{

}
void http_worker::test()
{
    QList<QString>  temp;
    temp.append("0");
    QSharedPointer<data_info> catalogue(new data_info);
    catalogue->set_id("123");
    catalogue->set_name("abc");
//                qDebug()<<catalogue->get_name();
    catalogue->setSort(0);
    catalogue->setParent_id("0");
    catalogue->setParent_id_lsit(temp);
    m_data_info->append_catalogue_by_sort(catalogue);


    QSharedPointer<data_info> catalogue2(new data_info);
    catalogue2->set_id("456");
    catalogue2->set_name("dfg");
//                qDebug()<<catalogue->get_name();
    catalogue2->setSort(0);
    catalogue2->setParent_id("123");
    catalogue2->setParent_id_lsit(temp);
    m_data_info->append_catalogue_by_sort(catalogue2);


    QSharedPointer<data_info> camera(new camera_info);
    camera->set_id(getUuid());
    camera->setCameraid(getUuid());
    camera->setCameraname("camera1");
    camera->setRegionid("456");
    camera->setType("GET-URL");//该对象用于获取摄像机播放url
    m_data_info->append_camera_by_sort(camera);

    QSharedPointer<data_info> camera2(new camera_info);
    camera2->set_id(getUuid());
    camera2->setCameraid(getUuid());
    camera2->setCameraname("camera2");
    camera2->setRegionid("456");
    camera2->setType("GET-URL");//该对象用于获取摄像机播放url
    m_data_info->append_camera_by_sort(camera2);


     m_data_info->send_camera_get_finish_signal(m_data_info->get_id());
}
void http_worker::get_camera_tree()
{
    QUrl newUrl = QUrl::fromUserInput("http://192.168.200.62:8000/aic/restful/getdata");//请求地址
    QNetworkRequest request;
    QByteArray text("admin:admin");
    request.setUrl(newUrl);
    request.setRawHeader("Authorization","Basic YWRtaW46YWRtaW4=");//Authorization身份验证
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");


    QByteArray dataArray = "{\"authorJson\":{\"loginAccount\":\"admin\"},\"parmJson\":{\"code\":\"HuoQuTongDaoMuLuShuKeHuDuan\",\"params\":{}}}" ;

    QByteArray post_data;
    QByteArray post_data1("{\"loginAccount\":\"admin\"}");
    QByteArray post_data2("{\"code\":\"HuoQuTongDaoMuLuShuKeHuDuan\",\"params\":{}}");
    post_data.append("authorJson=");
    post_data.append(post_data1);
    post_data.append("&");
    post_data.append("parmJson=");
    post_data.append(post_data2);

    action_hint=0;
    reply = networkManager.post(request,post_data);
    connect(reply,SIGNAL(finished()),this,SLOT(get_reply()));
}

void http_worker::get_camera_list()
{
    QUrl newUrl = QUrl::fromUserInput("http://192.168.200.62:8000/aic/restful/getdata");//请求地址
    QNetworkRequest request;

    QByteArray text("admin:admin");
    request.setUrl(newUrl);
    request.setRawHeader("Authorization","Basic YWRtaW46YWRtaW4=");//Authorization身份验证

    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");


    QByteArray dataArray = "{\"authorJson\":{\"loginAccount\":\"admin\"},\"parmJson\":{\"code\":\"HuoQuSuoYouSheXiangJiLieBiaoKeHuDuan\",\"params\":{}}}" ;



    QByteArray post_data;
    QByteArray post_data1("{\"loginAccount\":\"admin\"}");
    QByteArray post_data2("{\"code\":\"HuoQuSuoYouSheXiangJiLieBiaoKeHuDuan\",\"params\":{}}");
    post_data.append("authorJson=");
    post_data.append(post_data1);
    post_data.append("&");
    post_data.append("parmJson=");
    post_data.append(post_data2);

    action_hint=1;
    reply = networkManager.post(request,post_data);
    connect(reply,SIGNAL(finished()),this,SLOT(get_reply()));
}



void http_worker::get_reply()
{
    QByteArray bytes = reply->readAll();

    if(action_hint==0)
        hanlder_camera_tree(bytes);
    else if (action_hint==1){
        hanlder_camera_list(bytes);
    }


    QString string = QString::fromUtf8(bytes);
}

void http_worker::hanlder_camera_tree(QByteArray bytes)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(bytes, &jsonError);
    if(jsonError.error == QJsonParseError::NoError){

        if(!(jsonDoucment.isNull()||jsonDoucment.isEmpty())){

            QVariantList all_catalogue_list=jsonDoucment.toVariant().toList();
            QVariantMap  catalogue_list_map=all_catalogue_list.at(0).toMap();

            QVariantList  catalogue_list=catalogue_list_map["datas"].toList();
            qDebugxx("get catalogue num: ",catalogue_list.length());
            for (int i=0;i<catalogue_list.length();i++) {

                QVariantMap map=catalogue_list.at(i).toMap();
                QSharedPointer<data_info> catalogue(new data_info);
                catalogue->set_id(map["id"].toString());
                catalogue->set_name(map["name"].toString());
//                qDebug()<<catalogue->get_name();
                catalogue->setSort(map["sort"].toInt());
                catalogue->setParent_id(map["parent_id"].toString());
                catalogue->setParent_id_lsit(get_all_list(map["parent_ids"].toString()));
                m_data_info->append_catalogue_by_sort(catalogue);

            }
            get_camera_list();
        }

    }else{

        //检查错误类型
        qDebugxx("hanlder_camera_tree jsonError:",jsonError.errorString());
        qDebug()<<"hanlder_camera_tree jsonError:"<<jsonError.errorString();
    }
}

void http_worker::hanlder_camera_list(QByteArray bytes)
{

    qDebugx("get camera");
    QJsonParseError jsonError;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(bytes, &jsonError);
    if(jsonError.error == QJsonParseError::NoError){

        if(!(jsonDoucment.isNull()||jsonDoucment.isEmpty())){

            QVariantList all_camera_list=jsonDoucment.toVariant().toList();
            QVariantMap  camera_list_map=all_camera_list.at(0).toMap();

            QVariantList  camera_list=camera_list_map["datas"].toList();
            qDebugxx("get camera num: ",camera_list.length());
            for (int i=0;i<camera_list.length();i++) {

                QVariantMap map=camera_list.at(i).toMap();
                QSharedPointer<data_info> camera(new camera_info);
                camera->set_id(getUuid());
                camera->set_index(i);
                camera->setAuxstreamname(map["auxstreamname"].toString());
                camera->setMainstreamname(map["mainstreamname"].toString());
                camera->setCameraid(map["cameraid"].toString());
                camera->setCameraname(map["cameraname"].toString());
//                 qDebug()<<camera->getCameraname();
                camera->setRegionid(map["regionid"].toString());
                camera->setType("GET-URL");//该对象用于获取摄像机播放url
                m_data_info->append_camera_by_sort(camera);

            }

        }

    }else{

        //检查错误类型
        qDebugxx("hanlder_camera_list jsonError:",jsonError.errorString());
        qDebug()<<"hanlder_camera_list jsonError:"<<jsonError.errorString();
    }

    m_data_info->send_camera_get_finish_signal(m_data_info->get_id());
}

QList<QString> http_worker::get_all_list(QString val)
{
   QList<QString> temp=val.split(",");

   return  temp;
}




