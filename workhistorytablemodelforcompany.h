#ifndef WORKHISTORYTABLEMODELFORCOMPANY_H
#define WORKHISTORYTABLEMODELFORCOMPANY_H

#include <QAbstractTableModel>
#include "work.h"
#include "worker.h"
#include "company.h"
#include "workhistorytablemodelforcompanyitem.h"

class WorkHistoryTableModelForCompany : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit WorkHistoryTableModelForCompany(QList<Work>& workList, QList<Worker>& workerList, QList<Company>& companyList);

public:
    void clearItems();
    void setCompany(int compay_id);

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    bool workListForCompany(QList<Work>& out_list, QString blNum);

private:
    QList<WorkHistoryTableModelForCompanyItem> m_itemList;
    QList<Work>& m_workList;
    QList<Worker>& m_workerList;
    QList<Company>& m_companyList;
};

#endif // WORKHISTORYTABLEMODELFORCOMPANY_H
