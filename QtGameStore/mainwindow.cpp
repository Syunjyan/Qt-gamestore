#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usrsetting.h"
#include "ui_usrsetting.h"
#include "gameinfodialog.h"

#include <QDir>
#include <QFile>
#include <QImage>
#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QProcess>
#include <QSqlError>
#include <QDesktopServices>
#include <QUrl>


MainWindow::MainWindow(Client *clnt ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client=clnt;

    QSqlDatabase db_1;// = QSqlDatabase::database();

    QString dbPath_1 = client->curUsr + "main";
    if(QSqlDatabase::contains(dbPath_1)){
        db_1=QSqlDatabase::database(dbPath_1);
    }else{
        db_1 = QSqlDatabase::addDatabase("QSQLITE",dbPath_1);

    }


    db_1.setDatabaseName("./game.db");
    db_1.open();



    model = new QSqlTableModel(this,db_1);

    model->setTable("game");

    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();//自动调整列宽
    ui->tableView->resizeRowsToContents();//自动调整行距
    ui->tableView->setAlternatingRowColors(true);//设置行间交叉颜色
    ui->tableView->setColumnHidden(1,true);//设置某一列不显示
    ui->tableView->setColumnHidden(2,true);
    ui->tableView->setColumnWidth(0,300);

    //ui->gamenum->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));   //只能输入数字

    ui->DisplayWidget->setCurrentIndex(0);
    ui->playerName->setText(client->curUsr);

    QSqlDatabase db;// = QSqlDatabase::database();
    QString db_name = client->curUsr + ".db";
    QString dbPath = client->curUsr + "mainkjsahd";
    if(QSqlDatabase::contains(dbPath)){
        qDebug()<<"path is exist usr";
        db=QSqlDatabase::database(dbPath);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbPath);
//        db.setDatabaseName(db_name);
//        db.open();
        qDebug()<<"path is not exist usr";
    }


    db.setDatabaseName(db_name);
    db.open();

    QSqlQuery query(db);

    qDebug() << "now check user"<<query.exec("create table IF NOT EXISTS `" + client->curUsr + "` (name varchar primary key NOT NULL , info varchar, filename varchar)");
    qDebug()<<"error"<<query.lastError();

    model_usr = new QSqlTableModel(this,db);
    model_usr->setTable(client->curUsr);
    model_usr->select();
    model_usr->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->usr_tableView->setModel(model_usr);
    ui->usr_tableView->resizeColumnsToContents();//自动调整列宽
    ui->usr_tableView->resizeRowsToContents();//自动调整行距
    ui->usr_tableView->setAlternatingRowColors(true);//设置行间交叉颜色
    ui->usr_tableView->setColumnHidden(1,true);//设置某一列不显示
    ui->usr_tableView->setColumnHidden(2,true);
    ui->usr_tableView->setColumnWidth(0,300);
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);

    db.close();


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


void MainWindow::on_chooseBtn_clicked()
{


    client->upFileName = QFileDialog::getOpenFileName(this);
    if(!client->upFileName.isEmpty()){
        ui->confirmBtn->setEnabled(true);     //上传按钮生效
        int realNameIndex = client->upFileName.lastIndexOf("/");
        QString realName = client->upFileName.right(client->upFileName.length ()-realNameIndex-1);  //取真正文件名
        ui->filePathLineEdit->setText(tr("%1").arg(realName));
        qDebug() << client->upFileName;
    }

}


//断开数据库连接函数
void disconnect(QSqlDatabase &db){
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}
//在数据库中添加新的游戏名与信息
void addGame(QString gamename,QString gameinfo,QString Filename)
{
//    QSqlDatabase db = QSqlDatabase::database();
    QSqlDatabase db;// = QSqlDatabase::database();

    QString dbPath = gamename+gameinfo;
    if(QSqlDatabase::contains(dbPath)){
        qDebug()<<"path is exist spc";
        db=QSqlDatabase::database(dbPath);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbPath);
//        db.setDatabaseName("game.db");
//        db.open();
        qDebug()<<"path is not exist spc";
    }
