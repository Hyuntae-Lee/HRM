#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbhdlr.h"
#include "dialognewworker.h"
#include <QDir>
#include <QMessageBox>

#define DB_FILE_PATH "/data/main.db"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_dbHdlr = new DBHdlr();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_dbHdlr;
    delete ui;
}

void MainWindow::on_pushButton_connectDB_clicked()
{
    m_dbHdlr->connectToDB(QDir::currentPath() + DB_FILE_PATH);
}

void MainWindow::on_pushButton_refresh_clicked()
{
    // 내용 불러옴
    QList<Worker> workerList;
    if (!m_dbHdlr->getWorkerList(workerList)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot load data from!!"), tr("Ok"));
        return;
    }

    // list 를 채움
    // TODO
}

void MainWindow::on_pushButton_newWorker_clicked()
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
