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
        //


        QString strDateList = QString("%1")
    }
}

void Work::addWorkerInfoList(QList<WorkerInfo> value)
{
    m_workerInfoList.append(value);
}

QDate Work::dateBegin()
{
    return m_dateBegin;
}

void Work::setDateBegin(QDate value)
{
    m_dateBegin = value;
}

QDate Work::dateEnd()
{
    return m_dateEnd;
}

void Work::setDateEnd(QDate value)
{
    m_dateEnd = value;
}
