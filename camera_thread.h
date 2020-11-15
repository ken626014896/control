#ifndef CAMERA_THREAD_H
#define CAMERA_THREAD_H
#include "data_info.h"

#include <QObject>
#include <QThread>

class camera_thread :public QThread
{
    Q_OBJECT
public:
    explicit camera_thread(data_info *data, QObject *parent = nullptr);
protected:
    void run();

private:
    data_info *m_data_info;
};

#endif // CAMERA_THREAD_H
