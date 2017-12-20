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

QString Work::workerInfoListStr()
{
    QStringList strList;
    foreach(WorkerInfo workInfo, m_workerInfoList) {
        QStringList strWork;
        // - worker id
        strWork.append(QString("%1").arg(workInfo.worker_id));
        // - pay
        strWork.append(QString("%1").arg(workInfo.payPerDay));
        // - days
        QStringList strDateList;
        foreach(QDate workingDate, workInfo.dayList) {
            strDateList.append(workingDate.toString("yyyyMMdd"));
        }
        strWork.append(strDateList.join("-"));

        strList.append(strWork);
    }

    return strList.join(";");
}

void Work::setWorkerInfoList(QList<WorkerInfo> value)
{
    m_workerInfoList.clear();
    m_workerInfoList.append(value);
}
