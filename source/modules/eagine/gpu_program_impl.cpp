/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///

module eagine.oglplus;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.valid_if;
import eagine.shapes;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
auto program_input_bindings::count() const noexcept -> span_size_t {
    return _mapping.size();
}
//------------------------------------------------------------------------------
auto program_input_bindings::add(
  std::string name,
  shapes::vertex_attrib_variant vav) -> program_input_bindings& {
    _mapping.set(vav, std::move(name));
    return *this;
}
//------------------------------------------------------------------------------
auto program_input_bindings::apply(
  const gl_api& glapi,
  program_name prog,
  const vertex_attrib_bindings& bindings) const noexcept -> bool {
    span_size_t done{0};
    glapi.use_program(prog);
    for(auto& [vav, name] : _mapping) {
        if(const auto bloc{bindings.location(vav)}) {
            glapi.bind_attrib_location(prog, bloc, name);
            ++done;
        } else {
            const auto [vloc, val] = bindings.location_and_value(vav);
            if(vloc and val) {
                glapi.bind_attrib_location(prog, vloc, name);
                if(set_vertex_attrib_value(glapi, vloc, val)) {
                    ++done;
                }
            } else {
                ++done;
            }
        }
    }
    if(_mapping.size() == done) {
        glapi.link_program(prog);
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------
auto program_input_bindings::clear() noexcept -> program_input_bindings& {
    _mapping.clear();
    return *this;
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
