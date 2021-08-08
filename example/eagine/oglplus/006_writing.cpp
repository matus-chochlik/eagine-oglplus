/// @example oglplus/006_writing.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/gl_api.hpp>

#include <eagine/main.hpp>
#include <eagine/main_ctx_object.hpp>
#include <eagine/math/curve.hpp>
#include <eagine/math/functions.hpp>
#include <eagine/memory/flatten.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/vector.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

static const eagine::string_view vs_source{R"(
#version 330

in vec2 Position;

void main() {
    gl_Position = vec4(Position, 0.0, 1.0);
}
)"};

static const eagine::string_view gs_source{R"(
#version 330

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

void main() {
	vec4 offs = vec4(0.02, 0.01, 0.0, 0.0);
   	gl_Position = gl_in[0].gl_Position - offs;
   	EmitVertex();
   	gl_Position = gl_in[0].gl_Position + offs;
   	EmitVertex();
   	gl_Position = gl_in[1].gl_Position - offs;
   	EmitVertex();
   	gl_Position = gl_in[1].gl_Position + offs;
   	EmitVertex();
   	EndPrimitive();
}
)"};

static const eagine::string_view fs_source{R"(
#version 330

out vec4 fragColor;

void main() {
    fragColor = vec4(0.0, 0.0, 0.0, 1.0);
}
)"};

static void run_loop(
  eagine::main_ctx& ctx,
  GLFWwindow* window,
  int width,
  int height) {
    using namespace eagine;
    using namespace eagine::oglplus;

    gl_api glapi;
    const auto& [gl, GL] = glapi;

    if(gl.clear) {
        gl_debug_logger gdl{ctx};

        gl.debug_message_callback(gdl);
        gl.debug_message_control(
          GL.dont_care, GL.dont_care, GL.dont_care, GL.true_);

        // vertex shader
        owned_shader_name vs;
        const auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.create_shader(GL.vertex_shader) >> vs;
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // geometry shader
        owned_shader_name gs;
        const auto cleanup_gs = gl.delete_shader.raii(gs);
        gl.create_shader(GL.geometry_shader) >> gs;
        gl.shader_source(gs, glsl_string_ref(gs_source));
        gl.compile_shader(gs);

        // fragment shader
        owned_shader_name fs;
        const auto cleanup_fs = gl.delete_shader.raii(fs);
        gl.create_shader(GL.fragment_shader) >> fs;
        gl.shader_source(fs, glsl_string_ref(fs_source));
        gl.compile_shader(fs);

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        auto cleanup_prog = gl.delete_program.raii(prog);
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, gs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);

        // geometry
        const std::array<oglplus::vec2, 34> control_points{
          {{-0.33F, +0.50F}, {-0.45F, +0.70F}, {-0.66F, +0.70F},
           {-0.66F, +0.30F}, {-0.66F, -0.20F}, {-0.35F, -0.15F},
           {-0.30F, +0.05F}, {-0.20F, +0.50F}, {-0.30F, +0.50F},
           {-0.33F, +0.50F}, {-0.50F, +0.45F}, {-0.10F, +0.40F},
           {+0.10F, +0.55F}, {-0.20F, +0.40F}, {-0.30F, -0.10F},
           {+0.00F, -0.10F}, {+0.10F, -0.10F}, {+0.20F, -0.10F},
           {+0.10F, +0.55F}, {+0.20F, +0.00F}, {+0.30F, -0.70F},
           {+0.00F, -0.75F}, {-0.40F, -0.75F}, {+0.00F, +0.00F},
           {+0.40F, +0.10F}, {+0.60F, +0.10F}, {+0.70F, +0.90F},
           {+0.55F, +0.90F}, {+0.35F, +0.90F}, {+0.10F, -0.10F},
           {+0.55F, +0.00F}, {+0.90F, +0.10F}, {+0.70F, +0.10F},
           {+0.90F, +0.20F}}};

        math::bezier_curves<oglplus::vec2, float, 3> curve(
          view(control_points));
        std::vector<oglplus::vec2> curve_points;
        curve.approximate(curve_points, 20);
        std::vector<float> position_data;
        memory::flatten(view(curve_points), position_data);
        const auto point_count =
          limit_cast<gl_types::sizei_type>(curve_points.size());

        // vao
        owned_vertex_array_name vao;
        const auto cleanup_vao = gl.delete_vertex_arrays.raii(vao);
        gl.gen_vertex_arrays() >> vao;
        gl.bind_vertex_array(vao);

        // positions
        owned_buffer_name positions;
        const auto cleanup_positions = gl.delete_buffers.raii(positions);
        gl.gen_buffers() >> positions;
        gl.bind_buffer(GL.array_buffer, positions);
        gl.buffer_data(GL.array_buffer, view(position_data), GL.static_draw);

        vertex_attrib_location position_loc;
        gl.get_attrib_location(prog, "Position") >> position_loc;
        gl.vertex_attrib_pointer(position_loc, 2, GL.float_, GL.false_);
        gl.enable_vertex_attrib_array(position_loc);

        gl.clear_color(0.35F, 0.35F, 0.35F, 1.0F);

        while(true) {
            glfwPollEvents();

            if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, 1);
                break;
            }

            if(glfwWindowShouldClose(window)) {
                break;
            }

            int new_width, new_height;
            glfwGetWindowSize(window, &new_width, &new_height);
            if((width != new_width) || (height != new_height)) {
                width = new_width;
                height = new_height;
            }

            gl.viewport(width, height);
            gl.clear(GL.color_buffer_bit);
            gl.draw_arrays(GL.line_strip, 0, point_count);

            glfwSwapBuffers(window);
        }
    } else {
        std::cout << "missing required API" << std::endl;
    }
}

static void init_and_run(eagine::main_ctx& ctx) {
    if(!glfwInit()) {
        throw std::runtime_error("GLFW initialization error");
    } else {
        const auto ensure_glfw_cleanup = eagine::finally(glfwTerminate);

        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_DEPTH_BITS, 0);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);

        glfwWindowHint(GLFW_SAMPLES, GLFW_DONT_CARE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        int width = 800, height = 600;

        GLFWwindow* window =
          glfwCreateWindow(width, height, "OGLplus example", nullptr, nullptr);

        if(!window) {
            throw std::runtime_error("Error creating GLFW window");
        } else {
            glfwMakeContextCurrent(window);
            eagine::oglplus::api_initializer gl_api;
            glGetError();
            run_loop(ctx, window, width, height);
        }
    }
}

namespace eagine {

auto main(main_ctx& ctx) -> int {
    try {
        init_and_run(ctx);
        return 0;
    } catch(const std::runtime_error& sre) {
        std::cerr << "Runtime error: " << sre.what() << std::endl;
    } catch(const std::exception& se) {
        std::cerr << "Unknown error: " << se.what() << std::endl;
    }
    return 1;
}

} // namespace eagine
