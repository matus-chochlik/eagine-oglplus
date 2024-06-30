# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
configure_file(gl_def.hpp gl_def.hpp COPYONLY)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION config
	IMPORTS
		std
		eagine.core.types
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION math
	IMPORTS
		std config
		eagine.core.types
		eagine.core.math
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION camera
	IMPORTS
		std config math
		eagine.core.types
		eagine.core.math
		eagine.core.valid_if
		eagine.core.units
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION extensions
	IMPORTS
		std
		eagine.core.types
		eagine.core.memory
		eagine.core.math
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION enum_types
	IMPORTS
		std config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION type_utils
	IMPORTS
		std config enum_types math
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION glsl_source
	IMPORTS
		std config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION result
	IMPORTS
		std config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION objects
	IMPORTS
		std config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION prog_var_loc
	IMPORTS
		std config enum_types
		eagine.core.types
		eagine.core.memory
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION c_api
	IMPORTS
		std config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION api_traits
	IMPORTS
		std config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION constants
	IMPORTS
		std config enum_types
		objects math c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.valid_if
		eagine.core.c_api
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION api
	IMPORTS
		std config enum_types
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
		eagine.core.identifier
		eagine.core.c_api
		eagine.core.main_ctx
		eagine.core.resource
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION from_string
	IMPORTS
		std enum_types constants
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.valid_if
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION gl_debug_logger
	IMPORTS
		std config
		eagine.core.types
		eagine.core.memory
		eagine.core.main_ctx
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION shapes
	IMPORTS
		std config enum_types
		objects constants api
		eagine.core.types
		eagine.core.memory
		eagine.core.utility
		eagine.core.valid_if
		eagine.shapes
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION gpu_program
	IMPORTS
		std config enum_types
		shapes glsl_source
		prog_var_loc object api
		eagine.core.types
		eagine.core.memory
		eagine.core.valid_if
		eagine.shapes
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION resources
	IMPORTS
		std config objects
		enum_types api
		eagine.core.types
		eagine.core.memory
		eagine.core.reflection
		eagine.core.value_tree
		eagine.core.resource
		eagine.core.main_ctx
)

eagine_add_module(
	eagine.oglplus
	COMPONENT oglplus-dev
	PARTITION framebuffer
	IMPORTS
		std config enum_types
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
	COMPONENT oglplus-dev
	SOURCES
		constants
		api
		gl_debug_logger
		camera
		shapes
		gpu_program
		framebuffer
		resources
	IMPORTS
		std
		eagine.core.c_api
		eagine.core.container
		eagine.core.math
		eagine.core.memory
		eagine.core.reflection
		eagine.core.runtime
		eagine.core.string
		eagine.core.types
		eagine.core.units
		eagine.core.utility
		eagine.core.valid_if
		eagine.core.value_tree
		eagine.shapes
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

eagine_add_license(oglplus-dev)
eagine_add_debian_changelog(oglplus-dev)

eagine_add_package_property(
	oglplus-dev
	GENERATOR DEBIAN
	VARIABLE PACKAGE_DEPENDS
	VALUE "eagine-core-dev (>= ${EAGINE_VERSION}),eagine-shapes-dev (>= ${EAGINE_VERSION})")

eagine_add_package_property(
	oglplus-dev
	GENERATOR DEBIAN
	VARIABLE DESCRIPTION
	VALUE "C++ wrapper for OpenGL.")

