#ifndef DIALOGNEWWORKER_H
#define DIALOGNEWWORKER_H

#include <QDialog>
#include "worker.h"

namespace Ui {
class DialogNewWorker;
}

class DialogNewWorker : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewWorker(QWidget *parent = 0);
    ~DialogNewWorker();
    bool getWorkInfo(Worker* worker);

private:
    Ui::DialogNewWorker *ui;
};

#endif // DIALOGNEWWORKER_H
