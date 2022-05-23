/// @example oglplus/014_texture_projection.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/gl_api.hpp>

#include <eagine/embed.hpp>
#include <eagine/main.hpp>
#include <eagine/math/functions.hpp>
#include <eagine/oglplus/camera.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/matrix.hpp>
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/geometry.hpp>
#include <eagine/shapes/cube.hpp>
#include <eagine/shapes/sphere.hpp>
#include <eagine/shapes/torus.hpp>
#include <eagine/shapes/twisted_torus.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

static const eagine::string_view vs_source{R"(
#version 150
in vec3 Position;
in vec3 Normal;

out vec3 vertLightDir;
out vec3 vertNormal;
out vec2 vertTexCoord;

uniform mat4 model, camera, projector;
uniform vec3 lightPos;

void main() {
	gl_Position = model * vec4(Position, 1.0);
	vertLightDir = lightPos - Position.xyz;
	vertNormal = mat3(model) * -Normal;
	vertTexCoord = (projector * gl_Position).xy;
	gl_Position = camera * gl_Position;
}
)"};

static const eagine::string_view fs_source{R"(
#version 150
in vec3 vertLightDir;
in vec3 vertNormal;
in vec2 vertTexCoord;
out vec3 fragColor;

uniform vec3 lightDir;
uniform sampler2D colorTex;

void main() {
	float ld = dot(vertNormal, normalize(vertLightDir));
	fragColor = (abs(ld) * 0.6 + 0.4) * mix(
		vec3(1.0),
		texture(colorTex, vertTexCoord).rgb,
		sqrt(max(ld, 0.0)));
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
        vertex_attrib_bindings bindings{
          shapes::vertex_attrib_kind::position,
          shapes::vertex_attrib_kind::normal};

        auto [shape, inv_cull] = [&]() -> std::tuple<shape_generator, bool> {
            const auto attribs = bindings.attrib_kinds();
            if(ctx.args().find("--twisted-torus")) {
                return {
                  {glapi, shapes::unit_twisted_torus(attribs, 6, 48, 4, 0.5F)},
                  false};
            }
            if(ctx.args().find("--torus")) {
                return {{glapi, shapes::unit_torus(attribs)}, false};
            }
            if(ctx.args().find("--sphere")) {
                return {{glapi, shapes::unit_sphere(attribs)}, false};
            }
            return {{glapi, shapes::unit_cube(attribs)}, true};
        }();

        geometry geom{glapi, shape, bindings, 0, temp};
        geom.use(glapi);

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

        // color texture
        const auto color_tex_src{embed(EAGINE_ID(ColorTex), "oglplus")};

        owned_texture_name color_tex;
        gl.gen_textures() >> color_tex;
        const auto cleanup_color_tex = gl.delete_textures.raii(color_tex);
        gl.active_texture(GL.texture0 + 0);
        gl.bind_texture(GL.texture_2d, color_tex);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_min_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_mag_filter, GL.linear);
        gl.tex_parameter_i(
          GL.texture_2d, GL.texture_wrap_s, GL.clamp_to_border);
        gl.tex_parameter_i(
          GL.texture_2d, GL.texture_wrap_t, GL.clamp_to_border);
        gl.tex_parameter_fv(
          GL.texture_2d,
          GL.texture_border_color,
          element_view(oglplus::vec3{1.F}));
        glapi.spec_tex_image2d(
          GL.texture_2d,
          0,
          0,
          oglplus::texture_image_block(color_tex_src.unpack(ctx)));
        oglplus::uniform_location color_tex_loc;
        gl.get_uniform_location(prog, "colorTex") >> color_tex_loc;
        glapi.set_uniform(prog, color_tex_loc, 0);

        // uniform
        uniform_location model_loc;
        gl.get_uniform_location(prog, "model") >> model_loc;

        uniform_location camera_loc;
        gl.get_uniform_location(prog, "camera") >> camera_loc;

        uniform_location projector_loc;
        gl.get_uniform_location(prog, "projector") >> projector_loc;

        uniform_location light_pos_loc;
        gl.get_uniform_location(prog, "lightPos") >> light_pos_loc;

        orbiting_camera camera;
        camera.set_near(0.1F)
          .set_far(50.F)
          .set_fov(degrees_(75))
          .set_orbit_min(shape.bounding_sphere().radius() * 1.5F)
          .set_orbit_max(shape.bounding_sphere().radius() * 2.1F);

        orbiting_camera projector;
        projector.set_near(0.1F)
          .set_far(50.F)
          .set_fov(degrees_(90))
          .set_orbit_min(2.0F)
          .set_orbit_max(9.0F);

        gl.clear_color(0.35F, 0.35F, 0.35F, 1.0F);
        gl.clear_depth(1);
        gl.enable(GL.depth_test);
        gl.enable(GL.cull_face);
        if(inv_cull) {
            gl.cull_face(GL.front);
        } else {
            gl.cull_face(GL.back);
        }

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

            camera.set_azimuth(radians_(t))
              .set_elevation(radians_(std::sin(t)))
              .set_orbit_factor(math::sine_wave01(t * 0.1F));
            glapi.set_uniform(prog, camera_loc, camera.matrix(aspect));

            projector.set_azimuth(radians_(t * -0.1618F))
              .set_elevation(radians_(std::sin(t * 0.2F) * 0.618F))
              .set_orbit_factor(math::sine_wave01(t * 0.2F));
            glapi.set_uniform(prog, projector_loc, projector.matrix(1.F));
            glapi.set_uniform(prog, light_pos_loc, projector.position());

            glapi.set_uniform(
              prog, model_loc, matrix_rotation_x(right_angles_(t))());

            geom.draw(glapi);

            glfwSwapBuffers(window);
        }
        geom.clean_up(glapi);
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
