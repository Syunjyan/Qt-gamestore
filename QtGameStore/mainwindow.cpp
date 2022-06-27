#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"

MainWindow::MainWindow(Client *clnt ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client=clnt;
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

