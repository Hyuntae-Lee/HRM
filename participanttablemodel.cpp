#include "participanttablemodel.h"

typedef enum {
    COLUMN_LABEL = 0,
    COLUMN_PAY,
    COLUMN_DATES,
    COLUMN_NUM
} ModelItemColumnIdx;

typedef struct _ModelItem_t {
    ModelItemColumnIdx idx;
    QString label;
} ModelItem_t;

ModelItem_t s_model_item[] = {
    /*     idx    ,    label   */
    { COLUMN_LABEL, "대상"     },
    { COLUMN_PAY  , "수당(일)" },
    { COLUMN_DATES, "일정"     }
};

ParticipantTableModel::ParticipantTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ParticipantTableModel::clearItems()
{
    m_itemList.clear();
}

void ParticipantTableModel::addItem(int id, QString name, int pay, QList<QDate> days)
{
    if (_worker_in_participants(id)) {
        return;
    }

    ParticipantTableModelItem item;
    item.setWorkerId(id);
    item.setWorkerName(name);
    item.setPayPerDay(pay);
    item.addWorkDayList(days);
}

bool ParticipantTableModel::setPay(int index, int pay)
{
    if (index >= m_itemList.count()) {
        return false;
    }

    m_itemList[index].payPerDay = pay;

    return true;
}

bool ParticipantTableModel::setDays(int index, QList<QDate> days)
{
    if (index >= m_itemList.count()) {
        return false;
    }

    m_itemList[index].workDateList.clear();
    m_itemList[index].workDateList.append(days);

    return true;
}

QVariant ParticipantTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section >= COLUMN_NUM) {
            return QVariant();
        }

        return s_model_item[section].label;
    }
    else if (orientation == Qt::Vertical) {
        return QString("%1").arg(section);
    }
    else {
        return QVariant();
    }
}

int ParticipantTableModel::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

int ParticipantTableModel::columnCount(const QModelIndex &) const
{
    return COLUMN_NUM;
}

QVariant ParticipantTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole) {
        ParticipantTableModelItem item = m_itemList[index.row()];

        if (index.column() == COLUMN_LABEL) {
            return item.labelStr();
        }

        if (index.column() == COLUMN_PAY) {
            return QString("%1 원").arg(item.payPerDay);
        }

        if (index.column() == COLUMN_DATES) {
            return item.daysStr();
        }
    }

    return QVariant();
}

bool ParticipantTableModel::_worker_in_participants(int worker_id)
{
    foreach(ParticipantTableModelItem item, m_itemList) {
        if (worker_id == item.workerId()) {
            return true;
        }
    }

    return false;
}
