/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include "gl_def.hpp"
#include <cassert>

export module eagine.oglplus:api;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.string;
import eagine.core.math;
import eagine.core.units;
import eagine.core.utility;
import eagine.core.c_api;
import :config;
import :enum_types;
import :extensions;
import :objects;
import :constants;
import :prog_var_loc;
import :type_utils;
import :glsl_source;
import :math;
import :c_api;
import :api_traits;

namespace eagine::c_api {

template <>
struct cast_to_map<const oglplus::gl_types::ubyte_type*, string_view> {
    template <typename... P>
    constexpr auto operator()(size_constant<0> i, P&&... p) const noexcept {
        return trivial_map{}(i, std::forward<P>(p)...).transform([](auto src) {
            return src ? string_view{reinterpret_cast<const char*>(src)}
                       : string_view{};
        });
    }
};

template <
  std::size_t CI,
  std::size_t CppI,
  typename CS,
  typename CppV,
  typename CppP,
  typename CppS,
  CppS chunkSize>
struct make_args_map<
  CI,
  CppI,
  mp_list<CS, oglplus::gl_types::bool_type, CppV*>,
  mp_list<
    oglplus::true_false,
    memory::basic_chunk_span<CppV, CppP, CppS, chunkSize>>>
  : convert<CS, get_chunk_size_map<CI, CppI + 1, chunkSize>>
  , convert<oglplus::gl_types::bool_type, reorder_arg_map<CI + 1, CppI>>
  , get_data_map<CI + 2, CppI + 1> {
    using convert<CS, get_chunk_size_map<CI, CppI + 1, chunkSize>>::operator();
    using convert<oglplus::gl_types::bool_type, reorder_arg_map<CI + 1, CppI>>::
    operator();
    using get_data_map<CI + 2, CppI + 1>::operator();
};

template <std::size_t CI, std::size_t CppI, typename... CT, typename... CppT>
struct make_args_map<
  CI,
  CppI,
  mp_list<
    oglplus::gl_types::sizei_type,
    oglplus::gl_types::enum_type,
    const void*,
    CT...>,
  mp_list<string_view, substituted<GL_UTF8_NV>, CppT...>>
  : convert<oglplus::gl_types::sizei_type, get_size_map<CI, CppI>>
  , make_arg_map<CI + 2, CppI, const char*, string_view>
  , make_args_map<CI + 3, CppI + 1, mp_list<CT...>, mp_list<CppT...>> {

    using convert<oglplus::gl_types::sizei_type, get_size_map<CI, CppI>>::
    operator();
    using make_arg_map<CI + 2, CppI, const char*, string_view>::operator();
    using make_args_map<CI + 3, CppI + 1, mp_list<CT...>, mp_list<CppT...>>::
    operator();

    template <typename... P>
    constexpr auto operator()(size_constant<CI + 1>, P&&...) const noexcept
      -> oglplus::gl_types::enum_type {
        return GL_UTF8_NV;
    }
};

} // namespace eagine::c_api

namespace eagine::oglplus {
//------------------------------------------------------------------------------
export struct api_initializer {
    ~api_initializer() noexcept = default;
    api_initializer(const api_initializer&) = delete;
    api_initializer(api_initializer&&) = delete;
    auto operator=(const api_initializer&) = delete;
    auto operator=(api_initializer&&) = delete;

    explicit api_initializer(
      const int /*gl_ver_major*/ = 3,
      const int /*gl_ver_minor*/ = 3);
};
//------------------------------------------------------------------------------
class gl_debug_logger;
using c_api::adapted_function;
using c_api::enum_parameter_value;
using c_api::plain_adapted_function;
using c_api::simple_adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the GL API.
/// @ingroup gl_api_wrap
/// @see basic_gl_constants
/// @see basic_gl_c_api
export template <typename ApiTraits>
class basic_gl_operations : public basic_gl_c_api<ApiTraits> {

public:
    /// @brief Alias for the traits policy class.
    using api_traits = ApiTraits;

    /// @brief Alias for the basic GL API wrapper.
    using gl_api = basic_gl_c_api<ApiTraits>;

    using sizei_type = typename gl_types::sizei_type;
    using sizeiptr_type = typename gl_types::sizeiptr_type;
    using short_type = typename gl_types::short_type;
    using int_type = typename gl_types::int_type;
    using uint_type = typename gl_types::uint_type;
    using int64_type = typename gl_types::int64_type;
    using uint64_type = typename gl_types::uint64_type;
    using intptr_type = typename gl_types::intptr_type;
    using bool_type = typename gl_types::bool_type;
    using char_type = typename gl_types::char_type;
    using enum_type = typename gl_types::enum_type;
    using float_type = typename gl_types::float_type;
    using double_type = typename gl_types::double_type;
    using bitfield_type = typename gl_types::bitfield_type;

    using sync_type = typename gl_types::sync_type;
    using name_type = typename gl_types::name_type;

    using void_ptr_type = typename gl_types::void_ptr_type;
    using const_void_ptr_type = typename gl_types::const_void_ptr_type;

    using vertex_buffer_binding = uint_type;

    using debug_callback_type = typename gl_api::debug_callback_type;

    /// @brief Alias for GL extension info getter.
    using extension = basic_gl_extension<ApiTraits>;

    /// @var ARB_debug_output
    /// @glextwrap{ARB_debug_output}
    extension ARB_debug_output;

    /// @var ARB_compatibility
    /// @glextwrap{ARB_compatibility}
    extension ARB_compatibility;

    /// @var ARB_robustness
    /// @glextwrap{ARB_robustness}
    extension ARB_robustness;

    /// @var ARB_shading_language_include
    /// @glextwrap{ARB_shading_language_include}
    extension ARB_shading_language_include;

    // utilities
    static constexpr auto type_of(buffer_name) noexcept {
        return object_type(GL_BUFFER);
    }

    static constexpr auto type_of(framebuffer_name) noexcept {
        return object_type(GL_FRAMEBUFFER);
    }

    static constexpr auto type_of(program_pipeline_name) noexcept {
        return object_type(GL_PROGRAM_PIPELINE);
    }

    static constexpr auto type_of(program_name) noexcept {
        return object_type(GL_PROGRAM);
    }

    static constexpr auto type_of(query_name) noexcept {
        return object_type(GL_QUERY);
    }

    static constexpr auto type_of(renderbuffer_name) noexcept {
        return object_type(GL_RENDERBUFFER);
    }

    static constexpr auto type_of(sampler_name) noexcept {
        return object_type(GL_SAMPLER);
    }

    static constexpr auto type_of(shader_name) noexcept {
        return object_type(GL_SHADER);
    }

    static constexpr auto type_of(texture_name) noexcept {
        return object_type(GL_TEXTURE);
    }

    static constexpr auto type_of(transform_feedback_name) noexcept {
        return object_type(GL_TRANSFORM_FEEDBACK);
    }

    static constexpr auto type_of(vertex_array_name) noexcept {
        return object_type(GL_VERTEX_ARRAY);
    }

    // numeric query function
    template <
      auto wrapper,
      typename QueryResult,
      typename PreTypeList,
      typename QueryClassList,
      typename PostTypeList = mp_list<>>
    struct query_function;

    template <
      auto wrapper,
      typename QueryResult,
      typename... PreParams,
      typename... QueryClasses,
      typename... PostParams>
    struct query_function<
      wrapper,
      QueryResult,
      mp_list<PreParams...>,
      mp_list<QueryClasses...>,
      mp_list<PostParams...>>
      : simple_adapted_function<
          wrapper,
          void(PreParams..., enum_type, PostParams..., QueryResult*)> {
        using base = simple_adapted_function<
          wrapper,
          void(PreParams..., enum_type, PostParams..., QueryResult*)>;
        using base::base;

        template <typename Query>
        constexpr auto operator()(
          PreParams... pre_params,
          Query query,
          PostParams... post_params) const noexcept
            requires(
              (true or ... or
               c_api::is_enum_class_value_v<QueryClasses, Query>) and
              (not std::is_array_v<typename Query::tag_type>))
        {
            using RV = typename Query::tag_type;
            QueryResult result{};
            return base::operator()(
                     pre_params..., enum_type(query), post_params..., &result)
              .replaced_with(result)
              .cast_to(std::type_identity<RV>{});
        }

        template <typename Query>
        auto operator()(
          PreParams... pre_params,
          Query query,
          PostParams... post_params,
          span<QueryResult> dest) const noexcept
            requires(
              true or ... or c_api::is_enum_class_value_v<QueryClasses, Query>)
        {
            if constexpr(std::is_array_v<typename Query::tag_type>) {
                assert(dest.size() >= std::extent_v<typename Query::tag_type>);
            } else {
                assert(dest.size() > 0);
            }
            return base::operator()(
              pre_params..., enum_type(query), post_params..., dest.data());
        }
    };

    simple_adapted_function<
      &gl_api::FenceSync,
      void(sync_condition, c_api::enum_bitfield<sync_flag_bit>)>
      fence_sync{*this};

    template <auto Wrapper, typename ObjTag>
    struct make_object_func
      : simple_adapted_function<Wrapper, void(span<name_type>)> {
        using base = simple_adapted_function<Wrapper, void(span<name_type>)>;
        using base::base;
        using base::operator();

        constexpr auto operator()(
          gl_object_name_span<ObjTag> names) const noexcept {
            return (*this)(names.raw_handles());
        }

        constexpr auto operator()() const noexcept {
            name_type n{};
            return base::operator()(cover_one(n))
              .transform_if([&n](auto, bool valid) {
                  return gl_owned_object_name<ObjTag>(valid ? n : 0);
              });
        }

        constexpr auto object() const noexcept
          -> gl_object<basic_gl_operations, ObjTag> {
            gl_owned_object_name<ObjTag> name;
            (*this)() >> name;
            return {
              static_cast<const basic_gl_operations&>(base::api()),
              std::move(name)};
        }
    };

    using _create_shader_t = simple_adapted_function<
      &gl_api::CreateShader,
      owned_shader_name(shader_type)>;
    struct : _create_shader_t {
        using base = _create_shader_t;
        using base::base;

        constexpr auto object(shader_type shdr_type) const noexcept
          -> gl_object<basic_gl_operations, shader_tag> {
            owned_shader_name shdr;
            (*this)(shdr_type) >> shdr;
            return {
              static_cast<const basic_gl_operations&>(base::api()),
              std::move(shdr)};
        }
    } create_shader{*this};

    using _create_program_t =
      simple_adapted_function<&gl_api::CreateProgram, owned_program_name()>;
    struct : _create_program_t {
        using base = _create_program_t;
        using base::base;

        constexpr auto object() const noexcept
          -> gl_object<basic_gl_operations, program_tag> {
            owned_program_name prog;
            (*this)() >> prog;
            return {
              static_cast<const basic_gl_operations&>(base::api()),
              std::move(prog)};
        }
    } create_program{*this};

    make_object_func<&gl_api::GenBuffers, buffer_tag> gen_buffers{*this};

    make_object_func<&gl_api::CreateBuffers, buffer_tag> create_buffers{*this};

    make_object_func<&gl_api::GenFramebuffers, framebuffer_tag> gen_framebuffers{
      *this};

    make_object_func<&gl_api::CreateFramebuffers, framebuffer_tag>
      create_framebuffers{*this};

    make_object_func<&gl_api::GenProgramPipelines, program_pipeline_tag>
      gen_program_pipelines{*this};

    make_object_func<&gl_api::CreateProgramPipelines, program_pipeline_tag>
      create_program_pipelines{*this};

    make_object_func<&gl_api::GenQueries, query_tag> gen_queries{*this};

    make_object_func<&gl_api::CreateQueries, query_tag> create_queries{*this};

    make_object_func<&gl_api::GenRenderbuffers, renderbuffer_tag>
      gen_renderbuffers{*this};

    make_object_func<&gl_api::CreateRenderbuffers, renderbuffer_tag>
      create_renderbuffers{*this};

    make_object_func<&gl_api::GenSamplers, sampler_tag> gen_samplers{*this};

    make_object_func<&gl_api::CreateSamplers, sampler_tag> create_samplers{
      *this};

    make_object_func<&gl_api::GenTextures, texture_tag> gen_textures{*this};

    make_object_func<&gl_api::CreateTextures, texture_tag> create_textures{
      *this};

    make_object_func<&gl_api::GenTransformFeedbacks, transform_feedback_tag>
      gen_transform_feedbacks{*this};

    make_object_func<&gl_api::CreateTransformFeedbacks, transform_feedback_tag>
      create_transform_feedbacks{*this};

    make_object_func<&gl_api::GenVertexArrays, vertex_array_tag>
      gen_vertex_arrays{*this};

    make_object_func<&gl_api::CreateVertexArrays, vertex_array_tag>
      create_vertex_arrays{*this};

    simple_adapted_function<&gl_api::GenPathsNV, owned_path_nv_name(sizei_type)>
      create_paths_nv{*this};

    // delete objects
    simple_adapted_function<&gl_api::DeleteSync, void(sync_type)> delete_sync{
      *this};

    auto clean_up(sync_type obj) const noexcept {
        return delete_sync(obj);
    }

    template <auto Wrapper, typename ObjTag>
    using del_object_func = c_api::combined<
      simple_adapted_function<Wrapper, void(span<name_type>)>,
      simple_adapted_function<Wrapper, void(gl_owned_object_name<ObjTag>)>>;

    simple_adapted_function<&gl_api::DeleteShader, void(owned_shader_name)>
      delete_shader{*this};

    auto clean_up(owned_shader_name obj) const noexcept {
        return delete_shader(std::move(obj));
    }

    simple_adapted_function<&gl_api::DeleteProgram, void(owned_program_name)>
      delete_program{*this};

    auto clean_up(owned_program_name obj) const noexcept {
        return delete_program(std::move(obj));
    }

    del_object_func<&gl_api::DeleteBuffers, buffer_tag> delete_buffers{*this};

    auto clean_up(owned_buffer_name obj) const noexcept {
        return delete_buffers(std::move(obj));
    }

