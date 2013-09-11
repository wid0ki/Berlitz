#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

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
    void HideAll();

private slots:
    void ShowAddClient();
    void ShowAddContract();
    void BerlitzTabMake();
//    void SettingsTabMake();
    void GetSettings();
};

#endif // MAINWINDOW_H
