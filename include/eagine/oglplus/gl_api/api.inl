/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

namespace eagine::oglplus {
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_gl_operations<ApiTraits>::basic_gl_operations(api_traits& traits)
  : gl_api{traits}
  , ARB_debug_output{"ARB_debug_output", *this}
  , ARB_compatibility{"ARB_compatibility", *this}
  , ARB_robustness{"ARB_robustness", *this}
  , ARB_shading_language_include{"ARB_shading_language_include", *this}
  , uniform_subroutines{"uniform_subroutines", *this}
  , tex_parameter_i{"tex_parameter_i", *this}
  , texture_parameter_i{"texture_parameter_i", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
