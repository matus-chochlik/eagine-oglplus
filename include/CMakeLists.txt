# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
configure_file(
	eagine/oglplus/config/site.hpp.in
	eagine/oglplus/config/site.hpp
	@ONLY
)
set(GEN_HPPS eagine/oglplus/config/site.hpp)
include(./Sources.cmake)
# - generated headers ---------------------------------------------------------
add_library(eagine-oglplus-generated-headers INTERFACE)

target_include_directories(
	eagine-oglplus-generated-headers
	INTERFACE
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

foreach(FILENAME ${GEN_HPPS})
	set_property(
		TARGET eagine-oglplus-generated-headers
		APPEND PROPERTY PUBLIC_HEADER ${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}
	)
endforeach()
# - regular headers ------------------------------------------------------------
add_library(eagine-oglplus-headers INTERFACE)

target_include_directories(
	eagine-oglplus-headers
	INTERFACE
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

foreach(FILENAME ${HEADERS} ${PUB_INLS})
	set_property(
		TARGET eagine-oglplus-headers
		APPEND PROPERTY PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
	)
endforeach()
