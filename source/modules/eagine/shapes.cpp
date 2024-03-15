/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#include <cassert>

export module eagine.oglplus:shapes;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.utility;
import eagine.core.valid_if;
import eagine.shapes;
import :config;
import :enum_types;
import :objects;
import :constants;
import :prog_var_loc;
import :math;
import :api;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Translates from shape primitive type to GL primitive type.
/// @ingroup shapes
/// @see shapes::primitive_type
export template <typename A>
constexpr auto translate(
  const basic_gl_api<A>&,
  const shapes::primitive_type) noexcept -> primitive_type;
//------------------------------------------------------------------------------
/// @brief Translates from shape attribute data type to GL data type.
/// @ingroup shapes
/// @see shapes::attrib_data_type
export template <typename A>
constexpr auto translate(
  const basic_gl_api<A>&,
  const shapes::attrib_data_type) noexcept -> data_type;
//------------------------------------------------------------------------------
/// @brief Translates from shape index data type to GL data type.
/// @ingroup shapes
/// @see shapes::index_data_type
export template <typename A>
constexpr auto translate(
  const basic_gl_api<A>&,
  const shapes::index_data_type) noexcept -> index_data_type;
//------------------------------------------------------------------------------
/// @brief Returns the byte size of a shape attribute data type.
/// @ingroup shapes
/// @see shapes::attrib_data_type
export template <typename A>
auto type_size(const basic_gl_api<A>&, const shapes::attrib_data_type) noexcept
  -> span_size_t;
//------------------------------------------------------------------------------
/// @brief Returns the byte size of a shape index data type.
/// @ingroup shapes
/// @see shapes::index_data_type
export template <typename A>
auto type_size(const basic_gl_api<A>&, const shapes::index_data_type) noexcept
  -> span_size_t;
//------------------------------------------------------------------------------
/// @brief Shape draw operation parameters, translated to GL representation.
/// @ingroup shapes
/// @see draw_using_instructions
/// @see draw_instanced_using_instructions
export class shape_draw_operation {
public:
    /// @brief Default constructor.
    constexpr shape_draw_operation() noexcept = default;

    /// @brief Initialization from shape generator draw operation.
    template <typename A>
    shape_draw_operation(
      const basic_gl_api<A>& api,
      const shapes::draw_operation& draw_op) noexcept;

    /// @brief Moves the first index by the specified offset.
    auto offset_first(const span_size_t offs) noexcept -> auto& {
        _first += limit_cast<gl_types::int_type>(offs);
        return *this;
    }

    /// @brief Returns the drawing phase.
    auto phase() const noexcept {
        return _phase;
    }

    /// @brief Indicates if indexed drawing is enabled.
    template <typename A>
    auto is_indexed(const basic_gl_api<A>& api) const noexcept -> bool {
        const basic_gl_constants<A>& GL = api;
        return _idx_type != GL.none;
    }

    /// @brief Invokes the appropriate draw operation on the specified GL api.
    template <typename A>
    void draw(const basic_gl_api<A>& api) const noexcept;

    /// @brief Invokes the appropriate instanced draw operation on the given GL api.
    template <typename A>
    void draw_instanced(
      const basic_gl_api<A>& api,
      const gl_types::sizei_type inst_count) const noexcept;

private:
    primitive_type _mode{0};
    index_data_type _idx_type{0};
    gl_types::int_type _first{0};
    gl_types::sizei_type _count{0};
    gl_types::uint_type _phase{0};
    gl_types::uint_type _primitive_restart_index{0};
    gl_types::int_type _patch_vertices{3};
    bool _primitive_restart{false};
    bool _cw_face_winding{false};

    auto _idx_ptr() const noexcept -> gl_types::const_void_ptr_type;

