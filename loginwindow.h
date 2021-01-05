#pragma once
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "adminwindow.h"
#include "mainwindow.h"
#include "dbmanager.h"
#include <QWidget>
#include <QFileDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~LoginWindow();

private slots:

    void on_btnPath_clicked();

    void on_openBD_clicked();

    void on_createDB_clicked();

    void hide_login();

    void show_login();

    void on_btnAdmin_clicked();

    void on_btnOp_clicked();

    void on_btnLogin_clicked();

private:
    Ui::LoginWindow *ui;
    AdminWindow *adm_win;
    MainWindow *oper_win;
    DBManager* db_manager;
    bool path_was_chosen;
    bool admin_chosen;
};

#endif // LOGINWINDOW_H
