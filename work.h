#ifndef WORK_H
#define WORK_H

#include <QString>
#include <QList>

struct WorkDate
{
    int year;
    int month;
    int day;
};

struct WorkerInfo
{
    int worker_id;
    QList<WorkDate> dayList;
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
    QList<WorkDate> dayList();
    void addDayList(WorkDate value);
    QList<WorkerInfo> workerInfoList();
    void addWorkerInfoList(QList<WorkerInfo> value);

private:
    int m_idNum;
    int m_companyId;
    QList<WorkDate> m_dayList;
    QList<WorkerInfo> m_workerInfoList;
};

#endif // WORK_H
