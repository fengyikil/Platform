#include "communication.h"
#include "machine.h"
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


int  fk_comu_getId(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int id = bc->id;
    lua_pushinteger(L, id);
    return 1;
}

int  fk_comu_getLen(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int len = bc->rbfifo->len();
    lua_pushinteger(L, len);
    return 1;
}
int  fk_comu_getChar(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int pos = lua_tointeger(L,2);
    int c = bc->rbfifo->getChar(pos);
    lua_pushinteger(L, c);
    return 1;
}
int  fk_comu_getShort(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int pos = lua_tointeger(L,2);
    int c = bc->rbfifo->getShort(pos);
    lua_pushinteger(L, c);
    return 1;
}
int  fk_comu_getInt(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int pos = lua_tointeger(L,2);
    int c = bc->rbfifo->getShort(pos);
    lua_pushinteger(L, c);
    return 1;
}
int  fk_comu_getFloat(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int pos = lua_tointeger(L,2);
    float c = bc->rbfifo->getFloat(pos);
    lua_pushnumber(L,c);
    return 1;
}
int  fk_comu_getDouble(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int pos = lua_tointeger(L,2);
    double c = bc->rbfifo->getDouble(pos);
    lua_pushnumber(L,c);
    return 1;
}
int  fk_comu_getStr(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int pos = lua_tointeger(L,2);
    int size = lua_tointeger(L,3);
    char* str = (char*)malloc(size+1);

    bc->rbfifo->getStr(str,pos,size);
    lua_pushstring(L,str);
    free(str);
    return 1;
}
int fk_comu_getObj(lua_State* L)
{
    BaseCommunication* bc =(BaseCommunication*)lua_touserdata(L,1);
    int pos = lua_tointeger(L,2);
    int size = lua_tointeger(L,3);
    void* obj = nullptr;
    obj = lua_touserdata(L,3);
    if(obj!=nullptr)
       bc->rbfifo->getObj(obj,pos,size);
    else
       qDebug()<<"fk_comu_getObj:obj is nullptr";
    return 1;
}

void lua_communication_register(lua_State *L)
{
    lua_register(L, "fk_comu_getId", fk_comu_getId);
    lua_register(L, "fk_comu_getLen", fk_comu_getLen);
    lua_register(L, "fk_comu_getChar", fk_comu_getChar);
    lua_register(L, "fk_comu_getShort", fk_comu_getShort);
    lua_register(L, "fk_comu_getInt", fk_comu_getInt);
    lua_register(L, "fk_comu_getFloat", fk_comu_getFloat);
    lua_register(L, "fk_comu_getDouble", fk_comu_getDouble);
    lua_register(L, "fk_comu_getStr", fk_comu_getStr);
    lua_register(L, "fk_comu_getObj", fk_comu_getObj);
}


