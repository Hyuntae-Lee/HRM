#include "workhistorytablemodelitem.h"

WorkHistoryTableModelItem::WorkHistoryTableModelItem()
{

}

int WorkHistoryTableModelItem::workerPay()
{
    return m_workerPay;
}

void WorkHistoryTableModelItem::setWorkerPay(int value)
{
    m_workerPay = value;
}

int WorkHistoryTableModelItem::companyId()
{
    return m_companyId;
}

void WorkHistoryTableModelItem::setCompanyId(int value)
{
    m_companyId = value;
}

QString WorkHistoryTableModelItem::companyName()
{
    return m_companyName;
}

void WorkHistoryTableModelItem::setCompanyName(QString value)
{
    m_companyName = value;
}

QList<QDate> WorkHistoryTableModelItem::workDayList()
{
    return m_workDayList;
}

void WorkHistoryTableModelItem::setWorkDayList(QList<QDate>& dayList)
{
    m_workDayList.clear();
    m_workDayList.append(dayList);
}

QString WorkHistoryTableModelItem::dateListStr()
{
    QStringList strList;
    foreach (QDate date, m_workDayList) {
        strList.append(date.toString("MM/dd"));
    }

    return strList.join(", ");
}
