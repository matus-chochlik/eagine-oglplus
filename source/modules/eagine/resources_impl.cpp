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
class texture_builder : public valtree::object_builder_impl<texture_builder> {
    using base = valtree::object_builder_impl<texture_builder>;

public:
    texture_builder(
      const gl_api& glapi,
      memory::buffer_pool& buffers,
      texture_name tex,
      texture_target target) noexcept
      : _glapi{glapi}
      , _buffers{buffers}
      , _tex{tex}
      , _target{target} {}

    auto append_image_data(const memory::const_block blk) noexcept -> bool;

    void init_decompression(data_compression_method method) noexcept;

    template <typename T>
    void do_add(const basic_string_path& path, span<const T> data) noexcept {
        _forwarder.forward_data(path, data, _info);
    }

    void do_add(
      const basic_string_path& path,
      span<const string_view> data) noexcept {
        if(path.is("data_filter")) {
            auto method{data_compression_method::none};
            if(assign_if_fits(data, method)) {
                init_decompression(method);
            }
        } else {
            _forwarder.forward_data(path, data, _info);
        }
    }

    auto max_token_size() noexcept -> span_size_t final {
        return 64;
    }

    void unparsed_data(span<const memory::const_block> data) noexcept final;

    void begin() noexcept final {
        _success = true;
    }

    auto handle_texture_storage() noexcept -> bool {
        return _info.texture_storage(_tex, _target, _glapi);
    }
    auto handle_texture_image() noexcept -> bool {
        return _info.texture_image(_tex, _target, 0, view(_pixel_data), _glapi);
    }

    auto finish() noexcept -> bool final;

    void failed() noexcept final {
        _buffers.eat(std::move(_pixel_data));
        _success = false;
    }

private:
    const gl_api& _glapi;
    memory::buffer_pool& _buffers;
    memory::buffer _pixel_data;
    stream_decompression _decompression;
    valtree::object_builder_data_forwarder _forwarder;
    texture_name _tex;
    texture_target _target;
    texture_build_info _info;
    bool _success{false};
};
//------------------------------------------------------------------------------
void texture_builder::unparsed_data(
  span<const memory::const_block> data) noexcept {
    if(!_decompression.is_initialized()) {
        init_decompression(data_compression_method::none);
    }
    if(_success) {
        for(const auto& blk : data) {
            _decompression.next(blk);
        }
    }
}
//------------------------------------------------------------------------------
void texture_builder::init_decompression(
  data_compression_method method) noexcept {
    _pixel_data =
      _buffers.get(_info.dimensions() * extract_or(_info.channels, 1));
    _pixel_data.clear();
    _decompression = stream_decompression{
      data_compressor{method, _buffers},
      make_callable_ref<&texture_builder::append_image_data>(this),
      method};
}
//------------------------------------------------------------------------------
auto texture_builder::append_image_data(const memory::const_block blk) noexcept
  -> bool {
    memory::append_to(blk, _pixel_data);
    //  TODO: progressive image specification once we have enough
    //  data for width * some constant so that the temp buffer
    //  doesn't get too big
    return true;
}
//------------------------------------------------------------------------------
auto texture_builder::finish() noexcept -> bool {
    if(_success) {
        _decompression.finish();
        if(_info.is_complete()) {
            _success &= handle_texture_storage();
            if(_success && !_pixel_data.empty()) {
                _success &= handle_texture_image();
            }
        } else {
            _success = false;
        }
    }
    _buffers.eat(std::move(_pixel_data));
    return _success;
}
//------------------------------------------------------------------------------
auto make_texture_builder(
  const gl_api& glapi,
  memory::buffer_pool& buffers,
  texture_name tex,
  texture_target target) noexcept -> std::unique_ptr<valtree::object_builder> {
    return std::make_unique<texture_builder>(glapi, buffers, tex, target);
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

