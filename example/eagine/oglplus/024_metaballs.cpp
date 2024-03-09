/// @example oglplus/024_metaballs.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///

#include <GLFW/glfw3.h>

import std;
import eagine.core;
import eagine.shapes;
import eagine.oglplus;

static const eagine::string_view vs_source{R"(
#version 150
#define MB_COUNT 4

uniform mat4 cameraMatrix;
uniform ivec3 gridDim;
uniform float time;

in ivec3 Coord;
out float vertValue;
out int vertInside;

struct Metaball {
	vec3 axis;
	float speed;
	vec3 center;
	float radius;
};

Metaball metaballs[MB_COUNT] = Metaball[MB_COUNT](
	Metaball(vec3( 0.0, 1.0,15.0), 0.6, vec3( 0.0, 0.0, 1.0), 3.0),
	Metaball(vec3( 0.0, 1.0,-9.0), 0.5, vec3( 0.0, 0.0, 0.0), 6.0),
	Metaball(vec3(+7.0, 0.0, 0.0), 0.4, vec3(-7.0, 0.5, 0.0), 8.0),
	Metaball(vec3(-6.0, 0.0, 0.0), 0.3, vec3(+7.0,-0.5, 0.0), 9.0));

vec3 position() {
    ivec3 d = gridDim * 2;
    int x = gl_InstanceID % d.x;
    int z = (gl_InstanceID / d.x) % d.z;
    int y = gl_InstanceID / (d.x * d.z);
    return vec3(Coord + ivec3(x, y, z) - gridDim);
}

float fieldValue(vec3 coord) {
    const float inorm = (1.0 / MB_COUNT);
    float eps = 0.001;
	float result = 0.0;
    for(int i = 0; i < MB_COUNT; ++i) {
		float param = -cos(time * metaballs[i].speed);
        vec3 vect = coord - (metaballs[i].center + param * metaballs[i].axis);
        float rad = metaballs[i].radius;
        float value = (pow(rad, 2.0) / (dot(vect, vect) + eps)) - 0.5;
        result += value;
    }
    result *= inorm;
    return result;
}

void main() {
    vec3 p = position();
    vertValue = fieldValue(p);
    vertInside = (vertValue >= 0.0) ? 1 : 0;
    gl_Position = cameraMatrix * vec4(p / sqrt(dot(gridDim, gridDim)), 1.0) ;
}
)"};

static const eagine::string_view gs_source{R"(
#version 430

layout (lines_adjacency) in;
layout (triangle_strip, max_vertices = 16) out;

in float vertValue[4];
in int vertInside[4];
uniform mat4 perspectiveMatrix;

const uvec4 edgeVertices[32] = uvec4[32](
    uvec4(9, 9, 9, 9),  uvec4(9, 9, 9, 9),
    uvec4(0, 2, 1, 9),  uvec4(3, 3, 3, 9),
    uvec4(1, 3, 0, 9),  uvec4(2, 2, 2, 9),
    uvec4(1, 1, 0, 0),  uvec4(2, 3, 2, 3),
    uvec4(0, 3, 2, 9),  uvec4(1, 1, 1, 9),
    uvec4(0, 0, 2, 2),  uvec4(1, 3, 1, 3),
    uvec4(0, 0, 3, 3),  uvec4(2, 1, 2, 1),
    uvec4(0, 0, 0, 9),  uvec4(1, 3, 2, 9),
    uvec4(2, 3, 1, 9),  uvec4(0, 0, 0, 9),
    uvec4(2, 2, 1, 1),  uvec4(0, 3, 0, 3),
    uvec4(1, 3, 1, 3),  uvec4(2, 2, 0, 0),
    uvec4(1, 1, 1, 9),  uvec4(2, 3, 0, 9),
    uvec4(2, 3, 2, 3),  uvec4(0, 0, 1, 1),
    uvec4(2, 2, 2, 9),  uvec4(0, 3, 1, 9),
    uvec4(3, 3, 3, 9),  uvec4(0, 1, 2, 9),
    uvec4(9, 9, 9, 9),  uvec4(9, 9, 9, 9));

float findParam(uint i0, uint i1) {
    float d = vertValue[i1] - vertValue[i0];
    return d == 0.0 ? 0.5 : -vertValue[i0] / d;
}

void makeVertex(uint i0, uint i1) {
    float param = findParam(i0, i1);
    gl_Position = perspectiveMatrix *
                  mix(gl_in[i0].gl_Position, gl_in[i1].gl_Position, param);

    EmitVertex();
}

void makeSurface(uvec4 vi0, uvec4 vi1, int count) {
    for(int i = 0; i < count; ++i) {
        makeVertex(vi0[i], vi1[i]);
    }
    EndPrimitive();
}

void main() {
    ivec4 mask = ivec4(1);
    ivec4 inside =
      ivec4(vertInside[0], vertInside[1], vertInside[2], vertInside[3]);
    int cutCount = int(dot(inside, mask)) % 4;

    if(cutCount != 0) {
        int configIndex = int(dot(inside, ivec4(16, 8, 4, 2)));
        makeSurface(
          edgeVertices[configIndex + 0],
          edgeVertices[configIndex + 1],
          4 - cutCount % 2);
    }
}
)"};

