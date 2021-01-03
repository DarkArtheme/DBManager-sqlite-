#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~MainWindow();
signals:
    void loginWindow();
private slots:
    void on_pushButton_clicked();

    void on_relogin_triggered();

    void on_exit_triggered();

private:
    Ui::MainWindow *ui;
    DBManager* db_manager;
};
#endif // MAINWINDOW_H
