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

#endif // WORKHISTORYTABLEMODELFORWORKERITEM_H
