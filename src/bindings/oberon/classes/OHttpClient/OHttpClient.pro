######################################################################
# Automatically generated by qmake (3.0) dom jan 24 22:51:13 2016
######################################################################
QT += core sql
TEMPLATE = lib
CONFIG += plugin
CONFIG += no_plugin_name_prefix

INCLUDEPATH += .
INCLUDEPATH += ../../../../../include
INCLUDEPATH += ../../../../../vendors/include

TARGET = OHttpClient
DESTDIR = ../../../../../clib/

LIBS += -L ../../../../../vendors -loberon -llua

unix:LIBS  += -lcurl
win32:LIBS += ../../../../../vendors/libcurl.dll

# Input
SOURCES += OHttpClient.cpp

mac:QMAKE_POST_LINK += install_name_tool -change liblua.so  @executable_path/../vendors/liblua.so ../../../../../clib/OHttpClient.dylib; install_name_tool -change liboberon.1.dylib  @executable_path/../vendors/liboberon.1.dylib ../../../../../clib/OHttpClient.dylib
