#include "viewblock.h"
#include "ui_viewblock.h"
#include "buycard.h"
#include "client.h"
#include "contract.h"

ViewBlock::ViewBlock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewBlock)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Connection()));
}

void ViewBlock::Connection() {
    if (ui->pushButton->text() == "Купить карту") {
        BuyCard *form = new BuyCard;
        form->sdb = sdb;
        form->show();
    }
    if (ui->pushButton->text() == "Новый контракт") {
        Contract *form = new Contract;
        form->sdb = sdb;
        form->show();
    }
    if (ui->pushButton->text() == "Добавить клиента") {
        Client *form = new Client;
        form->sdb = sdb;
        form->show();
    }
}

void ViewBlock::Form() {
    ui->label->setAlignment(Qt::AlignCenter);
    ui->resultTable->setStyleSheet("QTableWidget {"
                                   "background-color: rgba(0, 0, 0, 0%);"
                                   "alternate-background-color: rgba(0, 0, 0, 0%);"
                                   "border: none;"
                                   "}"
                                   );
    ui->resultTable->show();
    ui->resultTable->horizontalHeader()->hide();
    QStringList headers;
    QSqlQuery * query = new QSqlQuery(sdb);
    int rows = 0;
    switch(type) {
    case 1:
            this->setWindowTitle("Просмотр активных карт");
            ui->label->setText("Активные карты");
            ui->pushButton->setText("Купить карту");
            headers.append("Номер");
            headers.append("Тип карты");
            headers.append("Дата начала");
            headers.append("Дата окончания");
            headers.append("ФИО Клиента");
            ui->resultTable->setHorizontalHeaderLabels(headers);
            ui->resultTable->setColumnCount(5);
            query->prepare("SELECT COUNT(card.id), card.id, card.type, card.date_begin, card.date_end, client.name, client.surname,"
                           "client.middlename FROM card, client WHERE client.id=card.id_client;");
            query->exec();
            rows = query->record().value("count").toInt();
            ui->resultTable->setRowCount(rows);
            for (int i=0; i<rows; i++) {
                QLabel * textId = new QLabel;
                textId->setText(query->record().value("id").toString());
                ui->resultTable->setCellWidget(i,0,textId);
                QLabel * textType = new QLabel;
                textType->setText(query->record().value("type").toString());
                ui->resultTable->setCellWidget(i,1,textType);
                QLabel * textBegin = new QLabel;
                textBegin->setText(query->record().value("date_begin").toString());
                ui->resultTable->setCellWidget(i,2,textBegin);
                QLabel * textEnd = new QLabel;
                textEnd->setText(query->record().value("date_end").toString());
                ui->resultTable->setCellWidget(i,3,textId);
                QLabel * textClient = new QLabel;
                textClient->setText(query->record().value("surname").toString()+" "+query->record().value("name").toString()+" "+query->record().value("middlename").toString());
                ui->resultTable->setCellWidget(i,0,textClient);
            }
            break;
        case 2:
            this->setWindowTitle("Просмотр клиентов");
            ui->label->setText("Клиенты");
            ui->pushButton->setText("Добавить клиента");
            headers.append("ФИО Клиента");
            headers.append("Тип карты");
            headers.append("Накопленная сумма");
            headers.append("ФИО Клиента");
            ui->resultTable->setHorizontalHeaderLabels(headers);
            ui->resultTable->setColumnCount(4);
            query->prepare("SELECT COUNT(id) FROM сlient;");
            query->exec();
            ui->resultTable->setRowCount(query->record().value("count").toInt());
            break;
        case 3:
            this->setWindowTitle("Просмотр контрактов");
            ui->label->setText("Архив контрактов");
            ui->pushButton->setText("Новый контракт");
            headers.append("Контракт");
            headers.append("Сумма по контракту");
            headers.append("ФИО Клиента");
            ui->resultTable->setHorizontalHeaderLabels(headers);
            ui->resultTable->setColumnCount(3);
            query->prepare("SELECT COUNT(id) FROM contract;");
            query->exec();
            ui->resultTable->setRowCount(query->record().value("count").toInt());
            break;
        case 4:
            this->setWindowTitle("Просмотр платежей");
            ui->label->setText("Архив платежей");
            ui->pushButton->hide();
            headers.append("Размер платежа");
            headers.append("Контракт");
            headers.append("ФИО Клиента");
            ui->resultTable->setHorizontalHeaderLabels(headers);
            ui->resultTable->setColumnCount(3);
            query->prepare("SELECT COUNT(id) FROM operation;");
            query->exec();
            ui->resultTable->setRowCount(query->record().value("count").toInt());
            break;
    }
}

ViewBlock::~ViewBlock()
{
    delete ui;
}
