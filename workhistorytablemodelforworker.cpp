#include "workhistorytablemodelforworker.h"
#include <QMessageBox>

typedef enum {
    COLUMN_COMPANY = 0,
    COLUMN_PAY,
    COLUMN_PAY_TOTAL,
    COLUMN_DATES,
    COLUMN_NUM
} WorkHistoryModelItemColumnIdx;

typedef struct _WorkHistoryModelItem_t {
    WorkHistoryModelItemColumnIdx idx;
    QString label;
} WorkHistoryModelItem_t;

static WorkHistoryModelItem_t s_model_item[] = {
    /*       idx      ,   label   */
    { COLUMN_COMPANY  , "업체"     },
    { COLUMN_PAY      , "일당"     },
    { COLUMN_PAY_TOTAL, "총수당"   },
    { COLUMN_DATES    , "일정"     },
};

WorkHistoryTableModelForWorker::WorkHistoryTableModelForWorker(QList<Work>& workList, QList<Worker>& workerList, QList<Company>& companyList)
    : m_workList(workList), m_workerList(workerList), m_companyList(companyList)
{
}

void WorkHistoryTableModelForWorker::clearItems()
{
    m_itemList.clear();
}

void WorkHistoryTableModelForWorker::setWorker(QString rrNum)
{
    clearItems();

    QList<Work> workList;
    if (!workListForWorker(workList, rrNum)) {
        return;
    }

    foreach (Work work, workList) {
        WorkHistoryTableModelForWorkerItem modelItem;

        QString company_blNum = work.companyBlNum();
        QString company_name = companyName(company_blNum);
        int pay = payForWorkerInWork(work, rrNum);
        QList<QDate> dateList;
        if (!workDayListForWorker(dateList, work, rrNum)) {
            QMessageBox::critical(NULL, tr("오류"), tr("일한 일 수를 찾을 수 없습니다.!!"), tr("확인"));
        }

        modelItem.setCompanyBlNum(company_blNum);
        modelItem.setCompanyName(company_name);
        modelItem.setWorkerPay(pay);
        modelItem.setWorkDayList(dateList);

        m_itemList.append(modelItem);
    }

    emit layoutChanged();
}

QVariant WorkHistoryTableModelForWorker::headerData(int section, Qt::Orientation orientation, int role) const
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

int WorkHistoryTableModelForWorker::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

int WorkHistoryTableModelForWorker::columnCount(const QModelIndex &) const
{
    return COLUMN_NUM;
}

QVariant WorkHistoryTableModelForWorker::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole) {
        WorkHistoryTableModelForWorkerItem item = m_itemList[index.row()];

        if (index.column() == COLUMN_COMPANY) {
            return item.companyName();
        }

        if (index.column() == COLUMN_DATES) {
            return item.dateListStr();
        }

        if (index.column() == COLUMN_PAY) {
            return QString("%1").arg(item.workerPay());
        }

        if (index.column() == COLUMN_PAY_TOTAL) {
            return QString("%1").arg(item.workerPay() * item.workDayList().count());
        }
    }

    return QVariant();
}

bool WorkHistoryTableModelForWorker::workListForWorker(QList<Work>& out_list, QString rrNum)
{
    if (m_workList.count() <= 0) {
        return false;
    }

    foreach (Work work, m_workList) {
        if (!work.isWorkerIn(rrNum)) {
            continue;
        }

        out_list.append(work);
    }

    return true;
}

int WorkHistoryTableModelForWorker::payForWorkerInWork(Work& work, QString rrNum)
{
    foreach (WorkerInfo workerInfo, work.workerInfoList()) {
        if (workerInfo.rrNum != rrNum) {
            continue;
        }

        return workerInfo.payPerDay;
    }

    return -1;
}

QString WorkHistoryTableModelForWorker::companyName(QString blNum)
{
    foreach (Company company, m_companyList) {
        if (company.blNum() != blNum) {
            continue;
        }

        return company.name();
    }

    return "";
}

bool WorkHistoryTableModelForWorker::workDayListForWorker(QList<QDate>& out_list, Work& work, QString rrNum)
{
    foreach (WorkerInfo workerInfo, work.workerInfoList()) {
        if (workerInfo.rrNum != rrNum) {
            continue;
        }

        out_list.clear();
        out_list.append(workerInfo.dayList);

        return true;
    }

    return false;
}
