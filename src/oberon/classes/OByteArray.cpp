// Copyright 2016 The Oberon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <QtCore>
#include <OByteArray>

OByteArray OByteArray::camelcase(void)
{
  return OByteArray(string::camelcase(this->data()));
}

OByteArray OByteArray::capitalize(void)
{
  return OByteArray(string::capitalize(this->data()));
}

OByteArray OByteArray::underscore(void)
{
  return OByteArray(string::underscore(this->data()));
}

OByteArray OByteArray::simplified(void)
{
  return (OByteArray) QByteArray::simplified();
}

OByteArray OByteArray::trimmed(void)
{
  return (OByteArray) QByteArray::trimmed();
}

OByteArray OByteArray::toUpper(void)
{
  return (OByteArray) QByteArray::toUpper();
}

OByteArray& OByteArray::append(const char *str)
{
  QByteArray::append(str);
  return *this;
}

OByteArray& OByteArray::append(const QByteArray &a)
{
  QByteArray::append(a);
  return *this;
}

OByteArray & OByteArray::operator=(const OByteArray &a)
{
  QByteArray::operator=(a);
  return *this;
}

OByteArray & OByteArray::operator=(const char * a)
{
  QByteArray::operator=(a);
  return *this;
}
