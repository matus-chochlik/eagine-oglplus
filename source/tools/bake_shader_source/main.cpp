/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.oglplus;
import <fstream>;
import <iostream>;

#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif
#ifndef GL_GEOMETRY_SHADER
#define GL_GEOMETRY_SHADER 0x8DD9
#endif
#ifndef GL_TESS_EVALUATION_SHADER
#define GL_TESS_EVALUATION_SHADER 0x8E87
#endif
#ifndef GL_TESS_CONTROL_SHADER
#define GL_TESS_CONTROL_SHADER 0x8E88
#endif
#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif
#ifndef GL_COMPUTE_SHADER
#define GL_COMPUTE_SHADER 0x91B9
#endif

namespace eagine {
//------------------------------------------------------------------------------
struct options {
    valid_if_existing_file<string_view> input_path;
    valid_if_in_writable_directory<string_view> output_path{"a.oglpshdr"};
    oglplus::gl_types::enum_type shader_type{0};

    void print_usage(std::ostream& log) {
        log << "bake_shader_source options" << std::endl;
        log << "  options:" << std::endl;
        log << "   -i|--input PATH: Input GLSL file path "
            << "or '-' for stdin." << std::endl;
        log << "   -o|--output PATH: Output file path "
               "or '-' for stdout."
            << std::endl;
        log << "   -t|--shader-type TYPE: Shader type." << std::endl;
        log << "     TYPE is one of the following:" << std::endl;
        log << "       vertex" << std::endl;
        log << "       geometry" << std::endl;
        log << "       tess_control" << std::endl;
        log << "       tess_evaluation" << std::endl;
        log << "       fragment" << std::endl;
        log << "       compute" << std::endl;
    }

    auto parse(program_arg& a, std::ostream& log) -> bool {
        if(a.is_tag("-o", "--output")) {
            if(!a.parse_next(output_path, log)) {
                return false;
            }
        } else if(a.is_tag("-i", "--input")) {
            if(!a.parse_next(input_path, log)) {
                return false;
            }
        } else if(a.is_tag("-t", "--shader-type")) {
            if(a.next() == "vertex") {
                shader_type = GL_VERTEX_SHADER;
            } else if(a.next() == "geometry") {
                shader_type = GL_GEOMETRY_SHADER;
            } else if(a.next() == "tess_control") {
                shader_type = GL_TESS_CONTROL_SHADER;
            } else if(a.next() == "tess_evaluation") {
                shader_type = GL_TESS_EVALUATION_SHADER;
            } else if(a.next() == "compute") {
                shader_type = GL_COMPUTE_SHADER;
            } else if(a.next() == "fragment") {
                shader_type = GL_FRAGMENT_SHADER;
            }
        }
        return false;
    }
};
//------------------------------------------------------------------------------
void write_output(
  std::istream& input,
  std::ostream& output,
  const options& opts) {
    oglplus::shader_source_header hdr;

    memory::buffer source_text;
    read_stream_data(input, source_text);

    memory::buffer buf;
    buf.resize(
      span_size(sizeof(oglplus::shader_source_header)) +
      source_text.size() * 2);

    data_bake_arena bakery(buf);

    auto& shdr_src_hdr = bakery.make<oglplus::shader_source_header>();

    shdr_src_hdr.shader_type = opts.shader_type;
    shdr_src_hdr.source_text =
      bakery.copy_array(memory::accommodate<const oglplus::gl_types::char_type>(
        memory::const_block(source_text)));

    write_to_stream(output, bakery.baked_data());
}
//------------------------------------------------------------------------------
auto parse_options(const program_args& args, options& opts) -> int;
//------------------------------------------------------------------------------
auto run(const program_args& args) -> int {
    options opts;

    if(int err = parse_options(args, opts)) {
        return err;
    }

    const auto from_stdin = opts.input_path == string_view("-");
    const auto to_stdout = opts.output_path == string_view("-");

    if(from_stdin && to_stdout) {
        write_output(std::cin, std::cout, opts);
    } else if(from_stdin) {
        std::ofstream output_file(c_str(opts.output_path));
        write_output(std::cin, output_file, opts);
    } else if(to_stdout) {
        std::ifstream input_file(c_str(opts.input_path));
        write_output(input_file, std::cout, opts);
    } else {
        std::ifstream input_file(c_str(opts.input_path));
        std::ofstream output_file(c_str(opts.output_path));
        write_output(input_file, output_file, opts);
    }
    return 0;
}
//------------------------------------------------------------------------------
auto main(main_ctx& ctx) -> int {

    try {
        return run(ctx.args());
    } catch(const std::exception& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }
    return 1;
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
    options.app_id = "BakeSLShdr";
    options.logger_opts.default_no_log = true;
    return eagine::main_impl(argc, argv, options, eagine::main);
}
