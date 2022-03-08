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
#include <eagine/valid_if/not_empty.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <png.h>
#include <stdexcept>
#include <vector>

namespace eagine {
//------------------------------------------------------------------------------
#ifdef GL_RGBA16
constexpr const bool has_rgba16 = true;
#else
constexpr const bool has_rgba16 = false;
#endif
//------------------------------------------------------------------------------
// program options
struct options {
    std::vector<valid_if_existing_file<string_view>> input_paths;
    valid_if_in_writable_directory<string_view> output_path;

    void print_usage(std::ostream& log) {
        log << "bake_noise_image options\n";
        log << "  options:\n";
        log << "   -i|--input PATH: Existing PNG file path or '-' for stdin.\n";
        log << "   -o|--output PATH: Output file path or '-' for stdout.\n";
    }

    auto parse(program_arg& arg, std::ostream& log) -> bool {
        if(arg.is_tag("-o", "--output")) {
            if(!arg.parse_next(output_path, log)) {
                return false;
            }
        } else if(arg.is_tag("-i", "--input")) {
            if(!arg.parse_next(input_paths, log)) {
                return false;
            }
        }
        return true;
    }

    auto from_stdin() const -> tribool {
        return !input_paths.empty() && input_paths.front() == string_view("-");
    }

    auto to_stdout() const -> tribool {
        return output_path == string_view("-");
    }
};
//------------------------------------------------------------------------------
// png_header_validator
class png_header_validator {
public:
    explicit png_header_validator(std::istream& input);
};
//------------------------------------------------------------------------------
class png_read_driver;

// png_read_struct
class png_read_struct {
protected:
    ::png_structp _read = {};

    [[noreturn]] static void _handle_error(::png_structp, const char* msg);

    static void _handle_warning(::png_structp, const char* msg);

    friend class png_read_driver;

public:
    png_read_struct();
    png_read_struct(png_read_struct&&) noexcept = default;
    png_read_struct(const png_read_struct&) noexcept = default;
    auto operator=(png_read_struct&&) = delete;
    auto operator=(const png_read_struct&) = delete;
    ~png_read_struct() noexcept;
};
//------------------------------------------------------------------------------
// png_read_info_struct
class png_read_info_struct : public png_read_struct {
protected:
    ::png_infop _info = {};

    friend class png_read_driver;

public:
    png_read_info_struct();
    png_read_info_struct(png_read_info_struct&&) noexcept = default;
    png_read_info_struct(const png_read_info_struct&) noexcept = default;
    auto operator=(png_read_info_struct&&) = delete;
    auto operator=(const png_read_info_struct&) = delete;
    ~png_read_info_struct() noexcept;

    auto row_bytes() -> png_uint_32;
    auto image_width() -> png_uint_32;
    auto image_height() -> png_uint_32;
    auto bit_depth() -> png_uint_32;
    auto channels() -> png_byte;
    auto color_type() -> png_byte;

    void set_palette_to_rgb();
    void set_expand_gray_1_2_4_to_8();
    void set_tRNS_to_alpha();
    auto get_valid(png_uint_32) -> png_uint_32;
};
//------------------------------------------------------------------------------
// png_read_info_end_struct
class png_read_info_end_struct : public png_read_info_struct {
protected:
    ::png_infop _endi = {};

    friend class png_read_driver;

public:
    png_read_info_end_struct();
    png_read_info_end_struct(png_read_info_end_struct&&) noexcept = default;
    png_read_info_end_struct(const png_read_info_end_struct&) noexcept = default;
    auto operator=(png_read_info_end_struct&&) = delete;
    auto operator=(const png_read_info_end_struct&) = delete;
    ~png_read_info_end_struct() noexcept;
};
//------------------------------------------------------------------------------
class png_reader;
// png_read_driver
class png_read_driver {
private:
    png_read_info_end_struct& _png;

    static void _read_data(::png_structp, ::png_bytep, ::png_size_t);

    static auto _read_user_chunk(::png_structp, ::png_unknown_chunkp) -> int;

    void _read_row(::png_bytep data);

