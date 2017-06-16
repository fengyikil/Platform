#ifndef FKMANAGE_H
#define FKMANAGE_H

#include <QObject>
#include <QThread>
#include<QList>



class ManageComm;
class LuaMachine;

class FkThread:public QThread
{
public:
    FkThread();
};

class FkManage : public QObject
{
    Q_OBJECT
public:
    explicit FkManage(QObject *parent = 0);
    ~FkManage();
signals:

public slots:
    //程序安全退出
    void exit();
private:
    ManageComm* magcm;
    LuaMachine* lm;
};


#endif // FKMANAGE_H
