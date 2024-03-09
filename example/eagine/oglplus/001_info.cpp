/// @example oglplus/001_info.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import std;
import eagine.core;
import eagine.oglplus;

namespace eagine {

static void run(main_ctx& ctx) {
    using namespace eagine::oglplus;

    const gl_api gl{ctx};
    const main_ctx_object out{"OGLplus", ctx};

    if(const ok info{gl.get_string(gl.vendor)}) {
        out.cio_print("Vendor: ${info}").arg("info", info);
    }

    if(const ok info{gl.get_string(gl.renderer)}) {
        out.cio_print("Renderer: ${info}").arg("info", info);
    }

    if(const ok info{gl.get_string(gl.version)}) {
        out.cio_print("Version: ${info}").arg("info", info);
    }

    if(const ok info{gl.get_integer(gl.major_version)}) {
        out.cio_print("Major version: ${info}").arg("info", info);
    }

    if(const ok info{gl.get_integer(gl.minor_version)}) {
        out.cio_print("Minor version: ${info}").arg("info", info);
    }

    if(const ok info{gl.get_string(gl.shading_language_version)}) {
        out.cio_print("GLSL version: ${info}").arg("info", info);
    }

    const auto ext_cio{out.cio_print("Extensions:").to_be_continued()};

    for(auto name : gl.get_extensions()) {
        ext_cio.print(name);
    }
}

static void init_and_run(main_ctx& ctx) {
    if(not glfwInit()) {
        throw std::runtime_error("GLFW initialization error");
    } else {
        auto ensure_glfw_cleanup = eagine::finally(glfwTerminate);

        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

        int width = 800, height = 600;

        GLFWwindow* window =
          glfwCreateWindow(width, height, "OGLplus example", nullptr, nullptr);

        if(not window) {
            throw std::runtime_error("Error creating GLFW window");
        } else {
            glfwMakeContextCurrent(window);
            glewExperimental = GL_TRUE;
            const GLenum init_result = glewInit();
            glGetError();
            if(init_result != GLEW_OK) {
                throw std::runtime_error("OpenGL/GLEW initialization error.");
            } else {
                run(ctx);
            }
        }
    }
}

auto main(main_ctx& ctx) -> int {
    try {
        init_and_run(ctx);
        return 0;
    } catch(const std::runtime_error& sre) {
        ctx.cio()
          .error("OGLplus", "Runtime error: ${message}")
          .arg("message", sre.what());
    } catch(const std::exception& se) {
        ctx.cio()
          .error("OGLplus", "Unknown error: ${message}")
          .arg("message", se.what());
    }
    return 1;
}
} // namespace eagine

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

