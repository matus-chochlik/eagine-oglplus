/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oglplus:objects;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Alias for template wrapping GL object handles.
/// @ingroup gl_api_wrap
/// @see gl_owned_object_name
/// @see gl_object_name_view
/// @see gl_object_name_span
/// @see gl_object_name_array
export template <typename Tag>
using gl_object_name = c_api::basic_handle<Tag, gl_types::name_type>;

/// @brief Alias for template wrapping owned GL object handles.
/// @ingroup gl_api_wrap
/// @see gl_object_name
export template <typename Tag>
using gl_owned_object_name =
  c_api::basic_owned_handle<Tag, gl_types::name_type>;

/// @brief Alias for GL object template.
/// @ingroup gl_api_wrap
/// @see gl_object_name
/// @see gl_owned_object_name
export template <typename Api, typename Tag, typename... P>
struct basic_gl_object
  : c_api::basic_object_from_handle_t<Api, gl_object_name<Tag>, P...> {
    using base =
      c_api::basic_object_from_handle_t<Api, gl_object_name<Tag>, P...>;
    using base::base;
};

/// @brief Alias for template wrapping a mutable span of GL object handles.
/// @ingroup gl_api_wrap
/// @see gl_object_name_view
/// @see gl_object_name_array
export template <typename Tag>
using gl_object_name_span = c_api::basic_handle_span<gl_object_name<Tag>>;

/// @brief Alias for template wrapping a const span of GL object handles.
/// @ingroup gl_api_wrap
/// @see gl_object_name_span
/// @see gl_object_name_array
export template <typename Tag>
using gl_object_name_view = c_api::basic_handle_view<gl_object_name<Tag>>;

/// @brief Alias for template wrapping an array of GL object handles.
/// @ingroup gl_api_wrap
/// @see gl_object_name_vector
/// @see gl_object_name_span
/// @see gl_object_name_view
export template <typename Tag, std::size_t N>
using gl_object_name_array = c_api::basic_handle_array<gl_object_name<Tag>, N>;

/// @brief Alias for template wrapping a vector of GL object handles.
/// @ingroup gl_api_wrap
/// @see gl_object_name_array
/// @see gl_object_name_span
/// @see gl_object_name_view
export template <typename Tag>
using gl_object_name_vector = c_api::basic_handle_vector<gl_object_name<Tag>>;
//------------------------------------------------------------------------------
export template <identifier_value Id>
using gl_lib_tag = static_message_id<"gl", Id>;

/// @brief Tag type denoting GL buffer objects.
/// @ingroup gl_api_wrap
export using buffer_tag = gl_lib_tag<"Buffer">;

/// @brief Tag type denoting GL framebuffer objects.
/// @ingroup gl_api_wrap
export using framebuffer_tag = gl_lib_tag<"Frmebuffer">;

/// @brief Tag type denoting GL program pipeline objects.
/// @ingroup gl_api_wrap
export using program_pipeline_tag = gl_lib_tag<"PrgPpline">;

/// @brief Tag type denoting GL program objects.
/// @ingroup gl_api_wrap
export using program_tag = gl_lib_tag<"Program">;

/// @brief Tag type denoting GL query objects.
/// @ingroup gl_api_wrap
export using query_tag = gl_lib_tag<"Query">;

/// @brief Tag type denoting GL renderbuffer objects.
/// @ingroup gl_api_wrap
export using renderbuffer_tag = gl_lib_tag<"Rndrbuffer">;

/// @brief Tag type denoting GL sampler objects.
/// @ingroup gl_api_wrap
export using sampler_tag = gl_lib_tag<"Sampler">;

/// @brief Tag type denoting GL shader objects.
/// @ingroup gl_api_wrap
export using shader_tag = gl_lib_tag<"Shader">;

/// @brief Tag type denoting GL texture objects.
/// @ingroup gl_api_wrap
export using texture_tag = gl_lib_tag<"Texture">;

/// @brief Tag type denoting GL transform feedback objects.
/// @ingroup gl_api_wrap
export using transform_feedback_tag = gl_lib_tag<"TransfFdbk">;

/// @brief Tag type denoting GL vertex array objects.
/// @ingroup gl_api_wrap
export using vertex_array_tag = gl_lib_tag<"VertexArry">;

/// @brief Tag type denoting GL path objects.
/// @ingroup gl_api_wrap
export using path_nv_tag = gl_lib_tag<"PathNV">;
//------------------------------------------------------------------------------
/// @brief Alias for GL buffer object handle.
/// @ingroup gl_api_wrap
/// @see owned_buffer_name
/// @see no_buffer
export using buffer_name = gl_object_name<buffer_tag>;

/// @brief Constant used to break existing buffer object binding.
/// @ingroup gl_api_wrap
export constexpr const buffer_name no_buffer{0};

/// @brief Alias for GL framebuffer object handle.
/// @ingroup gl_api_wrap
/// @see owned_framebuffer_name
/// @see default_framebuffer
export using framebuffer_name = gl_object_name<framebuffer_tag>;

