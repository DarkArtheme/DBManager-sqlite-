#include "fkcreator.h"
#include "ui_fkcreator.h"

FKCreator::FKCreator(QWidget *parent, DBManager* db_manager_) :
    QDialog(parent),
    ui(new Ui::FKCreator),
    db_manager(db_manager_),
    chosenTable("")
{
    ui->setupUi(this);
    ui->tableNames->setModel(db_manager->getTables());
    ui->tableNames->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

FKCreator::~FKCreator()
{
    delete ui;
}

void FKCreator::on_tableNames_clicked(const QModelIndex &index)
{
    chosenTable = ui->tableNames->model()->data(index).toString();
}

void FKCreator::on_chooseTable_clicked()
{
    if(chosenTable == "")
        return;
    emit tableWasChosen(FK_table, chosenTable);
    emit isClosed(true);
    this->close();
}
