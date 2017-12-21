#include "work.h"

Work::Work()
{

}

int Work::idNum()
{
    return m_idNum;
}

void Work::setIdNum(int value)
{
    m_idNum = value;
}

int Work::companyId()
{
    return m_companyId;
}

void Work::setCompanyId(int value)
{
    m_companyId = value;
}

QList<WorkerInfo> Work::workerInfoList()
{
    return m_workerInfoList;
}

void Work::setWorkerInfoList(QList<WorkerInfo> value)
{
    m_workerInfoList.clear();
    m_workerInfoList.append(value);
}
