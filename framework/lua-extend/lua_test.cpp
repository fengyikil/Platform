#include "communication.h"
#include "machine.h"
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
//注册该模块函数到 lua

int  lua_test(lua_State* L)
{
    int a = lua_tointeger(L, 1);
    double b = lua_tointeger(L, 2);
    char* str = (char*)malloc(20);
    strcpy(str,"hjhhjhhhjhj");

    int res = a * b ;
    lua_pushinteger(L, res);
    lua_pushstring(L,str);
    strcpy(str,"aaaaaaaaa");
    lua_pushstring(L,str);
    free(str);
    return 3;
}
int  fk_test_commu(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    bc->test();
    emit bc->lm->mesgSend();
    return 1;
}

void lua_test_register(lua_State *L)
{
    lua_register(L, "fk_test", lua_test);
    lua_register(L, "fk_test_commu", lua_test);
}
