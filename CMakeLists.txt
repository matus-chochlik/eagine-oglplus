# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 3.27)

project(
	EAGineOGLplus
	LANGUAGES CXX
	HOMEPAGE_URL https://github.com/matus-chochlik/eagine-oglplus
)
if(NOT EAGINE_CORE_ROOT)
	set(EAGINE_CORE_ROOT ${PROJECT_SOURCE_DIR}/submodules/eagine-core)
endif()
if(NOT EAGINE_CORE_BINARY_ROOT)
	set(EAGINE_CORE_BINARY_ROOT ${PROJECT_BINARY_DIR}/submodules/eagine-core)
endif()
if(NOT EAGINE_OGLPLUS_ROOT)
	set(EAGINE_OGLPLUS_ROOT ${PROJECT_SOURCE_DIR})
endif()
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/config)
list(APPEND CMAKE_MODULE_PATH ${EAGINE_CORE_ROOT}/config)
file(STRINGS "${EAGINE_CORE_ROOT}/VERSION" EAGINE_VERSION)

add_subdirectory(submodules)

include(EAGineCoreCommon)
find_package(EAGineGLEW)
find_package(EAGineGLFW3)

add_subdirectory(source)
add_subdirectory(assets)
add_subdirectory(example)
add_subdirectory(deploy)
