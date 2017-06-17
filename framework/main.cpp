#include "mainwindow.h"
#include <QApplication>
#include "communication.h"
#include "QDebug"
#include "QFile"
#include "machine.h"
#include "ftest.h"
#include "fkmanage.h"
//Ftest ftt;
//LuaMachine* lm;
//void check()
//{
//    QFile file;
//    file.setFileName("./settings/communication.ini");
//        if (!file.exists()){
//            qDebug()<<"./settings/communication.ini is not exists";
//            exit(0);
//        };
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    bool res;
//    Ftest* f3;
//    qDebug()<<"f3 is"<<f3;
//    if(f3!=nullptr)
//    qDebug()<<"f3 is"<<f3;
//    Ftest* f1 = new ft1(100,99);
////    f1->mem = 10;
//    qDebug()<<f1->mem;
//    delete f1;

//    Ftest* f2 = new ft2(2);
////    f2->mem = 20;
//    qDebug()<<f2->mem;

//    delete f2;

//    TcpSeverCommunication tsc("172.11.0.64",999,2048);
    FkManage* k = new FkManage;
//    lm = new LuaMachine();

    a.connect(&a,SIGNAL(lastWindowClosed()),k,SLOT(exit()));
//    res = lm->open_file("test.lua",NULL);
//    qDebug()<<res;
//    int b;
//    lm->call_func("test_add","ii>i",9,2,&b);

//    lm.lw_close();
//    check();
//    ManageComm mange;
//    MainWindow w;
//    w.show();

    return a.exec();
}
