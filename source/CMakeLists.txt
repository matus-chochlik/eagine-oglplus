# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

add_library(EAGine::OGLplus INTERFACE IMPORTED GLOBAL)
target_link_libraries(EAGine::OGLplus INTERFACE eagine-oglplus-headers)

target_link_libraries(
	EAGine::OGLplus
	INTERFACE
		GLEW::GLEW
		EAGine::Core
		eagine-oglplus-headers
)

install(
	TARGETS
		eagine-oglplus-headers
		EXPORT OGLplus
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
	PUBLIC_HEADER DESTINATION include
)

install(
	EXPORT OGLplus
	NAMESPACE EAGine::
	FILE OGLplus.cmake
	DESTINATION lib/cmake/EAGine
)
