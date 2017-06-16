#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H
#include<QMap>
#include<QThread>
#include<QtNetwork>
#include "bytefifo.h"

//enum{
//    COMMUN_STATE_UNCONNECT=0,
//    COMMUN_STATE_CONNECT,
//    COMMUN_STATE_ERRO,
//};



#include "QDebug"

class LuaMachine;
class FkThread;
class BaseCommunication;
class ManageComm:public QObject
{
    Q_OBJECT
public:
    ManageComm();
    ~ManageComm();
public slots:
    void init(); //根据配置文件创建信道
    void finish();//程序关闭时，操作
private:
    FkThread* thrd;
    QMap<int,BaseCommunication*> comuMap;
};

class BaseCommunication :public QObject
{
    Q_OBJECT
public:
    BaseCommunication(int id,int size);
    virtual ~BaseCommunication();
    virtual void init(){}
    //测试从lua中转回来后的指针，是否还具有多态特性。测试结果是：有 ; 原因：c++是运行时多态，虚函数表常驻内存有记录
    virtual void test(){
        qDebug()<<"I am BaseCommunication";
    }
signals:
    void applyRec(BaseCommunication*);
public slots:
    virtual void Send(){}
public:
    int id;
    int state;
    int type;
    ByteFiFo* rbfifo;
    ByteFiFo* sbfifo;

    FkThread* lm_thrd;
    LuaMachine* lm;
};

class TcpSeverCommunication:public BaseCommunication
{
    Q_OBJECT
public:
    TcpSeverCommunication(QString ip, int port,int id,int size);
    ~TcpSeverCommunication();
    virtual void init(){}
    virtual void test(){
        qDebug()<<"I am TcpSeverCommunication";
    }
public slots:
    virtual void Send();
    void newConnection();
    void readyRead();
private:
    QString ip;
    int port;
    QTcpServer *server;
    QTcpSocket *socket;
};

#endif
