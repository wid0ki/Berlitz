#ifndef PORT_H
#define PORT_H

#include <QDialog>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDate>

namespace Ui {
class Port;
}

class Port : public QDialog
{
    Q_OBJECT
    
public:
    explicit Port(QWidget *parent = 0);
    QSqlDatabase sdb;
    ~Port();
    
private:
    Ui::Port *ui;

private slots:
    void GenerateReport();
    void Export();
};

#endif // PORT_H
