#ifndef BUYCARD_H
#define BUYCARD_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QDate>

namespace Ui {
class BuyCard;
}

class BuyCard : public QDialog
{
    Q_OBJECT
    
public:
    explicit BuyCard(QWidget *parent = 0);
    QSqlDatabase sdb;
    int currentClient;
    int currentCard;
    ~BuyCard();
    
private:
    Ui::BuyCard *ui;

private slots:
    void Buy();
    void GetCards();
    void ChangePrice();
    void GetClients();
};

#endif // BUYCARD_H