    template <typename A>
    void _prepare(const basic_gl_api<A>& api) const noexcept;
};
//------------------------------------------------------------------------------
/// @brief Holds the first index and count of a subset of drawn shape elements.
/// @ingroup shapes
/// @see shape_draw_operation
export struct shape_draw_subset {
    /// @brief Index of the first element.
    span_size_t first{0};
    /// @brief Number of elements to be drawn.
    span_size_t count{0};
};
//------------------------------------------------------------------------------
/// @brief Takes a sequence of draw operations from a shape generator and draws them.
/// @ingroup shapes
/// @see shape_draw_operation
/// @see draw_instanced_using_instructions
export template <typename A>
void draw_using_instructions(
  const basic_gl_api<A>& api,
  const span<const shape_draw_operation> ops) noexcept;
//------------------------------------------------------------------------------
/// @brief Takes a sequence of draw operations from a shape generator and draws them.
/// @ingroup shapes
/// @see shape_draw_operation
/// @see draw_using_instructions
export template <typename A>
void draw_instanced_using_instructions(
  const basic_gl_api<A>& api,
  const span<const shape_draw_operation> ops,
  const gl_types::sizei_type inst_count) noexcept;
//------------------------------------------------------------------------------
/// @brief Takes a sequence of draw operations from a shape generator and draws them.
/// @ingroup shapes
/// @see shape_draw_operation
/// @see draw_instanced_using_instructions
export template <typename A>
void draw_using_instructions(
  const basic_gl_api<A>& api,
  const span<const shape_draw_operation> ops,
  const shape_draw_subset& subs) noexcept;
//------------------------------------------------------------------------------
/// @brief Takes a sequence of draw operations from a shape generator and draws them.
/// @ingroup shapes
/// @see shape_draw_operation
/// @see draw_using_instructions
export template <typename A>
void draw_instanced_using_instructions(
  const basic_gl_api<A>& api,
  const span<const shape_draw_operation> ops,
  const shape_draw_subset& subs,
  const gl_types::sizei_type inst_count) noexcept;
