/// @example oglplus/005_cartoon_sun.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/gl_api.hpp>

#include <eagine/main.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/geometry.hpp>
#include <eagine/shapes/screen.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

static const eagine::string_view vs_source{R"(
#version 140
in vec2 Position;
out vec2 vertCoord;
void main() {
	gl_Position = vec4(Position, 0.0, 1.0);
	vertCoord = gl_Position.xy;
}
)"};

static const eagine::string_view fs_source{R"(
#version 140
uniform float time;
uniform vec2 sunPos;
const vec3 sun1 = vec3(0.95, 0.85, 0.60);
const vec3 sun2 = vec3(0.90, 0.80, 0.20);
const vec3 sky1 = vec3(0.90, 0.80, 0.50);
const vec3 sky2 = vec3(0.80, 0.60, 0.40);

in vec2 vertCoord;
out vec3 fragColor;
void main() {
	vec2 v = vertCoord - sunPos;
	float l = length(v);
	float a = (sin(l)+atan(v.y, v.x)) / 3.1415;
	if(l < 0.1) {
		fragColor = sun1;
	} else if(int(18 * (time * 0.1 + 1.0 + a)) % 2 == 0) {
		fragColor = mix(sun1, sun2, l);
	} else {
		fragColor = mix(sky1, sky2, l);
	}
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

        memory::buffer temp;
        // geometry
        shape_generator shape(
          glapi, shapes::unit_screen(shapes::vertex_attrib_kind::position));

        geometry_and_bindings screen{glapi, shape, temp};

        // vertex shader
        const auto vs{gl.create_shader.object(GL.vertex_shader)};
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // fragment shader
        const auto fs{gl.create_shader.object(GL.fragment_shader)};
        gl.shader_source(fs, glsl_string_ref(fs_source));
        gl.compile_shader(fs);

        // program
        const auto prog{gl.create_program.object()};
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);

        gl.bind_attrib_location(prog, screen.position_loc(), "Position");

        // uniforms
        auto update_uniforms = [&glapi, &prog]() {
            uniform_location sun_pos_loc;
            glapi.get_uniform_location(prog, "sunPos") >> sun_pos_loc;

            uniform_location time_loc;
            glapi.get_uniform_location(prog, "time") >> time_loc;

            return [&glapi, &prog, sun_pos_loc, time_loc, time{0.F}](
                     float a) mutable {
                const float d = 0.5F;
                glapi.set_uniform(prog, time_loc, time);
                glapi.set_uniform(
                  prog,
                  sun_pos_loc,
                  oglplus::vec2(-a * d * std::cos(time), d * std::sin(time)));
                time += 0.01F;
            };
        }();

        gl.disable(GL.depth_test);

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

            update_uniforms(float(width) / float(height));
            screen.use(glapi);
            screen.draw(glapi);

            glfwSwapBuffers(window);
        }
        screen.clean_up(glapi);
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
