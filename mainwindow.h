#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMultiHash>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QString buttonStyle;
    QString lineStyle;
    QSqlDatabase sdb;
    QMultiHash<QString, QString> dbs;

private slots:
    void UpdateClientsNumber();
    void BuyCardClient();
    void ShowCards();
    void ShowClients();
    void ShowContracts();
    void ShowViewBlock(int);
    void ShowAddClient();
    void ShowAddContract();
    void BerlitzTabMake();
    void GetSettings();
    void OpenSettings();

signals:
    void UpdateCardInfo();
};

#endif // MAINWINDOW_H
