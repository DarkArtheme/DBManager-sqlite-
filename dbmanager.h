#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql>
#include <QObject>
#include <QDebug>
#include <QTextStream>

class DBManager : public QObject{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();
    void connectToDataBase();
    QSqlTableModel* printTable(QString table_name);
    void insertIntoTestTable(QString name);
    void deleteFromTestTable();
    QStringListModel* getTables();
    QStringListModel* getColumns(QString table_name);
private:
    QSqlDatabase database;
    QSqlRelationalTableModel* model{nullptr};
    QStringListModel* table_names_model{nullptr};
    QStringListModel* column_names_model{nullptr};
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();        // Открытие базы данных
    //bool restoreDataBase();     // Восстановление базы данных
    void closeDataBase();       // Закрытие базы данных
    //bool createTable();         // Создание базы таблицы в базе данных
};

#endif // DBMANAGER_H
