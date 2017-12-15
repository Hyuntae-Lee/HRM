#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class DBHdlr;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_connectDB_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_newWorker_clicked();

private:
    Ui::MainWindow *ui;
    DBHdlr* m_dbHdlr;
};

#endif // MAINWINDOW_H
