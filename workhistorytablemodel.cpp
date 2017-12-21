#include "workhistorytablemodel.h"
#include <QMessageBox>
#include <QDebug>

typedef enum {
    WORKHISTORY_COLUMN_COMPANY = 0,
    WORKHISTORY_COLUMN_DATES,
    WORKHISTORY_COLUMN_PAY,
    WORKHISTORY_COLUMN_PAY_TOTAL,
    WORKHISTORY_COLUMN_NUM
} WorkHistoryModelItemColumnIdx;

typedef struct _WorkHistoryModelItem_t {
    WorkHistoryModelItemColumnIdx idx;
    QString label;
} WorkHistoryModelItem_t;

static WorkHistoryModelItem_t s_model_item[] = {
    /*             idx            ,   label   */
    { WORKHISTORY_COLUMN_COMPANY  , "업체"     },
    { WORKHISTORY_COLUMN_DATES    , "일정"     },
    { WORKHISTORY_COLUMN_PAY      , "일당"     },
    { WORKHISTORY_COLUMN_PAY_TOTAL, "전체수당" },
};

WorkHistoryTableModel::WorkHistoryTableModel(QList<Work>& workList, QList<Worker>& workerList, QList<Company>& companyList)
    : m_workList(workList), m_workerList(workerList), m_companyList(companyList)
{
}

void WorkHistoryTableModel::clearItems()
{
    m_itemList.clear();
}

void WorkHistoryTableModel::setWorker(int worker_id)
{
    clearItems();

    QList<Work> workList;
    if (!workListForWorker(workList, worker_id)) {
        return;
    }

    foreach (Work work, workList) {
        WorkHistoryTableModelItem modelItem;

        int company_id = work.companyId();
        QString company_name = companyName(company_id);
        int pay = payForWorkerInWork(work, worker_id);
        QList<QDate> dateList;
        if (!workDayListForWorker(dateList, work, worker_id)) {
            QMessageBox::critical(NULL, tr("오류"), tr("일한 일 수를 찾을 수 없습니다.!!"), tr("확인"));
        }

        modelItem.setCompanyId(company_id);
        modelItem.setCompanyName(company_name);
        modelItem.setWorkerPay(pay);
        modelItem.setWorkDayList(dateList);

        m_itemList.append(modelItem);
    }

    emit layoutChanged();
}

QVariant WorkHistoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section >= WORKHISTORY_COLUMN_NUM) {
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

int WorkHistoryTableModel::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

int WorkHistoryTableModel::columnCount(const QModelIndex &) const
{
    return WORKHISTORY_COLUMN_NUM;
}

QVariant WorkHistoryTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole) {
        WorkHistoryTableModelItem item = m_itemList[index.row()];

        if (index.column() == WORKHISTORY_COLUMN_COMPANY) {
            return item.companyName();
        }

        if (index.column() == WORKHISTORY_COLUMN_DATES) {
            return item.dateListStr();
        }

        if (index.column() == WORKHISTORY_COLUMN_PAY) {
            return QString("%1").arg(item.workerPay());
        }

        if (index.column() == WORKHISTORY_COLUMN_PAY_TOTAL) {
            return QString("%1").arg(item.workerPay() * item.workDayList().count());
        }
    }

    return QVariant();
}

bool WorkHistoryTableModel::workListForWorker(QList<Work>& out_list, int worker_id)
{
    foreach (Work work, m_workList) {
        if (!work.isWorkerIn(worker_id)) {
            continue;
        }

        out_list.append(work);
        return true;
    }

    return false;
}

int WorkHistoryTableModel::payForWorkerInWork(Work& work, int worker_id)
{
    foreach (WorkerInfo workerInfo, work.workerInfoList()) {
        if (workerInfo.worker_id != worker_id) {
            continue;
        }

        return workerInfo.payPerDay;
    }

    return -1;
}

QString WorkHistoryTableModel::companyName(int company_id)
{
    foreach (Company company, m_companyList) {
        if (company.idNum() != company_id) {
            continue;
        }

        return company.name();
    }

    return "";
}

bool WorkHistoryTableModel::workDayListForWorker(QList<QDate>& out_list, Work& work, int worker_id)
{
    foreach (WorkerInfo workerInfo, work.workerInfoList()) {
        if (workerInfo.worker_id != worker_id) {
            continue;
        }

        qDebug() << workerInfo.dayList[0].toString("yyMMdd");

        out_list.clear();
        out_list.append(workerInfo.dayList);

        return true;
    }

    return false;
}
