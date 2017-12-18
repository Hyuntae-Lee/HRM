#ifndef DIALOGNEWWORK_H
#define DIALOGNEWWORK_H

#include <QDialog>
#include "worker.h"
#include "company.h"

namespace Ui {
class DialogNewWork;
}

class QStringListModel;
class QStandardItemModel;
class DialogNewWork : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewWork(QList<Worker> &workerList, QList<Company> &companyList);
    ~DialogNewWork();

private slots:
    void on_pushButton_workAddParticipant_clicked();

private:
    void _init_candidate_list();
    void _init_participant_list();
    void _update_participant_list();
    void _init_company_list();
    bool _worker_in_list(Worker& worker, QList<Worker> list);

private:
    Ui::DialogNewWork *ui;
    QStringListModel* m_model_candidates;
    QStandardItemModel *m_model_participants;
    QList<Worker> m_candidateList;
    QList<Worker> m_participantList;
    QList<Company> m_companyList;
};

#endif // DIALOGNEWWORK_H
