/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef EAGINE_OGLPLUS_UTILS_IMAGE_SPEC_HPP
#define EAGINE_OGLPLUS_UTILS_IMAGE_SPEC_HPP

#include "../gl_api/enum_types.hpp"
#include <eagine/assert.hpp>
#include <eagine/memory/block.hpp>
#include <eagine/span.hpp>

namespace eagine::oglplus {

class image_dimensions {
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
        EAGINE_ASSERT(_width > 0 && _height > 0 && _depth > 0);
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

class image_pixel_format {
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

class image_pixel_data {
public:
    image_pixel_data(
      const pixel_data_type pix_type,
      const memory::const_block pix_data,
      const span_size_t type_size) noexcept
      : _type{pix_type}
      , _pixels{pix_data}
      , _element_bytes{type_size} {
        EAGINE_ASSERT(_element_bytes > 0);
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

class image_spec
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

} // namespace eagine::oglplus

#endif // EAGINE_OGLPLUS_UTILS_IMAGE_SPEC_HPP
