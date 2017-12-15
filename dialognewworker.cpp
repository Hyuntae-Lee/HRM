#include "dialognewworker.h"
#include "ui_dialognewworker.h"

DialogNewWorker::DialogNewWorker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewWorker)
{
    ui->setupUi(this);
}

DialogNewWorker::~DialogNewWorker()
{
    delete ui;
}

bool DialogNewWorker::getWorkInfo(Worker* worker)
{
    if (!worker) {
        return false;
    }

    QString name = ui->lineEdit_name->text();
    QString idStr = ui->lineEdit_id->text();
    QString jobListStr = ui->lineEdit_job->text();
    QString age = ui->lineEdit_age->text();

    worker->setName(name);
    worker->setIdNum(idStr.toInt());
    worker->setAge(age.toInt());

    return true;
}
