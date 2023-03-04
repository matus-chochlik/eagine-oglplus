/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include "gl_def.hpp"

#if EAGINE_HAS_GL
extern "C" {

auto glXGetProcAddress(const GLubyte*) -> void*;

} // extern "C"
#endif

export module eagine.oglplus:api_traits;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :result;
import std;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the GL API
/// @ingroup gl_api_wrap
export class gl_api_traits : public c_api::default_traits {
public:
    /// @brief Alias for result type of currently unavailable functions.
    template <typename R>
    using no_result = gl_no_result<R>;

    /// @brief Alias for result type of functions.
    template <typename R>
    using result = gl_result<R>;

    /// @brief Alias for result type of optionally available functions.
    template <typename R>
    using opt_result = gl_opt_result<R>;

    /// @brief Combined result.
    /// @see result
    /// @see opt_result
    /// @see no_result
    template <typename R>
    using combined_result = gl_combined_result<R>;

    /// @brief Links a GL function with the specified name and Signature.
    template <typename Api, typename Tag, typename Signature>
    auto link_function(
      Api&,
      Tag,
      string_view name,
      std::type_identity<Signature>) -> std::add_pointer_t<Signature>;

private:
    std::string _full_name;
};
//------------------------------------------------------------------------------
template <typename Api, typename Tag, typename Signature>
inline auto gl_api_traits::link_function(
  Api&,
  Tag,
  string_view name,
  std::type_identity<Signature>) -> std::add_pointer_t<Signature> {
    _full_name.clear();
    _full_name.reserve(2 + name.size() + 1);
    _full_name.append("gl");
    _full_name.append(name.data(), std::size_t(name.size()));
#if EAGINE_HAS_GL
    auto func = glXGetProcAddress(
      reinterpret_cast<const gl_types::ubyte_type*>(_full_name.c_str()));
    // TODO: support for extension also needs to be checked
    if(func != nullptr) {
        return reinterpret_cast<std::remove_pointer_t<Signature>*>(func);
    }
#endif
    return nullptr;
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

