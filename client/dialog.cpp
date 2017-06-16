#include "dialog.h"
#include "ui_dialog.h"




Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QRegExp rx("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    ui->lineEdit_ip->setValidator(new QRegExpValidator(rx,this)); //设置
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(connected()), this, SLOT(connected()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::connected()
{
  ui->pushButton_connect->setText("disconnect");
}

void Dialog::disconnected()
{
    ui->pushButton_connect->setText("connect");
}

void Dialog::readyRead()
{
 buf.append(socket->readAll());
 char* p = (char*)&packRec;
 if(buf.length()>=sizeof(struct Pack))
 {
     memcpy(p,buf.data(),sizeof(struct Pack));
     buf.remove(0,sizeof(struct Pack));
     ui->label_rarg1->setText(QString::number(packRec.data.arg1));
     ui->label_rarg2->setText(QString::number(packRec.data.arg1));
 }
}

void Dialog::on_pushButton_connect_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    int port = ui->lineEdit_port->text().toInt();
    socket->connectToHost(ip,port);

    if(!socket->waitForConnected(5000))
    {
       qDebug() << "Error: " <<  socket->errorString();
    }
}

void Dialog::on_pushButton_send_clicked()
{
    packSend.head.len = sizeof(struct PackData);
    packSend.data.arg1 = ui->lineEdit_arg1->text().toInt();
    packSend.data.arg2 = ui->lineEdit_arg2->text().toInt();

    char* p = (char*)&packSend;
    if(socket->isOpen())
        socket->write(p,sizeof(struct Pack));
}
