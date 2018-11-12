// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef _CHARON_SERVICE_
#define _CHARON_SERVICE_

#include <charon/base>
#include <charon/cache>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>

namespace charon
{
  class service {

    private:
    static void run(char * uuid, char * fileName);
    int  m_version;
    bool m_quit;
    static int           s_version;
    static char        * s_dirName;
    static std::mutex  * s_mutex;
    static std::vector<std::string> * s_services;

    public:
    static char * start(const char * fileName);
    static void load(const char * dirName);
    static void load();
    bool loop(int secs);
    void quit();
    service();

  };
}

#endif // CHARONSERVICE_H
