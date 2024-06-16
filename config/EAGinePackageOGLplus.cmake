#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt
#
# Package specific options
#  Debian
#   Dependencies
set(CPACK_DEBIAN_OGLPLUS-APPS_PACKAGE_DEPENDS "")
set(CPACK_DEBIAN_OGLPLUS-DEV_PACKAGE_DEPENDS "eagine-core-dev (>= @EAGINE_VERSION@),eagine-shapes-dev (>= @EAGINE_VERSION@)")
#   Descriptions
set(CPACK_DEBIAN_OGLPLUS-APPS_DESCRIPTION "python3,python3-pip")
set(CPACK_DEBIAN_OGLPLUS-DEV_DESCRIPTION "C++ wrapper for OpenGL.")