//    qDebug() << " what happened" << gamename << gameinfo << Filename;
    db.setDatabaseName("./game.db");
    db.open();
    QSqlQuery query(db);
    query.prepare("insert into game (name, info, filename) values(?, ?, ?)");
    query.addBindValue(gamename);
    query.addBindValue(gameinfo);
    query.addBindValue(Filename);
//    qDebug()<<"check query.exec() ="<<query.exec();

//    db.setDatabaseName("./game.db");
//    db.open();

//    query.exec("select * from game");
//    int cnt = 0;
//    while(query.next()){
//            qDebug() << " cerr " <<endl;
//            QString group_id = query.value(0).toString();
//            QString group_key = query.value(1).toString();
//            QString filename_ = query.value(2).toString();
//            qDebug() << "group name=" << group_id;
//            qDebug() << "group info=" << group_key;
//            qDebug() << "group filename=" << filename_;
//    }
//    QString game_na = query.value(0).toString();
//    QString game_in = query.value(1).toString();
//    QString filename = query.value(2).toString();
    disconnect(db);
}


void MainWindow::on_confirmBtn_clicked()
{
    ui->confirmBtn->setEnabled(false);    //文件开始传输时上传按钮失效
    ui->chooseBtn->setEnabled(false);  //打开文件按钮失效

    //给服务器发送上传请求
    QString game_name = ui->nameLineEdit->text();
    QString game_info = ui->introductionTextEdit->document()->toPlainText();
    QString file_name = ui->filePathLineEdit ->text();

    addGame(game_name,game_info,file_name);

    QString id = client->curUsr;

    client->sendMessToServer(client->UPDATE, id, client->upFileName);  //向服务器发送开始上传请求

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

    }
    else {
        disconnect(client, 0, &loop, 0);
        QMessageBox::warning(this, tr(""),
                    tr("连接超时，请重试"),
                    QMessageBox::Yes);
        return;
    }
    qDebug() <<"send out.";
    if(client->receiveType == client->UPSTART){
//        qDebug() << "start update" << upFileName;
        client->upPerSize = 64*1024;   //64kb
        client->upTotalBytes = 0;
        client->upBytesWritten = 0;
        client->upBytesToWrite = 0;
        emit client->startUploadSignal(); //发送上传文件信号
    }
    //之后进⾏正常操作

    ui->confirmBtn->setEnabled(true);
    ui->chooseBtn->setEnabled(true);
//    ui->exitButton->setEnabled(false);  //退出登录按钮失效
//    ui->searchButton->setEnabled(false);    //查找按钮失效
//    ui->downButton->setEnabled(false);  //下载按钮失效

    QMessageBox dlg(QMessageBox::NoIcon,"","上传完成");
    dlg.exec();

}

void MainWindow::on_choose_file_download_clicked()
{
    int num = ui->gamenum->text().toInt()-1;
    QSqlDatabase db;// = QSqlDatabase::database();

    QString dbPath = ui->gamenum->text();
    if(QSqlDatabase::contains(dbPath)){
        qDebug()<<"path is exist spc";
        db=QSqlDatabase::database(dbPath);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbPath);

        qDebug()<<"path is not exist spc";
    }
    qDebug() << " cerr ";

    db.setDatabaseName("./game.db");
    db.open();
    QSqlQuery query(db);
    query.exec("select * from game");
    int cnt = 0;
    while(cnt <= num){
        cnt++;
        query.next();
    }
    QString game_na = query.value(0).toString();
    QString game_in = query.value(1).toString();
    QString filename = query.value(2).toString();



    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);


    gameInfoDialog dlg(client,game_na,game_in,filename);
    dlg.exec();
    //-------------------------------------

    qDebug()<<"now updating user db";
    QSqlDatabase db_s;// = QSqlDatabase::database();

    QString dbPath_s = client->curUsr + "x";
    if(QSqlDatabase::contains(dbPath_s)){
        qDebug()<<"path is exist spc";
        db_s=QSqlDatabase::database(dbPath_s);
    }else{
        db_s = QSqlDatabase::addDatabase("QSQLITE",dbPath_s);
//        db.setDatabaseName(client->curUsr + ".db");
//        db.open();
        qDebug()<<"path is not exist spc";
    }
    qDebug() << game_na << game_in<<filename << endl;
    db_s.setDatabaseName(client->curUsr + ".db");
    if(!db_s.open())qDebug()<<"open failed";
    QSqlQuery query_s(db_s);
    query_s.prepare(QString("replace into `"+ client->curUsr + "` (name, info, filename) values(?, ?, ?)"));
    query_s.addBindValue(game_na);
    query_s.addBindValue(game_in);
    query_s.addBindValue(filename);
    qDebug() << "now check personnal db" << query_s.exec();
    qDebug()<<query_s.lastError();

