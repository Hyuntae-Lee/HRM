#ifndef PARTICIPANTTABLEMODELITEM_H
#define PARTICIPANTTABLEMODELITEM_H

#include <QString>
#include <QList>
#include <QDate>

class ParticipantTableModelItem
{
public:
    ParticipantTableModelItem();

public:
    QString labelStr();
    QString daysStr();

private:
    int workerId;
    QString workerName;
    int payPerDay;
    QList<QDate> workDateList;
};

#endif // PARTICIPANTTABLEMODELITEM_H
