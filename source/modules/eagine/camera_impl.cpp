/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module eagine.oglplus;
import eagine.core.types;
import eagine.core.math;
import eagine.core.valid_if;
import eagine.core.units;
import std;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
auto orbiting_camera::target_to_camera_direction() const noexcept -> vec3 {
    return to_cartesian(unit_spherical_coordinate(azimuth(), elevation()));
}
//------------------------------------------------------------------------------
auto orbiting_camera::target_plane_point(
  const float_type ndcx,
  const float_type ndcy,
  const float_type aspect) const noexcept -> optionally_valid<vec3> {
    using math::inverse_matrix;
    using math::multiply;

    const auto mat = matrix(aspect);

    if(auto inv = inverse_matrix(mat)) {
        auto ndct = multiply(mat, vec4(target(), 1.F));
        auto ndc = vec4{ndcx * ndct.w(), ndcy * ndct.w(), ndct.z(), ndct.w()};
        return {vec3(math::multiply(inv.value(), ndc)), true};
    }
    return {};
}
//------------------------------------------------------------------------------
auto orbiting_camera::pointer_ray(
  const float_type ndcx,
  const float_type ndcy,
  const float_type aspect) const noexcept -> optionally_valid<line> {
    if(const auto ptr{target_plane_point(ndcx, ndcy, aspect)}) {
        return {line(position(), ptr.value_anyway() - position()), true};
    }
    return {};
}
//------------------------------------------------------------------------------
auto orbiting_camera::grab_sphere_radius() const noexcept -> float_type {
    const auto orb = orbit();
    return math::minimum(orb * tan(fov() * 0.5F), orb * 0.75F);
}
//------------------------------------------------------------------------------
auto orbiting_camera::grab_sphere() const noexcept -> sphere {
    return {target(), grab_sphere_radius()};
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
