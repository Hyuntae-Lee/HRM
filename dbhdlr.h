#ifndef DBHDLR_H
#define DBHDLR_H

#include <QObject>
#include <QSqlDatabase>
#include "worker.h"

class DBHdlr : public QObject
{
    Q_OBJECT
public:
    explicit DBHdlr(QObject *parent = 0);
    bool connectToDB(QString fileName);
    bool getWorkerList(QList<Worker>& list);
    bool addWorker(Worker worker);

signals:

public slots:

private:
    QSqlDatabase m_db;
};

#endif // DBHDLR_H