//------------------------------------------------------------------------------
export template <typename A>
constexpr auto translate(
  const basic_gl_api<A>& api,
  const shapes::primitive_type mode) noexcept -> primitive_type {
    auto& GL = api.constants();

    switch(mode) {
        case shapes::primitive_type::points:
            return GL.points;
        case shapes::primitive_type::lines:
            return GL.lines;
        case shapes::primitive_type::quads:
            return GL.lines_adjacency;
        case shapes::primitive_type::tetrahedrons:
            return GL.lines_adjacency;
        case shapes::primitive_type::line_strip:
            return GL.line_strip;
        case shapes::primitive_type::line_loop:
            return GL.line_loop;
        case shapes::primitive_type::triangles:
            return GL.triangles;
        case shapes::primitive_type::triangle_strip:
            return GL.triangle_strip;
        case shapes::primitive_type::triangle_fan:
            return GL.triangle_fan;
        case shapes::primitive_type::triangles_adjacency:
            return GL.triangles_adjacency;
        case shapes::primitive_type::patches:
            return GL.patches;
    }
    return GL.points;
}
//------------------------------------------------------------------------------
export template <typename A>
constexpr auto translate(
  const basic_gl_api<A>& api,
  const shapes::attrib_data_type type) noexcept -> data_type {
    auto& GL = api.constants();

    switch(type) {
        case shapes::attrib_data_type::ubyte:
            return GL.unsigned_byte_;
        case shapes::attrib_data_type::int_16:
            return GL.short_;
        case shapes::attrib_data_type::int_32:
            return GL.int_;
        case shapes::attrib_data_type::uint_16:
            return GL.unsigned_short_;
        case shapes::attrib_data_type::uint_32:
            return GL.unsigned_int_;
        case shapes::attrib_data_type::float_:
            return GL.float_;
        case shapes::attrib_data_type::none:
            break;
    }
    return GL.float_;
}
//------------------------------------------------------------------------------
export template <typename A>
constexpr auto translate(
  const basic_gl_api<A>& api,
  const shapes::index_data_type type) noexcept -> index_data_type {
    auto& GL = api.constants();

    switch(type) {
        case shapes::index_data_type::unsigned_8:
            return GL.unsigned_byte_;
        case shapes::index_data_type::unsigned_16:
            return GL.unsigned_short_;
        case shapes::index_data_type::unsigned_32:
            return GL.unsigned_int_;
        case shapes::index_data_type::none:
            break;
    }
    return GL.none;
}
//------------------------------------------------------------------------------
export constexpr auto type_size(const shapes::attrib_data_type type) noexcept
  -> span_size_t {
    switch(type) {
        case shapes::attrib_data_type::ubyte:
            return span_size(sizeof(gl_types::ubyte_type));
        case shapes::attrib_data_type::int_16:
            return span_size(sizeof(gl_types::short_type));
        case shapes::attrib_data_type::int_32:
            return span_size(sizeof(gl_types::int_type));
        case shapes::attrib_data_type::uint_16:
            return span_size(sizeof(gl_types::ushort_type));
        case shapes::attrib_data_type::uint_32:
            return span_size(sizeof(gl_types::uint_type));
        case shapes::attrib_data_type::float_:
            return span_size(sizeof(gl_types::float_type));
        case shapes::attrib_data_type::none:
            break;
    }
    return 1;
}
//------------------------------------------------------------------------------
export constexpr auto type_size(const shapes::index_data_type type) noexcept
  -> span_size_t {
    switch(type) {
        case shapes::index_data_type::unsigned_8:
            return span_size(sizeof(gl_types::ubyte_type));
        case shapes::index_data_type::unsigned_16:
            return span_size(sizeof(gl_types::ushort_type));
        case shapes::index_data_type::unsigned_32:
            return span_size(sizeof(gl_types::uint_type));
        case shapes::index_data_type::none:
            break;
    }
    return 1;
}
//------------------------------------------------------------------------------
template <typename A>
shape_draw_operation::shape_draw_operation(
  const basic_gl_api<A>& api,
  const shapes::draw_operation& draw_op) noexcept
  : _mode(translate(api, draw_op.mode))
  , _idx_type(translate(api, draw_op.idx_type))
  , _first(gl_types::int_type(draw_op.first * type_size(draw_op.idx_type)))
  , _count(gl_types::sizei_type(draw_op.count))
  , _phase(gl_types::uint_type(draw_op.phase))
  , _primitive_restart_index(draw_op.primitive_restart_index)
  , _patch_vertices(draw_op.patch_vertices)
  , _primitive_restart(draw_op.primitive_restart)
  , _cw_face_winding(draw_op.cw_face_winding) {}
