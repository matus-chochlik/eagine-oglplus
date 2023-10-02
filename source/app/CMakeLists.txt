# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
install(
	PROGRAMS png_to_eagitexi.py
	RENAME eagine-png-to-eagitexi
	DESTINATION bin
)

install(
	PROGRAMS png_transitions.py
	RENAME eagine-png-transitions
	DESTINATION bin
)

install(
	PROGRAMS tiling_to_eagitexi.py
	RENAME eagine-tiling-to-eagitexi
	DESTINATION bin
)

install(
	PROGRAMS generate_eagitexi.py
	RENAME eagine-generate-eagitexi
	DESTINATION bin
)

