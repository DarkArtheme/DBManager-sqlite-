#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "adminwindow.h"
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~LoginWindow();

private slots:
    void on_btnAdm_clicked();

    void on_btnOper_clicked();

private:
    Ui::LoginWindow *ui;
    AdminWindow *adm_win;
    MainWindow *oper_win;
    DBManager* db_manager;
};

#endif // LOGINWINDOW_H