//------------------------------------------------------------------------------
auto shape_draw_operation::_idx_ptr() const noexcept
  -> gl_types::const_void_ptr_type {
    return eagine::memory::typed_nullptr<const gl_types::ubyte_type> + _first;
}
//------------------------------------------------------------------------------
template <typename A>
void shape_draw_operation::_prepare(const basic_gl_api<A>& api) const noexcept {
    auto& [gl, GL] = api;

    if(_cw_face_winding) {
        gl.front_face(GL.cw);
    } else {
        gl.front_face(GL.ccw);
    }

    if(GL.primitive_restart) {
        if(_primitive_restart) {
            gl.enable(GL.primitive_restart);
            gl.primitive_restart_index(_primitive_restart_index);
        } else {
            gl.disable(GL.primitive_restart);
        }
    }

    if(GL.patches) {
        if(_mode == GL.patches) {
            gl.patch_parameter_i(GL.patch_vertices, _patch_vertices);
        }
    }
}
//------------------------------------------------------------------------------
template <typename A>
void shape_draw_operation::draw(const basic_gl_api<A>& api) const noexcept {
    _prepare(api);
    auto& [gl, GL] = api;

    if(is_indexed(api)) {
        gl.draw_elements(_mode, _count, _idx_type, _idx_ptr());
    } else {
        gl.draw_arrays(_mode, _first, _count);
    }
}
//------------------------------------------------------------------------------
template <typename A>
void shape_draw_operation::draw_instanced(
  const basic_gl_api<A>& api,
  const gl_types::sizei_type inst_count) const noexcept {
    _prepare(api);
    auto& [gl, GL] = api;

    if(is_indexed(api)) {
        gl.draw_elements_instanced(
          _mode, _count, _idx_type, _idx_ptr(), inst_count);
    } else {
        gl.draw_arrays_instanced(_mode, _first, _count, inst_count);
    }
}
//------------------------------------------------------------------------------
export template <typename A>
void draw_using_instructions(
  const basic_gl_api<A>& api,
  const span<const shape_draw_operation> ops) noexcept {
    for(const auto& op : ops) {
        op.draw(api);
    }
}
//------------------------------------------------------------------------------
export template <typename A>
void draw_instanced_using_instructions(
  const basic_gl_api<A>& api,
  const span<const shape_draw_operation> ops,
  const gl_types::sizei_type inst_count) noexcept {
    for(const auto& op : ops) {
        op.draw_instanced(api, inst_count);
    }
}
//------------------------------------------------------------------------------
export template <typename A>
void draw_using_instructions(
  const basic_gl_api<A>& api,
  const span<const shape_draw_operation> ops,
  const shape_draw_subset& subs) noexcept {
    for(const auto i : integer_range(subs.first, subs.first + subs.count)) {
        if(i < ops.size()) [[likely]] {
            ops[i].draw(api);
        }
    }
}
//------------------------------------------------------------------------------
export template <typename A>
void draw_using_instructions(
  const basic_gl_api<A>& api,
  const span<const shape_draw_operation> ops,
  const shape_draw_subset& subs,
  const gl_types::sizei_type inst_count) noexcept {
    for(const auto i : integer_range(subs.first, subs.first + subs.count)) {
        if(i < ops.size()) [[likely]] {
            ops[i].draw_instanced(api, inst_count);
        }
    }
}
//------------------------------------------------------------------------------
/// @brief Class wrapping a generic shape loader/generator, adapting it for GL.
/// @ingroup shapes
/// @see shapes::generator
export class shape_generator {
private:
    using generator = shapes::generator;
    shared_holder<generator> _gen{};

public:
    template <typename A>
    shape_generator(const basic_gl_api<A>&, shared_holder<generator>);

    template <typename A, typename Gen>
    shape_generator(const basic_gl_api<A>& api, shared_holder<Gen> gen)
      : shape_generator(api, shared_holder<generator>(std::move(gen))) {}

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

