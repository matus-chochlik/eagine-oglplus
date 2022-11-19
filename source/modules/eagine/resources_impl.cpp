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
import eagine.core.string;
import eagine.core.utility;
import eagine.core.runtime;
import eagine.core.reflection;
import eagine.core.value_tree;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
class gl_texture_builder
  : public valtree::object_builder_impl<gl_texture_builder> {
    using base = valtree::object_builder_impl<gl_texture_builder>;

public:
    gl_texture_builder(
      memory::buffer_pool& buffers,
      texture_name tex,
      texture_target target) noexcept
      : _buffers{buffers}
      , _tex{tex}
      , _target{target} {}

    auto append_image_data(const memory::const_block blk) noexcept -> bool {
        memory::append_to(blk, _temp);
        //  TODO: progressive image specification once we have enough
        //  data for width * some constant so that the temp buffer
        //  doesn't get too big
        return true;
    }

    void init_decompression(data_compression_method method) noexcept {
        _temp = _buffers.get(
          extract_or(_width, 1) * extract_or(_height, 1) *
          extract_or(_depth, 1) * extract_or(_channels, 1));
        _decompression = stream_decompression{
          data_compressor{method, _buffers},
          make_callable_ref<&gl_texture_builder::append_image_data>(this),
          method};
    }

    template <std::integral T>
    void do_add(const basic_string_path& path, span<const T> data) noexcept {
        if(path.size() == 1) {
            if(path.is("levels")) {
                _success &= assign_if_fits(data, _levels);
            } else if(path.is("width")) {
                _success &= assign_if_fits(data, _width);
            } else if(path.is("height")) {
                _success &= assign_if_fits(data, _height);
            } else if(path.is("depth")) {
                _success &= assign_if_fits(data, _depth);
            } else if(path.is("channels")) {
                _success &= assign_if_fits(data, _channels);
                if(_channels > 16) {
                    _channels = 16;
                }
            }
        }
    }

    void do_add(
      const basic_string_path& path,
      span<const string_view> data) noexcept {
        if(path.size() == 1) {
            if(path.is("data_type")) {
                _success &= assign_if_fits(data, _data_type);
            } else if(path.is("format")) {
                _success &= assign_if_fits(data, _format);
            } else if(path.is("iformat")) {
                _success &= assign_if_fits(data, _iformat);
            } else if(path.is("data_filter")) {
                auto method{data_compression_method::none};
                if(assign_if_fits(data, method)) {
                    init_decompression(method);
                }
            }
        }
    }

    template <typename T>
    void do_add(const basic_string_path&, span<const T>) noexcept {}

    void unparsed_data(span<const memory::const_block> data) noexcept final {
        if(!_decompression.is_initialized()) {
            init_decompression(data_compression_method::none);
        }
        if(_success) {
            for(const auto& blk : data) {
                _decompression.next(blk);
            }
        }
    }

    void begin() noexcept final {
        _success = true;
    }

    void finish() noexcept final {
        if(_success) {
            _decompression.finish();
            // extract(parent).handle_gl_texture_image(
            //_target, _params, _temp);
        } else {
            // extract(parent).mark_finished();
        }
        _buffers.eat(std::move(_temp));
    }

    void failed() noexcept final {
        _success = false;
    }

private:
    memory::buffer_pool& _buffers;
    memory::buffer _temp;
    stream_decompression _decompression;
    texture_name _tex;
    texture_target _target;
    std::optional<gl_types::int_type> _levels;
    std::optional<gl_types::int_type> _channels;
    std::optional<gl_types::sizei_type> _width;
    std::optional<gl_types::sizei_type> _height;
    std::optional<gl_types::sizei_type> _depth;
    std::optional<pixel_data_type> _data_type;
    std::optional<pixel_format> _format;
    std::optional<pixel_internal_format> _iformat;
    bool _success{false};
};
//------------------------------------------------------------------------------
auto make_gl_texture_builder(
  memory::buffer_pool& buffers,
  texture_name tex,
  texture_target target) noexcept -> std::unique_ptr<valtree::object_builder> {
    return std::make_unique<gl_texture_builder>(buffers, tex, target);
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

