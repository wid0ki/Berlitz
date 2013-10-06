#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T23:56:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Berlitz
TEMPLATE = app
CONFIG += static

#LIBS += libpqdll.lib qsqlodbc.dll
QTPLUGIN += qsqlodbc
LIBS += -lpq

SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    contract.cpp \
    buycard.cpp \
    settings.cpp \
    viewblock.cpp

HEADERS  += mainwindow.h \
    client.h \
    contract.h \
    buycard.h \
    settings.h \
    viewblock.h

FORMS    += mainwindow.ui \
    client.ui \
    contract.ui \
    buycard.ui \
    settings.ui \
    viewblock.ui

OTHER_FILES += \
    bd.sql \
    mssql_bd.sql

RESOURCES += \
    res.qrc
