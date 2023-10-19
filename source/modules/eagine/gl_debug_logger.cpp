/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:gl_debug_logger;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.main_ctx;
import :config;

namespace eagine::oglplus {

export class gl_debug_logger : public main_ctx_object {
public:
    void install(const auto& api) const noexcept {
        log_info("GL renderer: ${renderer}")
          .tag("GLinfo")
          .arg("vendor", api.get_vendor().value_or("N/A"))
          .arg("renderer", api.get_renderer().value_or("N/A"))
          .arg("version", api.get_version().value_or("N/A"));

        api.debug_message_callback(*this);
    }

    gl_debug_logger(main_ctx_parent parent)
      : main_ctx_object{"GLDbgLoger", parent} {}

    gl_debug_logger(main_ctx_parent parent, const auto& api)
      : gl_debug_logger{parent} {
        install(api);
    }

    auto callback() const noexcept -> decltype(auto) {
        return &_callback;
    }

    auto data() const noexcept -> const void* {
        return static_cast<const void*>(this);
    }

private:
    auto _do_log(const gl_types::enum_type severity, const string_view msg)
      const noexcept;

    void _log(
      const gl_types::enum_type source,
      const gl_types::enum_type type,
      const gl_types::uint_type id,
      const gl_types::enum_type severity,
      const gl_types::sizei_type length,
      const gl_types::char_type* message) const noexcept;

    static void _callback(
      gl_types::enum_type source,
      gl_types::enum_type type,
      gl_types::uint_type id,
      gl_types::enum_type severity,
      gl_types::sizei_type length,
      const gl_types::char_type* message,
      const void* raw_this);
};
} // namespace eagine::oglplus

