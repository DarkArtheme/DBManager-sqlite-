#pragma once
#ifndef COLUMNCREATOR_H
#define COLUMNCREATOR_H

#include "dbmanager.h"
#include <QDialog>

namespace Ui {
class ColumnCreator;
}

class ColumnCreator : public QDialog
{
    Q_OBJECT

public:
    explicit ColumnCreator(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~ColumnCreator();
    QString getName() const { return name; }
    QString getType() const { return type; }
    void setTableName(QString value) { table_name = value; }
signals:
    void nameIsEntered(QString table_name_, QString new_name, QString new_type);
    void isClosed(bool should_show_columns);
private slots:
    void on_pushButton_clicked();

private:
    Ui::ColumnCreator *ui;
    DBManager* db_manager;
    QString table_name;
    QString name;
    QString type;
};

#endif // COLUMNCREATOR_H
