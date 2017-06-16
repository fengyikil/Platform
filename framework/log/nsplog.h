//#ifndef NSPLOG_H
//#define NSPLOG_H

//#include <QObject>
//#include <QString>
//#include <QMutex>
//#include <QFile>
//#include <QMap>
//enum
//{
//    LOG_TYPE_NSG=0,
//    LOG_TYPE_ALG=1,
//};
//enum
//{
//    LOG_INFO=0x00000001,
//    LOG_ERR=0x00000003,
//    LOG_DEBUG=0x00000007,

//    LOG_CLOSE=0x00000008,
//    LOG_ALG1=0x00000010,
//    LOG_ALG2=0x00000020,
//    LOG_ALG3=0x00000040,
//};

//class LogManage;

//class NspLog
//{
//public:
//    friend class LogManage;
//    explicit NspLog(QString name,QString f=NULL);
//    ~NspLog();
////    void outPut(int flag,QString msg);
//    void logInfo(QString msg);
//    void logErr(QString msg);
//    void logDebug(QString msg);

//    void logAlg1(QString msg);
//    void logAlg2(QString msg);
//    void logAlg3(QString msg);

////    setFileName(QString f);
////    int type;
//    LogManage* mange;
//    QString name;
//    QFile file;
//    bool console;
//    bool signal;
//    QMutex mtx;

//public slots:
//};

//class LogManage : public QObject
//{
//     Q_OBJECT
//public:
//    explicit LogManage();
//    QMap<QString,NspLog*> logMap;
//signals:
//    void send(int level,QString msg);
//};

//extern void set_norFlags(int flags);

//extern void set_algFlags(int flags);


//#endif // NSPLOG_H
