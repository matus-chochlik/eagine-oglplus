/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include <cassert>

export module eagine.oglplus:program_source;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.valid_if;
import eagine.core.utility;
import eagine.core.runtime;
import :config;
import :enum_types;
import :glsl_source;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
export struct shader_source_header {
    file_magic_number<'o', 'g', 'l', '+', 's', 'h', 'd', 'r'> magic;
    memory::offset_span<const char> source_text = {};
    gl_types::enum_type shader_type{0};

    constexpr shader_source_header() noexcept = default;
};
//------------------------------------------------------------------------------
export struct program_source_header {
    file_magic_number<'o', 'g', 'l', '+', 'p', 'r', 'o', 'g'> magic;
    memory::offset_span<const memory::offset_ptr<const shader_source_header>>
      shader_sources = {};

    constexpr program_source_header() noexcept = default;
};
//------------------------------------------------------------------------------
export class shader_source_block {
public:
    shader_source_block(const memory::const_block blk)
      : _header{blk} {}

    shader_source_block(const shader_source_header* ptr)
      : _header{as_bytes(view_one(ptr))} {}

    auto is_valid() const noexcept -> bool {
        return _header->magic.is_valid();
    }

    auto type() const noexcept {
        assert(is_valid());
        return shader_type{_header->shader_type};
    }

    auto source_text() const noexcept -> string_view {
        assert(is_valid());
        return {
          _header->source_text.data(), span_size(_header->source_text.size())};
    }

    operator glsl_source_ref() const noexcept {
        assert(is_valid());
        return {_header->source_text};
    }

private:
    memory::structured_block<const shader_source_header> _header;
};
//------------------------------------------------------------------------------
export class shader_source_file
  : protected_member<file_contents>
  , public shader_source_block {
public:
    shader_source_file(file_contents&& fc)
      : protected_member<file_contents>{std::move(fc)}
      , shader_source_block{get_the_member()} {}

    shader_source_file(const string_view path)
      : shader_source_file{file_contents(path)} {}

    shader_source_file(const std::string& path)
      : shader_source_file{string_view(path)} {}
};
//------------------------------------------------------------------------------
export class program_source_block {
public:
    program_source_block(const memory::const_block blk)
      : _header(blk) {}

    auto is_valid() const noexcept -> bool {
        return _header->magic.is_valid();
    }

    auto shader_source_count() const noexcept -> span_size_t {
        assert(is_valid());
        return _header->shader_sources.size();
    }

    auto shader_source(const span_size_t index) const noexcept
      -> shader_source_block {
        assert(is_valid());
        assert(index < _header->shader_sources.size());
        return {_header->shader_sources[index]};
    }

private:
    memory::structured_block<const program_source_header> _header;
};
//------------------------------------------------------------------------------
export class program_source_file
  : protected_member<file_contents>
  , public program_source_block {
public:
    program_source_file(file_contents&& fc)
      : protected_member<file_contents>(std::move(fc))
      , program_source_block{get_the_member()} {}

    program_source_file(const string_view path)
      : program_source_file{file_contents(path)} {}

    program_source_file(const std::string& path)
      : program_source_file{string_view(path)} {}
};
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

