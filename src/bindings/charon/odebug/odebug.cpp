// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <lua/lua.hpp>
#include <charon/helper>

static int lua_charon_odebug_info( lua_State *L ) {
  lua_Debug info;

  lua_getstack(L, 2, &info);
  lua_getinfo(L, "Sl", &info);

  lua_pushstring(L, info.source);
  lua_pushinteger(L, info.currentline);

  return 2;
}

extern "C" {
  int luaopen_charon_odebug( lua_State *L ) {
    static const luaL_reg Map[] = {
      {"info", lua_charon_odebug_info},
      {NULL, NULL}
    };
    luaL_register(L, "odebug", Map);
    return 1;
  }
}
