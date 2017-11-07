// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CHARONMVM_H
#define CHARONMVM_H

#include <deque>
#include <lua/lua.hpp>
#include <charon/base>

namespace charon
{

class instance;

class mvm {

  friend class instance;

  public:
  class data {

    friend class mvm;
    friend class instance;

    private:
    lua_State * m_State;
    int         m_version;
    int         m_gc;

    public:
    data();
    ~data();
    lua_State * state();
    int version();
  };


  static int s_gc;
  static int s_version;
  static ByteArray s_charonPath;
  static ByteArray s_profilePath;
  static ByteArray s_dispatchPath;
  static QMutex    s_mutex;
  static std::deque<mvm::data *> * s_container;
  private:

  static void push(mvm::data *);
  static mvm::data * takeFirst();

  mvm() {};
  ~mvm() {};

  public:
  static void init(QCoreApplication *app);
  static void reload();
  static int  version();
  static int  gc();
  static int  clear();
  static charon::instance instance();

};

class instance {
  mvm::data * m_data;
  public:
  instance(mvm::data * data);
  ~instance();
  lua_State * state();
};

}
#endif // CHARONMVM_H
