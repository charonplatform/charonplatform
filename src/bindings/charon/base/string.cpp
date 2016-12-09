// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <lua/lua.hpp>
#include <charon/helper>

static int lua_charon_string_append( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  const char *str    = luaL_checkstring(L, 2);
  char *result = string::append(string, str);
  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

static int lua_charon_string_camelcase( lua_State *L ) {
  char * result;
  const char *string = luaL_checkstring(L, 1);
  bool  flag = false;

  if(lua_gettop(L) == 2) { /* número de argumentos */
    flag =  lua_toboolean(L, 2);
  }

  result = string::camelcase(string, flag);

  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

static int lua_charon_string_capitalize( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  char *result = string::capitalize(string);
  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

static int lua_charon_string_contains( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  const char *str    = luaL_checkstring(L, 2);
  bool result        = string::contains(string, str);
  lua_pushboolean(L, result);
  return 1;
}

static int lua_charon_string_endsWith( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  const char *str    = luaL_checkstring(L, 2);
  bool result        = string::endsWith(string, str);
  lua_pushboolean(L, result);
  return 1;
}

static int lua_charon_string_escape( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  char * result      = string::escape(string);
  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

static int lua_charon_string_escapeHtml( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  char * result      = string::escapeHtml(string);
  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

static int lua_charon_string_indexOf( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  const char *str    = luaL_checkstring(L, 2);
  int result = string::indexOf(string, str);
  lua_pushnumber(L, result);
  return 1;
}

static int lua_charon_string_insert( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  int len            = luaL_checkinteger(L, 2);
  const char *ba     = luaL_checkstring(L, 3);
  char *result = string::insert(string, len, ba);
  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

static int lua_charon_string_lastIndexOf( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  const char *str    = luaL_checkstring(L, 2);
  int result = string::lastIndexOf(string, str);
  lua_pushnumber(L, result);
  return 1;
}

static int lua_charon_string_left( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  int    len    =  luaL_checkinteger(L, 2);
  char * result = string::left(string, len);
  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

static int lua_charon_string_mid( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  int pos      =  luaL_checkinteger(L, 2);
  int len;
  if(lua_gettop(L) == 3) { /* número de argumentos */
    len =  luaL_checkinteger(L, 3);
  } else {
    len = -1;
  }
  char *result = string::mid(string, pos, len);
  lua_pushstring(L, result);  /* push result */
  delete[] result;
  return 1;
}

static int lua_charon_string_normalize( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  char * result       = string::normalize(string);
  lua_pushstring(L, result);  /* push result */
  delete[] result;
  return 1;
}

static int lua_charon_string_replace( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  const char * before = luaL_checkstring(L, 2);
  const char * after  = luaL_checkstring(L, 3);
  char * result       = string::replace(string, before[0], after[0]);
  lua_pushstring(L, result);  /* push result */
  delete[] result;
  return 1;
}

static int lua_charon_string_repeated( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  int    times  =  luaL_checkinteger(L, 2);
  char * result = string::repeated(string, times);
  lua_pushstring(L, result);  /* push result */
  delete[] result;
  return 1;
}

static int lua_charon_string_right( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  int    len    =  luaL_checkinteger(L, 2);
  char * result = string::right(string, len);
  lua_pushstring(L, result);  /* push result */
  delete[] result;
  return 1;
}

static int lua_charon_string_simplified( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  char * result = string::simplified(string);
  lua_pushstring(L, result);  /* push result */
  delete[] result;
  return 1;
}

static int lua_charon_string_startsWith( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  const char * ba     = luaL_checkstring(L, 2);
  bool result         = string::startsWith(string, ba);
  lua_pushboolean(L, result);  /* push result */
  return 1;
}

static int lua_charon_string_swap( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  const char * before = luaL_checkstring(L, 2);
  const char * after  = luaL_checkstring(L, 3);
  char * result       = string::swap(string, before, after);
  lua_pushstring(L, result);  /* push result */
  delete[] result;
  return 1;
}


static int lua_charon_string_trimmed( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  char * result       = string::trimmed(string);
  lua_pushstring(L, result);  /* push result */
  delete[] result;
  return 1;
}

static int lua_charon_string_truncate( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  int        pos     = luaL_checkinteger(L, 2);
  char      * result = string::truncate(string, pos);
  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

static int lua_charon_string_underscore( lua_State *L ) {
  const char *string = luaL_checkstring(L, 1);
  char      * result = string::underscore(string);
  lua_pushstring(L, result);
  delete[] result;
  return 1;
}

int luaopen_charon_string( lua_State *L ) {
  static const luaL_reg Map[] = {
    {"append",      lua_charon_string_append},
    {"camelcase",   lua_charon_string_camelcase},
    {"capitalize",  lua_charon_string_capitalize},
    {"contains",    lua_charon_string_contains},
    {"endsWith",    lua_charon_string_endsWith},
    {"escape",      lua_charon_string_escape},
    {"escapeHtml",  lua_charon_string_escapeHtml},
    {"indexOf",     lua_charon_string_indexOf},
    {"insert",      lua_charon_string_insert},
    {"left",        lua_charon_string_left},
    {"lastIndexOf", lua_charon_string_lastIndexOf},
    {"mid",         lua_charon_string_mid},
    {"normalize",   lua_charon_string_normalize},
    {"repeated",    lua_charon_string_repeated},
    {"replace",     lua_charon_string_replace},
    {"right",       lua_charon_string_right},
    {"simplified",  lua_charon_string_simplified},
    {"startsWith",  lua_charon_string_startsWith},
    {"swap",        lua_charon_string_swap},
    {"trimmed",     lua_charon_string_trimmed},
    {"truncate",    lua_charon_string_truncate},
    {"underscore",  lua_charon_string_underscore},
    {NULL, NULL}
  };
  luaL_register(L, "string", Map);
  return 1;
}