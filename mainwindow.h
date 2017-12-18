#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"

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
    void on_pushButton_refreshHR_clicked();
    void on_pushButton_newHR_clicked();
    void on_listView_worker_clicked(const QModelIndex &index);

private:
    // worker
    void _init_table_worker();
    void _update_table_worker(QList<Worker> listValue);
    void _load_worker_list(QList<Worker> &listValue);
    bool _find_worker_idx(int* out_idx, int id);

private:
    Ui::MainWindow *ui;
    DBHdlr* m_dbHdlr;
    QStringListModel* m_model_worker;
    QList<Worker> m_workerList;
};

#endif // MAINWINDOW_H
