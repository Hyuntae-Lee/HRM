#ifndef WORKHISTORYTABLEMODELFORWORKERITEM_H
#define WORKHISTORYTABLEMODELFORWORKERITEM_H

#include <QList>
#include <QDate>

class WorkHistoryTableModelForWorkerItem
{
public:
    WorkHistoryTableModelForWorkerItem();

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

#endif // WORKHISTORYTABLEMODELFORWORKERITEM_H
