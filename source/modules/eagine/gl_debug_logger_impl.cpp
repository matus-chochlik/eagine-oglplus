/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#include <cassert>

module eagine.oglplus;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.main_ctx;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
auto gl_debug_logger::_do_log(
  [[maybe_unused]] const gl_types::enum_type severity,
  const string_view msg) const noexcept {
    switch(severity) {
        case 0x9146:
            return this->log_error(msg);
        case 0x9147:
            return this->log_warning(msg);
        default:
            return this->log_debug(msg);
    }
}
//------------------------------------------------------------------------------
void gl_debug_logger::_log(
  [[maybe_unused]] const gl_types::enum_type source,
  [[maybe_unused]] const gl_types::enum_type type,
  [[maybe_unused]] const gl_types::uint_type id,
  [[maybe_unused]] const gl_types::enum_type severity,
  [[maybe_unused]] const gl_types::sizei_type length,
  [[maybe_unused]] const gl_types::char_type* message) const noexcept {
    const auto msg = length >= 0 ? string_view(message, span_size(length))
                                 : string_view(message);
    _do_log(severity, msg)
      .arg("severity", "DbgOutSvrt", severity)
      .arg("source", "DbgOutSrce", source)
      .arg("type", "DbgOutType", type)
      .arg("id", id);
}
//------------------------------------------------------------------------------
void gl_debug_logger::_callback(
  gl_types::enum_type source,
  gl_types::enum_type type,
  gl_types::uint_type id,
  gl_types::enum_type severity,
  gl_types::sizei_type length,
  const gl_types::char_type* message,
  const void* raw_this) {
    assert(raw_this);
    static_cast<const gl_debug_logger*>(raw_this)->_log(
      source, type, id, severity, length, message);
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
