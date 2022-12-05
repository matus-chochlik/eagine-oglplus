/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include "gl_def.hpp"

module eagine.oglplus;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.container;

namespace eagine {
//------------------------------------------------------------------------------
auto within_limits<oglplus::buffer_target, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_ARRAY_BUFFER:
        case GL_ATOMIC_COUNTER_BUFFER:
        case GL_COPY_READ_BUFFER:
        case GL_COPY_WRITE_BUFFER:
        case GL_DISPATCH_INDIRECT_BUFFER:
        case GL_DRAW_INDIRECT_BUFFER:
        case GL_ELEMENT_ARRAY_BUFFER:
        case GL_PIXEL_PACK_BUFFER:
        case GL_PIXEL_UNPACK_BUFFER:
        case GL_QUERY_BUFFER:
        case GL_SHADER_STORAGE_BUFFER:
        case GL_TEXTURE_BUFFER:
        case GL_TRANSFORM_FEEDBACK_BUFFER:
        case GL_UNIFORM_BUFFER:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::buffer_usage, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_STREAM_DRAW:
        case GL_STREAM_READ:
        case GL_STREAM_COPY:
        case GL_STATIC_DRAW:
        case GL_STATIC_READ:
        case GL_STATIC_COPY:
        case GL_DYNAMIC_DRAW:
        case GL_DYNAMIC_READ:
        case GL_DYNAMIC_COPY:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::capability, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_BLEND:
        case GL_CLIP_DISTANCE0:
        case GL_COLOR_LOGIC_OP:
        case GL_CULL_FACE:
        case GL_DEBUG_OUTPUT:
        case GL_DEBUG_OUTPUT_SYNCHRONOUS:
        case GL_DEPTH_CLAMP:
        case GL_DEPTH_TEST:
        case GL_DITHER:
        case GL_FRAMEBUFFER_SRGB:
        case GL_LINE_SMOOTH:
        case GL_MULTISAMPLE:
        case GL_POLYGON_OFFSET_FILL:
        case GL_POLYGON_OFFSET_LINE:
        case GL_POLYGON_OFFSET_POINT:
        case GL_POLYGON_SMOOTH:
        case GL_PRIMITIVE_RESTART:
        case GL_PRIMITIVE_RESTART_FIXED_INDEX:
        case GL_PROGRAM_POINT_SIZE:
        case GL_RASTERIZER_DISCARD:
        case GL_SAMPLE_ALPHA_TO_COVERAGE:
        case GL_SAMPLE_ALPHA_TO_ONE:
        case GL_SAMPLE_COVERAGE:
        case GL_SAMPLE_SHADING:
        case GL_SAMPLE_MASK:
        case GL_SCISSOR_TEST:
        case GL_STENCIL_TEST:
        case GL_TEXTURE_CUBE_MAP_SEAMLESS:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::object_type, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_BUFFER:
        case GL_FRAMEBUFFER:
        case GL_PROGRAM_PIPELINE:
        case GL_PROGRAM:
        case GL_QUERY:
        case GL_RENDERBUFFER:
        case GL_SAMPLER:
        case GL_SHADER:
        case GL_TEXTURE:
        case GL_TRANSFORM_FEEDBACK:
        case GL_VERTEX_ARRAY:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::pixel_data_type, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_FLOAT:
        case GL_UNSIGNED_BYTE:
        case GL_UNSIGNED_SHORT:
        case GL_UNSIGNED_INT:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::pixel_format, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_RED:
        case GL_RED_INTEGER:
        case GL_RGB:
        case GL_RGBA:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::pixel_internal_format, oglplus::gl_types::enum_type>::
  check(oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_R8:
        case GL_R8UI:
        case GL_RGB8:
        case GL_RGBA8:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::shader_type, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_COMPUTE_SHADER:
        case GL_VERTEX_SHADER:
        case GL_TESS_CONTROL_SHADER:
        case GL_TESS_EVALUATION_SHADER:
        case GL_GEOMETRY_SHADER:
        case GL_FRAGMENT_SHADER:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::texture_target, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_TEXTURE_1D:
        case GL_TEXTURE_1D_ARRAY:
        case GL_TEXTURE_2D:
        case GL_TEXTURE_2D_ARRAY:
        case GL_TEXTURE_2D_MULTISAMPLE:
        case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
        case GL_TEXTURE_3D:
        case GL_TEXTURE_CUBE_MAP:
        case GL_TEXTURE_CUBE_MAP_ARRAY:
        case GL_TEXTURE_RECTANGLE:
        case GL_TEXTURE_BUFFER:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::texture_min_filter, oglplus::gl_types::enum_type>::
  check(oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_NEAREST:
        case GL_NEAREST_MIPMAP_NEAREST:
        case GL_NEAREST_MIPMAP_LINEAR:
        case GL_LINEAR:
        case GL_LINEAR_MIPMAP_NEAREST:
        case GL_LINEAR_MIPMAP_LINEAR:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::texture_mag_filter, oglplus::gl_types::enum_type>::
  check(oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_NEAREST:
        case GL_LINEAR:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::texture_swizzle_mode, oglplus::gl_types::enum_type>::
  check(oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_RED:
        case GL_GREEN:
        case GL_BLUE:
        case GL_ALPHA:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::texture_wrap_mode, oglplus::gl_types::enum_type>::
  check(oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_REPEAT:
        case GL_CLAMP_TO_EDGE:
        case GL_CLAMP_TO_BORDER:
        case GL_MIRRORED_REPEAT:
        case GL_MIRROR_CLAMP_TO_EDGE:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<oglplus::true_false, oglplus::gl_types::enum_type>::check(
  oglplus::gl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_GL
        case GL_TRUE:
        case GL_FALSE:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
namespace oglplus {
//------------------------------------------------------------------------------
auto map_gl_enump_by_name() noexcept {
    return basic_lc_identifier_trie<gl_types::enum_type>()
#if EAGINE_HAS_GL
      .add("add", GL_ADD)
      .add("alpha", GL_ALPHA)
      .add("array_buffer", GL_ARRAY_BUFFER)
      .add("atomic_counter_buffer", GL_ATOMIC_COUNTER_BUFFER)
      .add("blend", GL_BLEND)
      .add("blue", GL_BLUE)
      .add("buffer", GL_BUFFER)
      .add("clamp_to_border", GL_CLAMP_TO_BORDER)
      .add("clamp_to_edge", GL_CLAMP_TO_EDGE)
      .add("clip_distance", GL_CLIP_DISTANCE0)
      .add("clip_distance_0", GL_CLIP_DISTANCE0)
      .add("color_logic_op", GL_COLOR_LOGIC_OP)
      .add("compute_shader", GL_COMPUTE_SHADER)
      .add("copy_read_buffer", GL_COPY_READ_BUFFER)
      .add("copy_write_buffer", GL_COPY_WRITE_BUFFER)
      .add("cull_face", GL_CULL_FACE)
      .add("debug_output", GL_DEBUG_OUTPUT)
      .add("debug_output_synchronous", GL_DEBUG_OUTPUT_SYNCHRONOUS)
      .add("depth_clamp", GL_DEPTH_CLAMP)
      .add("depth_test", GL_DEPTH_TEST)
      .add("dispatch_indirect_buffer", GL_DISPATCH_INDIRECT_BUFFER)
      .add("dither", GL_DITHER)
      .add("draw_indirect_buffer", GL_DRAW_INDIRECT_BUFFER)
      .add("dynamic_copy", GL_DYNAMIC_COPY)
      .add("dynamic_draw", GL_DYNAMIC_DRAW)
      .add("dynamic_read", GL_DYNAMIC_READ)
      .add("element_array_buffer", GL_ELEMENT_ARRAY_BUFFER)
      .add("false", GL_FALSE)
      .add("float", GL_FLOAT)
      .add("framebuffer", GL_FRAMEBUFFER)
      .add("framebuffer_srgb", GL_FRAMEBUFFER_SRGB)
      .add("fragment_shader", GL_FRAGMENT_SHADER)
      .add("geometry_shader", GL_GEOMETRY_SHADER)
      .add("green", GL_GREEN)
      .add("linear", GL_LINEAR)
      .add("linear_mipmap_linear", GL_LINEAR_MIPMAP_LINEAR)
      .add("linear_mipmap_nearest", GL_LINEAR_MIPMAP_NEAREST)
      .add("line_smooth", GL_LINE_SMOOTH)
      .add("mirror_clamp_to_edge", GL_MIRROR_CLAMP_TO_EDGE)
      .add("mirrored_repeat", GL_MIRRORED_REPEAT)
      .add("multisample", GL_MULTISAMPLE)
      .add("nearest", GL_NEAREST)
      .add("nearest_mipmap_linear", GL_NEAREST_MIPMAP_LINEAR)
      .add("nearest_mipmap_nearest", GL_NEAREST_MIPMAP_NEAREST)
      .add("pixel_pack_buffer", GL_PIXEL_PACK_BUFFER)
      .add("pixel_unpack_buffer", GL_PIXEL_UNPACK_BUFFER)
      .add("polygon_offset_fill", GL_POLYGON_OFFSET_FILL)
      .add("polygon_offset_line", GL_POLYGON_OFFSET_LINE)
      .add("polygon_offset_point", GL_POLYGON_OFFSET_POINT)
      .add("polygon_smooth", GL_POLYGON_SMOOTH)
      .add("primitive_restart", GL_PRIMITIVE_RESTART)
      .add("primitive_restart_fixed_index", GL_PRIMITIVE_RESTART_FIXED_INDEX)
      .add("program", GL_PROGRAM)
      .add("program_pipeline", GL_PROGRAM_PIPELINE)
      .add("program_point_size", GL_PROGRAM_POINT_SIZE)
      .add("query", GL_QUERY)
      .add("query_buffer", GL_QUERY_BUFFER)
      .add("rasterizer_discard", GL_RASTERIZER_DISCARD)
      .add("repeat", GL_REPEAT)
      .add("r8", GL_R8)
      .add("r8ui", GL_R8UI)
      .add("red", GL_RED)
      .add("rgb", GL_RGB)
      .add("rgb8", GL_RGB8)
      .add("rgba", GL_RGBA)
      .add("rgba8", GL_RGBA8)
      .add("red_integer", GL_RED_INTEGER)
      .add("renderbuffer", GL_RENDERBUFFER)
      .add("sampler", GL_SAMPLER)
      .add("sample_coverage", GL_SAMPLE_COVERAGE)
      .add("sample_alpha_to_coverage", GL_SAMPLE_ALPHA_TO_COVERAGE)
      .add("sample_alpha_to_one", GL_SAMPLE_ALPHA_TO_ONE)
      .add("sample_mask", GL_SAMPLE_MASK)
      .add("sample_shading", GL_SAMPLE_SHADING)
      .add("scissor_test", GL_SCISSOR_TEST)
      .add("static_copy", GL_STATIC_COPY)
      .add("static_draw", GL_STATIC_DRAW)
      .add("static_read", GL_STATIC_READ)
      .add("stencil_test", GL_STENCIL_TEST)
      .add("stream_copy", GL_STREAM_COPY)
      .add("stream_draw", GL_STREAM_DRAW)
      .add("stream_read", GL_STREAM_READ)
      .add("shader", GL_SHADER)
      .add("shader_storage_buffer", GL_SHADER_STORAGE_BUFFER)
      .add("tess_control_shader", GL_TESS_CONTROL_SHADER)
      .add("tess_evaluation_shader", GL_TESS_EVALUATION_SHADER)
      .add("texture", GL_TEXTURE)
      .add("texture_1d", GL_TEXTURE_1D)
      .add("texture_1d_array", GL_TEXTURE_1D_ARRAY)
      .add("texture_2d", GL_TEXTURE_2D)
      .add("texture_2d_array", GL_TEXTURE_2D_ARRAY)
      .add("texture_2d_multisample", GL_TEXTURE_2D_MULTISAMPLE)
      .add("texture_2d_multisample_array", GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
      .add("texture_3d", GL_TEXTURE_3D)
      .add("texture_buffer", GL_TEXTURE_BUFFER)
      .add("texture_cube_map", GL_TEXTURE_CUBE_MAP)
      .add("texture_cube_map_array", GL_TEXTURE_CUBE_MAP_ARRAY)
      .add("texture_cube_negative_x", GL_TEXTURE_CUBE_MAP_NEGATIVE_X)
      .add("texture_cube_positive_x", GL_TEXTURE_CUBE_MAP_POSITIVE_X)
      .add("texture_cube_negative_y", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)
      .add("texture_cube_positive_y", GL_TEXTURE_CUBE_MAP_POSITIVE_Y)
      .add("texture_cube_negative_z", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
      .add("texture_cube_positive_z", GL_TEXTURE_CUBE_MAP_POSITIVE_Z)
      .add("texture_rectangle", GL_TEXTURE_RECTANGLE)
      .add("transform_feedback", GL_TRANSFORM_FEEDBACK)
      .add("transform_feedback_buffer", GL_TRANSFORM_FEEDBACK_BUFFER)
      .add("true", GL_TRUE)
      .add("uniform_buffer", GL_UNIFORM_BUFFER)
      .add("unsigned_byte", GL_UNSIGNED_BYTE)
      .add("unsigned_int", GL_UNSIGNED_INT)
      .add("unsigned_short", GL_UNSIGNED_SHORT)
      .add("vertex_array", GL_VERTEX_ARRAY)
      .add("vertex_shader", GL_VERTEX_SHADER)
      .add("zero", GL_ZERO)
#endif
      ;
}
//------------------------------------------------------------------------------
auto gl_enum_by_name(const string_view name) noexcept
  -> std::optional<gl_types::enum_type> {
    if(!name.empty()) [[likely]] {
        static const auto enums{map_gl_enump_by_name()};
        if(auto found{enums.find(name)}) [[likely]] {
            return {extract(found)};
        }
    }
    return {};
}
//------------------------------------------------------------------------------
} // namespace oglplus
} // namespace eagine
