/// @example oglplus/008_worley_waves.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/gl_api.hpp>

#include <eagine/integer_range.hpp>
#include <eagine/main.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/generator.hpp>
#include <eagine/random_bytes.hpp>
#include <eagine/shapes/screen.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

static const eagine::oglplus::glsl_source_ref vs_source{R"(
#version 140

uniform vec2 viewSize;

in vec4 Position;

out vec2 vertTexCoord;

void main() {
    gl_Position = Position;
    vertTexCoord = min(viewSize * 0.01, vec2(25.0)) * Position.xy;
}
)"};

static const eagine::oglplus::glsl_source_ref fs_source{R"(
#version 140

uniform sampler2D noise;
uniform float time;

in vec2 vertTexCoord;

out vec3 fragColor;

const vec2 offs[9] = vec2[9](
  vec2(-1, -1),
  vec2(-1, 0),
  vec2(-1, 1),
  vec2(0, -1),
  vec2(0, 0),
  vec2(0, 1),
  vec2(1, -1),
  vec2(1, 0),
  vec2(1, 1));

vec2 point(vec2 tc, vec2 ofs) {
    vec2 cc = floor(tc + ofs);
	vec2 pa = texture(noise, cc / textureSize(noise, 0)).xy;
	float phase0 = pa.x * 2.0 * 3.14159;
	float phase1 = sin((2.0 * cc.x + cc.y) + time) + 1.618 * time * sign(pa.y - 0.5);
    return cc + vec2(cos(phase0 + phase1), sin(phase0 + phase1)) * 0.5 + vec2(0.5);
}

float dist(vec2 tc, vec2 ofs) {
    vec2 cp = point(tc, ofs);
    return distance(tc, cp);
}

vec3 worley(vec2 tc) {
	float ds[9];
    for(int c = 0; c < 9; ++c) {
		ds[c] = dist(tc, offs[c]);
    }
	float md = ds[0];
	int mc = 0;
    for(int c = 1; c < 9; ++c) {
		if(md > ds[c]) {
			md = ds[c];
			mc = c;
		}
    }
	float nd = 4;
    for(int c = 0; c < 9; ++c) {
		if(c != mc) {
			nd = min(nd, ds[c]);
		}
    }
    return vec3(pow(nd-md, 0.618));
}

void main() {
    fragColor = worley(vertTexCoord);
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

    float time = 0.F;

    if(gl.clear) {
        gl_debug_logger gdl{ctx};

        gl.debug_message_callback(gdl);
        gl.debug_message_control(
          GL.dont_care, GL.dont_care, GL.dont_care, GL.true_);

        memory::buffer buf;

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        const auto cleanup_prog = gl.delete_program.raii(prog);
        gl.object_label(prog, "draw program");
        glapi.add_shader(prog, GL.vertex_shader, vs_source);
        glapi.add_shader(prog, GL.fragment_shader, fs_source);
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

        // indices
        owned_buffer_name indices;
        gl.gen_buffers() >> indices;
        const auto cleanup_indices = gl.delete_buffers.raii(indices);
        shape.index_setup(glapi, indices, "indices", buf);

        // noise texture
        owned_texture_name noise_tex{};
        gl.gen_textures() >> noise_tex;
        const auto cleanup_gradients = gl.delete_textures.raii(noise_tex);
        gl.active_texture(GL.texture0);
        gl.bind_texture(GL.texture_2d, noise_tex);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_min_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_mag_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_wrap_s, GL.repeat);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_wrap_t, GL.repeat);
        {
            auto random_data =
              GL.unsigned_byte_.array(size_constant<256 * 256 * 2>{});
            fill_with_random_bytes(cover(random_data));
            gl.tex_image2d(
              GL.texture_2d,
              0,
              GL.rg,
              256,
              256,
              0,
              GL.rg,
              GL.unsigned_byte_,
              as_bytes(view(random_data)));
        }

        // uniform
        uniform_location time_loc;
        gl.get_uniform_location(prog, "time") >> time_loc;
        glapi.set_uniform(prog, time_loc, 0.F);

        uniform_location view_size_loc;
        gl.get_uniform_location(prog, "viewSize") >> view_size_loc;

        uniform_location noise_loc;
        gl.get_uniform_location(prog, "noise") >> noise_loc;
        glapi.set_uniform(prog, noise_loc, 0);

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

            glapi.set_uniform(
              prog, view_size_loc, oglplus::vec2(width, height));
            glapi.set_uniform(prog, time_loc, time);
            draw_using_instructions(glapi, view(_ops));

            glfwSwapBuffers(window);
            time += 0.01F;
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
