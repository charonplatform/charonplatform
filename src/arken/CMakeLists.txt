# ------------------------------------------------------------------------------
#
# Copyright 2016 The Arken Platform Authors.
#
# All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.
#
# ------------------------------------------------------------------------------

if(ARKEN_NOTIFY STREQUAL "libnotify")
  find_package(PkgConfig REQUIRED)
  find_package(GTK2 REQUIRED gtk)
  PKG_SEARCH_MODULE(GDK_PIXBUF ${_pkgconfig_REQUIRED} "gdk-pixbuf-2.0")
  pkg_check_modules(GLIB REQUIRED glib-2.0)
  pkg_check_modules(LIB_NOTIFY REQUIRED libnotify)
  PKG_CHECK_MODULES(GDK_PIXBUF, gio-2.0)
  include_directories(${GLIB_INCLUDE_DIRS})
  include_directories(${NOTIFY_INCLUDE_DIRS})
  find_path(GDK_PIXBUF_INCLUDE_DIRS gdk-pixbuf/gdk-pixbuf.h)
  include_directories(${GDK_PIXBUF_INCLUDE_DIRS})
endif()

if(ARKEN_NOTIFY STREQUAL "glib")
  find_package(PkgConfig REQUIRED)
  #find_package(GTK2 REQUIRED gtk)
  #PKG_SEARCH_MODULE(GDK_PIXBUF ${_pkgconfig_REQUIRED} "gdk-pixbuf-2.0")
  #pkg_check_modules(GLIB REQUIRED glib-2.0)
  pkg_check_modules(LIB_GIO REQUIRED gio-2.0)
  #PKG_CHECK_MODULES(GDK_PIXBUF, gio-2.0)
  include_directories(${GLIB_INCLUDE_DIRS})
  #find_path(GDK_PIXBUF_INCLUDE_DIRS gdk-pixbuf/gdk-pixbuf.h)
  #include_directories(${GDK_PIXBUF_INCLUDE_DIRS})
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/include)
include_directories(${PROJECT_SOURCE_DIR}/src/vendors/ap)
include_directories(${PROJECT_SOURCE_DIR}/src/vendors/mongrel2)
include_directories(${PROJECT_SOURCE_DIR}/src/vendors/mongrel2/http11)

file(GLOB src      ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB image    ${CMAKE_CURRENT_SOURCE_DIR}/image/*.cpp)
file(GLOB os       ${CMAKE_CURRENT_SOURCE_DIR}/os/*.c)
file(GLOB net      ${CMAKE_CURRENT_SOURCE_DIR}/net/*.cpp)
file(GLOB concurrent ${CMAKE_CURRENT_SOURCE_DIR}/concurrent/*.cpp)
file(GLOB compress ${CMAKE_CURRENT_SOURCE_DIR}/compress/*.cpp)
file(GLOB time     ${CMAKE_CURRENT_SOURCE_DIR}/time/*.cpp)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deps)
set(mongrel2 ${PROJECT_SOURCE_DIR}/src/vendors/mongrel2/http11/http11_parser.c)

add_library(
  arken SHARED
  ${src}
  ${base64}
  ${base64-embedded}
  ${compress}
  ${digest}
  ${digest-embedded}
  ${image}
  ${mvm-container}
  ${net}
  ${arken-notify}
  ${os} ${os-executablePath} ${os-filesystem} ${os-name} ${os-pid} ${os-uuid}
  ${concurrent}
  ${regex}
  ${time}
  ${mongrel2}
  ${utf8}
)

find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Gui)
find_package(Qt5Widgets)

target_link_libraries(arken Qt5::Core)
target_link_libraries(arken Qt5::Network)
target_link_libraries(arken Qt5::Gui)
target_link_libraries(arken Qt5::Widgets)

target_link_libraries(arken zip)
target_link_libraries(arken curl)
target_link_libraries(arken lua)
target_link_libraries(arken json)

if(ARKEN_NOTIFY STREQUAL "libnotify")
  target_link_libraries(arken notify)
  target_link_libraries(arken ${GLIB_LIBRARIES})
  target_link_libraries(arken ${NOTIFY_LIBRARIES})
endif()

if(ARKEN_NOTIFY STREQUAL "qt")
  include_directories(${PROJECT_SOURCE_DIR}/src/arken/notify/qt)
endif()

if(ARKEN_NOTIFY STREQUAL "opengl")
  include_directories(${PROJECT_SOURCE_DIR}/src/arken/notify/opengl)
endif()

if(ARKEN_NOTIFY STREQUAL "glib")
  message(STATUS ${GLIB_LIBRARIES})
  target_link_libraries(arken ${GLIB_LIBRARIES})
  target_link_libraries(arken gio-2.0)
endif()

if(ARKEN_NOTIFY STREQUAL "opengl")
  target_link_libraries(arken glut GL)
endif()

if(ARKEN_DIGEST STREQUAL "libssl")
  target_link_libraries(arken ssl)
endif()

if(ARKEN_OS_UUID STREQUAL "libuuid")
  target_link_libraries(arken uuid)
endif()

if(ARKEN_OS_FILESYSTEM STREQUAL "boost")
  message(STATUS "link libarken with ${Boost_LIBRARIES}")
  target_link_libraries(arken pthread m ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
endif()
