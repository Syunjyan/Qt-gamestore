#include "signdialog.h"
#include "ui_signdialog.h"

#include <QString>
#include <QMessageBox>

SignDialog::SignDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignDialog)
{
    ui->setupUi(this);
}

SignDialog::~SignDialog()
{
    delete ui;
}

void SignDialog::on_loginBtn_clicked()
{
    QString username = ui->usrLineEdit->text();
    QString password = ui->pwdLineEdit->text();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名或密码不能为空",QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
    }

    else {
//       QMessageBox::warning(this, tr("警告"),
//                   tr("用户名或密码错误！"),
//                   QMessageBox::Yes);
//       // 清空内容并定位光标
//       ui->usrLineEdit->clear();
//       ui->pwdLineEdit->clear();
//       ui->usrLineEdit->setFocus();
    }
}


void SignDialog::on_exitBtn_clicked()
{
    reject();
}
