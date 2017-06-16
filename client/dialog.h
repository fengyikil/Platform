#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>

#pragma pack(1)
struct HeadPack
{
   int len;
};
struct PackData
{
    int arg1;
    int arg2;
};
struct Pack
{
    struct HeadPack head;
    struct PackData data;
};

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void connected();
    void disconnected();
    void readyRead();
private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::Dialog *ui;
    QByteArray buf;
    struct Pack packRec;
    struct Pack packSend;
    QTcpSocket *socket;
};

#endif // DIALOG_H
