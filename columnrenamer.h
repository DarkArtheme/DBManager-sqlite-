#pragma once
#ifndef COLUMNRENAMER_H
#define COLUMNRENAMER_H

#include "dbmanager.h"
#include <QDialog>


namespace Ui {
class ColumnRenamer;
}

class ColumnRenamer : public QDialog
{
    Q_OBJECT

public:
    explicit ColumnRenamer(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~ColumnRenamer();
    QString getNewName() const { return new_name; }
    void setTableName(QString value) { table_name = value; }
    void setOldName(QString value) { old_name = value; }
signals:
    void nameIsEntered(QString table_name_, QString old_name_, QString new_name_);
    void isClosed(bool should_show_columns);
    void changeChosenColumn(QString new_name_);
private slots:
    void on_pushButton_clicked();

private:
    Ui::ColumnRenamer *ui;
    DBManager* db_manager;
    QString table_name;
    QString old_name;
    QString new_name;
};

#endif // COLUMNRENAMER_H
