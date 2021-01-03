#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QDebug>

AdminWindow::AdminWindow(QWidget *parent, DBManager* db_manager_) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow),
    db_manager(db_manager_),
    empty_model(new QStringListModel())
{
    ui->setupUi(this);
    table_creator = new EntityCreator(this, db_manager);
    ui->tableNames->setModel(db_manager->getTables());
    ui->tableNames->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->columnNames->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

AdminWindow::~AdminWindow()
{
    delete ui;
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
    ui->columnNames->setModel(db_manager->getColumns(ui->tableNames->model()->data(index).toString()));
}

void AdminWindow::on_addTable_clicked()
{
    connect(table_creator, &EntityCreator::nameIsEntered, db_manager, &DBManager::addTable);
    connect(table_creator, &EntityCreator::nameIsEntered, this, &AdminWindow::update);
    table_creator->exec();
}



void AdminWindow::on_update_triggered()
{
    this->update();
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
    this->update();
}

void AdminWindow::update()
{
    ui->tableNames->setModel(db_manager->getTables());

    ui->columnNames->setModel(empty_model);
}
