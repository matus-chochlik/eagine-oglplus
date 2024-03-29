/// @example oglplus/025_parallax_cube.cpp
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

static const eagine::oglplus::glsl_source_ref vs_source{R"(
#version 400
uniform mat4 perspective, camera, model;
uniform vec3 lightPos;

in vec4 Position;
in vec3 Normal;
in vec3 Tangent;
in vec2 TexCoord;

out vec3 vertLight;
out vec3 vertNormal;
out vec2 vertTexCoord;
out vec3 vertViewTangent;
out mat3 vertNormalMatrix;

void main() {
	mat4 modelview = camera * model;
	vec4 eyePos = modelview * Position;
	vec3 vertEye = eyePos.xyz;
	vec3 fragTangent = mat3(modelview) * Tangent;
	vertNormal = mat3(modelview) * Normal;
	vertLight = lightPos - (model * Position).xyz;
	vertNormalMatrix = mat3(fragTangent, cross(vertNormal, fragTangent), vertNormal);
	vertViewTangent = vec3(
		dot(vertNormalMatrix[0], vertEye),
		dot(vertNormalMatrix[1], vertEye),
		dot(vertNormalMatrix[2], vertEye)
	);
	vertTexCoord = TexCoord;
	gl_Position = perspective * eyePos;
}
)"};

