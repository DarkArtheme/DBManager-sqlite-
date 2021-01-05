#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent, DBManager* db_manager_) :
    QWidget(parent),
    ui(new Ui::LoginWindow),
    db_manager(db_manager_),
    path_was_chosen(false),
    admin_chosen(true)
{
    ui->setupUi(this);
    ui->pathBD->setReadOnly(true);
    ui->btnAdmin->click();
    ui->password_line->setEchoMode(QLineEdit::Password);
    this->hide_login();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}



void LoginWindow::on_btnPath_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Выберите базу данных", "", "Databases (*.db)");
    ui->pathBD->setText(file_path);
    path_was_chosen = true;
}

void LoginWindow::on_openBD_clicked()
{
    if(!path_was_chosen){
        QMessageBox::warning(this, "Ошибка!", "Выберите путь!");
        return;
    }
    if(!db_manager->connectToDataBase(ui->pathBD->text())){
        QMessageBox::warning(this, "Ошибка!", "База данных недоступна!");
        return;
    }
    this->show_login();
    ui->pathBD->clear();
    path_was_chosen = false;

}

void LoginWindow::on_createDB_clicked()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Выберите базу данных", "", "Databases (*.db)");
    ui->pathBD->setText(file_path);
    if(!file_path.isEmpty())
        path_was_chosen = true;
}

void LoginWindow::hide_login()
{
    ui->login_line->hide();
    ui->password_line->hide();
    ui->btnAdmin->hide();
    ui->btnOp->hide();
    ui->btnLogin->hide();
    ui->label->hide();
    ui->label_2->hide();
}

void LoginWindow::show_login()
{
    ui->login_line->show();
    ui->password_line->show();
    ui->btnAdmin->show();
    ui->btnOp->show();
    ui->btnLogin->show();
    ui->label->show();
    ui->label_2->show();
}



void LoginWindow::on_btnAdmin_clicked()
{
    admin_chosen = true;
}

void LoginWindow::on_btnOp_clicked()
{
    admin_chosen = false;
}

void LoginWindow::on_btnLogin_clicked()
{
    QString login = ui->login_line->text();
    QString password = ui->password_line->text();
    QString role;
    QString res = db_manager->checkPassword(admin_chosen, login, password);
    if(!res.isEmpty()){
        QMessageBox::warning(this, "Ошибка!", res);
        return;
    }
    if(admin_chosen){
        this->close();
        adm_win = new AdminWindow(this, db_manager);
        adm_win->setAttribute(Qt::WA_DeleteOnClose);
        connect(adm_win, &AdminWindow::loginWindow, this, &LoginWindow::show);
        connect(adm_win, &AdminWindow::loginWindow, this, &LoginWindow::hide_login);
        adm_win->show();
    } else{
        this->close();
        oper_win = new MainWindow(this, db_manager);
        oper_win->setAttribute(Qt::WA_DeleteOnClose);
        connect(oper_win, &MainWindow::loginWindow, this, &LoginWindow::show);
        connect(oper_win, &MainWindow::loginWindow, this, &LoginWindow::hide_login);
        oper_win->show();
    }
    ui->login_line->clear();
    ui->password_line->clear();
}
