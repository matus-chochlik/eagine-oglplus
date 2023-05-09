/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/testing/unit_begin.hpp>
import std;
import eagine.core;
import eagine.oglplus;
//------------------------------------------------------------------------------
void constants_enum_by_name(auto& s) {
    eagitest::case_ test{s, 1, "GL enum by name"};
    std::set<eagine::oglplus::gl_types::enum_type> distinct;

    const auto check{[&](eagine::string_view name) {
        if(auto value{eagine::oglplus::gl_enum_by_name(name)}) {
            distinct.insert(extract(value));
        } else {
            test.fail(name);
        }
    }};
    check("add");
    check("alpha");
    check("array_buffer");
    check("atomic_counter_buffer");
    check("blend");
    check("blue");
    check("buffer");
    check("clamp_to_border");
    check("clamp_to_edge");
    check("clip_distance");
    check("clip_distance_0");
    check("color_logic_op");
    check("compute_shader");
    check("copy_read_buffer");
    check("copy_write_buffer");
    check("cull_face");
    check("debug_output");
    check("debug_output_synchronous");
    check("depth_clamp");
    check("depth_test");
    check("dispatch_indirect_buffer");
    check("dither");
    check("draw_indirect_buffer");
    check("dynamic_copy");
    check("dynamic_draw");
    check("dynamic_read");
    check("element_array_buffer");
    check("false");
    check("float");
    check("framebuffer");
    check("framebuffer_srgb");
    check("fragment_shader");
    check("geometry_shader");
    check("green");
    check("linear");
    check("linear_mipmap_linear");
    check("linear_mipmap_nearest");
    check("line_smooth");
    check("mirror_clamp_to_edge");
    check("mirrored_repeat");
    check("multisample");
    check("nearest");
    check("nearest_mipmap_linear");
    check("nearest_mipmap_nearest");
    check("pixel_pack_buffer");
    check("pixel_unpack_buffer");
    check("polygon_offset_fill");
    check("polygon_offset_line");
    check("polygon_offset_point");
    check("polygon_smooth");
    check("primitive_restart");
    check("primitive_restart_fixed_index");
    check("program");
    check("program_pipeline");
    check("program_point_size");
    check("query");
    check("query_buffer");
    check("rasterizer_discard");
    check("repeat");
    check("r8");
    check("r8ui");
    check("red");
    check("rgb");
    check("rgb8");
    check("rgba");
    check("rgba8");
    check("red_integer");
    check("renderbuffer");
    check("sampler");
    check("sample_coverage");
    check("sample_alpha_to_coverage");
    check("sample_alpha_to_one");
    check("sample_mask");
    check("sample_shading");
    check("scissor_test");
    check("static_copy");
    check("static_draw");
    check("static_read");
    check("stencil_test");
    check("stream_copy");
    check("stream_draw");
    check("stream_read");
    check("shader");
    check("shader_storage_buffer");
    check("tess_control_shader");
    check("tess_evaluation_shader");
    check("texture");
    check("texture_1d");
    check("texture_1d_array");
    check("texture_2d");
    check("texture_2d_array");
    check("texture_2d_multisample");
    check("texture_2d_multisample_array");
    check("texture_3d");
    check("texture_buffer");
    check("texture_cube_map");
    check("texture_cube_map_array");
    check("texture_cube_negative_x");
    check("texture_cube_positive_x");
    check("texture_cube_negative_y");
    check("texture_cube_positive_y");
    check("texture_cube_negative_z");
    check("texture_cube_positive_z");
    check("texture_rectangle");
    check("transform_feedback");
    check("transform_feedback_buffer");
    check("true");
    check("uniform_buffer");
    check("unsigned_byte");
    check("unsigned_int");
    check("unsigned_short");
    check("vertex_array");
    check("vertex_shader");
    check("zero");

    test.check_equal(distinct.size(), 112U, "constant count");
}
//------------------------------------------------------------------------------
auto main(int argc, const char** argv) -> int {
    eagitest::suite test{argc, argv, "constants", 1};
    test.once(constants_enum_by_name);
    return test.exit_code();
}
//------------------------------------------------------------------------------
#include <eagine/testing/unit_end.hpp>
