#ifndef SIGNDIALOG_H
#define SIGNDIALOG_H

#include <QDialog>

namespace Ui {
class SignDialog;
}

class SignDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignDialog(QWidget *parent = nullptr);
    ~SignDialog();

private slots:
    void on_loginBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::SignDialog *ui;
};

#endif // SIGNDIALOG_H
