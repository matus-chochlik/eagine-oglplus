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
import <iomanip>;
import <iostream>;
#else
#include <eagine/integer_range.hpp>
#include <eagine/main_ctx.hpp>
#include <eagine/main_fwd.hpp>
#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/utils/image_file_io.hpp>
#include <eagine/program_args.hpp>
#include <eagine/valid_if/filesystem.hpp>
#include <eagine/valid_if/one_of.hpp>
#include <eagine/valid_if/positive.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#endif
#include <cassert>

#ifndef GL_RED_INTEGER
#define GL_RED_INTEGER 0x8D94
#endif
#ifndef GL_R8UI
#define GL_R8UI 0x8232
#endif
#ifndef GL_UNSIGNED_BYTE
#define GL_UNSIGNED_BYTE 0x1401
#endif

namespace eagine {
//------------------------------------------------------------------------------
struct options {
    std::vector<valid_if_existing_file<string_view>> input_paths;
    valid_if_in_writable_directory<string_view> output_path{"a.oglptex"};
    valid_if_one_of<int, 4> rank{4};
    valid_if_positive<int> width{256};
    valid_if_positive<int> height{256};

    void print_usage(std::ostream& log) {
        log << "bake_noise_image options\n";
        log << "  options:\n";
        log << "   -i|--input PATH: Existing PNG file path or '-' for stdin.\n";
        log << "   -o|--output PATH: Output file path or '-' for stdout.\n";
        log << "   -r|--rank N: Tiling rank.\n";
        log << "   -w|--width N: Output image width.\n";
        log << "   -h|--height N: Output image height.\n";
    }

    auto parse(program_arg& arg, std::ostream& log) -> bool {
        if(arg.is_tag("-o", "--output")) {
            if(!arg.next().parse(output_path, log)) {
                return false;
            }
        } else if(arg.is_tag("-i", "--input")) {
            if(!arg.next().parse(input_paths, log)) {
                return false;
            }
        } else if(arg.is_tag("-w", "--width")) {
            if(!arg.next().parse(width, log)) {
                return false;
            }
        } else if(arg.is_tag("-h", "--height")) {
            if(!arg.next().parse(height, log)) {
                return false;
            }
        } else if(arg.is_tag("-r", "--rank")) {
            if(!arg.next().parse(rank, log)) {
                return false;
            }
        }
        return true;
    }
};
//------------------------------------------------------------------------------
auto translate(char c, const options& opts) -> int {
    // TODO: other ranks
    assert(opts.rank.value() == 4);

    if(opts.rank.value() == 4) {
        if(c >= '0' && c <= '9') {
            return char(c - '0');
        }
        if(c >= 'A' && c <= 'F') {
            return char(c - 'A' + 10);
        }
        if(c >= 'a' && c <= 'f') {
            return char(c - 'a' + 10);
        }
    }
    return c;
}
//------------------------------------------------------------------------------
auto write_output(std::ostream& output, const options& opts) -> int {
    auto& input_paths = opts.input_paths;
    if(input_paths.empty()) {
        std::cerr << "error: no inputs" << std::endl;
        return 3;
    }

    oglplus::image_data_header hdr{
      opts.width, opts.height, limit_cast<int>(input_paths.size()), 1};
    hdr.format = GL_RED_INTEGER;
    hdr.internal_format = GL_R8UI;
    hdr.data_type = GL_UNSIGNED_BYTE;

    const auto size = span_size(opts.width.value() * opts.height.value()) *
                      span_size(input_paths.size());

    oglplus::write_and_pad_texture_image_data_header(output, hdr, size);

    for(auto input_path : input_paths) {
        std::ifstream input{c_str(input_path)};
        char c{};
        for(const int y : integer_range(opts.height.value())) {
            for(const int x : integer_range(opts.width.value())) {
                if(!(input >> c).good()) {
                    std::cerr << "error: failed to read from input file '"
                              << input_path.value_anyway() << "' at position "
                              << x << "," << y << std::endl;
                    return 4;
                }
                output.put(char(translate(c, opts)));
            }
        }
    }

    return 0;
}
//------------------------------------------------------------------------------
auto parse_options(const program_args& args, options& opts) -> int;
//------------------------------------------------------------------------------
auto main(main_ctx& ctx) -> int {
    try {
        options opts;

        if(auto err{parse_options(ctx.args(), opts)}) {
            return err;
        }

        if(are_equal(opts.output_path, string_view("-"))) {
            return write_output(std::cout, opts);
        } else {
            std::ofstream output_file(c_str(opts.output_path));
            return write_output(output_file, opts);
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
    options.app_id = "BakeTlngI";
    options.logger_opts.default_no_log = true;
    return eagine::main_impl(argc, argv, options, eagine::main);
}
