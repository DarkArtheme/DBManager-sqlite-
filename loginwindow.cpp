#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent, DBManager* db_manager_) :
    QWidget(parent),
    ui(new Ui::LoginWindow),
    db_manager(db_manager_)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnAdm_clicked()
{
    this->close();
    adm_win = new AdminWindow(this, db_manager);
    connect(adm_win, &AdminWindow::loginWindow, this, &LoginWindow::show);
    adm_win->show();
}

void LoginWindow::on_btnOper_clicked()
{
    this->close();
    oper_win = new MainWindow(this, db_manager);
    connect(oper_win, &MainWindow::loginWindow, this, &LoginWindow::show);
    oper_win->show();
}
