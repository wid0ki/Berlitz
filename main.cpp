#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QSettings>

//QT_BEGIN_NAMESPACE
//Q_IMPORT_PLUGIN(qsqlodbc)
//QT_END_NAMESPACE

int main(int argc, char *argv[])
{

    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");

    QApplication::setLibraryPaths(paths);
//    QApplication::addLibraryPath("C:\Qt\5.1.1\Src\qtbase\src\plugins");

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/logo.png"));

    MainWindow w;
    w.show();
    
    return a.exec();
}
