#ifndef DIALOGNEWWORK_H
#define DIALOGNEWWORK_H

#include <QDialog>
#include "worker.h"
#include "company.h"
#include "work.h"

namespace Ui {
class DialogNewWork;
}

class QStringListModel;
class QStandardItemModel;

typedef struct _Participant {
    Worker& worker;
    QList<QDate> workDates;
} Participant;

class DialogNewWork : public QDialog
{
    Q_OBJECT

    enum PARTICIPANT_TABLE_COLUMN {
        COLUMN_NAME = 0,
        COLUMN_PAY,
        COLUMN_DAYS,
        COLUMN_NUM
    };

public:
    explicit DialogNewWork(QList<Worker> &workerList, QList<Company> &companyList);
    ~DialogNewWork();

public:

private slots:
    void on_pushButton_workAddParticipant_clicked();
    void on_tableView_workParticipants_clicked(const QModelIndex &index);

private:
    void _init_candidate_list();
    void _init_participant_list();
    void _update_participant_list();
    void _init_company_list();
    bool _worker_in_partients(Worker& worker);
    bool _pick_dates(QList<QDate> &list);

private:
    Ui::DialogNewWork *ui;
    QStringListModel* m_model_candidates;
    QStandardItemModel *m_model_participants;
    QList<Worker> m_candidateList;
    QList<Participant> m_participantList;
    QList<Company> m_companyList;
    // result
    QList<WorkerInfo> m_workerInfoList;
};

#endif // DIALOGNEWWORK_H