//    query_s.exec("select * from `" + client->curUsr+"`");
//    while(query_s.next()){
//            qDebug() << " cerr " ;
//            QString group_id = query_s.value(0).toString();
//            QString group_key = query_s.value(1).toString();
//            QString filename_ = query_s.value(2).toString();
//            qDebug() << "group name=" << group_id;
//            qDebug() << "group info=" << group_key;
//            qDebug() << "group filename=" << filename_;
//            qDebug();
//    }

    model_usr = new QSqlTableModel(this,db_s);
    model_usr->setTable(client->curUsr);
    model_usr->select();
    model_usr->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->usr_tableView->setModel(model_usr);
    ui->usr_tableView->resizeColumnsToContents();//自动调整列宽
    ui->usr_tableView->resizeRowsToContents();//自动调整行距
    ui->usr_tableView->setAlternatingRowColors(true);//设置行间交叉颜色
    ui->usr_tableView->setColumnHidden(1,true);//设置某一列不显示
    ui->usr_tableView->setColumnHidden(2,true);

    ui->usr_tableView->setColumnWidth(0,300);

//    QString connection_s;
//    connection_s = db.connectionName();
//    db_s.close();
//    db_s = QSqlDatabase();
//    db_s.removeDatabase(connection_s);
    ui->gamenum->clear();
}


void MainWindow::on_choose_game_toplay_Btn_clicked()
{
    int num = ui->gamenum_2->text().toInt()-1;
    qDebug()<<"num ="<<num;
    QSqlDatabase db;// = QSqlDatabase::database();

    QString dbPath = ui->gamenum_2->text();
    if(QSqlDatabase::contains(dbPath)){
        qDebug()<<"path is exist spc";
        db=QSqlDatabase::database(dbPath);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbPath);
        qDebug()<<"path is not exist spc";
    }
    db.setDatabaseName(client->curUsr + ".db");
    db.open();

    QSqlQuery query(db);
    qDebug()<< "check toplay"<<
               query.exec("select * from `" + client->curUsr + "`");
    int cnt = 0;
    while(cnt <= num){
        cnt++;
        query.next();
    }
    QString game_na = query.value(0).toString();
    QString game_in = query.value(1).toString();
    QString file_name = query.value(2).toString();
    QProcess process(this);

    QString str =QDir::currentPath()+"/files/" + client->curUsr + "/" + file_name;//加可执行文件路径
    qDebug()<< str;
    qDebug() << "process is " <<process.startDetached(str,QStringList());//启动可执行文件
    ui->gamenum_2->clear();
}

void MainWindow::on_onSaleBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.bilibili.com/video/BV1GJ411x7h7?share_source=copy_web"));
}

void MainWindow::on_zhenghuoBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://web.pkuhollow.com/"));
}

void MainWindow::on_playBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.bilibili.com/video/BV1Jg411o7J4?share_source=copy_web"));
}

void MainWindow::on_logoutBtn_clicked()
{
    if(QMessageBox::question(this,"提示","确认退出？",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
        exit(0);
    }
}
