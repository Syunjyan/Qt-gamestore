#include "mainwindow.h"
#include "logindialog.h"
#include "client.h"

#include <QDir>
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client clnt;
    MainWindow w(&clnt);
    LoginDialog dlg(&clnt);

    dlg.setWindowTitle("登录");

    if(dlg.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    return 0;
}

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    Client w;
//    w.setWindowTitle("文件传输系统");
//    QDir dir;
//    if(!dir.exists("files"))
//    {
//        dir.mkdir("files");
//    }

//    w.show();

//    return a.exec();
//}
