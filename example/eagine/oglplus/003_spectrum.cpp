/// @example oglplus/003_spectrum.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <GLFW/glfw3.h>

import std;
import eagine.core;
import eagine.oglplus;

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

        gl.disable(GL.depth_test);
        gl.clear_color(math::string_to_rgba("Gray", 1.F).or_default());

        float time = 0.F;

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

            const auto h = GL.double_(2);
            const auto w = h * GL.double_(width) / GL.double_(height);

            gl.matrix_mode(GL.projection);
            gl.load_identity();
            gl.ortho(-w, +w, -h, +h, 0, 1);

            gl.clear(GL.color_buffer_bit);

            gl.matrix_mode(GL.modelview);
            gl.load_identity();
            gl.rotate_f(degrees_(time * 90), 0, 0, 1);

            gl.begin(GL.triangle_fan);

            gl.color3f(0.5F, 0.5F, 0.5F);
            gl.vertex2f(0.000F, 0.000F);

            gl.color3f(1.0F, 0.0F, 0.0F);
            gl.vertex2f(0.000F, 1.000F);

            gl.color3f(1.0F, 0.7F, 0.0F);
            gl.vertex2f(0.707F, 0.707F);

            gl.color3f(0.7F, 1.0F, 0.0F);
            gl.vertex2f(1.000F, 0.000F);

            gl.color3f(0.0F, 1.0F, 0.0F);
            gl.vertex2f(0.707F, -0.707F);

            gl.color3f(0.0F, 1.0F, 0.7F);
            gl.vertex2f(0.000F, -1.000F);

            gl.color3f(0.0F, 0.7F, 1.0F);
            gl.vertex2f(-0.707F, -0.707F);

            gl.color3f(0.0F, 0.0F, 1.0F);
            gl.vertex2f(-1.000F, 0.000F);

            gl.color3f(0.7F, 0.0F, 0.7F);
            gl.vertex2f(-0.707F, 0.707F);

            gl.color3f(1.0F, 0.0F, 0.0F);
            gl.vertex2f(0.000F, 1.000F);

            gl.end();

            gl.begin(GL.line_loop);

            gl.color3f(0.F, 0.F, 0.F);

            gl.vertex2f(0.000F, 1.000F);
            gl.vertex2f(0.707F, 0.707F);
            gl.vertex2f(1.000F, 0.000F);
            gl.vertex2f(0.707F, -0.707F);
            gl.vertex2f(0.000F, -1.000F);
            gl.vertex2f(-0.707F, -0.707F);
            gl.vertex2f(-1.000F, 0.000F);
            gl.vertex2f(-0.707F, 0.707F);
            gl.vertex2f(0.000F, 1.000F);

            gl.end();

            glfwSwapBuffers(window);

            time += 0.01F;
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
        glfwWindowHint(GLFW_DEPTH_BITS, 0);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, GLFW_DONT_CARE);
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

