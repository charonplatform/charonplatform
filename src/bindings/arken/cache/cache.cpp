// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <lua/lua.hpp>
#include <arken/cache>

char * json_lock_encode(lua_State *L);
void   json_lock_decode(lua_State *L, const char * data);

using arken::cache;

static int arken_cache_value( lua_State *L ) {
  const char * key   = luaL_checkstring(L, 1);
  const char * value = cache::value(key);
  if( value == 0 ) {
    lua_pushnil(L);
  } else {
    json_lock_decode(L, value);
  }
  return 1;
}

static int arken_cache_insert( lua_State *L ) {
  const char * key   = luaL_checkstring(L, 1);
  int expires = -1;
  if(lua_gettop(L) == 3) { /* número de argumentos */
    expires = lua_tointeger(L, 3);
    lua_remove(L, 3);
  }
  char * value = json_lock_encode(L);
  cache::insert(key, value, expires);
  delete[] value;
  return 1;
}

static int arken_cache_remove( lua_State *L ) {
  const char * key   = luaL_checkstring(L, 1);
  cache::remove(key);
  return 0;
}

extern "C" {
  int luaopen_arken_cache( lua_State *L ) {
    static const luaL_reg Map[] = {
      {"value",  arken_cache_value},
      {"insert", arken_cache_insert},
      {"remove", arken_cache_remove},
      {NULL, NULL}
    };
    luaL_newmetatable(L, "cache");
    luaL_register(L, NULL, Map);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    return 1;
  }
  int luaopen_arken_cache( lua_State *L ) {
    static const luaL_reg Map[] = {
      {"value",  arken_cache_value},
      {"insert", arken_cache_insert},
      {"remove", arken_cache_remove},
      {NULL, NULL}
    };
    luaL_newmetatable(L, "cache");
    luaL_register(L, NULL, Map);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    return 1;
  }
}
