#include "usrsetting.h"
#include "ui_usrsetting.h"
#include "client.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

usrSetting::usrSetting(Client *clnt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usrSetting)
{
    ui->setupUi(this);
    client=clnt;
    ui->uploadIconBtn->hide();

    QFile file("files/"+client->curUsr+"/information.txt");//新建QFile对象
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream in(&file);//新建文本流对象
        QApplication::setOverrideCursor(Qt::WaitCursor);
        //读文件的全部文本内容，并添加到编辑器中
        ui->informationTextEdit->setPlainText(in.readAll());
    }//只读方式打开文件
    this->setWindowTitle("个人信息修改");
}

usrSetting::~usrSetting()
{
    delete ui;
}

void usrSetting::on_chooseIconBtn_clicked()
{
    filename = QFileDialog::getOpenFileName(this,
                                                    tr("select your icon"));

    if (filename.isEmpty()) {
//        QMessageBox msg(QMessageBox::Warning,"警告","图片打开失败，请打开正确格式图片",QMessageBox::Yes,NULL);
//        msg.exec();
        return ;
    }
    ui->uploadIconBtn->setEnabled(true);     //上传按钮生效
    ui->uploadIconBtn->show();
    int realNameIndex = filename.lastIndexOf("/");
    QString realName = filename.right(filename.length ()-realNameIndex-1);  //取真正文件名
    ui->filenameLabel->setText(tr("文件名： %1").arg(realName));
    qDebug() << filename;
}


void usrSetting::on_uploadIconBtn_clicked()
{
    QImage image;
    if (!image.load(filename)) {
        QMessageBox::information(this, tr("Error"), tr("Open file error"));
        return ;
    }
    filename.clear();
    if(!image.save("./files/"+client->curUsr+"/user.png","PNG")){
        qDebug()<<"failed to save : "<<"./file/"+client->curUsr+"/user.png";
        QMessageBox::information(this, tr("Error"), tr("Save file error"));
        return ;
    }
    QMessageBox box;
    box.setWindowTitle("提示");
    box.setText("上传成功");
    QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
    box.exec();
}


void usrSetting::on_confirmChangeInfoBtn_clicked()
{
    QString fileName = "./files/"+client->curUsr+"/Info.txt";
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
    // %1和82分别对应后面arg两个参数，/n起换行的作用
        QMessageBox::warning(this,tr(""),
                                  tr("无法写入文件%1:/n%2")
                        .arg(fileName).arg(file.errorString()));
        return;
    }
    QTextStream out (&file) ;
    //鼠标指针交为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<< ui->informationTextEdit->toPlainText();
    //鼠标指针恢复原来的状态
    QApplication::restoreOverrideCursor();

    QMessageBox box;
    box.setWindowTitle("提示");
    box.setText("个人信息修改成功");
    QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
    box.exec();
}

