#include "dialognewwork.h"
#include "ui_dialognewwork.h"
#include <QStringListModel>
#include <QModelIndexList>
#include "dialogdatepicker.h"
#include "participanttablemodel.h"

DialogNewWork::DialogNewWork(QList<Worker>& workerList, QList<Company>& companyList) :
    ui(new Ui::DialogNewWork)
{
    m_model_participants = new ParticipantTableModel;
    m_model_candidates = new QStringListModel;
    m_candidateList.append(workerList);
    m_companyList.append(companyList);

    ui->setupUi(this);

    _init_candidate_list();
    _init_participant_list();
    _init_company_list();
}

DialogNewWork::~DialogNewWork()
{
    delete m_model_participants;
    delete m_model_candidates;
    delete ui;
}

bool DialogNewWork::getWork(Work* out_work)
{
    if (!out_work) {
        return false;
    }

    // company id
    int companyId = ui->comboBox_workCompany->currentData().toInt();
    out_work->setCompanyId(companyId);

    // working day list
    QList<QDate> workDateList = m_model_participants->

    QList<WorkerInfo> workInfoList;
    foreach(Participant participant, m_participantList) {
        WorkerInfo workInfo;
        workInfo.worker_id = participant.workerId;
        workInfo.payPerDay = participant.payPerDay;
        workInfo.dayList.append(participant.workDateList);

        workInfoList.append(workInfo);
    }
    out_work->setWorkerInfoList(workInfoList);

    return true;
}

void DialogNewWork::on_pushButton_workAddParticipant_clicked()
{
    QModelIndexList modelIdxList = ui->listView_workCandidates->selectionModel()->selectedIndexes();
    foreach(QModelIndex modelIdx, modelIdxList) {
        Worker worker = m_candidateList.at(modelIdx.row());
        m_model_participants->addItem(worker.idNum(), worker.name(), 0, QList<QDate>());
    }

    ui->tableView_workParticipants->update();
}

void DialogNewWork::on_tableView_workParticipants_clicked(const QModelIndex &index)
{
    switch (index.column()) {
    case COLUMN_NAME:
        break;
    case COLUMN_PAY:
        break;
    case COLUMN_DAYS:
        {
            QList<QDate> dateList;
            if (_pick_dates(dateList)) {
                m_model_participants->setDays(index.row(), dateList);
            }
        }
        break;
    default:
        break;
    }
}

void DialogNewWork::_init_candidate_list()
{
    QStringList itemList;
    foreach(Worker candidate, m_candidateList) {
        QString lableStr = QString("%1 (%2)").arg(candidate.name()).arg(candidate.idNum());
        itemList.append(lableStr);
    }
    m_model_candidates->setStringList(itemList);

    ui->listView_workCandidates->setModel(m_model_candidates);
}

void DialogNewWork::_init_participant_list()
{
    ui->tableView_workParticipants->setModel(m_model_participants);
    m_model_participants->clearItems();
}

void DialogNewWork::_init_company_list()
{
    foreach(Company company, m_companyList) {
        ui->comboBox_workCompany->addItem(company.name(), company.idNum());
    }
}

bool DialogNewWork::_pick_dates(QList<QDate>& list)
{
    list.clear();

    DialogDatePicker dlg;
    if (dlg.exec() != QDialog::Accepted) {
        return false;
    }

    QList<QDate> dateList;
    if (!dlg.getSelectedDates(dateList)) {
        return false;
    }

    list.append(dateList);
    return true;
}

QString DialogNewWork::_get_label_string_of_worker(int id)
{
    foreach(Worker worker, m_candidateList) {
        if (worker.idNum() == id) {
            return worker.labelStr();
        }
    }

    return "";
}
