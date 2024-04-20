/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:from_string;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.string;
import eagine.core.valid_if;
import :enum_types;
import :constants;

namespace eagine {
//------------------------------------------------------------------------------
template <typename EnumClass>
auto gl_enum_from_string(
  const string_view src,
  std::type_identity<EnumClass> = {}) noexcept -> optionally_valid<EnumClass> {
    if(const auto found{oglplus::gl_enum_by_name(src)}) {
        if(const auto conv{convert_if_fits<EnumClass>(*found)}) {
            return {*conv, true};
        }
    }
    return {};
}
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::buffer_target> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::buffer_target>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::buffer_usage> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::buffer_usage>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::capability> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::capability>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::object_type> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::object_type>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::pixel_data_type> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::pixel_data_type>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::pixel_internal_format> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::pixel_internal_format>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::pixel_format> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::pixel_format>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::texture_target> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::texture_target>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::texture_min_filter> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::texture_min_filter>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::texture_mag_filter> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::texture_mag_filter>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::texture_wrap_mode> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::texture_wrap_mode>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::texture_swizzle_mode> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::texture_swizzle_mode>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::shader_type> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::shader_type>{});
    }
};
//------------------------------------------------------------------------------
export template <>
struct string_traits<oglplus::true_false> {
    static auto from(const string_view src) noexcept {
        return gl_enum_from_string(
          src, std::type_identity<oglplus::true_false>{});
    }
};
//------------------------------------------------------------------------------
} // namespace eagine
