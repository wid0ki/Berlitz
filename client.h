#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "mainwindow.h"

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT
    
public:
    explicit Client(QWidget *parent = 0);
    QSqlDatabase sdb;
    ~Client();
    
private:
    Ui::Client *ui;

private slots:
    void AddClient();

signals:
    void NewClient();
};

#endif // CLIENT_H
