#ifndef WORKER_H
#define WORKER_H

#include <QString>
#include <QList>

class Worker
{
public:
    Worker();

public:
    QString name();
    void setName(QString value);
    int idNum();
    void setIdNum(int value);
    QList<QString> jobList();
    void addJob(QString value);
    QString picturePath();
    void setPicturePath(QString value);
    int age();
    void setAge(int value);
    QString address();
    void setAddress(QString value);
    QString phoneNum();
    void setPhoneNum(QString value);
    QString bankAccount();
    void setBankAccount(QString value);

private:
    QString m_name;
    int m_idNum;
    QList<QString> m_jobList;
    QString m_picturePath;
    int m_age;
    QString m_address;
    QString m_phoneNum;
    QString m_bankAccount;
};

#endif // WORKER_H
