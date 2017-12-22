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

    // name
    QString name = ui->lineEdit_name->text();
    out_work->setName(name);

    // business license number
    QString companyBlNum = ui->comboBox_workCompany->currentData().toString();
    out_work->setCompanyBlNum(companyBlNum);

    // workers
    QList<WorkerInfo> workerInfoList;
    for (int i = 0; i < m_model_participants->rowCount(); i ++) {
        WorkerInfo workerInfo;
        workerInfo.rrNum = m_model_participants->workerRrNum(i);
        workerInfo.payPerDay = m_model_participants->pay(i);
        workerInfo.dayList.append(m_model_participants->dayList(i));

        workerInfoList.append(workerInfo);
    }
    out_work->setWorkerInfoList(workerInfoList);

    return true;
}

void DialogNewWork::on_pushButton_workAddParticipant_clicked()
{
    QModelIndexList modelIdxList = ui->listView_workCandidates->selectionModel()->selectedIndexes();
    foreach(QModelIndex modelIdx, modelIdxList) {
        Worker worker = m_candidateList[modelIdx.row()];
        m_model_participants->addItem(worker.rrNum(), worker.name(), 0);
    }
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
                m_model_participants->setDayList(index.row(), dateList);
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
        QString lableStr = QString("%1(%2)").arg(candidate.name()).arg(candidate.rrNum());
        itemList.append(lableStr);
    }
    m_model_candidates->setStringList(itemList);

    ui->listView_workCandidates->setModel(m_model_candidates);
}

void DialogNewWork::_init_participant_list()
{
    ui->tableView_workParticipants->setModel(m_model_participants);
}

void DialogNewWork::_init_company_list()
{
    foreach(Company company, m_companyList) {
        ui->comboBox_workCompany->addItem(company.name(), company.blNum());
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
