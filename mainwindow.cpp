#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbhdlr.h"
#include <QDir>

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
