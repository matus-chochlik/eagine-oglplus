/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_CAMERA_HPP
#define EAGINE_OGLPLUS_CAMERA_HPP

#include "math/interpolate.hpp"
#include "math/matrix_ctrs.hpp"
#include "math/primitives.hpp"
#include "math/sign.hpp"
#include "math/vector.hpp"
#include <eagine/units/common.hpp>
#include <eagine/valid_if/positive.hpp>

namespace eagine::oglplus {

/// @brief Class representing a camera orbiting around its target.
/// @ingroup gl_utils
class orbiting_camera {
public:
    /// @brief Sets the target position.
    auto set_target(const vec3 target) noexcept -> auto& {
        _target = target;
        return *this;
    }

    /// @brief Sets the y-axis FOV angle.
    auto set_fov(const radians_t<float> angle) noexcept -> auto& {
        _fov = angle;
        return *this;
    }

    /// @brief Sets the distance of the near plane.
    auto set_near(valid_if_positive<float> dist) noexcept -> auto& {
        _near = dist.value();
        return *this;
    }

    /// @brief Sets the distance of the far plane.
    auto set_far(valid_if_positive<float> dist) noexcept -> auto& {
        _far = dist.value();
        return *this;
    }

    /// @brief Set minimal orbit value.
    auto set_orbit_min(valid_if_positive<float> orbit) noexcept -> auto& {
        _orbit_min = orbit.value();
        return *this;
    }

    /// @brief Set maximal orbit value.
    auto set_orbit_max(valid_if_positive<float> orbit) noexcept -> auto& {
        _orbit_max = orbit.value();
        return *this;
    }

    /// @brief Set the factor for calculating the orbit between min and max.
    auto set_orbit_factor(const float factor) noexcept -> auto& {
        _orbit_factor = factor;
        return *this;
    }

    /// @brief Sets the azimuth angle (longitude)
    auto set_azimuth(const radians_t<float> turns) noexcept -> auto& {
        _turns = turns;
        return *this;
    }

    /// @brief Sets the elevation angle (latitude)
    auto set_elevation(const radians_t<float> pitch) noexcept -> auto& {
        _pitch = pitch;
        return *this;
    }

    /// @brief Returns the near distance.
    /// @see far
    /// @see midpoint
    auto near() const noexcept -> float {
        return _near;
    }

    /// @brief Returns the far distance.
    /// @see near
    /// @see midpoint
    /// @see skybox_distance
    auto far() const noexcept -> float {
        return _far;
    }

    /// @brief Returns the midpoint distance between near and far range.
    /// @see near
    /// @see far
    /// @see skybox_distance
    auto midpoint() const noexcept -> float {
        return (near() + far()) * 0.5F;
    }

    /// @brief Returns the y-axis FOV angle
    auto fov() const noexcept -> radians_t<float> {
        return _fov;
    }

    /// @brief Returns the orbit altitude value.
    /// @see azimuth
    /// @see elevation
    /// @see near
    /// @see far
    auto orbit() const noexcept -> float {
        return smooth_lerp(_orbit_min, _orbit_max, _orbit_factor);
    }

    /// @brief Returns the prefered distance to the farthest part of a skybox.
    /// @see near
    /// @see midpoint
    /// @see far
    /// @see orbit
    auto skybox_distance() const noexcept -> float {
        return far() - orbit();
    }

    /// @brief Returns the azimuth angle (longitude).
    /// @see orbit
    /// @see elevation
    auto azimuth() const noexcept -> radians_t<float> {
        return _turns;
    }

    /// @brief Returns the elevation angle (latitude).
    /// @see orbit
    /// @see azimuth
    auto elevation() const noexcept -> radians_t<float> {
        return _pitch;
    }

    /// @brief Returns the target position.
    /// @see position
    auto target() const noexcept -> vec3 {
        return _target;
    }

    /// @brief Returns the target-to-camera direction vector.
    /// @see camera_to_target_direction
    auto target_to_camera_direction() const noexcept -> vec3;

    /// @brief Returns the camera-to-target direction vector.
    /// @see target_to_camera_direction
    auto camera_to_target_direction() const noexcept -> vec3 {
        return -target_to_camera_direction();
    }

    /// @brief Returns the position of the camera.
    /// @see target
    auto position() const noexcept -> vec3 {
        return target() + target_to_camera_direction() * orbit();
    }

    auto perspective_matrix_ctr(const float aspect) const noexcept {
        return matrix_perspective::y(_fov, aspect, _near, _far);
    }

    /// @brief Returns the perspective matrix for the given aspect ratio.
    auto perspective_matrix(const float aspect) const noexcept {
        return perspective_matrix_ctr(aspect)();
    }

    auto transform_matrix_ctr() const noexcept {
        return matrix_orbiting_y_up(_target, orbit(), azimuth(), elevation());
    }

    /// @brief Returns the camera transformation matrix.
    auto transform_matrix() const noexcept {
        return transform_matrix_ctr()();
    }

    /// @brief Returns the camera matrix (perspective * projection).
    auto matrix(const float aspect) const noexcept {
        return perspective_matrix_ctr(aspect) * transform_matrix_ctr();
    }

    /// @brief Returns the 3D position of a point (in NDC) on the target plane.
    auto target_plane_point(
      const float ndcx,
      const float ndcy,
      const float aspect) const noexcept -> optionally_valid<vec3>;

    /// @brief Returns a ray from the camera through a point on the target plane.
    auto pointer_ray(const float ndcx, const float ndcy, const float aspect)
      const noexcept -> optionally_valid<line>;

    auto grab_sphere_radius() const noexcept -> float;
    auto grab_sphere() const noexcept -> sphere;

private:
    vec3 _target{};
    radians_t<float> _fov{right_angle_()};

    float _near{0.5F};
    float _far{10.F};

protected:
    radians_t<float> _turns{};
    radians_t<float> _pitch{};

    float _orbit_min{1.5F};
    float _orbit_max{5.5F};
    float _orbit_factor = 0.50F;
};

} // namespace eagine::oglplus

#if !EAGINE_OGLPLUS_LIBRARY || defined(EAGINE_IMPLEMENTING_OGLPLUS_LIBRARY)
#include <eagine/oglplus/camera.inl>
#endif

#endif
