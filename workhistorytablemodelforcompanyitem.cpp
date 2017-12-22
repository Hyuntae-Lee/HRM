#include "workhistorytablemodelforcompanyitem.h"

WorkHistoryTableModelForCompanyItem::WorkHistoryTableModelForCompanyItem()
{

}

int WorkHistoryTableModelForCompanyItem::workerPay()
{
    return m_workerPay;
}

void WorkHistoryTableModelForCompanyItem::setWorkerPay(int value)
{
    m_workerPay = value;
}

int WorkHistoryTableModelForCompanyItem::companyId()
{
    return m_companyId;
}

void WorkHistoryTableModelForCompanyItem::setCompanyId(int value)
{
    m_companyId = value;
}

QString WorkHistoryTableModelForCompanyItem::companyName()
{
    return m_companyName;
}

void WorkHistoryTableModelForCompanyItem::setCompanyName(QString value)
{
    m_companyName = value;
}

QList<QDate> WorkHistoryTableModelForCompanyItem::workDayList()
{
    return m_workDayList;
}

void WorkHistoryTableModelForCompanyItem::setWorkDayList(QList<QDate>& dayList)
{
    m_workDayList.clear();
    m_workDayList.append(dayList);
}

QString WorkHistoryTableModelForCompanyItem::dateListStr()
{
    QStringList strList;
    foreach (QDate date, m_workDayList) {
        strList.append(date.toString("MM/dd"));
    }

    return strList.join(", ");
}