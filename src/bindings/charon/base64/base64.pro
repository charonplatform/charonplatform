######################################################################
# Automatically generated by qmake (3.0) s�b abr 16 12:10:40 2016
######################################################################

TEMPLATE = lib

CONFIG += plugin
CONFIG += no_plugin_name_prefix

DESTDIR = ../../../../clib/charon
TARGET = base64

INCLUDEPATH += .
INCLUDEPATH += ../../../../include
INCLUDEPATH += ../../../../deps/include

# Input
SOURCES += base64.cpp

LIBS += -L ../../../../deps -lcharon -llua

mac:QMAKE_POST_LINK += install_name_tool -change liblua.so  @executable_path/../deps/liblua.so ../../../../clib/charon/base64.dylib; install_name_tool -change libcharon.1.dylib  @executable_path/../deps/libcharon.1.dylib ../../../../clib/charon/base64.dylib
