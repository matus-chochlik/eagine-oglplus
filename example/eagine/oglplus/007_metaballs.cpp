/// @example oglplus/007_metaballs.cpp
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
#include <eagine/math/curve.hpp>
#include <eagine/math/functions.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/generator.hpp>
#include <eagine/shapes/screen.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <random>
#include <stdexcept>

static const eagine::string_view vs_source{R"(
#version 140
in vec2 Position;
out vec3 vertPosition;
void main() {
	vertPosition = vec3(Position, 0.0);
	gl_Position = vec4(vertPosition, 1.0);
}
)"};

static const eagine::string_view fs_source{R"(
#version 140
uniform sampler1D metaballs;
in vec3 vertPosition;
out vec3 fragColor;

const vec3 diffuseColor = vec3(0.4, 0.9, 0.5);
const vec3 lightDir = normalize(vec3(1.0, 1.0, 2.0));

void main() {
	int i = 0, n = textureSize(metaballs, 0);

	float invN = 1.0 / n;
	float value = 0.0;
	vec3 normal = vec3(0.0, 0.0, 0.0);

	while(i != n) {
		vec4 metaball = texelFetch(metaballs, i, 0);
		float radius = metaball.w;
		vec3 vect = vertPosition - metaball.xyz;
		float tmp = pow(radius, 2.0) / dot(vect, vect) - 0.25;
		value += tmp;
		normal += max(tmp, 0.0) *
			vec3(vect.xy, sqrt(abs(pow(radius, 2.0) - dot(vect.xy, vect.xy))));
		++i;
	}

	if(value > 0.0) {
		float ld = dot(lightDir, normalize(normal));
		float specular = min(pow(max(ld+0.001, 0.0), 64.0), 1.0);
		float diffuse = clamp(ld, 0.0, 1.0) * 0.7;
		float ambient = 0.3;

		fragColor = (ambient + diffuse) * diffuseColor + vec3(specular);
	} else {
		fragColor = vec3(0.4, 0.4, 0.4);
	}
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
          glapi, shapes::unit_screen(shapes::vertex_attrib_kind::position));

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

        // indices
        owned_buffer_name indices;
        gl.gen_buffers() >> indices;
        auto cleanup_indices = gl.delete_buffers.raii(indices);
        shape.index_setup(glapi, indices, buf);

        std::vector<math::cubic_bezier_loop<oglplus::vec4, float>> loops;
        std::vector<oglplus::vec4> cp_data;
        std::default_random_engine rnd_eng{std::random_device{}()};
        for(const auto l : integer_range(12)) {
            EAGINE_MAYBE_UNUSED(l);
            const auto n =
              3U + std::uniform_int_distribution<unsigned>{0U, 4U}(rnd_eng);
            cp_data.resize(n);
            const auto rad =
              std::uniform_real_distribution<float>{0.1F, 0.2F}(rnd_eng);
            for(auto p : integer_range(n)) {
                cp_data[p] = oglplus::vec4(
                  std::uniform_real_distribution<float>{-0.7F, 0.7F}(rnd_eng),
                  std::uniform_real_distribution<float>{-0.7F, 0.7F}(rnd_eng),
                  0.F,
                  rad);
            }
            loops.emplace_back(view(cp_data));
        }
        std::vector<float> metaball_data{};
        metaball_data.resize(loops.size() * 4U);

        // metaball parameters
        owned_texture_name metaball_tex{};
        gl.gen_textures() >> metaball_tex;
        auto cleanup_metaballs = gl.delete_textures.raii(metaball_tex);
        gl.active_texture(GL.texture0);
        gl.bind_texture(GL.texture_1d, metaball_tex);
        gl.tex_parameter_i(GL.texture_1d, GL.texture_min_filter, GL.nearest);
        gl.tex_parameter_i(GL.texture_1d, GL.texture_mag_filter, GL.nearest);

        auto update_metaballs =
          [&glapi, &loops, &metaball_data, t{0.F}]() mutable {
              auto& [gl_, GL_] = glapi;
              for(const auto i : integer_range(loops.size())) {
                  for(const auto c : integer_range(std_size(4))) {
                      const auto p = loops[i].position(t);
                      metaball_data[i * 4U + c] = p[c];
                  }
              }
              gl_.tex_image1d(
                GL_.texture_1d,
                0,
                GL_.rgba32f,
                limit_cast<oglplus::gl_types::uint_type>(loops.size()),
                0,
                GL_.rgba,
                GL_.float_,
                as_bytes(view(metaball_data)));
              t += 0.001F;
          };
        update_metaballs();

        // uniform
        uniform_location metaballs_loc;
        gl.get_uniform_location(prog, "metaballs") >> metaballs_loc;
        glapi.set_uniform(prog, metaballs_loc, 0);

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
            update_metaballs();

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