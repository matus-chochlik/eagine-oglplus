/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#include <cassert>

export module eagine.oglplus:glsl_source;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Class referencing a set of GLSL source code strings.
/// @ingroup glsl_utils
export class glsl_source_ref {
public:
    /// @brief Alias for character string type.
    using char_type = gl_types::char_type;

    /// @brief Alias for integer type.
    using int_type = gl_types::int_type;

    /// @brief Alias for integer type storing size values.
    using sizei_type = gl_types::sizei_type;

    /// @brief Construction from a single C-string and length value.
    constexpr glsl_source_ref(
      const char_type* part,
      const int_type length) noexcept
      : _part{part}
      , _length{length}
      , _count{1}
      , _parts{&_part}
      , _lengths{&_length} {}

    /// @brief Construction from a string_view.
    constexpr glsl_source_ref(string_view source_str) noexcept
      : glsl_source_ref{
          memory::accommodate<const char_type>(source_str).data(),
          eagine::limit_cast<int_type>(source_str.size())} {}

    /// @brief Construction from a string literal.
    template <std::size_t L>
    constexpr glsl_source_ref(const char (&source_str)[L]) noexcept
      : glsl_source_ref{
          reinterpret_cast<const char_type*>(source_str),
          eagine::limit_cast<int_type>(L - 1)} {}

    /// @brief Construction from C-string array and lengths array.
    glsl_source_ref(
      const span_size_t n,
      const char_type** ps,
      const int_type* ls) noexcept
      : _count{eagine::limit_cast<sizei_type>(n)}
      , _parts{ps}
      , _lengths{ls} {
        assert(_count >= 0);
        assert(_parts != nullptr);
    }

    /// @brief Returns the number of source string fragments.
    /// @see parts
    /// @see lengths
    constexpr auto count() const noexcept -> sizei_type {
        return _count;
    }

    /// @brief Returns pointers to the source string fragments.
    /// @see count
    /// @see lengths
    /// The Length of the returned array is at least the value returned by count().
    constexpr auto parts() const noexcept -> const char_type** {
        return _parts;
    }

    /// @brief Returns the lengths of the source string fragments.
    /// @see count
    /// @see parts
    /// The Length of the returned array is at least the value returned by count().
    auto lengths() const noexcept -> const int_type* {
        return _lengths;
    }

private:
    const char_type* _part{nullptr};
    const int_type _length{0};
    sizei_type _count{0};
    const char_type** _parts{nullptr};
    const int_type* _lengths{nullptr};
};
//------------------------------------------------------------------------------
/// @brief Reference to a GLSL source code string.
/// @ingroup glsl_utils
export class glsl_string_ref {
public:
    /// @brief Alias for string character type.
    using char_type = gl_types::char_type;

    /// @brief Alias for signed intever type.
    using int_type = gl_types::int_type;

    /// @brief Construction from a C-string and a length value.
    constexpr glsl_string_ref(const char* src_str, const span_size_t n) noexcept
      : _src_str{static_cast<const char_type*>(src_str)}
      , _length{int_type(n == 0 ? 0 : (src_str[n - 1] == '\0' ? n - 1 : n))} {}

    /// @brief Explicit construction from a string_view.
    constexpr explicit glsl_string_ref(const string_view str) noexcept
      : glsl_string_ref{str.data(), str.size()} {}

    /// @brief Explicit construction from a memory const_block.
    constexpr explicit glsl_string_ref(const memory::const_block blk) noexcept
      : glsl_string_ref{string_view{as_chars(blk)}} {}

    /// @brief Conversion to glsl_source_ref
    operator glsl_source_ref() const noexcept {
        return {1, &_src_str, &_length};
    }

private:
    mutable const char_type* _src_str{nullptr};
    int_type _length{0};
};
//------------------------------------------------------------------------------
/// @brief Wrapper class for a GLSL string literal, convertible to glsl_source_ref.
/// @ingroup glsl_utils
/// @see glsl_source_ref
export class glsl_literal : public glsl_string_ref {
public:
    /// @brief Construction from a zero-terminated string literal.
    template <span_size_t N>
    glsl_literal(const char (&src_str)[N]) noexcept
      : glsl_string_ref(static_cast<const char*>(src_str), N) {}
};
//------------------------------------------------------------------------------
/// @brief User defined literal for GLSL source code strings.
/// @ingroup glsl_utils
export constexpr auto operator"" _glsl(
  const char* src_str,
  const std::size_t n) noexcept -> glsl_string_ref {
    return {src_str, span_size(n)};
}
//------------------------------------------------------------------------------
/// @brief Base class typically storing GLSL source code strings.
/// @ingroup glsl_utils
export template <typename Container>
class glsl_container {
public:
    /// @brief Default constructor.
    glsl_container() = default;

    /// @brief Construction from the storage container.
    glsl_container(Container storage) noexcept
      : _storage{std::move(storage)}
      , _str_ref{_storage.data(), _storage.size()} {}

    /// @brief Returns a reference to the storage container.
    auto storage() noexcept -> Container& {
        return _storage;
    }

    /// @brief Conversion to glsl_string_ref.
    operator glsl_source_ref() const noexcept {
        return _str_ref;
    }

private:
    Container _storage;
    glsl_string_ref _str_ref;
};

using glsl_string = glsl_container<std::string>;
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

namespace eagine::c_api {

template <std::size_t I, typename... CT, typename... CppT>
struct make_args_map<
  I,
  I,
  mp_list<
    oglplus::gl_types::sizei_type,
    const oglplus::gl_types::char_type* const*,
    CT...>,
  mp_list<const oglplus::glsl_source_ref&, CppT...>>
  : make_args_map<I + 2, I + 1, mp_list<CT...>, mp_list<CppT...>> {
    using make_args_map<I + 2, I + 1, mp_list<CT...>, mp_list<CppT...>>::
    operator();

    template <typename... P>
    constexpr auto operator()(size_constant<I> i, P&&... p) const noexcept {
        return reorder_arg_map<I, I>{}(i, std::forward<P>(p)...).count();
    }

    template <typename... P>
    constexpr auto operator()(size_constant<I + 1> i, P&&... p) const noexcept {
        return reorder_arg_map<I + 1, I>{}(i, std::forward<P>(p)...).parts();
    }
};

template <std::size_t I, typename... CT, typename... CppT>
struct make_args_map<
  I,
  I,
  mp_list<
    oglplus::gl_types::sizei_type,
    const oglplus::gl_types::char_type* const*,
    const oglplus::gl_types::int_type*,
    CT...>,
  mp_list<const oglplus::glsl_source_ref&, CppT...>>
  : make_args_map<I + 3, I + 1, mp_list<CT...>, mp_list<CppT...>> {
    using make_args_map<I + 3, I + 1, mp_list<CT...>, mp_list<CppT...>>::
    operator();

    template <typename... P>
    constexpr auto operator()(size_constant<I> i, P&&... p) const noexcept {
        return reorder_arg_map<I, I>{}(i, std::forward<P>(p)...).count();
    }

    template <typename... P>
    constexpr auto operator()(size_constant<I + 1> i, P&&... p) const noexcept {
        return reorder_arg_map<I + 1, I>{}(i, std::forward<P>(p)...).parts();
    }

    template <typename... P>
    constexpr auto operator()(size_constant<I + 2> i, P&&... p) const noexcept {
        return reorder_arg_map<I + 2, I>{}(i, std::forward<P>(p)...).lengths();
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::c_api
