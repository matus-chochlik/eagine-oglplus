/// @example oglplus/017_subroutines.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <GLFW/glfw3.h>

import std;
import eagine.core;
import eagine.shapes;
import eagine.oglplus;

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

        // geometry
        memory::buffer temp;
        shape_generator shape(
          glapi,
          shapes::unit_round_cube(
            shapes::vertex_attrib_kind::position |
            shapes::vertex_attrib_kind::face_coord));
        geometry_and_bindings cube{glapi, shape, temp};
        cube.use(glapi);

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
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);

        gl.bind_attrib_location(prog, cube.position_loc(), "Position");
        gl.bind_attrib_location(prog, cube.face_coord_loc(), "Coord");

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
            if((width != new_width) or (height != new_height)) {
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

            for(const auto s : index_range(subroutines)) {
                const auto angle = turns_(float(s) / float(subroutines.size()));

                glapi.set_uniform(
                  prog,
                  center_loc,
                  vec3(2.5F * cos(angle), 0.F, 2.5F * sin(angle)));
                gl.uniform_subroutines(GL.fragment_shader, subroutines[s]);

                cube.draw(glapi);
            }

            glfwSwapBuffers(window);
        }
        cube.clean_up(glapi);
    } else {
        std::cout << "missing required API" << std::endl;
    }
}

static void init_and_run(eagine::main_ctx& ctx) {
    if(not glfwInit()) {
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

        if(not window) {
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

