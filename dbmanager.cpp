#include "dbmanager.h"

DBManager::DBManager(QObject *parent) : QObject(parent){
    admin_logins.append("admin");
    admin_passwords.append("admin");
    operator_logins.append("admin");
    operator_passwords.append("admin");
    operator_logins.append("user");
    operator_passwords.append("12345");
}

DBManager::~DBManager()
{
    delete model;
    database.close();
    QSqlDatabase::removeDatabase(database.databaseName());
}

QString DBManager::checkPassword(bool admin_chosen, QString login, QString password)
{
    if(admin_chosen){
        int c = -1;
        for(int i = 0; i < admin_logins.size(); ++i){
            if(admin_logins[i] == login){
                c = i;
                break;
            }
        }
        if(c < 0){
            return "Wrong login!";
        } else if(admin_passwords[c] != password){
            return "Wrong password!";
        }
    } else {
        int c = -1;
        for(int i = 0; i < operator_logins.size(); ++i){
            if(operator_logins[i] == login){
                c = i;
                break;
            }
        }
        if(c < 0){
            return "Wrong login!";
        } else if(operator_logins[c] != password){
            return "Wrong password!";
        }
    }
    return "";
}

bool DBManager::connectToDataBase(QString path)
{
    if(database.isOpen()){
        database.close();
        QSqlDatabase::removeDatabase(database.databaseName());
    }
    if(!openDataBase(path)){
        qDebug() << "Database couldn't open\n";
        return false;
    }
    table_names_model = new QStringListModel();
    column_names_model = new QStringListModel();
    model = new QSqlRelationalTableModel(this, database);
    return true;
}

