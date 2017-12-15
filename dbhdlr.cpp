#include "dbhdlr.h"
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

const QString DRIVER("QSQLITE");

DBHdlr::DBHdlr(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase(DRIVER);
}

bool DBHdlr::connectToDB(QString fileName)
{
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) {
        return false;
    }

    m_db.setDatabaseName(fileName);
    if(!m_db.open()) {
        qWarning() << "Cannot open database!!";
        return false;
    }

    return true;
}

bool DBHdlr::getWorkerList(QList<Worker>& list)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("SELECT name, id_num, age FROM HR");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getWorkerList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        QString name = query.value("name").toString();
        int id_num = query.value("id_num").toInt();
        int age = query.value("age").toInt();

        Worker worker;
        worker.setName(name);
        worker.setIdNum(id_num);
        worker.setAge(age);

        list.append(worker);
    }

    return true;
}

bool DBHdlr::addWorker(Worker worker)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("INSERT INTO HR(name, id_num, age) VALUES('%1', %2, %3)")
            .arg(worker.name()).arg(worker.idNum()).arg(worker.age());

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addWorker - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}
