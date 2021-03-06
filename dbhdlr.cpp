#include "dbhdlr.h"
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

const QString DB_DATE_FORMAT = "yyyyMMdd";
const QString DB_SEP_WORKINFO = ",";
const QString DB_SEP_WORKINFO_PROP = ";";
const QString DB_SEP_WORKINFO_DATE = "-";

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

    QString queryStr = QString("SELECT id, name, rr_num, major, picture_path, address, phone_num, bank_account FROM Worker");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getWorkerList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id_num = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString rrNum = query.value("rr_num").toString();
        QString picturePath = query.value("picture_path").toString();
        QString address = query.value("address").toString();
        QString phoneNum = query.value("phone_num").toString();
        QString bankAccount = query.value("bank_account").toString();
        QStringList majorList = query.value("major").toString().split(",");

        Worker worker;
        worker.setIdNum(id_num);
        worker.setName(name);
        worker.setRrNum(rrNum);
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

    QString queryStr = QString("INSERT INTO Worker(rr_num, name, major, picture_path, address, phone_num, bank_account) VALUES('%1','%2','%3','%4','%5','%6','%7')")
            .arg(worker.rrNum()).arg(worker.name()).arg(worker.majorStr())
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

    QString queryStr = QString("SELECT id, business_license, name, owner, address, phone_num, bank_account FROM Company");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getCompanyList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id_num = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString blNum = query.value("business_license").toString();
        QString address = query.value("address").toString();
        QString phoneNum = query.value("phone_num").toString();
        QString bankAccount = query.value("bank_account").toString();
        QString owner = query.value("owner").toString();

        Company company;
        company.setIdNum(id_num);
        company.setName(name);
        company.setBlNum(blNum);
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

    QString queryStr = QString("INSERT INTO Company(business_license, name, owner, address, phone_num, bank_account) VALUES('%1','%2','%3','%4','%5','%6')")
            .arg(company.blNum()).arg(company.name()).arg(company.owner())
            .arg(company.address()).arg(company.phoneNum()).arg(company.bankAccount());

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addCompany - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::getWorkList(QList<Work>& list)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("SELECT id, company_blNum, workers, name FROM Work");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getWorkList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        // id
        int id_num = query.value("id").toInt();

        // name
        QString name = query.value("name").toString();

        // company
        QString companyBlNum = query.value("company_blNum").toString();

        // workers
        QList<WorkerInfo> workerInfoList;
        QString workerInfoStrTotal = query.value("workers").toString();
        QStringList workerInfoStrTotalList = workerInfoStrTotal.split(DB_SEP_WORKINFO);
        foreach (QString workerInfoStrRaw, workerInfoStrTotalList) {
            QStringList workerInfoStr = workerInfoStrRaw.split(DB_SEP_WORKINFO_PROP);

            QString workerRrNum = workerInfoStr[0];
            int workerPay = workerInfoStr[1].toInt();

            QStringList workerInfoDateStrList = workerInfoStr[2].split(DB_SEP_WORKINFO_DATE);
            QList<QDate> workerDateList;
            foreach (QString dateStr, workerInfoDateStrList) {
                QDate date = QDate::fromString(dateStr, DB_DATE_FORMAT);
                workerDateList.append(date);
            }

            WorkerInfo workerInfo;
            workerInfo.rrNum = workerRrNum;
            workerInfo.payPerDay = workerPay;
            workerInfo.dayList.append(workerDateList);

            workerInfoList.append(workerInfo);
        }

        Work work;
        work.setIdNum(id_num);
        work.setName(name);
        work.setCompanyBlNum(companyBlNum);
        work.setWorkerInfoList(workerInfoList);

        list.append(work);
    }

    return true;
}

bool DBHdlr::addWork(Work work)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("INSERT INTO Work(company_blNum, name, workers) VALUES('%1', '%2','%3')")
            .arg(work.companyBlNum()).arg(work.name()).arg(packWorkInfoStr(work));

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addWork - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

QString DBHdlr::packWorkInfoStr(Work& work)
{
    QList<WorkerInfo> workerInfoList = work.workerInfoList();

    QStringList strList;
    foreach(WorkerInfo workInfo, workerInfoList) {
        QStringList strWorker;
        // - rr number
        strWorker.append(QString("%1").arg(workInfo.rrNum));
        // - pay
        strWorker.append(QString("%1").arg(workInfo.payPerDay));
        // - days
        QStringList strDateList;
        foreach(QDate workingDate, workInfo.dayList) {
            strDateList.append(workingDate.toString(DB_DATE_FORMAT));
        }
        strWorker.append(strDateList.join(DB_SEP_WORKINFO_DATE));

        strList.append(strWorker.join(DB_SEP_WORKINFO_PROP));
    }

    return strList.join(DB_SEP_WORKINFO);
}
