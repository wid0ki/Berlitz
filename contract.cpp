#include "contract.h"
#include "ui_contract.h"
#include "client.h"
#include <QDebug>
#include <QDate>
#include <QMessageBox>

Contract::Contract(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contract)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->cardInfo->setAlignment(Qt::AlignRight);
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(AddContract()));
    connect(ui->buyCard, SIGNAL(clicked()), this, SLOT(ClientBuyCard()));
    connect(ui->newClient, SIGNAL(clicked()), this, SLOT(AddClient()));
    connect(ui->clientBox, SIGNAL(highlighted(int)), this, SLOT(LoadClients()));
    connect(ui->clientBox, SIGNAL(currentTextChanged(QString)), this, SLOT(ClientCard()));
}

void Contract::SetStyle(QString buttonStyle, QString lineStyle) {
    this->lineStyle = lineStyle;
    this->buttonStyle = buttonStyle;
    ui->buyCard->setStyleSheet(buttonStyle);
    ui->cancel->setStyleSheet(buttonStyle);
    ui->save->setStyleSheet(buttonStyle);
    ui->newClient->setStyleSheet(buttonStyle);
    ui->price->setStyleSheet(lineStyle);
}

void Contract::AddContract() {
    QString currentCard = "none";
    int lastid = -1;
    int contractid = 0;
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
        QStringList list = ui->clientBox->currentText().split(" ");
        query->prepare("SELECT id FROM client WHERE name=:name AND surname=:surname AND middlename=:middlename;");
        query->bindValue(":name", list.at(1));
        query->bindValue(":surname", list.at(0));
        query->bindValue(":middlename", list.at(2));
        query->exec();
        query->next();
        currentClient = query->record().value("id").toInt();
        query->prepare("SELECT id, type FROM card WHERE id_client=:id_client ORDER BY id DESC;");
        query->bindValue(":id_client",currentClient);
        query->exec();
        if (query->first()) {
            lastid = query->record().value("id").toInt();
            currentCard = query->record().value("type").toString();
            qDebug()<<lastid<<" "<<currentCard;
        }
        query->prepare("INSERT INTO contract (id_client, sum) VALUES (:id_client,:sum);");
        query->bindValue(":id_client",currentClient);
        query->bindValue(":sum",ui->price->text().toInt());
        query->exec();

        query->prepare("SELECT id FROM contract WHERE id_client=:id_client ORDER BY id DESC;");
        query->bindValue(":id_client",currentClient);
        query->exec();
        if (query->first())
            contractid = query->record().value("id").toInt();

        query->prepare("INSERT INTO operation (id_client, id_contract, id_card, date, sum) VALUES (:id_client, :id_contract, :id_card, :date, :sum);");
        query->bindValue(":id_client", currentClient);
        query->bindValue(":id_contract", contractid);
        query->bindValue(":id_card", lastid);
        query->bindValue(":sum", ui->price->text().toInt());
        query->bindValue(":date", QDate::currentDate().toString("dd.MM.yyyy"));
        if (query->exec())
            this->close();
        else {
            ui->price->clear();
        }
    }

    if (!query->execBatch())
        qDebug() << query->lastError();

    if ((SumPrices() >= 25000 || ContractNumber() >= 2) && currentCard == "none") {
        query->prepare("INSERT INTO card(type, date_begin, id_client) VALUES ('Berlitz Respect',:date,:id_client);");
        query->bindValue(":id_client",currentClient);
        query->bindValue(":date",QDate::currentDate().toString("dd.MM.yyyy"));
        query->exec();
        QMessageBox msgBox;
        msgBox.setText("Клиент "+ui->clientBox->currentText()+" получает карту Berlitz Respect.");
        msgBox.exec();
    }
    if (SumPrices() >= 50000 && (currentCard == "Berlitz Respect" || currentCard == "none")) {
        query->prepare("UPDATE card SET date_end=:date_end WHERE id=:id;");
        query->bindValue(":date_end", QDate::currentDate().toString("dd.MM.yyyy"));
        query->bindValue(":id",lastid);
        query->exec();
        query->prepare("INSERT INTO card(type, date_begin, id_client, id_parent) VALUES ('Berlitz Honour',:date,:id_client, :id_parent);");
        query->bindValue(":id_client",currentClient);
        query->bindValue(":date",QDate::currentDate().toString("dd.MM.yyyy"));
        query->bindValue(":id_parent",lastid);
        query->exec();
        QMessageBox msgBox;
        msgBox.setText("Клиент "+ui->clientBox->currentText()+" получает карту Berlitz Honour.");
        msgBox.exec();
    }
    if ((ui->price->text().toInt() >= 100000 || SumPrices() >= 100000) && (currentCard == "Berlitz Honour" || currentCard == "none" || currentCard == "Berlitz Respect")) {
        query->prepare("UPDATE card SET date_end=:date_end WHERE id=:id;");
        query->bindValue(":date_end", QDate::currentDate().toString("dd.MM.yyyy"));
        query->bindValue(":id",lastid);
        query->exec();
        query->prepare("INSERT INTO card(type, date_begin, id_client, id_parent) VALUES ('Berlitz Silver Member',:date,:id_client, :id_parent);");
        query->bindValue(":id_client",currentClient);
        query->bindValue(":date",QDate::currentDate().toString("dd.MM.yyyy"));
        query->bindValue(":id_parent",lastid);
        query->exec();
        QMessageBox msgBox;
        msgBox.setText("Клиент "+ui->clientBox->currentText()+" получает карту Berlitz Silver Member.");
        msgBox.exec();
    }
    if ((ui->price->text().toInt() >= 200000 || SumPrices() >= 200000) && (currentCard == "Berlitz Silver Member" || currentCard == "Berlitz Honour" || currentCard == "none" || currentCard == "Berlitz Respect")) {
        query->prepare("UPDATE card SET date_end=:date_end FROM card WHERE id=:id;");
        query->bindValue(":date_end", QDate::currentDate());
        query->bindValue(":id",lastid);
        query->exec();
        query->prepare("INSERT INTO card(type, date_begin, id_client, id_parent) VALUES ('Berlitz Gold Member',:date,:id_client, :id_parent);");
        query->bindValue(":id_client",currentClient);
        query->bindValue(":date",QDate::currentDate());
        query->bindValue(":id_parent",lastid);
        query->exec();
        QMessageBox msgBox;
        msgBox.setText("Клиент "+ui->clientBox->currentText()+" получает карту Berlitz Gold Member.");
        msgBox.exec();
    }
}

