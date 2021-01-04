#include "columnrenamer.h"
#include "ui_columnrenamer.h"

ColumnRenamer::ColumnRenamer(QWidget *parent, DBManager* db_manager_) :
    QDialog(parent),
    ui(new Ui::ColumnRenamer),
    db_manager(db_manager_)
{
    ui->setupUi(this);
}

ColumnRenamer::~ColumnRenamer()
{
    emit isClosed(true);
    delete ui;
}

void ColumnRenamer::on_pushButton_clicked()
{
    QString col_name = ui->lineEdit->text();
    QSqlQuery query(*db_manager->getDatabase());
    bool res = query.prepare("ALTER TABLE " + table_name + " RENAME COLUMN " +
                        old_name + " TO " + col_name + ";");
    if(res){
        for(const auto& x : col_name){
            if(!((x >= '0' && x <= '9') || (x >='A' && x <= 'Z') || (x >= 'a' && x <= 'z') || x == '_')){
                res = false;
            }
        }
    }
    if(!res){
        QMessageBox::warning(this, "Ошибка!", "Данные некорректны!");
        return;
    }
    new_name = col_name;
    emit nameIsEntered(table_name, old_name, new_name);
    emit isClosed(true);
    emit changeChosenColumn(new_name);
    this->close();
}
