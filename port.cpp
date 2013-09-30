#include "port.h"
#include "ui_port.h"

Port::Port(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Port)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(ui->generate, SIGNAL(clicked()), this, SLOT(GenerateReport()));
    connect(ui->port, SIGNAL(clicked()), this, SLOT(Export()));
}

void Port::GenerateReport() {

}

void Port::Export() {
    QStringList forExport;
    if (ui->cart->isChecked()) forExport.append("cart");
    if (ui->client->isChecked()) forExport.append("client");
    if (ui->contact->isChecked()) forExport.append("contract");
    if (ui->payment->isChecked()) forExport.append("operation");
    QSqlQuery * query = new QSqlQuery(sdb);
    if (!sdb.open()) {
        qDebug()<<"Something wrong with db openning!";
    }
    else {
        this->hide();
        QString fileName = QFileDialog::getSaveFileName(this, tr("Экспорт данных"), "DataExport"+QDate::currentDate().toString("dd.MM.yyyy"),
            tr("Text Files (*.csv)"));
            if (fileName != "") {
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly)) {
                    QMessageBox msgBox;
                    msgBox.setText("Выбран некорректный файл");
                    msgBox.exec();
                    this->show();
                } else {
                    qDebug()<<"im here";
                    QTextStream stream(&file);


                    for (int i=0; i < forExport.length(); i++) {
                        query->prepare("SELECT * FROM :dbname;");
                        query->bindValue(":dbname",forExport.at(i));
                        query->exec();
                        while (query->next()) {
                            qDebug()<<query->record().value("id").toString();
//                            stream << query->record().value("id").toString();
                        }

                    }
                    file.close();
                }
            }
    }
    sdb.close();
}

Port::~Port()
{
    delete ui;
}
