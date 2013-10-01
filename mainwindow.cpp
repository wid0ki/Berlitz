#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "contract.h"
#include "settings.h"
#include "buycard.h"
#include "port.h"
#include "viewblock.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbs.insert("PostgreSQL","QPSQL");
    dbs.insert("MSSQL","QODBC");
    dbs.insert("MySQL","QMYSQL");
    buttonStyle = "";
    lineStyle = QString (
                "QLineEdit {"
                            "border-radius: 5px;"
                            "border: solid;"
                            "}");
    QSettings *settings = new QSettings("settings.conf",QSettings::NativeFormat);
    qDebug()<<settings->value("database").toString();
    connect(ui->settings, SIGNAL(triggered()), this, SLOT(OpenSettings()));
    connect(ui->exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->newClient, SIGNAL(triggered()),this, SLOT(ShowAddClient()));
    connect(ui->newContract, SIGNAL(triggered()), this, SLOT(ShowAddContract()));
    connect(ui->buyCard, SIGNAL(triggered()), this, SLOT(BuyCardClient()));
    connect(ui->showCards, SIGNAL(triggered()), this, SLOT(ShowCards()));
    connect(ui->showClients, SIGNAL(triggered()), this, SLOT(ShowClients()));
    connect(ui->showPays, SIGNAL(triggered()), this, SLOT(ShowPays()));
    connect(ui->showContract, SIGNAL(triggered()), this, SLOT(ShowContracts()));
    connect(ui->exportData, SIGNAL(triggered()), this, SLOT(Export()));
    connect(ui->importData, SIGNAL(triggered()), this, SLOT(Import()));
    BerlitzTabMake();
}

void MainWindow::Export() {
    Port *form = new Port;
    form->sdb = sdb;
    form->show();
}

void MainWindow::Import() {

}

void MainWindow::OpenSettings() {
    Settings * form = new Settings();
    form->show();
    connect(form, SIGNAL(NewSettings()), this, SLOT(BerlitzTabMake()));
}

void MainWindow::GetSettings() {
    QSettings *settings = new QSettings("settings.conf",QSettings::NativeFormat);
    sdb = QSqlDatabase::addDatabase(dbs.value(settings->value("database").toString()));
    sdb.setDatabaseName(settings->value("dbname").toString());
    sdb.setUserName(settings->value("username").toString());
    sdb.setHostName(settings->value("hostname").toString());
    sdb.setPassword(settings->value("password").toString());
    sdb.setPort(settings->value("port").toInt());
}

void MainWindow::BerlitzTabMake() {
    GetSettings();
    ui->bigNumber->setAlignment(Qt::AlignCenter);
    ui->historyNumber->setAlignment(Qt::AlignCenter);

    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning hey!";
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

    ui->historyNumber->setText("Уровень (по порядку)");
    connect(ui->addClient, SIGNAL (clicked()), this, SLOT(ShowAddClient()));
    connect(ui->addContract, SIGNAL (clicked()), this, SLOT(ShowAddContract()));
    connect(ui->buyCardBut, SIGNAL(clicked()), this, SLOT(BuyCardClient()));
}

void MainWindow::BuyCardClient() {
    BuyCard *form = new BuyCard;
    form->sdb = sdb;
    form->show();
}

void MainWindow::ShowViewBlock(int number) {
    ViewBlock *form = new ViewBlock;
    form->type = number;
    form->sdb = sdb;
    form->Form();
    form->show();
}

void MainWindow::ShowCards() {
    ShowViewBlock(1);
}

void MainWindow::ShowClients() {
    ShowViewBlock(2);
}

void MainWindow::ShowContracts() {
    ShowViewBlock(3);
}

void MainWindow::ShowPays() {
    ShowViewBlock(4);
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
