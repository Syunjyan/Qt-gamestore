#ifndef USRSETTING_H
#define USRSETTING_H

#include <QDialog>

#include "client.h"


namespace Ui {
class usrSetting;
}

class usrSetting : public QDialog
{
    Q_OBJECT

public:
    explicit usrSetting(Client *clnt, QWidget *parent = nullptr);
    ~usrSetting();

private slots:
    void on_chooseIconBtn_clicked();

    void on_uploadIconBtn_clicked();

    void on_confirmChangeInfoBtn_clicked();

private:
    Ui::usrSetting *ui;
    Client *client;
    QString filename;
};

#endif // USRSETTING_H
