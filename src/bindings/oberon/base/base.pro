######################################################################
# Automatically generated by qmake (3.0) qua mar 30 16:32:25 2016
######################################################################

TEMPLATE = lib

CONFIG += plugin
CONFIG += no_plugin_name_prefix

DESTDIR = ../../../../clib/oberon
TARGET = base

INCLUDEPATH += .
INCLUDEPATH += ../../../../include
INCLUDEPATH += ../../../../vendors/include

# Input
SOURCES += *.cpp
SOURCES += ../../../../src/oberon/os.cpp

win32:LIBS += ../../../../vendors/lua51.dll