int Contract::ContractNumber() {
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
        query->prepare("SELECT COUNT(*) FROM contract WHERE id_client=:id_client;");
        query->bindValue(":id_client", currentClient);
        query->exec();
        query->next();
        return query->record().value("count").toInt();
    }
    return 0;
}

int Contract::SumPrices() {
    int sum = 0;
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
        query->prepare("SELECT sum::numeric FROM contract WHERE id_client=:id_client;");
        query->bindValue(":id_client", currentClient);
        query->exec();
        while (query->next()) {
            sum += query->record().value("sum").toInt();
        }
    }
    qDebug()<<"Sum: "<<sum<<"Current client: "<<currentClient;
    return sum;
}

void Contract::ClientBuyCard() {
    BuyCard *form = new BuyCard;
    form->sdb = sdb;
    form->show();
}

void Contract::AddClient() {
    Client *form = new Client;
    form->SetStyle(buttonStyle, lineStyle);
    form->sdb = sdb;
    form->show();

    LoadClients();
}

void Contract::LoadClients() {
    ui->clientBox->setDuplicatesEnabled(false);
    ui->clientBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
            query->exec("SELECT * FROM client WHERE name<>'' AND surname<>'' AND middlename<>'';");
            while (query->next())
            {
                if (-1 == ui->clientBox->findText(query->record().value("surname").toString()+" "+
                                                  query->record().value("name").toString()+" "+query->record().value("middlename").toString()))
                    ui->clientBox->addItem(query->record().value("surname").toString()+" "+query->record().value("name").toString()+" "+
                                          query->record().value("middlename").toString());
            }
    }
    sdb.close();
}

void Contract::ClientCard() {
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
        QStringList list = ui->clientBox->currentText().split(" ");
            query->prepare("SELECT card.type FROM client, card WHERE card.id_client=client.id AND client.name=:name AND client.surname=:surname AND client.middlename=:middlename ORDER BY card.id;");
            query->bindValue(":name", list.at(1));
            query->bindValue(":surname", list.at(0));
            query->bindValue(":middlename", list.at(2));
            query->exec();
            if (query->last())
                ui->cardInfo->setText(query->record().value("type").toString());
            else
                ui->cardInfo->setText("Нет сведений о картах");

    }
    sdb.close();
}

Contract::~Contract()
{
    delete ui;
}
