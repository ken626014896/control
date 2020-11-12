#ifndef HTTP_THREAD_H
#define HTTP_THREAD_H
#include "data_info.h"

#include <QObject>
#include <QThread>

class http_thread :public QThread
{
    Q_OBJECT
public:
    explicit http_thread(data_info *data, QObject *parent = nullptr);
protected:
    void run();

private:
    data_info *m_data_info;
};

#endif // HTTP_THREAD_H
