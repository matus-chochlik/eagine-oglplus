/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef EAGINE_OGLPLUS_SHAPES_GEOMETRY_HPP
#define EAGINE_OGLPLUS_SHAPES_GEOMETRY_HPP

#include "bindings.hpp"

namespace eagine::oglplus {

/// @brief Class wrapping a vertex attribute array and buffers storing shape geometry.
/// @see generator
/// @see vertex_attrib_bindings
/// @ingroup shapes
class geometry {
public:
    /// @brief Default constructor.
    geometry() noexcept = default;

    /// @brief Initializes a previously default initialized geometry instance.
    auto init(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      const shapes::drawing_variant var,
      memory::buffer& temp) -> auto& {

        _instance_count = shape.instance_count();

        const auto& gl = glapi;
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
        return *this;
    }

    /// @brief Initializes a previously default initialized geometry instance.
    auto init(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      memory::buffer& temp) -> auto& {
        return init(glapi, shape, bindings, shape.draw_variant(0), temp);
    }

    /// @brief Construction using shape generator, attrib bindings and drawing variant.
    geometry(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      const shapes::drawing_variant var,
      memory::buffer& temp) {
        init(glapi, shape, bindings, var, temp);
    }

    /// @brief Construction using shape generator and attrib bindings.
    geometry(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      memory::buffer& temp)
      : geometry{glapi, shape, bindings, shape.draw_variant(0), temp} {}

    /// @brief Releases the used OpenGL resources.
    void clean_up(const gl_api& gl) {
        gl.clean_up(_buffers);
        gl.clean_up(std::move(_vao));
    }

    /// @brief Prepares and binds the resources to be used (for example by draw).
    /// @see draw
    auto use(const gl_api& gl) const {
        return gl.bind_vertex_array(_vao);
    }

    /// @brief Emits geometry draw commands using the specified GL API.
    /// @see use
    /// @see draw_instanced
    auto draw(const gl_api& glapi) const {
        draw_instanced_using_instructions(
          glapi, view(_ops), limit_cast<gl_types::sizei_type>(_instance_count));
    }

    /// @brief Emits geometry draw commands using the specified GL API.
    /// @see use
    /// @see draw
    auto draw_instanced(const gl_api& glapi, const span_size_t inst_count)
      const {
        draw_instanced_using_instructions(
          glapi,
          view(_ops),
          limit_cast<gl_types::sizei_type>(inst_count * _instance_count));
    }

private:
    span_size_t _instance_count{0};
    std::vector<shape_draw_operation> _ops;
    owned_vertex_array_name _vao;
    gl_object_name_vector<buffer_tag> _buffers;
};

class geometry_and_bindings
  : public vertex_attrib_bindings
  , public geometry {
public:
    geometry_and_bindings() noexcept = default;

    auto init(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      const shapes::drawing_variant var,
      memory::buffer& temp) -> auto& {
        vertex_attrib_bindings::init(bindings);
        geometry::init(glapi, shape, *this, var, temp);
        return *this;
    }

    geometry_and_bindings(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      const shapes::drawing_variant var,
      memory::buffer& temp) {
        init(glapi, shape, bindings, var, temp);
    }

    auto init(
      const gl_api& glapi,
      const shape_generator& shape,
      const shapes::drawing_variant var,
      memory::buffer& temp) -> auto& {
        vertex_attrib_bindings::init(shape);
        geometry::init(glapi, shape, *this, var, temp);
        return *this;
    }

    geometry_and_bindings(
      const gl_api& glapi,
      const shape_generator& shape,
      const shapes::drawing_variant var,
      memory::buffer& temp) {
        init(glapi, shape, var, temp);
    }

    auto init(
      const gl_api& glapi,
      const shape_generator& shape,
      memory::buffer& temp) -> auto& {
        return init(glapi, shape, shape.draw_variant(0), temp);
    }

    geometry_and_bindings(
      const gl_api& glapi,
      const shape_generator& shape,
      memory::buffer& temp) {
        init(glapi, shape, temp);
    }
};

} // namespace eagine::oglplus

#endif
