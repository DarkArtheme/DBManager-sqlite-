#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, DBManager* db_manager_)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db_manager(db_manager_)
    , selected_table("")
    , field_should_change(false)
{
    ui->setupUi(this);
    ui->tablesList->setModel(db_manager->getTables());
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectTable_clicked(){
    this->update();
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

void MainWindow::on_addLine_clicked()
{
    if(selected_table.isEmpty()){
        QMessageBox::warning(this, "Внимание!", "Выберите таблицу!");
        return;
    }
    db_manager->insertLineInto(selected_table);
    this->update();
}

void MainWindow::update()
{
    field_should_change = false;
    ui->fieldTable->clear();
    selected_table = ui->tablesList->currentText();
    //qDebug() << selected_table;
    current_model = db_manager->printTable(selected_table);
    ui->tableView->setModel(current_model);
}

void MainWindow::on_delLine_clicked()
{
    if(selected_table.isEmpty()){
        QMessageBox::warning(this, "Внимание!", "Выберите таблицу!");
        return;
    }
    int col = ui->tableView->currentIndex().column();
    QModelIndex ind = ui->tableView->currentIndex();
    if (col != 0){
        QMessageBox::warning(this, "Внимание!", "Выберите поле с ID!");
        return;
    }
    db_manager->deleteLineFrom(selected_table, current_model->data(ind, Qt::DisplayRole).toInt());
    this->update();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    index_of_field = index;
    field_should_change = true;
    ui->fieldTable->setText(current_model->data(index, Qt::DisplayRole).toString());
}

void MainWindow::on_changeField_clicked()
{
    if(!field_should_change){
        QMessageBox::warning(this, "Внимание!", "Выберите ячейку таблицы!");
        return;
    }
    int row = index_of_field.row();
    int col = index_of_field.column();
    int ID = db_manager->getID(selected_table, row);
    db_manager->updateField(selected_table, col, ID, ui->fieldTable->text());
    this->update();
}
