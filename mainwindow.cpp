#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "contract.h"
#include "settings.h"
#include "viewblock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttonStyle = "";
    lineStyle = QString (
                "QLineEdit {"
                            "border-radius: 5px;"
                            "border: solid;"
                            "}");
    connect(ui->settings, SIGNAL(triggered()), this, SLOT(OpenSettings()));
    connect(ui->exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->newClient, SIGNAL(triggered()),this, SLOT(ShowAddClient()));
    connect(ui->newContract, SIGNAL(triggered()), this, SLOT(ShowAddContract()));
    connect(ui->buyCard, SIGNAL(triggered()), this, SLOT(BuyCard()));
    connect(ui->showCards, SIGNAL(triggered()), this, SLOT(ShowCards()));
    connect(ui->showClients, SIGNAL(triggered()), this, SLOT(ShowClients()));
    connect(ui->showPays, SIGNAL(triggered()), this, SLOT(ShowPays()));
    connect(ui->showContract, SIGNAL(triggered()), this, SLOT(ShowContracts()));
    BerlitzTabMake();
}

void MainWindow::OpenSettings() {
    Settings *form = new Settings;
    form->show();
    connect(form, SIGNAL(NewSettings(QStringList)), this, SLOT(ChangeSettings(QStringList)));
}

void MainWindow::GetSettings() {
    QFile file("settings");
    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        QStringList settings = in.readLine().split(" ");
        file.close();
        if (!ConnectToDB(settings))
            BerlitzTabMake();
    }
    else
        OpenSettings();
}

bool MainWindow::ConnectToDB(QStringList settings) {
    if (settings.at(0) == "PostgreSQL")
        sdb = QSqlDatabase::addDatabase("QPSQL");
        else
        if (settings.at(0) == "MSSQL")
            sdb = QSqlDatabase::addDatabase("QODBC");
        else
            sdb = QSqlDatabase::addDatabase("QMYSQL");
    sdb.setDatabaseName(settings.at(2));
    sdb.setUserName(settings.at(3));
    sdb.setHostName(settings.at(1));
    sdb.setPassword(settings.at(4));
    return sdb.open();
}

void MainWindow::ChangeSettings(QStringList settings) {
    ConnectToDB(settings);
    QFile file("settings");
    QTextStream out(&file);
    out.setCodec("UTF-8");;

    if (!file.open(QIODevice::WriteOnly))
        qDebug()<<"Error with reading settings file";

    for (int i=0; i<settings.length(); i++)
        out << settings.at(i) << " ";
    file.close();
    GetSettings();
    BerlitzTabMake();
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
}

void MainWindow::BuyCard() {

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
