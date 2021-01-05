#pragma once
#ifndef FKCREATOR_H
#define FKCREATOR_H

#include "dbmanager.h"
#include <QDialog>

namespace Ui {
class FKCreator;
}

class FKCreator : public QDialog
{
    Q_OBJECT

public:
    explicit FKCreator(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~FKCreator();
    void setFKTable(QString value) { FK_table = value; }
signals:
    void tableWasChosen(QString FK_table_name, QString PK_table_name);
    void isClosed(bool should_show_columns);
private slots:
    void on_tableNames_clicked(const QModelIndex &index);

    void on_chooseTable_clicked();

private:
    Ui::FKCreator *ui;
    DBManager* db_manager;
    QString FK_table;
    QString chosenTable;
};

#endif // FKCREATOR_H
