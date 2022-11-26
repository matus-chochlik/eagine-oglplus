/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:from_string;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.string;
import :enum_types;
import :constants;
import <optional>;

namespace eagine {
//------------------------------------------------------------------------------
template <typename EnumClass>
auto gl_enum_from_string(
  const string_view src,
  std::type_identity<EnumClass>) noexcept -> std::optional<EnumClass> {
    if(const auto found{oglplus::gl_enum_by_name(src)}) {
        if(const auto conv{convert_if_fits<EnumClass>(extract(found))}) {
            return {extract(conv)};
        }
    }
    return {};
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_data_type> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_internal_format> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_format> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_target> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_min_filter> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_mag_filter> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_wrap_mode> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_swizzle_mode> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::shader_type> tid,
  const default_selector_t) noexcept {
    return gl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
} // namespace eagine
