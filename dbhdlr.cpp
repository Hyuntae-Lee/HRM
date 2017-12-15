#include "dbhdlr.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DBHdlr::DBHdlr(QObject *parent) : QObject(parent)
{

}

bool DBHdlr::connectToDB(QString fileName)
{
    const QString DRIVER("QSQLITE");

    if(!QSqlDatabase::isDriverAvailable(DRIVER)) {
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName(fileName);

    if(!db.open()) {
        qWarning() << "ERROR: " << db.lastError();
        return false;
    }

    return true;
}
