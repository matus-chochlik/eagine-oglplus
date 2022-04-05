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
  , delete_paths_nv{"delete_paths_nv", *this}
  , viewport{"viewport", *this}
  , viewport_array{"viewport_array", *this}
  , stencil_func{"stencil_func", *this}
  , shader_source{"shader_source", *this}
  , compile_shader_include{"compile_shader_include", *this}
  , get_shader_i{"get_shader_i", *this}
  , get_shader_info_log{"get_shader_info_log", *this}
  , get_program_i{"get_program_i", *this}
  , get_program_info_log{"get_program_info_log", *this}
  , get_program_resource_index{"get_program_resource_index", *this}
  , get_shader_storage_block_index{
      "get_shader_storage_block_index",
      *this}
  , get_program_resource_name{"get_program_resource_name", *this}
  , get_program_interface_i{"get_program_interface_i", *this}
  , get_program_resource_i{"get_program_resource_i", *this}
  , get_program_resource_f{"get_program_resource_f", *this}
  , bind_attrib_location{"bind_attrib_location", *this}
  , get_attrib_location{"get_attrib_location", *this}
  , get_active_attrib_name{"get_active_attrib_name", *this}
  , transform_feedback_varyings{"transform_feedback_varyings", *this}
  , bind_frag_data_location{"bind_frag_data_location", *this}
  , get_frag_data_location{"get_frag_data_location", *this}
  , get_frag_data_index{"get_frag_data_index", *this}
  , bind_frag_data_location_indexed{
      "bind_frag_data_location_indexed",
      *this}
  , get_uniform_location{"get_uniform_location", *this}
  , get_uniform_block_index{"get_uniform_block_index", *this}
  , get_active_uniform_name{"get_active_uniform_name", *this}
  , get_subroutine_uniform_location{
      "get_subroutine_uniform_location",
      *this}
  , get_active_subroutine_uniform_name{
      "get_active_subroutine_uniform_name",
      *this}
  , get_subroutine_index{"get_subroutine_index", *this}
  , get_active_subroutine_name{"get_active_subroutine_name", *this}
  , uniform_subroutines{"uniform_subroutines", *this}
  , uniform1ui{"uniform1ui", *this}
  , uniform2ui{"uniform2ui", *this}
  , uniform3ui{"uniform3ui", *this}
  , uniform4ui{"uniform4ui", *this}
  , uniform1uiv{"uniform1uiv", *this}
  , uniform2uiv{"uniform2uiv", *this}
  , uniform3uiv{"uniform3uiv", *this}
  , uniform4uiv{"uniform4uiv", *this}
  , uniform1i{"uniform1i", *this}
  , uniform2i{"uniform2i", *this}
  , uniform3i{"uniform3i", *this}
  , uniform4i{"uniform4i", *this}
  , uniform1iv{"uniform1iv", *this}
  , uniform2iv{"uniform2iv", *this}
  , uniform3iv{"uniform3iv", *this}
  , uniform4iv{"uniform4iv", *this}
  , uniform1f{"uniform1f", *this}
  , uniform2f{"uniform2f", *this}
  , uniform3f{"uniform3f", *this}
  , uniform4f{"uniform4f", *this}
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
  , program_uniform1ui{"program_uniform1ui", *this}
  , program_uniform2ui{"program_uniform2ui", *this}
  , program_uniform3ui{"program_uniform3ui", *this}
  , program_uniform4ui{"program_uniform4ui", *this}
  , program_uniform1uiv{"program_uniform1uiv", *this}
  , program_uniform2uiv{"program_uniform2uiv", *this}
  , program_uniform3uiv{"program_uniform3uiv", *this}
  , program_uniform4uiv{"program_uniform4uiv", *this}
  , program_uniform1i{"program_uniform1i", *this}
  , program_uniform2i{"program_uniform2i", *this}
  , program_uniform3i{"program_uniform3i", *this}
  , program_uniform4i{"program_uniform4i", *this}
  , program_uniform1iv{"program_uniform1iv", *this}
  , program_uniform2iv{"program_uniform2iv", *this}
  , program_uniform3iv{"program_uniform3iv", *this}
  , program_uniform4iv{"program_uniform4iv", *this}
  , program_uniform1f{"program_uniform1f", *this}
  , program_uniform2f{"program_uniform2f", *this}
  , program_uniform3f{"program_uniform3f", *this}
  , program_uniform4f{"program_uniform4f", *this}
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
  , uniform_block_binding{"uniform_block_binding", *this}
  , shader_storage_block_binding{"shader_storage_block_binding", *this}
  , bind_buffer{"bind_buffer", *this}
  , bind_buffer_base{"bind_buffer_base", *this}
  , bind_buffer_range{"bind_buffer_range", *this}
  , buffer_storage{"buffer_storage", *this}
  , named_buffer_storage{"named_buffer_storage", *this}
  , buffer_data{"buffer_data", *this}
  , named_buffer_data{"named_buffer_data", *this}
  , buffer_sub_data{"buffer_sub_data", *this}
  , named_buffer_sub_data{"named_buffer_sub_data", *this}
  , clear_buffer_data{"clear_buffer_data", *this}
  , clear_named_buffer_data{"clear_named_buffer_data", *this}
  , clear_buffer_sub_data{"clear_buffer_sub_data", *this}
  , clear_named_buffer_sub_data{"clear_named_buffer_sub_data", *this}
  , map_buffer{"map_buffer", *this}
  , map_named_buffer{"map_named_buffer", *this}
  , map_buffer_range{"map_buffer_range", *this}
  , map_named_buffer_range{"map_named_buffer_range", *this}
  , flush_mapped_buffer_range{"flush_mapped_buffer_range", *this}
  , flush_mapped_named_buffer_range{
      "flush_mapped_named_buffer_range",
      *this}
  , unmap_buffer{"unmap_buffer", *this}
  , unmap_named_buffer{"unmap_named_buffer", *this}
  , invalidate_buffer_data{"invalidate_buffer_data", *this}
  , invalidate_buffer_sub_data{"invalidate_buffer_sub_data", *this}
  , copy_buffer_sub_data{"copy_buffer_sub_data", *this}
  , copy_named_buffer_sub_data{"copy_named_buffer_sub_data", *this}
  , get_buffer_parameter_i{"get_buffer_parameter_i", *this}
  , get_named_buffer_parameter_i{"get_named_buffer_parameter_i", *this}
  , get_buffer_parameter_i64{"get_buffer_parameter_i64", *this}
  , get_named_buffer_parameter_i64{
      "get_named_buffer_parameter_i64",
      *this}
  , bind_vertex_array{"bind_vertex_array", *this}
  , bind_vertex_buffer{"bind_vertex_buffer", *this}
  , vertex_array_vertex_buffer{"vertex_array_vertex_buffer", *this}
  , vertex_array_element_buffer{"vertex_array_element_buffer", *this}
  , enable_vertex_attrib_array{"enable_vertex_attrib_array", *this}
  , enable_vertex_array_attrib{"enable_vertex_array_attrib", *this}
  , disable_vertex_attrib_array{"disable_vertex_attrib_array", *this}
  , disable_vertex_array_attrib{"disable_vertex_array_attrib", *this}
  , vertex_attrib_format{"vertex_attrib_format", *this}
  , vertex_attrib_iformat{"vertex_attrib_iformat", *this}
  , vertex_attrib_lformat{"vertex_attrib_lformat", *this}
  , vertex_array_attrib_format{"vertex_array_attrib_format", *this}
  , vertex_array_attrib_iformat{"vertex_array_attrib_iformat", *this}
  , vertex_array_attrib_lformat{"vertex_array_attrib_lformat", *this}
  , vertex_attrib_pointer{"vertex_attrib_pointer", *this}
  , vertex_attrib_ipointer{"vertex_attrib_ipointer", *this}
  , vertex_attrib_lpointer{"vertex_attrib_lpointer", *this}
  , vertex_attrib_binding{"vertex_attrib_binding", *this}
  , vertex_array_attrib_binding{"vertex_array_attrib_binding", *this}
  , vertex_binding_divisor{"vertex_binding_divisor", *this}
  , vertex_array_binding_divisor{"vertex_array_binding_divisor", *this}
  , vertex_attrib_divisor{"vertex_attrib_divisor", *this}
  , active_texture{"active_texture", *this}
  , bind_texture{"bind_texture", *this}
  , bind_textures{"bind_textures", *this}
  , bind_texture_unit{"bind_texture_unit", *this}
  , bind_image_texture{"bind_image_texture", *this}
  , tex_storage3d{"tex_storage3d", *this}
  , texture_storage3d{"texture_storage3d", *this}
  , tex_storage2d{"tex_storage2d", *this}
  , texture_storage2d{"texture_storage2d", *this}
  , tex_storage1d{"tex_storage1d", *this}
  , texture_storage1d{"texture_storage1d", *this}
  , tex_storage3d_multisample{"tex_storage3d_multisample", *this}
  , texture_storage3d_multisample{"texture_storage3d_multisample", *this}
  , tex_storage2d_multisample{"tex_storage2d_multisample", *this}
  , texture_storage2d_multisample{"texture_storage2d_multisample", *this}
  , tex_image3d{"tex_image3d", *this}
  , tex_image2d{"tex_image2d", *this}
  , tex_image1d{"tex_image1d", *this}
  , tex_sub_image3d{"tex_sub_image3d", *this}
  , texture_sub_image3d{"texture_sub_image3d", *this}
  , tex_sub_image2d{"tex_sub_image2d", *this}
  , texture_sub_image2d{"texture_sub_image2d", *this}
  , tex_sub_image1d{"tex_sub_image1d", *this}
  , texture_sub_image1d{"texture_sub_image1d", *this}
  , copy_tex_image2d{"copy_tex_image2d", *this}
  , copy_tex_image1d{"copy_tex_image1d", *this}
  , copy_tex_sub_image3d{"copy_tex_sub_image3d", *this}
  , copy_texture_sub_image3d{"copy_texture_sub_image3d", *this}
  , copy_tex_sub_image2d{"copy_tex_sub_image2d", *this}
  , copy_texture_sub_image2d{"copy_texture_sub_image2d", *this}
  , copy_tex_sub_image1d{"copy_tex_sub_image1d", *this}
  , copy_texture_sub_image1d{"copy_texture_sub_image1d", *this}
  , compressed_tex_image3d{"compressed_tex_image3d", *this}
  , compressed_tex_image2d{"compressed_tex_image2d", *this}
  , compressed_tex_image1d{"compressed_tex_image1d", *this}
  , compressed_tex_sub_image3d{"compressed_tex_sub_image3d", *this}
  , compressed_texture_sub_image3d{
      "compressed_texture_sub_image3d",
      *this}
  , compressed_tex_sub_image2d{"compressed_tex_sub_image2d", *this}
  , compressed_texture_sub_image2d{
      "compressed_texture_sub_image2d",
      *this}
  , compressed_tex_sub_image1d{"compressed_tex_sub_image1d", *this}
  , compressed_texture_sub_image1d{
      "compressed_texture_sub_image1d",
      *this}
  , tex_buffer{"tex_buffer", *this}
  , texture_buffer{"texture_buffer", *this}
  , tex_buffer_range{"tex_buffer_range", *this}
  , texture_buffer_range{"texture_buffer_range", *this}
  , tex_parameter_f{"tex_parameter_f", *this}
  , texture_parameter_f{"texture_parameter_f", *this}
  , tex_parameter_i{"tex_parameter_i", *this}
  , texture_parameter_i{"texture_parameter_i", *this}
  , tex_parameter_fv{"tex_parameter_fv", *this}
  , texture_parameter_fv{"texture_parameter_fv", *this}
  , tex_parameter_iv{"tex_parameter_iv", *this}
  , texture_parameter_iv{"texture_parameter_iv", *this}
  , tex_parameter_iiv{"tex_parameter_iiv", *this}
  , texture_parameter_iiv{"texture_parameter_iiv", *this}
  , tex_parameter_iuiv{"tex_parameter_iuiv", *this}
  , texture_parameter_iuiv{"texture_parameter_iuiv", *this}
  , get_tex_parameter_f{"get_tex_parameter_f", *this}
  , get_texture_parameter_f{"get_texture_parameter_f", *this}
  , get_tex_parameter_i{"get_tex_parameter_i", *this}
  , get_texture_parameter_i{"get_texture_parameter_i", *this}
  , get_tex_parameter_ii{"get_tex_parameter_ii", *this}
  , get_texture_parameter_ii{"get_texture_parameter_ii", *this}
  , get_tex_parameter_iui{"get_tex_parameter_iui", *this}
  , get_texture_parameter_iui{"get_texture_parameter_iui", *this}
  , generate_mipmap{"generate_mipmap", *this}
  , generate_texture_mipmap{"generate_texture_mipmap", *this}
  , bind_sampler{"bind_sampler", *this}
  , sampler_parameter_f{"sampler_parameter_f", *this}
  , sampler_parameter_i{"sampler_parameter_i", *this}
  , sampler_parameter_fv{"sampler_parameter_fv", *this}
  , sampler_parameter_iv{"sampler_parameter_iv", *this}
  , sampler_parameter_iiv{"sampler_parameter_iiv", *this}
  , sampler_parameter_iuiv{"sampler_parameter_iuiv", *this}
  , get_sampler_parameter_f{"get_sampler_parameter_f", *this}
  , get_sampler_parameter_i{"get_sampler_parameter_i", *this}
  , get_sampler_parameter_ii{"get_sampler_parameter_ii", *this}
  , get_sampler_parameter_iui{"get_sampler_parameter_iui", *this}
  , bind_renderbuffer{"bind_renderbuffer", *this}
  , renderbuffer_storage{"renderbuffer_storage", *this}
  , named_renderbuffer_storage{"named_renderbuffer_storage", *this}
  , renderbuffer_storage_multisample{
      "renderbuffer_storage_multisample",
      *this}
  , named_renderbuffer_storage_multisample{
      "named_renderbuffer_storage_multisample",
      *this}
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
  , get_string{"get_string", *this}
  , named_string{"named_string", *this}
  , delete_named_string{"delete_named_string", *this}
  , is_named_string{"is_named_string", *this}
  , begin{"begin", *this}
  , end{"end", *this}
  , vertex2i{"vertex2i", *this}
  , vertex3i{"vertex3i", *this}
  , vertex4i{"vertex4i", *this}
  , vertex2f{"vertex2f", *this}
  , vertex3f{"vertex3f", *this}
  , vertex4f{"vertex4f", *this}
  , color3i{"color3i", *this}
  , color4i{"color4i", *this}
  , color3f{"color3f", *this}
  , color4f{"color4f", *this}
  , secondary_color3i{"secondary_color3i", *this}
  , secondary_color4i{"secondary_color4i", *this}
  , secondary_color3f{"secondary_color3f", *this}
  , secondary_color4f{"secondary_color4f", *this}
  , tex_coord1i{"tex_coord1i", *this}
  , tex_coord2i{"tex_coord2i", *this}
  , tex_coord3i{"tex_coord3i", *this}
  , tex_coord4i{"tex_coord4i", *this}
  , tex_coord1f{"tex_coord1f", *this}
  , tex_coord2f{"tex_coord2f", *this}
  , tex_coord3f{"tex_coord3f", *this}
  , tex_coord4f{"tex_coord4f", *this}
  , multi_tex_coord1i{"multi_tex_coord1i", *this}
  , multi_tex_coord2i{"multi_tex_coord2i", *this}
  , multi_tex_coord3i{"multi_tex_coord3i", *this}
  , multi_tex_coord4i{"multi_tex_coord4i", *this}
  , multi_tex_coord1f{"multi_tex_coord1f", *this}
  , multi_tex_coord2f{"multi_tex_coord2f", *this}
  , multi_tex_coord3f{"multi_tex_coord3f", *this}
  , multi_tex_coord4f{"multi_tex_coord4f", *this}
  , matrix_mode{"matrix_mode", *this}
  , push_matrix{"push_matrix", *this}
  , pop_matrix{"pop_matrix", *this}
  , load_identity{"load_identity", *this}
  , translate_f{"translate_f", *this}
  , translate_d{"translate_d", *this}
  , rotate_f{"rotate_f", *this}
  , rotate_d{"rotate_d", *this}
  , scale_f{"scale_f", *this}
  , scale_d{"scale_d", *this}
  , frustum{"frustum", *this}
  , ortho{"ortho", *this}
  , load_matrix_f{"load_matrix_f", *this}
  , load_matrix_d{"load_matrix_d", *this}
  , mult_matrix_f{"mult_matrix_f", *this}
  , mult_matrix_d{"mult_matrix_d", *this}
  , load_transpose_matrix_f{"load_transpose_matrix_f", *this}
  , load_transpose_matrix_d{"load_transpose_matrix_d", *this}
  , mult_transpose_matrix_f{"mult_transpose_matrix_f", *this}
  , mult_transpose_matrix_d{"mult_transpose_matrix_d", *this}
  , debug_message_control{"debug_message_control", *this}
  , debug_message_insert{"debug_message_insert", *this}
  , debug_message_callback{"debug_message_callback", *this}
  , push_debug_group{"push_debug_group", *this}
  , pop_debug_group{"pop_debug_group", *this}
  , object_label{"object_label", *this}
  , flush{"flush", *this}
  , finish{"finish", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
