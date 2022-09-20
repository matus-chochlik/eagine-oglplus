# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

add_executable(oglplus-bake_tiling_image main.cpp)
eagine_add_exe_analysis(oglplus-bake_tiling_image)
eagine_target_modules(
	oglplus-bake_tiling_image
	eagine.core
	eagine.oglplus
)
