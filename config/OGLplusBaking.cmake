#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
function(oglplus_add_glsl_program PROG_NAME)
	file(GLOB BAKEPROG "${PROG_NAME}.bakeprog")
	if("${BAKEPROG}" MATCHES "^.*${PROG_NAME}\.bakeprog$")
		eagine_add_baked_resource(
			COMMAND oglplus-bake_program_source
			PREFIX oglp
			RES_KIND prog
			RES_NAME ${PROG_NAME}
		)
	else()
		message(FATAL_ERROR "Invalid input(s) for GLSL program '${PROG_NAME}'")
	endif()
endfunction()
