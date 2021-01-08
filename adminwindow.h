#pragma once
#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "dbmanager.h"
#include "entitycreator.h"
#include "columncreator.h"
#include "columnrenamer.h"
#include "fkcreator.h"
#include <QMainWindow>

namespace Ui {
class AdminWindow;
}

///@brief Окно администрирования БД.
class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit AdminWindow(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~AdminWindow();
signals:

    ///@brief Сигнал возврата к окну авторизации.
    void loginWindow();
private slots:

    ///@brief Возврат к окну авторизации.
    void on_relogin_triggered();

    ///@brief Выход из программы.
    void on_exit_triggered();

    ///@brief Двойное нажатие по таблице в списке.
    void on_tableNames_doubleClicked(const QModelIndex &index);

    ///@brief Добавление новой таблицы.
    void on_addTable_clicked();

    ///@brief Обновление страницы окна по нажатию кнопки.
    void on_update_triggered();

    ///@brief Одно нажатие по таблице в списке.
    void on_tableNames_clicked(const QModelIndex &index);

    ///@brief Удаление таблицы.
    void on_delTable_clicked();

    ///@brief Обновление страницы окна.
    void update(bool should_show_columns);

    ///@brief Добавление новой колонки в таблице.
    void on_addCol_clicked();

    ///@brief Одно нажатие по колонке в списке.
    void on_columnNames_clicked(const QModelIndex &index);

    ///@brief Удаление колонки в таблице.
    void on_delCol_clicked();

    ///@brief Изменить выбранную коллонку.
    void changeChosenColumn(QString new_name);

    ///@brief Переименование колонки.
    void on_renameCol_clicked();

    ///@brief Добавить внешний ключ.
    void on_makeFK_clicked();

private:
    Ui::AdminWindow *ui;
    DBManager *db_manager;
    EntityCreator* table_creator;
    ColumnCreator* column_creator;
    ColumnRenamer* column_renamer;
    FKCreator* fk_creator;
    QString chosenTable;
    QString chosenTable_double_clicked;
    QString chosenColumn;
    QStringListModel* empty_model;
};

#endif // ADMINWINDOW_H
