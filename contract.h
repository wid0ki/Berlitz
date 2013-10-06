#ifndef CONTRACT_H
#define CONTRACT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
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

signals:
    void NewClient();
};

#endif // CONTRACT_H
