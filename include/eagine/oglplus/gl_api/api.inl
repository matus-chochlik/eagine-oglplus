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
  , viewport_array{"viewport_array", *this}
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
  , uniform1uiv{"uniform1uiv", *this}
  , uniform2uiv{"uniform2uiv", *this}
  , uniform3uiv{"uniform3uiv", *this}
  , uniform4uiv{"uniform4uiv", *this}
  , uniform1iv{"uniform1iv", *this}
  , uniform2iv{"uniform2iv", *this}
  , uniform3iv{"uniform3iv", *this}
  , uniform4iv{"uniform4iv", *this}
  , uniform1fv{"uniform1fv", *this}
  , uniform2fv{"uniform2fv", *this}
  , uniform3fv{"uniform3fv", *this}
  , uniform4fv{"uniform4fv", *this}
  , uniform_matrix2fv{"uniform_matrix2fv", *this}
  , uniform_matrix3fv{"uniform_matrix3fv", *this}
  , uniform_matrix4fv{"uniform_matrix4fv", *this}
  , uniform_matrix2x3fv{"uniform_matrix2x3fv", *this}
  , uniform_matrix2x4fv{"uniform_matrix2x4fv", *this}
  , uniform_matrix3x2fv{"uniform_matrix3x2fv", *this}
  , uniform_matrix3x4fv{"uniform_matrix3x4fv", *this}
  , uniform_matrix4x2fv{"uniform_matrix4x2fv", *this}
  , uniform_matrix4x3fv{"uniform_matrix4x3fv", *this}
  , program_uniform1uiv{"program_uniform1uiv", *this}
  , program_uniform2uiv{"program_uniform2uiv", *this}
  , program_uniform3uiv{"program_uniform3uiv", *this}
  , program_uniform4uiv{"program_uniform4uiv", *this}
  , program_uniform1iv{"program_uniform1iv", *this}
  , program_uniform2iv{"program_uniform2iv", *this}
  , program_uniform3iv{"program_uniform3iv", *this}
  , program_uniform4iv{"program_uniform4iv", *this}
  , program_uniform1fv{"program_uniform1fv", *this}
  , program_uniform2fv{"program_uniform2fv", *this}
  , program_uniform3fv{"program_uniform3fv", *this}
  , program_uniform4fv{"program_uniform4fv", *this}
  , program_uniform_matrix2fv{"program_uniform_matrix2fv", *this}
  , program_uniform_matrix3fv{"program_uniform_matrix3fv", *this}
  , program_uniform_matrix4fv{"program_uniform_matrix4fv", *this}
  , program_uniform_matrix2x3fv{"program_uniform_matrix2x3fv", *this}
  , program_uniform_matrix2x4fv{"program_uniform_matrix2x4fv", *this}
  , program_uniform_matrix3x2fv{"program_uniform_matrix3x2fv", *this}
  , program_uniform_matrix3x4fv{"program_uniform_matrix3x4fv", *this}
  , program_uniform_matrix4x2fv{"program_uniform_matrix4x2fv", *this}
  , program_uniform_matrix4x3fv{"program_uniform_matrix4x3fv", *this}
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
  , bind_framebuffer{"bind_framebuffer", *this}
  , draw_buffer{"draw_buffer", *this}
  , named_framebuffer_draw_buffer{"named_framebuffer_draw_buffer", *this}
  , read_buffer{"read_buffer", *this}
  , named_framebuffer_read_buffer{"named_framebuffer_read_buffer", *this}
  , framebuffer_parameter_i{"framebuffer_parameter_i", *this}
  , named_framebuffer_parameter_i{"named_framebuffer_parameter_i", *this}
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
  , framebuffer_renderbuffer{"framebuffer_renderbuffer", *this}
  , named_framebuffer_renderbuffer{
      "named_framebuffer_renderbuffer",
      *this}
  , framebuffer_texture{"framebuffer_texture", *this}
  , named_framebuffer_texture{"named_framebuffer_texture", *this}
  , framebuffer_texture1d{"framebuffer_texture1d", *this}
  , framebuffer_texture2d{"framebuffer_texture2d", *this}
  , framebuffer_texture3d{"framebuffer_texture3d", *this}
  , framebuffer_texture_layer{"framebuffer_texture_layer", *this}
  , named_framebuffer_texture_layer{
      "named_framebuffer_texture_layer",
      *this}
  , check_framebuffer_status{"check_framebuffer_status", *this}
  , check_named_framebuffer_status{
      "check_named_framebuffer_status",
      *this}
  , blit_framebuffer{"blit_framebuffer", *this}
  , blit_named_framebuffer{"blit_named_framebuffer", *this}
  , bind_transform_feedback{"bind_transform_feedback", *this}
  , begin_transform_feedback{"begin_transform_feedback", *this}
  , pause_transform_feedback{"pause_transform_feedback", *this}
  , resume_transform_feedback{"resume_transform_feedback", *this}
  , end_transform_feedback{"end_transform_feedback", *this}
  , transform_feedback_buffer_base{
      "transform_feedback_buffer_base",
      *this}
  , transform_feedback_buffer_range{
      "transform_feedback_buffer_range",
      *this}
  , get_transform_feedback_i{"get_transform_feedback_i", *this}
  , get_transform_feedback_ii{"get_transform_feedback_ii", *this}
  , get_transform_feedback_i64i{"get_transform_feedback_i64i", *this}
  , get_query_i{"get_query_i", *this}
  , get_query_indexed_i{"get_query_indexed_i", *this}
  , get_query_object_i{"get_query_object_i", *this}
  , get_query_object_ui{"get_query_object_ui", *this}
  , get_query_object_i64{"get_query_object_i64", *this}
  , get_query_object_ui64{"get_query_object_ui64", *this}
  , get_query_buffer_object_i{"get_query_buffer_object_i", *this}
  , get_query_buffer_object_ui{"get_query_buffer_object_ui", *this}
  , get_query_buffer_object_i64{"get_query_buffer_object_i64", *this}
  , get_query_buffer_object_ui64{"get_query_buffer_object_ui64", *this}
  , begin_query{"begin_query", *this}
  , begin_query_indexed{"begin_query_indexed", *this}
  , end_query{"end_query", *this}
  , end_query_indexed{"end_query_indexed", *this}
  , query_counter{"query_counter", *this}
  , begin_conditional_render{"begin_conditional_render", *this}
  , end_conditional_render{"end_conditional_render", *this}
  , bind_program_pipeline{"bind_program_pipeline", *this}
  , validate_program_pipeline{"validate_program_pipeline", *this}
  , use_program_stages{"use_program_stages", *this}
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
  , primitive_restart_index{"primitive_restart_index", *this}
  , provoking_vertex{"provoking_vertex", *this}
  , point_size{"point_size", *this}
  , line_width{"line_width", *this}
  , point_parameter_i{"point_parameter_i", *this}
  , point_parameter_f{"point_parameter_f", *this}
  , patch_parameter_i{"patch_parameter_i", *this}
  , patch_parameter_fv{"patch_parameter_fv", *this}
  , front_face{"front_face", *this}
  , cull_face{"cull_face", *this}
  , polygon_mode{"polygon_mode", *this}
  , polygon_offset{"polygon_offset", *this}
  , polygon_offset_clamp{"polygon_offset_clamp", *this}
  , blend_equation{"blend_equation", *this}
  , blend_equation_separate{"blend_equation_separate", *this}
  , blend_equationi{"blend_equationi", *this}
  , blend_equation_separatei{"blend_equation_separatei", *this}
  , blend_func{"blend_func", *this}
  , blend_func_separate{"blend_func_separate", *this}
  , blend_funci{"blend_funci", *this}
  , blend_func_separatei{"blend_func_separatei", *this}
  , sample_coverage{"sample_coverage", *this}
  , sample_mask_i{"sample_mask_i", *this}
  , min_sample_shading{"min_sample_shading", *this}
  , get_multisample_f{"get_multisample_f", *this}
  , draw_arrays{"draw_arrays", *this}
  , draw_arrays_instanced_base_instance{
      "draw_arrays_instanced_base_instance",
      *this}
  , draw_arrays_instanced{"draw_arrays_instanced", *this}
  , draw_arrays_indirect{"draw_arrays_indirect", *this}
  , multi_draw_arrays{"multi_draw_arrays", *this}
  , multi_draw_arrays_indirect{"multi_draw_arrays_indirect", *this}
  , multi_draw_arrays_indirect_count{
      "multi_draw_arrays_indirect_count",
      *this}
  , draw_elements{"draw_elements", *this}
  , draw_range_elements{"draw_range_elements", *this}
  , draw_elements_instanced_base_instance{
      "draw_elements_instanced_base_instance",
      *this}
  , draw_elements_instanced{"draw_elements_instanced", *this}
  , draw_elements_indirect{"draw_elements_indirect", *this}
  , draw_elements_base_vertex{"draw_elements_base_vertex", *this}
  , draw_range_elements_base_vertex{
      "draw_range_elements_base_vertex",
      *this}
  , draw_elements_instanced_base_vertex{
      "draw_elements_instanced_base_vertex",
      *this}
  , draw_elements_instanced_base_vertex_base_instance{
      "draw_elements_instanced_base_vertex_base_instance",
      *this}
  , dispatch_compute{"dispatch_compute", *this}
  , dispatch_compute_indirect{"dispatch_compute_indirect", *this}
  , read_pixels{"read_pixels", *this}
  , get_integer{"get_integer", *this}
  , get_integer64{"get_integer64", *this}
  , get_float{"get_float", *this}
  , get_double{"get_double", *this}
  , get_string{"get_string", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
