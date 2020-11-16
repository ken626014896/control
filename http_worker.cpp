#include "http_worker.h"
#include <QThread>
#include <QDebug>
#include "camera_info.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
http_worker::http_worker(data_info *data, QObject *parent):QObject(parent),
    m_data_info(data),
    action_hint(-1)  //0 获取摄像机目录树  1 获取摄像机
{

}

void http_worker::start()
{


//    QString temp="[{\"id\": \"10ff533ed2c74c1caf7bab39b20c1c90\", \"name\": \"dasha\", \"parent_id\": \"18a62514-96ba-11e7-bee6-00163e080cc6\", \"parent_ids\": \"0,18a62514-96ba-11e7-bee6-00163e080cc6,\", \"sort\": 30},{ \"id\": \"18a62514-96ba-11e7-bee6-00163e080cc6\", \"name\": \"guangzhoushi\", \"parent_id\": \"0\", \"parent_ids\": \"0,\", \"sort\": 30},{ \"id\": \"4400c2cda01b40e886c6356e5bc965c3\", \"name\": \"608\", \"parent_id\": \"10ff533ed2c74c1caf7bab39b20c1c90\", \"parent_ids\": \"0,18a62514-96ba-11e7-bee600163e080cc6,10ff533ed2c74c1caf7bab39b20c1c90, \", \"sort\": 30},{ \"id\": \"4400c2cda01b40e886c6356e5bc965c3\", \"name\": \"609\", \"parent_id\": \"10ff533ed2c74c1caf7bab39b20c1c90\", \"parent_ids\": \"0,18a62514-96ba-11e7-bee600163e080cc6,10ff533ed2c74c1caf7bab39b20c1c90, \", \"sort\": 30},{\"id\": \"10ff533ed2c74c1caf7bab39b20c1c902\", \"name\": \"dasha2\", \"parent_id\": \"18a62514-96ba-11e7-bee6-00163e080cc62\", \"parent_ids\": \"0,18a62514-96ba-11e7-bee6-00163e080cc6,\", \"sort\": 30},{ \"id\": \"18a62514-96ba-11e7-bee6-00163e080cc62\", \"name\": \"guangzhoushi2\", \"parent_id\": \"0\", \"parent_ids\": \"0,\", \"sort\": 30},{ \"id\": \"4400c2cda01b40e886c6356e5bc965c3\", \"name\": \"6082\", \"parent_id\": \"10ff533ed2c74c1caf7bab39b20c1c902\", \"parent_ids\": \"0,18a62514-96ba-11e7-bee600163e080cc6,10ff533ed2c74c1caf7bab39b20c1c90, \", \"sort\": 30}]";
//    hanlder_camera_tree(temp.toUtf8());

//    QString temp2="[{ \"auxstreamname\": \"Rstp\", \"cameraid\": \"000831c9029f2ac2deb0482f384b75f0\", \"cameraname\": \"40.203\", \"mainstreamname\": \"Rstp\",\"regionid\": \"4400c2cda01b40e886c6356e5bc965c3\"},{ \"auxstreamname\": \"stream1\", \"cameraid\": \"0f5a6d72fe3a29a51bd977911e474cea\", \"cameraname\": \"120.7\", \"mainstreamname\": \"stream1\",\"regionid\": \"4400c2cda01b40e886c6356e5bc965c3\"},{ \"auxstreamname\": \"Rstp\", \"cameraid\": \"8002e3f404343c98bf8f59870799e794\", \"cameraname\": \"40.191\", \"mainstreamname\": \"Rstp\",\"regionid\":\"4400c2cda01b40e886c6356e5bc965c3\"}]";
//    hanlder_camera_list(temp2.toUtf8());
    get_camera_tree();

}

void http_worker::stop()
{

}

void http_worker::get_camera_tree()
{
    QUrl newUrl = QUrl::fromUserInput("http://192.168.0.1:8000/aic/restful/getdata");//请求地址
    QNetworkRequest request;

    request.setUrl(newUrl);

    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");


    QByteArray dataArray = "{\"authorJson\":\"admin\",\"parmJson\":{\"code\":\"HuoQuTongDaoMuLuShuKeHuDuan\",\"params\":{}}}" ;


    action_hint=0;
    reply = networkManager.post(request,dataArray);
    connect(reply,SIGNAL(finished()),this,SLOT(get_reply()));
}

void http_worker::get_camera_list()
{
    QUrl newUrl = QUrl::fromUserInput("http://192.168.0.1:8000/aic/restful/getdata");//请求地址
    QNetworkRequest request;

    request.setUrl(newUrl);

    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");


    QByteArray dataArray = "{\"authorJson\":\"admin\",\"parmJson\":{\"code\":\"HuoQuSuoYouSheXiangJiLieBiaoKeHuDuan\",\"params\":{}}}" ;


    action_hint=1;
    reply = networkManager.post(request,dataArray);
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

            QVariantList catalogue_list=jsonDoucment.toVariant().toList();

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
    QJsonParseError jsonError;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(bytes, &jsonError);
    if(jsonError.error == QJsonParseError::NoError){

        if(!(jsonDoucment.isNull()||jsonDoucment.isEmpty())){

            QVariantList camera_list=jsonDoucment.toVariant().toList();

            for (int i=0;i<camera_list.length();i++) {

                QVariantMap map=camera_list.at(i).toMap();
                QSharedPointer<data_info> camera(new camera_info);
                camera->setAuxstreamname(map["auxstreamname"].toString());
                camera->setMainstreamname(map["mainstreamname"].toString());
                camera->setCameraid(map["cameraid"].toString());
                camera->setCameraname(map["cameraname"].toString());
//                 qDebug()<<camera->getCameraname();
                camera->setRegionid(map["regionid"].toString());
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




