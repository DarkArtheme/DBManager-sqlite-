#pragma once
#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H

#include "dbmanager.h"
#include <QDialog>

namespace Ui {
class EntityCreator;
}

///@brief Окно создания таблицы.
class EntityCreator : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit EntityCreator(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~EntityCreator();

    ///@brief Получить название таблицы.
    QString getName() const { return name; }
signals:
    /**
     * @brief Сигнал ввода названия таблицы.
     * @param new_name Название таблицы.
     */
    void nameIsEntered(QString new_name);

    /**
     * @brief Сигнал закрытия окна.
     * @param should_show_columns true, если нужно показывать колонки в списке.
     */
    void isClosed(bool should_show_columns);
private slots:

    ///@brief Нажатие на кнопку создания.
    void on_pushButton_clicked();

private:
    Ui::EntityCreator *ui;
    DBManager* db_manager;
    QString name;
};

#endif // ENTITYCREATOR_H
