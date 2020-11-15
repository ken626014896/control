#ifndef CAMERA_INFO_H
#define CAMERA_INFO_H
#include "sy_logger.h"
#include <QObject>
#include  "data_info.h"
#include  "camera_thread.h"
#include <QThread>
class camera_info : public data_info
{
    Q_OBJECT
public:
    explicit camera_info(QObject *parent = nullptr);
    ~camera_info();
    void start();
    void stop();
signals:

private:
    camera_thread *m_camera_thread;
public slots:
};

#endif // CAMERA_INFO_H
