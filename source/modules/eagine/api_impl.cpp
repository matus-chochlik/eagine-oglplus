/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#include "gl_def.hpp"

module eagine.oglplus;
import std;
import eagine.core.types;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
#if OGLPLUS_USE_GLEW
api_initializer::api_initializer(const int, const int) {
    glewExperimental = GL_TRUE;
    GLenum init_result = glewInit();
    glGetError();
    if(init_result != GLEW_OK) {
        throw std::runtime_error("OpenGL/GLEW initialization error.");
    }
}
#else
api_initializer::api_initializer(const int, const int) {}
#endif
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
