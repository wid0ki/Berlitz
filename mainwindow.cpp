#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "contract.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttonStyle = "";

//    buttonStyle = "QPushButton {"
//                     "background-color: black;"
//                     "text-align: center;"
//                     "border-radius: 5px;"
//                     "color: white;"
//                     "border: solid;"
//                 "}"
//                 "QPushButton:hover {"
//                     "background-color: black;"
//                     "border-radius: 5px;"
//                     "background-repeat: repeat;"
//                     "color: white;"
//                 "}"
//                 "QPushButton:pressed {"
//                     "background-color: black;"
//                     "border-radius: 5px;"
//                     "background-repeat: repeat;"
//                     "color: white;"
//                 "}";
    lineStyle = QString (
                "QLineEdit {"
                            "border-radius: 5px;"
                            "border: solid;"
                            "}");

    GetSettings();
    BerlitzTabMake();
}

void MainWindow::GetSettings() {
    sdb = QSqlDatabase::addDatabase("QPSQL");
    sdb.setDatabaseName("berlitz");
    sdb.setUserName("postgres");
    sdb.setHostName("localhost");
    sdb.setPassword("123456");
}

void MainWindow::HideAll() {
    switch(0)
    {
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
    }
}

void MainWindow::BerlitzTabMake() {

    ui->bigNumber->setAlignment(Qt::AlignCenter);
    ui->historyNumber->setAlignment(Qt::AlignCenter);

    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
        ui->bigNumber->setText("0");
    }
    else {
        query->prepare("SELECT count(*) FROM client;");
        query->exec();
        query->next();
        ui->bigNumber->setText(query->record().value("count").toString());
    }
    if (!query->execBatch())
        qDebug() << query->lastError();
    ui->historyNumber->setText("количество активных клиентов");
    connect(ui->addClient, SIGNAL (clicked()), this, SLOT(ShowAddClient()));
    connect(ui->addContract, SIGNAL (clicked()), this, SLOT(ShowAddContract()));
}

void MainWindow::ShowAddClient() {
    Client *form = new Client;
    form->SetStyle(buttonStyle, lineStyle);
    form->sdb = sdb;
    form->show();
    connect(form, SIGNAL(destroyed(QObject*)), this, SLOT(BerlitzTabMake()));
}

void MainWindow::ShowAddContract() {
    Contract *form = new Contract;
    form->SetStyle(buttonStyle, lineStyle);
    form->sdb = sdb;
    form->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
