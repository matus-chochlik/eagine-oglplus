/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef EAGINE_OGLPLUS_SHAPES_GENERATOR_HPP
#define EAGINE_OGLPLUS_SHAPES_GENERATOR_HPP

#include "../gl_api.hpp"
#include "../math/primitives.hpp"
#include "drawing.hpp"
#include <eagine/memory/buffer.hpp>
#include <eagine/shapes/generator.hpp>
#include <eagine/shapes/vertex_attrib.hpp>
#include <eagine/span.hpp>
#include <memory>

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Class wrapping a generic shape loader/generator, adapting it for GL.
/// @ingroup shapes
/// @see shapes::generator
class shape_generator {
private:
    using generator = shapes::generator;
    std::shared_ptr<generator> _gen{};

public:
    template <typename A>
    shape_generator(const basic_gl_api<A>&, std::shared_ptr<generator>);

    template <typename A, typename Gen>
    shape_generator(const basic_gl_api<A>& api, std::shared_ptr<Gen> gen)
      : shape_generator(api, std::shared_ptr<generator>(std::move(gen))) {}

    auto indexed_drawing(const shapes::drawing_variant var) const -> bool {
        return _gen->indexed_drawing(var);
    }

    auto attrib_divisors() const {
        return _gen->attrib_divisors();
    }

    auto attrib_divisor(const shapes::vertex_attrib_variant vav) const {
        return _gen->attrib_divisor(vav);
    }

    auto find_variant(
      const shapes::vertex_attrib_kind attrib,
      const string_view name) const -> shapes::vertex_attrib_variant {
        return _gen->find_variant(attrib, name);
    }

    auto find_variant_or(
      const shapes::vertex_attrib_kind attrib,
      const string_view name,
      const span_size_t index) const -> shapes::vertex_attrib_variant {
        if(auto found{find_variant(attrib, name)}) {
            return found;
        }
        return {attrib, index};
    }

    auto supported_attrib_count() const -> span_size_t {
        return _gen->supported_attrib_count();
    }

    void for_each_attrib(callable_ref<void(
                           shapes::vertex_attrib_kinds,
                           shapes::vertex_attrib_name_and_kind)> func) const {
        _gen->for_each_attrib(func);
    }

    auto draw_variant_count() const -> span_size_t {
        return _gen->draw_variant_count();
    }

    auto draw_variant(const span_size_t index) const
      -> shapes::drawing_variant {
        return _gen->draw_variant(index);
    }

    auto vertex_count() const -> span_size_t {
        return _gen->vertex_count();
    }

    auto values_per_vertex(const shapes::vertex_attrib_variant vav) const
      -> span_size_t {
        return _gen->values_per_vertex(vav);
    }

    auto value_count(const shapes::vertex_attrib_variant vav) const
      -> span_size_t {
        return vertex_count() * values_per_vertex(vav);
    }

    template <typename A>
    auto attrib_type(
      const basic_gl_api<A>& api,
      const shapes::vertex_attrib_variant vav) const -> data_type {
        return translate(api, _gen->attrib_type(vav));
    }

    auto is_attrib_integral(const shapes::vertex_attrib_variant vav) const
      -> bool {
        return _gen->is_attrib_integral(vav);
    }

    template <typename A>
    auto is_attrib_normalized(
      const basic_gl_api<A>& api,
      const shapes::vertex_attrib_variant vav) const -> true_false {
        return translate(api, _gen->is_attrib_normalized(vav));
    }

    auto attrib_type_size(const shapes::vertex_attrib_variant vav) const
      -> span_size_t {
        return type_size(_gen->attrib_type(vav));
    }

    auto attrib_data_block_size(const shapes::vertex_attrib_variant vav) const
      -> span_size_t {
        return value_count(vav) * attrib_type_size(vav);
    }

    void attrib_data(const shapes::vertex_attrib_variant, memory::block data)
      const;

    auto is_indexed() const -> bool {
        return _gen->index_count() > 0;
    }

    auto index_count() const -> span_size_t {
        return _gen->index_count();
    }

    auto index_count(const shapes::drawing_variant dv) const -> span_size_t {
        return _gen->index_count(dv);
    }

