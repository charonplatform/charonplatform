######################################################################
# Automatically generated by qmake (3.0) s�b nov 5 14:42:37 2016
######################################################################

TEMPLATE = lib
CONFIG += plugin
CONFIG += no_plugin_name_prefix

INCLUDEPATH += .
INCLUDEPATH += ../../../deps/include

TARGET = json

DESTDIR = ../../../clib/charon

# Input
HEADERS += json.h dtoa_config.h fpconv.h strbuf.h
SOURCES += json.c strbuf.c g_fmt.c dtoa.c json_lock.cpp #fpconv.c

LIBS += -L ../../../deps -llua

mac:QMAKE_POST_LINK += install_name_tool -change liblua.so  @executable_path/../deps/liblua.so ../../../clib/json.dylib
