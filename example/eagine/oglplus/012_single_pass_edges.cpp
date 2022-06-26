/// @example oglplus/012_single_pass_edges.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/gl_api.hpp>

#include <eagine/main_ctx.hpp>
#include <eagine/math/functions.hpp>
#include <eagine/oglplus/camera.hpp>
#include <eagine/oglplus/gl_debug_logger.hpp>
#include <eagine/oglplus/glsl/string_ref.hpp>
#include <eagine/oglplus/math/matrix.hpp>
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/geometry.hpp>
#include <eagine/shapes/icosahedron.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

static const eagine::string_view vs_source{R"(
#version 150

const vec3 lightPosition = vec3(10.0, 10.0, 7.0);

uniform mat4 perspectiveMatrix, cameraMatrix, modelMatrix;

in vec3 Position;

out vec3 vertNormal;
out vec3 vertLightDir;

void main() {
	gl_Position = modelMatrix * vec4(Position, 1.0);
	vertNormal = mat3(modelMatrix) * Position;
	vertLightDir = lightPosition - gl_Position.xyz;
	gl_Position = perspectiveMatrix * cameraMatrix * gl_Position;
}
)"};

static const eagine::string_view gs_source{R"(
#version 150
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform vec2 viewportDimensions;

in vec3 vertNormal[], vertLightDir[];

noperspective out vec3 geomDist;
flat out vec3 geomNormal;
flat out vec3 geomColor;
out vec3 geomLightDir;

void main() {
	geomNormal = normalize(vertNormal[0] + vertNormal[1] + vertNormal[2]);
	geomColor = normalize(abs(vec3(1.0) - geomNormal ));

	vec2 screenPos[3];
	for(int i = 0; i != 3; ++i) {
		screenPos[i] = viewportDimensions *
			gl_in[i].gl_Position.xy / gl_in[i].gl_Position.w;
	}

	vec2 tmpVect[3];
	for(int i = 0; i != 3; ++i) {
		tmpVect[i] = screenPos[(i + 2) % 3] - screenPos[(i + 1) % 3];
	}

	const vec3 edgeMask[3] = vec3[3](
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0)
	);

	for(int i = 0; i != 3; ++i) {
		float dist = abs(
			tmpVect[(i + 1) % 3].x * tmpVect[(i + 2) % 3].y-
			tmpVect[(i + 1) % 3].y * tmpVect[(i + 2) % 3].x
		) / length(tmpVect[i]);
		vec3 distVect = vec3(dist);

		gl_Position = gl_in[i].gl_Position;
		geomLightDir = vertLightDir[i];
		geomDist = edgeMask[i] * distVect;
		EmitVertex();
	}
	EndPrimitive();
}
)"};

static const eagine::string_view fs_source{R"(
#version 150

const float edgeWidth = 3.0;

noperspective in vec3 geomDist;
flat in vec3 geomNormal;
flat in vec3 geomColor;
in vec3 geomLightDir;

out vec3 fragColor;

void main() {
	float minDist = min(min(geomDist.x,geomDist.y),geomDist.z);
	float edgeAlpha = exp2(-pow(minDist/edgeWidth, 2.0));

	const float ambient = 0.7;
	float lightDot = dot(normalize(geomNormal), normalize(geomLightDir));
	float diffuse = max(lightDot, 0.0);
	float specular = pow(max(lightDot, 0.0), 4.0);

	vec3 faceColor = geomColor * (diffuse + ambient) + vec3(0.2) * specular;
	const vec3 edgeColor = vec3(0.0);

	fragColor = mix(faceColor, edgeColor, edgeAlpha);
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
        shape_generator shape(
          glapi,
          shapes::unit_icosahedron(shapes::vertex_attrib_kind::position));

        geometry_and_bindings icosahedron{glapi, shape, temp};
        icosahedron.use(glapi);

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
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, gs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);

        gl.bind_attrib_location(prog, icosahedron.position_loc(), "Position");

        // uniform
        uniform_location viewport_dimensions_loc;
        gl.get_uniform_location(prog, "viewportDimensions") >>
          viewport_dimensions_loc;

        uniform_location perspective_matrix_loc;
        gl.get_uniform_location(prog, "perspectiveMatrix") >>
          perspective_matrix_loc;

        uniform_location camera_matrix_loc;
        gl.get_uniform_location(prog, "cameraMatrix") >> camera_matrix_loc;

        uniform_location model_matrix_loc;
        gl.get_uniform_location(prog, "modelMatrix") >> model_matrix_loc;

        orbiting_camera camera;
        camera.set_near(0.1F)
          .set_far(50.F)
          .set_fov(right_angle_())
          .set_orbit_min(2.F)
          .set_orbit_max(3.F);

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
            if((width != new_width) || (height != new_height)) {
                width = new_width;
                height = new_height;
            }

            gl.viewport(width, height);

            gl.clear(GL.color_buffer_bit | GL.depth_buffer_bit);

            const auto aspect = float(width) / float(height);
            camera.set_azimuth(radians_(t))
              .set_elevation(radians_(std::sin(t)))
              .set_orbit_factor(math::sine_wave01(t * 0.1F));

            glapi.set_uniform(
              prog, viewport_dimensions_loc, oglplus::vec2(width, height));
            glapi.set_uniform(
              prog, perspective_matrix_loc, camera.perspective_matrix(aspect));
            glapi.set_uniform(
              prog, camera_matrix_loc, camera.transform_matrix());
            glapi.set_uniform(
              prog,
              model_matrix_loc,
              oglplus::matrix_rotation_x(right_angles_(t))());

            icosahedron.draw(glapi);

            glfwSwapBuffers(window);
            t += 0.02F;
        }
        icosahedron.clean_up(glapi);
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

