/// @example oglplus/022_multi_viewport.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.shapes;
import eagine.oglplus;
import <array>;
import <cmath>;
import <iostream>;
import <stdexcept>;

#include <GLFW/glfw3.h>

static const eagine::string_view vs_source{R"(
#version 150
uniform mat4 model;
in vec4 Position;
in vec3 Normal;
in vec2 Coord;
out gl_PerVertex {
    vec4 gl_Position;
};
out vec3 vertNormal;
out vec2 vertCoord;
void main() {
       gl_Position = model * Position;
       vertNormal = mat3(model) * Normal;
       vertCoord = Coord;
}
)"};

static const eagine::string_view gs_source{R"(
#version 150
#extension GL_ARB_viewport_array : enable

layout(lines_adjacency) in;
layout(triangle_strip, max_vertices = 80) out;

uniform mat4 cameras[4];
uniform float time;

in gl_PerVertex {
    vec4 gl_Position;
} gl_in[];
in vec3 vertNormal[];
in vec2 vertCoord[];
out gl_PerVertex {
    vec4 gl_Position;
};
out vec2 geomCoord;
out float geomExtrude;

void main() {
    vec3 faceNormal = normalize(
        vertNormal[0]+
        vertNormal[1]+
        vertNormal[2]+
        vertNormal[3]
    );
    vec2 faceCoord = 0.25 * (
        vertCoord[0]+
        vertCoord[1]+
        vertCoord[2]+
        vertCoord[3]
    );
    float offs = sin((faceCoord.s + faceCoord.t + time/23.0)* 3.14 * 2.0 * 10)*0.5 + 0.5;
    offs *= pow(sin(faceCoord.t * 3.1415), 2.0);
    offs *= 0.1;
    vec3 pofs = faceNormal * offs;

    ivec4 eidx = ivec4(0, 2, 3, 1);

    const vec2 coord[4] = vec2[4](
        vec2(-1.0,-1.0),
        vec2(-1.0,+1.0),
        vec2(+1.0,-1.0),
        vec2(+1.0,+1.0)
    );

    for(int vp=0; vp<4; ++vp) {
        gl_ViewportIndex = vp;
        mat4 vpcam = cameras[vp];

        for(int i=0; i<4; ++i) {
            for(int j=0; j<2; ++j) {
                vec3 tpos = gl_in[eidx[(i+j)%4]].gl_Position.xyz;
                geomCoord = coord[2*j+0];
                geomExtrude = 0.0;
                gl_Position = vpcam * vec4(tpos, 1.0);
                EmitVertex();
                geomCoord = coord[2*j+1];
                geomExtrude = 1.0;
                gl_Position = vpcam * vec4(tpos + pofs, 1.0);
                EmitVertex();
            }
            EndPrimitive();
        }

        geomExtrude = 1.0;
        for(int i=0; i<4; ++i) {
            geomCoord = coord[i];
            gl_Position = vpcam * vec4(gl_in[i].gl_Position.xyz + pofs, 1.0);
            EmitVertex();
        }
        EndPrimitive();
    }
}
)"};

