#include "transction.h"

struct HeadPack
{
   int len;
};
struct PackData
{
  char arg1;
  short arg2;
  int arg3;
  float arg4;
  double arg5;
};
struct Pack
{
    struct HeadPack head;
    struct PackData data;
};

Transction::Transction()
{
}
