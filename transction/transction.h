#ifndef TRANSCTION_H
#define TRANSCTION_H

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
class Transction
{

public:
    Transction();
    Pack p;
    struct PackData data1;
    struct PackData data2;
};

#endif // TRANSCTION_H
