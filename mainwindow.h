#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


///@brief Окно оперирования БД.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    MainWindow(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~MainWindow();
signals:

    ///@brief Сигнал возврата к окну авторизации.
    void loginWindow();
private slots:

    ///@brief Нажатие на кнопку выбора таблицы.
    void on_selectTable_clicked();

    ///@brief Возврат к окну авторизации.
    void on_relogin_triggered();

    ///@brief Выход из программы.
    void on_exit_triggered();

    ///@brief Нажатие на кнопку добавления строки.
    void on_addLine_clicked();

    ///@brief Обновление страницы окна.
    void update();

    ///@brief Нажатие на кнопку удаления строки.
    void on_delLine_clicked();

    ///@brief Выбор таблицы.
    void on_tableView_clicked(const QModelIndex &index);

    ///@brief Нажатие на кнопку изменения значения в ячейке.
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
