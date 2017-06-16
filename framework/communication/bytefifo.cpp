/*
 * 参考linux内核kfifo构建的fifo，如果只有一个生产者，一个消费者的情况下，
 * 不需要加锁，使用__fifo_get和__fifo_put即可。其他情况需要加锁，
 * 使用fifo_get和fifo_put.非Linux平台需要重新修改加锁机制。
 *
 * 作者：蒋俊杰
 * 最后修改：2015-3-26
*/
#define __DEBUG__
#ifdef __DEBUG__
#define debug_msg(fmt,...) do{\
    printf("[%s(%d)<%s>]\n",__FILE__,__LINE__,__FUNCTION__);\
    printf("\t\t\t");\
    printf((fmt),##__VA_ARGS__);\
    }while(0)
#else
#define debug_msg(fmt,args...)
#endif
#include <malloc.h>
#include <stdio.h>
#include <bytefifo.h>
#include <string.h>

#define SHORT_SIZE   2
#define CHAR_SIZE    1
#define INT_SIZE     4
#define FLOAT_SIZE   4
#define DOUBLE_SIZE  8


//判断x是否是2的次方
#define is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
//取a和b中最小值
#define min(a, b) (((a) < (b)) ? (a) : (b))
static inline unsigned int fls(unsigned int x)
{
    unsigned int position;
    unsigned int i;
    if(0 != x)
    {
        for (i = (x >> 1), position = 0; i != 0; ++position)
            i >>= 1;
    }
    else
    {
        position = -1;
    }
    return position+1;
}
static inline unsigned int roundup_pow_of_two(unsigned int x)
{
    return 1UL << fls(x - 1);
}



ByteFiFo::ByteFiFo(unsigned int m_size)
{
    buffer = NULL;
    if(!is_power_of_2(m_size))
    {
        debug_msg("size must be power of 2.\n");
        m_size = roundup_pow_of_two(m_size);
        debug_msg("size is be roundup to %d\n",m_size);
    }
    buffer = (unsigned char*)malloc(m_size);
    if(!buffer)
    {
        debug_msg("malloc erro!\n");
    }
    size = m_size;
    in = 0;
    out = 0;
}

ByteFiFo::~ByteFiFo()
{
    if(buffer!=NULL)
        free(buffer);
}

unsigned int ByteFiFo::len()
{
    return (in - out);
}

bool ByteFiFo::inQue(void *data, unsigned int len)
{
    unsigned int l;
    unsigned char *buf =(unsigned char *) data;
    l = size - in + out;
    if( len > l)
    {
        debug_msg("fifo have no such space!\t len is %d \t fifo.space is %d\n",len,l);
        return false;
    }
    else
    {
        l = min(len,size - (in & (size -1)));
        memcpy(buffer+(in & (size -1)),buf,l);
        memcpy(buffer,buf+l,len-l);
        in += len;
        return true;
    }
}

char ByteFiFo::getChar(unsigned int pos)
{
    unsigned int l;
    char ret;
    char* p = &ret;
    l = in - out;
    if(pos+CHAR_SIZE > l)
    {
        ret = 0;
        return ret;
    }
    else
    {
        l = min(CHAR_SIZE,size - ((out+pos) & (size -1)));
        memcpy(p,buffer+((out+pos) & (size -1)),l);
        memcpy(p+l,buffer,CHAR_SIZE-l);
        return ret;
    }

}

short ByteFiFo::getShort(unsigned int pos)
{
    unsigned int l;
    short ret;
    char* p = (char*)&ret;
    l = in - out;
    if(pos+SHORT_SIZE > l)
    {
        ret = 0;
        return ret;
    }
    else
    {
        l = min(SHORT_SIZE,size - ((out+pos) & (size -1)));
        memcpy(p,buffer+((out+pos) & (size -1)),l);
        memcpy(p+l,buffer,SHORT_SIZE-l);
        return ret;
    }
}

int ByteFiFo::getInt(unsigned int pos)
{
    unsigned int l;
    int ret;
    char* p = (char*)&ret;
    l = in - out;
    if(pos+INT_SIZE> l)
    {
        ret = 0;
        return ret;
    }
    else
    {
        l = min(INT_SIZE,size - ((out+pos) & (size -1)));
        memcpy(p,buffer+((out+pos) & (size -1)),l);
        memcpy(p+l,buffer,INT_SIZE-l);
        return ret;
    }
}

float ByteFiFo::getFloat(unsigned int pos)
{
    unsigned int l;
    float ret;
    char* p = (char*)&ret;
    l = in - out;
    if(pos+FLOAT_SIZE > l)
    {
        ret = 0;
        return ret;
    }
    else
    {
        l = min(FLOAT_SIZE,size - ((out+pos) & (size -1)));
        memcpy(p,buffer+((out+pos) & (size -1)),l);
        memcpy(p+l,buffer,FLOAT_SIZE-l);
        return ret;
    }
}

double ByteFiFo::getDouble(unsigned int pos)
{
    unsigned int l;
    double ret;
    char* p = (char*)&ret;
    l = in - out;
    if(pos+DOUBLE_SIZE > l)
    {
        ret = 0;
        return ret;
    }
    else
    {
        l = min(DOUBLE_SIZE,size - ((out+pos) & (size -1)));
        memcpy(p,buffer+((out+pos) & (size -1)),l);
        memcpy(p+l,buffer,DOUBLE_SIZE-l);
        return ret;
    }
}

bool ByteFiFo::getStr(char *str, unsigned int pos, unsigned int m_size)
{
    unsigned int l;
    char* p = str;
    l = in - out;
    if(pos+m_size > l)
    {
        return false;
    }
    else
    {
        l = min(m_size,size - ((out+pos) & (size -1)));
        memcpy(p,buffer+((out+pos) & (size -1)),l);
        memcpy(p+l,buffer,m_size-l);
        p[m_size]='\0';
        return true;
    }
}

bool ByteFiFo::getObj(void *obj, unsigned int pos, unsigned int m_size)
{
    unsigned int l;
    char* p = (char*)obj;
    l = in - out;
    if(pos+m_size > l)
    {
        return false;
    }
    else
    {
        l = min(m_size,size - ((out+pos) & (size -1)));
        memcpy(p,buffer+((out+pos) & (size -1)),l);
        memcpy(p+l,buffer,m_size-l);
        return true;
    }
}

bool ByteFiFo::outQue(unsigned int m_size)
{
    unsigned int l;
    l = in - out;
    if(m_size > l)
    {
        return false;
    }
    else
    {
        l = min(m_size,size - (out & (size -1)));
        out +=m_size;
        return true;
    }
}

bool ByteFiFo::outQue(char *data, int m_size)
{
    char* p = (char*)data;
    unsigned int l;
    l = in - out;
    if(m_size > l)
    {
        return false;
    }
    else
    {
        l = min(m_size,size - (out & (size -1)));
        memcpy(p,buffer+(out & (size -1)),l);
        memcpy(p+l,buffer,m_size-l);
        out +=m_size;
        return true;
    }
}