    auto instance_count() const -> span_size_t {
        return _gen->instance_count();
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
        return opt_ray.and_then(
          [this](const line& ray) { return _gen->ray_intersection(ray); });
    }
};
//------------------------------------------------------------------------------
template <typename A>
shape_generator::shape_generator(
  const basic_gl_api<A>& api,
  shared_holder<shapes::generator> gen)
  : _gen{std::move(gen)} {
    using shapes::generator_capability;
    auto& [gl, GL] = api;

    if(GL.triangle_fan) {
        _gen->enable(generator_capability::element_fans);
    }
    if(GL.triangle_strip) {
        _gen->enable(generator_capability::element_strips);
    }
    if(GL.primitive_restart) {
        _gen->enable(generator_capability::primitive_restart);
    }
    if(gl.vertex_attrib_divisor) {
        _gen->enable(generator_capability::attrib_divisors);
    }
}
//------------------------------------------------------------------------------
template <typename A>
void shape_generator::attrib_setup(
  const basic_gl_api<A>& api,
  const vertex_array_name vao,
  const buffer_name buf,
  const vertex_attrib_location loc,
  const shapes::vertex_attrib_variant vav,
  const string_view label,
  memory::buffer& temp) const {
    auto& [gl, GL] = api;

    const auto size = attrib_data_block_size(vav);
    auto data = head(cover(temp.ensure(size)), size);
    attrib_data(vav, data);

    gl.bind_buffer(GL.array_buffer, buf);
    if(label) {
        gl.object_label(buf, label);
    }
    gl.buffer_data(GL.array_buffer, data, GL.static_draw);

    const auto is_integral{is_attrib_integral(vav)};
    const auto is_normalized{is_attrib_normalized(api, vav)};
    if(is_integral and not is_normalized) [[unlikely]] {
        gl.vertex_attrib_ipointer(
          loc,
          limit_cast<gl_types::int_type>(values_per_vertex(vav)),
          attrib_type(api, vav));
    } else {
        gl.vertex_attrib_pointer(
          loc,
          limit_cast<gl_types::int_type>(values_per_vertex(vav)),
          attrib_type(api, vav),
          is_normalized);
    }
    if(attrib_divisors()) {
        gl.vertex_attrib_divisor(
          loc, limit_cast<gl_types::uint_type>(attrib_divisor(vav)));
    } else {
        gl.vertex_attrib_divisor(loc, 0U);
    }

    if(gl.enable_vertex_array_attrib) {
        gl.enable_vertex_array_attrib(vao, loc);
    } else {
        gl.enable_vertex_attrib_array(loc);
    }
}
//------------------------------------------------------------------------------
auto shape_generator::operation_count(
  const span<const shapes::drawing_variant> dvs) const -> span_size_t {
    span_size_t result = 0;
    for(auto dv : dvs) {
        result += _gen->operation_count(dv);
    }
    return result;
}
//------------------------------------------------------------------------------
template <typename A>
inline void shape_generator::index_setup(
  const basic_gl_api<A>& api,
  const buffer_name buf,
  const shapes::drawing_variant dv,
  const string_view label,
  memory::buffer& temp) const {
    auto& [gl, GL] = api;

    const auto size = index_data_block_size(dv);
    auto data = head(cover(temp.ensure(size)), size);
    index_data(dv, data);

    gl.bind_buffer(GL.element_array_buffer, buf);
    if(label) {
        gl.object_label(buf, label);
    }
    gl.buffer_data(GL.element_array_buffer, data, GL.static_draw);
}
//------------------------------------------------------------------------------
template <typename A>
void shape_generator::index_setup(
  const basic_gl_api<A>& api,
  const buffer_name buf,
  const span<const shapes::drawing_variant> dvs,
  const string_view label,
  memory::buffer& temp) const {
    auto& [gl, GL] = api;

    // TODO: buffer_storage + buffer_sub_data if available
    span_size_t total_size = 0;
    for(auto dv : dvs) {
        const auto size = index_data_block_size(dv);
        auto data =
          head(skip(cover(temp.ensure(total_size + size)), total_size), size);
        index_data(dv, data);
        total_size += size;
    }

    auto data = head(cover(temp), total_size);

    gl.bind_buffer(GL.element_array_buffer, buf);
    if(label) {
        gl.object_label(buf, label);
    }
    gl.buffer_data(GL.element_array_buffer, data, GL.static_draw);
}
//------------------------------------------------------------------------------
template <typename A>
void shape_generator::instructions(
  const basic_gl_api<A>& api,
  const shapes::drawing_variant dv,
  span<shape_draw_operation> ops) const {
    assert(ops.size() >= operation_count(dv));

    std::vector<shapes::draw_operation> tmp(integer(operation_count(dv)));
    _gen->instructions(dv, cover(tmp));

    for(const auto i : index_range(tmp)) {
        ops[span_size(i)] = shape_draw_operation(api, tmp[i]);
    }
}
//------------------------------------------------------------------------------
template <typename A>
void shape_generator::instructions(
  const basic_gl_api<A>& api,
  const span<const shapes::drawing_variant> dvs,
  span<shape_draw_subset> subs,
  span<shape_draw_operation> ops) const {

    assert(dvs.size() <= subs.size());
    std::vector<shapes::draw_operation> tmp{};
    span_size_t total_count = 0;
    span_size_t elem_offset = 0;

    for(span_size_t s = 0; s < dvs.size(); ++s) {
        auto& dv = dvs[s];
        const auto count = operation_count(dv);

        assert(ops.size() >= total_count + count);
        tmp.resize(integer(count));

        _gen->instructions(dv, cover(tmp));

        for(decltype(tmp.size()) i = 0; i < tmp.size(); ++i) {
            const auto k = total_count + span_size(i);
            ops[k] = shape_draw_operation(api, tmp[i]);
            ops[k].offset_first(elem_offset);
        }

        auto& sub = subs[s];
        sub.first = total_count;
        sub.count = count;

        total_count += count;
        elem_offset += index_data_block_size(dv);
    }
}
//------------------------------------------------------------------------------
/// @brief Type for storing of vertex attribute values.
/// @ingroup shapes
export using vertex_attrib_value = shapes::vertex_attrib_value;

