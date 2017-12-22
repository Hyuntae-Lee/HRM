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

QString Work::companyBlNum()
{
    return m_companyBlNum;
}

void Work::setCompanyBlNum(QString value)
{
    m_companyBlNum = value;
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

QString Work::name()
{
    return m_name;
}

void Work::setName(QString value)
{
    m_name = value;
}

bool Work::isWorkerIn(QString rrNum)
{
    foreach(WorkerInfo workerInfo, m_workerInfoList) {
        if (workerInfo.rrNum == rrNum) {
            return true;
        }
    }

    return false;
}
