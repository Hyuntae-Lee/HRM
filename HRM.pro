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
    dialognewwork.cpp

HEADERS  += mainwindow.h \
    dbhdlr.h \
    worker.h \
    dialognewworker.h \
    company.h \
    work.h \
    dialognewcompany.h \
    dialognewwork.h

FORMS    += mainwindow.ui \
    dialognewworker.ui \
    dialognewcompany.ui \
    dialognewwork.ui
