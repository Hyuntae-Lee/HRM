#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    DBHdlr* m_dbHdlr;
    QStringListModel* m_listModel_hr;
};

#endif // MAINWINDOW_H
