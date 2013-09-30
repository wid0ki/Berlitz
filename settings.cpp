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
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(WriteSettings()));
}

void Settings::WriteSettings() {
    QSettings *settings = new QSettings("settings.conf",QSettings::NativeFormat);
    settings->setValue("hostname", "localhost");
    settings->setValue("database", "PostgreSQL");
    settings->setValue("dbname","postgres");
    settings->setValue("username","postgres");
    settings->setValue("password","12345");
    settings->sync();
    deleteLater();
}

Settings::~Settings()
{
    delete ui;
}
