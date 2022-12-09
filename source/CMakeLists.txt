# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
add_subdirectory(modules)
add_subdirectory(tools)

set(
	EAGINE_OGLPLUS_EXPORT_TARGETS
)

install(
	TARGETS ${EAGINE_OGLPLUS_EXPORT_TARGETS}
	EXPORT OGLplus
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
	PUBLIC_HEADER DESTINATION include
)