QSqlRelationalTableModel* DBManager::printTable(QString table_name)
{
    model->setEditStrategy(QSqlRelationalTableModel::EditStrategy::OnFieldChange);
    model->setTable(table_name);
    model->select();
    return model;
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
    QSqlQuery query_to_know_type(database);
    query_to_know_type.exec("PRAGMA table_info(" + table_name + ");");

    QStringList foreign_keys;
    QStringList foreign_tables;
    QSqlQuery query_to_know_fk(database);
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

int DBManager::getLastID(QString table_name)
{
    QSqlQuery query(database);
    QString query_text = "SELECT MAX(ID) FROM %1 ;";
    query.prepare(query_text.arg(table_name));
    query.exec();
    query.next();
    return query.value(0).toInt();
}

bool DBManager::insertLineInto(QString table_name)
{
    QSqlQuery query(database);
    QString query_text = "INSERT INTO %1 (ID) VALUES( %2 );";
    query.prepare(query_text.arg(table_name).arg(this->getLastID(table_name) + 1));
    return query.exec();
}

bool DBManager::deleteLineFrom(QString table_name, int id)
{
    QSqlQuery query(database);
    QString query_text = "DELETE FROM %1 WHERE ID = %2 ;";
    query.prepare(query_text.arg(table_name).arg(id));
    return query.exec();
}

int DBManager::getID(QString table_name, int row)
{
    QSqlQuery query(database);
    QString query_text = "SELECT * FROM %1;";
    query.prepare(query_text.arg(table_name));
    query.exec();
    int c = 0;
    int ID = 0;
    while(query.next()){
        ID = query.value(0).toInt();
        if(c == row)
            break;
        ++c;
    }
    return ID;
}

QString DBManager::getColumnName(QString table_name, int col)
{
    model->setTable(table_name);
    return model->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();
}

bool DBManager::updateField(QString table_name, int col, int ID, QString value)
{
    QSqlQuery query(database);
    QSqlQuery query_to_know_type(database);
    QString type;
    query_to_know_type.exec("PRAGMA table_info(" + table_name + ");");
    int c = 0;
    while(query_to_know_type.next()){
        type = query_to_know_type.value(2).toString();
        if(c == col)
            break;
        ++c;
    }
    if(type.toUpper() != "INT"){
        value = "'" + value +"'";
    }
    QString column = this->getColumnName(table_name, col);
    QString query_text = "UPDATE %1 SET %2 = %3 WHERE ID = %4;";
    query.prepare(query_text.arg(table_name).arg(column).arg(value).arg(ID));
    return query.exec();
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
    model->setTable(table_name);
    int column_number = model->columnCount();
    QStringList columns;
    int ind = 0;
    for(int i = 1; i < column_number; ++i){
        QString col = model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        if(col != column_name)
            columns.append(col);
        else
            ind = i - 1;
    }
    QStringList foreign_keys;
    QStringList foreign_tables;
    QStringList creatingFK;
    QString createFK = "FOREIGN KEY(%1) REFERENCES %2(ID) ON UPDATE CASCADE ON DELETE SET NULL";
    QSqlQuery query_to_know_fk(database);
    query_to_know_fk.exec("PRAGMA foreign_key_list(" + table_name + ");");
    while(query_to_know_fk.next()){
        if(query_to_know_fk.value(3).toString() != column_name){
            foreign_keys.append(query_to_know_fk.value(3).toString());
            foreign_tables.append(query_to_know_fk.value(2).toString());
        }
    }
    for(int i = 0; i < foreign_keys.size(); ++i){
        creatingFK.append(createFK.arg(foreign_keys[i]).arg(foreign_tables[i]));
    }
    QSqlQuery query_to_know_type(database);
    query_to_know_type.exec("PRAGMA table_info(" + table_name + ");");
    QStringList types;
    query_to_know_type.next();
    int c = 0;
    while(query_to_know_type.next()){
        if(c != ind)
            types.append(query_to_know_type.value(2).toString());
        ++c;
    }
    QString query_text = QString("CREATE TABLE %1_backup (ID INT PRIMARY KEY, ");
    QString field = "%1 %2";
    for(int i = 0; i < columns.size(); ++i){
        query_text += field.arg(columns[i]).arg(types[i]);
        if(i < columns.size() - 1 || !creatingFK.empty()){
            query_text += ", ";
        }
    }
    for(int i = 0; i < creatingFK.size(); ++i){
        query_text += creatingFK[i];
        if(i < creatingFK.size() - 1){
            query_text += ", ";
        }
    }
    query_text += ");";
    QSqlQuery query(database);
    ///*qDebug() <<*/ query_text.arg(table_name);
    query.prepare(QString(query_text.arg(table_name)));
    query.exec();

    query.clear();
    query_text = QString("INSERT INTO %1_backup(ID, ");
    for(int i = 0; i < columns.size(); ++i){
        query_text += columns[i];
        if(i < columns.size() - 1){
            query_text += ", ";
        }
    }
    query_text += ") SELECT ID, ";
    for(int i = 0; i < columns.size(); ++i){
        query_text += columns[i];
        if(i < columns.size() - 1){
            query_text += ", ";
        }
    }
    query_text += " FROM %1 ;";
    ///*qDebug() <<*/ query_text.arg(table_name);
    query.exec(QString(query_text.arg(table_name)));
    ///*qDebug() <<*/ query.lastError().text();

    query.clear();
    query_text = QString("DROP TABLE %1;");
    ///*qDebug() <<*/ query_text.arg(table_name);
    query.prepare(QString(query_text.arg(table_name)));
    query.exec();

    query.clear();
    query_text = QString("ALTER TABLE %1_backup RENAME TO %1;");
    ///*qDebug() <<*/ query_text.arg(table_name);
    query.prepare(QString(query_text.arg(table_name)));
    return query.exec();
}

bool DBManager::addTable(QString table_name)
{
    bool res = false;
    QSqlQuery query(database);
    res = query.prepare("CREATE TABLE " + table_name + "(ID INT PRIMARY KEY NOT NULL);");
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

bool DBManager::makeForeignKey(QString FK_table_name, QString PK_table_name)
{
    QSqlQuery query_to_add(database);
    QString query_to_add_text = "ALTER TABLE %1 ADD COLUMN ID_%2 INT;";
    query_to_add.prepare(query_to_add_text.arg(FK_table_name).arg(PK_table_name));
    query_to_add.exec();

    model->setTable(FK_table_name);
    int column_number = model->columnCount();
    QStringList columns;
    for(int i = 1; i < column_number; ++i){
        QString col = model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        columns.append(col);
    }
    QStringList foreign_keys;
    QStringList foreign_tables;
    QStringList creatingFK;
    QString createFK = "FOREIGN KEY(%1) REFERENCES %2(ID) ON UPDATE CASCADE ON DELETE SET NULL";
    QSqlQuery query_to_know_fk(database);
    query_to_know_fk.exec("PRAGMA foreign_key_list(" + FK_table_name + ");");
    while(query_to_know_fk.next()){
        foreign_keys.append(query_to_know_fk.value(3).toString());
        foreign_tables.append(query_to_know_fk.value(2).toString());
    }
    foreign_keys.append("ID_" + PK_table_name);
    foreign_tables.append(PK_table_name);
    for(int i = 0; i < foreign_keys.size(); ++i){
        creatingFK.append(createFK.arg(foreign_keys[i]).arg(foreign_tables[i]));
    }
    QSqlQuery query_to_know_type(database);
    query_to_know_type.exec("PRAGMA table_info(" + FK_table_name + ");");
    QStringList types;
    query_to_know_type.next();
    while(query_to_know_type.next()){
        types.append(query_to_know_type.value(2).toString());
    }
    QString query_text = QString("CREATE TABLE %1_backup (ID INT PRIMARY KEY, ");
    QString field = "%1 %2";
    for(int i = 0; i < columns.size(); ++i){
        query_text += field.arg(columns[i]).arg(types[i]);
        if(i < columns.size() - 1 || !creatingFK.empty()){
            query_text += ", ";
        }
    }
    for(int i = 0; i < creatingFK.size(); ++i){
        query_text += creatingFK[i];
        if(i < creatingFK.size() - 1){
            query_text += ", ";
        }
    }
    query_text += ");";
    QSqlQuery query(database);
    //qDebug() << query_text.arg(FK_table_name);
    query.prepare(QString(query_text.arg(FK_table_name)));
    query.exec();

    query.clear();
    query_text = QString("INSERT INTO %1_backup(ID, ");
    for(int i = 0; i < columns.size(); ++i){
        query_text += columns[i];
        if(i < columns.size() - 1){
            query_text += ", ";
        }
    }
    query_text += ") SELECT ID, ";
    for(int i = 0; i < columns.size(); ++i){
        query_text += columns[i];
        if(i < columns.size() - 1){
            query_text += ", ";
        }
    }
    query_text += " FROM %1 ;";
    ///*qDebug() <<*/ query_text.arg(FK_table_name);
    query.exec(QString(query_text.arg(FK_table_name)));

    query.clear();
    query_text = QString("DROP TABLE %1;");
    ///*qDebug() <<*/ query_text.arg(FK_table_name);
    query.prepare(QString(query_text.arg(FK_table_name)));
    query.exec();

    query.clear();
    query_text = QString("ALTER TABLE %1_backup RENAME TO %1;");
    //qDebug() << query_text.arg(FK_table_name) << "\n";
    query.prepare(QString(query_text.arg(FK_table_name)));
    return query.exec();

}

bool DBManager::openDataBase(QString path)
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    database = QSqlDatabase::addDatabase("QSQLITE");
    //database.setHostName("TestDatabase");
    database.setDatabaseName(path);
    return database.open();
}

void DBManager::closeDataBase()
{
    delete model;
    model = nullptr;
    database.close();
}


