/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_BASIC_GL_API_HPP
#define EAGINE_OGLPLUS_BASIC_GL_API_HPP

#include "gl_api/api.hpp"
#include "gl_api/api_traits.hpp"
#include "gl_api/constants.hpp"
#include <eagine/integer_range.hpp>
#include <eagine/math/tmat.hpp>
//
#include "utils/image_file.hpp"
#include "utils/program_file.hpp"

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Combined wrapper for the GL API operations and constants.
/// @ingroup gl_api_wrap
/// @see gl_api_traits
/// @see gl_api
template <typename ApiTraits>
class basic_gl_api
  : protected ApiTraits
  , public basic_gl_operations<ApiTraits>
  , public basic_gl_constants<ApiTraits> {

public:
    template <typename R>
    using combined_result = typename ApiTraits::template combined_result<R>;

    using int_type = typename gl_types::int_type;
    using float_type = typename gl_types::float_type;

    /// @brief Constructor using API traits..
    basic_gl_api(ApiTraits traits)
      : ApiTraits{std::move(traits)}
      , basic_gl_operations<ApiTraits>{*static_cast<ApiTraits*>(this)}
      , basic_gl_constants<ApiTraits>{
          *static_cast<ApiTraits*>(this),
          *static_cast<basic_gl_operations<ApiTraits>*>(this)} {}

    /// @brief Default constructor.
    basic_gl_api()
      : basic_gl_api{ApiTraits{}} {}

    /// @brief Returns a reference to the wrapped operations.
    auto operations() const noexcept -> const basic_gl_operations<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped operations.
    auto operator()() const noexcept -> const basic_gl_operations<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped constants.
    auto constants() const noexcept -> const basic_gl_constants<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped constants.
    auto operator~() const noexcept -> const basic_gl_constants<ApiTraits>& {
        return *this;
    }

    // convenience functions
    constexpr auto true_or_false(const bool b) const noexcept -> true_false {
        return b ? true_false(this->true_) : true_false(this->false_);
    }

    /// @brief Compiles and attaches a shader to the specified program.
    /// @see build_program
    auto add_shader(
      const program_name prog,
      shader_type shdr_type,
      const glsl_source_ref& shdr_src) const -> combined_result<void> {
        owned_shader_name shdr;
        this->create_shader(shdr_type) >> shdr;
        auto cleanup = this->delete_shader.raii(shdr);
        this->shader_source(shdr, shdr_src);
        this->compile_shader(shdr);
        return this->attach_shader(prog, shdr);
    }

    /// @brief Compiles and attaches a shader to the specified program.
    /// @see build_program
    auto add_shader(
      const program_name prog,
      shader_type shdr_type,
      const glsl_source_ref& shdr_src,
      const string_view label) const -> combined_result<void> {
        owned_shader_name shdr;
        this->create_shader(shdr_type) >> shdr;
        auto cleanup = this->delete_shader.raii(shdr);
        this->object_label(shdr, label);
        this->shader_source(shdr, shdr_src);
        this->compile_shader(shdr);
        return this->attach_shader(prog, shdr);
    }

    /// @brief Compiles and attaches a shader to the specified program.
    /// @see build_program
    auto add_shader(
      const program_name prog,
      const shader_source_block& shdr_src_blk) const -> combined_result<void> {
        return add_shader(prog, shdr_src_blk.type(), shdr_src_blk);
    }

    /// @brief Compiles and attaches a shader to the specified program.
    /// @see build_program
    auto add_shader(
      const program_name prog,
      const shader_source_block& shdr_src_blk,
      const string_view label) const -> combined_result<void> {
        return add_shader(prog, shdr_src_blk.type(), shdr_src_blk, label);
    }

    /// @brief Builds a shader program from the specified sources.
    /// @see add_shader
    auto build_program(
      const program_name prog,
      const program_source_block& prog_src_blk) const -> combined_result<void> {
        if(prog_src_blk.is_valid()) {
            const span_size_t n = prog_src_blk.shader_source_count();
            for(const auto i : integer_range(n)) {
                add_shader(prog, prog_src_blk.shader_source(i));
            }
        }
        return this->link_program(prog);
    }

    /// @brief Builds a shader program from the sources in a baked memory block.
    auto build_program(
      const program_name prog,
      const memory::const_block prog_src_blk) const -> combined_result<void> {
        return build_program(prog, program_source_block(prog_src_blk));
    }

    // set_uniform
private:
    template <typename ProgramUniformFunc, typename UniformFunc, typename T>
    auto _set_uniform(
      ProgramUniformFunc& program_uniform_func,
      UniformFunc& uniform_func,
      const program_name prog,
      const uniform_location loc,
      T&& value) const -> combined_result<void> {
        if(program_uniform_func) {
            return program_uniform_func(prog, loc, std::forward<T>(value));
        } else {
            if(auto use_res{this->use_program(prog)}) {
                return uniform_func(loc, std::forward<T>(value));
            } else {
                return use_res;
            }
        }
    }

    template <typename ProgramUniformFunc, typename UniformFunc, typename T>
    auto _set_uniform_matrix(
      ProgramUniformFunc& program_uniform_func,
      UniformFunc& uniform_func,
      const program_name prog,
      const uniform_location loc,
      T&& value,
      true_false transpose) const -> combined_result<void> {
        if(program_uniform_func) {
            return program_uniform_func(
              prog, loc, transpose, std::forward<T>(value));
        } else {
            if(auto use_res{this->use_program(prog)}) {
                return uniform_func(loc, transpose, std::forward<T>(value));
            } else {
                return use_res;
            }
        }
    }

public:
    // int
    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const int_type value) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1i, this->uniform1i, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const int_type> value,
      const type_identity<int_type[1]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1iv, this->uniform1iv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const int_type> value,
      const type_identity<int_type[2]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform2iv, this->uniform2iv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const int_type> value,
      const type_identity<int_type[3]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform3iv, this->uniform3iv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const int_type> value,
      const type_identity<int_type[4]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform4iv, this->uniform4iv, prog, loc, value);
    }

    // float
    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const float_type value) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1f, this->uniform1f, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const type_identity<float_type[1]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1fv, this->uniform1fv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const type_identity<float_type[2]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform2fv, this->uniform2fv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const type_identity<float_type[3]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform3fv, this->uniform3fv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const type_identity<float_type[4]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform4fv, this->uniform4fv, prog, loc, value);
    }

    template <typename T>
    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const T& value) const
      -> combined_result<void> requires(is_known_vector_type_v<T>) {
        return set_uniform(
          prog, loc, element_view(value), canonical_compound_type<T>());
    }

    // uniform matrix
    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[2][2]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix2fv,
          this->uniform_matrix2fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[2][3]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix2x3fv,
          this->uniform_matrix2x3fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[2][4]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix2x4fv,
          this->uniform_matrix2x4fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[3][2]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix3x2fv,
          this->uniform_matrix3x2fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[3][3]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix3fv,
          this->uniform_matrix3fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[3][4]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix3x4fv,
          this->uniform_matrix3x4fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[4][2]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix4x2fv,
          this->uniform_matrix4x2fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[4][3]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix4x3fv,
          this->uniform_matrix4x3fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const type_identity<float_type[4][4]>) const -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix4fv,
          this->uniform_matrix4fv,
          prog,
          loc,
          value,
          transpose);
    }

    template <typename T>
    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const T& value) const
      -> combined_result<void> requires(is_known_matrix_type_v<T>) {
        return set_uniform_matrix(
          prog,
          loc,
          element_view(value),
          true_or_false(math::is_row_major_v<T>),
          canonical_compound_type<T>());
    }

    // texture image
    auto spec_tex_image1d(
      const texture_target tex_tgt,
      const gl_types::int_type level,
      const gl_types::int_type border,
      const image_spec& image) const -> combined_result<void> {
        return this->tex_image1d(
          tex_tgt,
          level,
          image.internal_format(),
          image.width(),
          border,
          image.format(),
          image.type(),
          image.data());
    }

    auto spec_tex_image2d(
      const texture_target tex_tgt,
      const gl_types::int_type level,
      const gl_types::int_type border,
      const image_spec& image) const -> combined_result<void> {
        return this->tex_image2d(
          tex_tgt,
          level,
          image.internal_format(),
          image.width(),
          image.height(),
          border,
          image.format(),
          image.type(),
          image.data());
    }

    auto spec_tex_image3d(
      const texture_target tex_tgt,
      const gl_types::int_type level,
      const gl_types::int_type border,
      const image_spec& image) const -> combined_result<void> {
        return this->tex_image3d(
          tex_tgt,
          level,
          image.internal_format(),
          image.width(),
          image.height(),
          image.depth(),
          border,
          image.format(),
          image.type(),
          image.data());
    }

    auto spec_tex_image_cube(
      const gl_types::int_type level,
      const gl_types::int_type border,
      const image_spec& image) const {
        this->tex_image2d(
          this->texture_cube_map_positive_x,
          level,
          image.internal_format(),
          image.width(),
          image.height(),
          border,
          image.format(),
          image.type(),
          image.data_slice2d(0));
        this->tex_image2d(
          this->texture_cube_map_negative_x,
          level,
          image.internal_format(),
          image.width(),
          image.height(),
          border,
          image.format(),
          image.type(),
          image.data_slice2d(1));
        this->tex_image2d(
          this->texture_cube_map_positive_y,
          level,
          image.internal_format(),
          image.width(),
          image.height(),
          border,
          image.format(),
          image.type(),
          image.data_slice2d(2));
        this->tex_image2d(
          this->texture_cube_map_negative_y,
          level,
          image.internal_format(),
          image.width(),
          image.height(),
          border,
          image.format(),
          image.type(),
          image.data_slice2d(3));
        this->tex_image2d(
          this->texture_cube_map_positive_z,
          level,
          image.internal_format(),
          image.width(),
          image.height(),
          border,
          image.format(),
          image.type(),
          image.data_slice2d(4));
        this->tex_image2d(
          this->texture_cube_map_negative_z,
          level,
          image.internal_format(),
          image.width(),
          image.height(),
          border,
          image.format(),
          image.type(),
          image.data_slice2d(5));
    }
};

template <std::size_t I, typename ApiTraits>
auto get(const basic_gl_api<ApiTraits>& x) noexcept -> const
  typename std::tuple_element<I, basic_gl_api<ApiTraits>>::type& {
    return x;
}
//------------------------------------------------------------------------------
template <typename A>
auto translate(const basic_gl_api<A>& api, const bool value) noexcept
  -> true_false {
    if(value) {
        return api.true_;
    }
    return api.false_;
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std {
//------------------------------------------------------------------------------
template <typename ApiTraits>
struct tuple_size<eagine::oglplus::basic_gl_api<ApiTraits>>
  : public std::integral_constant<std::size_t, 2> {};

template <typename ApiTraits>
struct tuple_element<0, eagine::oglplus::basic_gl_api<ApiTraits>> {
    using type = eagine::oglplus::basic_gl_operations<ApiTraits>;
};

template <typename ApiTraits>
struct tuple_element<1, eagine::oglplus::basic_gl_api<ApiTraits>> {
    using type = eagine::oglplus::basic_gl_constants<ApiTraits>;
};
//------------------------------------------------------------------------------
} // namespace std

#endif // EAGINE_OGLPLUS_BASIC_GL_API_HPP
