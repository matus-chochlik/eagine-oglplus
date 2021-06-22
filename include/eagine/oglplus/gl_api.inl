/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

// clang-format off
#include <eagine/oglplus/gl_api/api_traits.inl>
#include <eagine/oglplus/gl_api/constants.inl>
#include <eagine/oglplus/gl_api/c_api.inl>
#include <eagine/oglplus/gl_api/api.inl>
// clang-format on

namespace eagine::oglplus {

template class basic_gl_constants<gl_api_traits>;
template class basic_gl_operations<gl_api_traits>;
template class basic_gl_c_api<gl_api_traits>;
template class basic_gl_api<gl_api_traits>;

} // namespace eagine::oglplus

