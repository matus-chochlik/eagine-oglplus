# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

add_library(eagine-oglplus INTERFACE IMPORTED GLOBAL)

target_link_libraries(
	eagine-oglplus
	INTERFACE
		EAGine::Deps::GLEW
		EAGine::Deps::GLFW3
		EAGine::Core
		EAGine::Shapes
		eagine-oglplus-generated-headers
		eagine-oglplus-headers
)
