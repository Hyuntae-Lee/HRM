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

QList<WorkDate> Work::dayList()
{
    return m_dayList;
}

void Work::addDayList(WorkDate value)
{
    m_dayList.append(value);
}

QList<WorkerInfo> Work::workerInfoList()
{
    return m_workerInfoList;
}

void Work::addWorkerInfoList(QList<WorkerInfo> value)
{
    m_workerInfoList.append(value);
}
