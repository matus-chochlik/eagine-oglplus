# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#

add_custom_target(eagine-oglplus-examples ALL)
set_target_properties(
	eagine-oglplus-examples
	PROPERTIES FOLDER "Example/OGLplus"
)

function(eagine_install_example TARGET_NAME)
	install(
		TARGETS ${TARGET_NAME}
		DESTINATION share/eagine/example/oglplus
	)
endfunction()

function(eagine_example_common EXAMPLE_NAME)
	add_executable(
		oglplus-${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		"${EXAMPLE_NAME}.cpp"
		${ARGN}
	)
	eagine_add_exe_analysis(oglplus-${EXAMPLE_NAME})
	eagine_target_modules(
		oglplus-${EXAMPLE_NAME}
		eagine.core
		eagine.shapes
		eagine.oglplus
	)
	target_link_libraries(
		oglplus-${EXAMPLE_NAME}
		PRIVATE EAGine::Deps::GLFW3
	)
	add_dependencies(eagine-oglplus-examples oglplus-${EXAMPLE_NAME})

	set_target_properties(
		oglplus-${EXAMPLE_NAME}
		PROPERTIES FOLDER "Example/OGLplus"
	)
	eagine_install_example(oglplus-${EXAMPLE_NAME})
endfunction()

eagine_example_common(001_info)
eagine_example_common(002_clear)
eagine_example_common(003_spectrum)
eagine_example_common(004_mandelbrot)
eagine_example_common(005_cartoon_sun)
eagine_example_common(006_writing)
eagine_example_common(007_metaballs)
eagine_example_common(008_worley_waves)
eagine_example_common(008_round_cube)
eagine_example_common(009_occlusion)
eagine_example_common(010_metallic_torus)
eagine_example_common(011_text_rendering)
eagine_example_common(012_single_pass_edges)
eagine_example_common(013_displacement)
eagine_example_common(014_texture_projection)
eagine_example_common(015_worleycraft)
eagine_example_common(016_cloud_morphing)
eagine_example_common(017_subroutines)
eagine_example_common(018_tessellation)
eagine_example_common(019_wooden_crate)
eagine_example_common(022_multi_viewport)
eagine_example_common(023_octree)
eagine_example_common(024_metaballs)
eagine_example_common(025_parallax_cube)
eagine_example_common(027_parallax_sphere)

eagine_embed_target_resources(
	TARGET oglplus-013_displacement
	RESOURCES
		WorleyTex "worley-bump.eagitex"
	ENABLE_SEARCH
)

eagine_embed_target_resources(
	TARGET oglplus-014_texture_projection
	RESOURCES
		ColorTex "oglplus.eagitex"
	ENABLE_SEARCH
)

eagine_embed_target_resources(
	TARGET oglplus-015_worleycraft
	RESOURCES
		WorleyTex "worley-bump.eagitex"
	ENABLE_SEARCH
)

eagine_embed_target_resources(
	TARGET oglplus-019_wooden_crate
	INPUT_TARGETS
	RESOURCES
		CrateDiff "wooden_crate-diff.eagitex"
		CrateLMap "wooden_crate-lmap.eagitex"
		CrateNMap "wooden_crate-nmap.eagitex"
	ENABLE_SEARCH
)
eagine_embed_target_resources(
	TARGET oglplus-025_parallax_cube
	INPUT_TARGETS
	wooden_crate-diff
	wooden_crate-hmap
	wooden_crate-nmap
)
eagine_embed_target_resources(
	TARGET oglplus-027_parallax_sphere
	RESOURCES
		WorleyTex  "worley-bump.eagitex"
		RectMskTex "round-rect-mask.eagitex"
	ENABLE_SEARCH
)

