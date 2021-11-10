/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_CONFIG_BASIC_HPP
#define EAGINE_OGLPLUS_CONFIG_BASIC_HPP

#include <eagine/config/basic.hpp>

#ifndef EAGINE_OGLPLUS_LIBRARY
#if defined(__clang_analyzer__)
#define EAGINE_OGLPLUS_LIBRARY 1
#else
#define EAGINE_OGLPLUS_LIBRARY 0
#endif
#endif

#if __has_include(<eagine/oglplus/config/site.hpp>)
#include <eagine/oglplus/config/site.hpp>
#endif

#ifndef OGLPLUS_GLX_FOUND
#define OGLPLUS_GLX_FOUND 0
#endif

#ifndef OGLPLUS_GLFW3_FOUND
#define OGLPLUS_GLFW3_FOUND 0
#endif

#ifndef OGLPLUS_GLFW_FOUND
#define OGLPLUS_GLFW_FOUND 0
#endif

#ifndef OGLPLUS_GLUT_FOUND
#define OGLPLUS_GLUT_FOUND 0
#endif

#ifndef OGLPLUS_FREEGLUT_FOUND
#define OGLPLUS_FREEGLUT_FOUND 0
#endif

#ifndef OGLPLUS_SDL_FOUND
#define OGLPLUS_SDL_FOUND 0
#endif

#ifndef OGLPLUS_LOW_PROFILE
#define OGLPLUS_LOW_PROFILE 0
#endif

#ifndef OGLPLUS_NO_LIMIT_CHECKS
#define OGLPLUS_NO_LIMIT_CHECKS OGLPLUS_LOW_PROFILE
#endif

#endif // EAGINE_OGLPLUS_CONFIG_BASIC_HPP
