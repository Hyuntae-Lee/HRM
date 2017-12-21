#ifndef WORKHISTORYTABLEMODELITEM_H
#define WORKHISTORYTABLEMODELITEM_H

#include <QList>
#include <QDate>

class WorkHistoryTableModelItem
{
public:
    WorkHistoryTableModelItem();

public:
    int workerPay();
    void setWorkerPay(int value);
    int companyId();
    void setCompanyId(int value);
    QString companyName();
    void setCompanyName(QString value);
    QList<QDate> workDayList();
    void setWorkDayList(QList<QDate>& dayList);
    QString dateListStr();

private:
    int m_workerPay;
    int m_companyId;
    QString m_companyName;
    QList<QDate> m_workDayList;
};

#endif // WORKHISTORYTABLEMODELITEM_H
