#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "dbmanager.h"
#include <QMainWindow>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr, DBManager* db_manager_ = nullptr);
    ~AdminWindow();
signals:
    void loginWindow();
private slots:
    void on_relogin_triggered();

    void on_exit_triggered();

    void on_tableNames_doubleClicked(const QModelIndex &index);

private:
    Ui::AdminWindow *ui;
    DBManager *db_manager;
};

#endif // ADMINWINDOW_H