/// @brief Constant representing the default framebuffer object.
/// @ingroup gl_api_wrap
export constexpr const framebuffer_name default_framebuffer{0};

/// @brief Alias for GL program pipeline object handle.
/// @ingroup gl_api_wrap
/// @see owned_program_pipeline_name
/// @see no_program_pipeline
export using program_pipeline_name = gl_object_name<program_pipeline_tag>;

/// @brief Constant used to break existing program pipeline object binding.
/// @ingroup gl_api_wrap
export constexpr const program_pipeline_name no_program_pipeline{0};

/// @brief Alias for GL program object handle.
/// @ingroup gl_api_wrap
/// @see owned_program_name
/// @see no_program
export using program_name = gl_object_name<program_tag>;

/// @brief Constant used to break existing program object binding.
/// @ingroup gl_api_wrap
export constexpr const program_name no_program{0};

/// @brief Alias for GL query object handle.
/// @ingroup gl_api_wrap
/// @see owned_query_name
export using query_name = gl_object_name<query_tag>;

/// @brief Alias for GL renderbuffer object handle.
/// @ingroup gl_api_wrap
/// @see owned_renderbuffer_name
/// @see no_renderbuffer
export using renderbuffer_name = gl_object_name<renderbuffer_tag>;

/// @brief Constant used to break existing renderbuffer object binding.
/// @ingroup gl_api_wrap
export constexpr const renderbuffer_name no_renderbuffer{0};

/// @brief Alias for GL sampler object handle.
/// @ingroup gl_api_wrap
/// @see owned_sampler_name
/// @see no_sampler
export using sampler_name = gl_object_name<sampler_tag>;

/// @brief Constant used to break existing sampler object binding.
/// @ingroup gl_api_wrap
export constexpr const sampler_name no_sampler{0};

/// @brief Alias for GL shader object handle.
/// @ingroup gl_api_wrap
/// @see owned_shader_name
export using shader_name = gl_object_name<shader_tag>;

/// @brief Alias for GL texture object handle.
/// @ingroup gl_api_wrap
/// @see owned_texture_name
/// @see default_texture
export using texture_name = gl_object_name<texture_tag>;

/// @brief Constant representing the default texture object.
/// @ingroup gl_api_wrap
export constexpr const texture_name default_texture{0};

/// @brief Alias for GL transform feedback object handle.
/// @ingroup gl_api_wrap
/// @see owned_transform_feedback_name
/// @see default_transform_feedback
export using transform_feedback_name = gl_object_name<transform_feedback_tag>;

/// @brief Constant representing the default transform feedback object.
/// @ingroup gl_api_wrap
export constexpr const transform_feedback_name default_transform_feedback{0};

/// @brief Alias for GL vertex array object handle.
/// @ingroup gl_api_wrap
/// @see owned_vertex_array_name
/// @see no_vertex_array
export using vertex_array_name = gl_object_name<vertex_array_tag>;

/// @brief Constant used to break existing vertex array object binding.
/// @ingroup gl_api_wrap
export constexpr const vertex_array_name no_vertex_array{0};

/// @brief Alias for GL path object handle.
/// @ingroup gl_api_wrap
/// @see owned_path_nv_name
export using path_nv_name = gl_object_name<path_nv_tag>;
//------------------------------------------------------------------------------
/// @brief Alias for owned GL buffer object handle.
/// @ingroup gl_api_wrap
/// @see buffer_name
export using owned_buffer_name = gl_owned_object_name<buffer_tag>;

/// @brief Alias for owned GL framebuffer object handle.
/// @ingroup gl_api_wrap
/// @see framebuffer_name
export using owned_framebuffer_name = gl_owned_object_name<framebuffer_tag>;

/// @brief Alias for owned GL program_pipeline object handle.
/// @ingroup gl_api_wrap
/// @see program_pipeline_name
export using owned_program_pipeline_name =
  gl_owned_object_name<program_pipeline_tag>;

/// @brief Alias for owned GL program object handle.
/// @ingroup gl_api_wrap
/// @see program_name
export using owned_program_name = gl_owned_object_name<program_tag>;

/// @brief Alias for owned GL query object handle.
/// @ingroup gl_api_wrap
/// @see query_name
export using owned_query_name = gl_owned_object_name<query_tag>;

/// @brief Alias for owned GL renderbuffer object handle.
/// @ingroup gl_api_wrap
/// @see renderbuffer_name
export using owned_renderbuffer_name = gl_owned_object_name<renderbuffer_tag>;

/// @brief Alias for owned GL sampler object handle.
/// @ingroup gl_api_wrap
/// @see sampler_name
export using owned_sampler_name = gl_owned_object_name<sampler_tag>;

/// @brief Alias for owned GL shader object handle.
/// @ingroup gl_api_wrap
/// @see shader_name
export using owned_shader_name = gl_owned_object_name<shader_tag>;

/// @brief Alias for owned GL texture object handle.
/// @ingroup gl_api_wrap
/// @see texture_name
export using owned_texture_name = gl_owned_object_name<texture_tag>;

