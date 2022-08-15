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
	eagine.oglplus PARTITION enum_types
	IMPORTS
		config
		eagine.core.types
		eagine.core.identifier
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
	eagine.oglplus PARTITION image_spec
	IMPORTS
		config enum_types
		eagine.core.types
		eagine.core.memory
		eagine.core.valid_if
		eagine.core.utility
		eagine.core.runtime
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
	eagine.oglplus
	PP_NAME OGLPLUS
	INTERFACES oglplus
	PARTITIONS
		config
		math
		enum_types
		glsl_source
		image_spec
		objects
	SOURCES
		image_spec_impl
)

