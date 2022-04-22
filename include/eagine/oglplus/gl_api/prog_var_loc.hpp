/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_GL_API_PROG_VAR_LOC_HPP
#define EAGINE_OGLPLUS_GL_API_PROG_VAR_LOC_HPP

#include "config.hpp"
#include <eagine/c_api/parameter_map.hpp>
#include <eagine/identifier.hpp>
#include <array>

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Class wrapping GL shader program variable location.
/// @ingroup gl_api_wrap
template <identifier_t TagId>
class prog_var_location {
    using int_type = gl_types::int_type;
    using uint_type = gl_types::uint_type;

public:
    /// @brief Default constructor.
    /// @post !is_active()
    constexpr prog_var_location() noexcept = default;

    /// @brief Explicit location initialization.
    explicit constexpr prog_var_location(const int_type init) noexcept
      : _location{init} {}

    /// @brief Indicates if this instance wraps an active program variable.
    auto is_active() const noexcept -> bool {
        return _location >= 0;
    }

    /// @brief Indicates if this instance wraps an active program variable.
    /// @see is_active
    explicit constexpr operator bool() const noexcept {
        return is_active();
    }

    /// @brief Returns the location value.
    constexpr auto location() const noexcept -> int_type {
        return _location;
    }

    constexpr auto index() const noexcept -> uint_type {
        if(_location < 0) {
#ifdef GL_INVALID_INDEX
            return GL_INVALID_INDEX;
#endif
        }
        return uint_type(_location);
    }

    /// @brief Explicit conversion to the variable location value.
    explicit constexpr operator int_type() const noexcept {
        return _location;
    }

    /// @brief Equality comparison (compares the location numeric value).
    friend constexpr auto operator==(
      const prog_var_location a,
      const prog_var_location b) noexcept {
        return a._location == b._location;
    }

    /// @brief Nonequality comparison (compares the location numeric value).
    friend constexpr auto operator!=(
      const prog_var_location a,
      const prog_var_location b) noexcept {
        return a._location != b._location;
    }

    /// @brief Less-than comparison (compares the location numeric value).
    friend constexpr auto operator<(
      const prog_var_location a,
      const prog_var_location b) noexcept {
        return a._location < b._location;
    }

private:
    int_type _location{-1};
};
//------------------------------------------------------------------------------
/// @brief Alias for generic shader program resource location wrapper.
/// @ingroup gl_api_wrap
/// @see vertex_attrib_location
/// @see uniform_location
/// @see subroutine_uniform_location
/// @see subroutine_location
/// @see frag_data_location
/// @see uniform_block_index
/// @see shader_storage_block_index
using program_resource_location = prog_var_location<EAGINE_ID_V(Resource)>;

/// @brief Alias for program vertex attribute location wrapper.
/// @ingroup gl_api_wrap
/// @see program_resource_location
/// @see uniform_location
/// @see subroutine_uniform_location
/// @see subroutine_location
/// @see frag_data_location
/// @see uniform_block_index
/// @see shader_storage_block_index
using vertex_attrib_location = prog_var_location<EAGINE_ID_V(VertexAttr)>;

/// @brief Alias for shader program uniform location wrapper.
/// @ingroup gl_api_wrap
/// @see program_resource_location
/// @see vertex_attrib_location
/// @see subroutine_uniform_location
/// @see subroutine_location
/// @see frag_data_location
/// @see uniform_block_index
/// @see shader_storage_block_index
using uniform_location = prog_var_location<EAGINE_ID_V(Uniform)>;

/// @brief Alias for shader program subroutine uniform location wrapper.
/// @ingroup gl_api_wrap
/// @see program_resource_location
/// @see vertex_attrib_location
/// @see uniform_location
/// @see subroutine_location
/// @see frag_data_location
/// @see uniform_block_index
/// @see shader_storage_block_index
using subroutine_uniform_location = prog_var_location<EAGINE_ID_V(SubrtUnfrm)>;

