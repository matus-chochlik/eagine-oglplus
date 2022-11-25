/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

module eagine.oglplus;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.string;
import <optional>;

namespace eagine {
//------------------------------------------------------------------------------
auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_data_type>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::pixel_data_type> {
    using R = oglplus::pixel_data_type;
    if(src == "unsigned_byte") {
        return R{0x1401};
    } else if(src == "unsigned_short") {
        return R{0x1403};
    } else if(src == "unsigned_int") {
        return R{0x1405};
    } else if(src == "float") {
        return R{0x1406};
    }
    // TODO
    return {};
}
//------------------------------------------------------------------------------
auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_internal_format>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::pixel_internal_format> {
    using R = oglplus::pixel_internal_format;
    if(src == "rgba8") {
        return R{0x8058};
    } else if(src == "rgb8") {
        return R{0x8051};
    } else if(src == "r8") {
        return R{0x8229};
    } else if(src == "r8ui") {
        return R{0x8232};
    }
    // TODO
    return {};
}
//------------------------------------------------------------------------------
auto from_string(
  const string_view src,
  const std::type_identity<oglplus::pixel_format>,
  const default_selector_t) noexcept -> std::optional<oglplus::pixel_format> {
    using R = oglplus::pixel_format;
    if(src == "rgba") {
        return R{0x1908};
    } else if(src == "rgb") {
        return R{0x1907};
    } else if(src == "red") {
        return R{0x1903};
    } else if(src == "red_integer") {
        return R{0x8D94};
    }
    // TODO
    return {};
}
//------------------------------------------------------------------------------
auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_target>,
  const default_selector_t) noexcept -> std::optional<oglplus::texture_target> {
    using R = oglplus::texture_target;
    if(src == "texture_2d") {
        return R{0x0DE1};
    } else if(src == "texture_2d_array") {
        return R{0x8C1A};
    } else if(src == "texture_3d") {
        return R{0x806F};
    } else if(src == "texture_1d") {
        return R{0x0DE0};
    } else if(src == "texture_1d_array") {
        return R{0x8C18};
    } else if(src == "texture_cube_map") {
        return R{0x8513};
    } else if(src == "texture_cube_map_positive_x") {
        return R{0x8515};
    } else if(src == "texture_cube_map_negative_x") {
        return R{0x8516};
    } else if(src == "texture_cube_map_positive_y") {
        return R{0x8517};
    } else if(src == "texture_cube_map_negative_y") {
        return R{0x8518};
    } else if(src == "texture_cube_map_positive_z") {
        return R{0x8519};
    } else if(src == "texture_cube_map_negative_z") {
        return R{0x851A};
    }
    // TODO
    return {};
}
//------------------------------------------------------------------------------
auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_min_filter>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::texture_min_filter> {
    using R = oglplus::texture_min_filter;
    if(src == "linear") {
        return R{0x2601};
    } else if(src == "nearest") {
        return R{0x2600};
    } else if(src == "nearest_mipmap_nearest") {
        return R{0x2700};
    } else if(src == "linear_mipmap_nearest") {
        return R{0x2701};
    } else if(src == "nearest_mipmap_linear") {
        return R{0x2702};
    } else if(src == "linear_mipmap_linear") {
        return R{0x2703};
    }
    // TODO
    return {};
}
//------------------------------------------------------------------------------
auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_mag_filter>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::texture_mag_filter> {
    using R = oglplus::texture_mag_filter;
    if(src == "linear") {
        return R{0x2601};
    } else if(src == "nearest") {
        return R{0x2600};
    }
    // TODO
    return {};
}
//------------------------------------------------------------------------------
auto from_string(
  const string_view src,
  const std::type_identity<oglplus::texture_swizzle_mode>,
  const default_selector_t) noexcept
  -> std::optional<oglplus::texture_swizzle_mode> {
    using R = oglplus::texture_swizzle_mode;
    if(src == "red") {
        return R{0x1903};
    } else if(src == "green") {
        return R{0x1904};
    } else if(src == "blue") {
        return R{0x1905};
    } else if(src == "alpha") {
        return R{0x1906};
    }
    // TODO
    return {};
}
//------------------------------------------------------------------------------
auto from_string(
  const string_view src,
  const std::type_identity<oglplus::shader_type>,
  const default_selector_t) noexcept -> std::optional<oglplus::shader_type> {
    using R = oglplus::shader_type;
    if((src == "fragment") || (src == "fragment_shader")) {
        return R{0x8B30};
    } else if((src == "vertex") || (src == "vertex_shader")) {
        return R{0x8B31};
    } else if((src == "geometry") || (src == "geometry_shader")) {
        return R{0x8DD9};
    } else if((src == "compute") || (src == "compute_shader")) {
        return R{0x91B9};
    } else if((src == "tess_evaluation") || (src == "tess_evaluation_shader")) {
        return R{0x8E87};
    } else if((src == "tess_control") || (src == "tess_control_shader")) {
        return R{0x8E88};
    }
    // TODO
    return {};
}
//------------------------------------------------------------------------------
} // namespace eagine
