######################################################################
# Automatically generated by qmake (3.0) dom jan 24 22:51:13 2016
######################################################################
TEMPLATE = lib
CONFIG += plugin
CONFIG += no_plugin_name_prefix

INCLUDEPATH += .
INCLUDEPATH += ../../../../include
INCLUDEPATH += ../../../../deps/include

TARGET = ByteArrayList
DESTDIR = ../../../../clib/charon

LIBS += -L ../../../../deps -lcharon -llua

# Input
SOURCES += bytearraylist.cpp
mac:QMAKE_POST_LINK += install_name_tool -change liblua.so  @executable_path/../deps/liblua.so ../../../../../clib/charon/StringList.dylib; install_name_tool -change libcharon.1.dylib  @executable_path/../deps/libcharon.1.dylib ../../../../../clib/charon/StringList.dylib