static const eagine::oglplus::glsl_source_ref fs_source{R"(
#version 400
uniform sampler2D colorTex;
uniform sampler2D normalTex;
uniform sampler2D offsetTex;
const float offsetMult = 0.12;

in vec3 vertLight;
in vec3 vertNormal;
in vec2 vertTexCoord;
in vec3 vertViewTangent;
in mat3 vertNormalMatrix;

out vec3 fragColor;

vec3 colorAt(vec2 c) {
	return texture(colorTex, c).xyz;
}

vec3 normalAt(vec2 c) {
	vec3 n = 2.0*texture(normalTex, c).xyz-vec3(1.0);
	return vertNormalMatrix * vec3(-n.xy, n.z);
}

float offsetAt(vec2 c) {
	return sqrt(1.0 - texture(offsetTex, c).r);
}

void main() {
	vec3 viewTangent = normalize(vertViewTangent);
	float sampleInterval = 1.0 / length(textureSize(offsetTex, 0));
	vec3 sampleStep = viewTangent*sampleInterval;
	float offset = offsetAt(vertTexCoord);
	float maxOffs = min((offset * offsetMult)/(-viewTangent.z), 1.0);
	vec3 viewOffs = vec3(0.0, 0.0, 0.0);
	vec2 offsTexC = vertTexCoord + viewOffs.xy;
	while(length(viewOffs) < maxOffs)
	{
		if(offsTexC.x <= 0.0 or offsTexC.x >= 1.0) {
			discard;
		}
		if(offsTexC.y <= 0.0 or offsTexC.y >= 1.0) {
			discard;
		}
		if(offset*offsetMult <= -viewOffs.z) {
			break;
		}
		viewOffs += sampleStep;
		offsTexC = vertTexCoord + viewOffs.xy;
		offset = offsetAt(offsTexC);
	}
	vec3 color = colorAt(offsTexC);
	vec3 normal = normalAt(offsTexC);
	float diffuse = dot(normalize(vertLight), normalize(normal));
	float light = 0.45 + 1.6*max(diffuse, 0.0);
	fragColor = color*light;
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

        memory::buffer buf;

        // program
        owned_program_name prog;
        gl.create_program() >> prog;
        const auto cleanup_prog = gl.delete_program.raii(prog);
        glapi.add_shader(prog, GL.vertex_shader, vs_source);
        glapi.add_shader(prog, GL.fragment_shader, fs_source);
        gl.link_program(prog);
        gl.use_program(prog);

        // geometry
        memory::buffer temp;
        shape_generator shape(
          glapi,
          shapes::unit_cube(
            shapes::vertex_attrib_kind::position |
            shapes::vertex_attrib_kind::normal |
            shapes::vertex_attrib_kind::tangent |
            shapes::vertex_attrib_kind::face_coord));
        geometry_and_bindings cube{glapi, shape, temp};
        cube.use(glapi);

        gl.bind_attrib_location(prog, cube.position_loc(), "Position");
        gl.bind_attrib_location(prog, cube.normal_loc(), "Normal");
        gl.bind_attrib_location(prog, cube.tangent_loc(), "Tangent");
        gl.bind_attrib_location(prog, cube.wrap_coord_loc(), "TexCoord");

        // color texture
        owned_texture_name color_tex;
        gl.gen_textures() >> color_tex;
        const auto cleanup_color_tex = gl.delete_textures.raii(color_tex);
        gl.active_texture(GL.texture0 + 0);
        gl.bind_texture(GL.texture_2d, color_tex);
        build_from_resource(
          ctx, glapi, search_resource("CrateDiff"), color_tex, GL.texture_2d);

        uniform_location color_tex_loc;
        gl.get_uniform_location(prog, "colorTex") >> color_tex_loc;
        glapi.set_uniform(prog, color_tex_loc, 0);

        // normal texture
        owned_texture_name normal_tex;
        gl.gen_textures() >> normal_tex;
        const auto cleanup_normal_tex = gl.delete_textures.raii(normal_tex);
        gl.active_texture(GL.texture0 + 1);
        gl.bind_texture(GL.texture_2d, normal_tex);
        build_from_resource(
          ctx, glapi, search_resource("CrateNMap"), normal_tex, GL.texture_2d);

        uniform_location normal_tex_loc;
        gl.get_uniform_location(prog, "normalTex") >> normal_tex_loc;
        glapi.set_uniform(prog, normal_tex_loc, 1);

        // offset texture
        owned_texture_name offset_tex;
        gl.gen_textures() >> offset_tex;
        const auto cleanup_offset_tex = gl.delete_textures.raii(offset_tex);
        gl.active_texture(GL.texture0 + 2);
        gl.bind_texture(GL.texture_2d, offset_tex);
        build_from_resource(
          ctx, glapi, search_resource("CrateHMap"), offset_tex, GL.texture_2d);

        uniform_location offset_tex_loc;
        gl.get_uniform_location(prog, "offsetTex") >> offset_tex_loc;
        glapi.set_uniform(prog, offset_tex_loc, 2);

        // uniforms
        uniform_location perspective_loc;
        gl.get_uniform_location(prog, "perspective") >> perspective_loc;

        uniform_location camera_loc;
        gl.get_uniform_location(prog, "camera") >> camera_loc;

        uniform_location model_loc;
        gl.get_uniform_location(prog, "model") >> model_loc;

        uniform_location light_pos_loc;
        gl.get_uniform_location(prog, "lightPos") >> light_pos_loc;

        orbiting_camera camera;
        camera.set_near(0.1F)
          .set_far(50.F)
          .set_fov(degrees_(60))
          .set_orbit_min(1.8F)
          .set_orbit_max(2.0F);

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
            camera.set_azimuth(radians_(t * 0.4F))
              .set_elevation(radians_(std::sin(t * 0.5F)))
              .set_orbit_factor(math::sine_wave01(t * 0.1F));
            glapi.set_uniform(
              prog, perspective_loc, camera.perspective_matrix(aspect));
            glapi.set_uniform(prog, camera_loc, camera.transform_matrix());
            glapi.set_uniform(
              prog, model_loc, matrix_rotation_x(right_angles_(t * 0.05))());
            glapi.set_uniform(
              prog,
              light_pos_loc,
              oglplus::vec3(
                10.0F * cos(degrees_(5.0F * t * 2.718F)),
                10.0F * sin(degrees_(5.0F * t * 2.718F)),
                10.0F * sin(degrees_(5.0F * t * 1.618F))));
            cube.draw(glapi);

            glfwSwapBuffers(window);
        }
        cube.clean_up(glapi);
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

