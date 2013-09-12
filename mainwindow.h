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

private slots:
    void BuyCard();
    void ShowCards();
    void ShowClients();
    void ShowContracts();
    void ShowPays();
    void ShowViewBlock(int);
    void ShowAddClient();
    void ShowAddContract();
    void BerlitzTabMake();
    void GetSettings();
    void OpenSettings();
    bool ConnectToDB(QStringList);
    void ChangeSettings(QStringList);
};

#endif // MAINWINDOW_H
