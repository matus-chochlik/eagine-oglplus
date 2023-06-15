/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:resources;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.reflection;
import eagine.core.value_tree;
import eagine.core.resource;
import eagine.core.main_ctx;
import :config;
import :objects;
import :enum_types;
import :api;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
// texture build info
//------------------------------------------------------------------------------
export struct texture_build_info {
    std::optional<gl_types::int_type> levels;
    std::optional<gl_types::int_type> channels;
    std::optional<gl_types::sizei_type> width;
    std::optional<gl_types::sizei_type> height;
    std::optional<gl_types::sizei_type> depth;
    std::optional<pixel_data_type> data_type;
    std::optional<pixel_format> format;
    std::optional<pixel_internal_format> iformat;
    //
    std::optional<texture_wrap_mode> wrap_s;
    std::optional<texture_wrap_mode> wrap_t;
    std::optional<texture_wrap_mode> wrap_r;
    std::optional<texture_swizzle_mode> swizzle_r;
    std::optional<texture_swizzle_mode> swizzle_g;
    std::optional<texture_swizzle_mode> swizzle_b;
    std::optional<texture_swizzle_mode> swizzle_a;
    std::optional<texture_min_filter> min_filter;
    std::optional<texture_mag_filter> mag_filter;

    auto dimensions() const noexcept -> span_size_t {
        return span_size(bool(width)) + span_size(bool(height)) +
               span_size(bool(depth));
    }

    auto is_complete() const noexcept -> bool {
        return width and data_type and format and iformat;
    }

    template <typename T>
    auto texture_storage1d(
      texture_name tex,
      texture_target target,
      const basic_gl_api<T>& glapi) const noexcept -> bool;

    template <typename T>
    auto texture_storage2d(
      texture_name tex,
      texture_target target,
      const basic_gl_api<T>& glapi) const noexcept -> bool;

    template <typename T>
    auto texture_storage3d(
      texture_name tex,
      texture_target target,
      const basic_gl_api<T>& glapi) const noexcept -> bool;

    template <typename T>
    auto texture_storage(
      texture_name tex,
      texture_target target,
      const basic_gl_api<T>& glapi) const noexcept -> bool {
        switch(dimensions()) {
            case 3:
                return texture_storage3d(tex, target, glapi);
            case 2:
                return texture_storage2d(tex, target, glapi);
            case 1:
                return texture_storage1d(tex, target, glapi);
            default:
                return false;
        }
    }

    template <typename T>
    auto texture_image1d(
      texture_name tex,
      texture_target target,
      gl_types::int_type level,
      const memory::const_block data,
      const basic_gl_api<T>& glapi) const noexcept -> bool;

    template <typename T>
    auto texture_image2d(
      texture_name tex,
      texture_target target,
      gl_types::int_type level,
      const memory::const_block data,
      const basic_gl_api<T>& glapi) const noexcept -> bool;

    template <typename T>
    auto texture_image3d(
      texture_name tex,
      texture_target target,
      gl_types::int_type level,
      const memory::const_block data,
      const basic_gl_api<T>& glapi) const noexcept -> bool;

    template <typename T>
    auto texture_image(
      texture_name tex,
      texture_target target,
      gl_types::int_type level,
      const memory::const_block data,
      const basic_gl_api<T>& glapi) const noexcept -> bool {
        switch(dimensions()) {
            case 3:
                return texture_image3d(tex, target, level, data, glapi);
            case 2:
                return texture_image2d(tex, target, level, data, glapi);
            case 1:
                return texture_image1d(tex, target, level, data, glapi);
            default:
                return false;
        }
    }

    template <typename T>
    auto texture_parameters(
      texture_name tex,
      texture_target target,
      const basic_gl_api<T>& glapi) const noexcept -> bool;

private:
    template <typename T, typename P, typename V>
    auto _set_parameter(
      texture_name tex,
      texture_target target,
      const P& parameter,
      const std::optional<V>& value,
      const basic_gl_api<T>& glapi) const noexcept -> bool;

