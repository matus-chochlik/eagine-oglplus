# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
eagine_add_module(
	eagine.oglplus PARTITION config
	IMPORTS eagine.core.types
)

eagine_add_module(
	eagine.oglplus PARTITION math
	IMPORTS
		config
		eagine.core.types
		eagine.core.math
)

eagine_add_module(
	eagine.oglplus PARTITION camera
	IMPORTS
		config math
		eagine.core.types
		eagine.core.math
		eagine.core.valid_if
		eagine.core.utility
)

eagine_add_module(
	eagine.oglplus PARTITION extensions
	IMPORTS
		eagine.core.types
		eagine.core.memory
		eagine.core.math
)

eagine_add_module(
	eagine.oglplus PARTITION enum_types
	IMPORTS
		config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION type_utils
	IMPORTS
		config enum_types math
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION glsl_source
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION result
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION objects
	IMPORTS
		config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION prog_var_loc
	IMPORTS
		config enum_types
		eagine.core.types
		eagine.core.memory
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION c_api
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION api_traits
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION constants
	IMPORTS
		config enum_types
		objects math c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION api
	IMPORTS
		config enum_types
		objects constants extensions
		glsl_source math
		prog_var_loc type_utils
		c_api api_traits
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.math
		eagine.core.units
		eagine.core.utility
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus PARTITION from_string
	IMPORTS
		enum_types constants
		eagine.core.types
		eagine.core.memory
		eagine.core.string
)

eagine_add_module(
	eagine.oglplus PARTITION gl_debug_logger
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.main_ctx
)

eagine_add_module(
	eagine.oglplus PARTITION shapes
	IMPORTS
		config enum_types
		objects constants api
		eagine.core.types
		eagine.core.memory
		eagine.shapes
)

eagine_add_module(
	eagine.oglplus PARTITION gpu_program
	IMPORTS
		config enum_types shapes
		glsl_source
		prog_var_loc object api
		eagine.core.types
		eagine.core.memory
		eagine.shapes
)

eagine_add_module(
	eagine.oglplus PARTITION resources
	IMPORTS
		config objects enum_types
		api
		eagine.core.types
		eagine.core.reflection
		eagine.core.value_tree
		eagine.core.resource
		eagine.core.main_ctx
)

eagine_add_module(
	eagine.oglplus PARTITION framebuffer
	IMPORTS
		config enum_types
		object constants
		prog_var_loc math api
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
		eagine.core.utility
		eagine.core.valid_if
)

eagine_add_module(
	eagine.oglplus
	PP_NAME OGLPLUS
	INTERFACES oglplus
	PARTITIONS
		config
		math
		camera
		extensions
		enum_types
		type_utils
		glsl_source
		result
		objects
		prog_var_loc
		c_api
		api_traits
		constants
		api
		from_string
		gl_debug_logger
		gpu_program
		framebuffer
		shapes
		resources
	SOURCES
		constants
		api
		camera
		shapes
		framebuffer
		resources
	IMPORTS
		eagine.core.memory
		eagine.core.string
		eagine.core.utility
		eagine.core.runtime
		eagine.core.reflection
)
target_link_libraries(
	eagine.oglplus
	PUBLIC
	EAGine::Deps::GLEW
)

eagine_add_module_tests(
	eagine.oglplus
	UNITS
		constants
	IMPORTS
		eagine.core
)
