#include "mainwindow.h"
#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings settings;
    MainWindow w;
    w.show();
    
    return a.exec();
}
