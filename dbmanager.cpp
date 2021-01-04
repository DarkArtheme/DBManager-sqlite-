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
    query_to_know_type.exec("PRAGMA table_info(" + table_name + ");");

    QStringList foreign_keys;
    QStringList foreign_tables;
    QSqlQuery query_to_know_fk;
    query_to_know_fk.exec("PRAGMA foreign_key_list(" + table_name + ");");
    while(query_to_know_fk.next()){
        foreign_keys.append(query_to_know_fk.value(3).toString());
        foreign_tables.append(query_to_know_fk.value(2).toString());
    }
    for(int i = 0; i < column_number; ++i){
        query_to_know_type.next();
        QString col_name = model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        QString buffer;
        QTextStream ss(&buffer);
        ss << col_name << " (" << query_to_know_type.value(2).toString()  << ")";
        if(query_to_know_type.value(5).toInt()){
            ss << " [PRIMARY_KEY]";
        }
        for(int j = 0; j < foreign_keys.size(); ++j){
            if(col_name == foreign_keys[j]){
                ss << " [FOREIGN_KEY TO " + foreign_tables[j].toUpper() + "]";
            }
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
    model->setTable(table_name);
    int column_number = model->columnCount();
    QStringList columns;
    for(int i = 0; i < column_number; ++i){
        QString col = model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        if(col != column_name)
            columns.append(col);
    }
    QSqlQuery query(database);
    QString query_text = "CREATE TABLE " + table_name + "_backup AS SELECT ";
    for(int i = 0; i < columns.size(); ++i){
        if(i != columns.size() - 1)
            query_text += columns[i] + ", ";
        else
            query_text += columns[i];
    }
    query_text += " FROM " + table_name + ";";
    query.prepare(query_text);
    query.exec();
    query.clear();
    query_text = "DROP TABLE " + table_name + ";";
    query.prepare(query_text);
    query.exec();
    query.clear();
    query_text = "ALTER TABLE " + table_name + "_backup RENAME  TO " + table_name + ";";
    res = query.prepare(query_text);
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

bool DBManager::renameColumn(QString table_name, QString old_name, QString new_name)
{
    bool res = false;
    QSqlQuery query(database);
    res = query.prepare("ALTER TABLE " + table_name + " RENAME COLUMN " +
                        old_name + " TO " + new_name + ";");
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
