#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QStringListModel>
#include "dbhdlr.h"
#include "dialognewworker.h"
#include "dialognewcompany.h"

#define DB_FILE_PATH "/data/main.db"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_dbHdlr = new DBHdlr;
    m_model_worker = new QStringListModel;
    m_model_company = new QStringListModel;

    ui->setupUi(this);

    ui->listView_worker->setModel(m_model_worker);
    ui->listView_company->setModel(m_model_company);
}

MainWindow::~MainWindow()
{
    delete m_dbHdlr;
    delete m_model_worker;
    delete m_model_company;
    delete ui;
}

void MainWindow::on_pushButton_connectDB_clicked()
{
    // 임시.. 개발 중
    //QString curPath = QDir::currentPath();
    QString curPath = "D:/projects/etc/HRM/src";

    m_dbHdlr->connectToDB(curPath + DB_FILE_PATH);
}

void MainWindow::on_pushButton_newHR_clicked()
{
    DialogNewWorker dlg;

    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    Worker worker;
    if (!dlg.getWorkInfo(&worker)) {
        return;
    }

    if (!m_dbHdlr->addWorker(worker)) {
        return;
    }

    QMessageBox::information(this, tr("Confirm"), tr("A new worker is added."), tr("Ok"));
}

void MainWindow::on_pushButton_refreshHR_clicked()
{
    _load_worker_list(m_workerList);
    _update_worker_list(m_workerList);
}

void MainWindow::on_listView_worker_clicked(const QModelIndex &index)
{
    Worker worker = m_workerList.at(index.row());

    QString name = worker.name();
    QString idStr = QString("%1").arg(worker.idNum());
    QString phoneNum = worker.phoneNum();
    QString address = worker.address();
    QString majorStr = worker.majorStr();

    ui->label_workerName->setText(name);
    ui->label_workerId->setText(idStr);
    ui->label_workerPhoneNum->setText(phoneNum);
    ui->label_workerAddr->setText(address);
    ui->label_workerMajor->setText(majorStr);
}

void MainWindow::on_pushButton_newCompany_clicked()
{
    DialogNewCompany dlg;

    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    Company company;
    if (!dlg.getCompanyInfo(&company)) {
        return;
    }

    if (!m_dbHdlr->addCompany(company)) {
        return;
    }

    QMessageBox::information(this, tr("Confirm"), tr("A new company is added."), tr("Ok"));
}

void MainWindow::on_pushButton_refreshCompany_clicked()
{
    _load_company_list(m_companyList);
    _update_company_list(m_companyList);
}

void MainWindow::on_listView_company_clicked(const QModelIndex &index)
{
    Company company = m_companyList.at(index.row());

    QString name = company.name();
    QString idStr = QString("%1").arg(company.idNum());
    QString phoneNum = company.phoneNum();
    QString address = company.address();
    QString owner = company.owner();
    QString bankAccount = company.bankAccount();

    ui->label_companyName->setText(name);
    ui->label_companyId->setText(idStr);
    ui->label_companyOwner->setText(owner);
    ui->label_companyAddress->setText(address);
    ui->label_companyPhoneNum->setText(phoneNum);
    ui->label_companyAccount->setText(bankAccount);
}

void MainWindow::_update_worker_list(QList<Worker> listValue)
{
    QStringList strList;
    foreach (Worker worker, listValue) {
        QString lableStr = QString("%1 (%2)").arg(worker.name()).arg(worker.idNum());
        strList.append(lableStr);
    }

    m_model_worker->setStringList(strList);
}

void MainWindow::_load_worker_list(QList<Worker>& listValue)
{
    listValue.clear();
    if (!m_dbHdlr->getWorkerList(listValue)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot load data from!!"), tr("Ok"));
        return;
    }
}

void MainWindow::_update_company_list(QList<Company> listValue)
{
    QStringList strList;
    foreach (Company company, listValue) {
        QString lableStr = QString("%1 (%2)").arg(company.name()).arg(company.idNum());
        strList.append(lableStr);
    }

    m_model_company->setStringList(strList);
}

void MainWindow::_load_company_list(QList<Company> &listValue)
{
    listValue.clear();
    if (!m_dbHdlr->getCompanyList(listValue)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot load data from!!"), tr("Ok"));
        return;
    }
}
