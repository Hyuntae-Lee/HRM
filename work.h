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
    void setWorkerInfoList(QList<WorkerInfo> value);
    QString name();
    void setName(QString value);
    bool isWorkerIn(int worker_id);

private:
    int m_idNum;
    int m_companyId;
    QList<WorkerInfo> m_workerInfoList;
    QString m_name;
};

#endif // WORK_H
