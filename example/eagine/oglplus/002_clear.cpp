/// @example oglplus/002_clear.cpp
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

static void run_loop(GLFWwindow* window, int width, int height) {
    using namespace eagine::oglplus;

    const gl_api gl;

    if(gl.operations().clear) {

        gl.clear_color(0.3F, 0.3F, 0.9F, 0.0F);
        gl.clear_depth(1);

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

            gl().clear(gl.color_buffer_bit | gl.depth_buffer_bit);

            glfwSwapBuffers(window);
        }
    } else {
        std::cout << "missing required API" << std::endl;
    }
}

static void init_and_run() {
    if(not glfwInit()) {
        throw std::runtime_error("GLFW initialization error");
    } else {
        const auto ensure_glfw_cleanup = eagine::finally(glfwTerminate);

        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        int width = 800, height = 600;

        GLFWwindow* window =
          glfwCreateWindow(width, height, "OGLplus example", nullptr, nullptr);

        if(not window) {
            throw std::runtime_error("Error creating GLFW window");
        } else {
            glfwMakeContextCurrent(window);
            const eagine::oglplus::api_initializer gl_api_init;
            glGetError();
            run_loop(window, width, height);
        }
    }
}

auto main() -> int {
    try {
        init_and_run();
        return 0;
    } catch(const std::runtime_error& sre) {
        std::cerr << "Runtime error: " << sre.what() << std::endl;
    } catch(const std::exception& se) {
        std::cerr << "Unknown error: " << se.what() << std::endl;
    }
    return 1;
}
