/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#if EAGINE_OGLPLUS_MODULE
import eagine.core;
import eagine.oglplus;
import <fstream>;
import <iostream>;
#else
#include <eagine/main_ctx.hpp>
#include <eagine/main_fwd.hpp>
#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/utils/image_file_io.hpp>
#include <eagine/program_args.hpp>
#include <eagine/valid_if/filesystem.hpp>
#include <eagine/valid_if/positive.hpp>
#include <fstream>
#endif

#ifndef GL_RGB
#define GL_RGB 0x1907
#endif
#ifndef GL_R3_G3_B2
#define GL_R3_G3_B2 0x2A10
#endif
#ifndef GL_UNSIGNED_BYTE_3_3_2
#define GL_UNSIGNED_BYTE_3_3_2 0x8032
#endif

namespace eagine {
//------------------------------------------------------------------------------
struct options {
    valid_if_in_writable_directory<string_view> output_path{"a.oglptex"};
    valid_if_positive<int> components{1};
    valid_if_positive<int> width{256};
    valid_if_positive<int> height{256};
    valid_if_positive<int> depth{1};
    valid_if_positive<int> rep_x{8};
    valid_if_positive<int> rep_y{8};
    valid_if_positive<int> rep_z{1};
    int verbosity{0};

    void print_usage(std::ostream& log) {
        log << "bake_noise_image options" << std::endl;
        log << "  options:" << std::endl;
        log << "   -o|--output PATH: Output file path "
               "or '-' for stdout."
            << std::endl;
        log << "   -w|--width N: Output image width." << std::endl;
        log << "   -h|--height N: Output image height." << std::endl;
        log << "   -d|--depth N: Output image depth." << std::endl;
        log << "   -x|--x-repeat N: X-repeats." << std::endl;
        log << "   -y|--y-repeat N: Y-repeats." << std::endl;
        log << "   -z|--z-repeat N: Z-repeats." << std::endl;
    }

    auto parse(program_arg& a, std::ostream& log) -> bool {
        if(a.is_tag("-o", "--output")) {
            if(!a.parse_next(output_path, log)) {
                return false;
            }
        } else if(a.is_tag("-w", "--width")) {
            if(!a.parse_next(width, log)) {
                return false;
            }
        } else if(a.is_tag("-h", "--height")) {
            if(!a.parse_next(height, log)) {
                return false;
            }
        } else if(a.is_tag("-d", "--depth")) {
            if(!a.parse_next(depth, log)) {
                return false;
            }
        } else if(a.is_tag("-x", "--x_repeats")) {
            if(!a.parse_next(width, log)) {
                return false;
            }
        } else if(a.is_tag("-y", "--y-repeats")) {
            if(!a.parse_next(height, log)) {
                return false;
            }
        } else if(a.is_tag("-z", "--z-repeats")) {
            if(!a.parse_next(depth, log)) {
                return false;
            }
        }
        return true;
    }
};
//------------------------------------------------------------------------------
void write_output(std::ostream& output, const options& opts) {
    oglplus::image_data_header hdr(opts.width, opts.height, opts.depth, 3);
    hdr.format = GL_RGB;

    hdr.internal_format = GL_R3_G3_B2;
    hdr.data_type = GL_UNSIGNED_BYTE_3_3_2;
    const oglplus::gl_types::sizei_type channels = 1;

    const auto size = span_size(
      extract(opts.width) * extract(opts.height) * extract(opts.depth) *
      channels);

    oglplus::write_and_pad_texture_image_data_header(output, hdr, size);

    const oglplus::gl_types::sizei_type fd =
      extract(opts.depth) / extract(opts.rep_z);
    const oglplus::gl_types::sizei_type fh =
      extract(opts.height) / extract(opts.rep_y);
    const oglplus::gl_types::sizei_type fw =
      extract(opts.width) / extract(opts.rep_x);

    for(oglplus::gl_types::sizei_type z = 0; z < hdr.depth; ++z) {
        const oglplus::gl_types::sizei_type fz = (fd == 0 ? 0 : z / fd);
        for(oglplus::gl_types::sizei_type y = 0; y < hdr.height; ++y) {
            const oglplus::gl_types::sizei_type fy = (fh == 0 ? 0 : y / fh);
            for(oglplus::gl_types::sizei_type x = 0; x < hdr.width; ++x) {
                const oglplus::gl_types::sizei_type fx = (fw == 0 ? 0 : x / fw);
                const bool black = ((fx % 2) + (fy % 2) + (fz % 2)) % 2 == 0;
                const char outb = char(black ? 0x00 : 0xFF);

                for(oglplus::gl_types::sizei_type c = 0; c < channels; ++c) {
                    output.put(outb);
                }
            }
        }
    }
}
//------------------------------------------------------------------------------
auto parse_options(const program_args& args, options& opts) -> int;
//------------------------------------------------------------------------------
auto main(main_ctx& ctx) -> int {
    try {
        options opts;

        if(int err = parse_options(ctx.args(), opts)) {
            return err;
        }

        if(opts.output_path == string_view("-")) {
            write_output(std::cout, opts);
        } else {
            std::ofstream output_file(c_str(opts.output_path));
            write_output(output_file, opts);
        }
    } catch(const std::exception& err) {
        std::cerr << "error: " << err.what() << std::endl;
    }
    return 0;
}
//------------------------------------------------------------------------------
auto parse_options(const program_args& args, options& opts) -> int {

    for(auto a : args) {
        if(a.is_help_arg()) {
            opts.print_usage(std::cout);
            return 1;
        } else if(!opts.parse(a, std::cerr)) {
            opts.print_usage(std::cerr);
            return 2;
        }
    }

    return 0;
}
//------------------------------------------------------------------------------
} // namespace eagine

auto main(int argc, const char** argv) -> int {
    eagine::main_ctx_options options;
    options.app_id = "BakeChkrI";
    options.logger_opts.default_no_log = true;
    return eagine::main_impl(argc, argv, options, eagine::main);
}
