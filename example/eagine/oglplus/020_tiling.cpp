/// @example oglplus/000_tiling.cpp
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
out float vertDist;
out vec2 vertCoord;
uniform mat4 Camera;

void main() {
    gl_Position = Camera * vec4(Position, 1.0);
	vertDist = gl_Position.w;
	vertCoord = Coord;
}
)"};

static const eagine::string_view fs_source{R"(
#version 400
in float vertDist;
in vec2 vertCoord;
out vec3 fragColor;
uniform sampler2D Transition;
uniform sampler2DArray Tileset;

void main() {
	vec2 TileCoord = vertCoord * 2048.0;
	vec4 LayerCoord = texelFetch(Transition, ivec2(TileCoord), 0);
	float Index = LayerCoord.x * 255.0;
	float Variant = LayerCoord.y * 255.0;
	float VariantCoef = LayerCoord.y * 15.0;
	float Layer = float(Index * 16.0 + Variant);
	float Mask = 1.0 - step(Index, 1.0);
	float Factor = pow(clamp(1.0 - vertDist, 0.0, 1.0), 2.0);
	float Rough = mix(0.30, 0.40, VariantCoef);
	float Detail = texture(Tileset, vec3(fract(TileCoord), Layer)).r;
	Detail = mix(Detail * mix(0.3, 0.6, VariantCoef), Detail, Factor);
	float Value = mix(Rough * Mask + 0.07 * (Detail - 0.5), Detail, Factor);
	fragColor = vec3(Value);
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
        gl_debug_logger gdl{ctx, glapi};
        gl.debug_message_control(
          GL.dont_care, GL.dont_care, GL.dont_care, GL.true_);

        memory::buffer temp;

        // geometry
        shape_generator shape(
          glapi,
          shapes::unit_plane(
            shapes::vertex_attrib_kind::position |
            shapes::vertex_attrib_kind::wrap_coord));

        geometry_and_bindings plane{glapi, shape, temp};
        plane.use(glapi);

        // vertex shader
        owned_shader_name vs;
        gl.create_shader(GL.vertex_shader) >> vs;
        const auto cleanup_vs{gl.delete_shader.raii(vs)};
        gl.object_label(vs, "vertex shader");
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // fragment shader
        owned_shader_name fs;
        gl.create_shader(GL.fragment_shader) >> fs;
        const auto cleanup_fs{gl.delete_shader.raii(fs)};
        gl.object_label(fs, "fragment shader");
        gl.shader_source(fs, glsl_string_ref(fs_source));
        gl.compile_shader(fs);

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        const auto cleanup_prog{gl.delete_program.raii(prog)};
        gl.object_label(prog, "draw program");
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);
        gl.bind_attrib_location(prog, plane.position_loc(), "Position");
        gl.bind_attrib_location(prog, plane.wrap_coord_loc(), "Coord");

        // transition texture
        owned_texture_name transition_tex;
        gl.gen_textures() >> transition_tex;
        const auto cleanup_transition_tex{
          gl.delete_textures.raii(transition_tex)};
        gl.active_texture(GL.texture0 + 0);
        gl.bind_texture(GL.texture_2d, transition_tex);
        if(not build_from_resource(
             ctx,
             glapi,
             search_resource("Transition"),
             transition_tex,
             GL.texture_2d)) {
            ctx.log().error("failed to load transition texture");
        }

        // tileset texture
        owned_texture_name tileset_tex;
        gl.gen_textures() >> tileset_tex;
        const auto cleanup_tileset_tex{gl.delete_textures.raii(tileset_tex)};
        gl.active_texture(GL.texture0 + 1);
        gl.bind_texture(GL.texture_2d_array, tileset_tex);
        if(not build_from_resource(
             ctx,
             glapi,
             search_resource("Tileset"),
             tileset_tex,
             GL.texture_2d_array)) {
            ctx.log().error("failed to load tileset texture");
        }
        gl.generate_mipmap(GL.texture_2d_array);

        // uniform
        oglplus::uniform_location transition_tex_loc;
        gl.get_uniform_location(prog, "Transition") >> transition_tex_loc;
        glapi.set_uniform(prog, transition_tex_loc, 0);
        oglplus::uniform_location tileset_tex_loc;
        gl.get_uniform_location(prog, "Tileset") >> tileset_tex_loc;
        glapi.set_uniform(prog, tileset_tex_loc, 1);

        uniform_location camera_loc;
        gl.get_uniform_location(prog, "Camera") >> camera_loc;

        // camera setup
        orbiting_camera camera;
        camera.set_near(0.0025F)
          .set_far(5.F)
          .set_orbit_min(0.0072F)
          .set_orbit_max(2.0F)
          .set_fov(degrees_(40));

        gl.clear_color(0.05F, 0.05F, 0.05F, 1.0F);
        gl.clear_depth(1.F);
        gl.enable(GL.depth_test);

        float t = 0.F;
        const float dt = 0.02F;

        animated_value<std::tuple<float, float, float>, float> coord;
        enum class animation_status { zoom_in, zoom_out, wait, relocate };
        animation_status camera_status{animation_status::zoom_in};

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

            const auto [target_x, target_y, orbit] = coord.update(dt).get();
            if(coord.is_done()) {
                switch(camera_status) {
                    case animation_status::relocate:
                        coord.set(
                          {target_x, target_y, 0.05F},
                          2.F + ctx.random_uniform_11());
                        camera_status = animation_status::zoom_in;
                        break;
                    case animation_status::zoom_in:
                        coord.set(
                          {target_x + 0.02, target_y + 0.02, 0.F},
                          9.F + ctx.random_uniform_11());
                        camera_status = animation_status::wait;
                        break;
                    case animation_status::wait:
                        coord.set(
                          {target_x, target_y, 1.F},
                          3.F + ctx.random_uniform_01());
                        camera_status = animation_status::zoom_out;
                        break;
                    case animation_status::zoom_out:
                        coord.set(
                          {ctx.random_uniform_11(),
                           ctx.random_uniform_11(),
                           orbit},
                          2.F + ctx.random_uniform_01());
                        camera_status = animation_status::relocate;
                        break;
                }
            }

            gl.viewport(width, height);

            gl.clear(GL.color_buffer_bit | GL.depth_buffer_bit);

            t += dt;
            const auto aspect = float(width) / float(height);
            glapi.set_uniform(
              prog,
              camera_loc,
              camera.set_target({target_x, 0.F, target_y})
                .set_azimuth(radians_(t * 0.2))
                .set_elevation(radians_(math::sine_wave01(t * 0.072) + 0.510))
                .set_orbit_factor(orbit)
                .matrix(aspect));

            plane.draw(glapi);

            glfwSwapBuffers(window);
        }
        plane.clean_up(glapi);
    } else {
        std::cout << "missing required API" << std::endl;
    }
}

static void init_and_run(eagine::main_ctx& ctx) {
    if(not glfwInit()) {
        throw std::runtime_error("GLFW initialization error");
    } else {
        auto ensure_glfw_cleanup{eagine::finally(glfwTerminate)};

        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);

        glfwWindowHint(GLFW_SAMPLES, GLFW_DONT_CARE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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

