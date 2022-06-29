#ifndef DATAEXECUTION_H
#define DATAEXECUTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

/*向数据库中添加用户信息*/
void disconnect(QSqlDatabase &db){
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}


void addDataModel(QString id, QString pass)
{
//    QSqlDatabase db = QSqlDatabase::database();
    QSqlDatabase db;// = QSqlDatabase::database();

    QString dbPath = id+pass;
    if(QSqlDatabase::contains(dbPath)){
        qDebug()<<"path is exist spc";
        db=QSqlDatabase::database(dbPath);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbPath);
        db.setDatabaseName("user.db");
        db.open();
        qDebug()<<"path is not exist spc";
    }

    db.setDatabaseName("user.db");
    db.open();
    QSqlQuery query(db);
    query.prepare("insert into user (id, pass) values(?, ?)");
    query.addBindValue(id);
    query.addBindValue(pass);
    query.exec();
    disconnect(db);
}

/*登录时查询数据库*/
/*返回值
 * 1 -- 登录成功
 * 2 -- 登录失败，密码错误
 * 3 -- 登录失败，无此用户*/
int loginSearchDataModel(QString id, QString pass)
{
    QSqlDatabase db;// = QSqlDatabase::database();

    QString dbPath = id;
    if(QSqlDatabase::contains(dbPath)){
        qDebug()<<"path is exist spc";
        db=QSqlDatabase::database(dbPath);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbPath);
        db.setDatabaseName("user.db");
        db.open();
        qDebug()<<"path is not exist spc";
    }
    qDebug() << " cerr ";

    QSqlQuery query(db);
    query.exec("select * from user");

    int ret=3;      //登录失败，无此用户
    while(query.next()){
        if(query.value(0).toString() == id){
            if(query.value(1).toString() == pass){
                ret = 1;   //登录成功
            }
            else{
                ret = 2;   //密码错误
            }
        }
    }

    disconnect(db);
    return ret;
}

/*注册时查询数据库*/
/*返回值
 *true -- 用户名不存在，可以注册
 *false -- 用户名已存在
 * */
bool regiSearchDataModel(QString id)
{
//    QSqlDatabase db = QSqlDatabase::database();
    QSqlDatabase db;// = QSqlDatabase::database();

    QString dbPath = id;
    if(QSqlDatabase::contains(dbPath)){
        qDebug()<<"path is exist spc";
        db=QSqlDatabase::database(dbPath);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbPath);
        db.setDatabaseName("user.db");
        db.open();
        qDebug()<<"path is not exist spc";
    }
    QSqlQuery query(db);
    query.exec("select * from user");
    bool ret = true;
    while(query.next()){
        if(query.value(0).toString() == id){
            ret = false;
        }
    }
    disconnect(db);
    return ret;
}

#endif // DATAEXECUTION_H
