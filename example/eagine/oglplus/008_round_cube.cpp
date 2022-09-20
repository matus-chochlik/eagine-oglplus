/// @example oglplus/008_round_cube.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.shapes;
import eagine.oglplus;
import <cmath>;
import <iostream>;
import <stdexcept>;

#include <GLFW/glfw3.h>

static const eagine::string_view vs_source{R"(
#version 140
in vec3 Position;
in vec3 Normal;
out vec3 vertColor;
uniform mat4 Camera;

void main() {
    gl_Position = Camera * vec4(Position, 1.0);
    vertColor = normalize(vec3(1.0) + Normal);
}
)"};

static const eagine::string_view fs_source{R"(
#version 140
in vec3 vertColor;
out vec3 fragColor;

void main() {
    fragColor = mix(vertColor, vec3(1), 0.5);
}
)"};

static void run_loop(
  eagine::main_ctx& ctx,
  GLFWwindow* window,
  int width,
  int height) {
    using namespace eagine;
    using namespace eagine::oglplus;

    const gl_api glapi;
    const auto& [gl, GL] = glapi;

    if(gl.clear) {
        gl_debug_logger gdl{ctx};

        gl.debug_message_callback(gdl);
        gl.debug_message_control(
          GL.dont_care, GL.dont_care, GL.dont_care, GL.true_);

        memory::buffer buf;

        // vertex shader
        owned_shader_name vs;
        gl.create_shader(GL.vertex_shader) >> vs;
        const auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.object_label(vs, "vertex shader");
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // fragment shader
        owned_shader_name fs;
        gl.create_shader(GL.fragment_shader) >> fs;
        const auto cleanup_fs = gl.delete_shader.raii(fs);
        gl.object_label(fs, "fragment shader");
        gl.shader_source(fs, glsl_string_ref(fs_source));
        gl.compile_shader(fs);

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        const auto cleanup_prog = gl.delete_program.raii(prog);
        gl.object_label(prog, "draw program");
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);

        // geometry
        shape_generator shape(
          glapi,
          shapes::unit_round_cube(
            shapes::vertex_attrib_kind::position |
            shapes::vertex_attrib_kind::normal));

        std::vector<shape_draw_operation> _ops;
        _ops.resize(std_size(shape.operation_count()));
        shape.instructions(glapi, cover(_ops));

        // vao
        owned_vertex_array_name vao;
        gl.gen_vertex_arrays() >> vao;
        const auto cleanup_vao = gl.delete_vertex_arrays.raii(vao);
        gl.bind_vertex_array(vao);

        // positions
        vertex_attrib_location position_loc{0};
        owned_buffer_name positions;
        gl.gen_buffers() >> positions;
        const auto cleanup_positions = gl.delete_buffers.raii(positions);
        shape.attrib_setup(
          glapi,
          vao,
          positions,
          position_loc,
          shapes::vertex_attrib_kind::position,
          "positions",
          buf);
        gl.bind_attrib_location(prog, position_loc, "Position");

        // normals
        vertex_attrib_location normal_loc{1};
        owned_buffer_name normals;
        gl.gen_buffers() >> normals;
        const auto cleanup_normals = gl.delete_buffers.raii(normals);
        shape.attrib_setup(
          glapi,
          vao,
          normals,
          normal_loc,
          shapes::vertex_attrib_kind::normal,
          "normals",
          buf);
        gl.bind_attrib_location(prog, normal_loc, "Normal");

        // indices
        owned_buffer_name indices;
        gl.gen_buffers() >> indices;
        const auto cleanup_indices = gl.delete_buffers.raii(indices);
        shape.index_setup(glapi, indices, "indices", buf);

        // uniform
        uniform_location camera_loc;
        gl.get_uniform_location(prog, "Camera") >> camera_loc;

        orbiting_camera camera;
        camera.set_near(0.1F).set_far(50.F).set_fov(right_angle_());

        gl.clear_color(0.35F, 0.35F, 0.35F, 1.0F);
        gl.clear_depth(1);
        gl.enable(GL.depth_test);
        gl.polygon_mode(GL.front_and_back, GL.line);

        float t = 0.F;

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

            gl.clear(GL.color_buffer_bit | GL.depth_buffer_bit);

            t += 0.02F;
            const auto aspect = float(width) / float(height);
            glapi.set_uniform(
              prog,
              camera_loc,
              camera.set_azimuth(radians_(t))
                .set_elevation(radians_(std::sin(t)))
                .set_orbit_factor(math::sine_wave01(t * 0.1F))
                .matrix(aspect));
            draw_using_instructions(glapi, view(_ops));

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
        auto ensure_glfw_cleanup = eagine::finally(glfwTerminate);

        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
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
            eagine::oglplus::api_initializer gl_api_init;
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

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

