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
          extract_or(_info.width, 1) * extract_or(_info.height, 1) *
          extract_or(_info.depth, 1) * extract_or(_info.channels, 1));
        _decompression = stream_decompression{
          data_compressor{method, _buffers},
          make_callable_ref<&texture_builder::append_image_data>(this),
          method};
    }

    template <typename T>
    void do_add(const basic_string_path& path, span<const T> data) noexcept {
        _forwarder.forward_data(path, data, _info);
    }

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
            // extract(parent).handle_texture_image(
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
    valtree::object_builder_data_forwarder _forwarder;
    texture_name _tex;
    texture_target _target;
    texture_build_info _info;
    bool _success{false};
};
//------------------------------------------------------------------------------
auto make_texture_builder(
  memory::buffer_pool& buffers,
  texture_name tex,
  texture_target target) noexcept -> std::unique_ptr<valtree::object_builder> {
    return std::make_unique<texture_builder>(buffers, tex, target);
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

