#include "dbmanager.h"
#include "loginwindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBManager db_manager;
    db_manager.connectToDataBase();
    //db_manager.printTable("TestTable");
    //db_manager.insertIntoTestTable("'Vorobushek'");
    qDebug() << "\n";
    //db_manager.printTable("TestTable");
    db_manager.deleteFromTestTable();
    LoginWindow l(nullptr, &db_manager);
    l.show();
    return a.exec();
}
