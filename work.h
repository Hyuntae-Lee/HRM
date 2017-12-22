#ifndef WORK_H
#define WORK_H

#include <QString>
#include <QList>
#include <QDate>

struct WorkerInfo
{
    QString rrNum;
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
    QString companyBlNum();
    void setCompanyBlNum(QString value);
    QList<WorkerInfo> workerInfoList();
    void setWorkerInfoList(QList<WorkerInfo> value);
    QString name();
    void setName(QString value);
    bool isWorkerIn(QString rrNum);

private:
    int m_idNum;
    QString m_companyBlNum;
    QList<WorkerInfo> m_workerInfoList;
    QString m_name;
};

#endif // WORK_H
