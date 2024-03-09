/// @example oglplus/023_octree.cpp
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

//------------------------------------------------------------------------------
class sort_program {
public:
    sort_program(const eagine::oglplus::gl_api& glapi) {
        using namespace eagine;

        const auto& [gl, GL] = glapi;

        static const string_view vs_source{R"(
            #version 150
            in vec4 PosAndSize;
            void main() {
                gl_Position = PosAndSize;
            }
        )"};
        oglplus::owned_shader_name vs;
        gl.create_shader(GL.vertex_shader) >> vs;
        const auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.object_label(vs, "sort vertex shader");
        gl.shader_source(vs, oglplus::glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        static const string_view gs_source{R"(
            #version 150
            layout (points) in;
            layout (points, max_vertices=8) out;

            uniform mat4 perspectiveMatrix, cameraMatrix;
            mat4 matrix = perspectiveMatrix*cameraMatrix;

            out vec4 xfbPosAndSize;

            int index[8] = int[8](0,1,2,3,4,5,6,7);

            const vec3 offset[8] = vec3[8](
                vec3(-0.5,-0.5,-0.5),
                vec3(+0.5,-0.5,-0.5),
                vec3(-0.5,+0.5,-0.5),
                vec3(+0.5,+0.5,-0.5),
                vec3(-0.5,-0.5,+0.5),
                vec3(+0.5,-0.5,+0.5),
                vec3(-0.5,+0.5,+0.5),
                vec3(+0.5,+0.5,+0.5) 
            );

            vec4 child[8], childVS[8];

            void makeChild(int i) {
                vec4 node = gl_in[0].gl_Position;
                child[i] = vec4(node.xyz+node.w*offset[i], node.w*0.5);
                childVS[i] = matrix*vec4(child[i].xyz, 1.0);
            }

            ivec2 sortingNW8[19] = ivec2[19](
                ivec2(0,7), ivec2(1,6), ivec2(2,5), ivec2(3,4),
                ivec2(0,3), ivec2(4,7), ivec2(1,2), ivec2(5,6),
                ivec2(0,1), ivec2(2,3), ivec2(4,5), ivec2(6,7),
                ivec2(2,4), ivec2(3,5),
                ivec2(1,2), ivec2(3,4), ivec2(5,6),
                ivec2(2,3), ivec2(4,5)
            );

            void sortSwapIdx(ivec2 pair) {
                float zx = childVS[index[pair.x]].z;
                float zy = childVS[index[pair.y]].z;
                if(zx < zy) {
                    int tmp = index[pair.y];
                    index[pair.y] = index[pair.x];
                    index[pair.x] = tmp;
                }
            }

            void main() {
                for(int c=0; c!=8; ++c) {
                    makeChild(c);
                }

                for(int s=0; s!=19; ++s) {
                    sortSwapIdx(sortingNW8[s]);
                }

                for(int c=0; c!=8; ++c) {
                    xfbPosAndSize = child[index[c]];
                    EmitVertex();
                    EndPrimitive();
                }
            }
        )"};
        oglplus::owned_shader_name gs;
        gl.create_shader(GL.geometry_shader) >> gs;
        const auto cleanup_gs = gl.delete_shader.raii(gs);
        gl.object_label(gs, "sort geometry shader");
        gl.shader_source(gs, oglplus::glsl_string_ref(gs_source));
        gl.compile_shader(gs);

        gl.create_program() >> prog;
        gl.object_label(prog, "sort program");
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, gs);
        gl.transform_feedback_varyings(
          prog, "xfbPosAndSize", GL.separate_attribs);
        gl.link_program(prog);
        gl.use_program(prog);

        gl.get_attrib_location(prog, "PosAndSize") >> pos_and_size_loc;
        gl.get_uniform_location(prog, "perspectiveMatrix") >> perspective_loc;
        gl.get_uniform_location(prog, "cameraMatrix") >> camera_loc;
    }

    void cleanup(const eagine::oglplus::gl_api& gl) {
        gl.delete_program(std::move(prog));
    }

