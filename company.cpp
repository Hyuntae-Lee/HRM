#include "company.h"

Company::Company()
{

}

int Company::idNum()
{
    return m_idNum;
}

void Company::setIdNum(int value)
{
    m_idNum = value;
}

QString Company::name()
{
    return m_name;
}

void Company::setName(QString value)
{
    m_name = value;
}

QString Company::address()
{
    return m_address;
}

void Company::setAddress(QString value)
{
    m_address = value;
}

QString Company::owner()
{
    return m_owner;
}

void Company::setOwner(QString value)
{
    m_owner = value;
}

QString Company::bankAccount()
{
    return m_bankAccount;
}

void Company::setBankAccount(QString value)
{
    m_bankAccount = value;
}
