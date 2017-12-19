#include "dialognewwork.h"
#include "ui_dialognewwork.h"
#include <QStandardItemModel>
#include <QStringListModel>
#include <QModelIndexList>
#include "dialogdatepicker.h"

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
        if (_worker_in_partients(worker)) {
            return;
        }

        Participant participant;
        participant.worker = m_candidateList.at(modelIdx.row());
        m_participantList.append(participant);
    }

    _update_participant_list();
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
                QVariant varParams;
                varParams.setValue<QList<QDate>>(dateList);
                m_model_participants->setData(index, varParams);
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
    m_model_participants->clear();
    m_model_participants->setRowCount(1);
    m_model_participants->setColumnCount(COLUMN_NUM);
    m_model_participants->setHorizontalHeaderItem(COLUMN_NAME, new QStandardItem(QString("이름")));
    m_model_participants->setHorizontalHeaderItem(COLUMN_PAY, new QStandardItem(QString("수당(일)")));
    m_model_participants->setHorizontalHeaderItem(COLUMN_DAYS, new QStandardItem(QString("일정")));

    ui->tableView_workParticipants->setModel(m_model_participants);
}

void DialogNewWork::_update_participant_list()
{
    m_model_participants->clear();
    m_model_participants->setRowCount(m_participantList.count());
    m_model_participants->setColumnCount(COLUMN_NUM);
    m_model_participants->setHorizontalHeaderItem(COLUMN_NAME, new QStandardItem(QString("이름")));
    m_model_participants->setHorizontalHeaderItem(COLUMN_PAY, new QStandardItem(QString("수당(일)")));
    m_model_participants->setHorizontalHeaderItem(COLUMN_DAYS, new QStandardItem(QString("일정")));
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

bool DialogNewWork::_worker_in_partients(Worker& worker)
{
    foreach(Participant participant, m_participantList) {
        if (worker.idNum() == participant.workerRef->idNum()) {
            return true;
        }
    }

    return false;
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