    eagine::oglplus::owned_program_name prog;
    eagine::oglplus::vertex_attrib_location pos_and_size_loc;
    eagine::oglplus::uniform_location perspective_loc;
    eagine::oglplus::uniform_location camera_loc;
};
//------------------------------------------------------------------------------
class draw_program {
public:
    draw_program(const eagine::oglplus::gl_api& glapi) {
        using namespace eagine;

        const auto& [gl, GL] = glapi;

        static const string_view vs_source{R"(
            #version 150
            uniform mat4 perspectiveMatrix, cameraMatrix;
            mat4 matrix = perspectiveMatrix*cameraMatrix;
            in vec4 PosAndSize;
            out vec3 vertColor;
            void main() {
                gl_Position = matrix * vec4(PosAndSize.xyz, 1.0);
                gl_PointSize = 25.0 * gl_Position.w / gl_Position.z;
                vertColor = normalize(vec3(1.0) - normalize(PosAndSize.xyz));
            }
        )"};
        oglplus::owned_shader_name vs;
        gl.create_shader(GL.vertex_shader) >> vs;
        const auto cleanup_vs = gl.delete_shader.raii(vs);
        gl.object_label(vs, "draw vertex shader");
        gl.shader_source(vs, oglplus::glsl_string_ref(vs_source));
        gl.compile_shader(vs);

        static const string_view fs_source{R"(
            #version 150
            in vec3 vertColor;
            out vec4 fragColor;
            void main() {
                fragColor = vec4(vertColor, 0.02);
            }
        )"};
        oglplus::owned_shader_name fs;
        gl.create_shader(GL.fragment_shader) >> fs;
        const auto cleanup_fs = gl.delete_shader.raii(fs);
        gl.object_label(fs, "draw fragment shader");
        gl.shader_source(fs, oglplus::glsl_string_ref(fs_source));
        gl.compile_shader(fs);

        gl.create_program() >> prog;
        gl.object_label(prog, "draw program shader");
        gl.attach_shader(prog, vs);
        gl.attach_shader(prog, fs);
        gl.link_program(prog);
        gl.use_program(prog);

        gl.get_attrib_location(prog, "PosAndSize") >> pos_and_size_loc;
        gl.get_uniform_location(prog, "perspectiveMatrix") >> perspective_loc;
        gl.get_uniform_location(prog, "cameraMatrix") >> camera_loc;
    }

    void cleanup(const eagine::oglplus::gl_api& gl) {
        gl.delete_program(std::move(prog));
    }

    eagine::oglplus::owned_program_name prog;
    eagine::oglplus::vertex_attrib_location pos_and_size_loc;
    eagine::oglplus::uniform_location perspective_loc;
    eagine::oglplus::uniform_location camera_loc;
};
//------------------------------------------------------------------------------
class octree_sorter {
    static constexpr const std::size_t levels = 6U;

public:
    octree_sorter(const eagine::oglplus::gl_api& glapi, float node_size)
      : sort_prog{glapi}
      , draw_prog{glapi} {
        using namespace eagine;

        const auto& [gl, GL] = glapi;

        std::vector<float> node_data;
        gl.gen_buffers(pos_and_size.raw_handles());
        gl.gen_vertex_arrays(vao.raw_handles());
        gl.gen_transform_feedbacks(xfb.raw_handles());

        for(const auto l : index_range(node_count)) {
            const auto ls = signedness_cast(l);
            node_count[l] = 1;
            for([[maybe_unused]] const auto p : integer_range(l)) {
                node_count[l] *= 8;
            }

            gl.bind_vertex_array(vao[ls]);
            gl.bind_buffer(GL.array_buffer, pos_and_size[ls]);

            if(l == 0) {
                const auto root_data =
                  GL.float_.array(0.F, 0.F, 0.F, node_size);
                gl.buffer_data(
                  GL.array_buffer, view(root_data), GL.static_draw);
            } else {
                node_data.resize(signedness_cast(node_count[l] * 4), 0.F);
                gl.buffer_data(
                  GL.array_buffer, view(node_data), GL.static_draw);
            }

            const auto pos_and_size_loc = (l + 1 == levels)
                                            ? draw_prog.pos_and_size_loc
                                            : sort_prog.pos_and_size_loc;

            gl.vertex_attrib_pointer(pos_and_size_loc, 4, GL.float_, GL.false_);
            gl.enable_vertex_attrib_array(pos_and_size_loc);
            gl.bind_vertex_array(oglplus::no_vertex_array);

            if(l != 0) {
                gl.bind_transform_feedback(GL.transform_feedback, xfb[ls - 1]);
                gl.bind_buffer(GL.transform_feedback_buffer, pos_and_size[ls]);
                gl.bind_buffer_base(
                  GL.transform_feedback_buffer, 0, pos_and_size[ls]);
                gl.bind_transform_feedback(
                  GL.transform_feedback, oglplus::default_transform_feedback);
            }
        }
    }

