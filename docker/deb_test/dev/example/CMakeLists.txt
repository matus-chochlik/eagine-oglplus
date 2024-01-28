# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
#
add_executable(eagine-basic_info basic_info.cpp)
target_link_libraries(eagine-basic_info PUBLIC EAGine::OGLplus)