export using vertex_attrib_values =
  shapes::vertex_attrib_map<vertex_attrib_value>;
//------------------------------------------------------------------------------
export template <typename A>
auto set_vertex_attrib_value(
  const basic_gl_api<A>& api,
  const vertex_attrib_location loc,
  const vertex_attrib_value& val) noexcept -> bool {
    if(val) {
        std::visit(
          overloaded(
            [&](const float v) { api.vertex_attrib_f(loc, v); },
            [&](const int v) { api.vertex_attrib_i(loc, v); },
            [&]<bool V>(const vector<int, 2, V> v) {
                api.vertex_attrib_i(loc, v.x(), v.y());
            },
            [&]<bool V>(const vector<int, 3, V> v) {
                api.vertex_attrib_i(loc, v.x(), v.y(), v.z());
            },
            [&]<bool V>(const vector<int, 4, V> v) {
                api.vertex_attrib_i(loc, v.x(), v.y(), v.z(), v.w());
            },
            [&]<bool V>(const vector<float, 2, V> v) {
                api.vertex_attrib_f(loc, v.x(), v.y());
            },
            [&]<bool V>(const vector<float, 3, V> v) {
                api.vertex_attrib_f(loc, v.x(), v.y(), v.z());
            },
            [&]<bool V>(const vector<float, 4, V> v) {
                api.vertex_attrib_f(loc, v.x(), v.y(), v.z(), v.w());
            },
            [&](const auto&) {}),
          val);
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------
/// @brief Interface for bindings between attribute variant and vertex array index.
/// @ingroup shapes
/// @see vertex_attrib_bindings
/// @note Do not use directly. Use vertex_attrib_bindings instead.
export struct vertex_attrib_binding_intf
  : interface<vertex_attrib_binding_intf> {

    /// @brief Returns the number of attributes in the binding.
    /// @see attrib_variant
    virtual auto attrib_count() noexcept -> span_size_t = 0;

    /// @brief Returns the attribute variant bound to specified index.
    /// @see attrib_count
    /// @see location
    /// @pre index < attrib_count()
    virtual auto attrib_variant(span_size_t index) noexcept
      -> shapes::vertex_attrib_variant = 0;

    /// @brief Returns the index at which the specified attribute variant is bound.
    /// @see attrib_variant
    virtual auto location(shapes::vertex_attrib_variant vav) noexcept
      -> vertex_attrib_location = 0;

    /// @brief Returns the single value of the specified attribute variant.
    /// @see attrib_variant
    virtual auto location_and_value(shapes::vertex_attrib_variant vav) noexcept
      -> std::tuple<vertex_attrib_location, vertex_attrib_value> = 0;
};

export auto make_default_vertex_attrib_bindings(const shape_generator& shape)
  -> shared_holder<vertex_attrib_binding_intf>;

export auto make_default_vertex_attrib_bindings(
  std::initializer_list<shapes::vertex_attrib_variant> vavs)
  -> shared_holder<vertex_attrib_binding_intf>;

/// @brief Class that specifies bindings between attribute variant and array index.
/// @ingroup shapes
/// @see generator
/// @see geometry
export class vertex_attrib_bindings {
public:
    vertex_attrib_bindings() noexcept = default;
    vertex_attrib_bindings(vertex_attrib_bindings&&) noexcept = default;
    vertex_attrib_bindings(const vertex_attrib_bindings&) = default;
    auto operator=(vertex_attrib_bindings&&) noexcept
      -> vertex_attrib_bindings& = default;
    auto operator=(const vertex_attrib_bindings&)
      -> vertex_attrib_bindings& = default;
    ~vertex_attrib_bindings() noexcept = default;

    vertex_attrib_bindings(
      shared_holder<vertex_attrib_binding_intf> pimpl) noexcept
      : _pimpl{std::move(pimpl)} {
        assert(_pimpl);
    }

    /// @brief Constructor matching supported attributes from a shape generator.
    vertex_attrib_bindings(const shape_generator& shape)
      : vertex_attrib_bindings{make_default_vertex_attrib_bindings(shape)} {}

    /// @brief Constructor matching supported attributes from a shape generator.
    vertex_attrib_bindings(
      std::initializer_list<shapes::vertex_attrib_variant> vavs)
      : vertex_attrib_bindings{make_default_vertex_attrib_bindings(vavs)} {}

    /// @brief Indicates if this bindings wrapper is initialized.
    auto is_initialized() const noexcept -> bool {
        return bool(_pimpl);
    }

    /// @brief Indicates if this bindings wrapper is initialized.
    /// @see is_initialized
    explicit operator bool() const noexcept {
        return is_initialized();
    }

    /// @brief Returns the number of attributes in the binding.
    /// @see attrib_variant
    auto attrib_count() const noexcept -> span_size_t {
        if(_pimpl) {
            return _pimpl->attrib_count();
        }
        return 0;
    }

    /// @brief Returns the attribute variant bound to specified index.
    /// @see attrib_count
    /// @see location
    /// @pre index < attrib_count()
    auto attrib_variant(span_size_t index) const noexcept
      -> shapes::vertex_attrib_variant {
        if(_pimpl) {
            assert(index < attrib_count());
            return _pimpl->attrib_variant(index);
        }
        return {};
    }

    /// @brief Returns the attribute kind bits for all attributes in this binding.
    auto attrib_kinds() const noexcept -> shapes::vertex_attrib_kinds {
        shapes::vertex_attrib_kinds result;
        for(const auto i : integer_range(attrib_count())) {
            result.set(attrib_variant(i).attribute());
        }
        return result;
    }

    /// @brief Returns the index at which the specified attribute variant is bound.
    /// @see attrib_variant
    auto location(shapes::vertex_attrib_variant vav) const noexcept
      -> vertex_attrib_location {
        if(_pimpl) {
            return _pimpl->location(vav);
        }
        return {};
    }

    /// @brief Returns the default value of the specified attribute variant.
    /// @see attrib_variant
    auto location_and_value(shapes::vertex_attrib_variant vav) const noexcept
      -> std::tuple<vertex_attrib_location, vertex_attrib_value> {
        if(_pimpl) {
            return _pimpl->location_and_value(vav);
        }
        return {};
    }

    /// @brief Returns the index at which the position variant is bound.
    /// @see location
    auto position_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::position, idx});
    }

    /// @brief Returns the index at which the inner position variant is bound.
    /// @see location
    auto inner_position_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::inner_position, idx});
    }

    /// @brief Returns the index at which the normal variant is bound.
    /// @see location
    auto normal_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::normal, idx});
    }

    /// @brief Returns the index at which the tangent variant is bound.
    /// @see location
    auto tangent_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::tangent, idx});
    }

    /// @brief Returns the index at which the bitangent variant is bound.
    /// @see location
    auto bitangent_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::bitangent, idx});
    }

    /// @brief Returns the index at which the shape pivot variant is bound.
    /// @see location
    auto pivot_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::pivot, idx});
    }

    /// @brief Returns the index at which the vertex pivot variant is bound.
    /// @see location
    auto vertex_pivot_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::vertex_pivot, idx});
    }

    /// @brief Returns the index at which the box_coord variant is bound.
    /// @see location
    auto box_coord_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::box_coord, idx});
    }

    /// @brief Returns the index at which the vertex_coord variant is bound.
    /// @see location
    auto vertex_coord_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::vertex_coord, idx});
    }

    /// @brief Returns the index at which the face_coord variant is bound.
    /// @see location
    auto face_coord_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::face_coord, idx});
    }

    /// @brief Returns the index at which the wrap_coord variant is bound.
    /// @see location
    auto wrap_coord_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::wrap_coord, idx});
    }

    /// @brief Returns the index at which the color variant is bound.
    /// @see location
    auto color_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::color, idx});
    }

    /// @brief Returns the index at which the weight variant is bound.
    /// @see location
    auto weight_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::weight, idx});
    }

    /// @brief Returns the index at which the roughness variant is bound.
    /// @see location
    auto roughness_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::roughness, idx});
    }

    /// @brief Returns the index at which the occlusion variant is bound.
    /// @see location
    auto occlusion_loc(span_size_t idx = 0) const noexcept
      -> vertex_attrib_location {
        return location({shapes::vertex_attrib_kind::occlusion, idx});
    }

