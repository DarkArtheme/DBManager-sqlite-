#include "columncreator.h"
#include "ui_columncreator.h"

ColumnCreator::ColumnCreator(QWidget *parent, DBManager* db_manager_) :
    QDialog(parent),
    ui(new Ui::ColumnCreator),
    db_manager(db_manager_),
    table_name("")
{
    ui->setupUi(this);
}

ColumnCreator::~ColumnCreator()
{
    emit isClosed(true);
    delete ui;
}

void ColumnCreator::on_pushButton_clicked()
{
    QString line_text = ui->lineEdit->text();
    QString column_name, column_type;
    QTextStream ss(&line_text);
    ss >> column_name >> column_type;
    if(!ss.atEnd()){
        QMessageBox::warning(this, "Ошибка!", "Данные некорректны, были введены лишние слова!");
        return;
    }
    bool res = true;
    QSqlQuery query(*db_manager->getDatabase());
    res = query.prepare("ALTER TABLE " + table_name + " ADD COLUMN " +
                        column_name + " " + column_type + ";");
    if(res){
        for(const auto& x : column_name){
            if(!((x >= '0' && x <= '9') || (x >='A' && x <= 'Z') || (x >= 'a' && x <= 'z') || x == '_')){
                res = false;
            }
        }
    }
    if(!res){
        QMessageBox::warning(this, "Ошибка!", "Данные некорректны!");
        return;
    }
    name = column_name;
    type = column_type;
    emit nameIsEntered(table_name, name, type);
    emit isClosed(true);
    this->close();
}
