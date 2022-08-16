/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include <cassert>

export module eagine.oglplus:gl_debug_logger;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.main_ctx;
import :config;

namespace eagine::oglplus {

class gl_debug_logger : public main_ctx_object {
public:
    gl_debug_logger(main_ctx_parent parent)
      : main_ctx_object{"GLDbgLoger", parent} {}

    auto callback() const noexcept -> decltype(auto) {
        return &_callback;
    }

    auto data() const noexcept -> const void* {
        return static_cast<const void*>(this);
    }

private:
    void _do_log(
      [[maybe_unused]] const gl_types::enum_type source,
      [[maybe_unused]] const gl_types::enum_type type,
      [[maybe_unused]] const gl_types::uint_type id,
      [[maybe_unused]] const gl_types::enum_type severity,
      [[maybe_unused]] const gl_types::sizei_type length,
      [[maybe_unused]] const gl_types::char_type* message) const {
        const auto msg = length >= 0 ? string_view(message, span_size(length))
                                     : string_view(message);
        this->log_debug(msg)
          .arg("severity", "DbgOutSvrt", severity)
          .arg("source", "DbgOutSrce", source)
          .arg("type", "DbgOutType", type)
          .arg("id", id);
    }

    static void _callback(
      gl_types::enum_type source,
      gl_types::enum_type type,
      gl_types::uint_type id,
      gl_types::enum_type severity,
      gl_types::sizei_type length,
      const gl_types::char_type* message,
      const void* raw_this) {
        assert(raw_this);
        static_cast<const gl_debug_logger*>(raw_this)->_do_log(
          source, type, id, severity, length, message);
    }
};
} // namespace eagine::oglplus

