/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:resources;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.reflection;
import eagine.core.value_tree;
import :config;
import :objects;
import :enum_types;
import <memory>;
import <optional>;

namespace eagine::oglplus {
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
};

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
      std::optional<pixel_internal_format>>(
      {"levels", &S::levels},
      {"channels", &S::channels},
      {"width", &S::width},
      {"height", &S::height},
      {"depth", &S::depth},
      {"data_type", &S::data_type},
      {"format", &S::format},
      {"iformat", &S::iformat});
}
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
  memory::buffer_pool&,
  texture_name tex,
  texture_target target) noexcept -> std::unique_ptr<valtree::object_builder>;
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