    template <typename T, typename P, typename V>
    void _add_parameter(
      texture_name tex,
      texture_target target,
      const P& parameter,
      const std::optional<V>& value,
      const basic_gl_api<T>& glapi,
      bool&) const noexcept;
};
//------------------------------------------------------------------------------
export template <typename Selector>
constexpr auto data_member_mapping(
  const std::type_identity<texture_build_info>,
  Selector) noexcept {
    using S = texture_build_info;
    return make_data_member_mapping<
      S,
      std::optional<gl_types::int_type>,
      std::optional<gl_types::int_type>,
      std::optional<gl_types::sizei_type>,
      std::optional<gl_types::sizei_type>,
      std::optional<gl_types::sizei_type>,
      std::optional<pixel_data_type>,
      std::optional<pixel_format>,
      std::optional<pixel_internal_format>,
      std::optional<texture_wrap_mode>,
      std::optional<texture_wrap_mode>,
      std::optional<texture_wrap_mode>,
      std::optional<texture_swizzle_mode>,
      std::optional<texture_swizzle_mode>,
      std::optional<texture_swizzle_mode>,
      std::optional<texture_swizzle_mode>,
      std::optional<texture_min_filter>,
      std::optional<texture_mag_filter>>(
      {"levels", &S::levels},
      {"channels", &S::channels},
      {"width", &S::width},
      {"height", &S::height},
      {"depth", &S::depth},
      {"data_type", &S::data_type},
      {"format", &S::format},
      {"iformat", &S::iformat},
      {"wrap_s", &S::wrap_s},
      {"wrap_t", &S::wrap_t},
      {"wrap_r", &S::wrap_r},
      {"swizzle_r", &S::swizzle_r},
      {"swizzle_g", &S::swizzle_g},
      {"swizzle_b", &S::swizzle_b},
      {"swizzle_a", &S::swizzle_a},
      {"min_filter", &S::min_filter},
      {"mag_filter", &S::mag_filter});
}
//------------------------------------------------------------------------------
template <typename T>
auto texture_build_info::texture_storage1d(
  texture_name tex,
  texture_target target,
  const basic_gl_api<T>& glapi) const noexcept -> bool {
    if(glapi.texture_storage1d) {
        return bool(
          glapi.texture_storage1d(tex, levels.value_or(1), *iformat, *width));
    } else if(glapi.tex_storage1d) {
        return bool(
          glapi.tex_storage1d(target, levels.value_or(1), *iformat, *width));
    } else if(glapi.tex_image1d) {
        bool result{true};
        auto level_width = *width;
        for(auto level : integer_range(levels.value_or(1))) {
            result = glapi.tex_image1d(
                       target,
                       level,
                       *iformat,
                       level_width,
                       0, // border
                       *format,
                       *data_type,
                       {}) and
                     result;
            level_width = std::max(level_width / 2, 1);
        }
        return result;
    }
    return false;
}
//------------------------------------------------------------------------------
template <typename T>
auto texture_build_info::texture_storage2d(
  texture_name tex,
  texture_target target,
  const basic_gl_api<T>& glapi) const noexcept -> bool {
    if(glapi.texture_storage2d) {
        return bool(glapi.texture_storage2d(
          tex, levels.value_or(1), *iformat, *width, *height));
    } else if(glapi.tex_storage2d) {
        return bool(glapi.tex_storage2d(
          target, levels.value_or(1), *iformat, *width, *height));
    } else if(glapi.tex_image2d) {
        bool result{true};
        auto level_width = *width;
        auto level_height = *height;
        for(auto level : integer_range(levels.value_or(1))) {
            result = glapi.tex_image2d(
                       target,
                       level,
                       *iformat,
                       level_width,
                       level_height,
                       0, // border
                       *format,
                       *data_type,
                       {}) and
                     result;
            level_width = std::max(level_width / 2, 1);
            level_height = std::max(level_height / 2, 1);
        }
        return result;
    }
    return false;
}
//------------------------------------------------------------------------------
template <typename T>
auto texture_build_info::texture_storage3d(
  texture_name tex,
  texture_target target,
  const basic_gl_api<T>& glapi) const noexcept -> bool {
    if(glapi.texture_storage3d) {
        return bool(glapi.texture_storage3d(
          tex, levels.value_or(1), *iformat, *width, *height, *depth));
    } else if(glapi.tex_storage3d) {
        return bool(glapi.tex_storage3d(
          target, levels.value_or(1), *iformat, *width, *height, *depth));
    } else if(glapi.tex_image3d) {
        bool result{true};
        auto level_width = *width;
        auto level_height = *height;
        auto level_depth = *depth;
        for(auto level : integer_range(levels.value_or(1))) {
            result = glapi.tex_image3d(
                       target,
                       level,
                       *iformat,
                       level_width,
                       level_height,
                       level_depth,
                       0, // border
                       *format,
                       *data_type,
                       {}) and
                     result;
            level_width = std::max(level_width / 2, 1);
            level_height = std::max(level_height / 2, 1);
            if(target == glapi.texture_3d) {
                level_depth = std::max(level_depth / 2, 1);
            }
        }
        return result;
    }
    return false;
}
//------------------------------------------------------------------------------
template <typename T>
auto texture_build_info::texture_image1d(
  texture_name tex,
  texture_target target,
  gl_types::int_type level,
  const memory::const_block data,
  const basic_gl_api<T>& glapi) const noexcept -> bool {
    if(glapi.texture_sub_image1d) {
        return bool(glapi.texture_sub_image1d(
          tex, level, 0, *width, *format, *data_type, data));
    } else if(glapi.tex_image1d) {
        return bool(glapi.tex_image1d(
          target,
          level,
          *iformat,
          *width,
          0, // border
          *format,
          *data_type,
          data));
    }
    return false;
}
//------------------------------------------------------------------------------
template <typename T>
auto texture_build_info::texture_image2d(
  texture_name tex,
  texture_target target,
  gl_types::int_type level,
  const memory::const_block data,
  const basic_gl_api<T>& glapi) const noexcept -> bool {
    if(glapi.texture_sub_image2d) {
        return bool(glapi.texture_sub_image2d(
          tex, level, 0, 0, *width, *height, *format, *data_type, data));
    } else if(glapi.tex_image2d) {
        return bool(glapi.tex_image2d(
          target,
          level,
          *iformat,
          *width,
          *height,
          0, // border
          *format,
          *data_type,
          data));
    }
    return false;
}
//------------------------------------------------------------------------------
template <typename T>
auto texture_build_info::texture_image3d(
  texture_name tex,
  texture_target target,
  gl_types::int_type level,
  const memory::const_block data,
  const basic_gl_api<T>& glapi) const noexcept -> bool {
    if(glapi.texture_sub_image3d) {
        return bool(glapi.texture_sub_image3d(
          tex,
          level,
          0,
          0,
          0,
          *width,
          *height,
          *depth,
          *format,
          *data_type,
          data));
    } else if(glapi.tex_image3d) {
        return bool(glapi.tex_image3d(
          target,
          level,
          *iformat,
          *width,
          *height,
          *depth,
          0, // border
          *format,
          *data_type,
          data));
    }
    return false;
}
//------------------------------------------------------------------------------
template <typename T, typename P, typename V>
auto texture_build_info::_set_parameter(
  texture_name tex,
  texture_target target,
  const P& parameter,
  const std::optional<V>& value,
  const basic_gl_api<T>& glapi) const noexcept -> bool {
    if(value) {
        if(glapi.texture_parameter_i) {
            return glapi.texture_parameter_i(tex, parameter, *value);
        } else if(glapi.tex_parameter_i) {
            return glapi.tex_parameter_i(target, parameter, *value);
        } else {
            return false;
        }
    }
    return true;
}
//------------------------------------------------------------------------------
template <typename T, typename P, typename V>
void texture_build_info::_add_parameter(
  texture_name tex,
  texture_target target,
  const P& parameter,
  const std::optional<V>& value,
  const basic_gl_api<T>& glapi,
  bool& result) const noexcept {
    result = _set_parameter(tex, target, parameter, value, glapi) and result;
}
//------------------------------------------------------------------------------
template <typename T>
auto texture_build_info::texture_parameters(
  texture_name tex,
  texture_target target,
  const basic_gl_api<T>& glapi) const noexcept -> bool {
    bool result{true};
    const auto& GL = glapi.constants();
    _add_parameter(tex, target, GL.texture_wrap_s, wrap_s, glapi, result);
    _add_parameter(tex, target, GL.texture_wrap_t, wrap_t, glapi, result);
    _add_parameter(tex, target, GL.texture_wrap_r, wrap_r, glapi, result);
    _add_parameter(tex, target, GL.texture_swizzle_r, swizzle_r, glapi, result);
    _add_parameter(tex, target, GL.texture_swizzle_g, swizzle_g, glapi, result);
    _add_parameter(tex, target, GL.texture_swizzle_b, swizzle_b, glapi, result);
    _add_parameter(tex, target, GL.texture_swizzle_a, swizzle_a, glapi, result);
    _add_parameter(
      tex, target, GL.texture_min_filter, min_filter, glapi, result);
    _add_parameter(
      tex, target, GL.texture_mag_filter, mag_filter, glapi, result);
    return result;
}
//------------------------------------------------------------------------------
// texture image build info
//------------------------------------------------------------------------------
export struct texture_image_build_info {
    std::optional<gl_types::int_type> level;
    std::optional<gl_types::int_type> channels;
    std::optional<gl_types::int_type> x_offs;
    std::optional<gl_types::int_type> y_offs;
    std::optional<gl_types::int_type> z_offs;
    std::optional<gl_types::sizei_type> width;
    std::optional<gl_types::sizei_type> height;
    std::optional<gl_types::sizei_type> depth;
    std::optional<pixel_data_type> data_type;
    std::optional<pixel_format> format;
    std::optional<pixel_internal_format> iformat;
};

