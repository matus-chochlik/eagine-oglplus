/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/main_ctx.hpp>
#include <eagine/main_fwd.hpp>
#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/utils/image_file_io.hpp>
#include <eagine/program_args.hpp>
#include <eagine/valid_if/filesystem.hpp>
#include <eagine/valid_if/positive.hpp>
#include <climits>
#include <fstream>
#include <random>

namespace eagine {
//------------------------------------------------------------------------------
struct options {
    valid_if_in_writable_directory<string_view> output_path{"a.oglptex"};
    valid_if_positive<int> components{1};
    valid_if_positive<int> width{256};
    valid_if_positive<int> height{256};
    valid_if_positive<int> depth{1};
    int verbosity{0};

    void print_usage(std::ostream& log) {
        log << "bake_noise_image options" << std::endl;
        log << "  options:" << std::endl;
        log << "   -o|--output PATH: Output file path "
               "or '-' for stdout."
            << std::endl;
        log << "   -c|--components N: Number of components.";
        log << std::endl;
        log << "   -f|--format FORMAT: Output format." << std::endl;
        log << "     FORMAT is one of the following:" << std::endl;
        log << "       R8" << std::endl;
        log << "       RG8" << std::endl;
        log << "       RGB8" << std::endl;
        log << "       RGBB8" << std::endl;
        log << "   -w|--width N: Output image width." << std::endl;
        log << "   -h|--height N: Output image height." << std::endl;
        log << "   -d|--depth N: Output image depth." << std::endl;
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
        } else if(a.is_tag("-c", "--components")) {
            if(!a.parse_next(components, log)) {
                return false;
            }
        } else if(a.is_tag("-f", "--format")) {
            if(a.next() == "R8") {
                components = 1;
            } else if(a.next() == "RG8") {
                components = 2;
            } else if(a.next() == "RGB8") {
                components = 3;
            } else if(a.next() == "RGBA8") {
                components = 4;
            } else {
                return false;
            }
        }
        return true;
    }
};
//------------------------------------------------------------------------------
void write_output(std::ostream& output, const options& opts) {
    oglplus::image_data_header hdr(
      opts.width, opts.height, opts.depth, extract(opts.components));
    switch(extract(opts.components)) {
        case 1:
            hdr.format = GL_RED;
            hdr.internal_format = GL_R8;
            break;
        case 2:
            hdr.format = GL_RG;
            hdr.internal_format = GL_RG8;
            break;
        case 3:
            hdr.format = GL_RGB;
            hdr.internal_format = GL_RGB8;
            break;
        case 4:
            hdr.format = GL_RGBA;
            hdr.internal_format = GL_RGBA8;
            break;
    }

    hdr.data_type = GL_UNSIGNED_BYTE;

    const auto size = span_size(
      extract(opts.width) * extract(opts.height) * extract(opts.depth) *
      extract(opts.components));

    oglplus::write_and_pad_texture_image_data_header(output, hdr, size);

    const unsigned mask = ((1U << unsigned(CHAR_BIT)) - 1U);

    std::random_device rd;
    std::independent_bits_engine<std::mt19937, CHAR_BIT, unsigned> ibe(rd());

    for(span_size_t i = 0; i < size; ++i) {
        output.put(char(ibe() & mask));
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

        if(are_equal(opts.output_path, string_view("-"))) {
            write_output(std::cout, opts);
        } else {
            std::ofstream output_file(c_str(opts.output_path));
            write_output(output_file, opts);
        }
    } catch(const std::exception& err) {
        std::cerr << "what: " << err.what() << std::endl;
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
    options.app_id = "BakeNoisI";
    options.logger_opts.default_no_log = true;
    return eagine::main_impl(argc, argv, options);
}
