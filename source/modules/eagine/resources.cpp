/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:resources;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.value_tree;
import :objects;
import :enum_types;
import <memory>;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
export auto make_gl_texture_builder(
  memory::buffer_pool&,
  texture_name tex,
  texture_target target) noexcept -> std::unique_ptr<valtree::object_builder>;
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

