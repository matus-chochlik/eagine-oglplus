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
  , get_shader_i{"get_shader_i", *this}
  , get_shader_info_log{"get_shader_info_log", *this}
  , get_program_i{"get_program_i", *this}
  , get_program_info_log{"get_program_info_log", *this}
  , get_shader_storage_block_index{
      "get_shader_storage_block_index",
      *this}
  , get_program_resource_name{"get_program_resource_name", *this}
  , get_program_interface_i{"get_program_interface_i", *this}
  , get_program_resource_i{"get_program_resource_i", *this}
  , get_program_resource_f{"get_program_resource_f", *this}
  , get_active_attrib_name{"get_active_attrib_name", *this}
  , transform_feedback_varyings{"transform_feedback_varyings", *this}
  , get_active_uniform_name{"get_active_uniform_name", *this}
  , get_active_subroutine_uniform_name{
      "get_active_subroutine_uniform_name",
      *this}
  , get_active_subroutine_name{"get_active_subroutine_name", *this}
  , uniform_subroutines{"uniform_subroutines", *this}
  , get_buffer_parameter_i{"get_buffer_parameter_i", *this}
  , get_named_buffer_parameter_i{"get_named_buffer_parameter_i", *this}
  , get_buffer_parameter_i64{"get_buffer_parameter_i64", *this}
  , get_named_buffer_parameter_i64{
      "get_named_buffer_parameter_i64",
      *this}
  , tex_image3d{"tex_image3d", *this}
  , tex_image2d{"tex_image2d", *this}
  , tex_image1d{"tex_image1d", *this}
  , tex_parameter_i{"tex_parameter_i", *this}
  , texture_parameter_i{"texture_parameter_i", *this}
  , get_tex_parameter_f{"get_tex_parameter_f", *this}
  , get_texture_parameter_f{"get_texture_parameter_f", *this}
  , get_tex_parameter_i{"get_tex_parameter_i", *this}
  , get_texture_parameter_i{"get_texture_parameter_i", *this}
  , get_tex_parameter_ii{"get_tex_parameter_ii", *this}
  , get_texture_parameter_ii{"get_texture_parameter_ii", *this}
  , get_tex_parameter_iui{"get_tex_parameter_iui", *this}
  , get_texture_parameter_iui{"get_texture_parameter_iui", *this}
  , get_sampler_parameter_f{"get_sampler_parameter_f", *this}
  , get_sampler_parameter_i{"get_sampler_parameter_i", *this}
  , get_sampler_parameter_ii{"get_sampler_parameter_ii", *this}
  , get_sampler_parameter_iui{"get_sampler_parameter_iui", *this}
  , get_renderbuffer_parameter_i{"get_renderbuffer_parameter_i", *this}
  , get_named_renderbuffer_parameter_i{
      "get_named_renderbuffer_parameter_i",
      *this}
  , get_framebuffer_parameter_i{"get_framebuffer_parameter_i", *this}
  , get_named_framebuffer_parameter_i{
      "get_named_framebuffer_parameter_i",
      *this}
  , get_framebuffer_attachment_parameter_i{
      "get_framebuffer_attachment_parameter_i",
      *this}
  , get_named_framebuffer_attachment_parameter_i{
      "get_named_framebuffer_attachment_parameter_i",
      *this}
  , end_transform_feedback{"end_transform_feedback", *this}
  , get_transform_feedback_i{"get_transform_feedback_i", *this}
  , get_transform_feedback_ii{"get_transform_feedback_ii", *this}
  , get_transform_feedback_i64i{"get_transform_feedback_i64i", *this}
  , get_query_i{"get_query_i", *this}
  , get_query_indexed_i{"get_query_indexed_i", *this}
  , get_query_object_i{"get_query_object_i", *this}
  , get_query_object_ui{"get_query_object_ui", *this}
  , get_query_object_i64{"get_query_object_i64", *this}
  , get_query_object_ui64{"get_query_object_ui64", *this}
  , get_program_stage_i{"get_program_stage_i", *this}
  , get_program_pipeline_i{"get_program_pipeline_i", *this}
  , get_program_pipeline_info_log{"get_program_pipeline_info_log", *this}
  , active_shader_program{"active_shader_program", *this}
  , path_color_gen_nv{"path_color_gen_nv", *this}
  , path_glyph_range_nv{"path_glyph_range_nv", *this}
  , get_path_spacing_nv{"get_path_spacing_nv", *this}
  , stencil_fill_path_nv{"stencil_fill_path_nv", *this}
  , stencil_stroke_path_nv{"stencil_stroke_path_nv", *this}
  , stencil_fill_path_instanced_nv{
      "stencil_fill_path_instanced_nv",
      *this}
  , stencil_stroke_path_instanced_nv{
      "stencil_stroke_path_instanced_nv",
      *this}
  , cover_fill_path_nv{"cover_fill_path_nv", *this}
  , cover_stroke_path_nv{"cover_stroke_path_nv", *this}
  , cover_fill_path_instanced_nv{"cover_fill_path_instanced_nv", *this}
  , cover_stroke_path_instanced_nv{
      "cover_stroke_path_instanced_nv",
      *this}
  , get_multisample_f{"get_multisample_f", *this}
  , get_integer{"get_integer", *this}
  , get_integer64{"get_integer64", *this}
  , get_float{"get_float", *this}
  , get_double{"get_double", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
