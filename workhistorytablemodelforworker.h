#ifndef WORKHISTORYTABLEMODELFORWORKER_H
#define WORKHISTORYTABLEMODELFORWORKER_H

#include <QAbstractTableModel>
#include "work.h"
#include "worker.h"
#include "company.h"
#include "workhistorytablemodelforworkeritem.h"

class WorkHistoryTableModelForWorker : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit WorkHistoryTableModelForWorker(QList<Work>& itemList, QList<Worker>& workerList, QList<Company>& companyList);

public:
    void clearItems();
    void setWorker(QString rrNum);

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    bool workListForWorker(QList<Work>& out_list, QString rrNum);
    int payForWorkerInWork(Work &work, QString rrNum);
    QString companyName(QString blNum);
    bool workDayListForWorker(QList<QDate>& out_list, Work& work, QString rrNum);

private:
    QList<WorkHistoryTableModelForWorkerItem> m_itemList;
    QList<Work>& m_workList;
    QList<Worker>& m_workerList;
    QList<Company>& m_companyList;
};

#endif // WORKHISTORYTABLEMODELFORWORKER_H
