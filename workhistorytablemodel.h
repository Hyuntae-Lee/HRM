#ifndef WORKHISTORYTABLEMODEL_H
#define WORKHISTORYTABLEMODEL_H

#include <QAbstractTableModel>
#include "work.h"
#include "worker.h"
#include "company.h"
#include "workhistorytablemodelitem.h"

class WorkHistoryTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit WorkHistoryTableModel(QList<Work>& itemList, QList<Worker>& workerList, QList<Company>& companyList);

public:
    void clearItems();
    void setWorker(int worker_id);

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    bool workListForWorker(QList<Work>& out_list, int worker_id);
    int payForWorkerInWork(Work &work, int worker_id);
    QString companyName(int company_id);
    bool workDayListForWorker(QList<QDate>& out_list, Work& work, int worker_id);

private:
    QList<WorkHistoryTableModelItem> m_itemList;
    QList<Work>& m_workList;
    QList<Worker>& m_workerList;
    QList<Company>& m_companyList;
};

#endif // WORKHISTORYTABLEMODEL_H
