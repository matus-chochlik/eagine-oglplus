#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt
file(APPEND "${CMAKE_BINARY_DIR}/CPackPropertiesEAGine.cmake"
	"set(EAGINE_OGLPLUS_RUNTIME_PKGS \"libglew2.2,libglfw3\")\n")
