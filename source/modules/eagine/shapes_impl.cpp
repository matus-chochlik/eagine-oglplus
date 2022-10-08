/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include <cassert>

module eagine.oglplus;
import eagine.core.types;
import eagine.core.memory;
import eagine.shapes;
import <iostream>;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
// shape_generator
//------------------------------------------------------------------------------
void shape_generator::attrib_data(
  const shapes::vertex_attrib_variant vav,
  memory::block data) const {
    using shapes::attrib_data_type;

    switch(_gen->attrib_type(vav)) {
        case attrib_data_type::float_:
            _gen->attrib_values(
              vav,
              accommodate(data, std::type_identity<gl_types::float_type>()));
            break;
        case attrib_data_type::ubyte:
            _gen->attrib_values(
              vav,
              accommodate(data, std::type_identity<gl_types::ubyte_type>()));
            break;
        case attrib_data_type::uint_16:
            _gen->attrib_values(
              vav,
              accommodate(data, std::type_identity<gl_types::ushort_type>()));
            break;
        case attrib_data_type::uint_32:
            _gen->attrib_values(
              vav,
              accommodate(data, std::type_identity<gl_types::uint_type>()));
            break;
        case attrib_data_type::int_16:
            _gen->attrib_values(
              vav,
              accommodate(data, std::type_identity<gl_types::short_type>()));
            break;
        case attrib_data_type::int_32:
            _gen->attrib_values(
              vav, accommodate(data, std::type_identity<gl_types::int_type>()));
            break;
        case attrib_data_type::none:
            break;
    }
}
//------------------------------------------------------------------------------
void shape_generator::index_data(
  const shapes::drawing_variant dv,
  memory::block data) const {
    using shapes::index_data_type;

    switch(_gen->index_type()) {
        case index_data_type::unsigned_32:
            _gen->indices(
              dv, accommodate(data, std::type_identity<gl_types::uint_type>()));
            break;
        case index_data_type::unsigned_16:
            _gen->indices(
              dv,
              accommodate(data, std::type_identity<gl_types::ushort_type>()));
            break;
        case index_data_type::unsigned_8:
            _gen->indices(
              dv,
              accommodate(data, std::type_identity<gl_types::ubyte_type>()));
            break;
        case index_data_type::none:
            break;
    }
}
//------------------------------------------------------------------------------
// default_vertex_attrib_bindings
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
// geometry
//------------------------------------------------------------------------------
auto geometry::operator=(geometry&& that) noexcept -> geometry& {
    assert(_ops.empty());
    assert(!_vao);
    _instance_count = that._instance_count;
    _ops = std::move(that._ops);
    _vao = std::move(that._vao);
    _buffers = std::move(that._buffers);
    return *this;
}
//------------------------------------------------------------------------------
geometry::geometry(
  const gl_api& glapi,
  const shape_generator& shape,
  const vertex_attrib_bindings& bindings,
  const shapes::drawing_variant var,
  memory::buffer& temp)
  : _instance_count{shape.instance_count()} {

    const auto& gl = glapi.operations();
    gl.gen_vertex_arrays() >> _vao;
    const auto attrib_count{bindings.attrib_count()};
    auto buffer_count{attrib_count};

    _ops.resize(integer(shape.operation_count(var)));
    shape.instructions(glapi, var, cover(_ops));

    const auto indexed{shape.indexed_drawing(var)};

    if(indexed) {
        ++buffer_count;
    }
    _buffers.resize(buffer_count);
    gl.gen_buffers(_buffers.raw_handles());

    gl.bind_vertex_array(_vao);

    for(const integer i : integer_range(attrib_count)) {
        shape.attrib_setup(
          glapi,
          _vao,
          _buffers[i],
          vertex_attrib_location{i},
          bindings.attrib_variant(i),
          temp);
    }
    if(indexed) {
        shape.index_setup(glapi, _buffers[attrib_count], temp);
    }
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
