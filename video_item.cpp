﻿#include "video_item.h"


#include <QDateTime>
#include <QtDebug>

video_item::video_item(QObject *parent):
    m_pix_map(QPixmap()),
    m_index(-1),
    m_data_model_signal_source(nullptr),
    m_id(QString())
{
//  qDebug()<<this;
}

video_item::~video_item()
{
    if(!m_data_info.isNull()){
//        qDebug()<<this<<qtr("断开连接");
        disconnect(m_data_info.data(), &data_info::image_incoming_signal,
                   this, &video_item::image_incoming_slot);
    }
}

void video_item::set_pix_map(QPixmap &map)
{
    m_pix_map = map;
    this->update();
}

QPixmap video_item::get_pix_map()
{
    return m_pix_map;
}

int video_item::get_index()
{
    return m_index;
}

void video_item::set_index(int val)
{
    m_index = val;
    emit index_changed();
}

QString video_item::get_id()
{
    return m_id;
}

void video_item::create_data_info()
{
    if(m_id.isEmpty()){
        if(!m_data_info.isNull()){
            disconnect(m_data_info.data(), &data_info::image_incoming_signal,
                       this, &video_item::image_incoming_slot);

            m_data_info = QSharedPointer<data_info>();
        }

        return;
    }
    if(!m_data_info.isNull() && m_data_info->get_id() != m_id){
        disconnect(m_data_info.data(), &data_info::image_incoming_signal,
                   this, &video_item::image_incoming_slot);

        m_data_info = QSharedPointer<data_info>();
    }
    if(m_data_info.isNull() && m_data_model_signal_source != nullptr && !m_id.isEmpty()){
            m_data_info = m_data_model_signal_source->get_data_by_id(m_id);
            if(!m_data_info.isNull()){
//                qDebugxx(qtr("建立连接"), m_data_info->get_name());
                qDebug()<<"connect viode"<<this;


                connect(m_data_info.data(), &data_info::image_incoming_signal,
                        this, &video_item::image_incoming_slot);

            }

    }
}

void video_item::set_id(QString val)
{
    m_id = val;

    create_data_info();
    emit id_changed();
}

data_model *video_item::get_model()
{
    return m_data_model_signal_source;
}

void video_item::set_model(data_model *val)
{
    m_data_model_signal_source = val;
//    qDebug()<<this<<2;
    emit model_changed();

    create_data_info();
}


void video_item::set_map(int idx, QPixmap map)
{
    if(idx == m_index){
        set_pix_map(map);
    }
}

void video_item::set_image(QString id, QImage img)
{
    if(m_id == id){
        m_image = img;
        this->update();
    }

}

void video_item::clear_image()
{
    m_image = QImage();
    this->update();
}

void video_item::paint(QPainter *painter)
{
//    if(m_pix_map.isNull()){
//        return;
//    }
//    qDebug() << "set_map:" << m_index << ":" << this->width() << ":" << this->height();
//    painter->drawPixmap(this->x(),this->y(),
//                        m_pix_map.scaled(this->width(), this->height(), Qt::KeepAspectRatioByExpanding));
    if(!m_image.isNull()){
        painter->drawImage(this->x(), this->y(), m_image.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
    }
}

void video_item::image_incoming_slot(QString id, QImage img)
{
//    qDebugxxx(qtr("显示图像"), m_id, id);
    if(m_id == id){

        m_image = img;

        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
//         qDebug()  <<"update" <<img.size()<<current_date;
        this->update();
        if(isfristplay){

            emit play_signal();
            isfristplay=false;
        }

    }
}
