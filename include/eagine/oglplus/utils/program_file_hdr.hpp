/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef EAGINE_OGLPLUS_UTILS_PROGRAM_FILE_HDR_HPP
#define EAGINE_OGLPLUS_UTILS_PROGRAM_FILE_HDR_HPP

#include <eagine/file_magic_number.hpp>
#include <eagine/memory/offset_span.hpp>
#include <array>

namespace eagine::oglplus {
//------------------------------------------------------------------------------
struct shader_source_header {
    file_magic_number<'o', 'g', 'l', '+', 's', 'h', 'd', 'r'> magic;
    memory::offset_span<const char> source_text = {};
    GLenum shader_type = GL_NONE;

    constexpr shader_source_header() noexcept = default;
};
//------------------------------------------------------------------------------
struct program_source_header {
    file_magic_number<'o', 'g', 'l', '+', 'p', 'r', 'o', 'g'> magic;
    memory::offset_span<const memory::offset_ptr<const shader_source_header>>
      shader_sources = {};

    constexpr program_source_header() noexcept = default;
};
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

#endif // EAGINE_OGLPLUS_UTILS_PROGRAM_FILE_HDR_HPP
