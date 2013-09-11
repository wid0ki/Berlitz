#ifndef CONTRACT_H
#define CONTRACT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDialog>
#include "buycard.h"

namespace Ui {
class Contract;
}

class Contract : public QDialog
{
    Q_OBJECT
    
public:
    explicit Contract(QWidget *parent = 0);
    QSqlDatabase sdb;
    void SetStyle(QString, QString);
    QString buttonStyle;
    QString lineStyle;
    int currentClient;
    ~Contract();
    
private:
    Ui::Contract *ui;

private slots:
    void AddContract();
    void ClientBuyCard();
    void AddClient();
    void LoadClients();
    void ClientCard();
    int SumPrices();
    int ContractNumber();
};

#endif // CONTRACT_H
