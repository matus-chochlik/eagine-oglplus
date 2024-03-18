/// @example oglplus/018_tessellation.cpp
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

static const eagine::oglplus::glsl_string_ref vs_source{R"(
#version 400

uniform vec3 viewPosition;

in vec3 Position;

out vec3 vertPosition;
out float vertDistance;

void main() {
	vertPosition = Position;
	vertDistance = length(viewPosition - vertPosition);
}
)"};

static const eagine::oglplus::glsl_source_ref cs_source{R"(
#version 400

layout(vertices = 3) out;

in vec3 vertPosition[];
in float vertDistance[];

out vec3 tecoPosition[];

int tessLevel(float dist) {
	return int(9.0 / sqrt(dist+0.1));
}

void main() {
	tecoPosition[gl_InvocationID] = vertPosition[gl_InvocationID];

	if(gl_InvocationID == 0) {
		gl_TessLevelInner[0] = tessLevel(
			(vertDistance[0] + vertDistance[1] + vertDistance[2]) * 0.333);
		gl_TessLevelOuter[0] = tessLevel(
			(vertDistance[1] + vertDistance[2]) * 0.5);
		gl_TessLevelOuter[1] = tessLevel(
			(vertDistance[2] + vertDistance[0]) * 0.5);
		gl_TessLevelOuter[2] = tessLevel(
			(vertDistance[0] + vertDistance[1]) * 0.5);
        }
}
)"};

static const eagine::oglplus::glsl_source_ref es_source{R"(
#version 400

layout(triangles, equal_spacing, ccw) in;

const vec3 lightPosition = vec3(12.0, 10.0, 7.0);

uniform mat4 perspectiveMatrix, cameraMatrix, modelMatrix;

in vec3 tecoPosition[];

out vec3 teevNormal;
out vec3 teevLightDir;

void main() {
	vec3 p0 = gl_TessCoord.x * tecoPosition[0];
   	vec3 p1 = gl_TessCoord.y * tecoPosition[1];
   	vec3 p2 = gl_TessCoord.z * tecoPosition[2];

   	vec4 tempPosition = vec4(normalize(p0+p1+p2), 0.0);
   	teevNormal = mat3(modelMatrix) * tempPosition.xyz;
   	tempPosition.w = 1.0;
   	tempPosition = modelMatrix * tempPosition;
   	teevLightDir = lightPosition - tempPosition.xyz;
   	gl_Position = perspectiveMatrix * cameraMatrix * tempPosition;
}
)"};

static const eagine::oglplus::glsl_source_ref gs_source{R"(
#version 400
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform vec2 viewportDimensions;

in vec3 teevNormal[], teevLightDir[];

noperspective out vec3 geomDist;
flat out vec3 geomNormal;
flat out vec3 geomColor;
out vec3 geomLightDir;

void main() {
	geomNormal = normalize(teevNormal[0] + teevNormal[1] + teevNormal[2]);
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
		geomLightDir = teevLightDir[i];
		geomDist = edgeMask[i] * distVect;
		EmitVertex();
	}
	EndPrimitive();
}
)"};

static const eagine::oglplus::glsl_source_ref fs_source{R"(
#version 400

const float edgeWidth = 2.0;

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

    const gl_api glapi{ctx};
    const auto& [gl, GL] = glapi;

    if(gl.clear) {
        gl_debug_logger gdl{ctx, glapi};
        gl.debug_message_control(
          GL.dont_care, GL.dont_care, GL.dont_care, GL.true_);

        // geometry
        memory::buffer temp;
        shape_generator shape(
          glapi,
          shapes::to_patches(
            shapes::unit_icosahedron(shapes::vertex_attrib_kind::position)));
        geometry_and_bindings icosahedron{glapi, shape, temp};
        icosahedron.use(glapi);

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        const auto cleanup_prog = gl.delete_program.raii(prog);
        glapi.add_shader(prog, GL.vertex_shader, vs_source);
        glapi.add_shader(prog, GL.tess_control_shader, cs_source);
        glapi.add_shader(prog, GL.tess_evaluation_shader, es_source);
        glapi.add_shader(prog, GL.geometry_shader, gs_source);
        glapi.add_shader(prog, GL.fragment_shader, fs_source);
        gl.link_program(prog);
        gl.use_program(prog);

        gl.bind_attrib_location(prog, icosahedron.position_loc(), "Position");

        // uniforms
        uniform_location view_position_loc;
        gl.get_uniform_location(prog, "viewPosition") >> view_position_loc;

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
          .set_fov(degrees_(65))
          .set_orbit_min(0.75F)
          .set_orbit_max(6.0F);

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

            const auto aspect = float(width) / float(height);
            camera.set_azimuth(radians_(t))
              .set_elevation(radians_(std::sin(t)))
              .set_orbit_factor(math::sine_wave01(t * 0.1F));

            glapi.set_uniform(
              prog, viewport_dimensions_loc, oglplus::vec2(width, height));
            glapi.set_uniform(prog, view_position_loc, camera.position());
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
            t += 0.01F;
        }
        icosahedron.clean_up(glapi);
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

