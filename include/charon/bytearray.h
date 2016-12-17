#ifndef _CBYTE_ARRAY_HEADER_
#define _CBYTE_ARRAY_HEADER_

#include <QtCore>
#include <charon/helper>

namespace charon
{

class ByteArray : public QByteArray
{

  //Data *d;
  private:

  bool underscore_special_char(char chr);
  int underscore_len(void);

  public:

  ByteArray() : QByteArray() { }
  ByteArray(const char *data) : QByteArray(data) { }
  ByteArray(const char *data, int size) : QByteArray(data, size) { }

  ByteArray camelcase(void);
  ByteArray capitalize(void);
  ByteArray underscore(void);
  ByteArray simplified(void);
  ByteArray trimmed(void);
  ByteArray toUpper(void);
  ByteArray &append(const char *s);
  ByteArray &append(const QByteArray &a);
  ByteArray &operator=(const ByteArray &a);
  ByteArray &operator=(const char * a);
};

}

#endif
