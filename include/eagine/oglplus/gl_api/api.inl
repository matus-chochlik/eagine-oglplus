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
  , get_program_resource_i{"get_program_resource_i", *this}
  , get_program_resource_f{"get_program_resource_f", *this}
  , get_active_attrib_name{"get_active_attrib_name", *this}
  , get_active_uniform_name{"get_active_uniform_name", *this}
  , get_active_subroutine_uniform_name{"get_active_subroutine_uniform_name", *this}
  , get_active_subroutine_name{"get_active_subroutine_name", *this}
  , uniform_subroutines{"uniform_subroutines", *this}
  , tex_parameter_i{"tex_parameter_i", *this}
  , texture_parameter_i{"texture_parameter_i", *this}
  , path_color_gen_nv{"path_color_gen_nv", *this}
  , path_glyph_range_nv{"path_glyph_range_nv", *this}
  , get_path_spacing_nv{"get_path_spacing_nv", *this}
  , stencil_fill_path_nv{"stencil_fill_path_nv", *this}
  , stencil_stroke_path_nv{"stencil_stroke_path_nv", *this}
  , stencil_fill_path_instanced_nv{"stencil_fill_path_instanced_nv", *this}
  , stencil_stroke_path_instanced_nv{"stencil_stroke_path_instanced_nv", *this}
  , cover_fill_path_nv{"cover_fill_path_nv", *this}
  , cover_stroke_path_nv{"cover_stroke_path_nv", *this}
  , cover_fill_path_instanced_nv{"cover_fill_path_instanced_nv", *this}
  , cover_stroke_path_instanced_nv{"cover_stroke_path_instanced_nv", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