/// @brief Alias for shader program subroutine location wrapper.
/// @ingroup gl_api_wrap
/// @see program_resource_location
/// @see vertex_attrib_location
/// @see uniform_location
/// @see subroutine_uniform_location
/// @see frag_data_location
/// @see uniform_block_index
/// @see shader_storage_block_index
using subroutine_location = prog_var_location<EAGINE_ID_V(Subroutine)>;

/// @brief Alias for shader program fragment data variable location wrapper.
/// @ingroup gl_api_wrap
/// @see program_resource_location
/// @see vertex_attrib_location
/// @see uniform_location
/// @see subroutine_uniform_location
/// @see subroutine_location
/// @see uniform_block_index
/// @see shader_storage_block_index
using frag_data_location = prog_var_location<EAGINE_ID_V(FragData)>;

/// @brief Alias for shader program uniform block location wrapper.
/// @ingroup gl_api_wrap
/// @see program_resource_location
/// @see vertex_attrib_location
/// @see uniform_location
/// @see subroutine_uniform_location
/// @see subroutine_location
/// @see frag_data_location
/// @see shader_storage_block_index
using uniform_block_index = prog_var_location<EAGINE_ID_V(UniformBlk)>;

/// @brief Alias for program shader storage block location wrapper.
/// @ingroup gl_api_wrap
/// @see program_resource_location
/// @see vertex_attrib_location
/// @see uniform_location
/// @see subroutine_uniform_location
/// @see subroutine_location
/// @see frag_data_location
/// @see uniform_block_index
using shader_storage_block_index = prog_var_location<EAGINE_ID_V(ShdrStrBlk)>;
//------------------------------------------------------------------------------
template <std::size_t N = 1U>
struct subroutine_bindings;

template <>
struct subroutine_bindings<1U> {
    constexpr subroutine_bindings(
      const subroutine_uniform_location su,
      const subroutine_location s) noexcept
      : _bindings{{{su, s}}} {}

    std::array<std::tuple<subroutine_uniform_location, subroutine_location>, 1U>
      _bindings;
};

template <std::size_t N>
struct subroutine_bindings {
public:
    constexpr subroutine_bindings(
      const subroutine_bindings<N - 1U>& head,
      const subroutine_uniform_location su,
      const subroutine_location s) noexcept
      : _bindings{concat(std::make_index_sequence<N - 1U>{}, head, {su, s})} {}

    constexpr subroutine_bindings(
      const subroutine_bindings<N - 1U>& head,
      const subroutine_bindings<1U>& tail) noexcept
      : _bindings{
          concat(std::make_index_sequence<N - 1U>{}, head, tail._bindings)} {}

private:
    template <std::size_t... I>
    static constexpr auto _concat(
      const std::index_sequence<I...>,
      const subroutine_bindings<N - 1U>& head,
      const std::tuple<subroutine_uniform_location, subroutine_location>
        tail) noexcept -> std::
      array<std::tuple<subroutine_uniform_location, subroutine_location>, N> {
        return {{head[I]..., tail}};
    }

    std::array<std::tuple<subroutine_uniform_location, subroutine_location>, N>
      _bindings;
};

static inline auto operator/(
  const subroutine_uniform_location su,
  const subroutine_location s) noexcept -> subroutine_bindings<> {
    return {su, s};
}

template <std::size_t N>
static inline auto operator+(
  const subroutine_bindings<N>& head,
  const subroutine_bindings<1U>& tail) noexcept -> subroutine_bindings<N + 1U> {
    return {head, tail};
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

namespace eagine::c_api {

template <std::size_t I, identifier_t TagId>
struct make_arg_map<
  I,
  I,
  oglplus::gl_types::uint_type,
  oglplus::prog_var_location<TagId>> : get_index_map<I, I> {};

template <std::size_t CI, std::size_t CppI, identifier_t TagId>
struct make_arg_map<
  CI,
  CppI,
  oglplus::gl_types::uint_type,
  oglplus::prog_var_location<TagId>> : get_index_map<CI, CppI> {};

} // namespace eagine::c_api

#endif // EAGINE_OGLPLUS_GL_API_PROG_VAR_LOC_HPP
