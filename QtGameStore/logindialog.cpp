#include <QMessageBox>
#include <QByteArray>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <iostream>

#include "logindialog.h"
#include "ui_logindialog.h"
#include "signdialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QString username = ui->usrLineEdit->text();
    QString password = ui->pwdLineEdit->text();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名或密码不能为空",QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
    }

    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    else if(ui->usrLineEdit->text().trimmed()  == tr("admin") &&
           ui->pwdLineEdit->text() == tr("1234"))
    {
       accept();
    }
    else {
       QMessageBox::warning(this, tr("警告"),
                   tr("用户名或密码错误！"),
                   QMessageBox::Yes);
       // 清空内容并定位光标
       ui->usrLineEdit->clear();
       ui->pwdLineEdit->clear();
       ui->usrLineEdit->setFocus();
    }
}


void LoginDialog::on_exitBtn_clicked()
{
    reject();
}


//void LoginDialog::on_sgnLabel_linkHovered(const QString &link)
//{
//    QApplication::setOverrideCursor(Qt::PointingHandCursor);
//}


void LoginDialog::on_signBtn_clicked()
{
    SignDialog dlg;
    dlg.exec();
}

