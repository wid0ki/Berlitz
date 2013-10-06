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
    connect(ui->client, SIGNAL(highlighted(QString)), this, SLOT(GetClients()));
    connect(ui->client, SIGNAL(currentIndexChanged(QString)), this, SLOT(GetCards()));
    connect(ui->card, SIGNAL(currentIndexChanged(QString)), this, SLOT(ChangePrice()));
}

void BuyCard::GetClients() {
    ui->client->setDuplicatesEnabled(false);
    ui->client->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
            query->exec("SELECT * FROM client WHERE name<>'' AND surname<>'' AND middlename<>'';");
            while (query->next())
            {
                if (-1 == ui->client->findText(query->record().value("surname").toString()+" "+
                                                  query->record().value("name").toString()+" "+query->record().value("middlename").toString()))
                    ui->client->addItem(query->record().value("surname").toString()+" "+query->record().value("name").toString()+" "+
                                          query->record().value("middlename").toString());
            }
    }
    sdb.close();
}

void BuyCard::ChangePrice() {
    if (ui->card->currentText() == "Berlitz Respect")
        ui->price->setText("25000");
    else if (ui->card->currentText() == "Berlitz Honour")
        ui->price->setText("50000");
    else if (ui->card->currentText() == "Berlitz Silver Member")
        ui->price->setText("100000");
    else if (ui->card->currentText() == "Berlitz Gold Member")
        ui->price->setText("200000");
    else
        ui->price->setText("стоимость не выбрана");
}

void BuyCard::GetCards() {
    ui->card->clear();
    QStringList cardTypes;
    cardTypes.append("Berlitz Respect");
    cardTypes.append("Berlitz Honour");
    cardTypes.append("Berlitz Silver Member");
    cardTypes.append("Berlitz Gold Member");
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
        QStringList list = ui->client->currentText().split(" ");
        query->prepare("SELECT card.type, client.id, card.id FROM client, card WHERE card.id_client=client.id AND client.name=:name AND client.surname=:surname AND client.middlename=:middlename ORDER BY card.id;");
        query->bindValue(":name", list.at(1));
        query->bindValue(":surname", list.at(0));
        query->bindValue(":middlename", list.at(2));
        query->exec();
        if (query->last()) {
            currentClient = query->record().value("client.id").toInt();
            currentCard = query->record().value("card.id").toInt();
            for (int i=cardTypes.indexOf(query->record().value("type").toString()); i<cardTypes.length(); i++)
                ui->card->addItem(cardTypes.at(i));
        }
        else
            ui->card->addItems(cardTypes);

    }
    sdb.close();
}

void BuyCard::Buy() {
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
        QStringList list = ui->client->currentText().split(" ");
        query->prepare("SELECT id FROM client WHERE client.name=:name AND client.surname=:surname AND client.middlename=:middlename;");
        query->bindValue(":name", list.at(1));
        query->bindValue(":surname", list.at(0));
        query->bindValue(":middlename", list.at(2));
        query->exec();
        query->next();
        currentClient = query->record().value("id").toInt();
        qDebug()<<currentClient;

        query->prepare("SELECT id FROM card WHERE id_client=:id_client ORDER BY id;");
        query->bindValue("id_client",currentClient);
        query->exec();
        query->last();
        currentCard = query->record().value("id").toInt();
        qDebug()<<currentCard;

        query->prepare("UPDATE card SET date_end=':date_end' WHERE id=:id;");
        query->bindValue(":date_end", QDate::currentDate().toString("dd.MM.yyyy"));
        query->bindValue(":id", currentCard);
        query->exec();

        query->prepare("INSERT INTO card(type, date_begin,id_client) VALUES (:type, :date_begin, :id_client);");
        query->bindValue(":type",ui->card->currentText());
        query->bindValue(":date_begin", QDate::currentDate().toString("dd.MM.yyyy"));
        query->bindValue(":id_client", currentClient);
        query->exec();

        emit ClientBuyCard();
    }
    if (!query->execBatch())
        qDebug() << query->lastError();
    this->deleteLater();
}

BuyCard::~BuyCard()
{
    delete ui;
}
