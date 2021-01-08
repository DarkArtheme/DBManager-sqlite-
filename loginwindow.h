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

///@brief Окно авторизации.
class LoginWindow : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit LoginWindow(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~LoginWindow();

private slots:

    ///@brief Нажатие на кнопку выбора пути.
    void on_btnPath_clicked();

    ///@brief Нажатие на кнопку открытия БД.
    void on_openBD_clicked();

    ///@brief Нажатие на кнопку создания новой БД.
    void on_createDB_clicked();

    ///@brief Спрятать поля авторизации.
    void hide_login();

    ///@brief Показать поля авторизации.
    void show_login();

    ///@brief Нажатие на кнопку выбора роли администратора.
    void on_btnAdmin_clicked();

    ///@brief Нажатие на кнопку выбора роли оператора.
    void on_btnOp_clicked();

    ///@brief Нажатие на кнопку входа.
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
