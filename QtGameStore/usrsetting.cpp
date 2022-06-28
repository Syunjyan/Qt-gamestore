#include "usrsetting.h"
#include "ui_usrsetting.h"

usrSetting::usrSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usrSetting)
{
    ui->setupUi(this);
}

usrSetting::~usrSetting()
{
    delete ui;
}
