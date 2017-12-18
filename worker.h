#ifndef WORKER_H
#define WORKER_H

#include <QString>
#include <QList>

class Worker
{
public:
    Worker();

public:
    int idNum();
    void setIdNum(int value);
    QString name();
    void setName(QString value);
    QList<QString> majorList();
    QString majorStr();
    void addMajor(QString value);
    QString picturePath();
    void setPicturePath(QString value);
    QString address();
    void setAddress(QString value);
    QString phoneNum();
    void setPhoneNum(QString value);
    QString bankAccount();
    void setBankAccount(QString value);
    bool operator ==(Worker &w) const;

private:
    int m_idNum;
    QString m_name;
    QList<QString> m_majorList;
    QString m_picturePath;
    int m_age;
    QString m_address;
    QString m_phoneNum;
    QString m_bankAccount;
};

#endif // WORKER_H