    auto index_type_size() const -> span_size_t {
        return type_size(_gen->index_type());
    }

    auto index_type_size(const shapes::drawing_variant dv) const
      -> span_size_t {
        return type_size(_gen->index_type(dv));
    }

    auto index_data_block_size() const -> span_size_t {
        return index_count() * index_type_size();
    }

    auto index_data_block_size(const shapes::drawing_variant dv) const
      -> span_size_t {
        return index_count(dv) * index_type_size(dv);
    }

    void index_data(const shapes::drawing_variant, memory::block data) const;
    void index_data(memory::block data) const {
        return index_data(0, data);
    }

    auto operation_count() const -> span_size_t {
        return _gen->operation_count();
    }

    auto operation_count(const shapes::drawing_variant dv) const
      -> span_size_t {
        return _gen->operation_count(dv);
    }

    auto operation_count(const span<const shapes::drawing_variant> dvs) const
      -> span_size_t;

    template <typename A>
    void attrib_setup(
      const basic_gl_api<A>& api,
      const vertex_array_name vao,
      const buffer_name buf,
      const vertex_attrib_location loc,
      const shapes::vertex_attrib_variant attrib_variant,
      const string_view label,
      memory::buffer& temp) const;

    template <typename A>
    void attrib_setup(
      const basic_gl_api<A>& api,
      const vertex_array_name vao,
      const buffer_name buf,
      const vertex_attrib_location loc,
      const shapes::vertex_attrib_variant attrib_variant,
      memory::buffer& temp) const {
        return attrib_setup(api, vao, buf, loc, attrib_variant, {}, temp);
    }

    template <typename A>
    void index_setup(
      const basic_gl_api<A>& api,
      const buffer_name buf,
      const shapes::drawing_variant dv,
      const string_view label,
      memory::buffer& temp) const;

    template <typename A>
    void index_setup(
      const basic_gl_api<A>& api,
      const buffer_name buf,
      const shapes::drawing_variant dv,
      memory::buffer& temp) const {
        return index_setup(api, buf, dv, {}, temp);
    }

    template <typename A>
    void index_setup(
      const basic_gl_api<A>& api,
      const buffer_name buf,
      const string_view label,
      memory::buffer& temp) const {
        return index_setup(api, buf, 0, label, temp);
    }

    template <typename A>
    void index_setup(
      const basic_gl_api<A>& api,
      const buffer_name buf,
      memory::buffer& temp) const {
        return index_setup(api, buf, 0, {}, temp);
    }

    template <typename A>
    void index_setup(
      const basic_gl_api<A>& api,
      const buffer_name buf,
      const span<const shapes::drawing_variant> dvs,
      const string_view label,
      memory::buffer& temp) const;

    template <typename A>
    void index_setup(
      const basic_gl_api<A>& api,
      const buffer_name buf,
      const span<const shapes::drawing_variant> dvs,
      memory::buffer& temp) const {
        return index_setup(api, buf, dvs, {}, temp);
    }

    template <typename A>
    void instructions(
      const basic_gl_api<A>&,
      const shapes::drawing_variant dv,
      span<shape_draw_operation>) const;

    template <typename A>
    void instructions(
      const basic_gl_api<A>& api,
      span<shape_draw_operation> dest) const {
        return instructions(api, 0, dest);
    }

    template <typename A>
    void instructions(
      const basic_gl_api<A>&,
      const span<const shapes::drawing_variant> dvs,
      span<shape_draw_subset>,
      span<shape_draw_operation>) const;

    auto bounding_sphere() const -> sphere {
        return _gen->bounding_sphere();
    }

    auto ray_intersection(const line& ray) const -> optionally_valid<float> {
        return _gen->ray_intersection(ray);
    }

    auto ray_intersection(const optionally_valid<line>& opt_ray) const
      -> optionally_valid<float> {
        if(opt_ray) {
            return ray_intersection(extract(opt_ray));
        }
        return {};
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

#include <eagine/oglplus/shapes/generator.inl>

#endif // EAGINE_OGLPLUS_SHAPES_GENERATOR_HPP
