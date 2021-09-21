# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 3.10)
project(eagine_oglplus_deb_test CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

find_package(EAGine REQUIRED COMPONENTS Core Shapes OGLplus)

if(EAGineOGLplus_FOUND)
	if(TARGET EAGine::OGLplus)
		message("EAGine OGLplus found")
		add_subdirectory(example)
	else()
		message(FATAL_ERROR "EAGine OGLplus target not found")
	endif()
else()
	message(FATAL_ERROR "EAGine OGLplus package not found")
endif()

