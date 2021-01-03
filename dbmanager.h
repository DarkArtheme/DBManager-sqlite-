#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql>
#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

class DBManager : public QObject{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();
    void connectToDataBase();
    const QSqlDatabase* getDatabase() const { return &database; }
    QSqlTableModel* printTable(QString table_name);
    void insertIntoTestTable(QString name);
    void deleteFromTestTable();
    QStringListModel* getTables();
    QStringListModel* getColumns(QString table_name);
public slots:
    bool addColumn(QString table_name, QString column_name, QString column_type);
    bool deleteColumn(QString table_name, QString column_name);
    bool addTable(QString table_name);
    bool deleteTable(QString table_name);
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
};

#endif // DBMANAGER_H
