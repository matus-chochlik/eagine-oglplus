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
import <optional>;

namespace eagine {
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_data_type>,
  const default_selector_t) noexcept -> std::optional<oglplus::pixel_data_type>;
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_internal_format>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::pixel_internal_format>;
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_format>,
  const default_selector_t) noexcept -> std::optional<oglplus::pixel_format>;
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_target>,
  const default_selector_t) noexcept -> std::optional<oglplus::texture_target>;
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_min_filter>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::texture_min_filter>;
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_mag_filter>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::texture_mag_filter>;
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_swizzle_mode>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::texture_swizzle_mode>;
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<oglplus::shader_type>,
  const default_selector_t) noexcept -> std::optional<oglplus::shader_type>;
//------------------------------------------------------------------------------
} // namespace eagine
