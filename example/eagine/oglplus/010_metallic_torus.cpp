/// @example oglplus/010_metallic_torus.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/gl_api.hpp>

#include <eagine/main.hpp>
#include <eagine/math/curve.hpp>
#include <eagine/math/functions.hpp>
#include <eagine/memory/flatten.hpp>
#include <eagine/oglplus/camera.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/matrix.hpp>
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/generator.hpp>
#include <eagine/shapes/twisted_torus.hpp>

#include <GLFW/glfw3.h>

#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>

static const eagine::string_view vs_source{R"(
#version 140
in vec3 Position;
in vec3 Normal;
out vec3 vertNormal;
out vec3 vertViewDir;
uniform vec3 cameraPos;
uniform mat4 camera;
uniform mat4 model;

void main() {
    gl_Position = model * vec4(Position, 1.0);
    vertNormal = mat3(model) * Normal;
	vertViewDir = gl_Position.xyz - cameraPos;
    gl_Position = camera * vec4(gl_Position.xyz, 1.0);
}
)"};

static const eagine::string_view fs_source{R"(
#version 140
uniform sampler1D gradient;
in vec3 vertNormal;
in vec3 vertViewDir;
out vec3 fragColor;

void main() {
	vec3 viewDir = normalize(vertViewDir);
	vec3 normal = normalize(vertNormal);
	vec3 reflected = reflect(viewDir, normal);
	float coord = 0.5 + 0.5*reflected.y;
    fragColor = vec3(texture(gradient, coord));
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
          shapes::unit_twisted_torus(
            shapes::vertex_attrib_kind::position |
              shapes::vertex_attrib_kind::normal,
            24,
            64,
            8,
            0.6F));

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

        // normals
        vertex_attrib_location normal_loc{1};
        owned_buffer_name normals;
        gl.gen_buffers() >> normals;
        auto cleanup_normals = gl.delete_buffers.raii(normals);
        shape.attrib_setup(
          glapi,
          vao,
          normals,
          normal_loc,
          shapes::vertex_attrib_kind::normal,
          buf);
        gl.bind_attrib_location(prog, normal_loc, "Normal");

        // indices
        owned_buffer_name indices;
        gl.gen_buffers() >> indices;
        auto cleanup_indices = gl.delete_buffers.raii(indices);
        shape.index_setup(glapi, indices, buf);

        // gradient

        owned_texture_name gradient_tex{};
        gl.gen_textures() >> gradient_tex;
        auto cleanup_gradients = gl.delete_textures.raii(gradient_tex);
        gl.active_texture(GL.texture0);
        gl.bind_texture(GL.texture_1d, gradient_tex);
        gl.tex_parameter_i(GL.texture_1d, GL.texture_min_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_1d, GL.texture_mag_filter, GL.linear);
        {
            std::array<oglplus::vec3, 12> grad_curve_cps{
              {{0.0F, 0.0F, 0.0F},
               {0.0F, 0.0F, 0.0F},
               {0.0F, 0.0F, 0.0F},
               {0.0F, 0.0F, 0.0F},
               {0.0F, 0.0F, 0.0F},
               {0.8F, 0.5F, 0.3F},
               {0.7F, 0.7F, 0.7F},
               {0.3F, 0.3F, 0.6F},
               {0.2F, 0.2F, 0.4F},
               {0.1F, 0.1F, 0.2F},
               {0.0F, 0.0F, 0.0F},
               {0.0F, 0.0F, 0.0F}}};
            math::bezier_curves<oglplus::vec3, float, 2> grad_curve{
              view(grad_curve_cps)};
            std::vector<oglplus::vec3> grad_colors;
            grad_curve.approximate(grad_colors, 64);
            std::vector<float> grad_data;
            memory::flatten(view(grad_colors), grad_data);
            gl.tex_image1d(
              GL.texture_1d,
              0,
              GL.rgb,
              limit_cast<oglplus::gl_types::int_type>(grad_colors.size()),
              0,
              GL.rgb,
              GL.float_,
              as_bytes(view(grad_data)));
        }

        // uniforms
        uniform_location gradients_loc;
        gl.get_uniform_location(prog, "gradients") >> gradients_loc;
        glapi.set_uniform(prog, gradients_loc, 0);

        uniform_location camera_pos_loc;
        gl.get_uniform_location(prog, "cameraPos") >> camera_pos_loc;

        uniform_location camera_loc;
        gl.get_uniform_location(prog, "camera") >> camera_loc;

        uniform_location model_loc;
        gl.get_uniform_location(prog, "model") >> model_loc;

        orbiting_camera camera;
        camera.set_near(0.1F)
          .set_far(50.F)
          .set_fov(degrees_(70))
          .set_orbit_min(1.F)
          .set_orbit_max(2.F);

        gl.clear_color(0.05F, 0.05F, 0.05F, 1.0F);
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

            t += 0.01F;
            const auto aspect = float(width) / float(height);
            camera.set_azimuth(radians_(t))
              .set_elevation(radians_(std::sin(t)))
              .set_orbit_factor(math::sine_wave01(t * 0.1F));
            glapi.set_uniform(prog, camera_pos_loc, camera.position());
            glapi.set_uniform(prog, camera_loc, camera.matrix(aspect));
            glapi.set_uniform(
              prog, model_loc, oglplus::matrix_rotation_x(right_angles_(t))());
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
