// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <lua/lua.hpp>
#include <charon/base>
#include <charon/mvm>
#include <iostream>
#include <cstdio>

using charon::mvm;

int charonFileLoad(lua_State *L, const char * filename)
{
  int rv;

  rv = luaL_loadfile(L, filename);
  if (rv) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    return rv;
  }

  rv = lua_pcall(L, 0, 0, lua_gettop(L) - 1);
  if (rv) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    return rv;
  }

  return rv;
}

void charonConsolePrintAround(string &buffer)
{
  buffer = buffer.mid(1);
  buffer.prepend("print(");
  buffer.append(")");
}

bool charonConsoleIncrementLevel(string &row)
{
  /* if */
  if(row.startsWith("if ") or row.contains(" if ")) {
    return true;
  }

  /* for */
  if(row.startsWith("for ") or row.contains(" for ")) {
    return true;
  }

  /* while */
  if(row.startsWith("while ") or row.contains(" while ")) {
    return true;
  }

  /* function */
  if(row.startsWith("function ") or row.contains("function(")) {
    return true;
  }

  return false;
}

bool charonConsoleDecrementLevel(string &row)
{
  /* end */
  if(row.startsWith("end") or row.contains(" end ")) {
    return true;
  }

  return false;
}

void executeRoutine(lua_State *L)
{
  lua_settop(L, 0);
  int rv;
  lua_getglobal(L, "require");
  lua_pushstring(L, "arken.routine");
  rv = lua_pcall(L, 1, 1, 0);
  if (rv) {
    fprintf(stderr, "erro no inicio: %s\n", lua_tostring(L, -1));
    throw;
  }

  lua_getfield(L, -1, "run");
  lua_getglobal(L, "arg");

  if( lua_pcall(L, 1, 0, 0) != 0 ) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
  } else {
    //return 0;
  }
}

/* TODO
 1) level for if, while etc
 2) set up
 3) ctrl + r
*/
int charonConsoleLoad(lua_State *L)
{
  int rv = 0;
  int level = 0;
  char cmd[255];
  std::string line;
  string row;
  string buffer;

  while(true) {
    sprintf(cmd, "arken %i> ", level);
    mvm::log(cmd);

    std::getline(std::cin, line);
    row = line.c_str();

    if (level == 0) {
      buffer = line.c_str();
    } else {
      buffer.append(line.c_str());
      buffer.append("\n");
    }

    if (buffer.startsWith("=")) {
      charonConsolePrintAround(buffer);
    }

    if (charonConsoleIncrementLevel(row)) {
      buffer.append("\n");
      level ++ ;
    }

    if (charonConsoleDecrementLevel(row)) {
      level -- ;
    }

    if (level == 0) {
      rv  = luaL_loadstring(L, buffer);
      rv  = lua_pcall(L, 0, 0, 0);
      if (rv) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
      }
    }
    if (level < 0) {
      std::cout << "invalid end statement\n";
      level = 0;
    }
  }
  return rv;
}

int main(int argc, char * argv[])
{
  mvm::init(argc, argv);
  os::sleep(0.1); // waiting mvm output log

  int rv = 0;
  string  charonPath;
  string  task;
  string  arg1;
  charon::instance i = mvm::instance();
  lua_State  * L = i.state();

  if ( argc == 1 ) {
    return charonConsoleLoad(L);
  }

  if( os::exists(argv[1]) ) {
    return charonFileLoad(L, argv[1]);
  } else {
    if (string::contains(argv[1], ":")) {
      executeRoutine(L);
    } else {
      fprintf(stderr, "No such file or directory %s\n", argv[1]);
      return 1;
    }
  }

  return rv;
}