    auto clean_up(gl_object_name_span<buffer_tag> objs) const noexcept {
        return delete_buffers(objs.raw_handles());
    }

    del_object_func<&gl_api::DeleteFramebuffers, framebuffer_tag>
      delete_framebuffers{*this};

    auto clean_up(owned_framebuffer_name obj) const noexcept {
        return delete_framebuffers(std::move(obj));
    }

    auto clean_up(gl_object_name_span<framebuffer_tag> objs) const noexcept {
        return delete_framebuffers(objs.raw_handles());
    }

    del_object_func<&gl_api::DeleteProgramPipelines, program_pipeline_tag>
      delete_program_pipelines{*this};

    auto clean_up(owned_program_pipeline_name obj) const noexcept {
        return delete_program_pipelines(std::move(obj));
    }

    auto clean_up(
      gl_object_name_span<program_pipeline_tag> objs) const noexcept {
        return delete_program_pipelines(objs.raw_handles());
    }

    del_object_func<&gl_api::DeleteQueries, query_tag> delete_queries{*this};

    auto clean_up(owned_query_name obj) const noexcept {
        return delete_queries(std::move(obj));
    }

    auto clean_up(gl_object_name_span<query_tag> objs) const noexcept {
        return delete_queries(objs.raw_handles());
    }

    del_object_func<&gl_api::DeleteRenderbuffers, renderbuffer_tag>
      delete_renderbuffers{*this};

    auto clean_up(owned_renderbuffer_name obj) const noexcept {
        return delete_renderbuffers(std::move(obj));
    }

    auto clean_up(gl_object_name_span<renderbuffer_tag> objs) const noexcept {
        return delete_renderbuffers(objs.raw_handles());
    }

    del_object_func<&gl_api::DeleteSamplers, sampler_tag> delete_samplers{
      *this};

    auto clean_up(owned_sampler_name obj) const noexcept {
        return delete_samplers(std::move(obj));
    }

    auto clean_up(gl_object_name_span<sampler_tag> objs) const noexcept {
        return delete_samplers(objs.raw_handles());
    }

    del_object_func<&gl_api::DeleteTextures, texture_tag> delete_textures{
      *this};

    auto clean_up(owned_texture_name obj) const noexcept {
        return delete_textures(std::move(obj));
    }

    auto clean_up(gl_object_name_span<texture_tag> objs) const noexcept {
        return delete_textures(objs.raw_handles());
    }

    del_object_func<&gl_api::DeleteTransformFeedbacks, transform_feedback_tag>
      delete_transform_feedbacks{*this};

    auto clean_up(owned_transform_feedback_name obj) const noexcept {
        return delete_transform_feedbacks(std::move(obj));
    }

    auto clean_up(
      gl_object_name_span<transform_feedback_tag> objs) const noexcept {
        return delete_transform_feedbacks(objs.raw_handles());
    }

    del_object_func<&gl_api::DeleteVertexArrays, vertex_array_tag>
      delete_vertex_arrays{*this};

    auto clean_up(owned_vertex_array_name obj) const noexcept {
        return delete_vertex_arrays(std::move(obj));
    }

    auto clean_up(gl_object_name_span<vertex_array_tag> objs) const noexcept {
        return delete_vertex_arrays(objs.raw_handles());
    }

    simple_adapted_function<
      &gl_api::DeletePathsNV,
      void(owned_path_nv_name, sizei_type)>
      delete_paths_nv{*this};

    auto clean_up(owned_path_nv_name obj, sizei_type count) const noexcept {
        return delete_paths_nv(std::move(obj), count);
    }

    simple_adapted_function<&gl_api::IsSync, true_false(sync_type)> is_sync{
      *this};

    simple_adapted_function<&gl_api::IsBuffer, true_false(buffer_name)>
      is_buffer{*this};

    simple_adapted_function<&gl_api::IsFramebuffer, true_false(framebuffer_name)>
      is_framebuffer{*this};

    simple_adapted_function<
      &gl_api::IsProgramPipeline,
      true_false(program_pipeline_name)>
      is_program_pipeline{*this};

    simple_adapted_function<&gl_api::IsProgram, true_false(program_name)>
      is_program{*this};

    simple_adapted_function<&gl_api::IsQuery, true_false(query_name)> is_query{
      *this};

    simple_adapted_function<
      &gl_api::IsRenderbuffer,
      true_false(renderbuffer_name)>
      is_renderbuffer{*this};

    simple_adapted_function<&gl_api::IsSampler, true_false(sampler_name)>
      is_sampler{*this};

    simple_adapted_function<&gl_api::IsShader, true_false(shader_name)>
      is_shader{*this};

    simple_adapted_function<&gl_api::IsTexture, true_false(texture_name)>
      is_texture{*this};

    simple_adapted_function<
      &gl_api::IsTransformFeedback,
      true_false(transform_feedback_name)>
      is_transform_feedback{*this};

    simple_adapted_function<&gl_api::IsVertexArray, true_false(vertex_array_name)>
      is_vertex_array{*this};

    simple_adapted_function<&gl_api::IsPathNV, true_false(path_nv_name)>
      is_path_nv{*this};

    simple_adapted_function<&gl_api::Enable, void(capability)> enable{*this};
    simple_adapted_function<&gl_api::Enablei, void(capability, uint_type)>
      enablei{*this};

    simple_adapted_function<&gl_api::Disable, void(capability)> disable{*this};
    simple_adapted_function<&gl_api::Disablei, void(capability, uint_type)>
      disablei{*this};

    simple_adapted_function<&gl_api::IsEnabled, true_false(capability)>
      is_enabled{*this};
    simple_adapted_function<
      &gl_api::IsEnabledi,
      true_false(capability, uint_type)>
      is_enabledi{*this};

    simple_adapted_function<
      &gl_api::MemoryBarrier,
      void(c_api::enum_bitfield<memory_barrier_bit>)>
      memory_barrier{*this};

