#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"
#include "company.h"

namespace Ui {
class MainWindow;
}

class DBHdlr;
class QStringListModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_connectDB_clicked();
    void on_pushButton_newHR_clicked();
    void on_pushButton_refreshHR_clicked();
    void on_listView_worker_clicked(const QModelIndex &index);
    void on_pushButton_newCompany_clicked();
    void on_pushButton_refreshCompany_clicked();

private:
    // worker
    void _update_worker_list(QList<Worker> listValue);
    void _load_worker_list(QList<Worker> &listValue);
    void _update_company_list(QList<Company> listValue);
    void _load_company_list(QList<Company> &listValue);

private:
    Ui::MainWindow *ui;
    DBHdlr* m_dbHdlr;
    QStringListModel* m_model_worker;
    QStringListModel* m_model_company;
    QList<Worker> m_workerList;
    QList<Company> m_companyList;
};

#endif // MAINWINDOW_H
