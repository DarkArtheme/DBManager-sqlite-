#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent, DBManager* db_manager_) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow),
    db_manager(db_manager_)
{
    ui->setupUi(this);
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
