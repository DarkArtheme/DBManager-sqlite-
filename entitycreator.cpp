#include "entitycreator.h"
#include "ui_entitycreator.h"
#include <QMessageBox>
#include <QDebug>

EntityCreator::EntityCreator(QWidget *parent, DBManager* db_manager_) :
    QDialog(parent),
    ui(new Ui::EntityCreator),
    db_manager(db_manager_)
{
    this->setEnabled(true);
    ui->setupUi(this);
}

EntityCreator::~EntityCreator()
{
    emit isClosed(false);
    delete ui;
}

void EntityCreator::on_pushButton_clicked()
{
    QString table_name = ui->lineEdit->text();
    //qDebug() << table_name;
    QSqlQuery query(*db_manager->getDatabase());
    bool res = query.prepare("CREATE TABLE " + table_name + "('ID' integer PRIMARY KEY AUTOINCREMENT NOT NULL);");
    for(const auto& x : table_name){
        if(!((x >= '0' && x <= '9') || (x >='A' && x <= 'Z') || (x >= 'a' && x <= 'z') || x == '_')){
            res = false;
        }
    }
    if(!res){
        QMessageBox::warning(this, "Ошибка!", "Данные некорректны!");
        return;
    }
    name = table_name;
    emit nameIsEntered(table_name);
    emit isClosed(false);
    this->close();
}
