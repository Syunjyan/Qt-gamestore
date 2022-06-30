#include "gameinfodialog.h"
#include "ui_gameinfodialog.h"


#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>

gameInfoDialog::gameInfoDialog(Client *clien,QString Na,QString In, QString fi,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameInfoDialog)
{
    ui->setupUi(this);
    name = Na;
    Info = In;
    client = clien;
    filename = fi;
    ui->gameInfoLabel->setText(Info);
    ui->nameLabel->setText(name);
}

gameInfoDialog::~gameInfoDialog()
{
    delete ui;
}
void gameInfoDialog::on_confirmDownloadBtn_clicked()
{

    ui->confirmDownloadBtn->setEnabled(false);
    QString id = client->curUsr;
    QString searchFileName = filename;    //获取要查找的文件名

    qDebug() << Qt::endl<<filename<<Qt::endl;

    client->sendMessToServer(client->SEARCH, id, searchFileName);       //给服务器发送查找请求
    // 这⾥发送请求
        //等待数据接收
    QEventLoop loop;//⼀个循环对象，相当于while(1)
    connect(client, SIGNAL(endReading()), &loop, SLOT(quit()));
    QTimer timer;
    timer.setInterval(5000);
    timer.setSingleShot(true);
    timer.start();
    QTimer::singleShot(5000, &loop, SLOT(quit()));// 5秒后强制退出loop

    loop.exec();
        /* 处理响应 */
        if (timer.isActive()) {
            // 5秒尚未结束，说明正常read
            if(client->receiveType == client->FILENONEXIST){
                QMessageBox::warning(this,"警告","发生错误:FILENONEXIST",QMessageBox::Yes,NULL);
                reject();
            }
       }
        else {
            disconnect(client, 0, &loop, 0);
            QMessageBox::warning(this, tr(""),
                        tr("连接超时，请重试"),
                        QMessageBox::Yes);
            return;
       }


    client->isDownloadingFile = true;       //客户端进入接收下载文件状态
    client->sendMessToServer(client->DOWNSTART, id, searchFileName);  //给服务器发送下载请求

    connect(client, SIGNAL(endReading()), &loop, SLOT(quit()));

    timer.setInterval(5000);
    timer.setSingleShot(true);
    timer.start();
    QTimer::singleShot(5000, &loop, SLOT(quit()));// 5秒后强制退出loop
    loop.exec();
    /* 处理响应 */
    if (timer.isActive()) {
        // 5秒尚未结束，说明正常read
        QMessageBox message(QMessageBox::NoIcon, "", "下载完成");
        message.exec();
        accept();

    }
    else {
        disconnect(client, 0, &loop, 0);
        QMessageBox::warning(this, tr(""),
                    tr("连接超时，请重试"),
                    QMessageBox::Yes);
        return;
    }

//    disconnect(db);
}
