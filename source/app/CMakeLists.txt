# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt

foreach(APP png-to-eagitexi png-transitions tiling-to-eagitexi)
	add_custom_command(
		OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/eagine-${APP}.bco"
		COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/${APP}.py"
					--print-bash-completion
					"${CMAKE_CURRENT_BINARY_DIR}/eagine-${APP}.bco"
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${APP}.py")

	add_custom_target("eagine-${APP}-bco"
		ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/eagine-${APP}.bco")

	install(
		FILES "${CMAKE_CURRENT_BINARY_DIR}/eagine-${APP}.bco"
		COMPONENT oglplus-apps
		RENAME eagine-${APP}
		PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
		DESTINATION share/bash-completion/completions)

	install(
		PROGRAMS ${APP}.py
		COMPONENT oglplus-apps
		RENAME eagine-${APP}
		DESTINATION bin)
endforeach()

eagine_add_license(oglplus-apps)
eagine_add_debian_changelog(oglplus-apps)

eagine_add_package_property(
	oglplus-apps
	GENERATOR DEBIAN
	VARIABLE PACKAGE_DEPENDS
	VALUE "\${CXX_RUNTIME_PKGS},\${EAGINE_CORE_RUNTIME_PKGS},\${EAGINE_OGLPLUS_RUNTIME_PKGS},python3")

eagine_add_package_property(
	oglplus-apps
	GENERATOR DEBIAN
	VARIABLE DESCRIPTION
	VALUE "EAGine OGLplus utility applications.")

