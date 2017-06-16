#include "communication.h"
#include "machine.h"

#include "fkmanage.h"
#include "QFile"
#include "QSettings"
#include "QDebug"
#include <QApplication>
//void BaseCommunication::init()
//{

//}
//void TcpSeverCommunication::init()
//{

//}
//ManageComm::ManageComm()
//{
//    moveToThread(this);
//    start();
//}

//void ManageComm::init()
//{
//    QString text;
//    QSettings setting("./settings/communication.ini",QSettings::IniFormat);
//    QStringList groupList=setting.childGroups();
//        foreach(QString group,groupList)
//        {
//            setting.beginGroup(group);
//            QStringList keyList=setting.childKeys();
//            foreach(QString key,keyList)
//            {
//                qDebug()<<key<<"is"<<setting.value(key).toBool();
//                text+=key+" "+tr(setting.value(key).toString().toStdString().c_str());
//            }
//            setting.endGroup();
//        }
////   QString id = "port1";
//}

//void ManageComm::run()
//{
//    init();
//    exec();
//}



ManageComm::ManageComm()//
{
    thrd = new FkThread;
    moveToThread(thrd);
    connect(thrd,SIGNAL(started()),this,SLOT(init()));
    connect(thrd,SIGNAL(finished()),this,SLOT(finish()));
    qDebug()<<"ManageComm construct"<<"ID is"<<QThread::currentThreadId();
    thrd->start();

}

ManageComm::~ManageComm()
{
    foreach (BaseCommunication* var, comuMap) {
        delete var;
    }
}

void ManageComm::init()
{
    qDebug()<<"ManageComm init"<<"ID is"<<QThread::currentThreadId();
    TcpSeverCommunication* tsc = new TcpSeverCommunication("172.11.0.64",999,1,2048);
    comuMap.insert(1,tsc);
}

void ManageComm::finish()
{
    qDebug()<<"ManageComm finish"<<"ID is"<<QThread::currentThreadId();
}

BaseCommunication::BaseCommunication(int id,int size)
{
    if(size<1024)
        size = 1024;
    this->id = id;
    rbfifo = new ByteFiFo(size);
    sbfifo = new ByteFiFo(size);
    lm = new LuaMachine();
    lm_thrd = new FkThread();
    lm->moveToThread(lm_thrd);
    connect(this,SIGNAL(applyRec(BaseCommunication*)),lm,SLOT(mesgRec(BaseCommunication*)));
    connect(lm,SIGNAL(mesgSend()),this,SLOT(Send()));
    lm_thrd->start();
}

BaseCommunication::~BaseCommunication(){
    delete rbfifo;
    delete sbfifo;
    delete lm;
}

TcpSeverCommunication::TcpSeverCommunication(QString ip, int port,int id,int size):BaseCommunication(id,size)
{
    server = nullptr;
    socket = nullptr;

    server = new QTcpServer();
    server->setMaxPendingConnections(1);
    server->listen( QHostAddress(ip),port);

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

TcpSeverCommunication::~TcpSeverCommunication()
{
    qDebug()<<"~TcpSeverCommunication";
    if(server!=nullptr)
    {
        delete server;
    }
    //socket不必释放，qt的框架管理
}

void TcpSeverCommunication::Send()
{
    if(socket!=nullptr)
    {
        if(socket->isOpen())
        {
            QByteArray buf(sbfifo->len(),'\0');
            sbfifo->outQue(buf.data(),sbfifo->len());
            socket->write(buf);
            qDebug()<<"TcpSeverCommunication send";
        }
    }
    else
    {
        qDebug()<<"socket unconnect";
    }

}

void TcpSeverCommunication::newConnection(){
    //只能有一个连接
    if(socket!=nullptr)
    {
        if(socket->isOpen())
            socket->close();
    }
    socket = server->nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    qDebug()<<"socket is "<<socket;
}

void TcpSeverCommunication::readyRead(){
    qDebug()<<"TcpSeverCommunication::readyRead()";
    QByteArray buf = socket->readAll();
    rbfifo->inQue(buf.data(),buf.length());
    qDebug()<<"rbfifo len is"<<rbfifo->len();
    emit applyRec(this);
}
