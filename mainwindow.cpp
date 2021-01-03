#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, DBManager* db_manager_)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db_manager(db_manager_)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked(){
    ui->tableView->setModel(db_manager->printTable("TestTable"));
}

void MainWindow::on_relogin_triggered()
{
    this->close();
    emit loginWindow();
}

void MainWindow::on_exit_triggered()
{
    QApplication::quit();
}
