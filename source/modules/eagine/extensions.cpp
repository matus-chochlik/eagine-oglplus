/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:extensions;
import eagine.core.types;
import eagine.core.memory;

namespace eagine::oglplus {

export template <typename ApiTraits>
class basic_gl_operations;

/// @brief Wrapper for GL extension information getter.
/// @ingroup gl_api_wrap
export template <typename ApiTraits>
class basic_gl_extension {
public:
    constexpr basic_gl_extension(
      const string_view name,
      const basic_gl_operations<ApiTraits>& api) noexcept
      : _api{api}
      , _name{name} {}

    /// @brief Tests if this extension is available.
    explicit operator bool() const noexcept {
        return _api.has_extension(_name);
    }

    /// @brief Tests if this extension is available.
    auto operator()() const noexcept -> bool {
        return _api.has_extension(_name);
    }

private:
    const basic_gl_operations<ApiTraits>& _api;
    string_view _name;
};

} // namespace eagine::oglplus

