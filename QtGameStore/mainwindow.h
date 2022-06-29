#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    Client *client;
    QString userFilePath;
};
#endif // MAINWINDOW_H
