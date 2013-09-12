#ifndef VIEWBLOCK_H
#define VIEWBLOCK_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

namespace Ui {
class ViewBlock;
}

class ViewBlock : public QDialog
{
    Q_OBJECT
    
public:
    explicit ViewBlock(QWidget *parent = 0);
    int type;
    QSqlDatabase sdb;
    void Form();
    ~ViewBlock();
    
private:
    Ui::ViewBlock *ui;
};

#endif // VIEWBLOCK_H
