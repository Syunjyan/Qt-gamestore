#include <QMessageBox>
#include <QByteArray>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <QTimer>
#include <iostream>

#include "logindialog.h"
#include "ui_logindialog.h"
#include "signdialog.h"
#include "client.h"

LoginDialog::LoginDialog(Client *clnt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    client = clnt;
    ui->usrLineEdit->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QString username = ui->usrLineEdit->text().trimmed();
    QString password = ui->pwdLineEdit->text();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名或密码不能为空",QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
        return;
    }

    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    qDebug()<<"ready to send";
    qDebug()<<client;
    client->sendMessToServer(client->LOGINREQ, username, password);

    //等待数据接收
    QEventLoop loop;

    connect(client, SIGNAL(endReading()), &loop, SLOT(quit()));

    QTimer timer;
    timer.setInterval(5000);
    timer.setSingleShot(true);
    timer.start();
    QTimer::singleShot(5000, &loop, SLOT(quit()));
    loop.exec();

    /* 处理响应 */
    if (timer.isActive()) {
        // 执行处理

    }
    else {
        disconnect(client, 0, &loop, 0);
        QMessageBox::warning(this, tr(""),
                    tr("连接超时，请重试"),
                    QMessageBox::Yes);
        return;
    }


    qDebug() <<"send out.";
    if(client->receiveType == client->LOGINSUCCESS)
    {
        client->curUsr = username;
        accept();
    }
    else if(client->receiveType == client->LOGINIDNON){
       QMessageBox::warning(this, tr("警告"),
                   tr("用户名不存在"),
                   QMessageBox::Yes);
       // 清空内容并定位光标
       ui->usrLineEdit->clear();
       ui->pwdLineEdit->clear();
       ui->usrLineEdit->setFocus();
    }
    else if(client->receiveType == client->LOGINPASSERROR){
       QMessageBox::warning(this, tr("警告"),
                   tr("密码错误！"),
                   QMessageBox::Yes);
       // 清空内容并定位光标
       ui->usrLineEdit->clear();
       ui->pwdLineEdit->clear();
       ui->usrLineEdit->setFocus();
    }
    else qDebug()<<"bug";
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
//    releaseKeyboard();
    SignDialog dlg(client);
    if(dlg.exec()==QDialog::Accepted){
        accept();
    }
//    grabKeyboard();
}

