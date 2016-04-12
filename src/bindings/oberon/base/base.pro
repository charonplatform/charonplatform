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
SOURCES += ../../../../src/oberon/string.cpp
SOURCES += ../../../../src/oberon/string/oberon_string_append.c
SOURCES += ../../../../src/oberon/string/oberon_string_endsWith.c
SOURCES += ../../../../src/oberon/string/oberon_string_insert.c
SOURCES += ../../../../src/oberon/string/oberon_string_underscore.c

SOURCES += ../../../../src/oberon/curl/curl-read.c

unix:LIBS += -lcurl
win32:LIBS += ../../../../vendors/lua51.dll
win32:LIBS += ../../../../vendors/libcurl.dll
