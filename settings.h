#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT
    
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void WriteSettings();
    
private:
    Ui::Settings *ui;

signals:
    void NewSettings();
};

#endif // SETTINGS_H
