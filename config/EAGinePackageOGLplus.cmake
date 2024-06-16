#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt
#
# Package specific options
#  Debian
#   Dependencies
set(CXX_RUNTIME_PKGS "libc6,libc++1-17")
set(CPACK_DEBIAN_OGLPLUS-APPS_PACKAGE_DEPENDS "${CXX_RUNTIME_PKGS},libsystemd0,zlib1g")
set(CPACK_DEBIAN_OGLPLUS-EXAMPLES_PACKAGE_DEPENDS "${CXX_RUNTIME_PKGS},libsystemd0,zlib1g")
set(CPACK_DEBIAN_OGLPLUS-DEV_PACKAGE_DEPENDS "eagine-core-dev (>= @EAGINE_VERSION@),eagine-shapes-dev (>= @EAGINE_VERSION@)")
set(CPACK_DEBIAN_OGLPLUS-ASSETS_PACKAGE_DEPENDS "")
#   Descriptions
set(CPACK_DEBIAN_OGLPLUS-APPS_DESCRIPTION "Collection of OGLplus applications.")
set(CPACK_DEBIAN_OGLPLUS-EXAMPLESS_DESCRIPTION "EAGine OGLplus examples.")
set(CPACK_DEBIAN_OGLPLUS-DEV_DESCRIPTION "C++ wrapper for OpenGL.")
set(CPACK_DEBIAN_OGLPLUS-ASSETS_DESCRIPTION "Collection of assets usable with the EAGine applications.")

