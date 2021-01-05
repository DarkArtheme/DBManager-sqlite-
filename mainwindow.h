#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~MainWindow();
signals:
    void loginWindow();
private slots:
    void on_selectTable_clicked();

    void on_relogin_triggered();

    void on_exit_triggered();

    void on_addLine_clicked();

    void update();

    void on_delLine_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_changeField_clicked();

private:
    Ui::MainWindow *ui;
    DBManager* db_manager;
    QString selected_table;
    QSqlRelationalTableModel* current_model;
    bool field_should_change;
    QModelIndex index_of_field;
};
#endif // MAINWINDOW_H
