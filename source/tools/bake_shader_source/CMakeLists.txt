# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

add_executable(oglplus-bake_shader_source main.cpp)
eagine_add_exe_analysis(oglplus-bake_shader_source)
if(${WITH_MODULES})
	eagine_target_modules(
		oglplus-bake_shader_source
		eagine.core
		eagine.oglplus
	)
else()
	target_link_libraries(
		oglplus-bake_shader_source
		PUBLIC EAGine::OGLplus
	)
endif()