private:
    shared_holder<vertex_attrib_binding_intf> _pimpl;
};
//------------------------------------------------------------------------------
/// @brief Class wrapping a vertex attribute array and buffers storing shape geometry.
/// @see generator
/// @see vertex_attrib_bindings
/// @ingroup shapes
export class geometry {
public:
    /// @brief Default constructor.
    geometry() noexcept = default;
    geometry(geometry&&) noexcept = default;
    geometry(const geometry&) = delete;
    auto operator=(geometry&&) noexcept -> geometry&;
    auto operator=(const geometry&) -> geometry& = delete;
    ~geometry() noexcept = default;

    /// @brief Construction using shape generator, attrib bindings and drawing variant.
    geometry(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      const shapes::drawing_variant var,
      memory::buffer& temp);

    /// @brief Construction using shape generator and attrib bindings.
    geometry(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      memory::buffer& temp)
      : geometry{glapi, shape, bindings, shape.draw_variant(0), temp} {}

    /// @brief Indicates if this geometry wrapper is initialized.
    auto is_initialized() const noexcept -> bool {
        return bool(_vao);
    }

    /// @brief Indicates if this geometry wrapper is initialized.
    /// @see is_initialized
    explicit operator bool() const noexcept {
        return is_initialized();
    }

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
//------------------------------------------------------------------------------
export class geometry_and_bindings
  : public vertex_attrib_bindings
  , public geometry {
public:
    geometry_and_bindings() noexcept = default;
    geometry_and_bindings(geometry_and_bindings&&) noexcept = default;
    geometry_and_bindings(const geometry_and_bindings&&) = delete;
    auto operator=(geometry_and_bindings&&) noexcept
      -> geometry_and_bindings& = default;
    auto operator=(const geometry_and_bindings&&) = delete;
    ~geometry_and_bindings() noexcept = default;

    geometry_and_bindings(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      const shapes::drawing_variant var,
      memory::buffer& temp)
      : vertex_attrib_bindings{bindings}
      , geometry{glapi, shape, bindings, var, temp} {}

    geometry_and_bindings(
      const gl_api& glapi,
      const shape_generator& shape,
      const vertex_attrib_bindings& bindings,
      memory::buffer& temp)
      : vertex_attrib_bindings{bindings}
      , geometry{glapi, shape, bindings, shape.draw_variant(0), temp} {}

    geometry_and_bindings(
      const gl_api& glapi,
      const shape_generator& shape,
      const shapes::drawing_variant var,
      memory::buffer& temp)
      : vertex_attrib_bindings{shape}
      , geometry{glapi, shape, *this, var, temp} {}

    geometry_and_bindings(
      const gl_api& glapi,
      const shape_generator& shape,
      memory::buffer& temp)
      : geometry_and_bindings{glapi, shape, shape.draw_variant(0), temp} {}

    /// @brief Indicates if this instance of geometry and bindings is initialized.
    auto is_initialized() const noexcept -> bool {
        return vertex_attrib_bindings::is_initialized() and
               geometry::is_initialized();
    }

    /// @brief Indicates if this instance of geometry and bindings is initialized.
    /// @see is_initialized
    explicit operator bool() const noexcept {
        return is_initialized();
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
