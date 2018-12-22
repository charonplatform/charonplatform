// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef _CHARON_REGEX_
#define _CHARON_REGEX_

#include <charon/ByteArrayList>

using List = charon::string::List;

namespace charon
{

class regex {
  public:
  static bool ematch(const char * string, const char * regex);
  static int index(const char * string, const char * regex);
  static int index(const char * string, const char * regex, int offset);
  static List * split(const char * string, const char * regex);
  static bool match(const char * string, const char * regex);
  static char * replace(const char * string, const char * regex, const char * after);
  static List * scan(const char * string, const char * regex);
};

}

#endif
