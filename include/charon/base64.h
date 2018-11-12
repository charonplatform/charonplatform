// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef _CHARON_BASE64_
#define _CHARON_BASE64_

namespace charon
{

class base64 {
  public:
  static char * decode(const char * data);
  static char * encode(const char * data, int len);
  static char * encode(const char * data);
};

}

#endif
