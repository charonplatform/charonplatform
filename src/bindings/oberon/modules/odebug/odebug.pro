######################################################################
# Automatically generated by qmake (3.0) s�b abr 16 12:10:40 2016
######################################################################

TEMPLATE = lib

CONFIG += plugin
CONFIG += no_plugin_name_prefix

DESTDIR = ../../../../../clib/oberon
TARGET = odebug

INCLUDEPATH += .
INCLUDEPATH += ../../../../../include
INCLUDEPATH += ../../../../../vendors/include

# Input
SOURCES += odebug.cpp

LIBS += -L ../../../../../vendors -loberon -llua

unix:LIBS += -lcurl
win32:LIBS += ../../../../../vendors/libcurl.dll

mac:QMAKE_POST_LINK += install_name_tool -change liblua.so  @executable_path/../vendors/liblua.so ../../../../../clib/oberon/odebug.dylib; install_name_tool -change liboberon.1.dylib  @executable_path/../vendors/liboberon.1.dylib ../../../../../clib/oberon/odebug.dylib
