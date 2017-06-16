#ifndef LUA_WRAP_H
#define LUA_WRAP_H
#include <QObject>
#include "communication.h"
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

typedef void(*regist_callback)(lua_State*);

//框架操作函数注册到lua虚拟机的测试函数
extern void  lua_test_register(lua_State *L);
extern void  lua_communication_register(lua_State* L);

void inline default_regist_callback(lua_State *L)
{
    lua_test_register(L);
    lua_communication_register(L);
}


class BaseCommunication;
class LuaMachine:public QObject
{
    Q_OBJECT
public:
    LuaMachine(const char* file="../../framework_run/script/test.lua",regist_callback rcfun=default_regist_callback);
    ~LuaMachine();
    bool open_file(const char* file,regist_callback rcfun);
    //注册到 lua虚拟机的c函数，用于 lua-extend

    void close();
    /*不清栈调用lua函数*/
    void nc_call_func(const char *func, const char *sig, ...);

    /*清栈、调用lua函数*/
    void call_func(const char *func, const char *sig, ...);
    /*手动清栈*/
    void clear_stack();


    lua_State* mState;
signals:
    void mesgSend();
public  slots:
    void mesgRec(BaseCommunication*);
};

#endif // !LUA_WRAP_H
