#include <arken/base>
#include <QtCore>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QHostInfo>
#include <QRegExp>
#include <QThread>

char * os::abspath(const char * path)
{
  QFileInfo info(path);
  QByteArray abspath = info.absoluteFilePath().toLocal8Bit();
  char * result = new char[abspath.size() + 1];
  strcpy(result, abspath);
  result[abspath.size()] = '\0';
  return result;
}

char * os::basename(const char * path)
{
  QFileInfo info(path);
  QByteArray basename = info.fileName().toLocal8Bit();
  char * result = new char[basename.size() + 1];
  strcpy(result, basename);
  result[basename.size()] = '\0';
  return result;
}

uint os::atime(const char * path)
{
  return QFileInfo(path).lastRead().toTime_t();
}

bool os::copy(const char * source, const char * destination, bool force = false)
{

  QFileInfo fileSource(source);
  if ( fileSource.isFile() ) {
    if( force && QFile::exists(destination) ) {
      QFile::remove(destination);
    }
    return QFile::copy(source, destination);
  }

  if( fileSource.isDir() ) {
    QDir dir(source);
    QString src(source);
    QString dest(destination);
    QStringList dirList = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for( int i = 0; i < dirList.size(); i++) {
        QString d = dirList.at(i);
        QString dst_path = dest + QDir::separator() + d;
        dir.mkpath(dst_path);
        if( os::copy((src + QDir::separator() + d).toLocal8Bit(), dst_path.toLocal8Bit()) == false ) {
          return false;
        }
    }

    QStringList fileList = dir.entryList(QDir::Files);
    for(int i=0; i < fileList.size(); i ++) {
        QString f = fileList.at(i);
        if( QFile::copy(src + QDir::separator() + f, dest + QDir::separator() + f) == false ) {
          return false;
        }
    }
  }

  return true;
}

bool os::chdir(const char * dirpath)
{
  return QDir::setCurrent( dirpath );
}

uint os::ctime(const char * path)
{
  return QFileInfo(path).lastModified().toTime_t();
}

char * os::dirpath(const char * path)
{
  QFileInfo info(path);
  QByteArray dirpath = info.absoluteFilePath().toLocal8Bit();
  char * result = new char[dirpath.size() + 1];
  strcpy(result, dirpath);
  result[dirpath.size()] = '\0';
  return result;
}

bool os::exists(const char * path)
{
  return QFile::exists(path);
}

char * os::home()
{
  QByteArray homePath = QDir::homePath().toLocal8Bit();
  char * result = new char[homePath.size()+1];
  strcpy(result, homePath);
  result[homePath.size()] = '\0';
  return result;
}

char * os::hostname()
{
  QByteArray hostname = QHostInfo::localHostName().toLocal8Bit();
  char * result = new char[hostname.size() + 1];
  strcpy(result, hostname);
  result[hostname.size()] = '\0';
  return result;
}

bool os::isdir(const char * path)
{
  QFileInfo info(path);
  return info.isDir();
}

bool os::isfile(const char * path)
{
  QFileInfo info(path);
  return info.isFile();
}

bool os::islink(const char * path)
{
  QFileInfo info(path);
  return info.isSymLink();
}

bool os::link(const char * source, const char * destination, bool force = false)
{
  if( force && QFile::exists(destination) ) {
    QFile::remove(destination);
  }
  return QFile::link(source, destination);
}

bool os::mkdir(const char * dirname)
{
  QDir dir;
  return dir.mkdir(dirname);
}

bool os::mkpath(const char * dirpath)
{
  QDir dir;
  return dir.mkpath(dirpath);
}

char * os::pwd()
{
  QByteArray pwd = QDir::currentPath().toLocal8Bit();
  char * result = new char[pwd.size() + 1];
  strcpy(result, pwd);
  result[pwd.size()] = '\0';
  return result;
}

bool os::rmdir(const char * dirname)
{
  QDir dir;
  return dir.rmdir(dirname);
}

bool os::rmpath(const char * dirpath)
{
  QDir dir;
  return dir.rmpath(dirpath);
}

char * os::target(const char * path)
{
  QByteArray target = QFile::symLinkTarget(path).toLocal8Bit();
  char * result  = new char[target.size() + 1];
  strcpy(result, target);
  result[target.size()] = '\0';
  return result;
}

char * os::temp()
{
  QByteArray temp = QDir::tempPath().toLocal8Bit();
  char * result = new char[temp.size() + 1];
  strcpy(result, temp);
  result[temp.size()] = '\0';
  return result;
}

char * os::root()
{
  QByteArray root = QDir::rootPath().toLocal8Bit();
  char * result = new char[root.size() + 1];
  strcpy(result, root);
  result[root.size()] = '\0';
  return result;
}