export template <typename Selector>
constexpr auto data_member_mapping(
  const std::type_identity<texture_image_build_info>,
  Selector) noexcept {
    using S = texture_image_build_info;
    return make_data_member_mapping<
      S,
      std::optional<gl_types::int_type>,
      std::optional<gl_types::int_type>,
      std::optional<gl_types::int_type>,
      std::optional<gl_types::int_type>,
      std::optional<gl_types::int_type>,
      std::optional<gl_types::sizei_type>,
      std::optional<gl_types::sizei_type>,
      std::optional<gl_types::sizei_type>,
      std::optional<pixel_data_type>,
      std::optional<pixel_format>,
      std::optional<pixel_internal_format>>(
      {"level", &S::level},
      {"channels", &S::channels},
      {"x_offs", &S::x_offs},
      {"y_offs", &S::y_offs},
      {"z_offs", &S::z_offs},
      {"width", &S::width},
      {"height", &S::height},
      {"depth", &S::depth},
      {"data_type", &S::data_type},
      {"format", &S::format},
      {"iformat", &S::iformat});
}
//------------------------------------------------------------------------------
export auto make_texture_builder(
  const gl_api& glapi,
  memory::buffer_pool&,
  texture_name tex,
  texture_target target) noexcept -> unique_holder<valtree::object_builder>;
//------------------------------------------------------------------------------
export template <typename T>
auto build_from_resource(
  main_ctx& ctx,
  const basic_gl_api<T>& glapi,
  const embedded_resource& res,
  texture_name tex,
  texture_target target) noexcept -> bool {
    return res.build(
      ctx, make_texture_builder(glapi, ctx.buffers(), tex, target));
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

