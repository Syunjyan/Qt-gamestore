#ifndef GAMEINFODIALOG_H
#define GAMEINFODIALOG_H

#include <QDialog>
#include "client.h"

namespace Ui {
class gameInfoDialog;
}

class gameInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gameInfoDialog(Client *clien,QString na,QString In,QString fi,QWidget *parent = nullptr);
    ~gameInfoDialog();

private slots:
    void on_confirmDownloadBtn_clicked();

private:
    Ui::gameInfoDialog *ui;
    Client *client;
    QString name;
    QString Info;
    QString filename;
};

#endif // GAMEINFODIALOG_H
