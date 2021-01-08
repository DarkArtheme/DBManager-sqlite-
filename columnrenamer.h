#pragma once
#ifndef COLUMNRENAMER_H
#define COLUMNRENAMER_H

#include "dbmanager.h"
#include <QDialog>


namespace Ui {
class ColumnRenamer;
}

///@brief Окно переименования колонки.
class ColumnRenamer : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit ColumnRenamer(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~ColumnRenamer();

    ///@brief Получить название колонки.
    QString getNewName() const { return new_name; }

    ///@brief Установить название таблицы.
    void setTableName(QString value) { table_name = value; }

    ///@brief Установить старое название колонки.
    void setOldName(QString value) { old_name = value; }
signals:

    /**
     * @brief Сигнал ввода нового названия колонки.
     * @param table_name_ Имя таблицы.
     * @param old_name_ Старое имя колонки.
     * @param new_name_ Новое имя колонки.
     */
    void nameIsEntered(QString table_name_, QString old_name_, QString new_name_);

    /**
     * @brief Сигнал закрытия окна.
     * @param should_show_columns true, если нужно показывать колонки в списке.
     */
    void isClosed(bool should_show_columns);

    /**
     * @brief Сигнал изменения выбранной колонки.
     * @param new_name_ Название выбранной колонки.
     */
    void changeChosenColumn(QString new_name_);
private slots:

    ///@brief Нажатие на кнопку переименования.
    void on_pushButton_clicked();

private:
    Ui::ColumnRenamer *ui;
    DBManager* db_manager;
    QString table_name;
    QString old_name;
    QString new_name;
};

#endif // COLUMNRENAMER_H
