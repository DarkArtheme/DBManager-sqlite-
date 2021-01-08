#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBManager db_manager;
    LoginWindow l(nullptr, &db_manager);
    l.show();
    return a.exec();
}
