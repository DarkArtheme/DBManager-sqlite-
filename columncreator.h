#pragma once
#ifndef COLUMNCREATOR_H
#define COLUMNCREATOR_H

#include "dbmanager.h"
#include <QDialog>

namespace Ui {
class ColumnCreator;
}

///@brief Окно создания колонки
class ColumnCreator : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit ColumnCreator(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~ColumnCreator();

    ///@brief Получить название колонки.
    QString getName() const { return name; }

    ///@brief Получить тип данных колонки.
    QString getType() const { return type; }

    ///@brief Установить название таблицы.
    void setTableName(QString value) { table_name = value; }
signals:

    /**
     * @brief Сигнал ввода названия и типа данных колонки.
     * @param table_name_ Имя таблицы.
     * @param new_name Имя колонки.
     * @param new_type Тип данных таблицы.
     */
    void nameIsEntered(QString table_name_, QString new_name, QString new_type);

    /**
     * @brief Сигнал закрытия окна.
     * @param should_show_columns true, если нужно показывать колонки в списке.
     */
    void isClosed(bool should_show_columns);
private slots:

    ///@brief Нажатие на кнопку создания.
    void on_pushButton_clicked();

private:
    Ui::ColumnCreator *ui;
    DBManager* db_manager;
    QString table_name;
    QString name;
    QString type;
};

#endif // COLUMNCREATOR_H
