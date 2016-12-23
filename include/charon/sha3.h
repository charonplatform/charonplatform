// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

namespace charon {

class sha3 {
  public:
  static char * sha224(const char * hash);
  static char * sha224(const char * hash, int length);
  static char * sha256(const char * hash);
  static char * sha256(const char * hash, int length);
  static char * sha384(const char * hash);
  static char * sha384(const char * hash, int length);
  static char * sha512(const char * hash);
  static char * sha512(const char * hash, int length);
};

}
