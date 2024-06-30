# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt

add_subdirectory(textures)

eagine_add_package_property(
	oglplus-assets
	GENERATOR DEBIAN
	VARIABLE PACKAGE_DEPENDS
	VALUE "\${CXX_RUNTIME_PKGS},\${EAGINE_CORE_RUNTIME_PKGS},\${EAGINE_OGLPLUS_RUNTIME_PKGS}")

eagine_add_package_property(
	oglplus-assets
	GENERATOR DEBIAN
	VARIABLE DESCRIPTION
	VALUE "EAGine OGLplus assets.")

eagine_add_package_property(
	oglplus-assets
	GENERATOR DEBIAN
	VARIABLE PACKAGE_ARCHITECTURE
	VALUE "all")

