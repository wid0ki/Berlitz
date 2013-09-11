#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T23:56:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Berlitz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    contract.cpp \
    buycard.cpp

HEADERS  += mainwindow.h \
    client.h \
    contract.h \
    buycard.h

FORMS    += mainwindow.ui \
    client.ui \
    contract.ui \
    buycard.ui

OTHER_FILES += \
    bd.sql

RESOURCES += \
    res.qrc
