#include <cstring>
#include <QFileInfo>

namespace oberon {
  namespace os {
    uint     atime(const char * path);
    bool     compare(const char * path1, const char * path2);
    bool     copy(const char * source, const char * destination, bool force);
    int      cores();
    uint     ctime(const char * path);
    bool     exists(const char * path);
    char   * hostname();
    bool     link(const char * source, const char * destination, bool force);
    double   microtime();
    char   * name();
    void     sleep(double secs);
    char   * target(const char * path);
    char   * uuid();
    char   * read(const char * path);
    char   * read(const char * path, size_t * size);
  }
}
