#include "viewblock.h"
#include "ui_viewblock.h"

ViewBlock::ViewBlock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewBlock)
{
    ui->setupUi(this);
}

void ViewBlock::Form() {
    ui->label->setAlignment(Qt::AlignCenter);
    switch(type) {
        case 1:
            this->setWindowTitle("Просмотр активных карт");
            ui->label->setText("Активные карты");
            ui->pushButton->setText("Купить карту");
            break;
        case 2:
            this->setWindowTitle("Просмотр клиентов");
            ui->label->setText("Клиенты");
            ui->pushButton->setText("Добавить клиента");
            break;
        case 3:
            this->setWindowTitle("Просмотр контрактов");
            ui->label->setText("Архив контрактов");
            ui->pushButton->setText("Новый контракт");
            break;
        case 4:
            this->setWindowTitle("Просмотр платежей");
            ui->label->setText("Архив платежей");
            ui->pushButton->hide();
            break;
    }
}

ViewBlock::~ViewBlock()
{
    delete ui;
}
