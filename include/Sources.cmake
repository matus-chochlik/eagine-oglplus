# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
set(HEADERS
    eagine/oglplus/basic_gl_api.hpp
    eagine/oglplus/camera.hpp
    eagine/oglplus/config/basic.hpp
    eagine/oglplus/gl_api/api.hpp
    eagine/oglplus/gl_api/api_traits.hpp
    eagine/oglplus/gl_api/c_api.hpp
    eagine/oglplus/gl_api/config.hpp
    eagine/oglplus/gl_api/constants.hpp
    eagine/oglplus/gl_api/enum_class.hpp
    eagine/oglplus/gl_api/enum_types.hpp
    eagine/oglplus/gl_api/extensions.hpp
    eagine/oglplus/gl_api_fwd.hpp
    eagine/oglplus/gl_api.hpp
    eagine/oglplus/gl_api/object_name.hpp
    eagine/oglplus/gl_api/prog_var_loc.hpp
    eagine/oglplus/gl_api/result.hpp
    eagine/oglplus/gl_api/type_utils.hpp
    eagine/oglplus/gl_debug_logger.hpp
    eagine/oglplus/gl_def.hpp
    eagine/oglplus/gl_fallback.hpp
    eagine/oglplus/gl.hpp
    eagine/oglplus/glsl/container.hpp
    eagine/oglplus/glsl_program.hpp
    eagine/oglplus/glsl/source_ref.hpp
    eagine/oglplus/glsl/string_ref.hpp
    eagine/oglplus/math/config.hpp
    eagine/oglplus/math/coordinates.hpp
    eagine/oglplus/math/interpolate.hpp
    eagine/oglplus/math/matrix_ctrs.hpp
    eagine/oglplus/math/matrix.hpp
    eagine/oglplus/math/primitives.hpp
    eagine/oglplus/math/sign.hpp
    eagine/oglplus/math/vector.hpp
    eagine/oglplus/shapes/bindings.hpp
    eagine/oglplus/shapes/drawing.hpp
    eagine/oglplus/shapes/generator.hpp
    eagine/oglplus/shapes/geometry.hpp
    eagine/oglplus/utils/image_file_hdr.hpp
    eagine/oglplus/utils/image_file.hpp
    eagine/oglplus/utils/image_file_io.hpp
    eagine/oglplus/utils/image_spec.hpp
    eagine/oglplus/utils/program_file_hdr.hpp
    eagine/oglplus/utils/program_file.hpp
)

set(PUB_INLS
    eagine/oglplus/gl_api/api.inl
    eagine/oglplus/gl_api/api_traits.inl
    eagine/oglplus/gl_api/c_api.inl
    eagine/oglplus/gl_api/constants.inl
    eagine/oglplus/gl_api.inl
    eagine/oglplus/shapes/drawing.inl
    eagine/oglplus/shapes/generator.inl
)

set(LIB_INLS
    eagine/oglplus/camera.inl
    eagine/oglplus/gl_def.inl
)

