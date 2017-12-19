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

    QString queryStr = QString("SELECT id, name, major, picture_path, address, phone_num, bank_account FROM Worker");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getWorkerList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id_num = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString picturePath = query.value("picture_path").toString();
        QString address = query.value("address").toString();
        QString phoneNum = query.value("phone_num").toString();
        QString bankAccount = query.value("bank_account").toString();
        QStringList majorList = query.value("major").toString().split(",");

        Worker worker;
        worker.setIdNum(id_num);
        worker.setName(name);
        worker.setPicturePath(picturePath);
        worker.setAddress(address);
        worker.setPhoneNum(phoneNum);
        worker.setBankAccount(bankAccount);
        foreach(QString major, majorList) {
            worker.addMajor(major);
        }

        list.append(worker);
    }

    return true;
}

bool DBHdlr::addWorker(Worker worker)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("INSERT INTO Worker(id, name, major, picture_path, address, phone_num, bank_account) VALUES(%1,'%2','%3','%4','%5','%6','%7')")
            .arg(worker.idNum()).arg(worker.name()).arg(worker.majorStr())
            .arg(worker.picturePath()).arg(worker.address()).arg(worker.phoneNum())
            .arg(worker.bankAccount());

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addWorker - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::getCompanyList(QList<Company>& list)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("SELECT id, name, owner, address, phone_num, bank_account FROM Company");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getCompanyList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id_num = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString address = query.value("address").toString();
        QString phoneNum = query.value("phone_num").toString();
        QString bankAccount = query.value("bank_account").toString();
        QString owner = query.value("owner").toString();

        Company company;
        company.setIdNum(id_num);
        company.setName(name);
        company.setAddress(address);
        company.setPhoneNum(phoneNum);
        company.setBankAccount(bankAccount);
        company.setOwner(owner);

        list.append(company);
    }

    return true;
}

bool DBHdlr::addCompany(Company company)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("INSERT INTO Company(id, name, owner, address, phone_num, bank_account) VALUES(%1,'%2','%3','%4','%5','%6')")
            .arg(company.idNum()).arg(company.name()).arg(company.owner())
            .arg(company.address()).arg(company.phoneNum()).arg(company.bankAccount());

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addCompany - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::addWork(Work work)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("INSERT INTO Work(id, company_id, workers) VALUES(%1,'%2','%3')")
            .arg(work.idNum()).arg(work.companyId()).arg(work.owner())
            .arg(company.address()).arg(company.phoneNum()).arg(company.bankAccount());

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addCompany - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}
