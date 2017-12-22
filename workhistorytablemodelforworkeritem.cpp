#include "workhistorytablemodelforworkeritem.h"

WorkHistoryTableModelForWorkerItem::WorkHistoryTableModelForWorkerItem()
{

}

int WorkHistoryTableModelForWorkerItem::workerPay()
{
    return m_workerPay;
}

void WorkHistoryTableModelForWorkerItem::setWorkerPay(int value)
{
    m_workerPay = value;
}

QString WorkHistoryTableModelForWorkerItem::companyBlNum()
{
    return m_companyBlNum;
}

void WorkHistoryTableModelForWorkerItem::setCompanyBlNum(QString value)
{
    m_companyBlNum = value;
}

QString WorkHistoryTableModelForWorkerItem::companyName()
{
    return m_companyName;
}

void WorkHistoryTableModelForWorkerItem::setCompanyName(QString value)
{
    m_companyName = value;
}

QList<QDate> WorkHistoryTableModelForWorkerItem::workDayList()
{
    return m_workDayList;
}

void WorkHistoryTableModelForWorkerItem::setWorkDayList(QList<QDate>& dayList)
{
    m_workDayList.clear();
    m_workDayList.append(dayList);
}

QString WorkHistoryTableModelForWorkerItem::dateListStr()
{
    QStringList strList;
    foreach (QDate date, m_workDayList) {
        strList.append(date.toString("MM/dd"));
    }

    return strList.join(", ");
}
