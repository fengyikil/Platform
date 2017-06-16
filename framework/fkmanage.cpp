#include "fkmanage.h"
#include "communication.h"
#include <QDebug>
#include<stdio.h>
#include "machine.h"
QList<QThread*> g_thrdList;

FkManage::FkManage(QObject *parent)
{
    lm = new LuaMachine();
    magcm = new ManageComm();
}

FkManage::~FkManage()
{
    qDebug()<<"~FkManage";
    delete lm;
    delete magcm;
}
//框架程序退出前处理函数，原则上线程资源统一释放，其它资源各对象自行释放
void FkManage::exit()
{
    int res;
    //调用应用层 lua exit,用户自行处理退出
    lm->call_func("test_exit",">i",&res);
//    qDebug()<<"res is "<<res;
     printf("res is %d\n",res);
    //关闭所有线程
    foreach (QThread* t, g_thrdList) {
        //            qDebug()<<"handle thread";
        printf("handle thread\n");

        t->quit();
        if(t->isRunning())
        {
            t->wait();
        }
        //释放线程对象
        delete t;
    }
    //释放框架资源
    delete this;
    //        QThread::msleep(5000);
}

FkThread::FkThread()
{
    g_thrdList.append(this);
}


