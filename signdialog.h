#ifndef SIGNDIALOG_H
#define SIGNDIALOG_H

#include <QDialog>
#include "client.h"

namespace Ui {
class SignDialog;
}

class SignDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignDialog(Client *clnt, QWidget *parent = nullptr);
    ~SignDialog();

private slots:
    void on_loginBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::SignDialog *ui;
    Client *client;
};

#endif // SIGNDIALOG_H
