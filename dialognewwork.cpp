#include "dialognewwork.h"
#include "ui_dialognewwork.h"
#include <QStandardItemModel>
#include <QStringListModel>
#include <QModelIndexList>

DialogNewWork::DialogNewWork(QList<Worker>& workerList, QList<Company>& companyList) :
    ui(new Ui::DialogNewWork)
{
    m_model_participants = new QStandardItemModel;
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

void DialogNewWork::on_pushButton_workAddParticipant_clicked()
{
    QModelIndexList modelIdxList = ui->listView_workCandidates->selectionModel()->selectedIndexes();
    foreach(QModelIndex modelIdx, modelIdxList) {
        Worker worker = m_candidateList.at(modelIdx.row());

        // check duplication
        if (_worker_in_list(worker, m_participantList)) {
            return;
        }

        m_participantList.append(worker);
    }

    _update_participant_list();
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
    m_model_participants->clear();
    m_model_participants->setRowCount(1);
    m_model_participants->setColumnCount(3);
    m_model_participants->setHorizontalHeaderItem(0, new QStandardItem(QString("이름")));
    m_model_participants->setHorizontalHeaderItem(1, new QStandardItem(QString("일정")));
    m_model_participants->setHorizontalHeaderItem(2, new QStandardItem(QString("일급여")));

    ui->tableView_workParticipants->setModel(m_model_participants);
}

void DialogNewWork::_update_participant_list()
{
    m_model_participants->clear();
    m_model_participants->setRowCount(m_participantList.count());
    m_model_participants->setColumnCount(3);
    m_model_participants->setHorizontalHeaderItem(0, new QStandardItem(QString("이름")));
    m_model_participants->setHorizontalHeaderItem(1, new QStandardItem(QString("일급여")));
    m_model_participants->setHorizontalHeaderItem(2, new QStandardItem(QString("일정")));

    for (int i = 0; i < m_participantList.count(); i++) {
        Worker worker = m_participantList.at(i);
        QString nameStr = QString("%1 (%2)").arg(worker.name()).arg(worker.idNum());

        m_model_participants->setItem(i, 0, new QStandardItem(nameStr));
    }
}

void DialogNewWork::_init_company_list()
{
    foreach(Company company, m_companyList) {
        ui->comboBox_workCompany->addItem(company.name(), company.idNum());
    }
}

bool DialogNewWork::_worker_in_list(Worker& worker, QList<Worker> list)
{
    foreach(Worker workerInList, list) {
        if (worker == workerInList) {
            return true;
        }
    }

    return false;
}
