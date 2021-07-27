/// @example oglplus/014_subroutines.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/gl_api.hpp>

#include <eagine/main.hpp>
#include <eagine/math/functions.hpp>
#include <eagine/oglplus/camera.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/generator.hpp>
#include <eagine/shapes/round_cube.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

static const eagine::string_view vs_source{R"(
#version 400
in vec3 Position;
in vec2 Coord;
out vec2 vertCoord;
uniform vec3 center;
uniform mat4 camera;

void main() {
    gl_Position = camera * vec4(center + Position, 1.0);
    vertCoord = Coord;
}
)"};

static const eagine::string_view fs_source{R"(
#version 400
in vec2 vertCoord;
out vec3 fragColor;

subroutine float patternType(vec2 c);

subroutine(patternType) float horzStrip(vec2 c) {
	return float(int(c.x * 8.0) % 2);
}

subroutine(patternType) float vertStrip(vec2 c) {
	return float(int(c.y * 8.0) % 2);
}

subroutine(patternType) float diagStrip(vec2 c) {
	c = c * 8.0;
	return float(int(c.x + c.y) % 2);
}

subroutine(patternType) float checker(vec2 c) {
	c = c * 8.0;
	return float((int(c.x) % 2 + int(c.y) % 2) % 2);
}

subroutine(patternType) float spiral(vec2 c) {
	vec2 center = (c - vec2(0.5)) * 16.0;
	float l = length(center);
	float t = atan(center.y, center.x) / (2.0 * asin(1.0));
	return float(int(l + t) % 2);
}

subroutine(patternType) float dots(vec2 c) {
	c = c * 4.0;
	vec2 center = floor(c) + vec2(0.5);
	float l = length(c - center);
	return l > 0.25 ? 1.0 : 0.0;
}

subroutine uniform patternType pattern;

void main() {
    fragColor = vec3(pattern(vertCoord));
}
)"};

static void
run_loop(eagine::main_ctx& ctx, GLFWwindow* window, int width, int height) {
    using namespace eagine;
    using namespace eagine::oglplus;

    gl_api glapi;
    auto& [gl, GL] = glapi;

    if(gl.clear) {
        gl_debug_logger gdl{ctx};

        gl.debug_message_callback(gdl);
        gl.debug_message_control(
          GL.dont_care, GL.dont_care, GL.dont_care, GL.true_);

        memory::buffer buf;

        // vertex shader
        owned_shader_name vs;
        gl.create_shader(GL.vertex_shader) >> vs;
        auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // fragment shader
        owned_shader_name fs;
        gl.create_shader(GL.fragment_shader) >> fs;
        auto cleanup_fs = gl.delete_shader.raii(fs);
        gl.shader_source(fs, glsl_string_ref(fs_source));
        gl.compile_shader(fs);

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        auto cleanup_prog = gl.delete_program.raii(prog);
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
        auto cleanup_vao = gl.delete_vertex_arrays.raii(vao);
        gl.bind_vertex_array(vao);

        // positions
        vertex_attrib_location position_loc{0};
        owned_buffer_name positions;
        gl.gen_buffers() >> positions;
        auto cleanup_positions = gl.delete_buffers.raii(positions);
        shape.attrib_setup(
          glapi,
          vao,
          positions,
          position_loc,
          shapes::vertex_attrib_kind::position,
          buf);
        gl.bind_attrib_location(prog, position_loc, "Position");

        // coords
        vertex_attrib_location coord_loc{1};
        owned_buffer_name coords;
        gl.gen_buffers() >> coords;
        auto cleanup_coords = gl.delete_buffers.raii(coords);
        shape.attrib_setup(
          glapi,
          vao,
          coords,
          coord_loc,
          shapes::vertex_attrib_kind::face_coord,
          buf);
        gl.bind_attrib_location(prog, coord_loc, "Coord");

        // indices
        owned_buffer_name indices;
        gl.gen_buffers() >> indices;
        auto cleanup_indices = gl.delete_buffers.raii(indices);
        shape.index_setup(glapi, indices, buf);

        // subroutines
        subroutine_uniform_location pattern_loc;
        gl.get_subroutine_uniform_location(
          prog, GL.fragment_shader, "pattern") >>
          pattern_loc;

        std::array<subroutine_location, 6> subroutines;
        gl.get_subroutine_index(prog, GL.fragment_shader, "horzStrip") >>
          subroutines[0];
        gl.get_subroutine_index(prog, GL.fragment_shader, "vertStrip") >>
          subroutines[1];
        gl.get_subroutine_index(prog, GL.fragment_shader, "diagStrip") >>
          subroutines[2];
        gl.get_subroutine_index(prog, GL.fragment_shader, "checker") >>
          subroutines[3];
        gl.get_subroutine_index(prog, GL.fragment_shader, "spiral") >>
          subroutines[4];
        gl.get_subroutine_index(prog, GL.fragment_shader, "dots") >>
          subroutines[5];

        // uniforms
        uniform_location center_loc;
        gl.get_uniform_location(prog, "center") >> center_loc;

        uniform_location camera_loc;
        gl.get_uniform_location(prog, "camera") >> camera_loc;

        orbiting_camera camera;
        camera.set_near(0.1F)
          .set_far(50.F)
          .set_fov(right_angle_())
          .set_orbit_min(4.F)
          .set_orbit_max(5.F);

        gl.clear_color(0.35F, 0.35F, 0.35F, 1.0F);
        gl.clear_depth(1);
        gl.enable(GL.depth_test);

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

            for(const auto s : integer_range(subroutines.size())) {
                const auto angle = turns_(float(s) / float(subroutines.size()));

                glapi.set_uniform(
                  prog,
                  center_loc,
                  vec3(2.5F * cos(angle), 0.F, 2.5F * sin(angle)));
                gl.uniform_subroutines(
                  GL.fragment_shader, pattern_loc / subroutines[s]);

                draw_using_instructions(glapi, view(_ops));
            }

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
