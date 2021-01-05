#pragma once
#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H

#include "dbmanager.h"
#include <QDialog>

namespace Ui {
class EntityCreator;
}

class EntityCreator : public QDialog
{
    Q_OBJECT

public:
    explicit EntityCreator(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~EntityCreator();
    QString getName() const { return name; }
signals:
    void nameIsEntered(QString new_name);
    void isClosed(bool should_show_columns);
private slots:
    void on_pushButton_clicked();

private:
    Ui::EntityCreator *ui;
    DBManager* db_manager;
    QString name;
};

#endif // ENTITYCREATOR_H
