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

struct vertex_attrib_binding_intf : interface<vertex_attrib_binding_intf> {

    virtual auto attrib_count() -> span_size_t = 0;

    virtual auto attrib_variant(span_size_t index)
      -> shapes::vertex_attrib_variant = 0;

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

class vertex_attrib_bindings {
public:
    static auto make_default(const shape_generator& shape)
      -> vertex_attrib_bindings {
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

    vertex_attrib_bindings(const shape_generator& shape)
      : vertex_attrib_bindings{make_default(shape)} {}

    auto attrib_count() const -> span_size_t {
        return _pimpl->attrib_count();
    }

    auto attrib_variant(span_size_t index) const
      -> shapes::vertex_attrib_variant {
        EAGINE_ASSERT(index < attrib_count());
        return _pimpl->attrib_variant(index);
    }

    auto location(shapes::vertex_attrib_variant vav) -> vertex_attrib_location {
        return _pimpl->location(vav);
    }

private:
    std::shared_ptr<vertex_attrib_binding_intf> _pimpl;
};

} // namespace eagine::oglplus

#endif
