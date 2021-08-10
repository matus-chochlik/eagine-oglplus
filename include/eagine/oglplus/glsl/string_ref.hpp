/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_GLSL_STRING_REF_HPP
#define EAGINE_OGLPLUS_GLSL_STRING_REF_HPP

#include "source_ref.hpp"
#include <eagine/memory/block.hpp>

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Reference to a GLSL source code string.
/// @ingroup glsl_utils
class glsl_string_ref {
public:
    /// @brief Alias for string character type.
    using char_type = gl_types::char_type;

    /// @brief Alias for signed intever type.
    using int_type = gl_types::int_type;

    /// @brief Construction from a C-string and a length value.
    glsl_string_ref(const char* src_str, const span_size_t n) noexcept
      : _src_str{static_cast<const char_type*>(src_str)}
      , _length{int_type(n == 0 ? 0 : (src_str[n - 1] == '\0' ? n - 1 : n))} {}

    /// @brief Explicit construction from a string_view.
    explicit glsl_string_ref(const string_view str) noexcept
      : glsl_string_ref(str.data(), str.size()) {}

    /// @brief Explicit construction from a memory const_block.
    explicit glsl_string_ref(const memory::const_block blk) noexcept
      : glsl_string_ref(as_chars(blk)) {}

    /// @brief Conversion to glsl_source_ref
    operator glsl_source_ref() const noexcept {
        return glsl_source_ref(1, &_src_str, &_length);
    }

private:
    mutable const char_type* _src_str{nullptr};
    int_type _length{0};
};
//------------------------------------------------------------------------------
/// @brief Wrapper class for a GLSL string literal, convertible to glsl_source_ref.
/// @ingroup glsl_utils
/// @see glsl_source_ref
class glsl_literal : public glsl_string_ref {
public:
    /// @brief Construction from a zero-terminated string literal.
    template <span_size_t N>
    glsl_literal(const char (&src_str)[N]) noexcept
      : glsl_string_ref(static_cast<const char*>(src_str), N) {}
};
//------------------------------------------------------------------------------
/// @brief User defined literal for GLSL source code strings.
/// @ingroup glsl_utils
static inline auto operator"" _glsl(
  const char* src_str,
  const std::size_t n) noexcept -> glsl_string_ref {
    return {src_str, span_size(n)};
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

#endif // EAGINE_OGLPLUS_GLSL_STRING_REF_HPP
