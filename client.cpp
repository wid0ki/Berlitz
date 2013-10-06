#include "client.h"
#include "ui_client.h"
#include <QDebug>

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this); 
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(AddClient()));
}

void Client::AddClient() {
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
        query->prepare("INSERT INTO client (surname, name, middlename) VALUES (:surname,:name,:middlename);");
        query->bindValue(":surname",ui->surname->text());
        query->bindValue(":name", ui->name->text());
        query->bindValue(":middlename", ui->middlename->text());
        if (query->exec())
            this->deleteLater();
        else {
            ui->middlename->clear();
            ui->surname->clear();
            ui->name->clear();
        }
    }
    if (!query->execBatch())
        qDebug() << query->lastError();
    this->deleteLater();
}

Client::~Client()
{
    emit NewClient();
    delete ui;
}
