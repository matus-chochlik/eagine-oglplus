/// @example oglplus/011_text_rendering.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.shapes;
import eagine.oglplus;
import <chrono>;
import <iostream>;
import <stdexcept>;

#include <GLFW/glfw3.h>

static void run_loop(
  eagine::main_ctx& ctx,
  GLFWwindow* window,
  int width,
  int height) {
    using namespace eagine;
    using namespace eagine::oglplus;

    const gl_api glapi;
    const auto& [gl, GL] = glapi;

    const bool has_requirements =
      gl.clear && gl.create_paths_nv && gl.delete_paths_nv;

    if(has_requirements) {
        gl_debug_logger gdl{ctx};

        gl.debug_message_callback(gdl);
        gl.debug_message_control(
          GL.dont_care, GL.dont_care, GL.dont_care, GL.true_);

        std::vector<oglplus::gl_types::float_type> glyph_spacings;

        // ascii-7 glyphs
        owned_path_nv_name text_glyphs;
        gl.create_paths_nv(128) >> text_glyphs;
        const auto cleanup_glyphs = gl.delete_paths_nv.raii(text_glyphs, 128);

        const auto font_size = 48.F;
        gl.path_glyph_range_nv(
          text_glyphs,
          GL.standard_font_name_nv,
          "Sans",
          GL.bold_bit_nv,
          0,
          128,
          GL.use_missing_glyph_nv,
          ~oglplus::gl_types::uint_type{0},
          font_size);

        const auto render_text =
          [&](float px, float py, const std::string& text) {
              const auto& [gl_, GL_] = glapi;

              glyph_spacings.resize(std_size(text.size() + 1));
              gl_.get_path_spacing_nv(
                GL_.accum_adjacent_pairs_nv,
                text,
                text_glyphs,
                1.F,
                1.F,
                GL_.translate_x_nv,
                cover(glyph_spacings));
              glyph_spacings.insert(glyph_spacings.begin(), 0.F);

              gl_.load_identity();
              gl_.translate_f(px, py, 0.F);
              gl_.stencil_fill_path_instanced_nv(
                text,
                text_glyphs,
                GL_.count_up_nv,
                0xFFU,
                GL_.translate_x_nv,
                view(glyph_spacings));
              gl_.cover_fill_path_instanced_nv(
                text,
                text_glyphs,
                GL_.bounding_box_of_bounding_boxes_nv,
                GL_.translate_x_nv,
                view(glyph_spacings));
          };

        const oglplus::gl_types::float_type color_gen_coeffs[9] = {
          -0.6F, 0.0F, 0.8F, 0.0F, 0.0F, 0.0F, 0.5F, 0.0F, 0.5F};
        gl.path_color_gen_nv(
          GL.primary_color_nv,
          GL.path_object_bounding_box_nv,
          GL.rgb,
          view(color_gen_coeffs));

        gl.clear_color(1.0F, 1.0F, 1.0F, 1.0F);
        gl.clear_stencil(0);
        gl.stencil_mask(~0U);
        gl.stencil_func(GL.notequal, 0, 0xFFU);
        gl.stencil_op(GL.keep, GL.keep, GL.zero);

        gl.disable(GL.depth_test);
        gl.enable(GL.stencil_test);

        int frame_no = 0;
        const auto start_time = std::chrono::steady_clock::now();

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

            gl.matrix_mode(GL.projection);
            gl.load_identity();
            gl.ortho(0, width, 0, height, 0, 1);

            gl.clear(GL.color_buffer_bit | GL.stencil_buffer_bit);

            gl.matrix_mode(GL.modelview);

            auto text_x = []() {
                return 5.F;
            };
            auto text_y = [font_size, height, line{0}]() mutable {
                return (float(height) - float(++line) * 1.21F * font_size);
            };

            const std::chrono::duration<float> run_time(
              std::chrono::steady_clock::now() - start_time);

            render_text(text_x(), text_y(), "NV_path rendering example");
            render_text(
              text_x(),
              text_y(),
              format("Frame no: ${1}") % std::to_string(frame_no));
            render_text(
              text_x(),
              text_y(),
              format("Run time: ${1} [s]") % std::to_string(run_time.count()));
            render_text(
              text_x(),
              text_y(),
              format("Average FPS: ${1}") %
                std::to_string(float(frame_no) / run_time.count()));
            render_text(
              text_x(),
              text_y(),
              format("Window width: ${1}") % std::to_string(width));
            render_text(
              text_x(),
              text_y(),
              format("Window height: ${1}") % std::to_string(height));
            render_text(
              text_x(),
              text_y(),
              format("Aspect ratio: ${1}") %
                std::to_string(float(width) / float(height)));

            glfwSwapBuffers(window);

            frame_no++;
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
        glfwWindowHint(GLFW_DEPTH_BITS, 0);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, GLFW_DONT_CARE);
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

