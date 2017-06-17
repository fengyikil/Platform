#include "transction.h"
extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <lualib.h>
#include <math.h>
}

Transction gtranc;


Transction::Transction()
{
}
static int trans_get_a1(lua_State *L)
{
    lua_pushlightuserdata(L,(void*)&gtranc.data1);
    return 1;
}
static int trans_get_a2(lua_State *L)
{
    lua_pushlightuserdata(L,(void*)&gtranc.data2);
    return 1;
}
static int trans_cal(lua_State *L)
{
    int res1 = gtranc.data1.arg1 + gtranc.data2.arg1;
    int res2 = gtranc.data1.arg2 + gtranc.data2.arg2;
    lua_pushinteger(L, res1);
    lua_pushinteger(L, res2);
    return 2;
}

extern "C" int __declspec(dllexport) luaopen_transction(lua_State *L)
{
//    luaL_newlib(L, mylib);
    lua_register(L, "trans_get_a1", trans_get_a1);
    lua_register(L, "trans_get_a2", trans_get_a2);
    lua_register(L, "trans_cal", trans_cal);
    return 1;
}
