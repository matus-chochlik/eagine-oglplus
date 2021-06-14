# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

add_custom_target(eagine-oglplus-examples ALL)
set_target_properties(
	eagine-oglplus-examples
	PROPERTIES FOLDER "Example/EAGine/OGLplus"
)

function(eagine_example_common EXAMPLE_NAME)
	add_executable(
		oglplus-${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		"${EXAMPLE_NAME}.cpp"
		${ARGN}
	)
	eagine_add_exe_analysis(oglplus-${EXAMPLE_NAME})
	add_dependencies(eagine-oglplus-examples oglplus-${EXAMPLE_NAME})
	target_link_libraries(
		oglplus-${EXAMPLE_NAME}
		PUBLIC EAGine::OGLplus
		PRIVATE ${ARGN}
	)

	set_target_properties(
		oglplus-${EXAMPLE_NAME}
		PROPERTIES FOLDER "Example/EAGine/OGLplus"
	)
	eagine_install_example(oglplus-${EXAMPLE_NAME})
endfunction()

add_subdirectory(oglplus)