    void sort(const eagine::oglplus::gl_api& glapi) {
        using namespace eagine;

        const auto& [gl, GL] = glapi;

        gl.enable(GL.rasterizer_discard);
        for(const auto l : integer_range(levels - 1)) {
            const auto ls = signedness_cast(l);

            gl.bind_vertex_array(vao[ls]);
            gl.bind_transform_feedback(GL.transform_feedback, xfb[ls]);
            gl.begin_transform_feedback(GL.points);
            gl.draw_arrays(GL.points, 0, node_count[l]);
            gl.end_transform_feedback();
        }
        gl.disable(GL.rasterizer_discard);
    }

    void draw(const eagine::oglplus::gl_api& glapi) {
        const auto& [gl, GL] = glapi;
        gl.bind_vertex_array(vao.back());
        gl.draw_arrays(GL.points, 0, node_count.back());
    }

    void cleanup(const eagine::oglplus::gl_api& gl) {
        draw_prog.cleanup(gl);
        sort_prog.cleanup(gl);
        gl.delete_transform_feedbacks(xfb.raw_handles());
        gl.delete_vertex_arrays(vao.raw_handles());
        gl.delete_buffers(pos_and_size.raw_handles());
    }

    sort_program sort_prog;
    draw_program draw_prog;

private:
    std::array<int, levels> node_count{};
    eagine::oglplus::buffer_name_array<levels> pos_and_size{};
    eagine::oglplus::vertex_array_name_array<levels> vao{};
    eagine::oglplus::transform_feedback_name_array<levels - 1U> xfb{};
};
//------------------------------------------------------------------------------
class octree_example {
public:
    octree_example(const eagine::oglplus::gl_api& glapi)
      : _sorter{glapi, 3.F} {
        using namespace eagine;

        const auto& [gl, GL] = glapi;

        gl.clear_color(0.2F, 0.2F, 0.2F, 1.F);
        gl.disable(GL.depth_test);
        gl.enable(GL.program_point_size);
        gl.enable(GL.blend);
        gl.blend_func(GL.src_alpha, GL.one_minus_src_alpha);

        _camera.set_near(0.1F)
          .set_far(50.F)
          .set_fov(degrees_(60))
          .set_orbit_min(8.F)
          .set_orbit_max(9.F);
    }

    void cleanup(const eagine::oglplus::gl_api& glapi) {
        _sorter.cleanup(glapi);
    }

    void reshape(
      const eagine::oglplus::gl_api& glapi,
      const int width,
      const int height) {
        const auto& [gl, GL] = glapi;

        gl.viewport(width, height);

        const auto perspective =
          _camera.perspective_matrix(float(width) / float(height));

        gl.use_program(_sorter.sort_prog.prog);
        glapi.set_uniform(
          _sorter.sort_prog.prog,
          _sorter.sort_prog.perspective_loc,
          perspective);

        gl.use_program(_sorter.draw_prog.prog);
        glapi.set_uniform(
          _sorter.draw_prog.prog,
          _sorter.draw_prog.perspective_loc,
          perspective);
    }

    void render(const eagine::oglplus::gl_api& glapi, const float t) {
        using namespace eagine;

        const auto& [gl, GL] = glapi;

        _camera.set_azimuth(radians_(t * 0.4F))
          .set_elevation(radians_(std::sin(t * 0.5F)))
          .set_orbit_factor(math::sine_wave01(t * 0.1F));

        const auto camera_mat = _camera.transform_matrix();

        gl.clear(GL.color_buffer_bit);

        gl.use_program(_sorter.sort_prog.prog);
        glapi.set_uniform(
          _sorter.sort_prog.prog, _sorter.sort_prog.camera_loc, camera_mat);

        _sorter.sort(glapi);

        gl.use_program(_sorter.draw_prog.prog);
        glapi.set_uniform(
          _sorter.draw_prog.prog, _sorter.draw_prog.camera_loc, camera_mat);

        _sorter.draw(glapi);
    }

private:
    eagine::oglplus::orbiting_camera _camera;
    octree_sorter _sorter;
};
//------------------------------------------------------------------------------
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

        octree_example example{glapi};
        const auto cleanup_example = finally([&]() { example.cleanup(glapi); });

        example.reshape(glapi, width, height);

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
                example.reshape(glapi, width, height);
            }

            example.render(glapi, t);

            glfwSwapBuffers(window);
            t += 0.02F;
        }
    } else {
        std::cout << "missing required API" << std::endl;
    }
}
//------------------------------------------------------------------------------
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
        glfwWindowHint(GLFW_DEPTH_BITS, 0);
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

