/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:framebuffer;
import eagine.core.types;
import eagine.core.memory;
import :config;
import :enum_types;
import :objects;
import :constants;
import :api;
import <algorithm>;
import <vector>;

namespace eagine::oglplus {

export class offscreen_framebuffer;

export class framebuffer_configuration {
    struct attch_info {
        pixel_format format{};
        pixel_internal_format iformat{};
        pixel_data_type data_type{};
        span_size_t count{0};
        bool is_texture{false};
    };

public:
    framebuffer_configuration(const gl_api& glapi) noexcept
      : _glapi{glapi} {}

    auto add_color_attachment(
      pixel_format format,
      pixel_internal_format iformat,
      pixel_data_type data_type,
      bool is_texture) noexcept -> framebuffer_configuration&;

    auto add_color_texture(
      pixel_format format,
      pixel_internal_format iformat,
      pixel_data_type data_type) noexcept -> framebuffer_configuration& {
        return add_color_attachment(format, iformat, data_type, true);
    }

    auto add_color_texture(
      pixel_format format,
      pixel_internal_format iformat) noexcept -> framebuffer_configuration& {
        return add_color_texture(format, iformat, _glapi.unsigned_byte_);
    }

    auto add_color_buffer(
      pixel_format format,
      pixel_internal_format iformat,
      pixel_data_type data_type) noexcept -> framebuffer_configuration& {
        return add_color_attachment(format, iformat, data_type, false);
    }

    auto add_depth_attachment(
      pixel_internal_format iformat,
      pixel_data_type data_type,
      bool is_texture) noexcept -> framebuffer_configuration&;

    auto add_depth_texture(pixel_data_type data_type) noexcept
      -> framebuffer_configuration& {
        return add_depth_attachment(_glapi.depth_component32f, data_type, true);
    }

    auto add_depth_buffer(pixel_data_type data_type) noexcept
      -> framebuffer_configuration& {
        return add_depth_attachment(
          _glapi.depth_component32f, data_type, false);
    }

    auto add_depth_buffer() noexcept -> framebuffer_configuration& {
        return add_depth_buffer(_glapi.float_);
    }

    auto add_stencil_attachment(
      pixel_internal_format iformat,
      pixel_data_type data_type,
      bool is_texture) noexcept -> framebuffer_configuration&;

    auto add_stencil_texture(pixel_data_type data_type) noexcept
      -> framebuffer_configuration& {
        return add_stencil_attachment(_glapi.stencil_index8, data_type, true);
    }

    auto add_stencil_buffer(pixel_data_type data_type) noexcept
      -> framebuffer_configuration& {
        return add_stencil_attachment(_glapi.stencil_index8, data_type, false);
    }

    auto add_stencil_buffer() noexcept -> framebuffer_configuration& {
        return add_stencil_buffer(_glapi.unsigned_byte_);
    }

    auto texture_count() const noexcept -> span_size_t;

    auto renderbuffer_count() const noexcept -> span_size_t;

private:
    friend class offscreen_framebuffer;

    const gl_api& _glapi;
    std::vector<attch_info> _color_attchs;
    attch_info _depth_attch;
    attch_info _stencil_attch;

    void _init_tex(
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      const gl_object_name_vector<texture_tag>& texs,
      const span<const gl_types::sizei_type> units,
      span_size_t i,
      const attch_info& entry) const noexcept;

    void _init(
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      gl_object_name_vector<texture_tag>& texs,
      const span<const gl_types::sizei_type> units) const noexcept;

    void _init_rbo(
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      gl_object_name_vector<renderbuffer_tag>& rbos,
      span_size_t i,
      const attch_info& entry) const noexcept;

    void _init(
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      gl_object_name_vector<renderbuffer_tag>& rbos) const noexcept;
};

export class offscreen_framebuffer : public owned_framebuffer_name {
    using base = owned_framebuffer_name;

public:
    auto init(
      const gl_api& glapi,
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      const framebuffer_configuration& config,
      const span<const gl_types::sizei_type> tex_units)
      -> offscreen_framebuffer&;

    auto label(const gl_api& glapi, string_view lbl) -> offscreen_framebuffer& {
        glapi.object_label(*this, lbl);
        return *this;
    }

    auto width() const noexcept {
        return _width;
    }

    auto height() const noexcept {
        return _height;
    }

    auto bind(const gl_api& glapi) -> offscreen_framebuffer& {
        const auto& [gl, GL] = glapi;
        gl.bind_framebuffer(GL.draw_framebuffer, *this);
        return *this;
    }

    auto bind_default(const gl_api& glapi) -> offscreen_framebuffer& {
        const auto& [gl, GL] = glapi;
        gl.bind_framebuffer(GL.draw_framebuffer, default_framebuffer);
        return *this;
    }

    auto resize(
      const gl_api& glapi,
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      const framebuffer_configuration& config,
      const span<const gl_types::sizei_type> tex_units)
      -> offscreen_framebuffer&;

    auto clean_up(const gl_api& glapi) -> offscreen_framebuffer& {
        glapi.clean_up(_renderbuffers);
        glapi.clean_up(_textures);
        glapi.clean_up(static_cast<base&&>(*this));
        return *this;
    }

private:
    gl_types::sizei_type _width{0};
    gl_types::sizei_type _height{0};
    gl_object_name_vector<texture_tag> _textures;
    gl_object_name_vector<renderbuffer_tag> _renderbuffers;
};

} // namespace eagine::oglplus