static const eagine::string_view fs_source{R"(
#version 150
in vec2 geomCoord;
in float geomExtrude;

out vec3 fragColor;

void main() {
    vec2 dist = vec2(1.0)-abs(geomCoord);
    float edgeAlpha = exp(-32.0*min(dist.x, dist.y));
    fragColor = mix(vec3(sqrt(geomExtrude)), vec3(0.0), edgeAlpha);
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
          shapes::to_quads(shapes::unit_torus(
            shapes::vertex_attrib_kind::position |
            shapes::vertex_attrib_kind::normal |
            shapes::vertex_attrib_kind::wrap_coord)));
        geometry_and_bindings torus{glapi, shape, temp};
        torus.use(glapi);

        // vertex shader
        owned_shader_name vs;
        const auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.create_shader(GL.vertex_shader) >> vs;
        gl.object_label(vs, "vertex shader");
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // geometry shader
        owned_shader_name gs;
        const auto cleanup_gs = gl.delete_shader.raii(gs);
        gl.create_shader(GL.geometry_shader) >> gs;
        gl.object_label(gs, "geometry shader");
        gl.shader_source(gs, glsl_string_ref(gs_source));
        gl.compile_shader(gs);

        // fragment shader
        owned_shader_name fs;
        const auto cleanup_fs = gl.delete_shader.raii(fs);
        gl.create_shader(GL.fragment_shader) >> fs;
        gl.object_label(fs, "fragment shader");
        gl.shader_source(fs, glsl_string_ref(fs_source));
        gl.compile_shader(fs);

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        const auto cleanup_prog = gl.delete_program.raii(prog);
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, gs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);

        gl.bind_attrib_location(prog, torus.position_loc(), "Position");
        gl.bind_attrib_location(prog, torus.normal_loc(), "Normal");
        gl.bind_attrib_location(prog, torus.wrap_coord_loc(), "Coord");

        // uniforms
        uniform_location time_loc;
        gl.get_uniform_location(prog, "time") >> time_loc;

        uniform_location camera_0_loc, camera_1_loc, camera_2_loc, camera_3_loc;
        gl.get_uniform_location(prog, "cameras[0]") >> camera_0_loc;
        gl.get_uniform_location(prog, "cameras[1]") >> camera_1_loc;
        gl.get_uniform_location(prog, "cameras[2]") >> camera_2_loc;
        gl.get_uniform_location(prog, "cameras[3]") >> camera_3_loc;

        uniform_location model_loc;
        gl.get_uniform_location(prog, "model") >> model_loc;

        orbiting_camera camera;
        camera.set_near(0.01F)
          .set_far(50.F)
          .set_fov(degrees_(55))
          .set_orbit_min(0.7F)
          .set_orbit_max(1.7F);

        gl.clear_color(0.85F, 0.85F, 0.85F, 1.0F);
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
            const auto aspect = float(width) / float(height);

            const auto w_2f = float(width) / 2.F;
            const auto h_2f = float(height) / 2.F;
            const auto zero = 0.F;
            // clang-format off
            const std::array<float, 4 * 4> viewport_coords{{
				zero, zero, w_2f, h_2f,
				w_2f, zero, w_2f, h_2f,
				zero, h_2f, w_2f, h_2f,
				w_2f, h_2f, w_2f, h_2f}};
            // clang-format on

            gl.viewport_array(view(viewport_coords));

            gl.clear(GL.color_buffer_bit | GL.depth_buffer_bit);

            t += 0.01F;
            camera.set_azimuth(radians_(t))
              .set_elevation(radians_(std::sin(t)))
              .set_orbit_factor(math::sine_wave01(t * 0.1F));

            glapi.set_uniform(prog, time_loc, t);
            glapi.set_uniform(prog, camera_0_loc, camera.matrix(aspect));
            glapi.set_uniform(
              prog,
              camera_1_loc,
              oglplus::matrix_perspective::y(
                degrees_(40), aspect, 0.01F, 10.F) *
                oglplus::matrix_translation{0.F, 0.F, -1.5F});
            glapi.set_uniform(
              prog,
              camera_2_loc,
              oglplus::matrix_perspective::y(
                degrees_(20), aspect, 0.01F, 10.F) *
                oglplus::matrix_rotation_y{right_angle_()} *
                oglplus::matrix_translation{1.5F, 0.F, 0.0F});
            glapi.set_uniform(
              prog,
              camera_3_loc,
              oglplus::matrix_perspective::y(
                degrees_(30), aspect, 0.01F, 10.F) *
                oglplus::matrix_rotation_x{-right_angle_()} *
                oglplus::matrix_translation{0.F, 1.5F, 0.0F});
            glapi.set_uniform(
              prog,
              model_loc,
              oglplus::matrix_rotation_x(right_angles_(t * 0.3F))());

            torus.draw(glapi);

            glfwSwapBuffers(window);
        }
        torus.clean_up(glapi);
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

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

