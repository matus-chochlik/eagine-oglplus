/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

module eagine.oglplus;
import eagine.core.types;
import eagine.core.memory;
import <iostream>;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
void write_and_pad_texture_image_data_header(
  std::ostream& output,
  image_data_header& header,
  const span_size_t pixel_data_size) {
    span_size_t spos = 0;

    if(output.tellp() >= 0) {
        spos = span_size_t(output.tellp());
    }

    write_and_pad_texture_image_data_header(
      output, header, pixel_data_size, spos);
}
//------------------------------------------------------------------------------
void write_and_pad_texture_image_data_header(
  std::ostream& output,
  image_data_header& header,
  const span_size_t pixel_data_size,
  span_size_t& spos) {
    using eagine::memory::is_aligned_as;
    while(!is_aligned_as<image_data_header>(spos)) {
        output.put('\0');
        ++spos;
    }

    const span_size_t size = 64;
    span_size_t done = 0;
    static_assert(size >= span_size(sizeof(image_data_header)));

    eagine::memory::const_address hdraddr(&header);

    header.pixels.reset(hdraddr + size, pixel_data_size);

    output.write(static_cast<const char*>(hdraddr), sizeof(header));
    spos += sizeof(header);
    done += sizeof(header);

    while(done < size) {
        output.put('\0');
        ++spos;
        ++done;
    }
}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
