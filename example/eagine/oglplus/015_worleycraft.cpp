/// @example oglplus/015_worleycraft.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.shapes;
import eagine.oglplus;
import std;

#include <GLFW/glfw3.h>

static const eagine::string_view vs_source{R"(
#version 140
in vec4 Position;
in vec2 Coord;
out vec2 vertCoord;

void main() {
    gl_Position = Position;
    vertCoord = Coord;
}
)"};

static const eagine::string_view gs_source{R"(
#version 150

layout(lines_adjacency) in;
layout(triangle_strip, max_vertices = 20) out;

in vec2 vertCoord[4];
out vec3 geomColor;
out float geomExtrude;
uniform mat4 Camera;
uniform sampler2D Tex;

void main() {
	vec2 Coord = (vertCoord[0]+vertCoord[1]+vertCoord[2]+vertCoord[3]) * 0.25;
	vec4 Texel = texture(Tex, Coord);
	geomColor = Texel.rgb;

    ivec4 eidx = ivec4(0, 2, 3, 1);
	vec3 pofs = vec3(0.0, Texel.a * 0.15, 0.0);

	for(int i=0; i<4; ++i) {
		for(int j=0; j<2; ++j) {
			vec3 tpos = gl_in[eidx[(i+j)%4]].gl_Position.xyz;
			geomExtrude = 0.0;
			gl_Position = Camera * vec4(tpos, 1.0);
			EmitVertex();
			geomExtrude = sqrt(Texel.a);
			gl_Position = Camera * vec4(tpos + pofs, 1.0);
			EmitVertex();
		}
		EndPrimitive();
	}

	geomExtrude = sqrt(Texel.a);
	for(int i=0; i<4; ++i) {
		gl_Position = Camera * vec4(gl_in[i].gl_Position.xyz + pofs, 1.0);
		EmitVertex();
	}
	EndPrimitive();
}
)"};

static const eagine::string_view fs_source{R"(
#version 140
in vec3 geomColor;
in float geomExtrude;
out vec3 fragColor;

void main() {
    fragColor = geomColor * geomExtrude * 1.41;
}
)"};

static void run_loop(
  eagine::main_ctx& ctx,
  GLFWwindow* window,
  int width,
  int height) {
    using namespace eagine;
    using namespace eagine::oglplus;

    auto& args = ctx.args();
    int divisions = 256;

    if(args.find("--128")) {
        divisions = 128;
    } else if(args.find("--512")) {
        divisions = 512;
    } else if(args.find("--64")) {
        divisions = 64;
    }

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
          glapi,
          shapes::to_quads(shapes::unit_plane(
            shapes::vertex_attrib_kind::position |
              shapes::vertex_attrib_kind::wrap_coord,
            divisions,
            divisions)));

        geometry_and_bindings plane{glapi, shape, temp};
        plane.use(glapi);

        // vertex shader
        owned_shader_name vs;
        gl.create_shader(GL.vertex_shader) >> vs;
        const auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.object_label(vs, "vertex shader");
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // geometry shader
        owned_shader_name gs;
        gl.create_shader(GL.geometry_shader) >> gs;
        const auto cleanup_gs = gl.delete_shader.raii(gs);
        gl.object_label(gs, "geometry shader");
        gl.shader_source(gs, glsl_string_ref(gs_source));
        gl.compile_shader(gs);

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
        gl.attach_shader(prog, gs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);
        gl.bind_attrib_location(prog, plane.position_loc(), "Position");
        gl.bind_attrib_location(prog, plane.wrap_coord_loc(), "Coord");

        // texture
        owned_texture_name tex;
        gl.gen_textures() >> tex;
        const auto cleanup_tex = gl.delete_textures.raii(tex);
        gl.active_texture(GL.texture0);
        gl.bind_texture(GL.texture_2d, tex);
        build_from_resource(
          ctx, glapi, search_resource("WorleyTex"), tex, GL.texture_2d);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_min_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_mag_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_wrap_s, GL.clamp_to_edge);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_wrap_t, GL.clamp_to_edge);

        // uniform
        oglplus::uniform_location tex_loc;
        gl.get_uniform_location(prog, "Tex") >> tex_loc;
        glapi.set_uniform(prog, tex_loc, 0);

        uniform_location camera_loc;
        gl.get_uniform_location(prog, "Camera") >> camera_loc;

        // camera setup
        orbiting_camera camera;
        camera.set_near(0.1F)
          .set_far(10.F)
          .set_orbit_min(1.41F)
          .set_orbit_max(1.71F)
          .set_fov(degrees_(40));

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
              camera.set_azimuth(radians_(t * 0.2))
                .set_elevation(radians_(std::sin(t * 0.618 * 0.3)))
                .set_orbit_factor(math::sine_wave01(t * 0.1618F))
                .matrix(aspect));

            plane.draw(glapi);

            glfwSwapBuffers(window);
        }
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

