######################################################################
# Automatically generated by qmake (3.0) dom jan 24 22:51:13 2016
######################################################################
TEMPLATE = lib
CONFIG += plugin
CONFIG += no_plugin_name_prefix

INCLUDEPATH += .
INCLUDEPATH += ../../../../include
INCLUDEPATH += ../../../../vendors/include

TARGET = QString
DESTDIR = ../../../../clib

LIBS  += -L ../../../../vendors -llua

# Input
SOURCES += QString.cpp

mac:QMAKE_POST_LINK += install_name_tool -change liblua.so  @executable_path/../vendors/liblua.so ../../../../clib/QString.dylib
