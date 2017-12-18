#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbhdlr.h"
#include "dialognewworker.h"
#include <QDir>
#include <QMessageBox>
#include <QStringListModel>

#define DB_FILE_PATH "/data/main.db"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_dbHdlr = new DBHdlr;
    m_model_worker = new QStringListModel;

    ui->setupUi(this);

    _init_table_worker();
}

MainWindow::~MainWindow()
{
    delete m_dbHdlr;
    delete m_model_worker;
    delete ui;
}

void MainWindow::on_pushButton_connectDB_clicked()
{
    // 임시.. 개발 중
    //QString curPath = QDir::currentPath();
    QString curPath = "D:/projects/etc/HRM/src";

    m_dbHdlr->connectToDB(curPath + DB_FILE_PATH);
}

void MainWindow::on_pushButton_refreshHR_clicked()
{
    _load_worker_list(m_workerList);
    _update_table_worker(m_workerList);
}

void MainWindow::on_pushButton_newHR_clicked()
{
    DialogNewWorker dlgNewWorker;

    if (dlgNewWorker.exec() != QDialog::Accepted) {
        return;
    }

    Worker worker;
    if (!dlgNewWorker.getWorkInfo(&worker)) {
        return;
    }

    if (!m_dbHdlr->addWorker(worker)) {
        return;
    }

    QMessageBox::information(this, tr("Confirm"), tr("A new worker is added."), tr("Ok"));
}

void MainWindow::_init_table_worker()
{
    ui->listView_worker->setModel(m_model_worker);
}

void MainWindow::_update_table_worker(QList<Worker> listValue)
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

bool MainWindow::_find_worker_idx(int* out_idx, int id)
{
    if (!out_idx) {
        return false;
    }

    for(int i = 0; i < m_workerList.count(); i++) {
        Worker worker = m_workerList.at(i);
        if (worker.idNum() == id) {
            *out_idx = i;
            return true;
        }
    }

    return false;
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
