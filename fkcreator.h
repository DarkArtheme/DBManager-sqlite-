#pragma once
#ifndef FKCREATOR_H
#define FKCREATOR_H

#include "dbmanager.h"
#include <QDialog>

namespace Ui {
class FKCreator;
}


///@brief Окно создания внешнего ключа.
class FKCreator : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit FKCreator(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~FKCreator();

    ///@brief Установить название таблицы, где создается внешний ключ.
    void setFKTable(QString value) { FK_table = value; }
signals:

    /**
     * @brief Сигнал выбора таблицы.
     * @param FK_table_name Название таблицы, где будет создаваться внешний ключ.
     * @param PK_table_name Название таблицы, куда внешний ключ будет относиться.
     */
    void tableWasChosen(QString FK_table_name, QString PK_table_name);

    /**
     * @brief Сигнал закрытия окна.
     * @param should_show_columns true, если нужно показывать колонки в списке.
     */
    void isClosed(bool should_show_columns);
private slots:

    ///@brief Нажатие на таблицу в списке.
    void on_tableNames_clicked(const QModelIndex &index);

    ///@brief Нажатие на кнопку выбора.
    void on_chooseTable_clicked();

private:
    Ui::FKCreator *ui;
    DBManager* db_manager;
    QString FK_table;
    QString chosenTable;
};

#endif // FKCREATOR_H
