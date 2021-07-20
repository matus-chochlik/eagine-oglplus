# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 3.10)

project(EAGineOGLplus)
if(NOT EAGINE_CORE_ROOT)
	set(EAGINE_CORE_ROOT ${PROJECT_SOURCE_DIR}/submodules/eagine-core)
endif()
if(NOT EAGINE_OGLPLUS_ROOT)
	set(EAGINE_OGLPLUS_ROOT ${PROJECT_SOURCE_DIR})
endif()
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/config)
list(APPEND CMAKE_MODULE_PATH ${EAGINE_CORE_ROOT}/config)

add_subdirectory(submodules)

include(EAGineCoreCommon)
include(OGLplusBaking)
find_package(EAGinePNG)
find_package(EAGineGLEW)
find_package(EAGineGLFW3)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(assets)
add_subdirectory(example)
