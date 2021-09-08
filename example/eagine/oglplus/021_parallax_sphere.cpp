/// @example oglplus/021_parallax_sphere.cpp
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
#include <eagine/oglplus/math/vector.hpp>
#include <eagine/oglplus/shapes/generator.hpp>
#include <eagine/shapes/round_cube.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

static const eagine::string_view vs_source{R"(
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

static const eagine::string_view fs_source{R"(
#version 400
uniform sampler2D normalTex;
uniform sampler2D maskTex;
const float depthMult = 0.15;

in vec3 vertLight;
in vec3 vertNormal;
in vec2 vertTexCoord;
in vec3 vertViewTangent;
in mat3 vertNormalMatrix;

out vec3 fragColor;

vec3 normalAt(vec2 c) {
    vec3 n = 2.0*texture(normalTex, c).xyz-vec3(1.0);
    return vertNormalMatrix * vec3(-n.xy, n.z);
}

float depthAt(vec2 c) {
    return texture(normalTex, c).a * texture(maskTex, c).r;
}

void main() {
    vec3 viewTangent = normalize(vertViewTangent);
    float sampleInterval = 1.0 / length(textureSize(normalTex, 0));
    vec3 sampleStep = viewTangent*sampleInterval;
    float depth = depthAt(vertTexCoord);
    float maxOffs = min((depth * depthMult)/(-viewTangent.z), 1.0);
    vec3 viewOffs = vec3(0.0, 0.0, 0.0);
    vec2 offsTexC = vertTexCoord + viewOffs.xy;
    while(true) {
        if(offsTexC.x <= 0.0 || offsTexC.x >= 1.0) {
            discard;
        }
        if(offsTexC.y <= 0.0 || offsTexC.y >= 1.0) {
            discard;
        }
        if(depth*depthMult <= -viewOffs.z) {
            break;
        }
        viewOffs += sampleStep;
        if(length(viewOffs) >= maxOffs) {
            break;
        }
        offsTexC = vertTexCoord + viewOffs.xy;
        depth = depthAt(offsTexC);
    }
    float emission = max(pow(fract(exp(1.1+depth*3.0)), 4.0), depth*1.2);
    vec3 normal = normalAt(offsTexC);
    float diffuse = max(dot(normalize(vertLight), normalize(normal)), 0.0);
    fragColor = max(
        0.6 * vec3(0.10 + 0.20*diffuse + 0.25*pow(diffuse, 2.0)),
        emission * vec3(1.2, 1.0, 0.6)
    );
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

        memory::buffer buf;

        // vertex shader
        owned_shader_name vs;
        gl.create_shader(GL.vertex_shader) >> vs;
        const auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.shader_source(vs, glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        // fragment shader
        owned_shader_name fs;
        gl.create_shader(GL.fragment_shader) >> fs;
        const auto cleanup_fs = gl.delete_shader.raii(fs);
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

        // geometry
        shape_generator shape(
          glapi,
          shapes::unit_round_cube(
            shapes::vertex_attrib_kind::position |
            shapes::vertex_attrib_kind::normal |
            shapes::vertex_attrib_kind::tangential |
            shapes::vertex_attrib_kind::face_coord));

        std::vector<shape_draw_operation> _ops;
        _ops.resize(std_size(shape.operation_count()));
        shape.instructions(glapi, cover(_ops));

        // vao
        owned_vertex_array_name vao;
        gl.gen_vertex_arrays() >> vao;
        const auto cleanup_vao = gl.delete_vertex_arrays.raii(vao);
        gl.bind_vertex_array(vao);

        // positions
        vertex_attrib_location position_loc{0};
        gl.get_attrib_location(prog, "Position") >> position_loc;
        owned_buffer_name positions;
        gl.gen_buffers() >> positions;
        const auto cleanup_positions = gl.delete_buffers.raii(positions);
        shape.attrib_setup(
          glapi,
          vao,
          positions,
          position_loc,
          shapes::vertex_attrib_kind::position,
          buf);

        // normals
        vertex_attrib_location normal_loc{1};
        gl.get_attrib_location(prog, "Normal") >> normal_loc;
        owned_buffer_name normals;
        gl.gen_buffers() >> normals;
        const auto cleanup_normals = gl.delete_buffers.raii(normals);
        shape.attrib_setup(
          glapi,
          vao,
          normals,
          normal_loc,
          shapes::vertex_attrib_kind::normal,
          buf);

        // tangentials
        vertex_attrib_location tangential_loc{2};
        gl.get_attrib_location(prog, "Tangent") >> tangential_loc;
        owned_buffer_name tangentials;
        gl.gen_buffers() >> tangentials;
        const auto cleanup_tangentials = gl.delete_buffers.raii(tangentials);
        shape.attrib_setup(
          glapi,
          vao,
          tangentials,
          tangential_loc,
          shapes::vertex_attrib_kind::tangential,
          buf);

        // tex coords
        vertex_attrib_location tex_coord_loc{3};
        gl.get_attrib_location(prog, "TexCoord") >> tex_coord_loc;
        owned_buffer_name tex_coords;
        gl.gen_buffers() >> tex_coords;
        const auto cleanup_tex_coords = gl.delete_buffers.raii(tex_coords);
        shape.attrib_setup(
          glapi,
          vao,
          tex_coords,
          tex_coord_loc,
          shapes::vertex_attrib_kind::face_coord,
          buf);

        // indices
        owned_buffer_name indices;
        gl.gen_buffers() >> indices;
        const auto cleanup_indices = gl.delete_buffers.raii(indices);
        shape.index_setup(glapi, indices, buf);

        // normal/height texture
        const auto normal_tex_src{embed(EAGINE_ID(NormalTex), "worley-bump")};

        owned_texture_name normal_tex;
        gl.gen_textures() >> normal_tex;
        const auto cleanup_normal_tex = gl.delete_textures.raii(normal_tex);
        gl.active_texture(GL.texture0);
        gl.bind_texture(GL.texture_2d, normal_tex);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_min_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_mag_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_wrap_s, GL.clamp_to_edge);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_wrap_t, GL.clamp_to_edge);
        glapi.spec_tex_image2d(
          GL.texture_2d,
          0,
          0,
          oglplus::texture_image_block(normal_tex_src.unpack(ctx)));
        oglplus::uniform_location normal_tex_loc;
        gl.get_uniform_location(prog, "normalTex") >> normal_tex_loc;
        glapi.set_uniform(prog, normal_tex_loc, 0);

        // mask texture
        const auto mask_tex_src{embed(EAGINE_ID(MAskTex), "round_rect_mask")};

        owned_texture_name mask_tex;
        gl.gen_textures() >> mask_tex;
        const auto cleanup_mask_tex = gl.delete_textures.raii(mask_tex);
        gl.active_texture(GL.texture0 + 1);
        gl.bind_texture(GL.texture_2d, mask_tex);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_min_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_mag_filter, GL.linear);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_wrap_s, GL.clamp_to_edge);
        gl.tex_parameter_i(GL.texture_2d, GL.texture_wrap_t, GL.clamp_to_edge);
        glapi.spec_tex_image2d(
          GL.texture_2d,
          0,
          0,
          oglplus::texture_image_block(mask_tex_src.unpack(ctx)));
        oglplus::uniform_location mask_tex_loc;
        gl.get_uniform_location(prog, "maskTex") >> mask_tex_loc;
        glapi.set_uniform(prog, mask_tex_loc, 1);

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
            camera.set_azimuth(radians_(t * 0.4F))
              .set_elevation(radians_(std::sin(t * 0.5F)))
              .set_orbit_factor(math::sine_wave01(t * 0.1F));
            glapi.set_uniform(
              prog, perspective_loc, camera.perspective_matrix(aspect));
            glapi.set_uniform(prog, camera_loc, camera.transform_matrix());
            glapi.set_uniform(
              prog, model_loc, matrix_translation(-0.45F, 0.F, 0.F)());
            glapi.set_uniform(
              prog,
              light_pos_loc,
              oglplus::vec3(
                10.0F * cos(degrees_(5.0F * t * 2.718F)),
                10.0F * sin(degrees_(5.0F * t * 2.718F)),
                10.0F * sin(degrees_(5.0F * t * 1.618F))));
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
