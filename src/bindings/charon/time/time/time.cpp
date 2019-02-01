// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <lua/lua.hpp>
#include <charon/base>

using charon::time::Time;

/**
 * checkTime
 */

Time *
checkTime( lua_State *L ) {
  return *(Time **) luaL_checkudata(L, 1, "Time.metatable");
}

Time *
checkTime( lua_State *L, int i ) {
  return *(Time **) luaL_checkudata(L, i, "Time.metatable");
}

/**
 * ClassMethods
 */

static int
charon_TimeClassMethodCurrentTime( lua_State *L ) {
  Time **ptr = (Time **)lua_newuserdata(L, sizeof(Time*));
  *ptr = new Time(Time::currentTime());
  luaL_getmetatable(L, "Time.metatable");
  lua_setmetatable(L, -2);
  return 1;
}

static int
charon_TimeClassMethodFromString( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  const char * format = luaL_checkstring(L, 2);
  Time **ptr = (Time **)lua_newuserdata(L, sizeof(Time*));
  *ptr= new Time(Time::fromString(string, format));
  luaL_getmetatable(L, "Time.metatable");
  lua_setmetatable(L, -2);
  return 1;
}

static int
charon_TimeClassMethodParse( lua_State *L ) {
  const char * string = luaL_checkstring(L, 1);
  Time * time = Time::parse(string);
  if( time == 0 ) {
    lua_pushnil(L);
  } else {
    Time **ptr = (Time **)lua_newuserdata(L, sizeof(Time*));
    *ptr = time;
    luaL_getmetatable(L, "Time.metatable");
    lua_setmetatable(L, -2);
  }
  return 1;
}

static const luaL_reg TimeClassMethods[] = {
  {"parse", charon_TimeClassMethodParse},
  {"fromString", charon_TimeClassMethodFromString},
  {"currentTime", charon_TimeClassMethodCurrentTime},
  {NULL, NULL}
};

void static
registerTimeClassMethods( lua_State *L ) {
  luaL_newmetatable(L, "Time");
  luaL_register(L, NULL, TimeClassMethods);
  lua_pushvalue(L, -1);
  lua_setfield(L, -1, "__index");
}

/**
 * InstanceMethods
 */

static int
charon_TimeInstanceMethodDestruct( lua_State *L ) {
  Time *udata = checkTime( L );
  delete udata;
  return 0;
}

static int
charon_TimeInstanceMethodToString( lua_State *L ) {
  Time *dt    = checkTime( L );
  const char * str;
  if(lua_isstring(L, 2)) {
    str = luaL_checkstring(L, 2);
  } else {
    str = "hh:mm:ss.z";
  }

  lua_pushstring(L, dt->toString(str));
  return 1;
}

static int
charon_TimeInstanceMethodConcat( lua_State *L ) {
  Time *dt;
  string concat;
  const char * str;
  const char * format = "hh:mm:ss.z";
  if(lua_isstring(L, 1)) {
    str = lua_tostring(L, 1);
    dt  = checkTime( L, 2 );
    concat = dt->toString(format).prepend(str);
  } else {
    dt  = checkTime( L, 1 );
    str = lua_tostring(L, 2);
    concat = dt->toString(format).append(str);
  }
  lua_pushstring(L, concat);
  return 1;
}

static int
charon_TimeInstanceMethodEqual( lua_State *L ) {
  Time *dt1 = checkTime( L );
  Time *dt2 = *(Time **) luaL_checkudata(L, 2, "Time.metatable");

  lua_pushboolean(L, dt1 == dt2);
  return 1;
}

static int
charon_TimeInstanceMethodLessThan( lua_State *L ) {
  Time *dt1 = checkTime( L );
  Time *dt2 = *(Time **) luaL_checkudata(L, 2, "Time.metatable");

  lua_pushboolean(L, dt1 < dt2);
  return 1;
}

static int
charon_TimeInstanceMethodAddSecs( lua_State *L ) {
  Time *dt    = checkTime( L );
  qint64 days = luaL_checkinteger(L, 2);
  Time other  = dt->addSecs(days);

  Time **ptr = (Time **)lua_newuserdata(L, sizeof(Time*));
  *ptr= new Time(other);
  luaL_getmetatable(L, "Time.metatable");
  lua_setmetatable(L, -2);

  return 1;
}

static int
charon_TimeInstanceMethodIsNull( lua_State *L ) {
  Time *dt   = checkTime( L );
  lua_pushboolean(L, dt->isNull());
  return 1;
}

static int
charon_TimeInstanceMethodIsValid( lua_State *L ) {
  Time *dt   = checkTime( L );
  lua_pushboolean(L, dt->isValid());
  return 1;
}

static const
luaL_reg TimeInstanceMethods[] = {
  {"isValid", charon_TimeInstanceMethodIsValid},
  {"isNull", charon_TimeInstanceMethodIsNull},
  {"addSecs", charon_TimeInstanceMethodAddSecs},
  {"toString", charon_TimeInstanceMethodToString},
  {"__lt", charon_TimeInstanceMethodLessThan},
  {"__eq", charon_TimeInstanceMethodEqual},
  {"__tostring", charon_TimeInstanceMethodToString},
  {"__concat", charon_TimeInstanceMethodConcat},
  {"__gc", charon_TimeInstanceMethodDestruct},
  {NULL, NULL}
};

void static
registerTimeInstanceMethods( lua_State *L ) {
  luaL_newmetatable(L, "Time.metatable");
  luaL_register(L, NULL, TimeInstanceMethods);
  lua_pushvalue(L, -1);
  lua_setfield(L, -1, "__index");
}

extern "C" {
  int
  luaopen_charon_time_Time( lua_State *L ) {
    registerTimeInstanceMethods(L);
    registerTimeClassMethods(L);
    return 1;
  }
}
