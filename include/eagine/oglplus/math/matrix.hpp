/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_MATH_MATRIX_HPP
#define EAGINE_OGLPLUS_MATH_MATRIX_HPP

#include "config.hpp"
#include <eagine/math/tmat.hpp>
#include <eagine/oglplus/gl_api/config.hpp>

namespace eagine::oglplus {

/// @brief Alias for math::matrix.
/// @ingroup gl_utils
using math::matrix;

/// @brief Template alias for math::tmat.
/// @ingroup gl_utils
template <typename T, unsigned C, unsigned R, bool RM = false, bool V = math_use_simd>
using tmat = math::tmat<T, C, R, RM, V>;

/// @brief Template alias for float matrices.
/// @ingroup gl_utils
template <unsigned C, unsigned R, bool RM>
using tfmat = tmat<gl_types::float_type, C, R, RM>;

/// @brief Template alias for column-major float matrices.
/// @ingroup gl_utils
template <unsigned C, unsigned R = C>
using tcfmat = tfmat<C, R, false>;

/// @brief Template alias for row-major float matrices.
/// @ingroup gl_utils
template <unsigned C, unsigned R = C>
using trfmat = tfmat<C, R, true>;

/// @brief Alias for 2x2 matrix.
/// @ingroup gl_utils
using mat2 = tcfmat<2>;

/// @brief Alias for 2x3 matrix.
/// @ingroup gl_utils
using mat2x3 = tcfmat<2, 3>;

/// @brief Alias for 2x4 matrix.
/// @ingroup gl_utils
using mat2x4 = tcfmat<2, 4>;

/// @brief Alias for 3x2 matrix.
/// @ingroup gl_utils
using mat3x2 = tcfmat<3, 2>;

/// @brief Alias for 3x3 matrix.
/// @ingroup gl_utils
using mat3 = tcfmat<3>;

/// @brief Alias for 3x4 matrix.
/// @ingroup gl_utils
using mat3x4 = tcfmat<3, 4>;

/// @brief Alias for 4x2 matrix.
/// @ingroup gl_utils
using mat4x2 = tcfmat<4, 2>;

/// @brief Alias for 4x3 matrix.
/// @ingroup gl_utils
using mat4x3 = tcfmat<4, 3>;

/// @brief Alias for 4x4 matrix.
/// @ingroup gl_utils
using mat4 = tcfmat<4>;

} // namespace eagine::oglplus

#endif // EAGINE_OGLPLUS_MATH_MATRIX_HPP
