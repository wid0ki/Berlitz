#include "viewblock.h"
#include "ui_viewblock.h"
#include "buycard.h"
#include "client.h"
#include "contract.h"
#include <QTableWidgetItem>

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
    QSqlQuery * query = new QSqlQuery(sdb);
    switch(type) {
        case 1:
            this->setWindowTitle("Просмотр активных карт");
            ui->label->setText("Активные карты");
            ui->pushButton->setText("Купить карту");
            ui->resultTable->verticalHeader()->hide();
            ui->resultTable->setColumnCount(5);

            ui->resultTable->setHorizontalHeaderItem(0, new QTableWidgetItem ("Номер"));
            ui->resultTable->setColumnWidth(0, 50);
            ui->resultTable->setHorizontalHeaderItem(1, new QTableWidgetItem ("Тип карты"));
            ui->resultTable->setColumnWidth(1, 150);
            ui->resultTable->setHorizontalHeaderItem(2, new QTableWidgetItem ("Дата получения"));
            ui->resultTable->setColumnWidth(2, 100);
            ui->resultTable->setHorizontalHeaderItem(3, new QTableWidgetItem ("Дата окончания"));
            ui->resultTable->setColumnWidth(3, 110);
            ui->resultTable->setHorizontalHeaderItem(4, new QTableWidgetItem ("ФИО Клиента"));
            ui->resultTable->setColumnWidth(4, 231);

            query->prepare("select card.id as cardid, card.type, card.date_begin, card.date_end, (client.name, client.surname, client.middlename) AS fio "
                           "FROM card, client WHERE client.id=card.id_client;");
            query->exec();
            while(query->next()) {
                ui->resultTable->setRowCount(ui->resultTable->rowCount()+1);
                QLabel * textId = new QLabel;
                textId->setText(query->record().value("cardid").toString());
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,0,textId);
                QLabel * textType = new QLabel;
                textType->setText(query->record().value("type").toString());
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,1,textType);
                QLabel * textBegin = new QLabel;
                textBegin->setText(query->record().value("date_begin").toString());
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,2,textBegin);
                QLabel * textEnd = new QLabel;
                if (query->record().value("date_end").toDate().isNull())
                    textEnd->setText("активная карта");
                else
                    textEnd->setText(query->record().value("date_end").toString());
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,3,textEnd);
                QLabel * textClient = new QLabel;
                textClient->setText(query->record().value("fio").toString().remove("(").remove(")").replace(","," "));
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,4,textClient);
            }
            break;

        case 2:
            this->setWindowTitle("Просмотр клиентов");
            ui->label->setText("Клиенты");
            ui->pushButton->setText("Добавить клиента");
            ui->resultTable->setColumnCount(3);
            ui->resultTable->setHorizontalHeaderItem(0, new QTableWidgetItem ("ФИО Клиента"));
            ui->resultTable->setColumnWidth(0, 261);
            ui->resultTable->setHorizontalHeaderItem(1, new QTableWidgetItem ("Тип карты"));
            ui->resultTable->setColumnWidth(1, 150);
            ui->resultTable->setHorizontalHeaderItem(2, new QTableWidgetItem ("Накопленная сумма"));
            ui->resultTable->setColumnWidth(2, 200);
            query->prepare("SELECT (surname, name, middlename) as fio, SUM(sum), type FROM info GROUP BY fio, type;");
            query->exec();
            while(query->next()) {
                ui->resultTable->setRowCount(ui->resultTable->rowCount()+1);
                QLabel * textName = new QLabel;
                textName->setText(query->record().value("fio").toString().remove("(").remove(")").replace(","," "));
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,0,textName);
                QLabel * textType = new QLabel;
                textType->setText(query->record().value("type").toString());
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,1,textType);
                QLabel * textSum = new QLabel;
                textSum->setText(query->record().value("sum").toString());
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,2,textSum);
            }
            break;
        case 3:
            this->setWindowTitle("Просмотр контрактов");
            ui->label->setText("Архив контрактов");
            ui->pushButton->setText("Новый контракт");
            ui->resultTable->setColumnCount(3);
            ui->resultTable->setHorizontalHeaderItem(0, new QTableWidgetItem ("Контракт"));
            ui->resultTable->setColumnWidth(0, 170);
            ui->resultTable->setHorizontalHeaderItem(1, new QTableWidgetItem ("Сумма по контракту"));
            ui->resultTable->setColumnWidth(1, 200);
            ui->resultTable->setHorizontalHeaderItem(2, new QTableWidgetItem ("ФИО клиента"));
            ui->resultTable->setColumnWidth(2, 261);
            query->prepare("SELECT contract.date_operation, contract.sum, (client.name, client.surname, client.middlename) AS fio FROM client, contract WHERE contract.id=client.id;");
            query->exec();
            while(query->next()) {
                ui->resultTable->setRowCount(ui->resultTable->rowCount()+1);
                QLabel * textName = new QLabel;
                textName->setText(query->record().value("date_operation").toString().remove("(").remove(")").replace(","," "));
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,0,textName);
                QLabel * textType = new QLabel;
                textType->setText(query->record().value("sum").toString());
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,1,textType);
                QLabel * textSum = new QLabel;
                textSum->setText(query->record().value("fio").toString().remove("(").remove(")").replace(","," "));
                ui->resultTable->setCellWidget(ui->resultTable->rowCount()-1,2,textSum);
            }
            break;
    }
    ui->resultTable->show();
}

ViewBlock::~ViewBlock()
{
    delete ui;
}

