/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_MATH_MATRIX_CTRS_HPP
#define EAGINE_OGLPLUS_MATH_MATRIX_CTRS_HPP

#include <eagine/math/matrix_reflection.hpp>
#include <eagine/math/matrix_rotation.hpp>
#include <eagine/math/matrix_scale.hpp>
#include <eagine/math/matrix_translation.hpp>

#include <eagine/math/matrix_looking_at.hpp>
#include <eagine/math/matrix_orbiting.hpp>

#include <eagine/math/matrix_ortho.hpp>
#include <eagine/math/matrix_perspective.hpp>

#include "config.hpp"
#include <eagine/oglplus/gl_api/config.hpp>

namespace eagine::oglplus {

/// @brief Alias for math::matrix_uniform_scale instantiation.
/// @ingroup gl_utils
using matrix_uniform_scale =
  math::matrix_uniform_scale<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_scale instantiation.
/// @ingroup gl_utils
using matrix_scale = math::matrix_scale<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_rotation_x instantiation.
/// @ingroup gl_utils
using matrix_rotation_x =
  math::matrix_rotation_x<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_rotation_y instantiation.
/// @ingroup gl_utils
using matrix_rotation_y =
  math::matrix_rotation_y<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_rotation_z instantiation.
/// @ingroup gl_utils
using matrix_rotation_z =
  math::matrix_rotation_z<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_translation instantiation.
/// @ingroup gl_utils
using matrix_translation =
  math::matrix_translation<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_reflection_x instantiation.
/// @ingroup gl_utils
using matrix_reflection_x =
  math::matrix_reflection_x<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_reflection_y instantiation.
/// @ingroup gl_utils
using matrix_reflection_y =
  math::matrix_reflection_y<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_reflection_z instantiation.
/// @ingroup gl_utils
using matrix_reflection_z =
  math::matrix_reflection_z<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_orbiting_y_up instantiation.
/// @ingroup gl_utils
using matrix_orbiting_y_up =
  math::matrix_orbiting_y_up<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_looking_at_y_up instantiation.
/// @ingroup gl_utils
using matrix_looking_at_y_up =
  math::matrix_looking_at_y_up<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_ortho instantiation.
/// @ingroup gl_utils
using matrix_ortho = math::matrix_ortho<gl_types::float_type, math_use_simd>;

/// @brief Alias for math::matrix_perspective instantiation.
/// @ingroup gl_utils
using matrix_perspective =
  math::matrix_perspective<gl_types::float_type, math_use_simd>;

} // namespace eagine::oglplus

#endif // EAGINE_OGLPLUS_MATH_MATRIX_CTRS_HPP
