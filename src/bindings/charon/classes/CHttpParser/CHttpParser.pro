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

TARGET = CHttpParser
DESTDIR = ../../../../../clib/

LIBS += -L ../../../../../vendors -lcharon -llua

# Input
SOURCES += CHttpParser.cpp

mac:QMAKE_POST_LINK += install_name_tool -change liblua.so  @executable_path/../vendors/liblua.so ../../../../../clib/CHttpParser.dylib; install_name_tool -change libcharon.1.dylib  @executable_path/../vendors/libcharon.1.dylib ../../../../../clib/CHttpParser.dylib