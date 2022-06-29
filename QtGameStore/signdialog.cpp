#include "signdialog.h"
#include "ui_signdialog.h"
#include "client.h"

#include <QString>
#include <QMessageBox>
#include <QTimer>

SignDialog::SignDialog(Client *clnt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignDialog)
{
    ui->setupUi(this);
    ui->loginBtn->setDefault ( true );
    setTabOrder(ui->usrLineEdit, ui->pwdLineEdit);
    client = clnt;
    ui->usrLineEdit->setFocus();
    this->setWindowTitle("注册");
}

SignDialog::~SignDialog()
{
    delete ui;
}

void SignDialog::on_loginBtn_clicked()
{
    QString username = ui->usrLineEdit->text();
    QString password = ui->pwdLineEdit->text();
    QString password_2 = ui->pwdLineEdit_2->text();
    if(username.isEmpty() || password.isEmpty() || password_2.isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名或密码不能为空",QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit_2->clear();
        ui->usrLineEdit->setFocus();
        return;
    }
    else if(password!=password_2){
        QMessageBox::warning(this,"警告","两次输入的密码不同",QMessageBox::Yes);
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit_2->clear();
        ui->pwdLineEdit->setFocus();
        return;
    }
    // 自定义创建账号提示框
    QMessageBox box;
    box.setWindowTitle("提示");
    box.setText("确认以 "+username+" 作为用户名吗？");
    QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
    QPushButton *noBtn = box.addButton(tr("否(&N)"),QMessageBox::RejectRole);
    box.exec();
    if(box.clickedButton() == noBtn){
        return;
    }

    client->sendMessToServer(client->REGIREQ, username, password);

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

    qDebug()<<client->receiveType<<' '<<client->REGISUCCESS;

    if(client->receiveType == client->REGISUCCESS){
        QMessageBox::warning(this,"","注册成功",QMessageBox::Yes);
        client->curUsr = username;
        accept();
    }
    else if(client->receiveType == client->REGIIDEXIT){
        QMessageBox::warning(this,"","该用户名已被使用",QMessageBox::Yes);
        reject();
    }
    else{

        QMessageBox::warning(this,"error",("发生未知错误: receiveCode "+client->receiveType),QMessageBox::Yes);
        qDebug()<<client->receiveType;
        exit(0);
    }
//       QMessageBox::warning(this, tr("警告"),
//                   tr("用户名或密码错误！"),
//                   QMessageBox::Yes);
//       // 清空内容并定位光标
//       ui->usrLineEdit->clear();
//       ui->pwdLineEdit->clear();
//       ui->usrLineEdit->setFocus();

}


void SignDialog::on_exitBtn_clicked()
{
    reject();
}
