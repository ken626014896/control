#include "data_info.h"
#include <QDebug>
data_info::data_info(QObject *parent) : QObject(parent),
    m_name(QString()),

    m_id(QString()) ,
   m_index(-1),
   m_ip_address(QString()),
   m_parent_id(QString()),
   m_auxstreamname(QString()),
   m_cameraid(QString()),
   m_cameraname(QString()),
   m_mainstreamname(QString()),
   m_regionid(QString()),
   m_resultdesc(QString()),
   m_url(QString()),
   m_sort(-1),
   m_result(-1)
{

}

QString data_info::get_name()
{
    return m_name;
}

void data_info::set_name(QString val)
{
    m_name = val;
}
QString data_info::get_id()
{
    return m_id;
}

void data_info::set_id(QString val)
{
    m_id = val;
}

int data_info::get_index()
{
    return m_index;
}

void data_info::set_index(int val)
{
    m_index = val;
}
void data_info::start()
{

}

void data_info::stop()
{

}

QString data_info::getIp_address() const
{
    return m_ip_address;
}

void data_info::setIp_address(const QString &ip_address)
{
    m_ip_address = ip_address;
}

QString data_info::getParent_id() const
{
    return m_parent_id;
}

void data_info::setParent_id(const QString &parent_id)
{
    m_parent_id = parent_id;
}

QList<QString> data_info::getParent_id_lsit() const
{
    return m_parent_id_lsit;
}

void data_info::setParent_id_lsit(const QList<QString> &parent_id_lsit)
{
    m_parent_id_lsit = parent_id_lsit;
}

QString data_info::getAuxstreamname() const
{
    return m_auxstreamname;
}

void data_info::setAuxstreamname(const QString &auxstreamname)
{
    m_auxstreamname = auxstreamname;
}

QString data_info::getCameraid() const
{
    return m_cameraid;
}
void data_info::send_image_incoming_event(QImage img)
{
    if(img.isNull()){
        return;
    }
    emit image_incoming_signal(get_id(), img);
}

int data_info::getPort() const
{
    return m_port;
}

void data_info::setPort(int port)
{
    m_port = port;
}

QString data_info::getType() const
{
    return m_type;
}

void data_info::setType(const QString &type)
{
    m_type = type;
}

int data_info::getChannel() const
{
    return m_channel;
}

void data_info::setChannel(int channel)
{
    m_channel = channel;
}
void data_info::setCameraid(const QString &cameraid)
{
    m_cameraid = cameraid;
}

QString data_info::getCameraname() const
{
    return m_cameraname;
}

void data_info::setCameraname(const QString &cameraname)
{
    m_cameraname = cameraname;
}

QString data_info::getMainstreamname() const
{
    return m_mainstreamname;
}

void data_info::setMainstreamname(const QString &mainstreamname)
{
    m_mainstreamname = mainstreamname;
}

QString data_info::getRegionid() const
{
    return m_regionid;
}

void data_info::setRegionid(const QString &regionid)
{
    m_regionid = regionid;
}

int data_info::getResult() const
{
    return m_result;
}

void data_info::setResult(int result)
{
    m_result = result;
}

QString data_info::getResultdesc() const
{
    return m_resultdesc;
}

void data_info::setResultdesc(const QString &resultdesc)
{
    m_resultdesc = resultdesc;
}

QString data_info::getUrl() const
{
    return m_url;
}

void data_info::setUrl(const QString &url)
{
    m_url = url;
}

QList<QSharedPointer<data_info> > data_info::getList_camera() const
{
    return m_list_camera;
}

void data_info::setList_camera(const QList<QSharedPointer<data_info> > &list_camera)
{
    m_list_camera = list_camera;
}

void data_info::append_camera(QSharedPointer<data_info> &val)
{
    if(val.isNull())
        return;

    m_list_camera.append(val);
    //    qDebug()<<m_list_camera;
}

void data_info::append_camera_by_sort(QSharedPointer<data_info> &val)
{
    m_list_camera.append(val);
    //    qDebug()<<m_list_camera;

    for (int i=0;i<m_list_catalogue.length()-1;i++) {

       QSharedPointer<data_info> catalogue= m_list_catalogue.at(i);

       if(val->getRegionid()==catalogue->get_id())  //说明val摄像机底下属于该目录
           catalogue->append_camera(val);



    }
}

int data_info::getSort() const
{
    return m_sort;
}

