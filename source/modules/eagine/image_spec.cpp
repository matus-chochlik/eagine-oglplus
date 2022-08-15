/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include <cassert>

export module eagine.oglplus:image_spec;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.valid_if;
import eagine.core.utility;
import eagine.core.runtime;
import :config;
import :enum_types;
import <iostream>;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
export struct image_data_header {
    file_magic_number<'o', 'g', 'l', '+', 't', 'e', 'x', 'i'> magic;
    gl_types::sizei_type width{0}, height{0}, depth{0}, channels{0};
    gl_types::enum_type format{0}, internal_format{0};
    gl_types::enum_type data_type{0};

    memory::offset_span<const gl_types::ubyte_type> pixels{};

    constexpr image_data_header() noexcept = default;

    image_data_header(
      const valid_if_positive<gl_types::sizei_type>& w,
      const valid_if_positive<gl_types::sizei_type>& h,
      const valid_if_positive<gl_types::sizei_type>& d,
      const valid_if_positive<gl_types::sizei_type>& c) noexcept
      : width{w.value()}
      , height{h.value()}
      , depth{d.value()}
      , channels{c.value()} {}
};
//------------------------------------------------------------------------------
export class image_dimensions {
public:
    image_dimensions(
      const gl_types::sizei_type w,
      const gl_types::sizei_type h,
      const gl_types::sizei_type d,
      const gl_types::sizei_type c) noexcept
      : _width{w}
      , _height{h}
      , _depth{d}
      , _channels{c} {
        assert(_width > 0 && _height > 0 && _depth > 0);
    }

    auto is_1d() const noexcept -> bool {
        return _width > 1 && _height == 1 && _depth == 1;
    }

    auto is_2d() const noexcept -> bool {
        return _width > 1 && _height > 1 && _depth == 1;
    }

    auto is_3d() const noexcept -> bool {
        return _width > 1 && _height > 1 && _depth > 1;
    }

    auto width() const noexcept -> gl_types::sizei_type {
        return _width;
    }

    auto height() const noexcept -> gl_types::sizei_type {
        return _height;
    }

    auto depth() const noexcept -> gl_types::sizei_type {
        return _depth;
    }

    auto channels() const noexcept -> gl_types::sizei_type {
        return _channels;
    }

private:
    gl_types::sizei_type _width{1};
    gl_types::sizei_type _height{1};
    gl_types::sizei_type _depth{1};
    gl_types::sizei_type _channels{1};
};
//------------------------------------------------------------------------------
export class image_pixel_format {
public:
    image_pixel_format(
      const pixel_format fmt,
      const pixel_internal_format ifmt) noexcept
      : _format{fmt}
      , _internal_format{ifmt} {}

    image_pixel_format(const pixel_format fmt) noexcept
      : _format{fmt}
      , _internal_format{pixel_internal_format(gl_types::enum_type(fmt))} {}

    auto format() const noexcept -> pixel_format {
        return _format;
    }

    auto internal_format() const noexcept -> pixel_internal_format {
        return _internal_format;
    }

private:
    pixel_format _format;
    pixel_internal_format _internal_format;
};
//------------------------------------------------------------------------------
export class image_pixel_data {
public:
    image_pixel_data(
      const pixel_data_type pix_type,
      const memory::const_block pix_data,
      const span_size_t type_size) noexcept
      : _type{pix_type}
      , _pixels{pix_data}
      , _element_bytes{type_size} {
        assert(_element_bytes > 0);
    }

    auto type() const noexcept -> pixel_data_type {
        return _type;
    }

    auto data() const noexcept -> memory::const_block {
        return _pixels;
    }

    auto element_bits() const noexcept -> span_size_t {
        return _element_bytes * 8;
    }

    auto element_bytes() const noexcept -> span_size_t {
        return _element_bytes;
    }

private:
    pixel_data_type _type;
    memory::const_block _pixels;
    span_size_t _element_bytes;
};
//------------------------------------------------------------------------------
export class image_spec
  : public image_dimensions
  , public image_pixel_format
  , public image_pixel_data {
public:
    image_spec(
      const image_dimensions& dims,
      const image_pixel_format& fmt,
      const image_pixel_data& pix_data) noexcept
      : image_dimensions(dims)
      , image_pixel_format(fmt)
      , image_pixel_data(pix_data) {}

    auto pixel_bytes() const noexcept -> span_size_t {
        return channels() * element_bytes();
    }

    auto data_slice2d(gl_types::sizei_type i) const noexcept
      -> memory::const_block {
        const span_size_t size{width() * height() * pixel_bytes()};
        return head(skip(data(), size * i), size);
    }
};
//------------------------------------------------------------------------------
export class texture_image_block {
private:
    memory::structured_block<const image_data_header> _header;

public:
    texture_image_block(const memory::const_block blk)
      : _header(blk) {}

    texture_image_block(const image_data_header* ptr)
      : _header(as_bytes(view_one(ptr))) {}

    auto is_valid() const noexcept -> bool {
        return _header->magic.is_valid();
    }

    auto dimensions() const noexcept -> image_dimensions {
        return {
          _header->width, _header->height, _header->depth, _header->channels};
    }

    auto format() const noexcept -> image_pixel_format {
        return {
          pixel_format(_header->format),
          pixel_internal_format(_header->internal_format)};
    }

    auto format(const pixel_internal_format ifmt) const noexcept
      -> image_pixel_format {
        return {pixel_format(_header->format), ifmt};
    }

    auto pixel_element_bytes() const noexcept -> span_size_t {
        return span_size(sizeof(gl_types::byte_type));
    }

    auto pixel_data() const noexcept -> image_pixel_data {
        return {
          pixel_data_type(_header->data_type),
          as_bytes(memory::const_block(_header->pixels)),
          pixel_element_bytes()};
    }

    auto spec() const noexcept -> image_spec {
        return {dimensions(), format(), pixel_data()};
    }

    auto spec(const pixel_internal_format ifmt) const noexcept -> image_spec {
        return {dimensions(), format(ifmt), pixel_data()};
    }

    inline operator image_spec() const noexcept {
        return spec();
    }
};
//------------------------------------------------------------------------------
export class texture_image_file
  : protected_member<file_contents>
  , public texture_image_block {
public:
    texture_image_file(file_contents&& fc)
      : protected_member<file_contents>(std::move(fc))
      , texture_image_block(get_the_member()) {}

    texture_image_file(const string_view path)
      : texture_image_file(file_contents(path)) {}

    texture_image_file(const std::string& path)
      : texture_image_file(string_view(path)) {}
};
//------------------------------------------------------------------------------
export void write_and_pad_texture_image_data_header(
  std::ostream& output,
  image_data_header& header,
  const span_size_t pixel_data_size,
  span_size_t& spos);
//------------------------------------------------------------------------------
export void write_and_pad_texture_image_data_header(
  std::ostream& output,
  image_data_header& header,
  const span_size_t pixel_data_size);
//------------------------------------------------------------------------------
export void write_texture_image_data(
  std::ostream& output,
  image_data_header& header,
  const memory::const_block pixels) {
    write_and_pad_texture_image_data_header(
      output, header, span_size(pixels.size()));

    write_to_stream(output, pixels);
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
