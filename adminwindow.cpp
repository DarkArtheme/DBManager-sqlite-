#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QDebug>

AdminWindow::AdminWindow(QWidget *parent, DBManager* db_manager_) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow),
    db_manager(db_manager_),
    empty_model(new QStringListModel())
{
    chosenTable_double_clicked = "";
    ui->setupUi(this);




    ui->tableNames->setModel(db_manager->getTables());
    ui->tableNames->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->columnNames->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

AdminWindow::~AdminWindow()
{
    delete ui;
    ui = nullptr;
}

void AdminWindow::on_relogin_triggered()
{
    this->close();
    emit loginWindow();
}

void AdminWindow::on_exit_triggered()
{
    QApplication::quit();
}

void AdminWindow::on_tableNames_doubleClicked(const QModelIndex &index)
{
    chosenTable_double_clicked = ui->tableNames->model()->data(index).toString();
    ui->columnNames->setModel(db_manager->getColumns(chosenTable_double_clicked));
}

void AdminWindow::on_addTable_clicked()
{
    table_creator = new EntityCreator(this, db_manager);
    table_creator->setAttribute(Qt::WA_DeleteOnClose);
    connect(table_creator, &EntityCreator::nameIsEntered, db_manager, &DBManager::addTable);
    connect(table_creator, &EntityCreator::isClosed, this, &AdminWindow::update);
    table_creator->exec();
}



void AdminWindow::on_update_triggered()
{
    this->update(false);
}

void AdminWindow::on_tableNames_clicked(const QModelIndex &index)
{
    chosenTable = ui->tableNames->model()->data(index).toString();
}

void AdminWindow::on_delTable_clicked()
{
    if(chosenTable == "sqlite_sequence" || chosenTable == "TestTable"){
        QMessageBox::warning(this, "Ошибка!", "Данная таблица необходима для корректной работы базы данных и не может быть удалена!");
        return;
    }
    db_manager->deleteTable(chosenTable);
    chosenTable = "";
    this->update(false);
}

void AdminWindow::update(bool should_show_columns)
{
    if(ui == nullptr)
        return;
    ui->tableNames->setModel(db_manager->getTables());
    if(!should_show_columns){
        ui->columnNames->setModel(empty_model);
    } else{
        ui->columnNames->setModel(db_manager->getColumns(chosenTable_double_clicked));
    }
}

void AdminWindow::on_addCol_clicked()
{
    column_creator = new ColumnCreator(this, db_manager);
    column_creator->setAttribute(Qt::WA_DeleteOnClose);
    if(chosenTable_double_clicked == ""){
        return;
    }
    column_creator->setTableName(chosenTable_double_clicked);
    connect(column_creator, &ColumnCreator::nameIsEntered, db_manager, &DBManager::addColumn);
    connect(column_creator, &ColumnCreator::isClosed, this, &AdminWindow::update);
    column_creator->exec();
}

void AdminWindow::on_columnNames_clicked(const QModelIndex &index)
{
    QString chosenColumn_ = ui->columnNames->model()->data(index).toString();
    QTextStream ss(&chosenColumn_);
    ss >> chosenColumn;
}

void AdminWindow::on_delCol_clicked()
{
    //qDebug() << chosenColumn << " " << chosenTable_double_clicked;
    if(chosenColumn == "" || chosenTable_double_clicked == "sqlite_sequence"){
        return;
    }
    if(chosenColumn == "ID"){
        QMessageBox::warning(this, "Ошибка!", "ID не может быть удален!");
        return;
    }
    db_manager->deleteColumn(chosenTable_double_clicked, chosenColumn);
    chosenColumn = "";
    this->update(true);
}

void AdminWindow::changeChosenColumn(QString new_name)
{
    chosenColumn = new_name;
}

void AdminWindow::on_renameCol_clicked()
{
    column_renamer = new ColumnRenamer(this, db_manager);
    column_renamer->setAttribute(Qt::WA_DeleteOnClose);
    if(chosenColumn == "" || chosenTable_double_clicked == "sqlite_sequence"){
        return;
    }
    if(chosenColumn == "ID"){
        QMessageBox::warning(this, "Ошибка!", "ID не может быть переименован!");
        return;
    }
    column_renamer->setTableName(chosenTable_double_clicked);
    column_renamer->setOldName(chosenColumn);
    connect(column_renamer, &ColumnRenamer::nameIsEntered, db_manager, &DBManager::renameColumn);
    connect(column_renamer, &ColumnRenamer::changeChosenColumn, this, &AdminWindow::changeChosenColumn);
    connect(column_renamer, &ColumnRenamer::isClosed, this, &AdminWindow::update);
    column_renamer->exec();
}

void AdminWindow::on_makeFK_clicked()
{
    fk_creator = new FKCreator(this, db_manager);
    fk_creator->setAttribute(Qt::WA_DeleteOnClose);
    fk_creator->setFKTable(chosenTable_double_clicked);
    connect(fk_creator, &FKCreator::tableWasChosen, db_manager, &DBManager::makeForeignKey);
    connect(fk_creator, &FKCreator::isClosed, this, &AdminWindow::update);
    fk_creator->exec();
}
