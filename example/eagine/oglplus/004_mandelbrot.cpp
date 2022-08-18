/// @example oglplus/004_mandelbrot.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#if EAGINE_OGLPLUS_MODULE
import eagine.core;
import eagine.shapes;
import eagine.oglplus;
import <iostream>;
import <stdexcept>;
#else
#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/gl_api.hpp>

#include <eagine/integer_range.hpp>
#include <eagine/main_ctx.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/generator.hpp>
#include <eagine/shapes/screen.hpp>
#include <iostream>
#include <stdexcept>
#endif
#include <GLFW/glfw3.h>

static const eagine::string_view vs_source{R"(
#version 120
attribute vec2 Position;
attribute vec2 Coord;
varying vec2 vertCoord;
void main() {
	vertCoord = Position.xy * 1.41 - vec2(0.6, 0.0);
	gl_Position = vec4(Position, 0.0, 1.0);
}
)"};

static const eagine::string_view fs_source{R"(
#version 120
varying vec2 vertCoord;
const int nclr = 5;
uniform vec4 clrs[5] = vec4[5](
  vec4(0.4, 0.2, 1.0f, 0.00),
  vec4(1.0, 0.2, 0.2f, 0.30),
  vec4(1.0, 1.0, 1.0f, 0.95),
  vec4(1.0, 1.0, 1.0f, 0.98),
  vec4(0.1, 0.1, 0.1f, 1.00)
);
void main() {
	vec2 z = vec2(0.0, 0.0);
	vec2 c = vertCoord;
	int i = 0, max = 128;
	while((i != max) && (distance(z, c) < 2.0)) {
		vec2 zn = vec2(
			z.x * z.x - z.y * z.y + c.x,
			2.0 * z.x * z.y + c.y
		);
		z = zn;
		++i;
	}
	float a = sqrt(float(i) / float(max));
	for(i = 0; i != (nclr - 1); ++i) {
		if(a > clrs[i].a && a <= clrs[i+1].a) {
			float m = (a - clrs[i].a) / (clrs[i+1].a - clrs[i].a);
			gl_FragColor = vec4(
				mix(clrs[i].rgb, clrs[i+1].rgb, m),
				1.0
			);
			break;
		}
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

        memory::buffer buf;

        // vertex shader
        const auto vs{gl.create_shader.object(GL.vertex_shader)};
        gl.object_label(vs, "mandelbrot vertex shader");
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // fragment shader
        const auto fs{gl.create_shader.object(GL.fragment_shader)};
        gl.object_label(fs, "mandelbrot fragment shader");
        gl.shader_source(fs, glsl_string_ref(fs_source));
        gl.compile_shader(fs);

        // program
        const auto prog{gl.create_program.object()};
        gl.object_label(prog, "mandelbrot program");
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);

        // geometry
        shape_generator shape(
          glapi, shapes::unit_screen(shapes::vertex_attrib_kind::position));

        std::vector<shape_draw_operation> _ops;
        _ops.resize(std_size(shape.operation_count()));
        shape.instructions(glapi, cover(_ops));

        // vao
        owned_vertex_array_name vao;
        gl.gen_vertex_arrays() >> vao;
        const auto cleanup_vao = gl.delete_vertex_arrays.raii(vao);
        gl.bind_vertex_array(vao);
        gl.object_label(vao, "screen VAO");

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
          buf);
        gl.bind_attrib_location(prog, position_loc, "Position");

        // indices
        owned_buffer_name indices;
        gl.gen_buffers() >> indices;
        const auto cleanup_indices = gl.delete_buffers.raii(indices);
        shape.index_setup(glapi, indices, buf);

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

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

