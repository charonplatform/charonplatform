######################################################################
# Automatically generated by qmake (3.0) dom jan 24 22:51:13 2016
######################################################################
TEMPLATE = lib
CONFIG += plugin
CONFIG += no_plugin_name_prefix

INCLUDEPATH += .
INCLUDEPATH += ../../../../include
INCLUDEPATH += ../../../../deps/include

TARGET = QFileInfoList
DESTDIR = ../../../../clib

LIBS += -L ../../../../deps -llua

# Input
SOURCES += QFileInfoList.cpp

mac:QMAKE_POST_LINK += install_name_tool -change liblua.so  @executable_path/../deps/liblua.so ../../../../clib/QFileInfoList.dylib
