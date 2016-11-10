#include <iostream>
#include <luajit-2.0/lua.hpp>
#include <QtCore>
#include <QCoreApplication>
#include <OByteArray>
#include <QDebug>
#include <QStringList>
#include <oberon/helper>
#include <triton.h>
#include <QJsonObject>

int main(int argc, char * argv[])
{

  int threads = os::cores();
  QCoreApplication app(argc, argv);
  QByteArray path  = app.applicationFilePath().toLocal8Bit().data();

  lua_State * L = Oberon::init(argc, argv, path);
  triton_register(L);

  lua_settop(L, 0);
  lua_getglobal(L, "OBERON_PATH");

  QByteArray oberonPath = lua_tostring(L, 1);

  if( argc == 1 ) {
    fprintf(stderr, "missing param, see your triton file\n");
    throw;
  }

  QByteArray fileName;

  if( os::exists(argv[1]) ) {
    fileName.append(argv[1]);
  } else {
    fileName.prepend("triton/");
    fileName.append(string::replace(argv[1], '.', '/'));
    if( ! os::exists(fileName) ) {
      fileName.prepend("/");
      fileName.prepend(oberonPath);
    }
    fileName.append(".lua");
  }

  int rv;
  rv = luaL_loadfile(L, fileName);
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
  lua_getglobal(L, "triton_start");
  if( lua_pcall(L, 0, 0, lua_gettop(L) - 1 ) != 0 ) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    throw;
  }

  QFile config("config/triton.json");
  if( config.exists() ) {
    config.open(QIODevice::ReadOnly);
    QJsonParseError * error = new QJsonParseError();
    QJsonDocument json = QJsonDocument::fromJson(config.readAll(), error);
    if( error->error != 0 ) {
      qDebug() << error->errorString();
      throw;
    }
    QJsonObject object = json.object();
    threads = object.value("threads").toInt();
  }

  QThreadPool * pool = new QThreadPool;
  pool->setMaxThreadCount(threads);

  for(int i = 0; i < threads; i++ ) {
    pool->start(new Triton(argc, argv, path, fileName));
  }

  pool->waitForDone();

  lua_settop(L, 0);
  lua_getglobal(L, "triton_stop");
  if( lua_pcall(L, 0, 0, lua_gettop(L) - 1 ) != 0 ) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    throw;
  }

  return 0;
}
