######################################################################
# Automatically generated by qmake (3.0) dom jan 24 22:51:13 2016
######################################################################
TEMPLATE = lib
INCLUDEPATH += .
INCLUDEPATH += ../../include
INCLUDEPATH += ../../vendors/include

TARGET = oberon
DESTDIR = ../../shared

# Input
SOURCES += ../../src/oberon/*.cpp
SOURCES += ../../src/oberon/curl/*.c
SOURCES += ../../src/oberon/string/oberon_string_append.c
SOURCES += ../../src/oberon/string/oberon_string_endsWith.c
SOURCES += ../../src/oberon/string/oberon_string_insert.c
SOURCES += ../../src/oberon/string/oberon_string_mid.c
SOURCES += ../../src/oberon/string/oberon_string_repeated.c
SOURCES += ../../src/oberon/string/oberon_string_underscore.c


unix:LIBS += -lcurl
win32:LIBS += ../../vendors/lua51.dll
win32:LIBS += ../../vendors/libcurl.dll
