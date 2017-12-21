#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T16:30:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HRM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbhdlr.cpp \
    worker.cpp \
    dialognewworker.cpp \
    company.cpp \
    work.cpp \
    dialognewcompany.cpp \
    dialognewwork.cpp \
    dialogdatepicker.cpp \
    participanttablemodel.cpp \
    participanttablemodelitem.cpp \
    workhistorytablemodel.cpp \
    workhistorytablemodelitem.cpp

HEADERS  += mainwindow.h \
    dbhdlr.h \
    worker.h \
    dialognewworker.h \
    company.h \
    work.h \
    dialognewcompany.h \
    dialognewwork.h \
    dialogdatepicker.h \
    participanttablemodel.h \
    participanttablemodelitem.h \
    workhistorytablemodel.h \
    workhistorytablemodelitem.h

FORMS    += mainwindow.ui \
    dialognewworker.ui \
    dialognewcompany.ui \
    dialognewwork.ui \
    dialogdatepicker.ui
