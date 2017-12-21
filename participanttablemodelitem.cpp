#include "participanttablemodelitem.h"

ParticipantTableModelItem::ParticipantTableModelItem()
{

}

int ParticipantTableModelItem::workerId()
{
    return m_workerId;
}

void ParticipantTableModelItem::setWorkerId(int value)
{
    m_workerId = value;
}

QString ParticipantTableModelItem::workerName()
{
    return m_workerName;
}

void ParticipantTableModelItem::setWorkerName(QString value)
{
    m_workerName = value;
}

int ParticipantTableModelItem::payPerDay()
{
    return m_payPerDay;
}

void ParticipantTableModelItem::setPayPerDay(int value)
{
    m_payPerDay = value;
}

QList<QDate>& ParticipantTableModelItem::workDateList()
{
    return m_workDateList;
}

void ParticipantTableModelItem::addWorkDay(QDate value)
{
    m_workDateList.append(value);
}

void ParticipantTableModelItem::setWorkDayList(QList<QDate> value)
{
    m_workDateList.clear();
    m_workDateList.append(value);
}

QString ParticipantTableModelItem::labelStr() {
    return QString("%1(%2)").arg(workerName()).arg(workerId());
}

QString ParticipantTableModelItem::daysStr() {
    QList<QDate> dateList = workDateList();

    if (dateList.count() <= 0) {
        return "";
    }

    return QString("%1 외 %2 일").arg(dateList[0].toString(Qt::DefaultLocaleLongDate)).arg(dateList.count());
}
