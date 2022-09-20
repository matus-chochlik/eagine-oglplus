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
    std::vector<valid_if_existing_file<string_view>> vertex_shader_paths;
    std::vector<valid_if_existing_file<string_view>> geometry_shader_paths;
    std::vector<valid_if_existing_file<string_view>> tess_control_shader_paths;
    std::vector<valid_if_existing_file<string_view>>
      tess_evaluation_shader_paths;
    std::vector<valid_if_existing_file<string_view>> fragment_shader_paths;
    std::vector<valid_if_existing_file<string_view>> compute_shader_paths;
    valid_if_in_writable_directory<string_view> output_path{"a.oglpprog"};

    auto parse(program_arg& a, std::ostream& log) -> bool {
        if(a.is_tag("-o", "--output")) {
            if(!a.parse_next(output_path, log)) {
                return false;
            }
        } else if(a.is_tag("-vx", "--vertex")) {
            if(!a.parse_next(vertex_shader_paths, log)) {
                return false;
            }
        } else if(a.is_tag("-gy", "--geometry")) {
            if(!a.parse_next(geometry_shader_paths, log)) {
                return false;
            }
        } else if(a.is_tag("-tc", "--tess-control")) {
            if(!a.parse_next(tess_control_shader_paths, log)) {
                return false;
            }
        } else if(a.is_tag("-te", "--tess-evaluation")) {
            if(!a.parse_next(tess_evaluation_shader_paths, log)) {
                return false;
            }
        } else if(a.is_tag("-ft", "--fragment")) {
            if(!a.parse_next(fragment_shader_paths, log)) {
                return false;
            }
        } else if(a.is_tag("-ce", "--compute")) {
            if(!a.parse_next(compute_shader_paths, log)) {
                return false;
            }
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
  std::vector<oglplus::gl_types::enum_type>& shader_types,
  oglplus::gl_types::enum_type shader_type,
  const std::vector<valid_if_existing_file<string_view>>& paths) {

    for(const auto& path : paths) {
        source_texts.emplace_back(extract(path));
        shader_types.push_back(shader_type);
    }
}
//------------------------------------------------------------------------------
void write_output(std::ostream& output, const options& opts) {
    std::vector<file_contents> source_texts;
    std::vector<oglplus::gl_types::enum_type> shader_types;

    read_shader_source_texts(
      source_texts, shader_types, GL_VERTEX_SHADER, opts.vertex_shader_paths);

    read_shader_source_texts(
      source_texts,
      shader_types,
      GL_GEOMETRY_SHADER,
      opts.geometry_shader_paths);

    read_shader_source_texts(
      source_texts,
      shader_types,
      GL_TESS_CONTROL_SHADER,
      opts.tess_control_shader_paths);

    read_shader_source_texts(
      source_texts,
      shader_types,
      GL_TESS_EVALUATION_SHADER,
      opts.tess_evaluation_shader_paths);

    read_shader_source_texts(
      source_texts,
      shader_types,
      GL_FRAGMENT_SHADER,
      opts.fragment_shader_paths);

    read_shader_source_texts(
      source_texts, shader_types, GL_COMPUTE_SHADER, opts.compute_shader_paths);

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
          memory::accommodate<const oglplus::gl_types::char_type>(
            source_texts[i].block()));

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

    if(opts.output_path == string_view("-")) {
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
    options.app_id = "BakeSLProg";
    options.logger_opts.default_no_log = true;
    return eagine::main_impl(argc, argv, options, eagine::main);
}
