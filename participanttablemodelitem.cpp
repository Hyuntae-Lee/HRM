#include "participanttablemodelitem.h"

ParticipantTableModelItem::ParticipantTableModelItem()
{

}

QString ParticipantTableModelItem::labelStr() {
    return QString("%1(%2)").arg(workerName).arg(workerId);
}

QString ParticipantTableModelItem::daysStr() {
    return QString("총 %1일").arg(workDateList.count());
}
