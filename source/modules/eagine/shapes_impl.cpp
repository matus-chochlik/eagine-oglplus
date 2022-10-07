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
import eagine.shapes;
import <iostream>;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
auto make_default_vertex_attrib_bindings(const shape_generator& shape)
  -> std::shared_ptr<vertex_attrib_binding_intf> {
    return std::make_shared<default_vertex_attrib_bindings>(shape);
}
//------------------------------------------------------------------------------
auto make_default_vertex_attrib_bindings(
  std::initializer_list<shapes::vertex_attrib_variant> vavs)
  -> std::shared_ptr<vertex_attrib_binding_intf> {
    return std::make_shared<default_vertex_attrib_bindings>(vavs);
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
