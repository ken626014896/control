#include "data_info.h"

data_info::data_info(QObject *parent) : QObject(parent),
    m_name(QString()),

    m_id(QString()) ,
   m_index(-1)
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
