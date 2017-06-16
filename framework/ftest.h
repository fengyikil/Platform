#ifndef FTEST_H
#define FTEST_H

#include "QDebug"

class Ftest
{

public:
    explicit Ftest(int m){
        mem =m;
        qDebug()<<"Ftest construct";}
    virtual ~Ftest(){qDebug()<<"Ftest del";}

    int mem;
};

class ft1:public Ftest
{
public:
   explicit ft1(int m,int n):Ftest(m)
    {
//        this->Ftest(m);
        qDebug()<<"ft1 construct"<<m;
    }
    ~ft1(){ qDebug()<<"ft1 del";}
};

class ft2:public Ftest
{
public:
   explicit ft2(int m):Ftest(m){qDebug()<<"ft2 construct";}
    ~ft2(){qDebug()<<"ft2 del";}
};
#endif // FTEST_H
