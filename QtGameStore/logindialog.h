#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "client.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(Client *clnt = nullptr, QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_loginBtn_clicked();

    void on_exitBtn_clicked();

    void on_signBtn_clicked();

private:
    Ui::LoginDialog *ui;
    Client *client;
};

#endif // LOGINDIALOG_H