void data_info::setSort(int sort)
{
    m_sort = sort;
}

QList<QSharedPointer<data_info> > data_info::getList_catalogue() const
{
    return m_list_catalogue;
}

void data_info::setList_catalogue(const QList<QSharedPointer<data_info> > &list_catalogue)
{
    m_list_catalogue = list_catalogue;
}

void data_info::append_catalogue(QSharedPointer<data_info> &val)
{
    if(val.isNull())
        return;
    m_list_catalogue.append(val);
}

void data_info::append_catalogue_by_sort(QSharedPointer<data_info> &val)
{
    if(val.isNull())
        return;
    m_list_catalogue.append(val);
    grade_well(val);
}

void data_info::grade_well(QSharedPointer<data_info> &val)
{
   if(m_list_catalogue.length()==1)
       return;

   for (int i=0;i<m_list_catalogue.length()-1;i++) {

      QSharedPointer<data_info> catalogue= m_list_catalogue.at(i);

      if(val->get_id()==catalogue->getParent_id())  //说明val底下还有子目录
          val->append_catalogue(catalogue);

      else if(val->getParent_id()==catalogue->get_id()) //说明val也是别人的子目录
          catalogue->append_catalogue(val);

   }
}
QVariantList data_info::get_group_childs(){


    QVariantList list;
//    qDebug()<<m_list_catalogue.length()<<m_list_camera.length();

    for(int i=0;i<m_list_catalogue.count(); i++) {
        QSharedPointer<data_info> info = m_list_catalogue.at(i);
        if(info.isNull()||info->getParent_id()!="0"){ //找到根目录
            continue;
        }
        QVariantMap map;
        map.insert("dmName", info->get_name());
        map.insert("dmId", info->get_id());
        map.insert("dmCount", 0);
        map.insert("dmType", 1); //目录
        map.insert("dmGroupChilds", QVariantList());
        if(info->getList_catalogue() .length()>0){
            qDebug() <<info->get_name()<< "find catalogue childs";

            QVariantList list = info->get_group_childs2(info->getList_catalogue()); //分组中的信号列表
            map.insert("dmGroupChilds", list);
            map.insert("dmCount", list.count());


        }
        else{
            map.insert("dmGroupChilds", QVariantList());
            map.insert("dmCount", 0);
        }
        list.append(map);
    }

    return list;

}

QVariantList data_info::get_group_childs2(const QList<QSharedPointer<data_info> > &list2)
{
    QVariantList list;

    for(int i=0;i<list2.count(); i++) {
        QSharedPointer<data_info> info = list2.at(i);
        if(info.isNull()){
            continue;
        }
        QVariantMap map;
        map.insert("dmName", info->get_name());
        map.insert("dmId", info->get_id());
        map.insert("dmType", 1); //目录
        if(info->getList_catalogue() .length()>0){ //存在子目录
            qDebug() << info->get_name()<<"find catalogue childs";

            QVariantList list = info->get_group_childs2(info->getList_catalogue()); //分组中的信号列表
            map.insert("dmGroupChilds", list);
            map.insert("dmCount", list.count());


        }
        else{  //没有子目录 ，开始存摄像机

            QVariantList camera_list=info->get_group_childs3(info->get_id());

            if(camera_list.length()==0) //该目录下没有摄像机
            {
                map.insert("dmGroupChilds", QVariantList());

            }


            else{
                qDebug() <<info->get_name()<< "find camera childs";
                map.insert("dmGroupChilds", camera_list);
            }

            map.insert("dmCount", 0);
        }
        list.append(map);
    }

    return list;
}

QVariantList data_info::get_group_childs3(QString id)
{
    QVariantList list;

    if(m_list_camera.count()==0)
        return list;
    for(int i=0;i<m_list_camera.count(); i++) {
        QSharedPointer<data_info> camera = m_list_camera.at(i);
        if(camera.isNull()||camera->getRegionid()!=id){
            continue;
        }
        QVariantMap map;
        map.insert("dmName", camera->getCameraname());
        map.insert("dmId", camera->getCameraid());
        map.insert("dmGroupChilds", QVariantList());
        map.insert("dmCount", 0);
        map.insert("dmType", 0); //摄像机
        map.insert("dmUrl",camera->getUrl());
        list.append(map);
    }

    return list;
}

void data_info::send_camera_get_finish_signal(QString id)
{
    emit camera_get_finish_signal(id);
}
