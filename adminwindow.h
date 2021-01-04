#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "dbmanager.h"
#include "entitycreator.h"
#include "columncreator.h"
#include "columnrenamer.h"
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

    void on_addTable_clicked();

    void on_update_triggered();

    void on_tableNames_clicked(const QModelIndex &index);

    void on_delTable_clicked();

    void update(bool should_show_columns);

    void on_addCol_clicked();

    void on_columnNames_clicked(const QModelIndex &index);

    void on_delCol_clicked();

    void changeChosenColumn(QString new_name);

    void on_renameCol_clicked();

private:
    Ui::AdminWindow *ui;
    DBManager *db_manager;
    EntityCreator* table_creator;
    ColumnCreator* column_creator;
    ColumnRenamer* column_renamer;
    QString chosenTable;
    QString chosenTable_double_clicked;
    QString chosenColumn;
    QStringListModel* empty_model;
};

#endif // ADMINWINDOW_H