/// @brief Alias for owned GL transform feedback  object handle.
/// @ingroup gl_api_wrap
/// @see transform_feedback_name
export using owned_transform_feedback_name =
  gl_owned_object_name<transform_feedback_tag>;

/// @brief Alias for owned GL vertex array object handle.
/// @ingroup gl_api_wrap
/// @see vertex_array_name
export using owned_vertex_array_name = gl_owned_object_name<vertex_array_tag>;

/// @brief Alias for owned GL path object handle.
/// @ingroup gl_api_wrap
/// @see path_nv_name
export using owned_path_nv_name = gl_owned_object_name<path_nv_tag>;
//------------------------------------------------------------------------------
/// Alias for owned GL sync object handle.
/// @ingroup gl_api_wrap
export using owned_sync = optionally_valid<gl_types::sync_type>;
//------------------------------------------------------------------------------
/// @brief Alias for array of N GL buffer object handles.
/// @ingroup gl_api_wrap
/// @see buffer_name
export template <std::size_t N>
using buffer_name_array = gl_object_name_array<buffer_tag, N>;

/// @brief Alias for array of N GL framebuffer object handles.
/// @ingroup gl_api_wrap
/// @see framebuffer_name
export template <std::size_t N>
using framebuffer_name_array = gl_object_name_array<framebuffer_tag, N>;

/// @brief Alias for array of N GL program pipeline  object handles.
/// @ingroup gl_api_wrap
/// @see program_pipeline_name
export template <std::size_t N>
using program_pipeline_name_array =
  gl_object_name_array<program_pipeline_tag, N>;

/// @brief Alias for array of N GL program object handles.
/// @ingroup gl_api_wrap
/// @see program_name
export template <std::size_t N>
using program_name_array = gl_object_name_array<program_tag, N>;

/// @brief Alias for array of N GL query object handles.
/// @ingroup gl_api_wrap
/// @see query_name
export template <std::size_t N>
using query_name_array = gl_object_name_array<query_tag, N>;

/// @brief Alias for array of N GL renderbuffer object handles.
/// @ingroup gl_api_wrap
/// @see renderbuffer_name
export template <std::size_t N>
using renderbuffer_name_array = gl_object_name_array<renderbuffer_tag, N>;

/// @brief Alias for array of N GL sampler object handles.
/// @ingroup gl_api_wrap
/// @see sampler_name
export template <std::size_t N>
using sampler_name_array = gl_object_name_array<sampler_tag, N>;

/// @brief Alias for array of N GL shader object handles.
/// @ingroup gl_api_wrap
/// @see shader_name
export template <std::size_t N>
using shader_name_array = gl_object_name_array<shader_tag, N>;

/// @brief Alias for array of N GL texture object handles.
/// @ingroup gl_api_wrap
/// @see texture_name
export template <std::size_t N>
using texture_name_array = gl_object_name_array<texture_tag, N>;

/// @brief Alias for array of N GL transform feedback object handles.
/// @ingroup gl_api_wrap
/// @see transform_feedback_name
export template <std::size_t N>
using transform_feedback_name_array =
  gl_object_name_array<transform_feedback_tag, N>;

/// @brief Alias for array of N GL vertex array object handles.
/// @ingroup gl_api_wrap
/// @see vertex_array_name
export template <std::size_t N>
using vertex_array_name_array = gl_object_name_array<vertex_array_tag, N>;
//------------------------------------------------------------------------------
/// @brief Alias for bind-less texture handle.
/// @ingroup gl_api_wrap
export using texture_handle =
  c_api::basic_handle<gl_lib_tag<"TexHandle">, gl_types::uint64_type>;

/// @brief Alias for bind-less texture sampler handle.
/// @ingroup gl_api_wrap
export using texture_sampler_handle =
  c_api::basic_handle<gl_lib_tag<"SamHandle">, gl_types::uint64_type>;

/// @brief Alias for bind-less texture image handle.
/// @ingroup gl_api_wrap
export using image_handle =
  c_api::basic_handle<gl_lib_tag<"ImgHandle">, gl_types::uint64_type>;
//------------------------------------------------------------------------------
///@brief Class representing a shader include named string.
/// @ingroup gl_api_wrap
export class shader_include {
public:
    /// @brief Construction from a path string.
    shader_include(std::string path) noexcept
      : _path{std::move(path)} {}

    /// @brief Default constructor
    /// @post not has_value()
    shader_include() noexcept = default;

    shader_include(shader_include&&) noexcept = default;
    shader_include(const shader_include&) = delete;
    auto operator=(shader_include&&) noexcept -> shader_include& = default;
    auto operator=(const shader_include&) = delete;
    ~shader_include() noexcept = default;

    /// @brief Indicates it this object represents a valid shader include path.
    auto has_value() const noexcept -> bool {
        return not _path.empty() and (_path.front() == '/');
    }

    /// @brief Indicates it this object represents a valid shader include path.
    explicit operator bool() const noexcept {
        return has_value();
    }

    /// @brief Returns the path of this include.
    auto path() const noexcept -> string_view {
        return has_value() ? string_view{_path} : string_view{};
    }

private:
    std::string _path;
};
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

