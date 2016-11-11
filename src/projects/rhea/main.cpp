#include <iostream>
#include <luajit-2.0/lua.hpp>
#include <QtCore>
#include <QCoreApplication>
#include <OByteArray>
#include <oberon/helper>

int main(int argc, char * argv[])
{
  QCoreApplication app(argc, argv);

  lua_State * L = Oberon::init(argc, argv, app.applicationFilePath().toLocal8Bit().data());

  lua_settop(L, 0);
  lua_getglobal(L, "OBERON_PATH");

  QByteArray rhea = lua_tostring(L, 1);
  rhea.append("/lib/rhea.lua");

  int rv;
  rv = luaL_loadfile(L, rhea);
  if (rv) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    throw;
  }

  rv = lua_pcall(L, 0, 0, lua_gettop(L) - 1);
  if (rv) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    throw;
  }

  lua_settop(L, 0);
  lua_getglobal(L, "rhea");

  if( lua_pcall(L, 0, 0, lua_gettop(L) - 1 ) != 0 ) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
  } else {
    return 0;
  }

}