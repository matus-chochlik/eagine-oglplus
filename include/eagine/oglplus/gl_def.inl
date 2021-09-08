/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#if OGLPLUS_USE_GLEW
#include <stdexcept>
#endif

namespace eagine::oglplus {
//------------------------------------------------------------------------------
#ifndef OGLPLUS_NO_GL
//------------------------------------------------------------------------------
#if OGLPLUS_USE_GLEW
EAGINE_LIB_FUNC
api_initializer::api_initializer(const int, const int) {
    glewExperimental = GL_TRUE;
    GLenum init_result = glewInit();
    glGetError();
    if(init_result != GLEW_OK) {
        throw std::runtime_error("OpenGL/GLEW initialization error.");
    }
}
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
#endif // NO_GL
} // namespace eagine::oglplus
//------------------------------------------------------------------------------
