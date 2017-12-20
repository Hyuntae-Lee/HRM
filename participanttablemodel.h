#ifndef PARTICIPANTTABLEMODEL_H
#define PARTICIPANTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QList>
#include "participanttablemodelitem.h"

class ParticipantTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ParticipantTableModel(QObject *parent = 0);

public:
    void clearItems();
    void addItem(int id, QString name, int pay, QList<QDate> days);
    bool setPay(int index, int pay);
    bool setDays(int index, QList<QDate> days);

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    bool _worker_in_participants(int worker_id);

private:
    QList<ParticipantTableModelItem> m_itemList;
};

#endif // PARTICIPANTTABLEMODEL_H
