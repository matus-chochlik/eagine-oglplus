/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_GL_DEF_HPP
#define EAGINE_OGLPLUS_GL_DEF_HPP

#include <eagine/diagnostic.hpp>
#include <eagine/oglplus/config/basic.hpp>

#ifdef __clang__
EAGINE_DIAG_PUSH()
EAGINE_DIAG_OFF(reserved-id-macro)
#endif
//------------------------------------------------------------------------------
#if defined(__glew_h__) || defined(__GLEW_H__)
#define OGLPLUS_GLEW_DETECTED 1
#else
#define OGLPLUS_GLEW_DETECTED 0
#endif
//------------------------------------------------------------------------------
#if OGLPLUS_GLEW_DETECTED
#undef OGLPLUS_USE_GLEW
#endif
//------------------------------------------------------------------------------
#ifndef OGLPLUS_USE_GLEW
#define OGLPLUS_USE_GLEW 1
#endif
//------------------------------------------------------------------------------
#ifndef OGLPLUS_NO_GL
//------------------------------------------------------------------------------
namespace eagine::oglp {

struct api_initializer {
    ~api_initializer() noexcept = default;
    api_initializer(const api_initializer&) = delete;
    api_initializer(api_initializer&&) = delete;
    auto operator=(const api_initializer&) = delete;
    auto operator=(api_initializer&&) = delete;

    explicit api_initializer(int /*gl_ver_major*/ = 3, int /*gl_ver_minor*/ = 3);
};

} // namespace eagine::oglp
//------------------------------------------------------------------------------
#if OGLPLUS_USE_GLEW
#include <GL/glew.h>
//------------------------------------------------------------------------------
#else
#error "Some library including OpenGL symbols is required!"
#endif // OGLPLUS_USE_*
//------------------------------------------------------------------------------
#endif // OGLPLUS_NO_GL
//------------------------------------------------------------------------------
#ifdef __clang__
EAGINE_DIAG_POP()
#endif
//------------------------------------------------------------------------------
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <eagine/oglplus/gl_def.inl>
#endif
//------------------------------------------------------------------------------
#endif // EAGINE_OGLPLUS_GL_DEF_HPP
