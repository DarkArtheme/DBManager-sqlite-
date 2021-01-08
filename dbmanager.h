#pragma once
#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql>
#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <algorithm>

///@brief Главный класс программы - обработчик запросов к базе данных.
class DBManager : public QObject{
    Q_OBJECT
public:
    /**
     * @brief Конструктор
     * @param parent Указатель на экземпляр родительского класса.
     */
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();
    /**
     * @brief Проверка логина и пароля.
     * @param admin_chosen Какая роль выбрана (true - администратор, false - оператор)
     * @param login Введенный пользователем логин.
     * @param password Введенный пользователем пароль.
     * @return Пустая строка, если вход успешен - иначе строка с ошибкой.
     */
    QString checkPassword(bool admin_chosen, QString login, QString password);

    /**
     * @brief Подключение к базе данных.
     * @param path Путь к файлу с базой данных.
     * @return true, если подключение успешно.
     */
    bool connectToDataBase(QString path);

    /**
     * @return Указатель на экземпляр класса, хранящий базу данных.
     */
    const QSqlDatabase* getDatabase() const { return &database; }

    /**
     * @param table_name Название таблицы.
     * @return Указатель на модель выбранной таблицы для последующего вывода на экран.
     */
    QSqlRelationalTableModel* printTable(QString table_name);

    /**
     * @return Указатель на модель строкового списка всех таблиц.
     */
    QStringListModel* getTables();

    /**
     * @return Указатель на модель строкового списка всех колонок данной таблицы.
     */
    QStringListModel* getColumns(QString table_name);

    /**
     * @param table_name Название таблицы.
     * @return Максимальное значение ID в таблице.
     */
    int getLastID(QString table_name);

    /**
     * @brief Вставка строки в выбранную таблицу.
     * @param table_name Название таблицы.
     * @return true, если транзакция успешна.
     */
    bool insertLineInto(QString table_name);

    /**
     * @brief Удаление строки из выбранной таблицы.
     * @param table_name Название таблицы.
     * @param id ID строки.
     * @return true, если транзакция успешна.
     */
    bool deleteLineFrom(QString table_name, int id);

    ///@brief Получение ID элемента в таблице по номеру строки.
    int getID(QString table_name, int row);

    ///@brief Получение названия колонки в таблице по номеру колонки.
    QString getColumnName(QString table_name, int col);

    /**
     * @brief Обновление ячейки в таблице.
     * @param table_name Название таблицы.
     * @param col Номер колонки.
     * @param ID ID элемента.
     * @param value Новое значение.
     * @return true, если транзакция успешна.
     */
    bool updateField(QString table_name, int col, int ID, QString value);
public slots:

    /**
     * @brief Добавление колонки.
     * @param table_name Название таблицы.
     * @param column_name Название колонки.
     * @param column_type Тип данных колонки.
     * @return true, если транзакция успешна.
     */
    bool addColumn(QString table_name, QString column_name, QString column_type);

    /**
     * @brief Удаление колонки.
     * @param table_name Название таблицы.
     * @param column_name Название колонки.
     * @return true, если транзакция успешна.
     */
    bool deleteColumn(QString table_name, QString column_name);

    /**
     * @brief Добавление таблицы.
     * @param table_name Название таблицы.
     * @return true, если транзакция успешна.
     */
    bool addTable(QString table_name);

    /**
     * @brief Удаление таблицы.
     * @param table_name Название таблицы.
     * @return true, если транзакция успешна.
     */
    bool deleteTable(QString table_name);

    /**
     * @brief Изменение названия колонки.
     * @param table_name Название таблицы.
     * @param old_name Старое название колонки.
     * @param new_name Новое название колонки.
     * @return true, если транзакция успешна.
     */
    bool renameColumn(QString table_name, QString old_name, QString new_name);

    /**
     * @brief Создание внешнего ключа.
     * @param FK_table_name Название таблицы, где будет создаваться внешний ключ.
     * @param PK_table_name Название таблицы, куда внешний ключ будет относиться.
     * @return true, если транзакция успешна.
     */
    bool makeForeignKey(QString FK_table_name, QString PK_table_name);
private:
    QSqlDatabase database;
    QSqlRelationalTableModel* model{nullptr};
    QStringListModel* table_names_model{nullptr};
    QStringListModel* column_names_model{nullptr};
    QStringList admin_logins;
    QStringList admin_passwords;
    QStringList operator_logins;
    QStringList operator_passwords;
    bool openDataBase(QString path);
    void closeDataBase();

};

#endif // DBMANAGER_H
