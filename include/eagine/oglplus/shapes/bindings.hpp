/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef EAGINE_OGLPLUS_SHAPES_BINDINGS_HPP
#define EAGINE_OGLPLUS_SHAPES_BINDINGS_HPP

#include "../gl_api/prog_var_loc.hpp"
#include "generator.hpp"
#include <memory>
#include <vector>

namespace eagine::oglplus {

/// @brief Interface for bindings between attribute variant and vertex array index.
/// @ingroup shapes
/// @see vertex_attrib_bindings
/// @note Do not use directly. Use vertex_attrib_bindings instead.
struct vertex_attrib_binding_intf : interface<vertex_attrib_binding_intf> {

    /// @brief Returns the number of attributes in the binding.
    /// @see attrib_variant
    virtual auto attrib_count() -> span_size_t = 0;

    /// @brief Returns the attribute variant bound to specified index.
    /// @see attrib_count
    /// @see location
    /// @pre index < attrib_count()
    virtual auto attrib_variant(span_size_t index)
      -> shapes::vertex_attrib_variant = 0;

    /// @brief Returns the index at which the specified attribute variant is bound.
    /// @see attrib_variant
    virtual auto location(shapes::vertex_attrib_variant vav)
      -> vertex_attrib_location = 0;
};

class default_vertex_attrib_bindings : public vertex_attrib_binding_intf {
public:
    default_vertex_attrib_bindings() noexcept = default;

    default_vertex_attrib_bindings(const shape_generator& shape) {
        shape.for_each_attrib(
          {construct_from, [this](const auto attribs, const auto info) {
               if(attribs.has(info.enumerator)) {
                   _bindings.emplace_back(info.enumerator, 0);
               }
           }});
    }

    default_vertex_attrib_bindings(
      std::initializer_list<shapes::vertex_attrib_variant> vavs)
      : _bindings{vavs.begin(), vavs.end()} {}

    auto add(shapes::vertex_attrib_variant vav) -> auto& {
        _bindings.push_back(vav);
        return *this;
    }

    auto attrib_count() -> span_size_t final {
        return span_size(_bindings.size());
    }

    auto attrib_variant(span_size_t index)
      -> shapes::vertex_attrib_variant final {
        return _bindings[integer(index)];
    }

    auto location(shapes::vertex_attrib_variant vav)
      -> vertex_attrib_location final {
        for(const integer i : integer_range(_bindings.size())) {
            const auto& entry = _bindings[i];
            if(entry == vav) {
                return vertex_attrib_location{i};
            }
        }
        return vertex_attrib_location{0};
    }

private:
    std::vector<shapes::vertex_attrib_variant> _bindings;
};

/// @brief Class that specifies bindings between attribute variant and array index.
/// @ingroup shapes
/// @see generator
/// @see geometry
class vertex_attrib_bindings {
public:
    static auto make(const shape_generator& shape) -> vertex_attrib_bindings {
        return {std::make_shared<default_vertex_attrib_bindings>(shape)};
    }

    static auto make(std::initializer_list<shapes::vertex_attrib_variant> vavs)
      -> vertex_attrib_bindings {
        return {std::make_shared<default_vertex_attrib_bindings>(vavs)};
    }

    vertex_attrib_bindings(
      std::shared_ptr<vertex_attrib_binding_intf> pimpl) noexcept
      : _pimpl{std::move(pimpl)} {
        EAGINE_ASSERT(_pimpl);
    }

    /// @brief Constructor matching supported attributes from a shape generator.
    vertex_attrib_bindings(const shape_generator& shape)
      : vertex_attrib_bindings{make(shape)} {}

    /// @brief Constructor matching supported attributes from a shape generator.
    vertex_attrib_bindings(
      std::initializer_list<shapes::vertex_attrib_variant> vavs)
      : vertex_attrib_bindings{make(vavs)} {}

    /// @brief Returns the number of attributes in the binding.
    /// @see attrib_variant
    auto attrib_count() const -> span_size_t {
        return _pimpl->attrib_count();
    }

    /// @brief Returns the attribute variant bound to specified index.
    /// @see attrib_count
    /// @see location
    /// @pre index < attrib_count()
    auto attrib_variant(span_size_t index) const
      -> shapes::vertex_attrib_variant {
        EAGINE_ASSERT(index < attrib_count());
        return _pimpl->attrib_variant(index);
    }

    /// @brief Returns the attribute kind bits for all attributes in this binding.
    auto attrib_kinds() const -> shapes::vertex_attrib_kinds {
        shapes::vertex_attrib_kinds result;
        for(const auto i : integer_range(attrib_count())) {
            result.set(attrib_variant(i).attribute());
        }
        return result;
    }

    /// @brief Returns the index at which the specified attribute variant is bound.
    /// @see attrib_variant
    auto location(shapes::vertex_attrib_variant vav) -> vertex_attrib_location {
        return _pimpl->location(vav);
    }

    /// @brief Returns the index at which the position variant is bound.
    /// @see location
    auto position_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::position, idx});
    }

    /// @brief Returns the index at which the normal variant is bound.
    /// @see location
    auto normal_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::normal, idx});
    }

    /// @brief Returns the index at which the tangent variant is bound.
    /// @see location
    auto tangent_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::tangent, idx});
    }

    /// @brief Returns the index at which the bitangent variant is bound.
    /// @see location
    auto bitangent_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::bitangent, idx});
    }

    /// @brief Returns the index at which the box_coord variant is bound.
    /// @see location
    auto box_coord_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::box_coord, idx});
    }

    /// @brief Returns the index at which the face_coord variant is bound.
    /// @see location
    auto face_coord_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::face_coord, idx});
    }

    /// @brief Returns the index at which the wrap_coord variant is bound.
    /// @see location
    auto wrap_coord_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::wrap_coord, idx});
    }

    /// @brief Returns the index at which the color variant is bound.
    /// @see location
    auto color_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::color, idx});
    }

    /// @brief Returns the index at which the weight variant is bound.
    /// @see location
    auto weight_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::weight, idx});
    }

    /// @brief Returns the index at which the occlusion variant is bound.
    /// @see location
    auto occlusion_loc(span_size_t idx = 0) -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::occlusion, idx});
    }

private:
    std::shared_ptr<vertex_attrib_binding_intf> _pimpl;
};

} // namespace eagine::oglplus

#endif