    friend class png_reader;

public:
    explicit png_read_driver(png_reader& reader);
};
//------------------------------------------------------------------------------
// png_reader
class png_reader {
private:
    std::istream& _input;
    png_header_validator _validator;
    png_read_info_end_struct _png;
    png_read_driver _driver;

    friend class png_read_driver;

public:
    explicit png_reader(std::istream& input);

    void do_read_data(::png_bytep, ::png_size_t);
    void read_row(::png_bytep data) {
        _driver._read_row(data);
    }

    auto channels() {
        return _driver._png.channels();
    }

    auto image_width() {
        return _driver._png.image_width();
    }
    auto image_height() {
        return _driver._png.image_height();
    }
    auto row_bytes() {
        return _driver._png.row_bytes();
    }
    auto data_size() {
        return row_bytes() * image_height();
    }

    auto gl_data_type() -> GLenum;
    auto gl_format() -> GLenum;
    auto gl_iformat() -> GLenum;
};
//------------------------------------------------------------------------------
void do_convert_image(
  std::istream& input,
  std::ostream& output,
  oglplus::image_data_header& header,
  int layer) {
    auto match_value = [](auto& original, const auto& current, auto message) {
        if(original) {
            if(original != current) {
                throw std::runtime_error(message);
            }
        } else {
            original = current;
        }
    };

    png_reader reader(input);

    const auto width = int(reader.image_width());
    const auto height = int(reader.image_height());
    const auto channels = int(reader.channels());

    match_value(header.width, width, "inconsistent image width");
    match_value(header.height, height, "inconsistent image height");
    match_value(header.channels, channels, "inconsistent image channel count");

    const auto data_type = reader.gl_data_type();
    const auto format = reader.gl_format();
    const auto iformat = reader.gl_iformat();

    match_value(header.data_type, data_type, "inconsistent image data type");
    match_value(header.format, format, "inconsistent pixel format");
    match_value(
      header.internal_format, iformat, "inconsistent internal format");

    auto row_size = reader.row_bytes();
    auto size = reader.data_size();

    if(layer == 0) {
        oglplus::write_and_pad_texture_image_data_header(
          output, header, span_size(size));
    }

    std::vector<::png_byte> buffer(std_size(size));

    for(png_uint_32 r = 0, h = reader.image_height(); r < h; ++r) {
        reader.read_row(buffer.data() + (h - 1 - r) * row_size);
    }

    output.write(
      reinterpret_cast<const char*>(buffer.data()),
      static_cast<std::streamsize>(buffer.size()));
}
//------------------------------------------------------------------------------
void convert_image(std::istream& input, std::ostream& output) {
    oglplus::image_data_header header{};
    header.depth = 1;
    do_convert_image(input, output, header, 0);
}
//------------------------------------------------------------------------------
auto parse_options(const program_args& args, options& opts) -> int;
//------------------------------------------------------------------------------
auto main(main_ctx& ctx) -> int {
    try {
        options opts;

        if(int err{parse_options(ctx.args(), opts)}) {
            return err;
        }

        const auto from_stdin = opts.from_stdin();
        const auto to_stdout = opts.to_stdout();

        if(from_stdin && to_stdout) {
            convert_image(std::cin, std::cout);
        } else if(from_stdin) {
            std::ofstream output_file(c_str(opts.output_path));
            convert_image(std::cin, output_file);
        } else if(to_stdout) {
            oglplus::image_data_header header{};
            header.depth = limit_cast<int>(opts.input_paths.size());
            int layer = 0;
            for(auto& input_path : opts.input_paths) {
                std::ifstream input_file(c_str(input_path));
                do_convert_image(input_file, std::cout, header, layer++);
            }
        } else {
            oglplus::image_data_header header{};
            header.depth = limit_cast<int>(opts.input_paths.size());
            std::ofstream output_file(c_str(opts.output_path));
            int layer = 0;
            for(auto& input_path : opts.input_paths) {
                std::ifstream input_file(c_str(input_path));
                do_convert_image(input_file, output_file, header, layer++);
            }
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
png_header_validator::png_header_validator(std::istream& input) {
    if(!input.good()) {
        throw std::runtime_error("Unable to read PNG input stream");
    }

    const size_t sig_size = 8;
    ::png_byte sig[sig_size];
    input.read(reinterpret_cast<char*>(sig), sig_size);

    if(!input.good()) {
        throw std::runtime_error("Unable to read PNG signature");
    }

    if(::png_sig_cmp(static_cast<::png_byte*>(sig), 0, sig_size) != 0) {
        throw std::runtime_error("Invalid PNG signature");
    }
}
//------------------------------------------------------------------------------
[[noreturn]] void png_read_struct::_handle_error(
  ::png_structp,
  const char* message) {
    throw ::std::runtime_error(message);
}
//------------------------------------------------------------------------------
void png_read_struct::_handle_warning(::png_structp, const char* message) {
    ::std::cerr << "libpng warning: " << message << ::std::endl;
}
//------------------------------------------------------------------------------
png_read_struct::png_read_struct()
  : _read(::png_create_read_struct(
      PNG_LIBPNG_VER_STRING,
      reinterpret_cast<::png_voidp>(this),
      &_handle_error,
      &_handle_warning)) {
    if(!_read) {
        throw std::runtime_error("Unable to create PNG read struct");
    }
}
//------------------------------------------------------------------------------
png_read_struct::~png_read_struct() noexcept {
    try {
        ::png_destroy_read_struct(&_read, nullptr, nullptr);
    } catch(...) {
    }
}
//------------------------------------------------------------------------------
png_read_info_struct::png_read_info_struct()
  : png_read_struct()
  , _info(::png_create_info_struct(_read)) {
    if(!_info) {
        throw std::runtime_error("Unable to create PNG info struct");
    }
}
//------------------------------------------------------------------------------
png_read_info_struct::~png_read_info_struct() noexcept {
    try {
        ::png_destroy_read_struct(&_read, &_info, nullptr);
    } catch(...) {
    }
}
//------------------------------------------------------------------------------
auto png_read_info_struct::row_bytes() -> png_uint_32 {
    return png_uint_32(::png_get_rowbytes(_read, _info));
}
//------------------------------------------------------------------------------
auto png_read_info_struct::image_width() -> png_uint_32 {
    return ::png_get_image_width(_read, _info);
}
//------------------------------------------------------------------------------
auto png_read_info_struct::image_height() -> png_uint_32 {
    return ::png_get_image_height(_read, _info);
}
//------------------------------------------------------------------------------
auto png_read_info_struct::bit_depth() -> png_uint_32 {
    return ::png_get_bit_depth(_read, _info);
}
//------------------------------------------------------------------------------
auto png_read_info_struct::channels() -> png_byte {
    return ::png_get_channels(_read, _info);
}
//------------------------------------------------------------------------------
auto png_read_info_struct::color_type() -> png_byte {
    return ::png_get_color_type(_read, _info);
}
//------------------------------------------------------------------------------
void png_read_info_struct::set_palette_to_rgb() {
    ::png_set_palette_to_rgb(_read);
}
//------------------------------------------------------------------------------
void png_read_info_struct::set_expand_gray_1_2_4_to_8() {
    ::png_set_expand_gray_1_2_4_to_8(_read);
}
//------------------------------------------------------------------------------
void png_read_info_struct::set_tRNS_to_alpha() {
    ::png_set_tRNS_to_alpha(_read);
}
//------------------------------------------------------------------------------
auto png_read_info_struct::get_valid(png_uint_32 flag) -> png_uint_32 {
    return ::png_get_valid(_read, _info, flag);
}
//------------------------------------------------------------------------------
png_read_info_end_struct::png_read_info_end_struct()
  : png_read_info_struct()
  , _endi(::png_create_info_struct(_read)) {
    if(!_endi) {
        throw std::runtime_error("Unable to create PNG end info struct");
    }
}
//------------------------------------------------------------------------------
png_read_info_end_struct::~png_read_info_end_struct() noexcept {
    try {
        ::png_destroy_read_struct(&_read, &_info, &_endi);
    } catch(...) {
    }
}
//------------------------------------------------------------------------------
void png_read_driver::_read_data(
  ::png_structp png,
  ::png_bytep data,
  ::png_size_t size) {
    ::png_voidp p = ::png_get_io_ptr(png);
    assert(p != nullptr); // NOLINT
    (reinterpret_cast<png_reader*>(p))->do_read_data(data, size);
}
//------------------------------------------------------------------------------
auto png_read_driver::_read_user_chunk(::png_structp, ::png_unknown_chunkp)
  -> int {
    return 0;
}
//------------------------------------------------------------------------------
void png_read_driver::_read_row(::png_bytep data) {
    ::png_read_row(_png._read, data, nullptr);
}
//------------------------------------------------------------------------------
png_read_driver::png_read_driver(png_reader& reader)
  : _png(reader._png) {
    ::png_set_read_fn(_png._read, &reader, &_read_data);
    ::png_set_read_user_chunk_fn(_png._read, &reader, &_read_user_chunk);
    ::png_set_keep_unknown_chunks(
      _png._read, PNG_HANDLE_CHUNK_NEVER, nullptr, 0);

    const size_t sig_size = 8;
    ::png_set_sig_bytes(_png._read, sig_size);
    ::png_read_info(_png._read, _png._info);

    switch(_png.color_type()) {
        case PNG_COLOR_TYPE_PALETTE: { // NOLINT
            _png.set_palette_to_rgb();
            break;
        }
        case PNG_COLOR_TYPE_GRAY: {
            if(_png.bit_depth() < 8) {
                _png.set_expand_gray_1_2_4_to_8();
            }
            break;
        }
        default:;
    }

    if(_png.get_valid(PNG_INFO_tRNS)) {
        _png.set_tRNS_to_alpha();
    }

    ::png_read_update_info(_png._read, _png._info);
}
//------------------------------------------------------------------------------
png_reader::png_reader(std::istream& input)
  : _input(input)
  , _validator(_input)
  , _driver(*this) {}
//------------------------------------------------------------------------------
auto png_reader::gl_data_type() -> GLenum {
    switch(_driver._png.bit_depth()) {
        case 1:
        case 2:
        case 4:
        case 8:
            return GL_UNSIGNED_BYTE;
        case 16: {
            if(has_rgba16) {
                return GL_UNSIGNED_SHORT;
            }
            throw std::runtime_error("Unsupported 16-bit color depth");
        }
        default: {
            throw std::runtime_error("Unsupported PNG image color depth");
        }
    }

    return GL_NONE;
}
//------------------------------------------------------------------------------
auto png_reader::gl_format() -> GLenum {
    switch(_driver._png.color_type()) {
        case PNG_COLOR_TYPE_GRAY:
            return GL_RED;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            return GL_RG;
        case PNG_COLOR_TYPE_PALETTE: // NOLINT
        case PNG_COLOR_TYPE_RGB:     // NOLINT
            return GL_RGB;
        case PNG_COLOR_TYPE_RGB_ALPHA: // NOLINT
            return GL_RGBA;
        default: {
            throw std::runtime_error("Unsupported PNG color type");
        }
    }
}
//------------------------------------------------------------------------------
auto png_reader::gl_iformat() -> GLenum {
    if(_driver._png.bit_depth() == 16) {
        if(has_rgba16) {
#if defined(GL_RGBA16)
            switch(gl_format()) {
                case GL_RED:
                    return GL_R16;
                case GL_RG:
                    return GL_RG16;
                case GL_RGB:
                    return GL_RGB16;
                case GL_RGBA:
                    return GL_RGBA16;
                default:;
            }
#endif
        }
    } else {
        switch(gl_format()) {
            case GL_RED:
                return GL_R8;
            case GL_RG:
                return GL_RG8;
            case GL_RGB:
                return GL_RGB8;
            case GL_RGBA:
                return GL_RGBA8;
            default:;
        }
    }

    return GL_NONE;
}
//------------------------------------------------------------------------------
void png_reader::do_read_data(::png_bytep data, ::png_size_t size) {
    _input.read(reinterpret_cast<char*>(data), std::streamsize(size));
    if(!_input.good()) {
        throw std::runtime_error("Unable to read PNG data");
    }
}
//------------------------------------------------------------------------------
} // namespace eagine

auto main(int argc, const char** argv) -> int {
    eagine::main_ctx_options options;
    options.app_id = EAGINE_ID(BakePNGI);
    options.logger_opts.default_no_log = true;
    return eagine::main_impl(argc, argv, options);
}
