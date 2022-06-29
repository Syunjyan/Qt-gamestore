#include "mainwindow.h"
#include "logindialog.h"
#include "client.h"

#include <QDir>
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
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
