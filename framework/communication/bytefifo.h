#ifndef __FIFO_H__
#define __FIFO_H__

#define DEFLAUT_NUM 1024


class ByteFiFo
{
public:
    ByteFiFo(unsigned int m_size = DEFLAUT_NUM);
    ~ByteFiFo();
    unsigned int len();
    bool inQue(void *data,unsigned int len);
    char getChar(unsigned int pos);
    short getShort(unsigned int pos);
    int getInt(unsigned int pos);
    float getFloat(unsigned int pos);
    double getDouble(unsigned int pos);

    bool getStr(char *str,unsigned int pos,unsigned int m_size);
    bool getObj(void *obj,unsigned int pos,unsigned int m_size);
    bool outQue(unsigned int m_size);
    bool outQue(char* data,int m_size);
//    ~fifo();
//private:
    unsigned char  *buffer;
    unsigned int size;
    unsigned int in;
    unsigned int out;
};

//extern struct fifo* fifo_init(unsigned int size);
//extern void fifo_free(struct fifo* f);
//extern void __fifo_reset(struct fifo *f);
//extern unsigned int __fifo_get(struct fifo* f,void *buf,unsigned int len);
//extern unsigned int __fifo_put(struct fifo* f,void *buf,unsigned int len);
//extern unsigned int __fifo_len(struct fifo* f);

#endif
