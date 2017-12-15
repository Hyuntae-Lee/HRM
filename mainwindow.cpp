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
    m_listModel_hr = new QStringListModel;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_dbHdlr;
    delete m_listModel_hr;
    delete ui;
}

void MainWindow::on_pushButton_connectDB_clicked()
{
    m_dbHdlr->connectToDB(QDir::currentPath() + DB_FILE_PATH);
}

void MainWindow::on_pushButton_refreshHR_clicked()
{
    // 내용 불러옴
    QList<Worker> workerList;
    if (!m_dbHdlr->getWorkerList(workerList)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot load data from!!"), tr("Ok"));
        return;
    }

    // list 를 채움
    // - 아이템 구성
    QStringList itemList;
    foreach(Worker worker, workerList) {
        itemList.append(worker.name());
    }
    // - ui 적용
    m_listModel_hr->setStringList(itemList);
    ui->listView_hr->setModel(m_listModel_hr);
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
