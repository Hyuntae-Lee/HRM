#ifndef WORK_H
#define WORK_H

#include <QString>
#include <QList>
#include <QDate>

struct WorkerInfo
{
    int worker_id;
    QList<QDate> dayList;
    int payPerDay;
};

class Work
{
public:
    Work();

public:
    int idNum();
    void setIdNum(int value);
    int companyId();
    void setCompanyId(int value);
    QList<WorkerInfo> workerInfoList();
    QString workerInfoListStr();
    void addWorkerInfoList(QList<WorkerInfo> value);
    QDate dateBegin();
    void setDateBegin(QDate value);
    QDate dateEnd();
    void setDateEnd(QDate value);

private:
    int m_idNum;
    int m_companyId;
    QList<WorkerInfo> m_workerInfoList;
    QDate m_dateBegin;
    QDate m_dateEnd;
};

#endif // WORK_H
