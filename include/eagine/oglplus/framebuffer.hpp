/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_FRAMEBUFFER_HPP
#define EAGINE_OGLPLUS_FRAMEBUFFER_HPP

#include "basic_gl_api.hpp"
#include <eagine/integer_range.hpp>
#include <algorithm>

namespace eagine::oglplus {

class offscreen_framebuffer;

class framebuffer_configuration {
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
      bool is_texture) noexcept -> framebuffer_configuration& {
        if(auto pos{std::find_if(
             _color_attchs.begin(),
             _color_attchs.end(),
             [=](const auto& entry) {
                 return (entry.format == format) &&
                        (entry.iformat == iformat) &&
                        (entry.data_type == data_type) &&
                        (entry.is_texture == is_texture);
             })};
           pos != _color_attchs.end()) {
            ++pos->count;
        } else {
            attch_info entry;
            entry.format = format;
            entry.iformat = iformat;
            entry.data_type = data_type;
            entry.is_texture = is_texture;
            entry.count = 1;
            _color_attchs.push_back(entry);
        }
        return *this;
    }

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
      bool is_texture) noexcept -> framebuffer_configuration& {
        _depth_attch.format = _glapi.depth_component;
        _depth_attch.iformat = iformat;
        _depth_attch.data_type = data_type;
        _depth_attch.count = 1;
        _depth_attch.is_texture = is_texture;
        return *this;
    }

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
      bool is_texture) noexcept -> framebuffer_configuration& {
        _stencil_attch.format = _glapi.stencil;
        _stencil_attch.iformat = iformat;
        _stencil_attch.data_type = data_type;
        _stencil_attch.count = 1;
        _stencil_attch.is_texture = is_texture;
        return *this;
    }

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

    auto texture_count() const noexcept -> span_size_t {
        auto result{span_size(std::count_if(
          _color_attchs.begin(), _color_attchs.end(), [](const auto& entry) {
              return entry.is_texture;
          }))};
        if(_depth_attch.is_texture) {
            result += _depth_attch.count;
        }
        if(_stencil_attch.is_texture) {
            result += _stencil_attch.count;
        }

        return result;
    }

    auto renderbuffer_count() const noexcept -> span_size_t {
        auto result{std::accumulate(
          _color_attchs.begin(),
          _color_attchs.end(),
          span_size(0),
          [](const auto state, const auto& entry) {
              return state + (entry.is_texture ? 0 : entry.count);
          })};
        if(!_depth_attch.is_texture) {
            result += _depth_attch.count;
        }
        if(!_stencil_attch.is_texture) {
            result += _stencil_attch.count;
        }

        return result;
    }

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
      const attch_info& entry) const noexcept {
        const auto& [gl, GL] = _glapi;
        gl.active_texture(GL.texture0 + units[i]);
        gl.bind_texture(GL.texture_2d_array, texs[i]);
        gl.tex_parameter_i(
          GL.texture_2d_array, GL.texture_min_filter, GL.nearest);
        gl.tex_parameter_i(
          GL.texture_2d_array, GL.texture_mag_filter, GL.nearest);
        gl.tex_parameter_i(
          GL.texture_2d_array, GL.texture_wrap_s, GL.clamp_to_border);
        gl.tex_parameter_i(
          GL.texture_2d_array, GL.texture_wrap_t, GL.clamp_to_border);
        gl.tex_parameter_i(
          GL.texture_2d_array, GL.texture_wrap_r, GL.clamp_to_border);
        gl.tex_image3d(
          GL.texture_2d_array,
          0,
          entry.iformat,
          width,
          height,
          integer(entry.count),
          0,
          entry.format,
          entry.data_type,
          memory::const_block());
    }

    void _init(
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      gl_object_name_vector<texture_tag>& texs,
      const span<const gl_types::sizei_type> units) const noexcept {
        texs.resize(integer(texture_count()));
        if(!texs.empty()) {
            const auto& [gl, GL] = _glapi;
            gl.gen_textures(texs);

            span_size_t i{0};
            span_size_t a{0};

            for(const auto& entry : _color_attchs) {
                if(entry.is_texture) {
                    _init_tex(width, height, texs, units, i, entry);
                    for(const integer l : integer_range(entry.count)) {
                        gl.framebuffer_texture_layer(
                          GL.draw_framebuffer,
                          GL.color_attachment0 + a,
                          texs[i],
                          0,
                          l);
                        ++a;
                    }
                    ++i;
                }
            }
            if(_depth_attch.count > 0) {
                if(_depth_attch.is_texture) {
                    _init_tex(width, height, texs, units, i, _depth_attch);
                    gl.framebuffer_texture_layer(
                      GL.draw_framebuffer, GL.depth_attachment, texs[i], 0, 0);
                    ++i;
                }
            }
            if(_stencil_attch.count > 0) {
                if(_stencil_attch.is_texture) {
                    _init_tex(width, height, texs, units, i, _stencil_attch);
                    gl.framebuffer_texture_layer(
                      GL.draw_framebuffer, GL.stencil_attachment, texs[i], 0, 0);
                    ++i;
                }
            }
        }
    }

    void _init_rbo(
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      gl_object_name_vector<renderbuffer_tag>& rbos,
      span_size_t i,
      const attch_info& entry) const noexcept {
        const auto& [gl, GL] = _glapi;
        gl.bind_renderbuffer(GL.renderbuffer, rbos[i]);
        gl.renderbuffer_storage(GL.renderbuffer, entry.iformat, width, height);
    }

    void _init(
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      gl_object_name_vector<renderbuffer_tag>& rbos) const noexcept {
        rbos.resize(integer(renderbuffer_count()));
        span_size_t i{0};
        if(!rbos.empty()) {
            const auto& [gl, GL] = _glapi;
            gl.gen_renderbuffers(rbos);
            for(const auto& entry : _color_attchs) {
                if(!entry.is_texture) {
                    _init_rbo(width, height, rbos, i, entry);
                    gl.framebuffer_renderbuffer(
                      GL.draw_framebuffer,
                      GL.color_attachment0 + i,
                      GL.renderbuffer,
                      rbos[i]);
                    ++i;
                }
            }
            if(_depth_attch.count > 0) {
                if(!_depth_attch.is_texture) {
                    _init_rbo(width, height, rbos, i, _depth_attch);
                    gl.framebuffer_renderbuffer(
                      GL.draw_framebuffer,
                      GL.depth_attachment,
                      GL.renderbuffer,
                      rbos[i]);
                    ++i;
                }
            }
            if(_stencil_attch.count > 0) {
                if(!_stencil_attch.is_texture) {
                    _init_rbo(width, height, rbos, i, _stencil_attch);
                    gl.framebuffer_renderbuffer(
                      GL.draw_framebuffer,
                      GL.stencil_attachment,
                      GL.renderbuffer,
                      rbos[i]);
                    ++i;
                }
            }
        }
    }
};

class offscreen_framebuffer : public owned_framebuffer_name {
    using base = owned_framebuffer_name;

public:
    auto init(
      const gl_api& glapi,
      gl_types::sizei_type width,
      gl_types::sizei_type height,
      const framebuffer_configuration& config,
      const span<const gl_types::sizei_type> tex_units)
      -> offscreen_framebuffer& {
        _width = width;
        _height = height;
        const auto& [gl, GL] = glapi;
        gl.gen_framebuffers() >> static_cast<base&>(*this);
        gl.bind_framebuffer(GL.draw_framebuffer, *this);

        config._init(_width, _height, _textures, tex_units);
        config._init(_width, _height, _renderbuffers);

        gl.bind_framebuffer(GL.draw_framebuffer, default_framebuffer);

        return *this;
    }

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
      -> offscreen_framebuffer& {
        if(_width != width || _height != height) {
            _width = width;
            _height = height;

            // TODO: just update what is necessary
            clean_up(glapi);
            init(glapi, width, height, config, tex_units);
        }
        return *this;
    }

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

#endif
