#include "dbmanager.h"

DBManager::DBManager(QObject *parent) : QObject(parent){
}

DBManager::~DBManager()
{
    delete model;
    database.close();
}

void DBManager::connectToDataBase()
{
    if(!openDataBase()){
        qDebug() << "Database couldn't open\n";
        return;
    }
    table_names_model = new QStringListModel();
    column_names_model = new QStringListModel();
    model = new QSqlRelationalTableModel(this, database);
}

QSqlTableModel* DBManager::printTable(QString table_name)
{
    model->setEditStrategy(QSqlRelationalTableModel::EditStrategy::OnFieldChange);
    model->setTable(table_name);
    model->select();
    return model;
}

void DBManager::insertIntoTestTable(QString name)
{
    QSqlQuery query(database);
    auto res = query.exec("insert into TestTable (name) values( " + name +" );");
    qDebug() << res;
}

void DBManager::deleteFromTestTable()
{
    QSqlQuery query(database);
    auto res = query.exec("delete from TestTable where id > 5;");
    qDebug() << query.lastError().text();
}

QStringListModel* DBManager::getTables()
{
    table_names_model->setStringList(database.tables());
    return  table_names_model;
}

QStringListModel *DBManager::getColumns(QString table_name)
{
    model->setTable(table_name);
    int column_number = model->columnCount();
    QStringList columns;
    QSqlQuery query_to_know_type;
    query_to_know_type.exec("PRAGMA table_info(" + table_name + ")");
    for(int i = 0; i < column_number; ++i){
        query_to_know_type.next();
        QString buffer;
        QTextStream ss(&buffer);
        ss << model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() << " (" << query_to_know_type.value(2).toString()  << ")";
        if(query_to_know_type.value(5).toInt()){
            ss << " [PRIMARY_KEY]";
        }
        columns.append(buffer);

    }
    column_names_model->setStringList(columns);
    return column_names_model;
}

bool DBManager::addColumn(QString table_name, QString column_name, QString column_type)
{
    bool res = false;
    QSqlQuery query(database);
    res = query.prepare("ALTER TABLE " + table_name + " ADD COLUMN " +
                        column_name + " " + column_type + ";");
    res = query.exec();
    return res;
}

bool DBManager::deleteColumn(QString table_name, QString column_name)
{
    bool res = false;
    QSqlQuery query(database);
    res = query.prepare("ALTER TABLE " + table_name + " DROP COLUMN " +
                        column_name + ";");
    res = query.exec();
    return res;
}

bool DBManager::addTable(QString table_name)
{
    bool res = false;
    QSqlQuery query(database);
    res = query.prepare("CREATE TABLE " + table_name + "(ID integer PRIMARY KEY AUTOINCREMENT NOT NULL);");
    res = query.exec();
    return res;
}

bool DBManager::deleteTable(QString table_name)
{

    bool res = false;
    QSqlQuery query(database);
    res = query.prepare("DROP TABLE " + table_name + ";");
    res = query.exec();
    return res;
}

bool DBManager::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    database = QSqlDatabase::addDatabase("QSQLITE");
    //database.setHostName("TestDatabase");
    database.setDatabaseName("databases/testdb.db");
    return database.open();
}

void DBManager::closeDataBase()
{
    delete model;
    model = nullptr;
    database.close();
}
