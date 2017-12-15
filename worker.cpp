#include "worker.h"

Worker::Worker()
{

}

QString Worker::name()
{
    return m_name;
}

void Worker::setName(QString value)
{
    m_name = value;
}

int Worker::idNum()
{
    return m_idNum;
}

void Worker::setIdNum(int value)
{
    m_idNum = value;
}

QList<QString> Worker::jobList()
{
    return m_jobList;
}

void Worker::addJob(QString value)
{
    m_jobList.append(value);
}

QString Worker::picturePath()
{
    return m_picturePath;
}

void Worker::setPicturePath(QString value)
{
    m_picturePath = value;
}

int Worker::age()
{
    return m_age;
}

void Worker::setAge(int value)
{
    m_age = value;
}
