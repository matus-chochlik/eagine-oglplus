/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_GL_API_FWD_HPP
#define EAGINE_OGLPLUS_GL_API_FWD_HPP

namespace eagine::oglplus {
//------------------------------------------------------------------------------
class gl_api_traits;

template <typename ApiTraits>
class basic_gl_api;

/// @brief Alias for the default instantation of basic_gl_api.
/// @ingroup gl_api_wrap
using gl_api = basic_gl_api<gl_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

#endif // EAGINE_OGLPLUS_GL_API_FWD_HPP
