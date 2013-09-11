#include "buycard.h"
#include "ui_buycard.h"

BuyCard::BuyCard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyCard)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->buy, SIGNAL(clicked()), this, SLOT(Buy()));
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(GetCards()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(ChangePrice()));
}

void BuyCard::ChangePrice() {

}

void BuyCard::GetCards() {

}

void BuyCard::Buy() {
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
//TODO
    }
    if (!query->execBatch())
        qDebug() << query->lastError();
}

BuyCard::~BuyCard()
{
    delete ui;
}
