#ifndef DBHDLR_H
#define DBHDLR_H

#include <QObject>

class DBHdlr : public QObject
{
    Q_OBJECT
public:
    explicit DBHdlr(QObject *parent = 0);
    bool connectToDB(QString fileName);

signals:

public slots:
};

#endif // DBHDLR_H
