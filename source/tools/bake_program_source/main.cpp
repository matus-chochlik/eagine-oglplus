/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/data_baking.hpp>
#include <eagine/file_contents.hpp>
#include <eagine/main_ctx.hpp>
#include <eagine/main_fwd.hpp>
#include <eagine/memory/buffer.hpp>
#include <eagine/oglplus/gl.hpp>
#include <eagine/oglplus/utils/program_file_hdr.hpp>
#include <eagine/program_args.hpp>
#include <eagine/valid_if/not_empty.hpp>
#include <fstream>
#include <iostream>

namespace eagine {
//------------------------------------------------------------------------------
struct options {
    std::vector<string_view> vertex_shader_paths;
    std::vector<string_view> geometry_shader_paths;
    std::vector<string_view> tess_control_shader_paths;
    std::vector<string_view> tess_evaluation_shader_paths;
    std::vector<string_view> fragment_shader_paths;
    std::vector<string_view> compute_shader_paths;
    string_view output_path{"a.oglpprog"};

    auto parse(program_arg& a, std::ostream&) -> bool {
        if(a.is_tag("-o", "--output")) {
            output_path = a.next();
        } else if(a.is_tag("-vx", "--vertex")) {
            vertex_shader_paths.emplace_back(a.next());
        } else if(a.is_tag("-gy", "--geometry")) {
            geometry_shader_paths.emplace_back(a.next());
        } else if(a.is_tag("-tc", "--tess-control")) {
            tess_control_shader_paths.emplace_back(a.next());
        } else if(a.is_tag("-te", "--tess-evaluation")) {
            tess_evaluation_shader_paths.emplace_back(a.next());
        } else if(a.is_tag("-ft", "--fragment")) {
            fragment_shader_paths.emplace_back(a.next());
        } else if(a.is_tag("-ce", "--compute")) {
            compute_shader_paths.emplace_back(a.next());
        }
        return true;
    }

    void print_usage(std::ostream& log) {
        log << "bake_noise_image options\n";
        log << "  options:\n";
        log << "   -o|--output PATH: Output file path or '-' for stdout.\n";
        log << "   -vx|--vertex PATH: Vertex shader file path.\n";
        log << "   -gy|--geometry PATH: Geometry shader file path.\n";
        log << "   -tc|--tess-control PATH: Tess.ctrl. shader file path.\n";
        log << "   -te|--tess-evaluation PATH: Tess.eval. shader file path.\n";
        log << "   -ft|--fragment PATH: Fragment shader file path.\n";
        log << "   -ce|--compute PATH: Compute shader file path.\n";
    }
};
//------------------------------------------------------------------------------
void read_shader_source_texts(
  std::vector<file_contents>& source_texts,
  std::vector<GLenum>& shader_types,
  GLenum shader_type,
  const std::vector<string_view>& paths) {

    for(const auto& path : paths) {
        source_texts.emplace_back(file_contents(path));
        shader_types.push_back(shader_type);
    }
}
//------------------------------------------------------------------------------
void write_output(std::ostream& output, const options& opts) {
    std::vector<file_contents> source_texts;
    std::vector<GLenum> shader_types;

    read_shader_source_texts(
      source_texts, shader_types, GL_VERTEX_SHADER, opts.vertex_shader_paths);

#ifdef GL_GEOMETRY_SHADER
    read_shader_source_texts(
      source_texts,
      shader_types,
      GL_GEOMETRY_SHADER,
      opts.geometry_shader_paths);
#endif

#ifdef GL_TESS_CONTROL_SHADER
    read_shader_source_texts(
      source_texts,
      shader_types,
      GL_TESS_CONTROL_SHADER,
      opts.tess_control_shader_paths);
#endif

#ifdef GL_TESS_EVALUATION_SHADER
    read_shader_source_texts(
      source_texts,
      shader_types,
      GL_TESS_EVALUATION_SHADER,
      opts.tess_evaluation_shader_paths);
#endif

    read_shader_source_texts(
      source_texts,
      shader_types,
      GL_FRAGMENT_SHADER,
      opts.fragment_shader_paths);

#ifdef GL_COMPUTE_SHADER
    read_shader_source_texts(
      source_texts, shader_types, GL_COMPUTE_SHADER, opts.compute_shader_paths);
#endif

    std::vector<span_size_t> slens;
    slens.reserve(source_texts.size());

    auto required_size = span_size(
      sizeof(oglplus::program_source_header) +
      source_texts.size() *
        (sizeof(memory::offset_ptr<oglplus::shader_source_header>) +
         sizeof(oglplus::shader_source_header)));

    for(auto& source_text : source_texts) {
        slens.push_back(source_text.block().size());
        required_size += slens.back() * 2;
    }

    memory::buffer buf;
    buf.resize(required_size);

    data_bake_arena bakery(buf);

    auto& prog_src_hdr = bakery.make<oglplus::program_source_header>();

    auto ssh_ptrs =
      bakery.make_array<memory::offset_ptr<const oglplus::shader_source_header>>(
        span_size(source_texts.size()));

    prog_src_hdr.shader_sources = ssh_ptrs;

    for(std_size_t i = 0; i < shader_types.size(); ++i) {
        auto& shdr_src_hdr = bakery.make<oglplus::shader_source_header>();

        shdr_src_hdr.shader_type = shader_types[i];
        shdr_src_hdr.source_text = bakery.copy_array(
          memory::accommodate<const GLchar>(source_texts[i].block()));

        ssh_ptrs[i] = &shdr_src_hdr;
    }

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

    if(are_equal(opts.output_path, string_view("-"))) {
        write_output(std::cout, opts);
    } else {
        std::ofstream output_file(c_str(opts.output_path));
        write_output(output_file, opts);
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
    options.app_id = EAGINE_ID(BakeSLProg);
    options.logger_opts.default_no_log = true;
    return eagine::main_impl(argc, argv, options);
}
