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
  : c_api{traits}
  , ARB_debug_output{"ARB_debug_output", traits, *this}
  , ARB_compatibility{"ARB_compatibility", traits, *this}
  , ARB_robustness{"ARB_robustness", traits, *this}
  , ARB_shading_language_include{"ARB_shading_language_include", traits, *this}
  , fence_sync{"fence_sync", traits, *this}
  , create_shader{"create_shader", traits, *this}
  , create_program{"create_program", traits, *this}
  , gen_buffers{"gen_buffers", traits, *this}
  , create_buffers{"create_buffers", traits, *this}
  , gen_framebuffers{"gen_framebuffers", traits, *this}
  , create_framebuffers{"create_framebuffers", traits, *this}
  , gen_program_pipelines{"gen_program_pipelines", traits, *this}
  , create_program_pipelines{"create_program_pipelines", traits, *this}
  , gen_queries{"gen_queries", traits, *this}
  , create_queries{"create_queries", traits, *this}
  , gen_renderbuffers{"gen_renderbuffers", traits, *this}
  , create_renderbuffers{"create_renderbuffers", traits, *this}
  , gen_samplers{"gen_samplers", traits, *this}
  , create_samplers{"create_samplers", traits, *this}
  , gen_textures{"gen_textures", traits, *this}
  , create_textures{"create_textures", traits, *this}
  , gen_transform_feedbacks{"gen_transform_feedbacks", traits, *this}
  , create_transform_feedbacks{"create_transform_feedbacks", traits, *this}
  , gen_vertex_arrays{"gen_vertex_arrays", traits, *this}
  , create_vertex_arrays{"create_vertex_arrays", traits, *this}
  , create_paths_nv{"create_paths_nv", traits, *this}
  , delete_sync{"delete_sync", traits, *this}
  , delete_shader{"delete_shader", traits, *this}
  , delete_program{"delete_program", traits, *this}
  , delete_buffers{"delete_buffers", traits, *this}
  , delete_framebuffers{"delete_framebuffers", traits, *this}
  , delete_program_pipelines{"delete_program_pipelines", traits, *this}
  , delete_queries{"delete_queries", traits, *this}
  , delete_renderbuffers{"delete_renderbuffers", traits, *this}
  , delete_samplers{"delete_samplers", traits, *this}
  , delete_textures{"delete_textures", traits, *this}
  , delete_transform_feedbacks{"delete_transform_feedbacks", traits, *this}
  , delete_vertex_arrays{"delete_vertex_arrays", traits, *this}
  , delete_paths_nv{"delete_paths_nv", traits, *this}
  , is_sync{"is_sync", traits, *this}
  , is_buffer{"is_buffer", traits, *this}
  , is_framebuffer{"is_framebuffer", traits, *this}
  , is_program_pipeline{"is_program_pipeline", traits, *this}
  , is_program{"is_program", traits, *this}
  , is_query{"is_query", traits, *this}
  , is_renderbuffer{"is_renderbuffer", traits, *this}
  , is_sampler{"is_sampler", traits, *this}
  , is_shader{"is_shader", traits, *this}
  , is_texture{"is_texture", traits, *this}
  , is_transform_feedback{"is_transform_feedback", traits, *this}
  , is_vertex_array{"is_vertex_array", traits, *this}
  , is_path_nv{"is_path_nv", traits, *this}
  , enable{"enable", traits, *this}
  , enablei{"enablei", traits, *this}
  , disable{"disable", traits, *this}
  , disablei{"disablei", traits, *this}
  , is_enabled{"is_enabled", traits, *this}
  , is_enabledi{"is_enabledi", traits, *this}
  , memory_barrier{"memory_barrier", traits, *this}
  , memory_barrier_by_region{"memory_barrier_by_region", traits, *this}
  , viewport{"viewport", traits, *this}
  , stencil_func{"stencil_func", traits, *this}
  , stencil_func_separate{"stencil_func_separate", traits, *this}
  , stencil_op{"stencil_op", traits, *this}
  , stencil_op_separate{"stencil_op_separate", traits, *this}
  , depth_func{"depth_func", traits, *this}
  , color_mask{"color_mask", traits, *this}
  , color_mask_i{"color_mask_i", traits, *this}
  , depth_mask{"depth_mask", traits, *this}
  , stencil_mask{"stencil_mask", traits, *this}
  , stencil_mask_separate{"stencil_mask_separate", traits, *this}
  , clear_color{"clear_color", traits, *this}
  , clear_depth{"clear_depth", traits, *this}
  , clear_stencil{"clear_stencil", traits, *this}
  , clear{"clear", traits, *this}
  , shader_source{"shader_source", traits, *this}
  , compile_shader{"compile_shader", traits, *this}
  , compile_shader_include{"compile_shader_include", traits, *this}
  , get_shader_i{"get_shader_i", traits, *this}
  , get_shader_info_log{"get_shader_info_log", traits, *this}
  , attach_shader{"attach_shader", traits, *this}
  , detach_shader{"detach_shader", traits, *this}
  , link_program{"link_program", traits, *this}
  , get_program_i{"get_program_i", traits, *this}
  , get_program_info_log{"get_program_info_log", traits, *this}
  , use_program{"use_program", traits, *this}
  , get_program_resource_index{"get_program_resource_index", traits, *this}
  , get_shader_storage_block_index{
      "get_shader_storage_block_index",
      traits,
      *this}
  , get_program_resource_location{"get_program_resource_location", traits, *this}
  , get_program_resource_name{"get_program_resource_name", traits, *this}
  , get_program_interface_i{"get_program_interface_i", traits, *this}
  , get_program_resource_i{"get_program_resource_i", traits, *this}
  , get_program_resource_f{"get_program_resource_f", traits, *this}
  , bind_attrib_location{"bind_attrib_location", traits, *this}
  , get_attrib_location{"get_attrib_location", traits, *this}
  , get_active_attrib_name{"get_active_attrib_name", traits, *this}
  , transform_feedback_varyings{"transform_feedback_varyings", traits, *this}
  , bind_frag_data_location{"bind_frag_data_location", traits, *this}
  , get_frag_data_location{"get_frag_data_location", traits, *this}
  , get_frag_data_index{"get_frag_data_index", traits, *this}
  , bind_frag_data_location_indexed{
      "bind_frag_data_location_indexed",
      traits,
      *this}
  , get_uniform_location{"get_uniform_location", traits, *this}
  , get_uniform_block_index{"get_uniform_block_index", traits, *this}
  , get_active_uniform_name{"get_active_uniform_name", traits, *this}
  , get_subroutine_uniform_location{
      "get_subroutine_uniform_location",
      traits,
      *this}
  , get_active_subroutine_uniform_name{
      "get_active_subroutine_uniform_name",
      traits,
      *this}
  , get_subroutine_index{"get_subroutine_index", traits, *this}
  , get_active_subroutine_name{"get_active_subroutine_name", traits, *this}
  , uniform_subroutines{"uniform_subroutines", traits, *this}
  , uniform1ui{"uniform1ui", traits, *this}
  , uniform2ui{"uniform2ui", traits, *this}
  , uniform3ui{"uniform3ui", traits, *this}
  , uniform4ui{"uniform4ui", traits, *this}
  , uniform1uiv{"uniform1uiv", traits, *this}
  , uniform2uiv{"uniform2uiv", traits, *this}
  , uniform3uiv{"uniform3uiv", traits, *this}
  , uniform4uiv{"uniform4uiv", traits, *this}
  , uniform1i{"uniform1i", traits, *this}
  , uniform2i{"uniform2i", traits, *this}
  , uniform3i{"uniform3i", traits, *this}
  , uniform4i{"uniform4i", traits, *this}
  , uniform1iv{"uniform1iv", traits, *this}
  , uniform2iv{"uniform2iv", traits, *this}
  , uniform3iv{"uniform3iv", traits, *this}
  , uniform4iv{"uniform4iv", traits, *this}
  , uniform1f{"uniform1f", traits, *this}
  , uniform2f{"uniform2f", traits, *this}
  , uniform3f{"uniform3f", traits, *this}
  , uniform4f{"uniform4f", traits, *this}
  , uniform1fv{"uniform1fv", traits, *this}
  , uniform2fv{"uniform2fv", traits, *this}
  , uniform3fv{"uniform3fv", traits, *this}
  , uniform4fv{"uniform4fv", traits, *this}
  , uniform_matrix2fv{"uniform_matrix2fv", traits, *this}
  , uniform_matrix3fv{"uniform_matrix3fv", traits, *this}
  , uniform_matrix4fv{"uniform_matrix4fv", traits, *this}
  , uniform_matrix2x3fv{"uniform_matrix2x3fv", traits, *this}
  , uniform_matrix2x4fv{"uniform_matrix2x4fv", traits, *this}
  , uniform_matrix3x2fv{"uniform_matrix3x2fv", traits, *this}
  , uniform_matrix3x4fv{"uniform_matrix3x4fv", traits, *this}
  , uniform_matrix4x2fv{"uniform_matrix4x2fv", traits, *this}
  , uniform_matrix4x3fv{"uniform_matrix4x3fv", traits, *this}
  , program_uniform1ui{"program_uniform1ui", traits, *this}
  , program_uniform2ui{"program_uniform2ui", traits, *this}
  , program_uniform3ui{"program_uniform3ui", traits, *this}
  , program_uniform4ui{"program_uniform4ui", traits, *this}
  , program_uniform1uiv{"program_uniform1uiv", traits, *this}
  , program_uniform2uiv{"program_uniform2uiv", traits, *this}
  , program_uniform3uiv{"program_uniform3uiv", traits, *this}
  , program_uniform4uiv{"program_uniform4uiv", traits, *this}
  , program_uniform1i{"program_uniform1i", traits, *this}
  , program_uniform2i{"program_uniform2i", traits, *this}
  , program_uniform3i{"program_uniform3i", traits, *this}
  , program_uniform4i{"program_uniform4i", traits, *this}
  , program_uniform1iv{"program_uniform1iv", traits, *this}
  , program_uniform2iv{"program_uniform2iv", traits, *this}
  , program_uniform3iv{"program_uniform3iv", traits, *this}
  , program_uniform4iv{"program_uniform4iv", traits, *this}
  , program_uniform1f{"program_uniform1f", traits, *this}
  , program_uniform2f{"program_uniform2f", traits, *this}
  , program_uniform3f{"program_uniform3f", traits, *this}
  , program_uniform4f{"program_uniform4f", traits, *this}
  , program_uniform1fv{"program_uniform1fv", traits, *this}
  , program_uniform2fv{"program_uniform2fv", traits, *this}
  , program_uniform3fv{"program_uniform3fv", traits, *this}
  , program_uniform4fv{"program_uniform4fv", traits, *this}
  , program_uniform_matrix2fv{"program_uniform_matrix2fv", traits, *this}
  , program_uniform_matrix3fv{"program_uniform_matrix3fv", traits, *this}
  , program_uniform_matrix4fv{"program_uniform_matrix4fv", traits, *this}
  , program_uniform_matrix2x3fv{"program_uniform_matrix2x3fv", traits, *this}
  , program_uniform_matrix2x4fv{"program_uniform_matrix2x4fv", traits, *this}
  , program_uniform_matrix3x2fv{"program_uniform_matrix3x2fv", traits, *this}
  , program_uniform_matrix3x4fv{"program_uniform_matrix3x4fv", traits, *this}
  , program_uniform_matrix4x2fv{"program_uniform_matrix4x2fv", traits, *this}
  , program_uniform_matrix4x3fv{"program_uniform_matrix4x3fv", traits, *this}
  , uniform_block_binding{"uniform_block_binding", traits, *this}
  , shader_storage_block_binding{"shader_storage_block_binding", traits, *this}
  , bind_buffer{"bind_buffer", traits, *this}
  , bind_buffer_base{"bind_buffer_base", traits, *this}
  , bind_buffer_range{"bind_buffer_range", traits, *this}
  , buffer_storage{"buffer_storage", traits, *this}
  , named_buffer_storage{"named_buffer_storage", traits, *this}
  , buffer_data{"buffer_data", traits, *this}
  , named_buffer_data{"named_buffer_data", traits, *this}
  , buffer_sub_data{"buffer_sub_data", traits, *this}
  , named_buffer_sub_data{"named_buffer_sub_data", traits, *this}
  , clear_buffer_data{"clear_buffer_data", traits, *this}
  , clear_named_buffer_data{"clear_named_buffer_data", traits, *this}
  , clear_buffer_sub_data{"clear_buffer_sub_data", traits, *this}
  , clear_named_buffer_sub_data{"clear_named_buffer_sub_data", traits, *this}
  , map_buffer{"map_buffer", traits, *this}
  , map_named_buffer{"map_named_buffer", traits, *this}
  , map_buffer_range{"map_buffer_range", traits, *this}
  , map_named_buffer_range{"map_named_buffer_range", traits, *this}
  , flush_mapped_buffer_range{"flush_mapped_buffer_range", traits, *this}
  , flush_mapped_named_buffer_range{
      "flush_mapped_named_buffer_range",
      traits,
      *this}
  , unmap_buffer{"unmap_buffer", traits, *this}
  , unmap_named_buffer{"unmap_named_buffer", traits, *this}
  , invalidate_buffer_data{"invalidate_buffer_data", traits, *this}
  , invalidate_buffer_sub_data{"invalidate_buffer_sub_data", traits, *this}
  , copy_buffer_sub_data{"copy_buffer_sub_data", traits, *this}
  , copy_named_buffer_sub_data{"copy_named_buffer_sub_data", traits, *this}
  , get_buffer_parameter_i{"get_buffer_parameter_i", traits, *this}
  , get_named_buffer_parameter_i{"get_named_buffer_parameter_i", traits, *this}
  , get_buffer_parameter_i64{"get_buffer_parameter_i64", traits, *this}
  , get_named_buffer_parameter_i64{
      "get_named_buffer_parameter_i64",
      traits,
      *this}
  , bind_vertex_array{"bind_vertex_array", traits, *this}
  , bind_vertex_buffer{"bind_vertex_buffer", traits, *this}
  , vertex_array_vertex_buffer{"vertex_array_vertex_buffer", traits, *this}
  , vertex_array_element_buffer{"vertex_array_element_buffer", traits, *this}
  , enable_vertex_attrib_array{"enable_vertex_attrib_array", traits, *this}
  , enable_vertex_array_attrib{"enable_vertex_array_attrib", traits, *this}
  , disable_vertex_attrib_array{"disable_vertex_attrib_array", traits, *this}
  , disable_vertex_array_attrib{"disable_vertex_array_attrib", traits, *this}
  , vertex_attrib_format{"vertex_attrib_format", traits, *this}
  , vertex_attrib_iformat{"vertex_attrib_iformat", traits, *this}
  , vertex_attrib_lformat{"vertex_attrib_lformat", traits, *this}
  , vertex_array_attrib_format{"vertex_array_attrib_format", traits, *this}
  , vertex_array_attrib_iformat{"vertex_array_attrib_iformat", traits, *this}
  , vertex_array_attrib_lformat{"vertex_array_attrib_lformat", traits, *this}
  , vertex_attrib_pointer{"vertex_attrib_pointer", traits, *this}
  , vertex_attrib_ipointer{"vertex_attrib_ipointer", traits, *this}
  , vertex_attrib_lpointer{"vertex_attrib_lpointer", traits, *this}
  , vertex_attrib_binding{"vertex_attrib_binding", traits, *this}
  , vertex_array_attrib_binding{"vertex_array_attrib_binding", traits, *this}
  , vertex_binding_divisor{"vertex_binding_divisor", traits, *this}
  , vertex_array_binding_divisor{"vertex_array_binding_divisor", traits, *this}
  , vertex_attrib_divisor{"vertex_attrib_divisor", traits, *this}
  , active_texture{"active_texture", traits, *this}
  , bind_texture{"bind_texture", traits, *this}
  , bind_textures{"bind_textures", traits, *this}
  , bind_texture_unit{"bind_texture_unit", traits, *this}
  , bind_image_texture{"bind_image_texture", traits, *this}
  , tex_storage3d{"tex_storage3d", traits, *this}
  , texture_storage3d{"texture_storage3d", traits, *this}
  , tex_storage2d{"tex_storage2d", traits, *this}
  , texture_storage2d{"texture_storage2d", traits, *this}
  , tex_storage1d{"tex_storage1d", traits, *this}
  , texture_storage1d{"texture_storage1d", traits, *this}
  , tex_storage3d_multisample{"tex_storage3d_multisample", traits, *this}
  , texture_storage3d_multisample{"texture_storage3d_multisample", traits, *this}
  , tex_storage2d_multisample{"tex_storage2d_multisample", traits, *this}
  , texture_storage2d_multisample{"texture_storage2d_multisample", traits, *this}
  , tex_image3d{"tex_image3d", traits, *this}
  , tex_image2d{"tex_image2d", traits, *this}
  , tex_image1d{"tex_image1d", traits, *this}
  , tex_sub_image3d{"tex_sub_image3d", traits, *this}
  , texture_sub_image3d{"texture_sub_image3d", traits, *this}
  , tex_sub_image2d{"tex_sub_image2d", traits, *this}
  , texture_sub_image2d{"texture_sub_image2d", traits, *this}
  , tex_sub_image1d{"tex_sub_image1d", traits, *this}
  , texture_sub_image1d{"texture_sub_image1d", traits, *this}
  , copy_tex_image2d{"copy_tex_image2d", traits, *this}
  , copy_tex_image1d{"copy_tex_image1d", traits, *this}
  , copy_tex_sub_image3d{"copy_tex_sub_image3d", traits, *this}
  , copy_texture_sub_image3d{"copy_texture_sub_image3d", traits, *this}
  , copy_tex_sub_image2d{"copy_tex_sub_image2d", traits, *this}
  , copy_texture_sub_image2d{"copy_texture_sub_image2d", traits, *this}
  , copy_tex_sub_image1d{"copy_tex_sub_image1d", traits, *this}
  , copy_texture_sub_image1d{"copy_texture_sub_image1d", traits, *this}
  , compressed_tex_image3d{"compressed_tex_image3d", traits, *this}
  , compressed_tex_image2d{"compressed_tex_image2d", traits, *this}
  , compressed_tex_image1d{"compressed_tex_image1d", traits, *this}
  , compressed_tex_sub_image3d{"compressed_tex_sub_image3d", traits, *this}
  , compressed_texture_sub_image3d{
      "compressed_texture_sub_image3d",
      traits,
      *this}
  , compressed_tex_sub_image2d{"compressed_tex_sub_image2d", traits, *this}
  , compressed_texture_sub_image2d{
      "compressed_texture_sub_image2d",
      traits,
      *this}
  , compressed_tex_sub_image1d{"compressed_tex_sub_image1d", traits, *this}
  , compressed_texture_sub_image1d{
      "compressed_texture_sub_image1d",
      traits,
      *this}
  , tex_buffer{"tex_buffer", traits, *this}
  , texture_buffer{"texture_buffer", traits, *this}
  , tex_buffer_range{"tex_buffer_range", traits, *this}
  , texture_buffer_range{"texture_buffer_range", traits, *this}
  , tex_parameter_f{"tex_parameter_f", traits, *this}
  , texture_parameter_f{"texture_parameter_f", traits, *this}
  , tex_parameter_i{"tex_parameter_i", traits, *this}
  , texture_parameter_i{"texture_parameter_i", traits, *this}
  , tex_parameter_fv{"tex_parameter_fv", traits, *this}
  , texture_parameter_fv{"texture_parameter_fv", traits, *this}
  , tex_parameter_iv{"tex_parameter_iv", traits, *this}
  , texture_parameter_iv{"texture_parameter_iv", traits, *this}
  , tex_parameter_iiv{"tex_parameter_iiv", traits, *this}
  , texture_parameter_iiv{"texture_parameter_iiv", traits, *this}
  , tex_parameter_iuiv{"tex_parameter_iuiv", traits, *this}
  , texture_parameter_iuiv{"texture_parameter_iuiv", traits, *this}
  , get_tex_parameter_f{"get_tex_parameter_f", traits, *this}
  , get_texture_parameter_f{"get_texture_parameter_f", traits, *this}
  , get_tex_parameter_i{"get_tex_parameter_i", traits, *this}
  , get_texture_parameter_i{"get_texture_parameter_i", traits, *this}
  , get_tex_parameter_ii{"get_tex_parameter_ii", traits, *this}
  , get_texture_parameter_ii{"get_texture_parameter_ii", traits, *this}
  , get_tex_parameter_iui{"get_tex_parameter_iui", traits, *this}
  , get_texture_parameter_iui{"get_texture_parameter_iui", traits, *this}
  , generate_mipmap{"generate_mipmap", traits, *this}
  , generate_texture_mipmap{"generate_texture_mipmap", traits, *this}
  , bind_sampler{"bind_sampler", traits, *this}
  , sampler_parameter_f{"sampler_parameter_f", traits, *this}
  , sampler_parameter_i{"sampler_parameter_i", traits, *this}
  , sampler_parameter_fv{"sampler_parameter_fv", traits, *this}
  , sampler_parameter_iv{"sampler_parameter_iv", traits, *this}
  , sampler_parameter_iiv{"sampler_parameter_iiv", traits, *this}
  , sampler_parameter_iuiv{"sampler_parameter_iuiv", traits, *this}
  , get_sampler_parameter_f{"get_sampler_parameter_f", traits, *this}
  , get_sampler_parameter_i{"get_sampler_parameter_i", traits, *this}
  , get_sampler_parameter_ii{"get_sampler_parameter_ii", traits, *this}
  , get_sampler_parameter_iui{"get_sampler_parameter_iui", traits, *this}
  , bind_renderbuffer{"bind_renderbuffer", traits, *this}
  , renderbuffer_storage{"renderbuffer_storage", traits, *this}
  , named_renderbuffer_storage{"named_renderbuffer_storage", traits, *this}
  , renderbuffer_storage_multisample{
      "renderbuffer_storage_multisample",
      traits,
      *this}
  , named_renderbuffer_storage_multisample{
      "named_renderbuffer_storage_multisample",
      traits,
      *this}
  , get_renderbuffer_parameter_i{"get_renderbuffer_parameter_i", traits, *this}
  , get_named_renderbuffer_parameter_i{
      "get_named_renderbuffer_parameter_i",
      traits,
      *this}
  , bind_framebuffer{"bind_framebuffer", traits, *this}
  , draw_buffer{"draw_buffer", traits, *this}
  , named_framebuffer_draw_buffer{"named_framebuffer_draw_buffer", traits, *this}
  , read_buffer{"read_buffer", traits, *this}
  , named_framebuffer_read_buffer{"named_framebuffer_read_buffer", traits, *this}
  , framebuffer_parameter_i{"framebuffer_parameter_i", traits, *this}
  , named_framebuffer_parameter_i{"named_framebuffer_parameter_i", traits, *this}
  , get_framebuffer_parameter_i{"get_framebuffer_parameter_i", traits, *this}
  , get_named_framebuffer_parameter_i{
      "get_named_framebuffer_parameter_i",
      traits,
      *this}
  , get_framebuffer_attachment_parameter_i{
      "get_framebuffer_attachment_parameter_i",
      traits,
      *this}
  , get_named_framebuffer_attachment_parameter_i{
      "get_named_framebuffer_attachment_parameter_i",
      traits,
      *this}
  , framebuffer_renderbuffer{"framebuffer_renderbuffer", traits, *this}
  , named_framebuffer_renderbuffer{
      "named_framebuffer_renderbuffer",
      traits,
      *this}
  , framebuffer_texture{"framebuffer_texture", traits, *this}
  , named_framebuffer_texture{"named_framebuffer_texture", traits, *this}
  , framebuffer_texture1d{"framebuffer_texture1d", traits, *this}
  , framebuffer_texture2d{"framebuffer_texture2d", traits, *this}
  , framebuffer_texture3d{"framebuffer_texture3d", traits, *this}
  , framebuffer_texture_layer{"framebuffer_texture_layer", traits, *this}
  , named_framebuffer_texture_layer{
      "named_framebuffer_texture_layer",
      traits,
      *this}
  , check_framebuffer_status{"check_framebuffer_status", traits, *this}
  , check_named_framebuffer_status{
      "check_named_framebuffer_status",
      traits,
      *this}
  , blit_framebuffer{"blit_framebuffer", traits, *this}
  , blit_named_framebuffer{"blit_named_framebuffer", traits, *this}
  , bind_transform_feedback{"bind_transform_feedback", traits, *this}
  , begin_transform_feedback{"begin_transform_feedback", traits, *this}
  , pause_transform_feedback{"pause_transform_feedback", traits, *this}
  , resume_transform_feedback{"resume_transform_feedback", traits, *this}
  , end_transform_feedback{"end_transform_feedback", traits, *this}
  , transform_feedback_buffer_base{
      "transform_feedback_buffer_base",
      traits,
      *this}
  , transform_feedback_buffer_range{
      "transform_feedback_buffer_range",
      traits,
      *this}
  , get_transform_feedback_i{"get_transform_feedback_i", traits, *this}
  , get_transform_feedback_ii{"get_transform_feedback_ii", traits, *this}
  , get_transform_feedback_i64i{"get_transform_feedback_i64i", traits, *this}
  , get_query_i{"get_query_i", traits, *this}
  , get_query_indexed_i{"get_query_indexed_i", traits, *this}
  , get_query_object_i{"get_query_object_i", traits, *this}
  , get_query_object_ui{"get_query_object_ui", traits, *this}
  , get_query_object_i64{"get_query_object_i64", traits, *this}
  , get_query_object_ui64{"get_query_object_ui64", traits, *this}
  , get_query_buffer_object_i{"get_query_buffer_object_i", traits, *this}
  , get_query_buffer_object_ui{"get_query_buffer_object_ui", traits, *this}
  , get_query_buffer_object_i64{"get_query_buffer_object_i64", traits, *this}
  , get_query_buffer_object_ui64{"get_query_buffer_object_ui64", traits, *this}
  , begin_query{"begin_query", traits, *this}
  , begin_query_indexed{"begin_query_indexed", traits, *this}
  , end_query{"end_query", traits, *this}
  , end_query_indexed{"end_query_indexed", traits, *this}
  , query_counter{"query_counter", traits, *this}
  , begin_conditional_render{"begin_conditional_render", traits, *this}
  , end_conditional_render{"end_conditional_render", traits, *this}
  , bind_program_pipeline{"bind_program_pipeline", traits, *this}
  , validate_program_pipeline{"validate_program_pipeline", traits, *this}
  , use_program_stages{"use_program_stages", traits, *this}
  , get_program_stage_i{"get_program_stage_i", traits, *this}
  , get_program_pipeline_i{"get_program_pipeline_i", traits, *this}
  , get_program_pipeline_info_log{"get_program_pipeline_info_log", traits, *this}
  , active_shader_program{"active_shader_program", traits, *this}
  , path_color_gen_nv{"path_color_gen_nv", traits, *this}
  , path_glyph_range_nv{"path_glyph_range_nv", traits, *this}
  , get_path_spacing_nv{"get_path_spacing_nv", traits, *this}
  , stencil_fill_path_nv{"stencil_fill_path_nv", traits, *this}
  , stencil_stroke_path_nv{"stencil_stroke_path_nv", traits, *this}
  , stencil_fill_path_instanced_nv{
      "stencil_fill_path_instanced_nv",
      traits,
      *this}
  , stencil_stroke_path_instanced_nv{
      "stencil_stroke_path_instanced_nv",
      traits,
      *this}
  , cover_fill_path_nv{"cover_fill_path_nv", traits, *this}
  , cover_stroke_path_nv{"cover_stroke_path_nv", traits, *this}
  , cover_fill_path_instanced_nv{"cover_fill_path_instanced_nv", traits, *this}
  , cover_stroke_path_instanced_nv{
      "cover_stroke_path_instanced_nv",
      traits,
      *this}
  , primitive_restart_index{"primitive_restart_index", traits, *this}
  , provoking_vertex{"provoking_vertex", traits, *this}
  , point_size{"point_size", traits, *this}
  , line_width{"line_width", traits, *this}
  , point_parameter_i{"point_parameter_i", traits, *this}
  , point_parameter_f{"point_parameter_f", traits, *this}
  , patch_parameter_i{"patch_parameter_i", traits, *this}
  , patch_parameter_fv{"patch_parameter_fv", traits, *this}
  , front_face{"front_face", traits, *this}
  , cull_face{"cull_face", traits, *this}
  , polygon_mode{"polygon_mode", traits, *this}
  , polygon_offset{"polygon_offset", traits, *this}
  , polygon_offset_clamp{"polygon_offset_clamp", traits, *this}
  , blend_equation{"blend_equation", traits, *this}
  , blend_equation_separate{"blend_equation_separate", traits, *this}
  , blend_equationi{"blend_equationi", traits, *this}
  , blend_equation_separatei{"blend_equation_separatei", traits, *this}
  , blend_func{"blend_func", traits, *this}
  , blend_func_separate{"blend_func_separate", traits, *this}
  , blend_funci{"blend_funci", traits, *this}
  , blend_func_separatei{"blend_func_separatei", traits, *this}
  , sample_coverage{"sample_coverage", traits, *this}
  , sample_mask_i{"sample_mask_i", traits, *this}
  , min_sample_shading{"min_sample_shading", traits, *this}
  , get_multisample_f{"get_multisample_f", traits, *this}
  , draw_arrays{"draw_arrays", traits, *this}
  , draw_arrays_instanced_base_instance{
      "draw_arrays_instanced_base_instance",
      traits,
      *this}
  , draw_arrays_instanced{"draw_arrays_instanced", traits, *this}
  , draw_arrays_indirect{"draw_arrays_indirect", traits, *this}
  , multi_draw_arrays{"multi_draw_arrays", traits, *this}
  , multi_draw_arrays_indirect{"multi_draw_arrays_indirect", traits, *this}
  , multi_draw_arrays_indirect_count{
      "multi_draw_arrays_indirect_count",
      traits,
      *this}
  , draw_elements{"draw_elements", traits, *this}
  , draw_range_elements{"draw_range_elements", traits, *this}
  , draw_elements_instanced_base_instance{
      "draw_elements_instanced_base_instance",
      traits,
      *this}
  , draw_elements_instanced{"draw_elements_instanced", traits, *this}
  , draw_elements_indirect{"draw_elements_indirect", traits, *this}
  , draw_elements_base_vertex{"draw_elements_base_vertex", traits, *this}
  , draw_range_elements_base_vertex{
      "draw_range_elements_base_vertex",
      traits,
      *this}
  , draw_elements_instanced_base_vertex{
      "draw_elements_instanced_base_vertex",
      traits,
      *this}
  , draw_elements_instanced_base_vertex_base_instance{
      "draw_elements_instanced_base_vertex_base_instance",
      traits,
      *this}
  , dispatch_compute{"dispatch_compute", traits, *this}
  , dispatch_compute_indirect{"dispatch_compute_indirect", traits, *this}
  , read_pixels{"read_pixels", traits, *this}
  , get_integer{"get_integer", traits, *this}
  , get_integer64{"get_integer64", traits, *this}
  , get_float{"get_float", traits, *this}
  , get_double{"get_double", traits, *this}
  , get_string{"get_string", traits, *this}
  , named_string{"named_string", traits, *this}
  , delete_named_string{"delete_named_string", traits, *this}
  , is_named_string{"is_named_string", traits, *this}
  , begin{"begin", traits, *this}
  , end{"end", traits, *this}
  , vertex2i{"vertex2i", traits, *this}
  , vertex3i{"vertex3i", traits, *this}
  , vertex4i{"vertex4i", traits, *this}
  , vertex2f{"vertex2f", traits, *this}
  , vertex3f{"vertex3f", traits, *this}
  , vertex4f{"vertex4f", traits, *this}
  , color3i{"color3i", traits, *this}
  , color4i{"color4i", traits, *this}
  , color3f{"color3f", traits, *this}
  , color4f{"color4f", traits, *this}
  , secondary_color3i{"secondary_color3i", traits, *this}
  , secondary_color4i{"secondary_color4i", traits, *this}
  , secondary_color3f{"secondary_color3f", traits, *this}
  , secondary_color4f{"secondary_color4f", traits, *this}
  , tex_coord1i{"tex_coord1i", traits, *this}
  , tex_coord2i{"tex_coord2i", traits, *this}
  , tex_coord3i{"tex_coord3i", traits, *this}
  , tex_coord4i{"tex_coord4i", traits, *this}
  , tex_coord1f{"tex_coord1f", traits, *this}
  , tex_coord2f{"tex_coord2f", traits, *this}
  , tex_coord3f{"tex_coord3f", traits, *this}
  , tex_coord4f{"tex_coord4f", traits, *this}
  , multi_tex_coord1i{"multi_tex_coord1i", traits, *this}
  , multi_tex_coord2i{"multi_tex_coord2i", traits, *this}
  , multi_tex_coord3i{"multi_tex_coord3i", traits, *this}
  , multi_tex_coord4i{"multi_tex_coord4i", traits, *this}
  , multi_tex_coord1f{"multi_tex_coord1f", traits, *this}
  , multi_tex_coord2f{"multi_tex_coord2f", traits, *this}
  , multi_tex_coord3f{"multi_tex_coord3f", traits, *this}
  , multi_tex_coord4f{"multi_tex_coord4f", traits, *this}
  , matrix_mode{"matrix_mode", traits, *this}
  , push_matrix{"push_matrix", traits, *this}
  , pop_matrix{"pop_matrix", traits, *this}
  , load_identity{"load_identity", traits, *this}
  , translate_f{"translate_f", traits, *this}
  , translate_d{"translate_d", traits, *this}
  , rotate_f{"rotate_f", traits, *this}
  , rotate_d{"rotate_d", traits, *this}
  , scale_f{"scale_f", traits, *this}
  , scale_d{"scale_d", traits, *this}
  , frustum{"frustum", traits, *this}
  , ortho{"ortho", traits, *this}
  , load_matrix_f{"load_matrix_f", traits, *this}
  , load_matrix_d{"load_matrix_d", traits, *this}
  , mult_matrix_f{"mult_matrix_f", traits, *this}
  , mult_matrix_d{"mult_matrix_d", traits, *this}
  , load_transpose_matrix_f{"load_transpose_matrix_f", traits, *this}
  , load_transpose_matrix_d{"load_transpose_matrix_d", traits, *this}
  , mult_transpose_matrix_f{"mult_transpose_matrix_f", traits, *this}
  , mult_transpose_matrix_d{"mult_transpose_matrix_d", traits, *this}
  , debug_message_control{"debug_message_control", traits, *this}
  , debug_message_insert{"debug_message_insert", traits, *this}
  , debug_message_callback{"debug_message_callback", traits, *this}
  , push_debug_group{"push_debug_group", traits, *this}
  , pop_debug_group{"pop_debug_group", traits, *this}
  , object_label{"object_label", traits, *this}
  , flush{"flush", traits, *this}
  , finish{"finish", traits, *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
