######################################################################
# Automatically generated by qmake (3.0) s�b abr 16 12:10:40 2016
######################################################################

TEMPLATE = lib

CONFIG += plugin
CONFIG += no_plugin_name_prefix

DESTDIR = ../../../../clib/oberon
TARGET = http

INCLUDEPATH += .
INCLUDEPATH += ../../../../include
INCLUDEPATH += ../../../../vendors/include

# Input
SOURCES += http.cpp

unix:LIBS += ../../../../shared/liboberon.so
win32:LIBS += ../../../../shared/oberon.dll

unix:LIBS += -lcurl
win32:LIBS += ../../../../vendors/lua51.dll
win32:LIBS += ../../../../vendors/libcurl.dll
