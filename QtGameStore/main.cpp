#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog dlg;
    dlg.setWindowTitle("登录");

    if(dlg.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    return 0;
}
