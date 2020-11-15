#ifndef DATA_INFO_H
#define DATA_INFO_H

#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QVariantList>
#include <QSharedPointer>

class data_info : public QObject
{
    Q_OBJECT
public:
    explicit data_info(QObject *parent = nullptr);
    QString get_name();
    void set_name(QString val);

    int get_index();
    void set_index(int val);

    QString get_id();
    void set_id(QString val);

//    QString
    virtual void start();
    virtual void stop();
    QString getIp_address() const;
    void setIp_address(const QString &ip_address);

    QString getParent_id() const;
    void setParent_id(const QString &parent_id);

    QList<QString> getParent_id_lsit() const;
    void setParent_id_lsit(const QList<QString> &parent_id_lsit);

    QString getAuxstreamname() const;
    void setAuxstreamname(const QString &auxstreamname);

    QString getCameraid() const;
    void setCameraid(const QString &cameraid);

    QString getCameraname() const;
    void setCameraname(const QString &cameraname);

    QString getMainstreamname() const;
    void setMainstreamname(const QString &mainstreamname);

    QString getRegionid() const;
    void setRegionid(const QString &regionid);

    int getResult() const;
    void setResult(int result);

    QString getResultdesc() const;
    void setResultdesc(const QString &resultdesc);

    QString getUrl() const;
    void setUrl(const QString &url);

    QList<QSharedPointer<data_info> > getList_camera() const;
    void setList_camera(const QList<QSharedPointer<data_info> > &list_camera);
    void append_camera(QSharedPointer<data_info> &val);
    void append_camera_by_sort(QSharedPointer<data_info> &val);
    int getSort() const;
    void setSort(int sort);

    QList<QSharedPointer<data_info> > getList_catalogue() const;
    void setList_catalogue(const QList<QSharedPointer<data_info> > &list_catalogue);
    void append_catalogue(QSharedPointer<data_info> &val);
    void append_catalogue_by_sort(QSharedPointer<data_info> &val);

    QVariantList get_group_childs(); //获取根目录

    QVariantList get_group_childs2(const QList<QSharedPointer<data_info> > &list2);//获取不是根目录


    QVariantList get_group_childs3(QString id); //获取目录下的摄像机



    void send_camera_get_finish_signal(QString id);
signals:
    void camera_get_finish_signal(QString id); //摄像机获取完毕发送
public slots:


protected:
    QString m_name;
    QString m_id;
    int m_index;//设备索引

    QString m_ip_address;


    QString m_parent_id;//父级目录编号
    QList<QString> m_parent_id_lsit;//所有父级目录编号
    int m_sort; //目录排序


    QString m_auxstreamname ;//辅码流
    QString m_cameraid ;//摄像机编号
    QString m_cameraname ;//摄像机名称
    QString m_mainstreamname ;//主码流
    QString m_regionid ;//目录编号


    int m_result ;//返回码
    QString m_resultdesc ;//返回说明
    QString m_url ;//播放 uri


    QList<QSharedPointer<data_info>> m_list_camera; //摄像机列表
    QList<QSharedPointer<data_info>> m_list_catalogue; //目录列表
    //以上两个变量多个地方用到， 比如目录对象下也会有摄像机列表
    void grade_well(QSharedPointer<data_info> &val);//处理好目录分级关系
};

#endif // DATA_INFO_H
