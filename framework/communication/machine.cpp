#include "stdio.h"
#include <string>
#include <stdarg.h>
#include "machine.h"
#include "communication.h"

LuaMachine::LuaMachine(const char *file, regist_callback rcfun){
    mState = NULL;
    open_file(file,rcfun);
}

LuaMachine::~LuaMachine()
{
    printf("~LuaMachine\n");
    close();
}

bool LuaMachine::open_file(const char *file, regist_callback rcfun)
{
    if (mState != NULL)
        lua_close(mState);
    mState = luaL_newstate();
    if (NULL != mState)
    {
        luaL_openlibs(mState);
        //        mStatus = true;
        if(rcfun!=NULL)
            (*rcfun)(mState);
    }
    else
    {
        //        mStatus = false;
        return false;
    }
    int bRet = luaL_loadfile(mState, file);
    if (bRet)
    {
        lua_close(mState);
        return false;
    }
    bRet = lua_pcall(mState, 0, 0, 0);
    if (bRet)
    {
        lua_close(mState);
        return false;
    }
    return true;
}



void LuaMachine::close()
{
    if(mState!=NULL)
        lua_close(mState);
}

void LuaMachine::nc_call_func(const char *func, const char *sig, ...)
{
    va_list vl;
    int narg, nres;   /* number of arguments and results */
    //	//qDebug() << "lua_gettop is" << lua_gettop(mState);
    va_start(vl, sig);
    lua_getglobal(mState, func);  /* get function */

    /* push arguments */
    narg = 0;
    while (*sig) {    /* push arguments */
        switch (*sig++) {
        case 'b':/* boolean argument*/
            lua_pushboolean(mState, va_arg(vl, bool));
            break;

        case 'i':  /* int argument */
            lua_pushinteger(mState, va_arg(vl, int));
            break;

        case 'd':  /* double argument */
            lua_pushnumber(mState, va_arg(vl, double));
            break;

        case 's':  /* string argument */
            lua_pushstring(mState, va_arg(vl, char *));
            break;
        case 'l': /*light userdata*/
            lua_pushlightuserdata(mState, va_arg(vl, void *));
            break;
        case '>':
            goto endwhile;

        default:
            break;
            //error(mState, "invalid option (%c)", *(sig - 1));
        }
        narg++;
        luaL_checkstack(mState, 1, "too many arguments");
    }
endwhile:

    /* do the call */
    nres = strlen(sig);  /* number of expected results */
    if (lua_pcall(mState, narg, nres, 0) != 0)  /* do the call */
    {
        //qDebug() << "lua_pcal erro";
    }
    //error(mState, "error running function `%s': %s",func, lua_tostring(mState, -1));

    /* retrieve results */
    nres = -nres;     /* stack index of first result */

    while (*sig) {    /* get results */
        ////qDebug() <<"nres is"  <<nres<<"type is"<<lua_type(mState, nres);
        switch (*sig++) {

        case 'b':/* boolean argument*/
            if (!lua_isboolean(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(mState, "wrong result type");
            *va_arg(vl, bool *) = lua_tonumber(mState, nres);
            break;

        case 'i':  /* int result */
            if (!lua_isinteger(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }

            //error(L, "wrong result type");
            *va_arg(vl, int *) = (int)lua_tointeger(mState, nres);
            break;

        case 'd':  /* double result */
            if (!lua_isnumber(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(mState, "wrong result type");
            *va_arg(vl, double *) = lua_tonumber(mState, nres);
            break;

        case 's':  /* string result */
            if (!lua_isstring(mState, nres))
            {
                //qDebug() << "wrong result type"<< lua_type(mState, nres);
            }
            //error(L, "wrong result type");
            *va_arg(vl, const char **) = lua_tostring(mState, nres);
            break;
        case  'l':
            if (!lua_islightuserdata(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);

            }
            //error(L, "wrong result type");
            *va_arg(vl, void **) = lua_touserdata(mState, nres);
            break;

        default:
            //error(mState, "invalid option (%c)", *(sig - 1));
            break;
        }
        nres++;
    }
    va_end(vl);
}

void LuaMachine::call_func(const char *func, const char *sig, ...)
{
    lua_settop(mState, 0);
    va_list vl;
    int narg, nres;   /* number of arguments and results */
    //	//qDebug() << "lua_gettop is" << lua_gettop(mState);
    va_start(vl, sig);
    lua_getglobal(mState, func);  /* get function */

    /* push arguments */
    narg = 0;
    while (*sig) {    /* push arguments */
        switch (*sig++) {
        case 'b':/* boolean argument*/
            lua_pushboolean(mState, va_arg(vl, bool));
            break;

        case 'i':  /* int argument */
            lua_pushinteger(mState, va_arg(vl, int));
            break;

        case 'd':  /* double argument */
            lua_pushnumber(mState, va_arg(vl, double));
            break;

        case 's':  /* string argument */
            lua_pushstring(mState, va_arg(vl, char *));
            break;
        case 'l': /*light userdata*/
            lua_pushlightuserdata(mState, va_arg(vl, void *));
            break;
        case '>':
            goto endwhile;

        default:
            break;
            //error(mState, "invalid option (%c)", *(sig - 1));
        }
        narg++;
        luaL_checkstack(mState, 1, "too many arguments");
    }
endwhile:

    /* do the call */
    nres = strlen(sig);  /* number of expected results */
    if (lua_pcall(mState, narg, nres, 0) != 0)  /* do the call */
    {
        //qDebug() << "lua_pcal erro";
    }
    //error(mState, "error running function `%s': %s",func, lua_tostring(mState, -1));

    /* retrieve results */
    nres = -nres;     /* stack index of first result */

    while (*sig) {    /* get results */
        ////qDebug() <<"nres is"  <<nres<<"type is"<<lua_type(mState, nres);
        switch (*sig++) {

        case 'b':/* boolean argument*/
            if (!lua_isboolean(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(mState, "wrong result type");
            *va_arg(vl, bool *) = lua_tonumber(mState, nres);
            break;

        case 'i':  /* int result */
            if (!lua_isinteger(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(L, "wrong result type");
            *va_arg(vl, int *) = (int)lua_tointeger(mState, nres);
            break;

        case 'd':  /* double result */
            if (!lua_isnumber(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(mState, "wrong result type");
            *va_arg(vl, double *) = lua_tonumber(mState, nres);
            break;

        case 's':  /* string result */
            if (!lua_isstring(mState, nres))
            {
                //qDebug() << "wrong result type"<< lua_type(mState, nres);
            }
            //error(L, "wrong result type");
            *va_arg(vl, const char **) = lua_tostring(mState, nres);
            break;
        case  'l':
            if (!lua_islightuserdata(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(L, "wrong result type");
            *va_arg(vl, void **) = lua_touserdata(mState, nres);
            break;

        default:
            //error(mState, "invalid option (%c)", *(sig - 1));
            break;
        }
        nres++;
    }
    va_end(vl);
}
void LuaMachine::clear_stack()
{
    lua_settop(mState, 0);
}

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

void LuaMachine::mesgRec(BaseCommunication* comt)
{
    int res;
    qDebug()<<"mesgRec come in"<<QThread::currentThreadId();
    QByteArray buf(comt->rbfifo->len(),'\0');

//    qDebug()<<comt->rbfifo->getInt(0);
//    qDebug()<<comt->rbfifo->getInt(4);
//    qDebug()<<comt->rbfifo->getInt(8);

call_func("handleMesg","l>i",comt,&res);

//    comt->rbfifo->outQue(buf.data(),comt->rbfifo->len());
//     Pack* pk = (Pack*)buf.data();

//     qDebug()<<pk->head.len;
//     qDebug()<<pk->data.arg1;
//     qDebug()<<pk->data.arg2;

//    qDebug()<<"rec is"<<buf;
//    char str[]="hhhh";
//    comt->sbfifo->inQue(str,4);

//    call_func("test_run",">i",&res);
//    printf("mesgRec1 : res is %d\n",res);

//    call_func("test_commu","l>i",comt,&res);
//    printf("mesgRec2 : res is %d\n",res);

    //   emit comt->lm->mesgSend();
}
