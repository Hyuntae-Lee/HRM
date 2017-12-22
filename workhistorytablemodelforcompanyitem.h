#ifndef WORKHISTORYTABLEMODELFORCOMPANYITEM_H
#define WORKHISTORYTABLEMODELFORCOMPANYITEM_H

#include <QList>
#include <QDate>

class WorkHistoryTableModelForCompanyItem
{
public:
    WorkHistoryTableModelForCompanyItem();

public:
    int workerPay();
    void setWorkerPay(int value);
    QString companyBlNum();
    void setCompanyBlNum(QString value);
    QString companyName();
    void setCompanyName(QString value);
    QList<QDate> workDayList();
    void setWorkDayList(QList<QDate>& dayList);
    QString dateListStr();

private:
    int m_workerPay;
    QString m_companyBlNum;
    QString m_companyName;
    QList<QDate> m_workDayList;
};

#endif // WORKHISTORYTABLEMODELFORCOMPANYITEM_H
