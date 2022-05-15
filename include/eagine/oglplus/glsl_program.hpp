/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_GLSL_PROGRAM_HPP
#define EAGINE_OGLPLUS_GLSL_PROGRAM_HPP

#include "basic_gl_api.hpp"
#include "gl_api/prog_var_loc.hpp"

namespace eagine::oglplus {

class glsl_program : public owned_program_name {
    using base = owned_program_name;

public:
    auto create(const gl_api& glapi) -> glsl_program& {
        glapi.create_program() >> static_cast<base&>(*this);
        return *this;
    }

    auto label(const gl_api& glapi, string_view lbl) -> glsl_program& {
        glapi.object_label(*this, lbl);
        return *this;
    }

    auto add_shader(
      const gl_api& glapi,
      oglplus::shader_type shdr_type,
      const oglplus::glsl_source_ref& shdr_src) -> glsl_program& {
        glapi.add_shader(*this, shdr_type, shdr_src);
        return *this;
    }

    auto add_shader(
      const gl_api& glapi,
      oglplus::shader_type shdr_type,
      const oglplus::glsl_source_ref& shdr_src,
      const string_view label) -> glsl_program& {
        glapi.add_shader(*this, shdr_type, shdr_src, label);
        return *this;
    }

    auto add_shader(
      const gl_api& glapi,
      const oglplus::shader_source_block& shdr_src_blk) -> glsl_program& {
        glapi.add_shader(*this, shdr_src_blk);
        return *this;
    }

    auto add_shader(
      const gl_api& glapi,
      const oglplus::shader_source_block& shdr_src_blk,
      const string_view label) -> glsl_program& {
        glapi.add_shader(*this, shdr_src_blk, label);
        return *this;
    }

    auto link(const gl_api& glapi) -> glsl_program& {
        glapi.link_program(*this);
        return *this;
    }

    auto build(
      const gl_api& glapi,
      const oglplus::program_source_block& prog_src_blk) -> glsl_program& {
        glapi.build_program(*this, prog_src_blk);
        return *this;
    }

    auto init(
      const gl_api& glapi,
      const oglplus::program_source_block& prog_src_blk) -> glsl_program& {
        return create(glapi).build(glapi, prog_src_blk);
    }

    auto use(const gl_api& glapi) -> glsl_program& {
        glapi.use_program(*this);
        return *this;
    }

    auto get_uniform_location(const gl_api& glapi, string_view name) -> auto {
        return glapi.get_uniform_location(*this, name);
    }

    auto query(
      const gl_api& glapi,
      string_view name,
      oglplus::uniform_location& loc) -> glsl_program& {
        get_uniform_location(glapi, name) >> loc;
        return *this;
    }

    template <typename T>
    auto set(const gl_api& glapi, oglplus::uniform_location loc, T&& value)
      -> glsl_program& {
        glapi.set_uniform(*this, loc, std::forward<T>(value));
        return *this;
    }

    auto bind(
      const gl_api& glapi,
      oglplus::vertex_attrib_location loc,
      string_view name) -> glsl_program& {
        glapi.bind_attrib_location(*this, loc, name);
        return *this;
    }

    auto clean_up(const gl_api& glapi) -> glsl_program& {
        glapi.delete_program(static_cast<base&&>(*this));
        return *this;
    }
};

} // namespace eagine::oglplus

#endif
