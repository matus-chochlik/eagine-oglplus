# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
eagine_example_common(001_info)
eagine_example_common(002_clear)
eagine_example_common(003_spectrum)
eagine_example_common(004_mandelbrot)
eagine_example_common(005_cartoon_sun)
eagine_example_common(006_writing)
eagine_example_common(007_metaballs)
eagine_example_common(008_worley_waves)
eagine_example_common(009_round_cube)
eagine_example_common(010_metallic_torus)
eagine_example_common(011_text_rendering)
eagine_example_common(012_single_pass_edges)
eagine_example_common(013_texture_projection)
eagine_example_common(014_subroutines)
eagine_example_common(015_tessellation)
eagine_example_common(016_wooden_crate)
eagine_example_common(020_parallax_map)

eagine_embed_target_resources(
	TARGET oglplus-013_texture_projection
	INPUT_TARGETS
	oglplus
)

eagine_embed_target_resources(
	TARGET oglplus-016_wooden_crate
	INPUT_TARGETS
	wooden_crate-diff
	wooden_crate-hmap
	wooden_crate-nmap
)
eagine_embed_target_resources(
	TARGET oglplus-020_parallax_map
	INPUT_TARGETS
	wooden_crate-diff
	wooden_crate-hmap
	wooden_crate-nmap
)

