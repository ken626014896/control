#include "camera_worker.h"
#include <QThread>
#include <QDebug>

#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>

camera_worker::camera_worker(data_info *data, QObject *parent):QObject(parent),
    m_data_info(data),
    action_hint(-1)  //0 获取摄像机播放url  1 ptz控制
{
    connect(m_data_info, &data_info::ptz_control_signal, this, &camera_worker::ptz_control);
}

void camera_worker::start()
{
#if 0
    test();

#endif

#if 1
    get_camera_url();

#endif


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


    //发送json
    QByteArray post_data;
    QByteArray post_data1("{\"loginAccount\":\"admin\"}");


    QString  str=m_data_info->getCameraid();
    char*  ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();
    QByteArray post_data3="{\"code\":\"getRealUri\",\"params\":{\"cameraid\":\"";
    post_data3.append(ch);
    post_data3.append("\"}}");


    post_data.append("authorJson=");
    post_data.append(post_data1);
    post_data.append("&");
    post_data.append("parmJson=");
    post_data.append(post_data3);


    action_hint=0;
    reply = networkManager.post(request,post_data);
    connect(reply,SIGNAL(finished()),this,SLOT(get_reply()));
}

void camera_worker::ptz_control(QString cmd, QString status, int speed1, int speed2)
{

    QUrl newUrl = QUrl::fromUserInput("http://192.168.200.62:8000/aic/restful/getdata");//请求地址
    QNetworkRequest request;
    QByteArray text("admin:admin");

    request.setUrl(newUrl);
    request.setRawHeader("Authorization","Basic YWRtaW46YWRtaW4=");//Authorization身份验证
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");


    //发送json
    QByteArray post_data;
    QByteArray authorJson_data("{\"loginAccount\":\"admin\"}");


    QString  str=m_data_info->getCameraid();
    char*  ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();
    QByteArray parmJson_data="{\"code\":\"getRealUri\",\"params\":{\"cameraid\":\"";
    parmJson_data.append(ch);
    parmJson_data.append("\",\"cmd\":\"");
    char*  ch_cmd=cmd.toLatin1().data();
    parmJson_data.append(ch_cmd);

    parmJson_data.append("\",\"status\":\"");
    char*  ch_status=status.toLatin1().data();
    parmJson_data.append(ch_status);

    parmJson_data.append("\",\"speed1\":");
    parmJson_data.append(speed1);

    parmJson_data.append(",\"speed2\":");
    parmJson_data.append(speed2);
    parmJson_data.append("}}");



    post_data.append("authorJson=");
    post_data.append(authorJson_data);
    post_data.append("&");
    post_data.append("parmJson=");
    post_data.append(parmJson_data);

    qDebug()<<post_data;

    action_hint=1;
//    reply = networkManager.post(request,post_data);
//    connect(reply,SIGNAL(finished()),this,SLOT(get_reply()));
}


void camera_worker::get_reply()
{
    QByteArray bytes = reply->readAll();

    if(action_hint==0){
        hanlder_camera_url(bytes);
    }
    else if (action_hint==1) {
        hanlder_camera_ptz(bytes);
    }

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
                m_data_info->send_get_video_url_signal();

            }

        }

    }else{

        //检查错误类型
        qDebug()<<"hanlder_camera_url jsonError:"<<jsonError.errorString();
//        qDebugxx("hanlder_camera_url jsonError:",jsonError.errorString());
    }
}

void camera_worker::hanlder_camera_ptz(QByteArray bytes)
{

}
