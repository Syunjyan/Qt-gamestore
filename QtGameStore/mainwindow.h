#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Client *clnt = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_usrBtn_clicked();

    void on_storeBtn_clicked();

    void on_libraryBtn_clicked();

    void on_uploadBtn_clicked();

    void on_settingBtn_clicked();

    void on_chooseBtn_clicked();

    void on_confirmBtn_clicked();

//    void on_tableView_activated(const QModelIndex &index);

    void on_choose_file_download_clicked();

    void on_choose_game_toplay_Btn_clicked();

    void on_onSaleBtn_clicked();

    void on_zhenghuoBtn_clicked();

    void on_playBtn_clicked();

    void on_logoutBtn_clicked();

private:
    Ui::MainWindow *ui;
    Client *client;
    QString userFilePath;
    QSqlTableModel *model;
    QSqlTableModel *model_usr;
};
void disconnect(QSqlDatabase &db);
#endif // MAINWINDOW_H
