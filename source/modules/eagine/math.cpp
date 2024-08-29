/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:math;
import eagine.core.types;
import eagine.core.math;
import :config;

namespace eagine::oglplus {

//------------------------------------------------------------------------------
/// @brief Alias for math::sign.
/// @ingroup gl_utils
export using sign = math::sign<gl_types::float_type>;

/// @brief Alias for math::smooth_lerp.
/// @ingroup gl_utils
export using math::smooth_lerp;

/// @brief Alias for math::smooth_oscillate.
/// @ingroup gl_utils
export using math::smooth_oscillate;

/// @brief Alias for math::unit_spherical_coordinate instantiation.
/// @ingroup gl_utils
export using unit_spherical_coordinate =
  math::unit_spherical_coordinate<gl_types::float_type>;

export using math::to_cartesian;
export using math::to_unit_spherical;
//------------------------------------------------------------------------------
/// @brief Alias for math::line instantiation.
/// @ingroup gl_utils
export using line = math::line<gl_types::float_type>;

/// @brief Alias for math::sphere instantiation.
/// @ingroup gl_utils
export using sphere = math::sphere<gl_types::float_type>;

/// @brief Alias for math::triangle instantiation.
/// @ingroup gl_utils
export using triangle = math::triangle<gl_types::float_type>;
//------------------------------------------------------------------------------
/// @brief Alias for math::point.
/// @ingroup gl_utils
export using math::point;

/// @brief Alias 3D point.
/// @ingroup gl_utils
export using point3 = point<gl_types::float_type, 3>;
//------------------------------------------------------------------------------
/// @brief Alias for math::vector.
/// @ingroup gl_utils
export using math::vector;

/// @brief Alias for a floating-point 2D vector type.
/// @ingroup gl_utils
export using vec2 = vector<gl_types::float_type, 2>;

/// @brief Alias for a floating-point 3D vector type.
/// @ingroup gl_utils
export using vec3 = vector<gl_types::float_type, 3>;

/// @brief Alias for a floating-point 4D vector type.
/// @ingroup gl_utils
export using vec4 = vector<gl_types::float_type, 4>;

/// @brief Alias for a integer 2D vector type.
/// @ingroup gl_utils
export using ivec2 = vector<gl_types::int_type, 2>;

/// @brief Alias for a integer 3D vector type.
/// @ingroup gl_utils
export using ivec3 = vector<gl_types::int_type, 3>;

/// @brief Alias for a integer 4D vector type.
/// @ingroup gl_utils
export using ivec4 = vector<gl_types::int_type, 4>;
//------------------------------------------------------------------------------
/// @brief Alias for math::matrix.
/// @ingroup gl_utils
export using math::matrix;

/// @brief Template alias for float matrices.
/// @ingroup gl_utils
export template <unsigned C, unsigned R, bool RM>
using tfmat = matrix<gl_types::float_type, C, R, RM>;

/// @brief Template alias for column-major float matrices.
/// @ingroup gl_utils
export template <unsigned C, unsigned R = C>
using tcfmat = tfmat<C, R, false>;

/// @brief Template alias for row-major float matrices.
/// @ingroup gl_utils
export template <unsigned C, unsigned R = C>
using trfmat = tfmat<C, R, true>;

/// @brief Alias for 2x2 matrix.
/// @ingroup gl_utils
export using mat2 = tcfmat<2>;

/// @brief Alias for 2x3 matrix.
/// @ingroup gl_utils
export using mat2x3 = tcfmat<2, 3>;

/// @brief Alias for 2x4 matrix.
/// @ingroup gl_utils
export using mat2x4 = tcfmat<2, 4>;

/// @brief Alias for 3x2 matrix.
/// @ingroup gl_utils
export using mat3x2 = tcfmat<3, 2>;

/// @brief Alias for 3x3 matrix.
/// @ingroup gl_utils
export using mat3 = tcfmat<3>;

/// @brief Alias for 3x4 matrix.
/// @ingroup gl_utils
export using mat3x4 = tcfmat<3, 4>;

/// @brief Alias for 4x2 matrix.
/// @ingroup gl_utils
export using mat4x2 = tcfmat<4, 2>;

/// @brief Alias for 4x3 matrix.
/// @ingroup gl_utils
export using mat4x3 = tcfmat<4, 3>;

/// @brief Alias for 4x4 matrix.
/// @ingroup gl_utils
export using mat4 = tcfmat<4>;
//------------------------------------------------------------------------------
/// @brief Alias for math::matrix_uniform_scale instantiation.
/// @ingroup gl_utils
export using matrix_uniform_scale =
  math::matrix_uniform_scale<gl_types::float_type>;

/// @brief Alias for math::matrix_scale instantiation.
/// @ingroup gl_utils
export using matrix_scale = math::matrix_scale<gl_types::float_type>;

/// @brief Alias for math::matrix_rotation_x instantiation.
/// @ingroup gl_utils
export using matrix_rotation_x = math::matrix_rotation_x<gl_types::float_type>;

/// @brief Alias for math::matrix_rotation_y instantiation.
/// @ingroup gl_utils
export using matrix_rotation_y = math::matrix_rotation_y<gl_types::float_type>;

/// @brief Alias for math::matrix_rotation_z instantiation.
/// @ingroup gl_utils
export using matrix_rotation_z = math::matrix_rotation_z<gl_types::float_type>;

/// @brief Alias for math::matrix_translation instantiation.
/// @ingroup gl_utils
export using matrix_translation =
  math::matrix_translation<gl_types::float_type>;

/// @brief Alias for math::matrix_reflection_x instantiation.
/// @ingroup gl_utils
export using matrix_reflection_x =
  math::matrix_reflection_x<gl_types::float_type>;

/// @brief Alias for math::matrix_reflection_y instantiation.
/// @ingroup gl_utils
export using matrix_reflection_y =
  math::matrix_reflection_y<gl_types::float_type>;

/// @brief Alias for math::matrix_reflection_z instantiation.
/// @ingroup gl_utils
export using matrix_reflection_z =
  math::matrix_reflection_z<gl_types::float_type>;

/// @brief Alias for math::matrix_orbiting_y_up instantiation.
/// @ingroup gl_utils
export using matrix_orbiting_y_up =
  math::matrix_orbiting_y_up<gl_types::float_type>;

/// @brief Alias for math::matrix_looking_at_y_up instantiation.
/// @ingroup gl_utils
export using matrix_looking_at_y_up =
  math::matrix_looking_at_y_up<gl_types::float_type>;

/// @brief Alias for math::matrix_ortho instantiation.
/// @ingroup gl_utils
export using matrix_ortho = math::matrix_ortho<gl_types::float_type>;

/// @brief Alias for math::matrix_perspective instantiation.
/// @ingroup gl_utils
export using matrix_perspective =
  math::matrix_perspective<gl_types::float_type>;
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

