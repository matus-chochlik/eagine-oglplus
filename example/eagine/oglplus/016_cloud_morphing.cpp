/// @example oglplus/016_cloud_morphing.cpp
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
in vec3 Position1;
in vec3 Position2;
in vec3 Color1;
in vec3 Color2;
out vec3 vertColor;
uniform mat4 Camera;
uniform float Factor;

void main() {
    gl_Position = Camera * vec4(mix(Position1, Position2, Factor), 1.0);
    vertColor = mix(
		vec3(1.0, 0.1, 0.0) * Color1.r * 1.4,
		vec3(0.0, 0.1, 1.0) * Color2.g * 1.4,
		Factor);
}
)"};

static const eagine::string_view fs_source{R"(
#version 140
in vec3 vertColor;
out vec3 fragColor;

void main() {
    fragColor = vertColor;
}
)"};

static void run_loop(
  eagine::main_ctx& ctx,
  GLFWwindow* window,
  int width,
  int height) {
    using namespace eagine;
    using namespace eagine::oglplus;

    const auto progress_callback = [window] {
        glfwPollEvents();
        return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
    };

    set_progress_update_callback(
      ctx, {construct_from, progress_callback}, std::chrono::milliseconds{100});

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
        const span_size_t point_count = 512 * 1024;

        shape_generator shape1(
          glapi,
          shapes::surface_points(
            shapes::unit_torus(
              shapes::vertex_attrib_kind::position |
              shapes::vertex_attrib_kind::normal),
            point_count,
            ctx));

        shape_generator shape2(
          glapi,
          shapes::surface_points(
            shapes::unit_twisted_torus(
              shapes::vertex_attrib_kind::position |
                shapes::vertex_attrib_kind::normal,
              6,
              48,
              4,
              0.5F),
            point_count,
            ctx));

        std::vector<shape_draw_operation> _ops;
        _ops.resize(std_size(shape1.operation_count()));
        shape1.instructions(glapi, cover(_ops));

        // vao
        owned_vertex_array_name vao;
        gl.gen_vertex_arrays() >> vao;
        const auto cleanup_vao = gl.delete_vertex_arrays.raii(vao);
        gl.bind_vertex_array(vao);

        // positions
        vertex_attrib_location position1_loc{0};
        owned_buffer_name positions1;
        gl.gen_buffers() >> positions1;
        const auto cleanup_positions1 = gl.delete_buffers.raii(positions1);
        shape1.attrib_setup(
          glapi,
          vao,
          positions1,
          position1_loc,
          shapes::vertex_attrib_kind::position,
          "positions",
          buf);
        gl.bind_attrib_location(prog, position1_loc, "Position1");

        vertex_attrib_location position2_loc{1};
        owned_buffer_name positions2;
        gl.gen_buffers() >> positions2;
        const auto cleanup_positions2 = gl.delete_buffers.raii(positions2);
        shape2.attrib_setup(
          glapi,
          vao,
          positions2,
          position2_loc,
          shapes::vertex_attrib_kind::position,
          "positions",
          buf);
        gl.bind_attrib_location(prog, position2_loc, "Position2");

        // colors
        vertex_attrib_location color1_loc{2};
        owned_buffer_name colors1;
        gl.gen_buffers() >> colors1;
        const auto cleanup_colors1 = gl.delete_buffers.raii(colors1);
        shape1.attrib_setup(
          glapi,
          vao,
          colors1,
          color1_loc,
          shapes::vertex_attrib_kind::normal,
          "colors",
          buf);
        gl.bind_attrib_location(prog, color1_loc, "Color1");

        vertex_attrib_location color2_loc{3};
        owned_buffer_name colors2;
        gl.gen_buffers() >> colors2;
        const auto cleanup_colors2 = gl.delete_buffers.raii(colors2);
        shape2.attrib_setup(
          glapi,
          vao,
          colors2,
          color2_loc,
          shapes::vertex_attrib_kind::normal,
          "colors",
          buf);
        gl.bind_attrib_location(prog, color2_loc, "Color2");

        // uniform
        uniform_location factor_loc;
        gl.get_uniform_location(prog, "Factor") >> factor_loc;

        uniform_location camera_loc;
        gl.get_uniform_location(prog, "Camera") >> camera_loc;

        orbiting_camera camera;
        camera.set_near(0.1F)
          .set_far(50.F)
          .set_fov(right_angle_())
          .set_orbit_min(0.5F)
          .set_orbit_max(0.8F);

        gl.clear_color(0.35F, 0.35F, 0.35F, 1.0F);
        gl.clear_depth(1);
        gl.enable(GL.depth_test);
        gl.point_size(3.F);

        float tim = 0.F;
        animated_value<float, float> fac;
        const std::array<float, 4> fac_next{{0.F, 0.F, 1.F, 1.F}};
        std::size_t fac_idx = 0U;

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

            const auto delta_t = 0.02F;
            tim += delta_t;
            fac.update(delta_t);
            if(fac.is_done()) {
                fac_idx = (fac_idx + 1) % fac_next.size();
                fac.set(fac_next[fac_idx], 2.F);
            }
            const auto aspect = float(width) / float(height);
            glapi.set_uniform(prog, factor_loc, fac.get());
            glapi.set_uniform(
              prog,
              camera_loc,
              camera.set_azimuth(radians_(tim * 0.7F))
                .set_elevation(right_angles_(std::sin(tim * 0.3F)))
                .set_orbit_factor(math::sine_wave01(tim * 0.1F))
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

