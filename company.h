#ifndef COMPANY_H
#define COMPANY_H

#include <QString>\

class Company
{
public:
    Company();

public:
    int idNum();
    void setIdNum(int value);
    QString name();
    void setName(QString value);
    QString address();
    void setAddress(QString value);
    QString owner();
    void setOwner(QString value);
    QString bankAccount();
    void setBankAccount(QString value);

private:
    int m_idNum;
    QString m_name;
    QString m_address;
    QString m_owner;
    QString m_bankAccount;

};

#endif // COMPANY_H
