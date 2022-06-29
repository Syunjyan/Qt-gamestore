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

}

usrSetting::~usrSetting()
{
    delete ui;
}

void usrSetting::on_chooseIconBtn_clicked()
{
    filename = QFileDialog::getOpenFileName(this,
                                                    tr("select your icon"), //tr("Images (*.png *.bmp *.jpg *.gif *.ico)"));
                                                    tr("Images (*.png)"));
    if (filename.isEmpty()) {
        return ;
    }
    ui->uploadIconBtn->setEnabled(true);     //上传按钮生效
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

