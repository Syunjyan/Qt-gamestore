#include "mainwindow.h"
#include "logindialog.h"
#include "client.h"

#include <QDir>
#include <QApplication>
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>


int main(int argc, char *argv[])
{
    //建立新的游戏数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","initdb");
    db.setDatabaseName("./game.db");
    if(!db.open()){
        QMessageBox::critical(0, "Cannot open database",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);

    query.exec("create table IF NOT EXISTS game (name varchar primary key, info varchar, filename varchar)");
    db.close();

    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);

    QApplication a(argc, argv);
    QDir dir;
    if(!dir.exists("files"))
    {
        dir.mkdir("files");
    }
    Client clnt;

    LoginDialog dlg(&clnt);

    dlg.setWindowTitle("登录");

    if(dlg.exec()==QDialog::Accepted)
    {
        MainWindow w(&clnt);
        w.show();
        return a.exec();
    }
    return 0;
}
