#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    QSettings *settings = new QSettings("settings.conf",QSettings::NativeFormat);
    ui->comboBox->setCurrentText(settings->value("database").toString());
    ui->hostName->setText(settings->value("hostname").toString());
    ui->dbName->setText(settings->value("dbname").toString());
    ui->userName->setText(settings->value("username").toString());
    ui->passName->setText(settings->value("password").toString());
    ui->port->setText(settings->value("port").toString());
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(WriteSettings()));
}

void Settings::WriteSettings() {
    QSettings *settings = new QSettings("settings.conf",QSettings::NativeFormat);
    settings->setValue("hostname", ui->hostName->text());
    settings->setValue("database", ui->comboBox->currentText());
    settings->setValue("dbname", ui->dbName->text());
    settings->setValue("username", ui->userName->text());
    settings->setValue("password", ui->passName->text());
    settings->setValue("port", ui->port->text());
    settings->sync();
    emit NewSettings();
    deleteLater();
}

Settings::~Settings()
{
    delete ui;
}
