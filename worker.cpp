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

QString Worker::address()
{
    return m_address;
}

void Worker::setAddress(QString value)
{
    m_address = value;
}

QString Worker::phoneNum()
{
    return m_phoneNum;
}

void Worker::setPhoneNum(QString value)
{
    m_phoneNum = value;
}

QString Worker::bankAccount()
{
    return m_bankAccount;
}

void Worker::setBankAccount(QString value)
{
    m_bankAccount = value;
}