static const eagine::string_view fs_source{R"(
#version 150

uniform vec3 color;
out vec3 fragColor;

void main() {
    fragColor = color;
}
)"};

static void run_loop(
  eagine::main_ctx& ctx,
  GLFWwindow* window,
  int width,
  int height) {
    using namespace eagine;
    using namespace eagine::oglplus;

    const gl_api glapi{ctx};
    const auto& [gl, GL] = glapi;

    if(gl.clear) {
        gl_debug_logger gdl{ctx, glapi};
        gl.debug_message_control(
          GL.dont_care, GL.dont_care, GL.dont_care, GL.true_);

        memory::buffer temp;
        shape_generator shape(
          glapi,
          shapes::marching_tetrahedrons(shapes::vertex_attrib_kind::box_coord));

        geometry_and_bindings domain{glapi, shape, temp};
        domain.use(glapi);

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        const auto cleanup_prog = gl.delete_program.raii(prog);

        // vertex shader
        owned_shader_name vs;
        gl.create_shader(GL.vertex_shader) >> vs;
        const auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.object_label(vs, "vertex shader");
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);
        gl.attach_shader(prog, vs);

        // geometry shader
        owned_shader_name gs;
        gl.create_shader(GL.geometry_shader) >> gs;
        const auto cleanup_gs = gl.delete_shader.raii(gs);
        gl.object_label(gs, "geometry shader");
        gl.shader_source(gs, glsl_string_ref(gs_source));
        gl.compile_shader(gs);
        gl.attach_shader(prog, gs);

        // fragment shader
        owned_shader_name fs;
        gl.create_shader(GL.fragment_shader) >> fs;
        const auto cleanup_fs = gl.delete_shader.raii(fs);
        gl.object_label(fs, "fragment shader");
        gl.shader_source(fs, glsl_string_ref(fs_source));
        gl.compile_shader(fs);
        gl.attach_shader(prog, fs);

        gl.link_program(prog);
        gl.use_program(prog);
        gl.bind_attrib_location(prog, domain.box_coord_loc(), "Coord");

        // uniform
        const ivec3 grid_dim{24, 16, 24};
        const auto grid_cell_count =
          grid_dim.x() * grid_dim.y() * grid_dim.z() * 8;
        uniform_location grid_dim_loc;
        gl.get_uniform_location(prog, "gridDim") >> grid_dim_loc;
        glapi.set_uniform(prog, grid_dim_loc, grid_dim);

        uniform_location time_loc;
        gl.get_uniform_location(prog, "time") >> time_loc;

        uniform_location color_loc;
        gl.get_uniform_location(prog, "color") >> color_loc;

        uniform_location perspective_matrix_loc;
        gl.get_uniform_location(prog, "perspectiveMatrix") >>
          perspective_matrix_loc;

        uniform_location camera_matrix_loc;
        gl.get_uniform_location(prog, "cameraMatrix") >> camera_matrix_loc;

        orbiting_camera camera;
        camera.set_near(0.1F)
          .set_far(10.F)
          .set_fov(degrees_(50))
          .set_orbit_min(1.0F)
          .set_orbit_max(1.3F);

        gl.clear_color(0.45F, 0.45F, 0.45F, 1.0F);
        gl.clear_depth(1);
        gl.enable(GL.depth_test);
        gl.depth_func(GL.lequal);
        gl.enable(GL.polygon_offset_line);
        gl.polygon_offset(-1.F, -2.F);

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

            const auto aspect = float(width) / float(height);
            camera.set_azimuth(radians_(t * 0.2F))
              .set_elevation(radians_(std::sin(t * 0.1F)))
              .set_orbit_factor(math::sine_wave01(t * 0.05F));

            glapi.set_uniform(prog, time_loc, t);
            glapi.set_uniform(
              prog, perspective_matrix_loc, camera.perspective_matrix(aspect));
            glapi.set_uniform(
              prog, camera_matrix_loc, camera.transform_matrix());

            gl.polygon_mode(GL.front_and_back, GL.fill);
            glapi.set_uniform(prog, color_loc, oglplus::vec3(1.F));
            domain.draw_instanced(glapi, grid_cell_count);

            gl.polygon_mode(GL.front_and_back, GL.line);
            glapi.set_uniform(prog, color_loc, oglplus::vec3(0.F));
            domain.draw_instanced(glapi, grid_cell_count);

            glfwSwapBuffers(window);
            t += 0.02F;
        }
        domain.clean_up(glapi);
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

