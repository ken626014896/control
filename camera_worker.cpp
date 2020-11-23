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
#if 0
    test();
    qDebug()<<"coming"<<m_data_info->getCameraname();

#endif
    get_camera_url();

}
void camera_worker::test()
{
     m_data_info->setUrl("123.com");
}

void camera_worker::stop()
{

}

void camera_worker::get_camera_url()
{
    QUrl newUrl = QUrl::fromUserInput("http://192.168.200.62:8000/aic/restful/getdata");//请求地址
    QNetworkRequest request;
    QByteArray text("admin:admin");

    request.setUrl(newUrl);
    request.setRawHeader("Authorization","Basic YWRtaW46YWRtaW4=");//Authorization身份验证
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");


    QByteArray dataArray = "{\"authorJson\":{\"loginAccount\":\"admin\"},\"parmJson\":{\"code\":\"getRealUri\",\"params\":{\"cameraid\":\"f9d5e03e4a0a4597b106e9e4995ed7bf\"}}}" ;
    //发送json
    QByteArray post_data;
    QByteArray post_data1("{\"loginAccount\":\"admin\"}");
    QString temp="{\"code\":\"getRealUri\",\"params\":{\"cameraid\":"+m_data_info->getCameraid()+"}}";
    QByteArray post_data2;


    QString  str=m_data_info->getCameraid();
    char*  ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();
    QByteArray post_data3="{\"code\":\"getRealUri\",\"params\":{\"cameraid\":\"";
    post_data3.append(ch);
    post_data3.append("\"}}");
    QJsonObject json;

    json.insert("code", "getRealUri");

    QJsonObject parmjson;

    QJsonObject parmsjson;
    parmsjson.insert("cameraid",m_data_info->getCameraid());


    json.insert("params", parmjson);
    QJsonDocument document;
    document.setObject(json);
    post_data2 = document.toJson(QJsonDocument::Compact);

    post_data.append("authorJson=");
    post_data.append(post_data1);
    post_data.append("&");
    post_data.append("parmJson=");
    post_data.append(post_data3);



    reply = networkManager.post(request,post_data);
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