    simple_adapted_function<
      &gl_api::MemoryBarrierByRegion,
      void(c_api::enum_bitfield<memory_barrier_bit>)>
      memory_barrier_by_region{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::Viewport,
        void(int_type, int_type, sizei_type, sizei_type)>,
      simple_adapted_function<
        &gl_api::Viewport,
        void(c_api::defaulted, c_api::defaulted, sizei_type, sizei_type)>>
      viewport{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::ViewportArrayv,
        void(uint_type, memory::chunk_span<const float_type, 4>)>,
      simple_adapted_function<
        &gl_api::ViewportArrayv,
        void(c_api::defaulted, memory::chunk_span<const float_type, 4>)>>
      viewport_array{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::StencilFunc,
        void(compare_function, int_type, uint_type)>,
      simple_adapted_function<
        &gl_api::StencilFunc,
        void(compare_function, int_type, c_api::substituted<~uint_type{0U}>)>>
      stencil_func{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::StencilFuncSeparate,
        void(face_mode, compare_function, int_type, uint_type)>,
      simple_adapted_function<
        &gl_api::StencilFuncSeparate,
        void(
          face_mode,
          compare_function,
          int_type,
          c_api::substituted<~uint_type{0U}>)>>
      stencil_func_separate{*this};

    simple_adapted_function<
      &gl_api::StencilOp,
      void(stencil_operation, stencil_operation, stencil_operation)>
      stencil_op{*this};

    simple_adapted_function<
      &gl_api::StencilOpSeparate,
      void(face_mode, stencil_operation, stencil_operation, stencil_operation)>
      stencil_op_separate{*this};

    simple_adapted_function<&gl_api::DepthFunc, void(compare_function)>
      depth_func{*this};

    simple_adapted_function<
      &gl_api::ColorMask,
      void(true_false, true_false, true_false, true_false)>
      color_mask{*this};

    simple_adapted_function<
      &gl_api::ColorMaski,
      void(uint_type, true_false, true_false, true_false, true_false)>
      color_mask_i{*this};

    simple_adapted_function<&gl_api::DepthMask, void(true_false)> depth_mask{
      *this};

    simple_adapted_function<&gl_api::StencilMask, void(uint_type)> stencil_mask{
      *this};

    simple_adapted_function<
      &gl_api::StencilMaskSeparate,
      void(face_mode, uint_type)>
      stencil_mask_separate{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::ClearColor,
        void(float_type, float_type, float_type, float_type)>,
      simple_adapted_function<&gl_api::ClearColor, void(vec4)>>
      clear_color{*this};

    simple_adapted_function<&gl_api::ClearDepth, void(float_type)> clear_depth{
      *this};
    simple_adapted_function<&gl_api::ClearStencil, void(int_type)> clear_stencil{
      *this};

    simple_adapted_function<
      &gl_api::Clear,
      void(c_api::enum_bitfield<buffer_clear_bit>)>
      clear{*this};

    simple_adapted_function<
      &gl_api::ShaderSource,
      void(shader_name, const glsl_source_ref&)>
      shader_source{*this};

    simple_adapted_function<&gl_api::CompileShader, void(shader_name)>
      compile_shader{*this};

    simple_adapted_function<
      &gl_api::CompileShaderInclude,
      void(shader_name, const glsl_source_ref&)>
      compile_shader_include{*this};

    query_function<
      &gl_api::GetShaderiv,
      int_type,
      mp_list<shader_name>,
      mp_list<shader_parameter>>
      get_shader_i{*this};

    adapted_function<
      &gl_api::GetShaderInfoLog,
      void(shader_name, span<char_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 3, 2>,
        c_api::convert<name_type, c_api::trivial_arg_map<1>>,
        c_api::convert<sizei_type, c_api::get_size_map<2, 2>>,
        c_api::get_data_map<4, 2>>>
      get_shader_info_log{*this};

    simple_adapted_function<
      &gl_api::AttachShader,
      void(program_name, shader_name)>
      attach_shader{*this};

    simple_adapted_function<
      &gl_api::DetachShader,
      void(program_name, shader_name)>
      detach_shader{*this};

    simple_adapted_function<&gl_api::LinkProgram, void(program_name)>
      link_program{*this};

    query_function<
      &gl_api::GetProgramiv,
      int_type,
      mp_list<program_name>,
      mp_list<program_parameter>>
      get_program_i{*this};

    adapted_function<
      &gl_api::GetProgramInfoLog,
      void(program_name, span<char_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 3, 2>,
        c_api::convert<name_type, c_api::trivial_arg_map<1>>,
        c_api::convert<sizei_type, c_api::get_size_map<2, 2>>,
        c_api::get_data_map<4, 2>>>
      get_program_info_log{*this};

    simple_adapted_function<&gl_api::UseProgram, void(program_name)> use_program{
      *this};

    simple_adapted_function<
      &gl_api::GetProgramResourceIndex,
      uint_type(program_name, program_interface, string_view)>
      get_program_resource_index{*this};

    simple_adapted_function<
      &gl_api::GetProgramResourceIndex,
      shader_storage_block_index(
        program_name,
        c_api::substituted<GL_SHADER_STORAGE_BLOCK>,
        string_view)>
      get_shader_storage_block_index{*this};

    simple_adapted_function<
      &gl_api::GetProgramResourceLocation,
      program_resource_location(program_name, program_interface, string_view)>
      get_program_resource_location{*this};

    adapted_function<
      &gl_api::GetProgramResourceName,
      program_resource_location(
        program_name,
        program_interface,
        uint_type,
        span<char_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 5, 4>,
        c_api::trivial_arg_map<1, 2, 3>,
        c_api::convert<sizei_type, c_api::get_size_map<4, 4>>,
        c_api::get_data_map<6, 4>>>
      get_program_resource_name{*this};

    query_function<
      &gl_api::GetProgramInterfaceiv,
      int_type,
      mp_list<program_name, program_interface>,
      mp_list<program_property>>
      get_program_interface_i{*this};

    adapted_function<
      &gl_api::GetProgramResourceiv,
      program_resource_location(
        program_name,
        program_interface,
        uint_type,
        c_api::enum_class_view<program_property>,
        span<int_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 7, 5>,
        c_api::make_arg_map<1, 1, name_type, program_name>,
        c_api::trivial_arg_map<2, 3>,
        c_api::convert<sizei_type, c_api::get_size_map<4, 4>>,
        c_api::get_data_map<7, 4>,
        c_api::convert<sizei_type, c_api::get_size_map<6, 6>>,
        c_api::get_data_map<8, 5>>>
      get_program_resource_i{*this};

    adapted_function<
      &gl_api::GetProgramResourcefvNV,
      program_resource_location(
        program_name,
        program_interface,
        uint_type,
        c_api::enum_class_view<program_property>,
        span<float_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 7, 5>,
        c_api::make_arg_map<1, 1, name_type, program_name>,
        c_api::trivial_arg_map<2, 3>,
        c_api::convert<sizei_type, c_api::get_size_map<4, 4>>,
        c_api::get_data_map<7, 4>,
        c_api::convert<sizei_type, c_api::get_size_map<6, 6>>,
        c_api::get_data_map<8, 5>>>
      get_program_resource_f{*this};

    simple_adapted_function<
      &gl_api::BindAttribLocation,
      void(program_name, vertex_attrib_location, string_view)>
      bind_attrib_location{*this};

    simple_adapted_function<
      &gl_api::GetAttribLocation,
      vertex_attrib_location(program_name, string_view)>
      get_attrib_location{*this};

    using _get_active_attrib_name_t = adapted_function<
      &gl_api::GetActiveAttrib,
      program_resource_location(
        program_name,
        vertex_attrib_location,
        int_type*,
        enum_type*,
        span<char_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 4, 5>,
        c_api::make_arg_map<1, 1, name_type, program_name>,
        c_api::get_index_map<2, 2>,
        c_api::convert<sizei_type, c_api::get_size_map<3, 5>>,
        c_api::reorder_arg_map<5, 3>,
        c_api::reorder_arg_map<6, 4>,
        c_api::get_data_map<7, 5>>>;

    struct : _get_active_attrib_name_t {
        using base = _get_active_attrib_name_t;
        using base::base;

        constexpr auto operator()(
          program_name prog,
          vertex_attrib_location loc,
          int_type& size,
          span<char_type> dest) const noexcept {
            enum_type type{};
            return base::operator()(prog, loc, &size, &type, dest);
        }
    } get_active_attrib_name{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::TransformFeedbackVaryings,
        void(program_name, const glsl_source_ref&, transform_feedback_mode)>,
      simple_adapted_function<
        &gl_api::TransformFeedbackVaryings,
        void(
          program_name,
          const glsl_source_ref&,
          c_api::substituted<GL_SEPARATE_ATTRIBS>)>>
      transform_feedback_varyings{*this};

    simple_adapted_function<
      &gl_api::BindFragDataLocation,
      void(program_name, frag_data_location, string_view)>
      bind_frag_data_location{*this};

    simple_adapted_function<
      &gl_api::GetFragDataLocation,
      frag_data_location(program_name, string_view)>
      get_frag_data_location{*this};

    simple_adapted_function<
      &gl_api::GetFragDataIndex,
      int_type(program_name, string_view)>
      get_frag_data_index{*this};

    simple_adapted_function<
      &gl_api::BindFragDataLocationIndexed,
      void(program_name, uint_type, frag_data_location, string_view)>
      bind_frag_data_location_indexed{*this};

    simple_adapted_function<
      &gl_api::GetUniformLocation,
      uniform_location(program_name, string_view)>
      get_uniform_location{*this};

    simple_adapted_function<
      &gl_api::GetUniformBlockIndex,
      uniform_block_index(program_name, string_view)>
      get_uniform_block_index{*this};

    adapted_function<
      &gl_api::GetActiveUniformName,
      program_resource_location(program_name, uniform_location, span<char_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 4, 3>,
        c_api::trivial_arg_map<1>,
        c_api::get_index_map<2, 2>,
        c_api::convert<sizei_type, c_api::get_size_map<3, 3>>,
        c_api::get_data_map<5, 3>>>
      get_active_uniform_name{*this};

    simple_adapted_function<
      &gl_api::GetSubroutineUniformLocation,
      subroutine_uniform_location(program_name, shader_type, string_view)>
      get_subroutine_uniform_location{*this};

    adapted_function<
      &gl_api::GetActiveSubroutineUniformName,
      program_resource_location(
        program_name,
        shader_type,
        uniform_location,
        span<char_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 5, 4>,
        c_api::trivial_arg_map<1, 2>,
        c_api::get_index_map<3, 3>,
        c_api::convert<sizei_type, c_api::get_size_map<4, 4>>,
        c_api::get_data_map<6, 4>>>
      get_active_subroutine_uniform_name{*this};

    simple_adapted_function<
      &gl_api::GetSubroutineIndex,
      subroutine_location(program_name, shader_type, string_view)>
      get_subroutine_index{*this};

    adapted_function<
      &gl_api::GetActiveSubroutineName,
      program_resource_location(
        program_name,
        shader_type,
        subroutine_location,
        span<char_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 5, 4>,
        c_api::trivial_arg_map<1, 2>,
        c_api::get_index_map<3, 3>,
        c_api::convert<sizei_type, c_api::get_size_map<4, 4>>,
        c_api::get_data_map<6, 4>>>
      get_active_subroutine_name{*this};

    using _uniform_subroutines_t = simple_adapted_function<
      &gl_api::UniformSubroutinesuiv,
      void(shader_type, span<const uint_type>)>;

    struct : _uniform_subroutines_t {
        using base = _uniform_subroutines_t;
        using base::base;

        constexpr auto operator()(
          shader_type shdr_type,
          subroutine_location subr) const noexcept {
            const uint_type idx{subr.index()};
            return base::operator()(shdr_type, view_one(idx));
        }
    } uniform_subroutines{*this};

    // uniform
    // uint
    simple_adapted_function<
      &gl_api::Uniform1ui,
      void(uniform_location, uint_type)>
      uniform1ui{*this};

    simple_adapted_function<
      &gl_api::Uniform2ui,
      void(uniform_location, uint_type, uint_type)>
      uniform2ui{*this};

    simple_adapted_function<
      &gl_api::Uniform3ui,
      void(uniform_location, uint_type, uint_type, uint_type)>
      uniform3ui{*this};

    simple_adapted_function<
      &gl_api::Uniform4ui,
      void(uniform_location, uint_type, uint_type, uint_type, uint_type)>
      uniform4ui{*this};

    simple_adapted_function<
      &gl_api::Uniform1uiv,
      void(uniform_location, memory::chunk_span<const uint_type, 1>)>
      uniform1uiv{*this};

    simple_adapted_function<
      &gl_api::Uniform2uiv,
      void(uniform_location, memory::chunk_span<const uint_type, 2>)>
      uniform2uiv{*this};

    simple_adapted_function<
      &gl_api::Uniform3uiv,
      void(uniform_location, memory::chunk_span<const uint_type, 3>)>
      uniform3uiv{*this};

    simple_adapted_function<
      &gl_api::Uniform4uiv,
      void(uniform_location, memory::chunk_span<const uint_type, 4>)>
      uniform4uiv{*this};

    // int
    simple_adapted_function<&gl_api::Uniform1i, void(uniform_location, int_type)>
      uniform1i{*this};

    simple_adapted_function<
      &gl_api::Uniform2i,
      void(uniform_location, int_type, int_type)>
      uniform2i{*this};

    simple_adapted_function<
      &gl_api::Uniform3i,
      void(uniform_location, int_type, int_type, int_type)>
      uniform3i{*this};

    simple_adapted_function<
      &gl_api::Uniform4i,
      void(uniform_location, int_type, int_type, int_type, int_type)>
      uniform4i{*this};

    simple_adapted_function<
      &gl_api::Uniform1iv,
      void(uniform_location, memory::chunk_span<const int_type, 1>)>
      uniform1iv{*this};

    simple_adapted_function<
      &gl_api::Uniform2iv,
      void(uniform_location, memory::chunk_span<const int_type, 2>)>
      uniform2iv{*this};

    simple_adapted_function<
      &gl_api::Uniform3iv,
      void(uniform_location, memory::chunk_span<const int_type, 3>)>
      uniform3iv{*this};

    simple_adapted_function<
      &gl_api::Uniform4iv,
      void(uniform_location, memory::chunk_span<const int_type, 4>)>
      uniform4iv{*this};

    // float
    simple_adapted_function<
      &gl_api::Uniform1f,
      void(uniform_location, float_type)>
      uniform1f{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::Uniform2f,
        void(uniform_location, float_type, float_type)>,
      simple_adapted_function<&gl_api::Uniform2f, void(uniform_location, vec2)>>
      uniform2f{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::Uniform3f,
        void(uniform_location, float_type, float_type, float_type)>,
      simple_adapted_function<&gl_api::Uniform3f, void(uniform_location, vec3)>>
      uniform3f{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::Uniform4f,
        void(uniform_location, float_type, float_type, float_type, float_type)>,
      simple_adapted_function<&gl_api::Uniform4f, void(uniform_location, vec4)>>
      uniform4f{*this};

    simple_adapted_function<
      &gl_api::Uniform1fv,
      void(uniform_location, memory::chunk_span<const float_type, 1>)>
      uniform1fv{*this};

    simple_adapted_function<
      &gl_api::Uniform2fv,
      void(uniform_location, memory::chunk_span<const float_type, 2>)>
      uniform2fv{*this};

    simple_adapted_function<
      &gl_api::Uniform3fv,
      void(uniform_location, memory::chunk_span<const float_type, 3>)>
      uniform3fv{*this};

    simple_adapted_function<
      &gl_api::Uniform4fv,
      void(uniform_location, memory::chunk_span<const float_type, 4>)>
      uniform4fv{*this};

    // matrix float
    simple_adapted_function<
      &gl_api::UniformMatrix2fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 4>)>
      uniform_matrix2fv{*this};

    simple_adapted_function<
      &gl_api::UniformMatrix3fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 9>)>
      uniform_matrix3fv{*this};

    simple_adapted_function<
      &gl_api::UniformMatrix4fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 16>)>
      uniform_matrix4fv{*this};

    simple_adapted_function<
      &gl_api::UniformMatrix2x3fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 6>)>
      uniform_matrix2x3fv{*this};

    simple_adapted_function<
      &gl_api::UniformMatrix2x4fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 8>)>
      uniform_matrix2x4fv{*this};

    simple_adapted_function<
      &gl_api::UniformMatrix3x2fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 6>)>
      uniform_matrix3x2fv{*this};

    simple_adapted_function<
      &gl_api::UniformMatrix3x4fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 12>)>
      uniform_matrix3x4fv{*this};

    simple_adapted_function<
      &gl_api::UniformMatrix4x2fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 8>)>
      uniform_matrix4x2fv{*this};

    simple_adapted_function<
      &gl_api::UniformMatrix4x3fv,
      void(
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 12>)>
      uniform_matrix4x3fv{*this};

    // program uniform
    // uint
    simple_adapted_function<
      &gl_api::ProgramUniform1ui,
      void(program_name, uniform_location, uint_type)>
      program_uniform1ui{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform2ui,
      void(program_name, uniform_location, uint_type, uint_type)>
      program_uniform2ui{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform3ui,
      void(program_name, uniform_location, uint_type, uint_type, uint_type)>
      program_uniform3ui{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform4ui,
      void(
        program_name,
        uniform_location,
        uint_type,
        uint_type,
        uint_type,
        uint_type)>
      program_uniform4ui{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform1uiv,
      void(program_name, uniform_location, memory::chunk_span<const uint_type, 1>)>
      program_uniform1uiv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform2uiv,
      void(program_name, uniform_location, memory::chunk_span<const uint_type, 2>)>
      program_uniform2uiv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform3uiv,
      void(program_name, uniform_location, memory::chunk_span<const uint_type, 3>)>
      program_uniform3uiv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform4uiv,
      void(program_name, uniform_location, memory::chunk_span<const uint_type, 4>)>
      program_uniform4uiv{*this};

    // int
    simple_adapted_function<
      &gl_api::ProgramUniform1i,
      void(program_name, uniform_location, int_type)>
      program_uniform1i{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform2i,
      void(program_name, uniform_location, int_type, int_type)>
      program_uniform2i{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform3i,
      void(program_name, uniform_location, int_type, int_type, int_type)>
      program_uniform3i{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform4i,
      void(program_name, uniform_location, int_type, int_type, int_type, int_type)>
      program_uniform4i{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform1iv,
      void(program_name, uniform_location, memory::chunk_span<const int_type, 1>)>
      program_uniform1iv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform2iv,
      void(program_name, uniform_location, memory::chunk_span<const int_type, 2>)>
      program_uniform2iv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform3iv,
      void(program_name, uniform_location, memory::chunk_span<const int_type, 3>)>
      program_uniform3iv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform4iv,
      void(program_name, uniform_location, memory::chunk_span<const int_type, 4>)>
      program_uniform4iv{*this};

    // float
    simple_adapted_function<
      &gl_api::ProgramUniform1f,
      void(program_name, uniform_location, float_type)>
      program_uniform1f{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::ProgramUniform2f,
        void(program_name, uniform_location, float_type, float_type)>,
      simple_adapted_function<
        &gl_api::ProgramUniform2f,
        void(program_name, uniform_location, vec2)>>
      program_uniform2f{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::ProgramUniform3f,
        void(program_name, uniform_location, float_type, float_type, float_type)>,
      simple_adapted_function<
        &gl_api::ProgramUniform3f,
        void(program_name, uniform_location, vec3)>>
      program_uniform3f{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::ProgramUniform4f,
        void(
          program_name,
          uniform_location,
          float_type,
          float_type,
          float_type,
          float_type)>,
      simple_adapted_function<
        &gl_api::ProgramUniform4f,
        void(program_name, uniform_location, vec4)>>
      program_uniform4f{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform1fv,
      void(
        program_name,
        uniform_location,
        memory::chunk_span<const float_type, 1>)>
      program_uniform1fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform2fv,
      void(
        program_name,
        uniform_location,
        memory::chunk_span<const float_type, 2>)>
      program_uniform2fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform3fv,
      void(
        program_name,
        uniform_location,
        memory::chunk_span<const float_type, 3>)>
      program_uniform3fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniform4fv,
      void(
        program_name,
        uniform_location,
        memory::chunk_span<const float_type, 4>)>
      program_uniform4fv{*this};

    // matrix float
    simple_adapted_function<
      &gl_api::ProgramUniformMatrix2fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 4>)>
      program_uniform_matrix2fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniformMatrix3fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 9>)>
      program_uniform_matrix3fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniformMatrix4fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 16>)>
      program_uniform_matrix4fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniformMatrix2x3fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 6>)>
      program_uniform_matrix2x3fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniformMatrix2x4fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 8>)>
      program_uniform_matrix2x4fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniformMatrix3x2fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 6>)>
      program_uniform_matrix3x2fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniformMatrix3x4fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 12>)>
      program_uniform_matrix3x4fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniformMatrix4x2fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 8>)>
      program_uniform_matrix4x2fv{*this};

    simple_adapted_function<
      &gl_api::ProgramUniformMatrix4x3fv,
      void(
        program_name,
        uniform_location,
        true_false transp,
        memory::chunk_span<const float_type, 12>)>
      program_uniform_matrix4x3fv{*this};

    simple_adapted_function<
      &gl_api::UniformBlockBinding,
      void(program_name, uniform_block_index, uint_type)>
      uniform_block_binding{*this};

    simple_adapted_function<
      &gl_api::ShaderStorageBlockBinding,
      void(program_name, shader_storage_block_index, uint_type)>
      shader_storage_block_binding{*this};

    // buffer ops
    simple_adapted_function<&gl_api::BindBuffer, void(buffer_target, buffer_name)>
      bind_buffer{*this};

    simple_adapted_function<
      &gl_api::BindBufferBase,
      void(buffer_target, uint_type, buffer_name)>
      bind_buffer_base{*this};

    simple_adapted_function<
      &gl_api::BindBufferRange,
      void(buffer_target, uint_type, buffer_name, intptr_type, sizeiptr_type)>
      bind_buffer_range{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::BufferStorage,
        void(
          buffer_target,
          sizeiptr_type,
          const_void_ptr_type,
          c_api::enum_bitfield<buffer_storage_bit>)>,
      simple_adapted_function<
        &gl_api::BufferStorage,
        void(buffer_target, sizeiptr_type, c_api::defaulted, c_api::defaulted)>>
      buffer_storage{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::NamedBufferStorage,
        void(
          buffer_name,
          sizeiptr_type,
          const_void_ptr_type,
          c_api::enum_bitfield<buffer_storage_bit>)>,
      simple_adapted_function<
        &gl_api::NamedBufferStorage,
        void(buffer_name, sizeiptr_type, c_api::defaulted, c_api::defaulted)>>
      named_buffer_storage{*this};

    simple_adapted_function<
      &gl_api::BufferData,
      void(buffer_target, buffer_data_spec, buffer_usage)>
      buffer_data{*this};

    simple_adapted_function<
      &gl_api::NamedBufferData,
      void(buffer_name, buffer_data_spec, buffer_usage)>
      named_buffer_data{*this};

    simple_adapted_function<
      &gl_api::BufferSubData,
      void(buffer_target, intptr_type, buffer_data_spec)>
      buffer_sub_data{*this};

    simple_adapted_function<
      &gl_api::NamedBufferSubData,
      void(buffer_name, intptr_type, buffer_data_spec)>
      named_buffer_sub_data{*this};

    using _clear_buffer_data_t = simple_adapted_function<
      &gl_api::ClearBufferData,
      void(
        buffer_target,
        pixel_internal_format,
        pixel_format,
        pixel_data_type,
        const_void_ptr_type)>;

    struct : _clear_buffer_data_t {
        using base = _clear_buffer_data_t;
        using base::base;
        using base::operator();

        template <typename T>
        constexpr auto operator()(
          buffer_target tgt,
          pixel_internal_format ifmt,
          const T& value) const noexcept {
            return (*this)(
              tgt, ifmt, pixel_format_of<T>(), pixel_data_type_of<T>(), &value);
        }

        template <typename T>
        constexpr auto operator()(buffer_target tgt, const T& value)
          const noexcept {
            return (*this)(tgt, internal_format_of<T>(), &value);
        }

        template <typename T>
        constexpr auto operator()(
          buffer_target tgt,
          pixel_internal_format ifmt,
          std::type_identity<T>) const noexcept {
            return (*this)(
              tgt, ifmt, pixel_format_of<T>(), pixel_data_type_of<T>(), nullptr);
        }

        template <typename T>
        constexpr auto operator()(buffer_target tgt, std::type_identity<T> tid)
          const noexcept {
            return (*this)(tgt, internal_format_of<T>(), tid);
        }
    } clear_buffer_data{*this};

    using _clear_named_buffer_data_t = simple_adapted_function<
      &gl_api::ClearNamedBufferData,
      void(
        buffer_name,
        pixel_internal_format,
        pixel_format,
        pixel_data_type,
        const_void_ptr_type)>;

    struct : _clear_named_buffer_data_t {
        using base = _clear_named_buffer_data_t;
        using base::base;
        using base::operator();

        template <typename T>
        constexpr auto operator()(
          buffer_name buf,
          pixel_internal_format ifmt,
          const T& value) const noexcept {
            return (*this)(
              buf, ifmt, pixel_format_of<T>(), pixel_data_type_of<T>(), &value);
        }

        template <typename T>
        constexpr auto operator()(buffer_name buf, const T& value)
          const noexcept {
            return (*this)(buf, internal_format_of<T>(), &value);
        }

        template <typename T>
        constexpr auto operator()(
          buffer_name buf,
          pixel_internal_format ifmt,
          pixel_format fmt,
          std::type_identity<T>) const noexcept {
            return (*this)(buf, ifmt, fmt, pixel_data_type_of<T>(), nullptr);
        }

        template <typename T>
        constexpr auto operator()(buffer_name buf, std::type_identity<T> tid)
          const noexcept {
            return (*this)(buf, internal_format_of<T>(), tid);
        }
    } clear_named_buffer_data{*this};

    using _clear_buffer_sub_data_t = simple_adapted_function<
      &gl_api::ClearBufferSubData,
      void(
        buffer_target,
        pixel_internal_format,
        intptr_type,
        sizeiptr_type,
        pixel_format,
        pixel_data_type,
        const_void_ptr_type)>;

    struct : _clear_buffer_sub_data_t {
        using base = _clear_buffer_sub_data_t;
        using base::base;
        using base::operator();

        template <typename T>
        constexpr auto operator()(
          buffer_target tgt,
          intptr_type offs,
          sizeiptr_type count,
          pixel_internal_format ifmt,
          const T& value) const noexcept {
            return (*this)(
              tgt,
              ifmt,
              offs,
              count * span_size_of<T>(),
              pixel_format_of<T>(),
              pixel_data_type_of<T>(),
              &value);
        }

        template <typename T>
        constexpr auto operator()(
          buffer_target tgt,
          intptr_type offs,
          sizeiptr_type count,
          const T& value) const noexcept {
            return (*this)(tgt, offs, count, internal_format_of<T>(), value);
        }
    } clear_buffer_sub_data{*this};

    using _clear_named_buffer_sub_data_t = simple_adapted_function<
      &gl_api::ClearNamedBufferSubData,
      void(
        buffer_name,
        pixel_internal_format,
        intptr_type,
        sizeiptr_type,
        pixel_format,
        pixel_data_type,
        const_void_ptr_type)>;

    struct : _clear_named_buffer_sub_data_t {
        using base = _clear_named_buffer_sub_data_t;
        using base::base;
        using base::operator();

        template <typename T>
        constexpr auto operator()(
          buffer_name buf,
          intptr_type offs,
          sizeiptr_type count,
          pixel_internal_format ifmt,
          const T& value) const noexcept {
            return (*this)(
              buf,
              ifmt,
              offs,
              count * span_size_of<T>(),
              pixel_format_of<T>(),
              pixel_data_type_of<T>(),
              &value);
        }

        template <typename T>
        constexpr auto operator()(
          buffer_name buf,
          intptr_type offs,
          sizeiptr_type count,
          const T& value) const noexcept {
            return (*this)(buf, offs, count, internal_format_of<T>(), value);
        }
    } clear_named_buffer_sub_data{*this};

    simple_adapted_function<
      &gl_api::MapBuffer,
      void_ptr_type(buffer_target, c_api::enum_bitfield<buffer_map_access_bit>)>
      map_buffer{*this};

    simple_adapted_function<
      &gl_api::MapNamedBuffer,
      void_ptr_type(buffer_name, c_api::enum_bitfield<buffer_map_access_bit>)>
      map_named_buffer{*this};

    simple_adapted_function<
      &gl_api::MapBufferRange,
      void_ptr_type(
        buffer_target,
        intptr_type,
        sizeiptr_type,
        c_api::enum_bitfield<buffer_map_access_bit>)>
      map_buffer_range{*this};

    simple_adapted_function<
      &gl_api::MapNamedBufferRange,
      void_ptr_type(
        buffer_name,
        intptr_type,
        sizeiptr_type,
        c_api::enum_bitfield<buffer_map_access_bit>)>
      map_named_buffer_range{*this};

    simple_adapted_function<
      &gl_api::FlushMappedBufferRange,
      void_ptr_type(buffer_target, intptr_type, sizeiptr_type)>
      flush_mapped_buffer_range{*this};

    simple_adapted_function<
      &gl_api::FlushMappedNamedBufferRange,
      void_ptr_type(buffer_name, intptr_type, sizeiptr_type)>
      flush_mapped_named_buffer_range{*this};

    simple_adapted_function<&gl_api::UnmapBuffer, void_ptr_type(buffer_target)>
      unmap_buffer{*this};

    simple_adapted_function<&gl_api::UnmapNamedBuffer, void_ptr_type(buffer_name)>
      unmap_named_buffer{*this};

    simple_adapted_function<&gl_api::InvalidateBufferData, void(buffer_name)>
      invalidate_buffer_data{*this};

    simple_adapted_function<
      &gl_api::InvalidateBufferSubData,
      void(buffer_name, intptr_type, sizeiptr_type)>
      invalidate_buffer_sub_data{*this};

    simple_adapted_function<
      &gl_api::CopyBufferSubData,
      void(buffer_target, buffer_target, intptr_type, intptr_type, sizeiptr_type)>
      copy_buffer_sub_data{*this};

    simple_adapted_function<
      &gl_api::CopyNamedBufferSubData,
      void(buffer_name, buffer_name, intptr_type, intptr_type, sizeiptr_type)>
      copy_named_buffer_sub_data{*this};

    query_function<
      &gl_api::GetBufferParameteriv,
      int_type,
      mp_list<buffer_target>,
      mp_list<buffer_parameter>>
      get_buffer_parameter_i{*this};

    query_function<
      &gl_api::GetNamedBufferParameteriv,
      int_type,
      mp_list<buffer_name>,
      mp_list<buffer_parameter>>
      get_named_buffer_parameter_i{*this};

    query_function<
      &gl_api::GetBufferParameteri64v,
      int64_type,
      mp_list<buffer_target>,
      mp_list<buffer_parameter>>
      get_buffer_parameter_i64{*this};

    query_function<
      &gl_api::GetNamedBufferParameteri64v,
      int64_type,
      mp_list<buffer_name>,
      mp_list<buffer_parameter>>
      get_named_buffer_parameter_i64{*this};

    // vertex_array ops
    simple_adapted_function<&gl_api::BindVertexArray, void(vertex_array_name)>
      bind_vertex_array{*this};

    simple_adapted_function<
      &gl_api::BindVertexBuffer,
      void(vertex_buffer_binding, buffer_name, intptr_type, sizei_type)>
      bind_vertex_buffer{*this};

    simple_adapted_function<
      &gl_api::VertexArrayVertexBuffer,
      void(
        vertex_array_name,
        vertex_buffer_binding,
        buffer_name,
        intptr_type,
        sizei_type)>
      vertex_array_vertex_buffer{*this};

    simple_adapted_function<
      &gl_api::VertexArrayElementBuffer,
      void(vertex_array_name, buffer_name)>
      vertex_array_element_buffer{*this};

    simple_adapted_function<
      &gl_api::EnableVertexAttribArray,
      void(vertex_attrib_location)>
      enable_vertex_attrib_array{*this};

    simple_adapted_function<
      &gl_api::EnableVertexArrayAttrib,
      void(vertex_array_name, vertex_attrib_location)>
      enable_vertex_array_attrib{*this};

    simple_adapted_function<
      &gl_api::DisableVertexAttribArray,
      void(vertex_attrib_location)>
      disable_vertex_attrib_array{*this};

    simple_adapted_function<
      &gl_api::DisableVertexArrayAttrib,
      void(vertex_array_name, vertex_attrib_location)>
      disable_vertex_array_attrib{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::VertexAttrib1s,
        void(vertex_attrib_location, short_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib2s,
        void(vertex_attrib_location, short_type, short_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib3s,
        void(vertex_attrib_location, short_type, short_type, short_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib4s,
        void(vertex_attrib_location, short_type, short_type, short_type, short_type)>>
      vertex_attrib_s{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::VertexAttribI1i,
        void(vertex_attrib_location, int_type)>,
      simple_adapted_function<
        &gl_api::VertexAttribI2i,
        void(vertex_attrib_location, int_type, int_type)>,
      simple_adapted_function<
        &gl_api::VertexAttribI3i,
        void(vertex_attrib_location, int_type, int_type, int_type)>,
      simple_adapted_function<
        &gl_api::VertexAttribI4i,
        void(vertex_attrib_location, int_type, int_type, int_type, int_type)>>
      vertex_attrib_i{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::VertexAttrib1f,
        void(vertex_attrib_location, float_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib2f,
        void(vertex_attrib_location, float_type, float_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib3f,
        void(vertex_attrib_location, float_type, float_type, float_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib4f,
        void(vertex_attrib_location, float_type, float_type, float_type, float_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib2f,
        void(vertex_attrib_location, vec2)>,
      simple_adapted_function<
        &gl_api::VertexAttrib3f,
        void(vertex_attrib_location, vec3)>,
      simple_adapted_function<
        &gl_api::VertexAttrib4f,
        void(vertex_attrib_location, vec4)>>
      vertex_attrib_f{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::VertexAttrib1d,
        void(vertex_attrib_location, double_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib2d,
        void(vertex_attrib_location, double_type, double_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib3d,
        void(vertex_attrib_location, double_type, double_type, double_type)>,
      simple_adapted_function<
        &gl_api::VertexAttrib4d,
        void(
          vertex_attrib_location,
          double_type,
          double_type,
          double_type,
          double_type)>>
      vertex_attrib_d{*this};

    simple_adapted_function<
      &gl_api::VertexAttribFormat,
      void(vertex_attrib_location, int_type, data_type, true_false, uint_type)>
      vertex_attrib_format{*this};

    simple_adapted_function<
      &gl_api::VertexAttribIFormat,
      void(vertex_attrib_location, int_type, data_type, uint_type)>
      vertex_attrib_iformat{*this};

    simple_adapted_function<
      &gl_api::VertexAttribLFormat,
      void(vertex_attrib_location, int_type, data_type, uint_type)>
      vertex_attrib_lformat{*this};

    simple_adapted_function<
      &gl_api::VertexArrayAttribFormat,
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        true_false,
        uint_type)>
      vertex_array_attrib_format{*this};

    simple_adapted_function<
      &gl_api::VertexArrayAttribIFormat,
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        uint_type)>
      vertex_array_attrib_iformat{*this};

    simple_adapted_function<
      &gl_api::VertexArrayAttribLFormat,
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        uint_type)>
      vertex_array_attrib_lformat{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::VertexAttribPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          true_false,
          sizei_type,
          const_void_ptr_type)>,
      simple_adapted_function<
        &gl_api::VertexAttribPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          true_false,
          c_api::defaulted,
          c_api::defaulted)>>
      vertex_attrib_pointer{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::VertexAttribIPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          sizei_type,
          const_void_ptr_type)>,
      simple_adapted_function<
        &gl_api::VertexAttribIPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          c_api::defaulted,
          c_api::defaulted)>>
      vertex_attrib_ipointer{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::VertexAttribLPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          sizei_type,
          const_void_ptr_type)>,
      simple_adapted_function<
        &gl_api::VertexAttribLPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          c_api::defaulted,
          c_api::defaulted)>>
      vertex_attrib_lpointer{*this};

    simple_adapted_function<
      &gl_api::VertexAttribBinding,
      void(vertex_attrib_location, vertex_buffer_binding)>
      vertex_attrib_binding{*this};

    simple_adapted_function<
      &gl_api::VertexArrayAttribBinding,
      void(vertex_array_name, vertex_attrib_location, vertex_buffer_binding)>
      vertex_array_attrib_binding{*this};

    simple_adapted_function<
      &gl_api::VertexBindingDivisor,
      void(vertex_buffer_binding, uint_type)>
      vertex_binding_divisor{*this};

    simple_adapted_function<
      &gl_api::VertexArrayBindingDivisor,
      void(vertex_buffer_binding, uint_type)>
      vertex_array_binding_divisor{*this};

    simple_adapted_function<
      &gl_api::VertexAttribDivisor,
      void(vertex_attrib_location, uint_type)>
      vertex_attrib_divisor{*this};

    // texture ops
    simple_adapted_function<&gl_api::ActiveTexture, void(texture_unit)>
      active_texture{*this};

    simple_adapted_function<
      &gl_api::BindTexture,
      void(texture_target, texture_name)>
      bind_texture{*this};

    simple_adapted_function<
      &gl_api::BindTextures,
      void(uint_type, span<const name_type>)>
      bind_textures{*this};

    simple_adapted_function<
      &gl_api::BindTextureUnit,
      void(uint_type, texture_name)>
      bind_texture_unit{*this};

    simple_adapted_function<
      &gl_api::BindImageTexture,
      void(
        uint_type,
        texture_name,
        int_type,
        true_false,
        int_type,
        access_specifier,
        image_unit_format)>
      bind_image_texture{*this};

    simple_adapted_function<
      &gl_api::TexStorage3D,
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type)>
      tex_storage3d{*this};

    simple_adapted_function<
      &gl_api::TextureStorage3D,
      void(
        texture_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type)>
      texture_storage3d{*this};

    simple_adapted_function<
      &gl_api::TexStorage2D,
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      tex_storage2d{*this};

    simple_adapted_function<
      &gl_api::TextureStorage2D,
      void(texture_name, sizei_type, pixel_internal_format, sizei_type, sizei_type)>
      texture_storage2d{*this};

    simple_adapted_function<
      &gl_api::TexStorage1D,
      void(texture_target, sizei_type, pixel_internal_format, sizei_type)>
      tex_storage1d{*this};

    simple_adapted_function<
      &gl_api::TextureStorage1D,
      void(texture_name, sizei_type, pixel_internal_format, sizei_type)>
      texture_storage1d{*this};

    simple_adapted_function<
      &gl_api::TexStorage3DMultisample,
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type,
        bool_type)>
      tex_storage3d_multisample{*this};

    simple_adapted_function<
      &gl_api::TextureStorage3DMultisample,
      void(
        texture_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type,
        bool_type)>
      texture_storage3d_multisample{*this};

    simple_adapted_function<
      &gl_api::TexStorage2DMultisample,
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        bool_type)>
      tex_storage2d_multisample{*this};

    simple_adapted_function<
      &gl_api::TextureStorage2DMultisample,
      void(
        texture_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        bool_type)>
      texture_storage2d_multisample{*this};

    simple_adapted_function<
      &gl_api::TexImage3D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type,
        int_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      tex_image3d{*this};

    simple_adapted_function<
      &gl_api::TexImage2D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        int_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      tex_image2d{*this};

    simple_adapted_function<
      &gl_api::TexImage1D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        sizei_type,
        int_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      tex_image1d{*this};

    simple_adapted_function<
      &gl_api::TexSubImage3D,
      void(
        texture_target,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      tex_sub_image3d{*this};

    simple_adapted_function<
      &gl_api::TextureSubImage3D,
      void(
        texture_name,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      texture_sub_image3d{*this};

    simple_adapted_function<
      &gl_api::TexSubImage2D,
      void(
        texture_target,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      tex_sub_image2d{*this};

    simple_adapted_function<
      &gl_api::TextureSubImage2D,
      void(
        texture_name,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      texture_sub_image2d{*this};

    simple_adapted_function<
      &gl_api::TexSubImage1D,
      void(
        texture_target,
        int_type,
        int_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      tex_sub_image1d{*this};

    simple_adapted_function<
      &gl_api::TextureSubImage1D,
      void(
        texture_name,
        int_type,
        int_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      texture_sub_image1d{*this};

    simple_adapted_function<
      &gl_api::CopyTexImage2D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        int_type)>
      copy_tex_image2d{*this};

    simple_adapted_function<
      &gl_api::CopyTexImage1D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        int_type,
        int_type,
        sizei_type,
        int_type)>
      copy_tex_image1d{*this};

    simple_adapted_function<
      &gl_api::CopyTexSubImage3D,
      void(
        texture_target,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type)>
      copy_tex_sub_image3d{*this};

    simple_adapted_function<
      &gl_api::CopyTexSubImage2D,
      void(
        texture_target,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type)>
      copy_tex_sub_image2d{*this};

    simple_adapted_function<
      &gl_api::CopyTextureSubImage2D,
      void(
        texture_name,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type)>
      copy_texture_sub_image2d{*this};

    simple_adapted_function<
      &gl_api::CopyTexSubImage1D,
      void(texture_target, int_type, int_type, int_type, int_type, sizei_type)>
      copy_tex_sub_image1d{*this};

    simple_adapted_function<
      &gl_api::CopyTextureSubImage1D,
      void(texture_name, int_type, int_type, int_type, int_type, sizei_type)>
      copy_texture_sub_image1d{*this};

    simple_adapted_function<
      &gl_api::CompressedTexImage3D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type,
        int_type,
        memory::const_block)>
      compressed_tex_image3d{*this};

    simple_adapted_function<
      &gl_api::CompressedTexImage2D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        int_type,
        memory::const_block)>
      compressed_tex_image2d{*this};

    simple_adapted_function<
      &gl_api::CompressedTexImage1D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        sizei_type,
        int_type,
        memory::const_block)>
      compressed_tex_image1d{*this};

    simple_adapted_function<
      &gl_api::CompressedTexSubImage3D,
      void(
        texture_target,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        pixel_format,
        memory::const_block)>
      compressed_tex_sub_image3d{*this};

    simple_adapted_function<
      &gl_api::CompressedTextureSubImage3D,
      void(
        texture_name,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        pixel_format,
        memory::const_block)>
      compressed_texture_sub_image3d{*this};

    simple_adapted_function<
      &gl_api::CompressedTexSubImage2D,
      void(
        texture_target,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        pixel_format,
        memory::const_block)>
      compressed_tex_sub_image2d{*this};

    simple_adapted_function<
      &gl_api::CompressedTextureSubImage2D,
      void(
        texture_name,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        pixel_format,
        memory::const_block)>
      compressed_texture_sub_image2d{*this};

    simple_adapted_function<
      &gl_api::CompressedTexSubImage1D,
      void(
        texture_target,
        int_type,
        int_type,
        sizei_type,
        pixel_format,
        memory::const_block)>
      compressed_tex_sub_image1d{*this};

    simple_adapted_function<
      &gl_api::CompressedTextureSubImage1D,
      void(
        texture_name,
        int_type,
        int_type,
        sizei_type,
        pixel_format,
        memory::const_block)>
      compressed_texture_sub_image1d{*this};

    simple_adapted_function<
      &gl_api::ClearTexSubImage,
      void(
        texture_name,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      clear_tex_sub_image{*this};

    simple_adapted_function<
      &gl_api::ClearTexImage,
      void(
        texture_name,
        int_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      clear_tex_image{*this};

    simple_adapted_function<
      &gl_api::TexBuffer,
      void(texture_target, pixel_internal_format, buffer_name)>
      tex_buffer{*this};

    simple_adapted_function<
      &gl_api::TextureBuffer,
      void(texture_name, pixel_internal_format, buffer_name)>
      texture_buffer{*this};

    simple_adapted_function<
      &gl_api::TexBufferRange,
      void(
        texture_target,
        pixel_internal_format,
        buffer_name,
        intptr_type,
        sizeiptr_type)>
      tex_buffer_range{*this};

    simple_adapted_function<
      &gl_api::TextureBufferRange,
      void(
        texture_name,
        pixel_internal_format,
        buffer_name,
        intptr_type,
        sizeiptr_type)>
      texture_buffer_range{*this};

    simple_adapted_function<
      &gl_api::TexParameterf,
      void(texture_target, texture_parameter, float_type)>
      tex_parameter_f{*this};

    simple_adapted_function<
      &gl_api::TextureParameterf,
      void(texture_name, texture_parameter, float_type)>
      texture_parameter_f{*this};

    using _tex_parameter_i_t = simple_adapted_function<
      &gl_api::TexParameteri,
      void(texture_target, enum_parameter_value<texture_parameter, int_type>)>;

    struct : _tex_parameter_i_t {
        using base = _tex_parameter_i_t;
        using base::base;
        template <typename Param, typename Value>
        constexpr auto operator()(texture_target tgt, Param param, Value value)
          const noexcept {
            return base::operator()(tgt, {param, value});
        }
    } tex_parameter_i{*this};

    using _texture_parameter_i_t = simple_adapted_function<
      &gl_api::TextureParameteri,
      void(texture_name, enum_parameter_value<texture_parameter, int_type>)>;

    struct : _texture_parameter_i_t {
        using base = _texture_parameter_i_t;
        using base::base;
        template <typename Param, typename Value>
        constexpr auto operator()(texture_name tex, Param param, Value value)
          const noexcept {
            return base::operator()(tex, {param, value});
        }
    } texture_parameter_i{*this};

    simple_adapted_function<
      &gl_api::TexParameterfv,
      void(texture_target, texture_parameter, span<const float_type>)>
      tex_parameter_fv{*this};

    simple_adapted_function<
      &gl_api::TextureParameterfv,
      void(texture_name, texture_parameter, span<const float_type>)>
      texture_parameter_fv{*this};

    simple_adapted_function<
      &gl_api::TexParameteriv,
      void(texture_target, texture_parameter, span<const int_type>)>
      tex_parameter_iv{*this};

    simple_adapted_function<
      &gl_api::TextureParameteriv,
      void(texture_name, texture_parameter, span<const int_type>)>
      texture_parameter_iv{*this};

    simple_adapted_function<
      &gl_api::TexParameterIiv,
      void(texture_target, texture_parameter, span<const int_type>)>
      tex_parameter_iiv{*this};

    simple_adapted_function<
      &gl_api::TextureParameterIiv,
      void(texture_name, texture_parameter, span<const int_type>)>
      texture_parameter_iiv{*this};

    simple_adapted_function<
      &gl_api::TexParameterIuiv,
      void(texture_target, texture_parameter, span<const uint_type>)>
      tex_parameter_iuiv{*this};

    simple_adapted_function<
      &gl_api::TextureParameterIuiv,
      void(texture_name, texture_parameter, span<const uint_type>)>
      texture_parameter_iuiv{*this};

    query_function<
      &gl_api::GetTexParameterfv,
      float_type,
      mp_list<texture_target>,
      mp_list<texture_parameter>>
      get_tex_parameter_f{*this};

    query_function<
      &gl_api::GetTextureParameterfv,
      float_type,
      mp_list<texture_name>,
      mp_list<texture_parameter>>
      get_texture_parameter_f{*this};

    query_function<
      &gl_api::GetTexParameteriv,
      int_type,
      mp_list<texture_target>,
      mp_list<texture_parameter>>
      get_tex_parameter_i{*this};

    query_function<
      &gl_api::GetTextureParameteriv,
      int_type,
      mp_list<texture_name>,
      mp_list<texture_parameter>>
      get_texture_parameter_i{*this};

    query_function<
      &gl_api::GetTexParameterIiv,
      int_type,
      mp_list<texture_target>,
      mp_list<texture_parameter>>
      get_tex_parameter_ii{*this};

    query_function<
      &gl_api::GetTextureParameterIiv,
      int_type,
      mp_list<texture_name>,
      mp_list<texture_parameter>>
      get_texture_parameter_ii{*this};

    query_function<
      &gl_api::GetTexParameterIuiv,
      uint_type,
      mp_list<texture_target>,
      mp_list<texture_parameter>>
      get_tex_parameter_iui{*this};

    query_function<
      &gl_api::GetTextureParameterIuiv,
      uint_type,
      mp_list<texture_name>,
      mp_list<texture_parameter>>
      get_texture_parameter_iui{*this};

    simple_adapted_function<&gl_api::GenerateMipmap, void(texture_target)>
      generate_mipmap{*this};
    simple_adapted_function<&gl_api::GenerateTextureMipmap, void(texture_name)>
      generate_texture_mipmap{*this};

    // sampler ops
    simple_adapted_function<&gl_api::BindSampler, void(uint_type, sampler_name)>
      bind_sampler{*this};

    simple_adapted_function<
      &gl_api::SamplerParameterf,
      void(sampler_name, sampler_parameter, float_type)>
      sampler_parameter_f{*this};

    simple_adapted_function<
      &gl_api::SamplerParameteri,
      void(sampler_name, sampler_parameter, int_type)>
      sampler_parameter_i{*this};

    simple_adapted_function<
      &gl_api::SamplerParameterfv,
      void(sampler_name, sampler_parameter, span<const float_type>)>
      sampler_parameter_fv{*this};

    simple_adapted_function<
      &gl_api::SamplerParameteriv,
      void(sampler_name, sampler_parameter, span<const int_type>)>
      sampler_parameter_iv{*this};

    simple_adapted_function<
      &gl_api::SamplerParameterIiv,
      void(sampler_name, sampler_parameter, span<const int_type>)>
      sampler_parameter_iiv{*this};

    simple_adapted_function<
      &gl_api::SamplerParameterIuiv,
      void(sampler_name, sampler_parameter, span<const uint_type>)>
      sampler_parameter_iuiv{*this};

    query_function<
      &gl_api::GetSamplerParameterfv,
      float_type,
      mp_list<sampler_name>,
      mp_list<sampler_parameter>>
      get_sampler_parameter_f{*this};

    query_function<
      &gl_api::GetSamplerParameteriv,
      int_type,
      mp_list<sampler_name>,
      mp_list<sampler_parameter>>
      get_sampler_parameter_i{*this};

    query_function<
      &gl_api::GetSamplerParameterIiv,
      int_type,
      mp_list<sampler_name>,
      mp_list<sampler_parameter>>
      get_sampler_parameter_ii{*this};

    query_function<
      &gl_api::GetSamplerParameterIuiv,
      uint_type,
      mp_list<sampler_name>,
      mp_list<sampler_parameter>>
      get_sampler_parameter_iui{*this};

    // renderbuffer ops
    simple_adapted_function<
      &gl_api::BindRenderbuffer,
      void(renderbuffer_target, renderbuffer_name)>
      bind_renderbuffer{*this};

    simple_adapted_function<
      &gl_api::RenderbufferStorage,
      void(renderbuffer_target, pixel_internal_format, sizei_type, sizei_type)>
      renderbuffer_storage{*this};

    simple_adapted_function<
      &gl_api::NamedRenderbufferStorage,
      void(renderbuffer_name, pixel_internal_format, sizei_type, sizei_type)>
      named_renderbuffer_storage{*this};

    simple_adapted_function<
      &gl_api::RenderbufferStorageMultisample,
      void(
        renderbuffer_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      renderbuffer_storage_multisample{*this};

    simple_adapted_function<
      &gl_api::NamedRenderbufferStorageMultisample,
      void(
        renderbuffer_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      named_renderbuffer_storage_multisample{*this};

    query_function<
      &gl_api::GetRenderbufferParameteriv,
      int_type,
      mp_list<renderbuffer_target>,
      mp_list<renderbuffer_parameter>>
      get_renderbuffer_parameter_i{*this};

    query_function<
      &gl_api::GetNamedRenderbufferParameteriv,
      int_type,
      mp_list<renderbuffer_name>,
      mp_list<renderbuffer_parameter>>
      get_named_renderbuffer_parameter_i{*this};

    // framebuffer ops
    simple_adapted_function<
      &gl_api::BindFramebuffer,
      void(framebuffer_target, framebuffer_name)>
      bind_framebuffer{*this};

    simple_adapted_function<&gl_api::DrawBuffer, void(surface_buffer)>
      draw_buffer{*this};

    simple_adapted_function<
      &gl_api::NamedFramebufferDrawBuffer,
      void(framebuffer_name, surface_buffer)>
      named_framebuffer_draw_buffer{*this};

    simple_adapted_function<&gl_api::ReadBuffer, void(surface_buffer)>
      read_buffer{*this};

    simple_adapted_function<
      &gl_api::NamedFramebufferReadBuffer,
      void(framebuffer_name, surface_buffer)>
      named_framebuffer_read_buffer{*this};

    simple_adapted_function<
      &gl_api::FramebufferParameteri,
      void(framebuffer_target, framebuffer_parameter, int_type)>
      framebuffer_parameter_i{*this};

    simple_adapted_function<
      &gl_api::NamedFramebufferParameteri,
      void(framebuffer_name, framebuffer_parameter, int_type)>
      named_framebuffer_parameter_i{*this};

    query_function<
      &gl_api::GetFramebufferParameteriv,
      int_type,
      mp_list<framebuffer_target>,
      mp_list<framebuffer_parameter>>
      get_framebuffer_parameter_i{*this};

    query_function<
      &gl_api::GetNamedFramebufferParameteriv,
      int_type,
      mp_list<framebuffer_name>,
      mp_list<framebuffer_parameter>>
      get_named_framebuffer_parameter_i{*this};

    query_function<
      &gl_api::GetFramebufferAttachmentParameteriv,
      int_type,
      mp_list<framebuffer_target, framebuffer_attachment>,
      mp_list<framebuffer_attachment_parameter>>
      get_framebuffer_attachment_parameter_i{*this};

    query_function<
      &gl_api::GetNamedFramebufferAttachmentParameteriv,
      int_type,
      mp_list<framebuffer_name, framebuffer_attachment>,
      mp_list<framebuffer_attachment_parameter>>
      get_named_framebuffer_attachment_parameter_i{*this};

    simple_adapted_function<
      &gl_api::FramebufferRenderbuffer,
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        renderbuffer_target,
        renderbuffer_name)>
      framebuffer_renderbuffer{*this};

    simple_adapted_function<
      &gl_api::NamedFramebufferRenderbuffer,
      void(
        framebuffer_name,
        oglplus::framebuffer_attachment,
        renderbuffer_target,
        renderbuffer_name)>
      named_framebuffer_renderbuffer{*this};

    simple_adapted_function<
      &gl_api::FramebufferTexture,
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type)>
      framebuffer_texture{*this};

    simple_adapted_function<
      &gl_api::NamedFramebufferTexture,
      void(
        framebuffer_name,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type)>
      named_framebuffer_texture{*this};

    simple_adapted_function<
      &gl_api::FramebufferTexture1D,
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type)>
      framebuffer_texture1d{*this};

    simple_adapted_function<
      &gl_api::FramebufferTexture2D,
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        oglplus::texture_target,
        texture_name,
        int_type)>
      framebuffer_texture2d{*this};

    simple_adapted_function<
      &gl_api::FramebufferTexture3D,
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        oglplus::texture_target,
        texture_name,
        int_type)>
      framebuffer_texture3d{*this};

    simple_adapted_function<
      &gl_api::FramebufferTextureLayer,
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type,
        int_type)>
      framebuffer_texture_layer{*this};

    simple_adapted_function<
      &gl_api::NamedFramebufferTextureLayer,
      void(
        framebuffer_name,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type,
        int_type)>
      named_framebuffer_texture_layer{*this};

    simple_adapted_function<
      &gl_api::CheckFramebufferStatus,
      framebuffer_status(framebuffer_target)>
      check_framebuffer_status{*this};

    simple_adapted_function<
      &gl_api::CheckNamedFramebufferStatus,
      framebuffer_status(framebuffer_name, framebuffer_target)>
      check_named_framebuffer_status{*this};

    simple_adapted_function<
      &gl_api::BlitFramebuffer,
      void(
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        c_api::enum_bitfield<buffer_blit_bit>,
        blit_filter)>
      blit_framebuffer{*this};

    simple_adapted_function<
      &gl_api::BlitNamedFramebuffer,
      void(
        framebuffer_name,
        framebuffer_name,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        c_api::enum_bitfield<buffer_blit_bit>,
        blit_filter)>
      blit_named_framebuffer{*this};

    // transform feedback ops
    simple_adapted_function<
      &gl_api::BindTransformFeedback,
      void(transform_feedback_target, transform_feedback_name)>
      bind_transform_feedback{*this};

    simple_adapted_function<
      &gl_api::BeginTransformFeedback,
      void(transform_feedback_primitive_type)>
      begin_transform_feedback{*this};

    plain_adapted_function<&gl_api::PauseTransformFeedback>
      pause_transform_feedback{*this};

    plain_adapted_function<&gl_api::ResumeTransformFeedback>
      resume_transform_feedback{*this};

    plain_adapted_function<&gl_api::EndTransformFeedback> end_transform_feedback{
      *this};

    simple_adapted_function<
      &gl_api::TransformFeedbackBufferBase,
      void(transform_feedback_name, uint_type, buffer_name)>
      transform_feedback_buffer_base{*this};

    simple_adapted_function<
      &gl_api::TransformFeedbackBufferRange,
      void(
        transform_feedback_name,
        uint_type,
        buffer_name,
        intptr_type,
        sizeiptr_type)>
      transform_feedback_buffer_range{*this};

    query_function<
      &gl_api::GetTransformFeedbackiv,
      int_type,
      mp_list<transform_feedback_name>,
      mp_list<transform_feedback_parameter>>
      get_transform_feedback_i{*this};

    query_function<
      &gl_api::GetTransformFeedbacki_v,
      int_type,
      mp_list<transform_feedback_name>,
      mp_list<transform_feedback_parameter>,
      mp_list<uint_type>>
      get_transform_feedback_ii{*this};

    query_function<
      &gl_api::GetTransformFeedbacki64_v,
      int64_type,
      mp_list<transform_feedback_name>,
      mp_list<transform_feedback_parameter>,
      mp_list<uint_type>>
      get_transform_feedback_i64i{*this};

    // query ops
    query_function<
      &gl_api::GetQueryiv,
      int_type,
      mp_list<query_target>,
      mp_list<query_parameter>>
      get_query_i{*this};

    query_function<
      &gl_api::GetQueryIndexediv,
      int_type,
      mp_list<query_target, uint_type>,
      mp_list<query_parameter>>
      get_query_indexed_i{*this};

    query_function<
      &gl_api::GetQueryObjectiv,
      int_type,
      mp_list<query_name>,
      mp_list<query_parameter>>
      get_query_object_i{*this};

    query_function<
      &gl_api::GetQueryObjectuiv,
      uint_type,
      mp_list<query_name>,
      mp_list<query_parameter>>
      get_query_object_ui{*this};

    query_function<
      &gl_api::GetQueryObjecti64v,
      int64_type,
      mp_list<query_name>,
      mp_list<query_parameter>>
      get_query_object_i64{*this};

    query_function<
      &gl_api::GetQueryObjectui64v,
      uint64_type,
      mp_list<query_name>,
      mp_list<query_parameter>>
      get_query_object_ui64{*this};

    simple_adapted_function<
      &gl_api::GetQueryBufferObjectiv,
      void(query_name, buffer_name, query_parameter, intptr_type)>
      get_query_buffer_object_i{*this};

    simple_adapted_function<
      &gl_api::GetQueryBufferObjectuiv,
      void(query_name, buffer_name, query_parameter, intptr_type)>
      get_query_buffer_object_ui{*this};

    simple_adapted_function<
      &gl_api::GetQueryBufferObjecti64v,
      void(query_name, buffer_name, query_parameter, intptr_type)>
      get_query_buffer_object_i64{*this};

    simple_adapted_function<
      &gl_api::GetQueryBufferObjectui64v,
      void(query_name, buffer_name, query_parameter, intptr_type)>
      get_query_buffer_object_ui64{*this};

    simple_adapted_function<&gl_api::BeginQuery, void(query_target, query_name)>
      begin_query{*this};

    simple_adapted_function<
      &gl_api::BeginQueryIndexed,
      void(query_target, uint_type, query_name)>
      begin_query_indexed{*this};

    simple_adapted_function<&gl_api::EndQuery, void(query_target)> end_query{
      *this};

    simple_adapted_function<
      &gl_api::EndQueryIndexed,
      void(query_target, uint_type)>
      end_query_indexed{*this};

    simple_adapted_function<
      &gl_api::QueryCounter,
      void(query_name, counter_query_target)>
      query_counter{*this};

    simple_adapted_function<
      &gl_api::BeginConditionalRender,
      void(query_name, conditional_render_mode)>
      begin_conditional_render{*this};

    plain_adapted_function<&gl_api::EndConditionalRender> end_conditional_render{
      *this};

    // program pipeline ops
    simple_adapted_function<
      &gl_api::BindProgramPipeline,
      void(program_pipeline_name)>
      bind_program_pipeline{*this};

    simple_adapted_function<
      &gl_api::ValidateProgramPipeline,
      void(program_pipeline_name)>
      validate_program_pipeline{*this};

    simple_adapted_function<
      &gl_api::UseProgramStages,
      void(
        program_pipeline_name,
        c_api::enum_bitfield<program_stage_bit>,
        program_name)>
      use_program_stages{*this};

    query_function<
      &gl_api::GetProgramStageiv,
      int_type,
      mp_list<program_name, shader_type>,
      mp_list<program_stage_parameter>>
      get_program_stage_i{*this};

    query_function<
      &gl_api::GetProgramPipelineiv,
      int_type,
      mp_list<program_name>,
      mp_list<program_pipeline_parameter>>
      get_program_pipeline_i{*this};

    adapted_function<
      &gl_api::GetProgramPipelineInfoLog,
      void(program_pipeline_name, span<char_type>),
      c_api::combined_map<
        c_api::head_transform_map<sizei_type, 3, 2>,
        c_api::convert<name_type, c_api::trivial_arg_map<1>>,
        c_api::convert<sizei_type, c_api::get_size_map<2, 2>>,
        c_api::get_data_map<4, 2>>>
      get_program_pipeline_info_log{*this};

    simple_adapted_function<
      &gl_api::ActiveShaderProgram,
      void(program_pipeline_name, program_name)>
      active_shader_program{*this};

    // path NV ops
    simple_adapted_function<
      &gl_api::PathColorGenNV,
      void(
        path_color_nv,
        path_gen_mode_nv,
        path_color_format_nv,
        span<const float_type>)>
      path_color_gen_nv{*this};

    adapted_function<
      &gl_api::PathGlyphRangeNV,
      void(
        path_nv_name,
        path_font_target_nv,
        string_view,
        path_font_style_nv,
        uint_type,
        sizei_type,
        path_missing_glyph_nv,
        uint_type,
        float_type),
      c_api::combined_map<
        c_api::make_arg_map<1, 1, name_type, path_nv_name>,
        c_api::make_arg_map<2, 2, enum_type, path_font_target_nv>,
        c_api::make_arg_map<3, 3, const char*, string_view>,
        c_api::make_arg_map<4, 4, bitfield_type, path_font_style_nv>,
        c_api::make_arg_map<7, 7, enum_type, path_missing_glyph_nv>,
        c_api::trivial_arg_map<0, 5, 6, 8, 9>>>
      path_glyph_range_nv{*this};

    simple_adapted_function<
      &gl_api::GetPathSpacingNV,
      void(
        path_list_mode_nv,
        string_view,
        c_api::substituted<GL_UTF8_NV>,
        path_nv_name,
        float_type,
        float_type,
        path_transform_type_nv,
        span<float_type>)>
      get_path_spacing_nv{*this};

    simple_adapted_function<
      &gl_api::StencilFillPathNV,
      void(path_nv_name, path_fill_mode_nv, uint_type)>
      stencil_fill_path_nv{*this};

    simple_adapted_function<
      &gl_api::StencilStrokePathNV,
      void(path_nv_name, int_type, uint_type)>
      stencil_stroke_path_nv{*this};

    simple_adapted_function<
      &gl_api::StencilFillPathInstancedNV,
      void(
        string_view,
        c_api::substituted<GL_UTF8_NV>,
        path_nv_name,
        path_fill_mode_nv,
        uint_type,
        path_transform_type_nv,
        span<const float_type>)>
      stencil_fill_path_instanced_nv{*this};

    simple_adapted_function<
      &gl_api::StencilStrokePathInstancedNV,
      void(
        string_view,
        c_api::substituted<GL_UTF8_NV>,
        path_nv_name,
        path_fill_mode_nv,
        int_type,
        uint_type,
        path_transform_type_nv,
        span<const float_type>)>
      stencil_stroke_path_instanced_nv{*this};

    simple_adapted_function<
      &gl_api::CoverFillPathNV,
      void(path_nv_name, path_fill_cover_mode_nv)>
      cover_fill_path_nv{*this};

    simple_adapted_function<
      &gl_api::CoverStrokePathNV,
      void(path_nv_name, path_stroke_cover_mode_nv)>
      cover_stroke_path_nv{*this};

    simple_adapted_function<
      &gl_api::CoverFillPathInstancedNV,
      void(
        string_view,
        c_api::substituted<GL_UTF8_NV>,
        path_nv_name,
        path_fill_cover_mode_nv,
        path_transform_type_nv,
        span<const float_type>)>
      cover_fill_path_instanced_nv{*this};

    simple_adapted_function<
      &gl_api::CoverStrokePathInstancedNV,
      void(
        string_view,
        c_api::substituted<GL_UTF8_NV>,
        path_nv_name,
        path_stroke_cover_mode_nv,
        path_transform_type_nv,
        span<const float_type>)>
      cover_stroke_path_instanced_nv{*this};

    // draw parameters
    plain_adapted_function<&gl_api::PrimitiveRestartIndex>
      primitive_restart_index{*this};

    simple_adapted_function<&gl_api::ProvokingVertex, void(provoke_mode)>
      provoking_vertex{*this};

    plain_adapted_function<&gl_api::PointSize> point_size{*this};
    plain_adapted_function<&gl_api::LineWidth> line_width{*this};

    simple_adapted_function<
      &gl_api::PointParameteri,
      void(point_parameter, int_type)>
      point_parameter_i{*this};

    simple_adapted_function<
      &gl_api::PointParameterf,
      void(point_parameter, float_type)>
      point_parameter_f{*this};

    simple_adapted_function<
      &gl_api::PatchParameteri,
      void(patch_parameter, int_type)>
      patch_parameter_i{*this};

    simple_adapted_function<
      &gl_api::PatchParameterfv,
      void(patch_parameter, span<const float_type>)>
      patch_parameter_fv{*this};

    simple_adapted_function<&gl_api::FrontFace, void(face_orientation)>
      front_face{*this};
    simple_adapted_function<&gl_api::CullFace, void(face_mode)> cull_face{
      *this};

    simple_adapted_function<
      &gl_api::PolygonMode,
      void(face_mode, oglplus::polygon_mode)>
      polygon_mode{*this};

    plain_adapted_function<&gl_api::PolygonOffset> polygon_offset{*this};
    plain_adapted_function<&gl_api::PolygonOffsetClamp> polygon_offset_clamp{
      *this};

    simple_adapted_function<&gl_api::BlendEquation, void(oglplus::blend_equation)>
      blend_equation{*this};

    simple_adapted_function<
      &gl_api::BlendEquationSeparate,
      void(oglplus::blend_equation, oglplus::blend_equation)>
      blend_equation_separate{*this};

    simple_adapted_function<
      &gl_api::BlendEquationi,
      void(uint_type, oglplus::blend_equation)>
      blend_equationi{*this};

    simple_adapted_function<
      &gl_api::BlendEquationSeparatei,
      void(uint_type, oglplus::blend_equation, oglplus::blend_equation)>
      blend_equation_separatei{*this};

    simple_adapted_function<
      &gl_api::BlendFunc,
      void(oglplus::blend_function, oglplus::blend_function)>
      blend_func{*this};

    simple_adapted_function<
      &gl_api::BlendFuncSeparate,
      void(
        oglplus::blend_function,
        oglplus::blend_function,
        oglplus::blend_function,
        oglplus::blend_function)>
      blend_func_separate{*this};

    simple_adapted_function<
      &gl_api::BlendFunci,
      void(uint_type, oglplus::blend_function, oglplus::blend_function)>
      blend_funci{*this};

    simple_adapted_function<
      &gl_api::BlendFuncSeparatei,
      void(
        uint_type,
        oglplus::blend_function,
        oglplus::blend_function,
        oglplus::blend_function,
        oglplus::blend_function)>
      blend_func_separatei{*this};

    plain_adapted_function<&gl_api::SampleCoverage> sample_coverage{*this};
    plain_adapted_function<&gl_api::SampleMaski> sample_mask_i{*this};
    plain_adapted_function<&gl_api::MinSampleShading> min_sample_shading{*this};

    query_function<
      &gl_api::GetMultisamplefv,
      float_type,
      mp_list<>,
      mp_list<sample_parameter>,
      mp_list<uint_type>>
      get_multisample_f{*this};

    // drawing
    // arrays
    simple_adapted_function<
      &gl_api::DrawArrays,
      void(primitive_type, int_type, sizei_type)>
      draw_arrays{*this};

    simple_adapted_function<
      &gl_api::DrawArraysInstancedBaseInstance,
      void(primitive_type, int_type, sizei_type, sizei_type, uint_type)>
      draw_arrays_instanced_base_instance{*this};

    simple_adapted_function<
      &gl_api::DrawArraysInstanced,
      void(primitive_type, int_type, sizei_type, sizei_type)>
      draw_arrays_instanced{*this};

    simple_adapted_function<
      &gl_api::DrawArraysIndirect,
      void(primitive_type, const_void_ptr_type)>
      draw_arrays_indirect{*this};

    simple_adapted_function<
      &gl_api::MultiDrawArrays,
      void(primitive_type, const int_type*, const sizei_type*, sizei_type)>
      multi_draw_arrays{*this};

    simple_adapted_function<
      &gl_api::MultiDrawArraysIndirect,
      void(primitive_type, const_void_ptr_type, sizei_type, sizei_type)>
      multi_draw_arrays_indirect{*this};

    simple_adapted_function<
      &gl_api::MultiDrawArraysIndirectCount,
      void(primitive_type, const_void_ptr_type, intptr_type, sizei_type, sizei_type)>
      multi_draw_arrays_indirect_count{*this};

    // elements
    simple_adapted_function<
      &gl_api::DrawElements,
      void(primitive_type, sizei_type, index_data_type, const_void_ptr_type)>
      draw_elements{*this};

    simple_adapted_function<
      &gl_api::DrawRangeElements,
      void(
        primitive_type,
        uint_type,
        uint_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type)>
      draw_range_elements{*this};

    simple_adapted_function<
      &gl_api::DrawElementsInstancedBaseInstance,
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        sizei_type,
        uint_type)>
      draw_elements_instanced_base_instance{*this};

    simple_adapted_function<
      &gl_api::DrawElementsInstanced,
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        sizei_type)>
      draw_elements_instanced{*this};

    simple_adapted_function<
      &gl_api::DrawElementsIndirect,
      void(primitive_type, index_data_type, const_void_ptr_type)>
      draw_elements_indirect{*this};

    simple_adapted_function<
      &gl_api::DrawElementsBaseVertex,
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        int_type)>
      draw_elements_base_vertex{*this};

    simple_adapted_function<
      &gl_api::DrawRangeElements,
      void(
        primitive_type,
        uint_type,
        uint_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        int_type)>
      draw_range_elements_base_vertex{*this};

    simple_adapted_function<
      &gl_api::DrawElementsInstancedBaseVertex,
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        sizei_type,
        int_type)>
      draw_elements_instanced_base_vertex{*this};

    simple_adapted_function<
      &gl_api::DrawElementsInstancedBaseVertexBaseInstance,
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        sizei_type,
        int_type,
        uint_type)>
      draw_elements_instanced_base_vertex_base_instance{*this};

    // computing
    plain_adapted_function<&gl_api::DispatchCompute> dispatch_compute{*this};
    plain_adapted_function<&gl_api::DispatchComputeIndirect>
      dispatch_compute_indirect{*this};

    // pixel transfer
    simple_adapted_function<
      &gl_api::ReadPixels,
      void(
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::block)>
      read_pixels{*this};

    // get_integer
    query_function<
      &gl_api::GetIntegerv,
      int_type,
      mp_list<>,
      mp_list<integer_query, binding_query>>
      get_integer{*this};

    // get_integer64
    query_function<
      &gl_api::GetInteger64v,
      int64_type,
      mp_list<>,
      mp_list<integer_query>>
      get_integer64{*this};

    // get_float
    query_function<&gl_api::GetFloatv, float_type, mp_list<>, mp_list<float_query>>
      get_float{*this};

    // get_double
    query_function<
      &gl_api::GetDoublev,
      double_type,
      mp_list<>,
      mp_list<float_query>>
      get_double{*this};

    simple_adapted_function<&gl_api::GetString, string_view(string_query)>
      get_string{*this};

    auto get_vendor() const noexcept {
#ifdef GL_VENDOR
        return get_string(string_query(GL_VENDOR));
#else
        return get_string(string_query(0x1F00));
#endif
    }

    auto get_renderer() const noexcept {
#ifdef GL_RENDERER
        return get_string(string_query(GL_RENDERER));
#else
        return get_string(string_query(0x1F01));
#endif
    }

    auto get_version() const noexcept {
#ifdef GL_VERSION
        return get_string(string_query(GL_VERSION));
#else
        return get_string(string_query(0x1F02));
#endif
    }

    // get_strings
    auto get_strings(string_query query, char separator) const noexcept {
        return get_string(query).transform([separator](auto src) {
            return split_into_string_list(src, separator);
        });
    }

    // get_extensions
    auto get_extensions() const noexcept {
#ifdef GL_EXTENSIONS
        return get_string(string_query(GL_EXTENSIONS))
#else
        return get_string(string_query(0x1F03))
#endif
          .transform([](auto src) { return split_into_string_list(src, ' '); });
    }

    // has_extension
    auto has_extension(string_view which) const noexcept {
        if(ok extensions{get_extensions()}) {
            for(auto ext_name : extensions) {
                if(ends_with(ext_name, which)) {
                    return true;
                }
            }
        }
        return false;
    }

    // named strings
    simple_adapted_function<
      &gl_api::NamedString,
      void(named_string_kind, string_view, string_view)>
      named_string{*this};

    simple_adapted_function<&gl_api::DeleteNamedString, void(string_view)>
      delete_named_string{*this};

    simple_adapted_function<&gl_api::IsNamedString, true_false(string_view)>
      is_named_string{*this};

    // arb compatibility
    simple_adapted_function<&gl_api::Begin, void(old_primitive_type)> begin{
      *this};
    plain_adapted_function<&gl_api::End> end{*this};

    plain_adapted_function<&gl_api::Vertex2i> vertex2i{*this};
    plain_adapted_function<&gl_api::Vertex3i> vertex3i{*this};
    plain_adapted_function<&gl_api::Vertex4i> vertex4i{*this};
    plain_adapted_function<&gl_api::Vertex2f> vertex2f{*this};
    plain_adapted_function<&gl_api::Vertex3f> vertex3f{*this};
    plain_adapted_function<&gl_api::Vertex4f> vertex4f{*this};

    plain_adapted_function<&gl_api::Color3i> color3i{*this};
    plain_adapted_function<&gl_api::Color4i> color4i{*this};
    plain_adapted_function<&gl_api::Color3f> color3f{*this};
    plain_adapted_function<&gl_api::Color4f> color4f{*this};

    plain_adapted_function<&gl_api::SecondaryColor3i> secondary_color3i{*this};
    plain_adapted_function<&gl_api::SecondaryColor4i> csecondary_olor4i{*this};
    plain_adapted_function<&gl_api::SecondaryColor3f> csecondary_olor3f{*this};
    plain_adapted_function<&gl_api::SecondaryColor4f> csecondary_olor4f{*this};

    plain_adapted_function<&gl_api::TexCoord1i> tex_coord1i{*this};
    plain_adapted_function<&gl_api::TexCoord2i> tex_coord2i{*this};
    plain_adapted_function<&gl_api::TexCoord3i> tex_coord3i{*this};
    plain_adapted_function<&gl_api::TexCoord4i> tex_coord4i{*this};
    plain_adapted_function<&gl_api::TexCoord1f> tex_coord1f{*this};
    plain_adapted_function<&gl_api::TexCoord2f> tex_coord2f{*this};
    plain_adapted_function<&gl_api::TexCoord3f> tex_coord3f{*this};
    plain_adapted_function<&gl_api::TexCoord4f> tex_coord4f{*this};

    simple_adapted_function<
      &gl_api::MultiTexCoord1i,
      void(texture_unit, int_type)>
      multi_tex_coord1i{*this};
    simple_adapted_function<
      &gl_api::MultiTexCoord2i,
      void(texture_unit, int_type, int_type)>
      multi_tex_coord2i{*this};
    simple_adapted_function<
      &gl_api::MultiTexCoord3i,
      void(texture_unit, int_type, int_type, int_type)>
      multi_tex_coord3i{*this};
    simple_adapted_function<
      &gl_api::MultiTexCoord4i,
      void(texture_unit, int_type, int_type, int_type, int_type)>
      multi_tex_coord4i{*this};

    simple_adapted_function<
      &gl_api::MultiTexCoord1f,
      void(texture_unit, float_type)>
      multi_tex_coord1f{*this};
    simple_adapted_function<
      &gl_api::MultiTexCoord2f,
      void(texture_unit, float_type, float_type)>
      multi_tex_coord2f{*this};
    simple_adapted_function<
      &gl_api::MultiTexCoord3f,
      void(texture_unit, float_type, float_type, float_type)>
      multi_tex_coord3f{*this};
    simple_adapted_function<
      &gl_api::MultiTexCoord4f,
      void(texture_unit, float_type, float_type, float_type, float_type)>
      multi_tex_coord4f{*this};

    simple_adapted_function<&gl_api::MatrixMode, void(matrix_mode)> matrix_mode{
      *this};
    plain_adapted_function<&gl_api::PushMatrix> push_matrix{*this};
    plain_adapted_function<&gl_api::PopMatrix> pop_matrix{*this};

    plain_adapted_function<&gl_api::LoadIdentity> load_identity{*this};

    plain_adapted_function<&gl_api::Translatef> translate_f{*this};
    plain_adapted_function<&gl_api::Translated> translate_d{*this};

    simple_adapted_function<
      &gl_api::Rotatef,
      void(degrees_t<float_type>, float_type, float_type, float_type)>
      rotate_f{*this};

    simple_adapted_function<
      &gl_api::Rotated,
      void(degrees_t<double_type>, double_type, double_type, double_type)>
      rotate_d{*this};

    plain_adapted_function<&gl_api::Scalef> scale_f{*this};
    plain_adapted_function<&gl_api::Scaled> scale_d{*this};

    plain_adapted_function<&gl_api::Frustum> frustum{*this};
    plain_adapted_function<&gl_api::Ortho> ortho{*this};

    plain_adapted_function<&gl_api::LoadMatrixf> load_matrix_f{*this};
    plain_adapted_function<&gl_api::LoadMatrixd> load_matrix_d{*this};

    plain_adapted_function<&gl_api::MultMatrixf> mult_matrix_f{*this};
    plain_adapted_function<&gl_api::MultMatrixd> mult_matrix_d{*this};

    plain_adapted_function<&gl_api::LoadTransposeMatrixf>
      load_transpose_matrix_f{*this};
    plain_adapted_function<&gl_api::LoadTransposeMatrixd>
      load_transpose_matrix_d{*this};

    plain_adapted_function<&gl_api::MultTransposeMatrixf>
      mult_transpose_matrix_f{*this};
    plain_adapted_function<&gl_api::MultTransposeMatrixd>
      mult_transpose_matrix_d{*this};

    c_api::combined<
      simple_adapted_function<
        &gl_api::DebugMessageControl,
        void(
          debug_output_source,
          debug_output_type,
          debug_output_severity,
          c_api::defaulted,
          c_api::defaulted,
          true_false)>,
      simple_adapted_function<
        &gl_api::DebugMessageControl,
        void(
          debug_output_source,
          debug_output_type,
          debug_output_severity,
          span<const uint_type>,
          true_false)>>
      debug_message_control{*this};

    simple_adapted_function<
      &gl_api::DebugMessageInsert,
      void(
        debug_output_source,
        debug_output_type,
        debug_output_severity,
        uint_type,
        string_view)>
      debug_message_insert{*this};

    using _debug_message_callback_t = simple_adapted_function<
      &gl_api::DebugMessageCallback,
      void(debug_callback_type*, const_void_ptr_type)>;

    struct : _debug_message_callback_t {
        using base = _debug_message_callback_t;
        using base::base;
        using base::operator();

        template <typename Log>
            requires(std::is_same_v<Log, gl_debug_logger>)
        constexpr auto operator()(const Log& log) const noexcept {
            return base::operator()(log.callback(), log.data());
        }
    } debug_message_callback{*this};

    simple_adapted_function<
      &gl_api::PushDebugGroup,
      void(debug_output_source, uint_type, string_view)>
      push_debug_group{*this};

    plain_adapted_function<&gl_api::PopDebugGroup> pop_debug_group{*this};

    using _object_label_t = simple_adapted_function<
      &gl_api::ObjectLabel,
      void(object_type, name_type, string_view)>;

    struct : _object_label_t {
        using base = _object_label_t;
        using base::base;
        template <typename ObjTag>
        constexpr auto operator()(
          gl_object_name<ObjTag> name,
          string_view label) const noexcept {
            return base::operator()(type_of(name), name_type{name}, label);
        }
    } object_label{*this};

    plain_adapted_function<&gl_api::Flush> flush{*this};
    plain_adapted_function<&gl_api::Finish> finish{*this};

    basic_gl_operations(api_traits& traits);
};
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_gl_operations<ApiTraits>::basic_gl_operations(api_traits& traits)
  : gl_api{traits}
  , ARB_debug_output{"ARB_debug_output", *this}
  , ARB_compatibility{"ARB_compatibility", *this}
  , ARB_robustness{"ARB_robustness", *this}
  , ARB_shading_language_include{"ARB_shading_language_include", *this} {}
//------------------------------------------------------------------------------
/// @brief Combined wrapper for the GL API operations and constants.
/// @ingroup gl_api_wrap
/// @see gl_api_traits
/// @see gl_api
export template <typename ApiTraits>
class basic_gl_api
  : protected ApiTraits
  , public basic_gl_operations<ApiTraits>
  , public basic_gl_constants<ApiTraits> {

public:
    template <typename R>
    using combined_result = typename ApiTraits::template combined_result<R>;

    using int_type = typename gl_types::int_type;
    using float_type = typename gl_types::float_type;

    /// @brief Constructor using API traits..
    basic_gl_api(ApiTraits traits)
      : ApiTraits{std::move(traits)}
      , basic_gl_operations<ApiTraits>{*static_cast<ApiTraits*>(this)}
      , basic_gl_constants<ApiTraits> {
        *static_cast<ApiTraits*>(this),
          *static_cast<basic_gl_operations<ApiTraits>*>(this)
    }
    {}

    /// @brief Default constructor.
    basic_gl_api()
      : basic_gl_api{ApiTraits{}} {}

    /// @brief Returns a reference to the wrapped operations.
    auto operations() const noexcept -> const basic_gl_operations<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped operations.
    auto operator()() const noexcept -> const basic_gl_operations<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped constants.
    auto constants() const noexcept -> const basic_gl_constants<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped constants.
    auto operator~() const noexcept -> const basic_gl_constants<ApiTraits>& {
        return *this;
    }

    // convenience functions
    constexpr auto true_or_false(const bool b) const noexcept -> true_false {
        return b ? true_false(this->true_) : true_false(this->false_);
    }

    /// @brief Compiles and attaches a shader to the specified program.
    /// @see build_program
    auto add_shader(
      const program_name prog,
      shader_type shdr_type,
      const glsl_source_ref& shdr_src) const -> combined_result<void> {
        owned_shader_name shdr;
        this->create_shader(shdr_type) >> shdr;
        auto cleanup = this->delete_shader.raii(shdr);
        this->shader_source(shdr, shdr_src);
        this->compile_shader(shdr);
        return this->attach_shader(prog, shdr);
    }

    /// @brief Compiles and attaches a shader to the specified program.
    /// @see build_program
    auto add_shader(
      const program_name prog,
      shader_type shdr_type,
      const glsl_source_ref& shdr_src,
      const string_view label) const -> combined_result<void> {
        owned_shader_name shdr;
        this->create_shader(shdr_type) >> shdr;
        auto cleanup = this->delete_shader.raii(shdr);
        this->object_label(shdr, label);
        this->shader_source(shdr, shdr_src);
        this->compile_shader(shdr);
        return this->attach_shader(prog, shdr);
    }

    auto shader_info_log(const shader_name prog) const
      -> optionally_valid<std::string> {
        if(const auto len{this->get_shader_i(prog, this->info_log_length)}) {
            string_buffer logstr{*len + 1};
            if(const auto s{this->get_shader_info_log(prog, cover(logstr))}) {
                return {to_string(*s), true};
            }
        }
        return {};
    }

    auto program_info_log(const program_name prog) const
      -> optionally_valid<std::string> {
        if(const auto len{this->get_program_i(prog, this->info_log_length)}) {
            string_buffer logstr{*len + 1};
            if(const auto s{this->get_program_info_log(prog, cover(logstr))}) {
                return {to_string(*s), true};
            }
        }
        return {};
    }

private:
    // set_uniform
    template <typename ProgramUniformFunc, typename UniformFunc, typename T>
    auto _set_uniform(
      ProgramUniformFunc& program_uniform_func,
      UniformFunc& uniform_func,
      const program_name prog,
      const uniform_location loc,
      T&& value) const -> combined_result<void> {
        if(program_uniform_func) {
            return program_uniform_func(prog, loc, std::forward<T>(value));
        } else {
            if(auto use_res{this->use_program(prog)}) {
                return uniform_func(loc, std::forward<T>(value));
            } else {
                return use_res;
            }
        }
    }

    template <typename ProgramUniformFunc, typename UniformFunc, typename T>
    auto _set_uniform_matrix(
      ProgramUniformFunc& program_uniform_func,
      UniformFunc& uniform_func,
      const program_name prog,
      const uniform_location loc,
      T&& value,
      true_false transpose) const -> combined_result<void> {
        if(program_uniform_func) {
            return program_uniform_func(
              prog, loc, transpose, std::forward<T>(value));
        } else {
            if(auto use_res{this->use_program(prog)}) {
                return uniform_func(loc, transpose, std::forward<T>(value));
            } else {
                return use_res;
            }
        }
    }

public:
    // int
    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const int_type value) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1i, this->uniform1i, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const texture_unit tex_unit) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1i,
          this->uniform1i,
          prog,
          loc,
          int_type(tex_unit.value() - constants().texture0.value()));
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const int_type> value,
      const std::type_identity<int_type[1]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1iv, this->uniform1iv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const int_type> value,
      const std::type_identity<int_type[2]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform2iv, this->uniform2iv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const int_type> value,
      const std::type_identity<int_type[3]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform3iv, this->uniform3iv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const int_type> value,
      const std::type_identity<int_type[4]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform4iv, this->uniform4iv, prog, loc, value);
    }

    // float
    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const float_type value) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1f, this->uniform1f, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const std::type_identity<float_type[1]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform1fv, this->uniform1fv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const std::type_identity<float_type[2]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform2fv, this->uniform2fv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const std::type_identity<float_type[3]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform3fv, this->uniform3fv, prog, loc, value);
    }

    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const std::type_identity<float_type[4]>) const -> combined_result<void> {
        return _set_uniform(
          this->program_uniform4fv, this->uniform4fv, prog, loc, value);
    }

    template <typename T>
        requires(is_known_vector_type_v<T>)
    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const T& value) const -> combined_result<void> {
        return set_uniform(
          prog, loc, element_view(value), canonical_compound_type<T>());
    }

    // uniform matrix
    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[2][2]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix2fv,
          this->uniform_matrix2fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[2][3]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix2x3fv,
          this->uniform_matrix2x3fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[2][4]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix2x4fv,
          this->uniform_matrix2x4fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[3][2]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix3x2fv,
          this->uniform_matrix3x2fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[3][3]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix3fv,
          this->uniform_matrix3fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[3][4]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix3x4fv,
          this->uniform_matrix3x4fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[4][2]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix4x2fv,
          this->uniform_matrix4x2fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[4][3]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix4x3fv,
          this->uniform_matrix4x3fv,
          prog,
          loc,
          value,
          transpose);
    }

    auto set_uniform_matrix(
      const program_name prog,
      const uniform_location loc,
      const span<const float_type> value,
      const true_false transpose,
      const std::type_identity<float_type[4][4]>) const
      -> combined_result<void> {
        return _set_uniform_matrix(
          this->program_uniform_matrix4fv,
          this->uniform_matrix4fv,
          prog,
          loc,
          value,
          transpose);
    }

    template <typename T>
    auto set_uniform(
      const program_name prog,
      const uniform_location loc,
      const T& value) const -> combined_result<void>
        requires(is_known_matrix_type_v<T>)
    {
        return set_uniform_matrix(
          prog,
          loc,
          element_view(value),
          true_or_false(math::is_row_major_v<T>),
          canonical_compound_type<T>());
    }
};

export template <std::size_t I, typename ApiTraits>
auto get(const basic_gl_api<ApiTraits>& x) noexcept -> const
  typename std::tuple_element<I, basic_gl_api<ApiTraits>>::type& {
    return x;
}
//------------------------------------------------------------------------------
template <typename A>
auto translate(const basic_gl_api<A>& api, const bool value) noexcept
  -> true_false {
    if(value) {
        return api.true_;
    }
    return api.false_;
}
//------------------------------------------------------------------------------
/// @brief Alias for the default instantation of basic_gl_api.
/// @ingroup gl_api_wrap
export using gl_api = basic_gl_api<gl_api_traits>;
} // namespace eagine::oglplus

// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std {
//------------------------------------------------------------------------------
template <typename ApiTraits>
struct tuple_size<eagine::oglplus::basic_gl_api<ApiTraits>>
  : integral_constant<std::size_t, 2> {};

template <typename ApiTraits>
struct tuple_element<0, eagine::oglplus::basic_gl_api<ApiTraits>>
  : type_identity<eagine::oglplus::basic_gl_operations<ApiTraits>> {};

template <typename ApiTraits>
struct tuple_element<1, eagine::oglplus::basic_gl_api<ApiTraits>>
  : type_identity<eagine::oglplus::basic_gl_constants<ApiTraits>> {};
//------------------------------------------------------------------------------
} // namespace std
namespace eagine::oglplus {
//------------------------------------------------------------------------------
export template <typename ApiTraits>
using basic_gl_api_reference =
  c_api::basic_api_reference<basic_gl_api<ApiTraits>>;

export using gl_api_reference = basic_gl_api_reference<gl_api_traits>;
} // namespace eagine::oglplus

