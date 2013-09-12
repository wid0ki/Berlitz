#include "settings.h"
#include "ui_settings.h"
#include <QFile>
#include <QTextStream>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    QFile file("settings");
    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        QStringList settings = in.readLine().split(" ");
        ui->comboBox->setCurrentText(settings.at(0));
        ui->hostName->setText(settings.at(1));
        ui->dbName->setText(settings.at(2));
        ui->userName->setText(settings.at(3));
        ui->passName->setText(settings.at(4));
        file.close();
    }
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(WriteSettings()));
}

void Settings::WriteSettings() {
    QStringList settings;
    settings.append(ui->comboBox->currentText());
    settings.append(ui->hostName->text());
    settings.append(ui->dbName->text());
    settings.append(ui->userName->text());
    settings.append(ui->passName->text());
    emit NewSettings(settings);
    deleteLater();
}

Settings::~Settings()
{
    delete ui;
}
