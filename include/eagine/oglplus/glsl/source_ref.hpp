/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_GLSL_SOURCE_REF_HPP
#define EAGINE_OGLPLUS_GLSL_SOURCE_REF_HPP

#include "../gl_api/config.hpp"
#include <eagine/assert.hpp>
#include <eagine/c_api/parameter_map.hpp>
#include <eagine/string_span.hpp>
#include <cstddef>

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Class referencing a set of GLSL source code strings.
/// @ingroup glsl_utils
class glsl_source_ref {
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
        EAGINE_ASSERT(_count >= 0);
        EAGINE_ASSERT(_parts != nullptr);
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

} // namespace eagine::c_api

#endif // EAGINE_OGLPLUS_GLSL_SOURCE_REF_HPP
