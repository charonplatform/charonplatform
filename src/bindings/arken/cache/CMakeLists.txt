# ------------------------------------------------------------------------------
#
# Copyright 2016 The Arken Platform Authors.
#
# All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.
#
# ------------------------------------------------------------------------------

include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/include)

add_library(
  cache SHARED cache.cpp
)

find_package(Qt5Core)
find_package(Qt5Network)

set_target_properties(cache PROPERTIES PREFIX "")

target_link_libraries(cache Qt5::Core Qt5::Network arken lua json)
