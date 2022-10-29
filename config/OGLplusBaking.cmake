#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
function(oglplus_add_texture TEX_NAME)
	file(GLOB BAKETEX "${TEX_NAME}.*.baketex")
	if("${BAKETEX}" MATCHES "^.*${TEX_NAME}\.(.*)\.baketex$")
		eagine_add_baked_resource(
			COMMAND oglplus-bake_${CMAKE_MATCH_1}_image
			PREFIX oglp
			RES_KIND tex
			RES_NAME ${TEX_NAME}
			SUFFIX .${CMAKE_MATCH_1}
			PACKED
		)
	else()
		if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${TEX_NAME}.png")
			file(
				WRITE "${CMAKE_CURRENT_BINARY_DIR}/${TEX_NAME}.baketex"
				"--input;${CMAKE_CURRENT_SOURCE_DIR}/${TEX_NAME}.png"
			)
			eagine_add_baked_resource(
				COMMAND oglplus-bake_png_image
				PREFIX oglp
				RES_KIND tex
				RES_NAME ${TEX_NAME}
				PACKED
			)
		else()
			message(FATAL_ERROR "Invalid input(s) for texture '${TEX_NAME}'")
		endif()
	endif()
endfunction()

