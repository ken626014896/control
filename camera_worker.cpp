#include "camera_worker.h"
#include <QThread>
#include <QDebug>

#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include "sy_logger.h"
camera_worker::camera_worker(data_info *data, QObject *parent):QObject(parent),
    m_data_info(data)
{

}

void camera_worker::start()
{
    QString temp="[{ \"result\":0, \"resultdesc\":\"成功\", \"uri\":\"rtsp://192.168.31.170:8554/vlc\"}]";
    hanlder_camera_url(temp.toUtf8());
}

void camera_worker::stop()
{

}

void camera_worker::get_camera_url()
{
    QUrl newUrl = QUrl::fromUserInput("http://192.168.0.1:8000/aic/restful/getdata");//请求地址
    QNetworkRequest request;

    request.setUrl(newUrl);

    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");


    QByteArray dataArray = "{\"authorJson\":\"admin\",\"parmJson\":{\"code\":\"getRealUri\",\"params\":{\"cameraid\":\"f9d5e03e4a0a4597b106e9e4995ed7bf\"}}}" ;
    //发送json
    QJsonObject json;
    QByteArray dataArray2 ;
    json.insert("authorJson", "admin");

    QJsonObject parmjson;

    QJsonObject parmsjson;
    parmsjson.insert("cameraid",m_data_info->getCameraid());

    parmjson.insert("params",parmsjson);
    parmjson.insert("code","getRealUri");
    json.insert("parmJson", parmjson);
    QJsonDocument document;
    document.setObject(json);
    dataArray2 = document.toJson(QJsonDocument::Compact);



    reply = networkManager.post(request,dataArray2);
    connect(reply,SIGNAL(finished()),this,SLOT(get_reply()));
}



void camera_worker::get_reply()
{
    QByteArray bytes = reply->readAll();

    hanlder_camera_url(bytes);
    QString string = QString::fromUtf8(bytes);
}

void camera_worker::hanlder_camera_url(QByteArray bytes)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(bytes, &jsonError);
    if(jsonError.error == QJsonParseError::NoError){

        if(!(jsonDoucment.isNull()||jsonDoucment.isEmpty())){

            QVariantList catalogue_list=jsonDoucment.toVariant().toList();

            for (int i=0;i<catalogue_list.length();i++) {

                QVariantMap map=catalogue_list.at(i).toMap();
                QSharedPointer<data_info> catalogue(new data_info);
                m_data_info->setUrl(map["uri"].toString());

            }

        }

    }else{

        //检查错误类型
        qDebug()<<"hanlder_camera_url jsonError:"<<jsonError.errorString();
        qDebugxx("hanlder_camera_url jsonError:",jsonError.errorString());
    }
}
