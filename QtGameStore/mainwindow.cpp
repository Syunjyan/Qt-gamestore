#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usrsetting.h"
#include "ui_usrsetting.h"

#include <QDir>
#include <QFile>
#include <QImage>
#include <QFileDialog>

MainWindow::MainWindow(Client *clnt ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client=clnt;

    ui->DisplayWidget->setCurrentIndex(0);
    ui->playerName->setText(client->curUsr);

    QDir dir;
//    QFileDialog::getOpenFileName()
    userFilePath = "./files/"+client->curUsr;
    if(!dir.exists(userFilePath)){
        dir.mkdir(userFilePath);
    }
    QImage icon;
    QString iconPath = userFilePath + "/user.png";
    if(icon.load(iconPath)){

        QPixmap pixmap = QPixmap::fromImage(icon);

//        QSize imageSize = pixmap.size();

        ui->playerIcon->setPixmap(pixmap);
        ui->playerIcon->setScaledContents(true);
//        ui->playerIcon->resize(imageSize);
    }

    QFile Info(userFilePath + "/Info.txt");
    if(Info.open(QFile::ReadOnly | QFile::Text)){
        QTextStream in(&Info);
        ui->showInformationTextBrowser->setPlainText(in.readAll());
    }

    this->setWindowTitle("the Wizards");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_usrBtn_clicked()
{
    ui->DisplayWidget->setCurrentIndex(0);
}


void MainWindow::on_storeBtn_clicked()
{
    ui->DisplayWidget->setCurrentIndex(1);
}


void MainWindow::on_libraryBtn_clicked()
{
    ui->DisplayWidget->setCurrentIndex(2);
}


void MainWindow::on_uploadBtn_clicked()
{
    ui->DisplayWidget->setCurrentIndex(3);
}




void MainWindow::on_settingBtn_clicked()
{
    usrSetting dlg(client);
    dlg.exec();
    QImage icon;
    QString iconPath = userFilePath + "/user.png";
    if(icon.load(iconPath)){

        QPixmap pixmap = QPixmap::fromImage(icon);

        ui->playerIcon->setPixmap(pixmap);
        ui->playerIcon->setScaledContents(true);
    }
    QFile Info(userFilePath + "/Info.txt");
    if(Info.open(QFile::ReadOnly | QFile::Text)){
        QTextStream in(&Info);
        ui->showInformationTextBrowser->setPlainText(in.readAll());
    }

}

