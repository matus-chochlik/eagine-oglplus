/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:gpu_program;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.valid_if;
import eagine.shapes;
import :config;
import :enum_types;
import :objects;
import :glsl_source;
import :prog_var_loc;
import :shapes;
import :api;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Class managing the mapping of program input variable to attrib location.
/// @ingroup gl_api_wrap
/// @see vertex_attrib_bindings
export class program_input_bindings {
public:
    /// @brief Indicates is this instance of bindings is initialized.
    auto is_initialized() const noexcept -> bool {
        return not _mapping.empty();
    }

    /// @brief Indicates is this instance of bindings is initialized.
    /// @see is_initialized
    explicit operator bool() const noexcept {
        return is_initialized();
    }

    /// @brief Returns the count of input attributes.
    auto count() const noexcept -> span_size_t;

    /// @brief Adds mapping from input variable name to vertex attribute variant
    auto add(std::string name, shapes::vertex_attrib_variant vav)
      -> program_input_bindings&;

    /// @brief Applies this mapping and vertex attribute bindings to a program.
    auto apply(
      const gl_api& glapi,
      program_name prog,
      const vertex_attrib_bindings& bindings) const noexcept -> bool;

    /// @brief Clear the bindings.
    auto clear() noexcept -> program_input_bindings&;

private:
    shapes::vertex_attrib_map<std::string> _mapping;
};
//------------------------------------------------------------------------------
export class gpu_program : public owned_program_name {
    using base = owned_program_name;

public:
    auto create(const gl_api& glapi) -> gpu_program& {
        glapi.create_program() >> static_cast<base&>(*this);
        return *this;
    }

    auto label(const gl_api& glapi, string_view lbl) -> gpu_program& {
        glapi.object_label(*this, lbl);
        return *this;
    }

    auto add_shader(
      const gl_api& glapi,
      shader_type shdr_type,
      const glsl_source_ref& shdr_src) -> gpu_program& {
        glapi.add_shader(*this, shdr_type, shdr_src);
        return *this;
    }

    auto add_shader(
      const gl_api& glapi,
      shader_type shdr_type,
      const glsl_source_ref& shdr_src,
      const string_view label) -> gpu_program& {
        glapi.add_shader(*this, shdr_type, shdr_src, label);
        return *this;
    }

    auto link(const gl_api& glapi) -> gpu_program& {
        glapi.link_program(*this);
        return *this;
    }

    auto use(const gl_api& glapi) -> gpu_program& {
        glapi.use_program(*this);
        return *this;
    }

    auto get_uniform_location(const gl_api& glapi, string_view name) -> auto {
        return glapi.get_uniform_location(*this, name);
    }

    auto get_uniform_block_index(const gl_api& glapi, string_view name)
      -> auto {
        return glapi.get_uniform_block_index(*this, name);
    }

    auto query(const gl_api& glapi, string_view name, uniform_location& loc)
      -> gpu_program& {
        get_uniform_location(glapi, name) >> loc;
        return *this;
    }

    auto query(const gl_api& glapi, string_view name, uniform_block_index& ubi)
      -> gpu_program& {
        get_uniform_block_index(glapi, name) >> ubi;
        return *this;
    }

    template <typename T>
    auto set(const gl_api& glapi, uniform_location loc, T&& value)
      -> gpu_program& {
        glapi.set_uniform(*this, loc, std::forward<T>(value));
        return *this;
    }

    auto bind(const gl_api& glapi, vertex_attrib_location loc, string_view name)
      -> gpu_program& {
        glapi.bind_attrib_location(*this, loc, name);
        return *this;
    }

    auto bind(
      const gl_api& glapi,
      uniform_block_index blk_idx,
      gl_types::uint_type binding) -> gpu_program& {
        glapi.uniform_block_binding(*this, blk_idx, binding);
        return *this;
    }

    auto clean_up(const gl_api& glapi) -> gpu_program& {
        glapi.clean_up(static_cast<base&&>(*this));
        return *this;
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

