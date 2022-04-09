/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OGLPLUS_GL_API_API_HPP
#define EAGINE_OGLPLUS_GL_API_API_HPP

#include "../glsl/source_ref.hpp"
#include "c_api.hpp"
#include "enum_types.hpp"
#include "extensions.hpp"
#include "object_name.hpp"
#include "prog_var_loc.hpp"
#include "type_utils.hpp"
#include <eagine/c_api/adapted_function.hpp>
#include <eagine/c_api_wrap.hpp>
#include <eagine/oglplus/utils/buffer_data.hpp>
#include <eagine/quantities.hpp>
#include <eagine/scope_exit.hpp>
#include <eagine/string_list.hpp>

namespace eagine::oglplus {
class gl_debug_logger;
using c_api::adapted_function;
//------------------------------------------------------------------------------
#define OGLPAFP(FUNC) decltype(gl_api::FUNC), &gl_api::FUNC
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the GL API.
/// @ingroup gl_api_wrap
/// @see basic_gl_constants
/// @see basic_gl_c_api
template <typename ApiTraits>
class basic_gl_operations : public basic_gl_c_api<ApiTraits> {

public:
    /// @brief Alias for the traits policy class.
    using api_traits = ApiTraits;

    /// @brief Alias for the basic GL API wrapper.
    using gl_api = basic_gl_c_api<ApiTraits>;

    using sizei_type = typename gl_types::sizei_type;
    using sizeiptr_type = typename gl_types::sizeiptr_type;
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

    template <typename W, W gl_api::*F, typename Signature = typename W::signature>
    class func;

    template <typename W, W gl_api::*F, typename RVC, typename... Params>
    class func<W, F, RVC(Params...)>
      : public wrapped_c_api_function<gl_api, api_traits, nothing_t, W, F> {
        using base =
          wrapped_c_api_function<gl_api, api_traits, nothing_t, W, F>;

    public:
        using base::base;

        constexpr auto operator()(Params... params) const noexcept {
            return this->_chkcall(_conv(params)...)
              .cast_to(type_identity<RVC>{});
        }

        auto bind(Params... params) const noexcept {
            return [this, params...] {
                return (*this)(params...);
            };
        }

    protected:
        template <typename... Args>
        constexpr auto _chkcall(Args&&... args) const noexcept {
            return this->_check(this->_call(std::forward<Args>(args)...));
        }

        using base::_conv;

        template <identifier_t I>
        static constexpr auto _conv(prog_var_location<I> loc) noexcept {
            return loc.index();
        }

        template <typename T>
        static constexpr auto _conv(degrees_t<T> angle) noexcept {
            return angle.value();
        }

        template <typename... Args>
        constexpr auto _cnvchkcall(Args&&... args) const noexcept {
            return this->_chkcall(_conv(std::forward<Args>(args))...)
              .cast_to(type_identity<RVC>{});
        }

    private:
        template <typename Res>
        constexpr auto _check(Res&& res) const noexcept {
            res.error_code(this->api().GetError());
            return std::forward<Res>(res);
        }
    };

    template <typename W, W gl_api::*F, typename Signature = typename W::signature>
    class unck_func;

    template <typename W, W gl_api::*F, typename RVC, typename... Params>
    class unck_func<W, F, RVC(Params...)>
      : public wrapped_c_api_function<gl_api, api_traits, nothing_t, W, F> {
        using base =
          wrapped_c_api_function<gl_api, api_traits, nothing_t, W, F>;

    public:
        using base::base;

        constexpr auto operator()(Params... params) const noexcept {
            return this->_call(_conv(params)...).cast_to(type_identity<RVC>{});
        }

        auto bind(Params... params) const noexcept {
            return [this, params...] {
                return (*this)(params...);
            };
        }

    protected:
        using base::_conv;

        template <identifier_t I>
        static constexpr auto _conv(prog_var_location<I> loc) noexcept {
            return loc.index();
        }

        template <typename T>
        static constexpr auto _conv(degrees_t<T> angle) noexcept {
            return angle.value();
        }

        template <typename... Args>
        constexpr auto _cnvcall(Args&&... args) const noexcept {
            return this->_call(_conv(std::forward<Args>(args))...)
              .cast_to(type_identity<RVC>{});
        }
    };

    // numeric query function
    template <
      typename PreTypeList,
      typename QueryClassList,
      typename PostTypeList,
      typename QueryResult,
      typename W,
      W gl_api::*F>
    struct query_func;

    template <
      typename... PreParams,
      typename... QueryClasses,
      typename... PostParams,
      typename QueryResult,
      typename W,
      W gl_api::*F>
    struct query_func<
      mp_list<PreParams...>,
      mp_list<QueryClasses...>,
      mp_list<PostParams...>,
      QueryResult,
      W,
      F> : func<W, F> {
        using func<W, F>::func;

        template <typename Query>
        constexpr auto operator()(
          PreParams... pre_params,
          Query query,
          PostParams... post_params) const noexcept
          requires((true || ... || is_enum_class_value_v<QueryClasses, Query>)&&(
            !std::is_array_v<typename Query::tag_type>)) {
            using RV = typename Query::tag_type;
            QueryResult result{};
            return this
              ->_cnvchkcall(
                pre_params..., enum_type(query), post_params..., &result)
              .replaced_with(result)
              .cast_to(type_identity<RV>{});
        }

        template <typename Query>
        auto operator()(
          PreParams... pre_params,
          Query query,
          PostParams... post_params,
          span<QueryResult> dest) const noexcept
          requires(true || ... || is_enum_class_value_v<QueryClasses, Query>) {
            EAGINE_ASSERT(dest.size());
            return this->_cnvchkcall(
              pre_params..., enum_type(query), post_params..., dest.data());
        }
    };

    adapted_function<
      &gl_api::FenceSync,
      void(sync_condition, enum_bitfield<sync_flag_bit>)>
      fence_sync{*this};

    template <auto Wrapper, typename ObjTag>
    struct make_object_func : adapted_function<Wrapper, void(span<name_type>)> {
        using base = adapted_function<Wrapper, void(span<name_type>)>;
        using base::base;
        using base::operator();

        constexpr auto operator()(
          gl_object_name_span<gl_object_name<ObjTag>> names) const noexcept {
            return (*this)(names.raw_handles());
        }

        constexpr auto operator()() const noexcept {
            name_type n{};
            return base::operator()(cover_one(n)).transformed([&n](bool valid) {
                return gl_owned_object_name<ObjTag>(valid ? n : 0);
            });
        }
    };

    adapted_function<&gl_api::CreateShader, owned_shader_name(shader_type)>
      create_shader{*this};

    adapted_function<&gl_api::CreateProgram, owned_program_name()>
      create_program{*this};

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

    adapted_function<&gl_api::GenPathsNV, owned_path_nv_name(sizei_type)>
      create_paths_nv{*this};

    // delete objects
    adapted_function<&gl_api::DeleteSync, void(sync_type)> delete_sync{*this};

    template <auto Wrapper, typename ObjTag>
    using del_object_func = c_api::combined<
      adapted_function<Wrapper, void(span<name_type>)>,
      adapted_function<Wrapper, void(gl_owned_object_name<ObjTag>)>>;

    adapted_function<&gl_api::DeleteShader, void(owned_shader_name)>
      delete_shader{*this};

    adapted_function<&gl_api::DeleteProgram, void(owned_program_name)>
      delete_program{*this};

    del_object_func<&gl_api::DeleteBuffers, buffer_tag> delete_buffers{*this};

    del_object_func<&gl_api::DeleteFramebuffers, framebuffer_tag>
      delete_framebuffers{*this};

    del_object_func<&gl_api::DeleteProgramPipelines, program_pipeline_tag>
      delete_program_pipelines{*this};

    del_object_func<&gl_api::DeleteQueries, query_tag> delete_queries{*this};

    del_object_func<&gl_api::DeleteRenderbuffers, renderbuffer_tag>
      delete_renderbuffers{*this};

    del_object_func<&gl_api::DeleteSamplers, sampler_tag> delete_samplers{
      *this};

    del_object_func<&gl_api::DeleteTextures, texture_tag> delete_textures{
      *this};

    del_object_func<&gl_api::DeleteTransformFeedbacks, transform_feedback_tag>
      delete_transform_feedbacks{*this};

    del_object_func<&gl_api::DeleteVertexArrays, vertex_array_tag>
      delete_vertex_arrays{*this};

    adapted_function<&gl_api::DeletePathsNV, void(owned_path_nv_name, sizei_type)>
      delete_paths_nv{*this};

    adapted_function<&gl_api::IsSync, true_false(sync_type)> is_sync{*this};

    adapted_function<&gl_api::IsBuffer, true_false(buffer_name)> is_buffer{
      *this};

    adapted_function<&gl_api::IsFramebuffer, true_false(framebuffer_name)>
      is_framebuffer{*this};

    adapted_function<
      &gl_api::IsProgramPipeline,
      true_false(program_pipeline_name)>
      is_program_pipeline{*this};

    adapted_function<&gl_api::IsProgram, true_false(program_name)> is_program{
      *this};

    adapted_function<&gl_api::IsQuery, true_false(query_name)> is_query{*this};

    adapted_function<&gl_api::IsRenderbuffer, true_false(renderbuffer_name)>
      is_renderbuffer{*this};

    adapted_function<&gl_api::IsSampler, true_false(sampler_name)> is_sampler{
      *this};

    adapted_function<&gl_api::IsShader, true_false(shader_name)> is_shader{
      *this};

    adapted_function<&gl_api::IsTexture, true_false(texture_name)> is_texture{
      *this};

    adapted_function<
      &gl_api::IsTransformFeedback,
      true_false(transform_feedback_name)>
      is_transform_feedback{*this};

    adapted_function<&gl_api::IsVertexArray, true_false(vertex_array_name)>
      is_vertex_array{*this};

    adapted_function<&gl_api::IsPathNV, true_false(path_nv_name)> is_path_nv{
      *this};

    adapted_function<&gl_api::Enable, void(capability)> enable{*this};
    adapted_function<&gl_api::Enablei, void(capability, uint_type)> enablei{
      *this};

    adapted_function<&gl_api::Disable, void(capability)> disable{*this};
    adapted_function<&gl_api::Disablei, void(capability, uint_type)> disablei{
      *this};

    adapted_function<&gl_api::IsEnabled, true_false(capability)> is_enabled{
      *this};
    adapted_function<&gl_api::IsEnabledi, true_false(capability, uint_type)>
      is_enabledi{*this};

    adapted_function<
      &gl_api::MemoryBarrier,
      void(enum_bitfield<memory_barrier_bit>)>
      memory_barrier{*this};

    adapted_function<
      &gl_api::MemoryBarrierByRegion,
      void(enum_bitfield<memory_barrier_bit>)>
      memory_barrier_by_region{*this};

    c_api::combined<
      adapted_function<
        &gl_api::Viewport,
        void(int_type, int_type, sizei_type, sizei_type)>,
      adapted_function<
        &gl_api::Viewport,
        void(c_api::substituted<0>, c_api::substituted<0>, sizei_type, sizei_type)>>
      viewport{*this};

    // viewport_array
    struct : func<OGLPAFP(ViewportArrayv)> {
        using base = func<OGLPAFP(ViewportArrayv)>;

        using base::base;

        constexpr auto operator()(
          uint_type first,
          const span<const float_type> coords) const noexcept {
            EAGINE_ASSERT(coords.size() % 4 == 0);
            return base::operator()(
              first, limit_cast<sizei_type>(coords.size() / 4), coords.data());
        }

        constexpr auto operator()(
          const span<const float_type> coords) const noexcept {
            return (*this)(0U, coords);
        }
    } viewport_array;

    c_api::combined<
      adapted_function<
        &gl_api::StencilFunc,
        void(compare_function, int_type, uint_type)>,
      adapted_function<
        &gl_api::StencilFunc,
        void(compare_function, int_type, c_api::substituted<~uint_type{0U}>)>>
      stencil_func{*this};

    c_api::combined<
      adapted_function<
        &gl_api::StencilFuncSeparate,
        void(face_mode, compare_function, int_type, uint_type)>,
      adapted_function<
        &gl_api::StencilFuncSeparate,
        void(
          face_mode,
          compare_function,
          int_type,
          c_api::substituted<~uint_type{0U}>)>>
      stencil_func_separate{*this};

    adapted_function<
      &gl_api::StencilOp,
      void(stencil_operation, stencil_operation, stencil_operation)>
      stencil_op{*this};

    adapted_function<
      &gl_api::StencilOpSeparate,
      void(face_mode, stencil_operation, stencil_operation, stencil_operation)>
      stencil_op_separate{*this};

    adapted_function<&gl_api::DepthFunc, void(compare_function)> depth_func{
      *this};

    adapted_function<
      &gl_api::ColorMask,
      void(true_false, true_false, true_false, true_false)>
      color_mask{*this};

    adapted_function<
      &gl_api::ColorMaski,
      void(uint_type, true_false, true_false, true_false, true_false)>
      color_mask_i{*this};

    adapted_function<&gl_api::DepthMask, void(true_false)> depth_mask{*this};

    adapted_function<&gl_api::StencilMask, void(uint_type)> stencil_mask{*this};

    adapted_function<&gl_api::StencilMaskSeparate, void(face_mode, uint_type)>
      stencil_mask_separate{*this};

    adapted_function<
      &gl_api::ClearColor,
      void(float_type, float_type, float_type, float_type)>
      clear_color{*this};

    adapted_function<&gl_api::ClearDepth, void(float_type)> clear_depth{*this};
    adapted_function<&gl_api::ClearStencil, void(int_type)> clear_stencil{
      *this};

    adapted_function<&gl_api::Clear, void(enum_bitfield<buffer_clear_bit>)>
      clear{*this};

    adapted_function<
      &gl_api::ShaderSource,
      void(shader_name, const glsl_source_ref&)>
      shader_source{*this};

    adapted_function<&gl_api::CompileShader, void(shader_name)> compile_shader{
      *this};

    adapted_function<
      &gl_api::CompileShaderInclude,
      void(shader_name, const glsl_source_ref&)>
      compile_shader_include{*this};

    query_func<
      mp_list<shader_name>,
      mp_list<shader_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetShaderiv)>
      get_shader_i;

    struct : func<OGLPAFP(GetShaderInfoLog)> {
        using func<OGLPAFP(GetShaderInfoLog)>::func;

        constexpr auto operator()(shader_name shdr, span<char_type> dest)
          const noexcept {
            sizei_type real_len{0};
            return this
              ->_chkcall(
                name_type(shdr), sizei_type(dest.size()), &real_len, dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_shader_info_log;

    adapted_function<&gl_api::AttachShader, void(program_name, shader_name)>
      attach_shader{*this};

    adapted_function<&gl_api::DetachShader, void(program_name, shader_name)>
      detach_shader{*this};

    adapted_function<&gl_api::LinkProgram, void(program_name)> link_program{
      *this};

    query_func<
      mp_list<program_name>,
      mp_list<program_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetProgramiv)>
      get_program_i;

    struct : func<OGLPAFP(GetProgramInfoLog)> {
        using func<OGLPAFP(GetProgramInfoLog)>::func;

        constexpr auto operator()(program_name prog, span<char_type> dest)
          const noexcept {
            sizei_type real_len{0};
            return this
              ->_chkcall(
                name_type(prog), sizei_type(dest.size()), &real_len, dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_program_info_log;

    adapted_function<&gl_api::UseProgram, void(program_name)> use_program{
      *this};

    adapted_function<
      &gl_api::GetProgramResourceIndex,
      uint_type(program_name, program_interface, string_view)>
      get_program_resource_index{*this};

    struct : func<OGLPAFP(GetProgramResourceIndex)> {
        using func<OGLPAFP(GetProgramResourceIndex)>::func;
        constexpr auto operator()(program_name prog, string_view name)
          const noexcept {
#ifdef GL_SHADER_STORAGE_BLOCK
            return this
              ->_cnvchkcall(name_type(prog), GL_SHADER_STORAGE_BLOCK, name)
              .cast_to(type_identity<shader_storage_block_index>{});
#else
            return this->_fake().cast_to(
              type_identity<shader_storage_block_index>{});
#endif
        }
    } get_shader_storage_block_index;

    adapted_function<
      &gl_api::GetProgramResourceLocation,
      program_resource_location(program_name, program_interface, string_view)>
      get_program_resource_location{*this};

    struct : func<OGLPAFP(GetProgramResourceName)> {
        using func<OGLPAFP(GetProgramResourceName)>::func;

        constexpr auto operator()(
          program_name prog,
          program_interface intf,
          uint_type index,
          span<char_type> dest) const noexcept {
            sizei_type real_len{0};
            return this
              ->_chkcall(
                name_type(prog),
                enum_type(intf),
                index,
                sizei_type(dest.size()),
                &real_len,
                dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_program_resource_name;

    query_func<
      mp_list<program_name, program_interface>,
      mp_list<program_property>,
      mp_list<>,
      int_type,
      OGLPAFP(GetProgramInterfaceiv)>
      get_program_interface_i;

    struct : func<OGLPAFP(GetProgramResourceiv)> {
        using func<OGLPAFP(GetProgramResourceiv)>::func;

        auto operator()(
          program_name prog,
          program_interface intf,
          uint_type index,
          enum_class_view<program_property> props,
          span<int_type> dest) const noexcept {
            sizei_type real_len{0};
            return this
              ->_cnvchkcall(
                prog,
                intf,
                index,
                sizei_type(props.size()),
                props.raw_enums().data(),
                sizei_type(dest.size()),
                &real_len,
                dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_program_resource_i;

    struct : func<OGLPAFP(GetProgramResourcefvNV)> {
        using func<OGLPAFP(GetProgramResourcefvNV)>::func;

        auto operator()(
          program_name prog,
          program_interface intf,
          uint_type index,
          enum_class_view<program_property> props,
          span<float_type> dest) const noexcept {
            sizei_type real_len{0};
            return this
              ->_cnvchkcall(
                prog,
                intf,
                index,
                sizei_type(props.size()),
                props.raw_enums().data(),
                sizei_type(dest.size()),
                &real_len,
                dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_program_resource_f;

    adapted_function<
      &gl_api::BindAttribLocation,
      void(program_name, vertex_attrib_location, string_view)>
      bind_attrib_location{*this};

    adapted_function<
      &gl_api::GetAttribLocation,
      vertex_attrib_location(program_name, string_view)>
      get_attrib_location{*this};

    struct : func<OGLPAFP(GetActiveAttrib)> {
        using func<OGLPAFP(GetActiveAttrib)>::func;

        constexpr auto operator()(
          program_name prog,
          vertex_attrib_location loc,
          span<char_type> dest) const noexcept {
            int_type size{0};
            enum_type type{0};
            sizei_type real_len{0};
            return this
              ->_chkcall(
                name_type(prog),
                loc.index(),
                sizei_type(dest.size()),
                &real_len,
                &size,
                &type,
                dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_active_attrib_name;

    struct : func<OGLPAFP(TransformFeedbackVaryings)> {
        using func<OGLPAFP(TransformFeedbackVaryings)>::func;

        auto operator()(
          program_name prog,
          string_view name,
          transform_feedback_mode mode) const noexcept {
            const auto name_c_str{c_str(name)};
            const char* varyings = name_c_str;
            return this->_cnvchkcall(prog, 1, &varyings, mode);
        }

        auto operator()(
          [[maybe_unused]] program_name prog,
          [[maybe_unused]] string_view name) const noexcept {
#ifdef GL_SEPARATE_ATTRIBS
            const auto name_c_str{c_str(name)};
            const char* varyings = name_c_str;
            return this->_cnvchkcall(prog, 1, &varyings, GL_SEPARATE_ATTRIBS);
#else
            return this->_fake();
#endif
        }
    } transform_feedback_varyings;

    adapted_function<
      &gl_api::BindFragDataLocation,
      void(program_name, frag_data_location, string_view)>
      bind_frag_data_location{*this};

    adapted_function<
      &gl_api::GetFragDataLocation,
      frag_data_location(program_name, string_view)>
      get_frag_data_location{*this};

    adapted_function<
      &gl_api::GetFragDataIndex,
      int_type(program_name, string_view)>
      get_frag_data_index{*this};

    adapted_function<
      &gl_api::BindFragDataLocationIndexed,
      void(program_name, uint_type, frag_data_location, string_view)>
      bind_frag_data_location_indexed{*this};

    adapted_function<
      &gl_api::GetUniformLocation,
      uniform_location(program_name, string_view)>
      get_uniform_location{*this};

    adapted_function<
      &gl_api::GetUniformBlockIndex,
      uniform_block_index(program_name, string_view)>
      get_uniform_block_index{*this};

    struct : func<OGLPAFP(GetActiveUniformName)> {
        using func<OGLPAFP(GetActiveUniformName)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<char_type> dest) const noexcept {
            sizei_type real_len{0};
            return this
              ->_chkcall(
                name_type(prog),
                loc.index(),
                sizei_type(dest.size()),
                &real_len,
                dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_active_uniform_name;

    adapted_function<
      &gl_api::GetSubroutineUniformLocation,
      subroutine_uniform_location(program_name, shader_type, string_view)>
      get_subroutine_uniform_location{*this};

    struct : func<OGLPAFP(GetActiveSubroutineUniformName)> {
        using func<OGLPAFP(GetActiveSubroutineUniformName)>::func;

        constexpr auto operator()(
          program_name prog,
          shader_type shdr_type,
          uniform_location loc,
          span<char_type> dest) const noexcept {
            sizei_type real_len{0};
            return this
              ->_chkcall(
                name_type(prog),
                enum_type(shdr_type),
                loc.index(),
                sizei_type(dest.size()),
                &real_len,
                dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_active_subroutine_uniform_name;

    adapted_function<
      &gl_api::GetSubroutineIndex,
      subroutine_location(program_name, shader_type, string_view)>
      get_subroutine_index{*this};

    struct : func<OGLPAFP(GetActiveSubroutineName)> {
        using func<OGLPAFP(GetActiveSubroutineName)>::func;

        constexpr auto operator()(
          program_name prog,
          shader_type shdr_type,
          subroutine_location loc,
          span<char_type> dest) const noexcept {
            sizei_type real_len{0};
            return this
              ->_cnvchkcall(
                prog,
                shdr_type,
                loc.index(),
                sizei_type(dest.size()),
                &real_len,
                dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_active_subroutine_name;

    struct : func<OGLPAFP(UniformSubroutinesuiv)> {
        using func<OGLPAFP(UniformSubroutinesuiv)>::func;

        constexpr auto operator()(
          shader_type shdr_type,
          subroutine_location subr) const noexcept {
            const uint_type idx{subr.index()};
            return this->_cnvchkcall(shdr_type, 1, &idx);
        }

        template <std::size_t N>
        constexpr auto operator()(
          shader_type shdr_type,
          const subroutine_bindings<N>& subrs) const noexcept {
            std::array<uint_type, N> idcs{};
            for(const auto& [su, s] : subrs._bindings) {
                idcs[su.index()] = s.index();
            }
            return this->_cnvchkcall(
              shdr_type, limit_cast<sizei_type>(idcs.size()), idcs.data());
        }
    } uniform_subroutines;

    // uniform
    // uint
    adapted_function<&gl_api::Uniform1ui, void(uniform_location, uint_type)>
      uniform1ui{*this};

    adapted_function<
      &gl_api::Uniform2ui,
      void(uniform_location, uint_type, uint_type)>
      uniform2ui{*this};

    adapted_function<
      &gl_api::Uniform3ui,
      void(uniform_location, uint_type, uint_type, uint_type)>
      uniform3ui{*this};

    adapted_function<
      &gl_api::Uniform4ui,
      void(uniform_location, uint_type, uint_type, uint_type, uint_type)>
      uniform4ui{*this};

    struct : func<OGLPAFP(Uniform1uiv)> {
        using func<OGLPAFP(Uniform1uiv)>::func;

        constexpr auto operator()(uniform_location loc, span<const uint_type> v)
          const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 1), v.data());
        }
    } uniform1uiv;

    struct : func<OGLPAFP(Uniform2uiv)> {
        using func<OGLPAFP(Uniform2uiv)>::func;

        constexpr auto operator()(uniform_location loc, span<const uint_type> v)
          const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 2), v.data());
        }
    } uniform2uiv;

    struct : func<OGLPAFP(Uniform3uiv)> {
        using func<OGLPAFP(Uniform3uiv)>::func;

        constexpr auto operator()(uniform_location loc, span<const uint_type> v)
          const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 3), v.data());
        }
    } uniform3uiv;

    struct : func<OGLPAFP(Uniform4uiv)> {
        using func<OGLPAFP(Uniform4uiv)>::func;

        constexpr auto operator()(uniform_location loc, span<const uint_type> v)
          const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 4), v.data());
        }
    } uniform4uiv;

    // int
    adapted_function<&gl_api::Uniform1i, void(uniform_location, int_type)>
      uniform1i{*this};

    adapted_function<
      &gl_api::Uniform2i,
      void(uniform_location, int_type, int_type)>
      uniform2i{*this};

    adapted_function<
      &gl_api::Uniform3i,
      void(uniform_location, int_type, int_type, int_type)>
      uniform3i{*this};

    adapted_function<
      &gl_api::Uniform4i,
      void(uniform_location, int_type, int_type, int_type, int_type)>
      uniform4i{*this};

    struct : func<OGLPAFP(Uniform1iv)> {
        using func<OGLPAFP(Uniform1iv)>::func;

        constexpr auto operator()(uniform_location loc, span<const int_type> v)
          const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 1), v.data());
        }
    } uniform1iv;

    struct : func<OGLPAFP(Uniform2iv)> {
        using func<OGLPAFP(Uniform2iv)>::func;

        constexpr auto operator()(uniform_location loc, span<const int_type> v)
          const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 2), v.data());
        }
    } uniform2iv;

    struct : func<OGLPAFP(Uniform3iv)> {
        using func<OGLPAFP(Uniform3iv)>::func;

        constexpr auto operator()(uniform_location loc, span<const int_type> v)
          const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 3), v.data());
        }
    } uniform3iv;

    struct : func<OGLPAFP(Uniform4iv)> {
        using func<OGLPAFP(Uniform4iv)>::func;

        constexpr auto operator()(uniform_location loc, span<const int_type> v)
          const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 4), v.data());
        }
    } uniform4iv;

    // float
    adapted_function<&gl_api::Uniform1f, void(uniform_location, float_type)>
      uniform1f{*this};

    adapted_function<
      &gl_api::Uniform2f,
      void(uniform_location, float_type, float_type)>
      uniform2f{*this};

    adapted_function<
      &gl_api::Uniform3f,
      void(uniform_location, float_type, float_type, float_type)>
      uniform3f{*this};

    adapted_function<
      &gl_api::Uniform4f,
      void(uniform_location, float_type, float_type, float_type, float_type)>
      uniform4f{*this};

    struct : func<OGLPAFP(Uniform1fv)> {
        using func<OGLPAFP(Uniform1fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 1), v.data());
        }
    } uniform1fv;

    struct : func<OGLPAFP(Uniform2fv)> {
        using func<OGLPAFP(Uniform2fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 2), v.data());
        }
    } uniform2fv;

    struct : func<OGLPAFP(Uniform3fv)> {
        using func<OGLPAFP(Uniform3fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 3), v.data());
        }
    } uniform3fv;

    struct : func<OGLPAFP(Uniform4fv)> {
        using func<OGLPAFP(Uniform4fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(loc, sizei_type(v.size() / 4), v.data());
        }
    } uniform4fv;

    // matrix float
    struct : func<OGLPAFP(UniformMatrix2fv)> {
        using func<OGLPAFP(UniformMatrix2fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 4), transp, v.data());
        }
    } uniform_matrix2fv;

    struct : func<OGLPAFP(UniformMatrix3fv)> {
        using func<OGLPAFP(UniformMatrix3fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 9), transp, v.data());
        }
    } uniform_matrix3fv;

    struct : func<OGLPAFP(UniformMatrix4fv)> {
        using func<OGLPAFP(UniformMatrix4fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 16), transp, v.data());
        }
    } uniform_matrix4fv;

    struct : func<OGLPAFP(UniformMatrix2x3fv)> {
        using func<OGLPAFP(UniformMatrix2x3fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 6), transp, v.data());
        }
    } uniform_matrix2x3fv;

    struct : func<OGLPAFP(UniformMatrix2x4fv)> {
        using func<OGLPAFP(UniformMatrix2x4fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 8), transp, v.data());
        }
    } uniform_matrix2x4fv;

    struct : func<OGLPAFP(UniformMatrix3x2fv)> {
        using func<OGLPAFP(UniformMatrix3x2fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 6), transp, v.data());
        }
    } uniform_matrix3x2fv;

    struct : func<OGLPAFP(UniformMatrix3x4fv)> {
        using func<OGLPAFP(UniformMatrix3x4fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 12), transp, v.data());
        }
    } uniform_matrix3x4fv;

    struct : func<OGLPAFP(UniformMatrix4x2fv)> {
        using func<OGLPAFP(UniformMatrix4x2fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 8), transp, v.data());
        }
    } uniform_matrix4x2fv;

    struct : func<OGLPAFP(UniformMatrix4x3fv)> {
        using func<OGLPAFP(UniformMatrix4x3fv)>::func;

        constexpr auto operator()(
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              loc, sizei_type(v.size() / 12), transp, v.data());
        }
    } uniform_matrix4x3fv;

    // program uniform
    // uint
    adapted_function<
      &gl_api::ProgramUniform1ui,
      void(program_name, uniform_location, uint_type)>
      program_uniform1ui{*this};

    adapted_function<
      &gl_api::ProgramUniform2ui,
      void(program_name, uniform_location, uint_type, uint_type)>
      program_uniform2ui{*this};

    adapted_function<
      &gl_api::ProgramUniform3ui,
      void(program_name, uniform_location, uint_type, uint_type, uint_type)>
      program_uniform3ui{*this};

    adapted_function<
      &gl_api::ProgramUniform4ui,
      void(
        program_name,
        uniform_location,
        uint_type,
        uint_type,
        uint_type,
        uint_type)>
      program_uniform4ui{*this};

    struct : func<OGLPAFP(ProgramUniform1uiv)> {
        using func<OGLPAFP(ProgramUniform1uiv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const uint_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 1), v.data());
        }
    } program_uniform1uiv;

    struct : func<OGLPAFP(ProgramUniform2uiv)> {
        using func<OGLPAFP(ProgramUniform2uiv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const uint_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 2), v.data());
        }
    } program_uniform2uiv;

    struct : func<OGLPAFP(ProgramUniform3uiv)> {
        using func<OGLPAFP(ProgramUniform3uiv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const uint_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 3), v.data());
        }
    } program_uniform3uiv;

    struct : func<OGLPAFP(ProgramUniform4uiv)> {
        using func<OGLPAFP(ProgramUniform4uiv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const uint_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 4), v.data());
        }
    } program_uniform4uiv;

    // int
    adapted_function<
      &gl_api::ProgramUniform1i,
      void(program_name, uniform_location, int_type)>
      program_uniform1i{*this};

    adapted_function<
      &gl_api::ProgramUniform2i,
      void(program_name, uniform_location, int_type, int_type)>
      program_uniform2i{*this};

    adapted_function<
      &gl_api::ProgramUniform3i,
      void(program_name, uniform_location, int_type, int_type, int_type)>
      program_uniform3i{*this};

    adapted_function<
      &gl_api::ProgramUniform4i,
      void(program_name, uniform_location, int_type, int_type, int_type, int_type)>
      program_uniform4i{*this};

    struct : func<OGLPAFP(ProgramUniform1iv)> {
        using func<OGLPAFP(ProgramUniform1iv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const int_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 1), v.data());
        }
    } program_uniform1iv;

    struct : func<OGLPAFP(ProgramUniform2iv)> {
        using func<OGLPAFP(ProgramUniform2iv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const int_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 2), v.data());
        }
    } program_uniform2iv;

    struct : func<OGLPAFP(ProgramUniform3iv)> {
        using func<OGLPAFP(ProgramUniform3iv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const int_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 3), v.data());
        }
    } program_uniform3iv;

    struct : func<OGLPAFP(ProgramUniform4iv)> {
        using func<OGLPAFP(ProgramUniform4iv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const int_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 4), v.data());
        }
    } program_uniform4iv;

    // float
    adapted_function<
      &gl_api::ProgramUniform1f,
      void(program_name, uniform_location, float_type)>
      program_uniform1f{*this};

    adapted_function<
      &gl_api::ProgramUniform2f,
      void(program_name, uniform_location, float_type, float_type)>
      program_uniform2f{*this};

    adapted_function<
      &gl_api::ProgramUniform3f,
      void(program_name, uniform_location, float_type, float_type, float_type)>
      program_uniform3f{*this};

    adapted_function<
      &gl_api::ProgramUniform4f,
      void(
        program_name,
        uniform_location,
        float_type,
        float_type,
        float_type,
        float_type)>
      program_uniform4f{*this};

    struct : func<OGLPAFP(ProgramUniform1fv)> {
        using func<OGLPAFP(ProgramUniform1fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 1), v.data());
        }
    } program_uniform1fv;

    struct : func<OGLPAFP(ProgramUniform2fv)> {
        using func<OGLPAFP(ProgramUniform2fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 2), v.data());
        }
    } program_uniform2fv;

    struct : func<OGLPAFP(ProgramUniform3fv)> {
        using func<OGLPAFP(ProgramUniform3fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 3), v.data());
        }
    } program_uniform3fv;

    struct : func<OGLPAFP(ProgramUniform4fv)> {
        using func<OGLPAFP(ProgramUniform4fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 4), v.data());
        }
    } program_uniform4fv;

    // matrix float
    struct : func<OGLPAFP(ProgramUniformMatrix2fv)> {
        using func<OGLPAFP(ProgramUniformMatrix2fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 4), transp, v.data());
        }
    } program_uniform_matrix2fv;

    struct : func<OGLPAFP(ProgramUniformMatrix3fv)> {
        using func<OGLPAFP(ProgramUniformMatrix3fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 9), transp, v.data());
        }
    } program_uniform_matrix3fv;

    struct : func<OGLPAFP(ProgramUniformMatrix4fv)> {
        using func<OGLPAFP(ProgramUniformMatrix4fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 16), transp, v.data());
        }
    } program_uniform_matrix4fv;

    struct : func<OGLPAFP(ProgramUniformMatrix2x3fv)> {
        using func<OGLPAFP(ProgramUniformMatrix2x3fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 6), transp, v.data());
        }
    } program_uniform_matrix2x3fv;

    struct : func<OGLPAFP(ProgramUniformMatrix2x4fv)> {
        using func<OGLPAFP(ProgramUniformMatrix2x4fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 8), transp, v.data());
        }
    } program_uniform_matrix2x4fv;

    struct : func<OGLPAFP(ProgramUniformMatrix3x2fv)> {
        using func<OGLPAFP(ProgramUniformMatrix3x2fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 6), transp, v.data());
        }
    } program_uniform_matrix3x2fv;

    struct : func<OGLPAFP(ProgramUniformMatrix3x4fv)> {
        using func<OGLPAFP(ProgramUniformMatrix3x4fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 12), transp, v.data());
        }
    } program_uniform_matrix3x4fv;

    struct : func<OGLPAFP(ProgramUniformMatrix4x2fv)> {
        using func<OGLPAFP(ProgramUniformMatrix4x2fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 8), transp, v.data());
        }
    } program_uniform_matrix4x2fv;

    struct : func<OGLPAFP(ProgramUniformMatrix4x3fv)> {
        using func<OGLPAFP(ProgramUniformMatrix4x3fv)>::func;

        constexpr auto operator()(
          program_name prog,
          uniform_location loc,
          true_false transp,
          span<const float_type> v) const noexcept {
            return this->_cnvchkcall(
              prog, loc, sizei_type(v.size() / 12), transp, v.data());
        }
    } program_uniform_matrix4x3fv;

    adapted_function<
      &gl_api::UniformBlockBinding,
      void(program_name, uniform_block_index, uint_type)>
      uniform_block_binding{*this};

    adapted_function<
      &gl_api::ShaderStorageBlockBinding,
      void(program_name, shader_storage_block_index, uint_type)>
      shader_storage_block_binding{*this};

    // buffer ops
    adapted_function<&gl_api::BindBuffer, void(buffer_target, buffer_name)>
      bind_buffer{*this};

    adapted_function<
      &gl_api::BindBufferBase,
      void(buffer_target, uint_type, buffer_name)>
      bind_buffer_base{*this};

    adapted_function<
      &gl_api::BindBufferRange,
      void(buffer_target, uint_type, buffer_name, intptr_type, sizeiptr_type)>
      bind_buffer_range{*this};

    c_api::combined<
      adapted_function<
        &gl_api::BufferStorage,
        void(
          buffer_target,
          sizeiptr_type,
          const_void_ptr_type,
          enum_bitfield<buffer_storage_bit>)>,
      adapted_function<
        &gl_api::BufferStorage,
        void(
          buffer_target,
          sizeiptr_type,
          c_api::substituted<nullptr>,
          c_api::substituted<0U>)>>
      buffer_storage{*this};

    c_api::combined<
      adapted_function<
        &gl_api::NamedBufferStorage,
        void(
          buffer_name,
          sizeiptr_type,
          const_void_ptr_type,
          enum_bitfield<buffer_storage_bit>)>,
      adapted_function<
        &gl_api::NamedBufferStorage,
        void(
          buffer_name,
          sizeiptr_type,
          c_api::substituted<nullptr>,
          c_api::substituted<0U>)>>
      named_buffer_storage{*this};

    adapted_function<
      &gl_api::BufferData,
      void(buffer_target, buffer_data_spec, buffer_usage)>
      buffer_data{*this};

    adapted_function<
      &gl_api::NamedBufferData,
      void(buffer_name, buffer_data_spec, buffer_usage)>
      named_buffer_data{*this};

    adapted_function<
      &gl_api::BufferSubData,
      void(buffer_target, intptr_type, buffer_data_spec)>
      buffer_sub_data{*this};

    adapted_function<
      &gl_api::NamedBufferSubData,
      void(buffer_name, intptr_type, buffer_data_spec)>
      named_buffer_sub_data{*this};

    using _clear_buffer_data_t = adapted_function<
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
          type_identity<T>) const noexcept {
            return (*this)(
              tgt, ifmt, pixel_format_of<T>(), pixel_data_type_of<T>(), nullptr);
        }

        template <typename T>
        constexpr auto operator()(buffer_target tgt, type_identity<T> tid)
          const noexcept {
            return (*this)(tgt, internal_format_of<T>(), tid);
        }
    } clear_buffer_data{*this};

    using _clear_named_buffer_data_t = adapted_function<
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
          type_identity<T>) const noexcept {
            return (*this)(buf, ifmt, fmt, pixel_data_type_of<T>(), nullptr);
        }

        template <typename T>
        constexpr auto operator()(buffer_name buf, type_identity<T> tid)
          const noexcept {
            return (*this)(buf, internal_format_of<T>(), tid);
        }
    } clear_named_buffer_data{*this};

    using _clear_buffer_sub_data_t = adapted_function<
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

    using _clear_named_buffer_sub_data_t = adapted_function<
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

    adapted_function<
      &gl_api::MapBuffer,
      void_ptr_type(buffer_target, enum_bitfield<buffer_map_access_bit>)>
      map_buffer{*this};

    adapted_function<
      &gl_api::MapNamedBuffer,
      void_ptr_type(buffer_name, enum_bitfield<buffer_map_access_bit>)>
      map_named_buffer{*this};

    adapted_function<
      &gl_api::MapBufferRange,
      void_ptr_type(
        buffer_target,
        intptr_type,
        sizeiptr_type,
        enum_bitfield<buffer_map_access_bit>)>
      map_buffer_range{*this};

    adapted_function<
      &gl_api::MapNamedBufferRange,
      void_ptr_type(
        buffer_name,
        intptr_type,
        sizeiptr_type,
        enum_bitfield<buffer_map_access_bit>)>
      map_named_buffer_range{*this};

    adapted_function<
      &gl_api::FlushMappedBufferRange,
      void_ptr_type(buffer_target, intptr_type, sizeiptr_type)>
      flush_mapped_buffer_range{*this};

    adapted_function<
      &gl_api::FlushMappedNamedBufferRange,
      void_ptr_type(buffer_name, intptr_type, sizeiptr_type)>
      flush_mapped_named_buffer_range{*this};

    adapted_function<&gl_api::UnmapBuffer, void_ptr_type(buffer_target)>
      unmap_buffer{*this};

    adapted_function<&gl_api::UnmapNamedBuffer, void_ptr_type(buffer_name)>
      unmap_named_buffer{*this};

    adapted_function<&gl_api::InvalidateBufferData, void(buffer_name)>
      invalidate_buffer_data{*this};

    adapted_function<
      &gl_api::InvalidateBufferSubData,
      void(buffer_name, intptr_type, sizeiptr_type)>
      invalidate_buffer_sub_data{*this};

    adapted_function<
      &gl_api::CopyBufferSubData,
      void(buffer_target, buffer_target, intptr_type, intptr_type, sizeiptr_type)>
      copy_buffer_sub_data{*this};

    adapted_function<
      &gl_api::CopyNamedBufferSubData,
      void(buffer_name, buffer_name, intptr_type, intptr_type, sizeiptr_type)>
      copy_named_buffer_sub_data{*this};

    query_func<
      mp_list<buffer_target>,
      mp_list<buffer_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetBufferParameteriv)>
      get_buffer_parameter_i;

    query_func<
      mp_list<buffer_name>,
      mp_list<buffer_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetNamedBufferParameteriv)>
      get_named_buffer_parameter_i;

    query_func<
      mp_list<buffer_target>,
      mp_list<buffer_parameter>,
      mp_list<>,
      int64_type,
      OGLPAFP(GetBufferParameteri64v)>
      get_buffer_parameter_i64;

    query_func<
      mp_list<buffer_name>,
      mp_list<buffer_parameter>,
      mp_list<>,
      int64_type,
      OGLPAFP(GetNamedBufferParameteri64v)>
      get_named_buffer_parameter_i64;

    // vertex_array ops
    adapted_function<&gl_api::BindVertexArray, void(vertex_array_name)>
      bind_vertex_array{*this};

    adapted_function<
      &gl_api::BindVertexBuffer,
      void(vertex_buffer_binding, buffer_name, intptr_type, sizei_type)>
      bind_vertex_buffer{*this};

    adapted_function<
      &gl_api::VertexArrayVertexBuffer,
      void(
        vertex_array_name,
        vertex_buffer_binding,
        buffer_name,
        intptr_type,
        sizei_type)>
      vertex_array_vertex_buffer{*this};

    adapted_function<
      &gl_api::VertexArrayElementBuffer,
      void(vertex_array_name, buffer_name)>
      vertex_array_element_buffer{*this};

    adapted_function<
      &gl_api::EnableVertexAttribArray,
      void(vertex_attrib_location)>
      enable_vertex_attrib_array{*this};

    adapted_function<
      &gl_api::EnableVertexArrayAttrib,
      void(vertex_array_name, vertex_attrib_location)>
      enable_vertex_array_attrib{*this};

    adapted_function<
      &gl_api::DisableVertexAttribArray,
      void(vertex_attrib_location)>
      disable_vertex_attrib_array{*this};

    adapted_function<
      &gl_api::DisableVertexArrayAttrib,
      void(vertex_array_name, vertex_attrib_location)>
      disable_vertex_array_attrib{*this};

    adapted_function<
      &gl_api::VertexAttribFormat,
      void(vertex_attrib_location, int_type, data_type, true_false, uint_type)>
      vertex_attrib_format{*this};

    adapted_function<
      &gl_api::VertexAttribIFormat,
      void(vertex_attrib_location, int_type, data_type, uint_type)>
      vertex_attrib_iformat{*this};

    adapted_function<
      &gl_api::VertexAttribLFormat,
      void(vertex_attrib_location, int_type, data_type, uint_type)>
      vertex_attrib_lformat{*this};

    adapted_function<
      &gl_api::VertexArrayAttribFormat,
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        true_false,
        uint_type)>
      vertex_array_attrib_format{*this};

    adapted_function<
      &gl_api::VertexArrayAttribIFormat,
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        uint_type)>
      vertex_array_attrib_iformat{*this};

    adapted_function<
      &gl_api::VertexArrayAttribLFormat,
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        uint_type)>
      vertex_array_attrib_lformat{*this};

    c_api::combined<
      adapted_function<
        &gl_api::VertexAttribPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          true_false,
          sizei_type,
          const_void_ptr_type)>,
      adapted_function<
        &gl_api::VertexAttribPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          true_false,
          c_api::substituted<0>,
          c_api::substituted<nullptr>)>>
      vertex_attrib_pointer{*this};

    c_api::combined<
      adapted_function<
        &gl_api::VertexAttribIPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          sizei_type,
          const_void_ptr_type)>,
      adapted_function<
        &gl_api::VertexAttribIPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          c_api::substituted<0>,
          c_api::substituted<nullptr>)>>
      vertex_attrib_ipointer{*this};

    c_api::combined<
      adapted_function<
        &gl_api::VertexAttribLPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          sizei_type,
          const_void_ptr_type)>,
      adapted_function<
        &gl_api::VertexAttribLPointer,
        void(
          vertex_attrib_location,
          int_type,
          data_type,
          c_api::substituted<0>,
          c_api::substituted<nullptr>)>>
      vertex_attrib_lpointer{*this};

    adapted_function<
      &gl_api::VertexAttribBinding,
      void(vertex_attrib_location, vertex_buffer_binding)>
      vertex_attrib_binding{*this};

    adapted_function<
      &gl_api::VertexArrayAttribBinding,
      void(vertex_array_name, vertex_attrib_location, vertex_buffer_binding)>
      vertex_array_attrib_binding{*this};

    adapted_function<
      &gl_api::VertexBindingDivisor,
      void(vertex_buffer_binding, uint_type)>
      vertex_binding_divisor{*this};

    adapted_function<
      &gl_api::VertexArrayBindingDivisor,
      void(vertex_buffer_binding, uint_type)>
      vertex_array_binding_divisor{*this};

    adapted_function<
      &gl_api::VertexAttribDivisor,
      void(vertex_attrib_location, uint_type)>
      vertex_attrib_divisor{*this};

    // texture ops
    adapted_function<&gl_api::ActiveTexture, void(texture_unit)> active_texture{
      *this};

    adapted_function<&gl_api::BindTexture, void(texture_target, texture_name)>
      bind_texture{*this};

    adapted_function<
      &gl_api::BindTextures,
      void(uint_type, span<const name_type>)>
      bind_textures{*this};

    adapted_function<&gl_api::BindTextureUnit, void(uint_type, texture_name)>
      bind_texture_unit{*this};

    adapted_function<
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

    adapted_function<
      &gl_api::TexStorage3D,
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type)>
      tex_storage3d{*this};

    adapted_function<
      &gl_api::TextureStorage3D,
      void(
        texture_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type)>
      texture_storage3d{*this};

    adapted_function<
      &gl_api::TexStorage2D,
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      tex_storage2d{*this};

    adapted_function<
      &gl_api::TextureStorage2D,
      void(texture_name, sizei_type, pixel_internal_format, sizei_type, sizei_type)>
      texture_storage2d{*this};

    adapted_function<
      &gl_api::TexStorage1D,
      void(texture_target, sizei_type, pixel_internal_format, sizei_type)>
      tex_storage1d{*this};

    adapted_function<
      &gl_api::TextureStorage1D,
      void(texture_name, sizei_type, pixel_internal_format, sizei_type)>
      texture_storage1d{*this};

    adapted_function<
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

    adapted_function<
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

    adapted_function<
      &gl_api::TexStorage2DMultisample,
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        bool_type)>
      tex_storage2d_multisample{*this};

    adapted_function<
      &gl_api::TextureStorage2DMultisample,
      void(
        texture_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        bool_type)>
      texture_storage2d_multisample{*this};

    func<
      OGLPAFP(TexImage3D),
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
      tex_image3d;

    func<
      OGLPAFP(TexImage2D),
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
      tex_image2d;

    func<
      OGLPAFP(TexImage1D),
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        sizei_type,
        int_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      tex_image1d;

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
      &gl_api::CopyTexSubImage1D,
      void(texture_target, int_type, int_type, int_type, int_type, sizei_type)>
      copy_tex_sub_image1d{*this};

    adapted_function<
      &gl_api::CopyTextureSubImage1D,
      void(texture_name, int_type, int_type, int_type, int_type, sizei_type)>
      copy_texture_sub_image1d{*this};

    adapted_function<
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

    adapted_function<
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

    adapted_function<
      &gl_api::CompressedTexImage1D,
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        sizei_type,
        int_type,
        memory::const_block)>
      compressed_tex_image1d{*this};

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
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

    adapted_function<
      &gl_api::CompressedTexSubImage1D,
      void(
        texture_target,
        int_type,
        int_type,
        sizei_type,
        pixel_format,
        memory::const_block)>
      compressed_tex_sub_image1d{*this};

    adapted_function<
      &gl_api::CompressedTextureSubImage1D,
      void(
        texture_name,
        int_type,
        int_type,
        sizei_type,
        pixel_format,
        memory::const_block)>
      compressed_texture_sub_image1d{*this};

    adapted_function<
      &gl_api::TexBuffer,
      void(texture_target, pixel_internal_format, buffer_name)>
      tex_buffer{*this};

    adapted_function<
      &gl_api::TextureBuffer,
      void(texture_name, pixel_internal_format, buffer_name)>
      texture_buffer{*this};

    adapted_function<
      &gl_api::TexBufferRange,
      void(
        texture_target,
        pixel_internal_format,
        buffer_name,
        intptr_type,
        sizeiptr_type)>
      tex_buffer_range{*this};

    adapted_function<
      &gl_api::TextureBufferRange,
      void(
        texture_name,
        pixel_internal_format,
        buffer_name,
        intptr_type,
        sizeiptr_type)>
      texture_buffer_range{*this};

    adapted_function<
      &gl_api::TexParameterf,
      void(texture_target, texture_parameter, float_type)>
      tex_parameter_f{*this};

    adapted_function<
      &gl_api::TextureParameterf,
      void(texture_name, texture_parameter, float_type)>
      texture_parameter_f{*this};

    struct : func<OGLPAFP(TexParameteri)> {
        using func<OGLPAFP(TexParameteri)>::func;

        template <typename TexParam, typename Value>
        constexpr auto operator()(
          texture_target tgt,
          TexParam param,
          Value value) const noexcept
          requires(is_enum_parameter_value_v<
                   texture_parameter,
                   TexParam,
                   int_type,
                   Value>) {
            return this->_chkcall(
              enum_type(tgt), enum_type(param), enum_type(value));
        }
    } tex_parameter_i;

    struct : func<OGLPAFP(TextureParameteri)> {
        using func<OGLPAFP(TextureParameteri)>::func;

        template <typename TexParam, typename Value>
        constexpr auto operator()(texture_name tex, TexParam param, Value value)
          const noexcept requires(is_enum_parameter_value_v<
                                  texture_parameter,
                                  TexParam,
                                  int_type,
                                  Value>) {
            return this->_chkcall(
              name_type(tex), enum_type(param), enum_type(value));
        }
    } texture_parameter_i;

    adapted_function<
      &gl_api::TexParameterfv,
      void(texture_target, texture_parameter, span<const float_type>)>
      tex_parameter_fv{*this};

    adapted_function<
      &gl_api::TextureParameterfv,
      void(texture_name, texture_parameter, span<const float_type>)>
      texture_parameter_fv{*this};

    adapted_function<
      &gl_api::TexParameteriv,
      void(texture_target, texture_parameter, span<const int_type>)>
      tex_parameter_iv{*this};

    adapted_function<
      &gl_api::TextureParameteriv,
      void(texture_name, texture_parameter, span<const int_type>)>
      texture_parameter_iv{*this};

    adapted_function<
      &gl_api::TexParameterIiv,
      void(texture_target, texture_parameter, span<const int_type>)>
      tex_parameter_iiv{*this};

    adapted_function<
      &gl_api::TextureParameterIiv,
      void(texture_name, texture_parameter, span<const int_type>)>
      texture_parameter_iiv{*this};

    adapted_function<
      &gl_api::TexParameterIuiv,
      void(texture_target, texture_parameter, span<const uint_type>)>
      tex_parameter_iuiv{*this};

    adapted_function<
      &gl_api::TextureParameterIuiv,
      void(texture_name, texture_parameter, span<const uint_type>)>
      texture_parameter_iuiv{*this};

    query_func<
      mp_list<texture_target>,
      mp_list<texture_parameter>,
      mp_list<>,
      float_type,
      OGLPAFP(GetTexParameterfv)>
      get_tex_parameter_f;

    query_func<
      mp_list<texture_name>,
      mp_list<texture_parameter>,
      mp_list<>,
      float_type,
      OGLPAFP(GetTextureParameterfv)>
      get_texture_parameter_f;

    query_func<
      mp_list<texture_target>,
      mp_list<texture_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetTexParameteriv)>
      get_tex_parameter_i;

    query_func<
      mp_list<texture_name>,
      mp_list<texture_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetTextureParameteriv)>
      get_texture_parameter_i;

    query_func<
      mp_list<texture_target>,
      mp_list<texture_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetTexParameterIiv)>
      get_tex_parameter_ii;

    query_func<
      mp_list<texture_name>,
      mp_list<texture_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetTextureParameterIiv)>
      get_texture_parameter_ii;

    query_func<
      mp_list<texture_target>,
      mp_list<texture_parameter>,
      mp_list<>,
      uint_type,
      OGLPAFP(GetTexParameterIuiv)>
      get_tex_parameter_iui;

    query_func<
      mp_list<texture_name>,
      mp_list<texture_parameter>,
      mp_list<>,
      uint_type,
      OGLPAFP(GetTextureParameterIuiv)>
      get_texture_parameter_iui;

    adapted_function<&gl_api::GenerateMipmap, void(texture_target)>
      generate_mipmap{*this};
    adapted_function<&gl_api::GenerateTextureMipmap, void(texture_name)>
      generate_texture_mipmap{*this};

    // sampler ops
    adapted_function<&gl_api::BindSampler, void(uint_type, sampler_name)>
      bind_sampler{*this};

    adapted_function<
      &gl_api::SamplerParameterf,
      void(sampler_name, sampler_parameter, float_type)>
      sampler_parameter_f{*this};

    adapted_function<
      &gl_api::SamplerParameteri,
      void(sampler_name, sampler_parameter, int_type)>
      sampler_parameter_i{*this};

    adapted_function<
      &gl_api::SamplerParameterfv,
      void(sampler_name, sampler_parameter, span<const float_type>)>
      sampler_parameter_fv{*this};

    adapted_function<
      &gl_api::SamplerParameteriv,
      void(sampler_name, sampler_parameter, span<const int_type>)>
      sampler_parameter_iv{*this};

    adapted_function<
      &gl_api::SamplerParameterIiv,
      void(sampler_name, sampler_parameter, span<const int_type>)>
      sampler_parameter_iiv{*this};

    adapted_function<
      &gl_api::SamplerParameterIuiv,
      void(sampler_name, sampler_parameter, span<const uint_type>)>
      sampler_parameter_iuiv{*this};

    query_func<
      mp_list<sampler_name>,
      mp_list<sampler_parameter>,
      mp_list<>,
      float_type,
      OGLPAFP(GetSamplerParameterfv)>
      get_sampler_parameter_f;

    query_func<
      mp_list<sampler_name>,
      mp_list<sampler_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetSamplerParameteriv)>
      get_sampler_parameter_i;

    query_func<
      mp_list<sampler_name>,
      mp_list<sampler_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetSamplerParameterIiv)>
      get_sampler_parameter_ii;

    query_func<
      mp_list<sampler_name>,
      mp_list<sampler_parameter>,
      mp_list<>,
      uint_type,
      OGLPAFP(GetSamplerParameterIuiv)>
      get_sampler_parameter_iui;

    // renderbuffer ops
    adapted_function<
      &gl_api::BindRenderbuffer,
      void(renderbuffer_target, renderbuffer_name)>
      bind_renderbuffer{*this};

    adapted_function<
      &gl_api::RenderbufferStorage,
      void(renderbuffer_target, pixel_internal_format, sizei_type, sizei_type)>
      renderbuffer_storage{*this};

    adapted_function<
      &gl_api::NamedRenderbufferStorage,
      void(renderbuffer_name, pixel_internal_format, sizei_type, sizei_type)>
      named_renderbuffer_storage{*this};

    adapted_function<
      &gl_api::RenderbufferStorageMultisample,
      void(
        renderbuffer_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      renderbuffer_storage_multisample{*this};

    adapted_function<
      &gl_api::NamedRenderbufferStorageMultisample,
      void(
        renderbuffer_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      named_renderbuffer_storage_multisample{*this};

    query_func<
      mp_list<renderbuffer_target>,
      mp_list<renderbuffer_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetRenderbufferParameteriv)>
      get_renderbuffer_parameter_i;

    query_func<
      mp_list<renderbuffer_name>,
      mp_list<renderbuffer_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetNamedRenderbufferParameteriv)>
      get_named_renderbuffer_parameter_i;

    // framebuffer ops
    func<OGLPAFP(BindFramebuffer), void(framebuffer_target, framebuffer_name)>
      bind_framebuffer;

    func<OGLPAFP(DrawBuffer), void(surface_buffer)> draw_buffer;

    func<
      OGLPAFP(NamedFramebufferDrawBuffer),
      void(framebuffer_name, surface_buffer)>
      named_framebuffer_draw_buffer;

    func<OGLPAFP(ReadBuffer), void(surface_buffer)> read_buffer;

    func<
      OGLPAFP(NamedFramebufferReadBuffer),
      void(framebuffer_name, surface_buffer)>
      named_framebuffer_read_buffer;

    func<
      OGLPAFP(FramebufferParameteri),
      void(framebuffer_target, framebuffer_parameter, int_type)>
      framebuffer_parameter_i;

    func<
      OGLPAFP(NamedFramebufferParameteri),
      void(framebuffer_name, framebuffer_parameter, int_type)>
      named_framebuffer_parameter_i;

    query_func<
      mp_list<framebuffer_target>,
      mp_list<framebuffer_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetFramebufferParameteriv)>
      get_framebuffer_parameter_i;

    query_func<
      mp_list<framebuffer_name>,
      mp_list<framebuffer_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetNamedFramebufferParameteriv)>
      get_named_framebuffer_parameter_i;

    query_func<
      mp_list<framebuffer_target, framebuffer_attachment>,
      mp_list<framebuffer_attachment_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetFramebufferAttachmentParameteriv)>
      get_framebuffer_attachment_parameter_i;

    query_func<
      mp_list<framebuffer_name, framebuffer_attachment>,
      mp_list<framebuffer_attachment_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetNamedFramebufferAttachmentParameteriv)>
      get_named_framebuffer_attachment_parameter_i;

    func<
      OGLPAFP(FramebufferRenderbuffer),
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        renderbuffer_target,
        renderbuffer_name)>
      framebuffer_renderbuffer;

    func<
      OGLPAFP(NamedFramebufferRenderbuffer),
      void(
        framebuffer_name,
        oglplus::framebuffer_attachment,
        renderbuffer_target,
        renderbuffer_name)>
      named_framebuffer_renderbuffer;

    func<
      OGLPAFP(FramebufferTexture),
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type)>
      framebuffer_texture;

    func<
      OGLPAFP(NamedFramebufferTexture),
      void(
        framebuffer_name,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type)>
      named_framebuffer_texture;

    func<
      OGLPAFP(FramebufferTexture1D),
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type)>
      framebuffer_texture1d;

    func<
      OGLPAFP(FramebufferTexture2D),
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        oglplus::texture_target,
        texture_name,
        int_type)>
      framebuffer_texture2d;

    func<
      OGLPAFP(FramebufferTexture3D),
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        oglplus::texture_target,
        texture_name,
        int_type)>
      framebuffer_texture3d;

    func<
      OGLPAFP(FramebufferTextureLayer),
      void(
        framebuffer_target,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type,
        int_type)>
      framebuffer_texture_layer;

    func<
      OGLPAFP(NamedFramebufferTextureLayer),
      void(
        framebuffer_name,
        oglplus::framebuffer_attachment,
        texture_name,
        int_type,
        int_type)>
      named_framebuffer_texture_layer;

    func<OGLPAFP(CheckFramebufferStatus), framebuffer_status(framebuffer_target)>
      check_framebuffer_status;

    func<
      OGLPAFP(CheckNamedFramebufferStatus),
      framebuffer_status(framebuffer_name, framebuffer_target)>
      check_named_framebuffer_status;

    func<
      OGLPAFP(BlitFramebuffer),
      void(
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        enum_bitfield<buffer_blit_bit>,
        blit_filter)>
      blit_framebuffer;

    func<
      OGLPAFP(BlitNamedFramebuffer),
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
        enum_bitfield<buffer_blit_bit>,
        blit_filter)>
      blit_named_framebuffer;

    // transform feedback ops
    func<
      OGLPAFP(BindTransformFeedback),
      void(transform_feedback_target, transform_feedback_name)>
      bind_transform_feedback;

    func<OGLPAFP(BeginTransformFeedback), void(transform_feedback_primitive_type)>
      begin_transform_feedback;

    func<OGLPAFP(PauseTransformFeedback)> pause_transform_feedback;

    func<OGLPAFP(ResumeTransformFeedback)> resume_transform_feedback;

    func<OGLPAFP(EndTransformFeedback)> end_transform_feedback;

    func<
      OGLPAFP(TransformFeedbackBufferBase),
      void(transform_feedback_name, uint_type, buffer_name)>
      transform_feedback_buffer_base;

    func<
      OGLPAFP(TransformFeedbackBufferRange),
      void(
        transform_feedback_name,
        uint_type,
        buffer_name,
        intptr_type,
        sizeiptr_type)>
      transform_feedback_buffer_range;

    query_func<
      mp_list<transform_feedback_name>,
      mp_list<transform_feedback_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetTransformFeedbackiv)>
      get_transform_feedback_i;

    query_func<
      mp_list<transform_feedback_name>,
      mp_list<transform_feedback_parameter>,
      mp_list<uint_type>,
      int_type,
      OGLPAFP(GetTransformFeedbacki_v)>
      get_transform_feedback_ii;

    query_func<
      mp_list<transform_feedback_name>,
      mp_list<transform_feedback_parameter>,
      mp_list<uint_type>,
      int64_type,
      OGLPAFP(GetTransformFeedbacki64_v)>
      get_transform_feedback_i64i;

    // query ops
    query_func<
      mp_list<query_target>,
      mp_list<query_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetQueryiv)>
      get_query_i;

    query_func<
      mp_list<query_target, uint_type>,
      mp_list<query_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetQueryIndexediv)>
      get_query_indexed_i;

    query_func<
      mp_list<query_name>,
      mp_list<query_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetQueryObjectiv)>
      get_query_object_i;

    query_func<
      mp_list<query_name>,
      mp_list<query_parameter>,
      mp_list<>,
      uint_type,
      OGLPAFP(GetQueryObjectuiv)>
      get_query_object_ui;

    query_func<
      mp_list<query_name>,
      mp_list<query_parameter>,
      mp_list<>,
      int64_type,
      OGLPAFP(GetQueryObjecti64v)>
      get_query_object_i64;

    query_func<
      mp_list<query_name>,
      mp_list<query_parameter>,
      mp_list<>,
      uint64_type,
      OGLPAFP(GetQueryObjectui64v)>
      get_query_object_ui64;

    func<
      OGLPAFP(GetQueryBufferObjectiv),
      void(query_name, buffer_name, query_parameter, intptr_type)>
      get_query_buffer_object_i;

    func<
      OGLPAFP(GetQueryBufferObjectuiv),
      void(query_name, buffer_name, query_parameter, intptr_type)>
      get_query_buffer_object_ui;

    func<
      OGLPAFP(GetQueryBufferObjecti64v),
      void(query_name, buffer_name, query_parameter, intptr_type)>
      get_query_buffer_object_i64;

    func<
      OGLPAFP(GetQueryBufferObjectui64v),
      void(query_name, buffer_name, query_parameter, intptr_type)>
      get_query_buffer_object_ui64;

    func<OGLPAFP(BeginQuery), void(query_target, query_name)> begin_query;

    func<OGLPAFP(BeginQueryIndexed), void(query_target, uint_type, query_name)>
      begin_query_indexed;

    func<OGLPAFP(EndQuery), void(query_target)> end_query;

    func<OGLPAFP(EndQueryIndexed), void(query_target, uint_type)>
      end_query_indexed;

    func<OGLPAFP(QueryCounter), void(query_name, counter_query_target)>
      query_counter;

    func<
      OGLPAFP(BeginConditionalRender),
      void(query_name, conditional_render_mode)>
      begin_conditional_render;

    func<OGLPAFP(EndConditionalRender)> end_conditional_render;

    // program pipeline ops
    func<OGLPAFP(BindProgramPipeline), void(program_pipeline_name)>
      bind_program_pipeline;

    func<OGLPAFP(ValidateProgramPipeline), void(program_pipeline_name)>
      validate_program_pipeline;

    func<
      OGLPAFP(UseProgramStages),
      void(program_pipeline_name, enum_bitfield<program_stage_bit>, program_name)>
      use_program_stages;

    query_func<
      mp_list<program_name, shader_type>,
      mp_list<program_stage_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetProgramStageiv)>
      get_program_stage_i;

    query_func<
      mp_list<program_name>,
      mp_list<program_pipeline_parameter>,
      mp_list<>,
      int_type,
      OGLPAFP(GetProgramPipelineiv)>
      get_program_pipeline_i;

    struct : func<OGLPAFP(GetProgramPipelineInfoLog)> {
        using func<OGLPAFP(GetProgramPipelineInfoLog)>::func;

        constexpr auto operator()(
          program_pipeline_name pipe,
          span<char_type> dest) const noexcept {
            sizei_type real_len{0};
            return this
              ->_chkcall(
                name_type(pipe), sizei_type(dest.size()), &real_len, dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_program_pipeline_info_log;

    func<OGLPAFP(ActiveShaderProgram), void(program_pipeline_name, program_name)>
      active_shader_program;

    // path NV ops
    struct : func<OGLPAFP(PathColorGenNV)> {
        using func<OGLPAFP(PathColorGenNV)>::func;

        constexpr auto operator()(
          path_color_nv clr,
          path_gen_mode_nv mode,
          path_color_format_nv fmt,
          span<const float_type> coords) const noexcept {
            return this->_cnvchkcall(clr, mode, fmt, coords.data());
        }
    } path_color_gen_nv;

    struct : func<OGLPAFP(PathGlyphRangeNV)> {
        using func<OGLPAFP(PathGlyphRangeNV)>::func;

        constexpr auto operator()(
          path_nv_name pth,
          path_font_target_nv tgt,
          string_view font_name,
          path_font_style_nv style,
          uint_type first,
          sizei_type count,
          path_missing_glyph_nv missing,
          uint_type param_tpl,
          float_type em_scale) const noexcept {
            return this->_cnvchkcall(
              pth,
              tgt,
              static_cast<const char*>(c_str(font_name)),
              style,
              first,
              count,
              missing,
              param_tpl,
              em_scale);
        }
    } path_glyph_range_nv;

    struct : func<OGLPAFP(GetPathSpacingNV)> {
        using func<OGLPAFP(GetPathSpacingNV)>::func;

        constexpr auto operator()(
          [[maybe_unused]] path_list_mode_nv mode,
          [[maybe_unused]] string_view glyphs,
          [[maybe_unused]] path_nv_name pth,
          [[maybe_unused]] float_type advance_scale,
          [[maybe_unused]] float_type kerning_scale,
          [[maybe_unused]] path_transform_type_nv transf,
          [[maybe_unused]] span<float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              mode,
              sizei_type(glyphs.size()),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              advance_scale,
              kerning_scale,
              transf,
              dst.data());
#else
            return this->_fake();
#endif
        }
    } get_path_spacing_nv;

    func<
      OGLPAFP(StencilFillPathNV),
      void(path_nv_name, path_fill_mode_nv, uint_type)>
      stencil_fill_path_nv;

    func<OGLPAFP(StencilStrokePathNV), void(path_nv_name, int_type, uint_type)>
      stencil_stroke_path_nv;

    struct : func<OGLPAFP(StencilFillPathInstancedNV)> {
        using func<OGLPAFP(StencilFillPathInstancedNV)>::func;
        constexpr auto operator()(
          [[maybe_unused]] string_view glyphs,
          [[maybe_unused]] path_nv_name pth,
          [[maybe_unused]] path_fill_mode_nv mode,
          [[maybe_unused]] uint_type mask,
          [[maybe_unused]] path_transform_type_nv transf,
          [[maybe_unused]] span<const float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              sizei_type(glyphs.size()),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              mode,
              mask,
              transf,
              dst.data());
#else
            return this->_fake();
#endif
        }
    } stencil_fill_path_instanced_nv;

    struct : func<OGLPAFP(StencilStrokePathInstancedNV)> {
        using func<OGLPAFP(StencilStrokePathInstancedNV)>::func;
        constexpr auto operator()(
          [[maybe_unused]] string_view glyphs,
          [[maybe_unused]] path_nv_name pth,
          [[maybe_unused]] int_type reference,
          [[maybe_unused]] uint_type mask,
          [[maybe_unused]] path_transform_type_nv transf,
          [[maybe_unused]] span<const float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              sizei_type(glyphs.size()),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              reference,
              mask,
              transf,
              dst.data());
#else
            return this->_fake();
#endif
        }
    } stencil_stroke_path_instanced_nv;

    func<OGLPAFP(CoverFillPathNV), void(path_nv_name, path_fill_cover_mode_nv)>
      cover_fill_path_nv;

    func<
      OGLPAFP(CoverStrokePathNV),
      void(path_nv_name, path_stroke_cover_mode_nv)>
      cover_stroke_path_nv;

    struct : func<OGLPAFP(CoverFillPathInstancedNV)> {
        using func<OGLPAFP(CoverFillPathInstancedNV)>::func;
        constexpr auto operator()(
          [[maybe_unused]] string_view glyphs,
          [[maybe_unused]] path_nv_name pth,
          [[maybe_unused]] path_fill_cover_mode_nv mode,
          [[maybe_unused]] path_transform_type_nv transf,
          [[maybe_unused]] span<const float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              sizei_type(glyphs.size()),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              mode,
              transf,
              dst.data());
#else
            return this->_fake();
#endif
        }
    } cover_fill_path_instanced_nv;

    struct : func<OGLPAFP(CoverStrokePathInstancedNV)> {
        using func<OGLPAFP(CoverStrokePathInstancedNV)>::func;
        constexpr auto operator()(
          [[maybe_unused]] string_view glyphs,
          [[maybe_unused]] path_nv_name pth,
          [[maybe_unused]] path_stroke_cover_mode_nv mode,
          [[maybe_unused]] path_transform_type_nv transf,
          [[maybe_unused]] span<const float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              sizei_type(glyphs.size()),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              mode,
              transf,
              dst.data());
#else
            return this->_fake();
#endif
        }
    } cover_stroke_path_instanced_nv;

    // draw parameters
    func<OGLPAFP(PrimitiveRestartIndex)> primitive_restart_index;

    func<OGLPAFP(ProvokingVertex), void(provoke_mode)> provoking_vertex;

    func<OGLPAFP(PointSize)> point_size;
    func<OGLPAFP(LineWidth)> line_width;

    func<OGLPAFP(PointParameteri), void(point_parameter, int_type)>
      point_parameter_i;

    func<OGLPAFP(PointParameterf), void(point_parameter, float_type)>
      point_parameter_f;

    func<OGLPAFP(PatchParameteri), void(patch_parameter, int_type)>
      patch_parameter_i;

    func<OGLPAFP(PatchParameterfv), void(patch_parameter, span<const float_type>)>
      patch_parameter_fv;

    func<OGLPAFP(FrontFace), void(face_orientation)> front_face;
    func<OGLPAFP(CullFace), void(face_mode)> cull_face;

    func<OGLPAFP(PolygonMode), void(face_mode, oglplus::polygon_mode)>
      polygon_mode;

    func<OGLPAFP(PolygonOffset)> polygon_offset;
    func<OGLPAFP(PolygonOffsetClamp)> polygon_offset_clamp;

    func<OGLPAFP(BlendEquation), void(oglplus::blend_equation)> blend_equation;
    func<
      OGLPAFP(BlendEquation),
      void(oglplus::blend_equation, oglplus::blend_equation)>
      blend_equation_separate;

    func<OGLPAFP(BlendEquation), void(uint_type, oglplus::blend_equation)>
      blend_equationi;
    func<
      OGLPAFP(BlendEquation),
      void(uint_type, oglplus::blend_equation, oglplus::blend_equation)>
      blend_equation_separatei;

    func<
      OGLPAFP(BlendFunc),
      void(oglplus::blend_function, oglplus::blend_function)>
      blend_func;

    func<
      OGLPAFP(BlendFunc),
      void(
        oglplus::blend_function,
        oglplus::blend_function,
        oglplus::blend_function,
        oglplus::blend_function)>
      blend_func_separate;

    func<
      OGLPAFP(BlendFunc),
      void(uint_type, oglplus::blend_function, oglplus::blend_function)>
      blend_funci;

    func<
      OGLPAFP(BlendFunc),
      void(
        uint_type,
        oglplus::blend_function,
        oglplus::blend_function,
        oglplus::blend_function,
        oglplus::blend_function)>
      blend_func_separatei;

    func<OGLPAFP(SampleCoverage)> sample_coverage;
    func<OGLPAFP(SampleMaski)> sample_mask_i;
    func<OGLPAFP(MinSampleShading)> min_sample_shading;

    query_func<
      mp_list<>,
      mp_list<sample_parameter>,
      mp_list<uint_type>,
      float_type,
      OGLPAFP(GetMultisamplefv)>
      get_multisample_f;

    // drawing
    // arrays
    func<OGLPAFP(DrawArrays), void(primitive_type, int_type, sizei_type)>
      draw_arrays;

    func<
      OGLPAFP(DrawArraysInstancedBaseInstance),
      void(primitive_type, int_type, sizei_type, sizei_type, uint_type)>
      draw_arrays_instanced_base_instance;

    func<
      OGLPAFP(DrawArraysInstanced),
      void(primitive_type, int_type, sizei_type, sizei_type)>
      draw_arrays_instanced;

    func<OGLPAFP(DrawArraysIndirect), void(primitive_type, const_void_ptr_type)>
      draw_arrays_indirect;

    func<
      OGLPAFP(MultiDrawArrays),
      void(primitive_type, const int_type*, const sizei_type*, sizei_type)>
      multi_draw_arrays;

    func<
      OGLPAFP(MultiDrawArraysIndirect),
      void(primitive_type, const_void_ptr_type, sizei_type, sizei_type)>
      multi_draw_arrays_indirect;

    func<
      OGLPAFP(MultiDrawArraysIndirectCount),
      void(primitive_type, const_void_ptr_type, intptr_type, sizei_type, sizei_type)>
      multi_draw_arrays_indirect_count;

    // elements
    func<
      OGLPAFP(DrawElements),
      void(primitive_type, sizei_type, index_data_type, const_void_ptr_type)>
      draw_elements;

    func<
      OGLPAFP(DrawRangeElements),
      void(
        primitive_type,
        uint_type,
        uint_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type)>
      draw_range_elements;

    func<
      OGLPAFP(DrawElementsInstancedBaseInstance),
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        sizei_type,
        uint_type)>
      draw_elements_instanced_base_instance;

    func<
      OGLPAFP(DrawElementsInstanced),
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        sizei_type)>
      draw_elements_instanced;

    func<
      OGLPAFP(DrawElementsIndirect),
      void(primitive_type, index_data_type, const_void_ptr_type)>
      draw_elements_indirect;

    func<
      OGLPAFP(DrawElementsBaseVertex),
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        int_type)>
      draw_elements_base_vertex;

    func<
      OGLPAFP(DrawRangeElements),
      void(
        primitive_type,
        uint_type,
        uint_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        int_type)>
      draw_range_elements_base_vertex;

    func<
      OGLPAFP(DrawElementsInstancedBaseVertex),
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        sizei_type,
        int_type)>
      draw_elements_instanced_base_vertex;

    func<
      OGLPAFP(DrawElementsInstancedBaseVertexBaseInstance),
      void(
        primitive_type,
        sizei_type,
        index_data_type,
        const_void_ptr_type,
        sizei_type,
        int_type,
        uint_type)>
      draw_elements_instanced_base_vertex_base_instance;

    // computing
    func<OGLPAFP(DispatchCompute)> dispatch_compute;
    func<OGLPAFP(DispatchComputeIndirect)> dispatch_compute_indirect;

    // pixel transfer
    func<
      OGLPAFP(ReadPixels),
      void(
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::block)>
      read_pixels;

    // get_integer
    query_func<
      mp_list<>,
      mp_list<integer_query, binding_query>,
      mp_list<>,
      int_type,
      OGLPAFP(GetIntegerv)>
      get_integer;

    // get_integer64
    query_func<
      mp_list<>,
      mp_list<integer_query>,
      mp_list<>,
      int64_type,
      OGLPAFP(GetInteger64v)>
      get_integer64;

    // get_float
    query_func<
      mp_list<>,
      mp_list<float_query>,
      mp_list<>,
      float_type,
      OGLPAFP(GetFloatv)>
      get_float;

    // get_double
    query_func<
      mp_list<>,
      mp_list<float_query>,
      mp_list<>,
      double_type,
      OGLPAFP(GetDoublev)>
      get_double;

    // get_string
    struct : func<OGLPAFP(GetString)> {
        using func<OGLPAFP(GetString)>::func;

        constexpr auto operator()(string_query query) const noexcept {
            return this->_cnvchkcall(query).transformed(
              [](auto src, bool valid) {
                  return valid && src
                           ? string_view{reinterpret_cast<const char*>(src)}
                           : string_view{};
              });
        }

        constexpr auto operator()() const noexcept {
            return this->fake_empty_c_str().cast_to(
              type_identity<string_view>{});
        }
    } get_string;

    // get_strings
    auto get_strings(string_query query, char separator) const noexcept {
        return get_string(query).transformed([separator](auto src, bool) {
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
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
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
    adapted_function<
      &gl_api::NamedString,
      void(named_string_kind, string_view, string_view)>
      named_string{*this};

    adapted_function<&gl_api::DeleteNamedString, void(string_view)>
      delete_named_string{*this};

    adapted_function<&gl_api::IsNamedString, true_false(string_view)>
      is_named_string{*this};

    // arb compatibility
    adapted_function<&gl_api::Begin, void(old_primitive_type)> begin{*this};
    adapted_function<&gl_api::End> end{*this};

    adapted_function<&gl_api::Vertex2i> vertex2i{*this};
    adapted_function<&gl_api::Vertex3i> vertex3i{*this};
    adapted_function<&gl_api::Vertex4i> vertex4i{*this};
    adapted_function<&gl_api::Vertex2f> vertex2f{*this};
    adapted_function<&gl_api::Vertex3f> vertex3f{*this};
    adapted_function<&gl_api::Vertex4f> vertex4f{*this};

    adapted_function<&gl_api::Color3i> color3i{*this};
    adapted_function<&gl_api::Color4i> color4i{*this};
    adapted_function<&gl_api::Color3f> color3f{*this};
    adapted_function<&gl_api::Color4f> color4f{*this};

    adapted_function<&gl_api::SecondaryColor3i> secondary_color3i{*this};
    adapted_function<&gl_api::SecondaryColor4i> csecondary_olor4i{*this};
    adapted_function<&gl_api::SecondaryColor3f> csecondary_olor3f{*this};
    adapted_function<&gl_api::SecondaryColor4f> csecondary_olor4f{*this};

    adapted_function<&gl_api::TexCoord1i> tex_coord1i{*this};
    adapted_function<&gl_api::TexCoord2i> tex_coord2i{*this};
    adapted_function<&gl_api::TexCoord3i> tex_coord3i{*this};
    adapted_function<&gl_api::TexCoord4i> tex_coord4i{*this};
    adapted_function<&gl_api::TexCoord1f> tex_coord1f{*this};
    adapted_function<&gl_api::TexCoord2f> tex_coord2f{*this};
    adapted_function<&gl_api::TexCoord3f> tex_coord3f{*this};
    adapted_function<&gl_api::TexCoord4f> tex_coord4f{*this};

    adapted_function<&gl_api::MultiTexCoord1i, void(texture_unit, int_type)>
      multi_tex_coord1i{*this};
    adapted_function<
      &gl_api::MultiTexCoord2i,
      void(texture_unit, int_type, int_type)>
      multi_tex_coord2i{*this};
    adapted_function<
      &gl_api::MultiTexCoord3i,
      void(texture_unit, int_type, int_type, int_type)>
      multi_tex_coord3i{*this};
    adapted_function<
      &gl_api::MultiTexCoord4i,
      void(texture_unit, int_type, int_type, int_type, int_type)>
      multi_tex_coord4i{*this};

    adapted_function<&gl_api::MultiTexCoord1f, void(texture_unit, float_type)>
      multi_tex_coord1f{*this};
    adapted_function<
      &gl_api::MultiTexCoord2f,
      void(texture_unit, float_type, float_type)>
      multi_tex_coord2f{*this};
    adapted_function<
      &gl_api::MultiTexCoord3f,
      void(texture_unit, float_type, float_type, float_type)>
      multi_tex_coord3f{*this};
    adapted_function<
      &gl_api::MultiTexCoord4f,
      void(texture_unit, float_type, float_type, float_type, float_type)>
      multi_tex_coord4f{*this};

    adapted_function<&gl_api::MatrixMode, void(matrix_mode)> matrix_mode{*this};
    adapted_function<&gl_api::PushMatrix> push_matrix{*this};
    adapted_function<&gl_api::PopMatrix> pop_matrix{*this};

    adapted_function<&gl_api::LoadIdentity> load_identity{*this};

    adapted_function<&gl_api::Translatef> translate_f{*this};
    adapted_function<&gl_api::Translated> translate_d{*this};

    adapted_function<
      &gl_api::Rotatef,
      void(degrees_t<float_type>, float_type, float_type, float_type)>
      rotate_f{*this};

    adapted_function<
      &gl_api::Rotated,
      void(degrees_t<double_type>, double_type, double_type, double_type)>
      rotate_d{*this};

    adapted_function<&gl_api::Scalef> scale_f{*this};
    adapted_function<&gl_api::Scaled> scale_d{*this};

    adapted_function<&gl_api::Frustum> frustum{*this};
    adapted_function<&gl_api::Ortho> ortho{*this};

    adapted_function<&gl_api::LoadMatrixf> load_matrix_f{*this};
    adapted_function<&gl_api::LoadMatrixd> load_matrix_d{*this};

    adapted_function<&gl_api::MultMatrixf> mult_matrix_f{*this};
    adapted_function<&gl_api::MultMatrixd> mult_matrix_d{*this};

    adapted_function<&gl_api::LoadTransposeMatrixf> load_transpose_matrix_f{
      *this};
    adapted_function<&gl_api::LoadTransposeMatrixd> load_transpose_matrix_d{
      *this};

    adapted_function<&gl_api::MultTransposeMatrixf> mult_transpose_matrix_f{
      *this};
    adapted_function<&gl_api::MultTransposeMatrixd> mult_transpose_matrix_d{
      *this};

    c_api::combined<
      adapted_function<
        &gl_api::DebugMessageControl,
        void(
          debug_output_source,
          debug_output_type,
          debug_output_severity,
          c_api::substituted<0>,
          c_api::substituted<nullptr>,
          true_false)>,
      adapted_function<
        &gl_api::DebugMessageControl,
        void(
          debug_output_source,
          debug_output_type,
          debug_output_severity,
          span<const uint_type>,
          true_false)>>
      debug_message_control{*this};

    adapted_function<
      &gl_api::DebugMessageInsert,
      void(
        debug_output_source,
        debug_output_type,
        debug_output_severity,
        uint_type,
        string_view)>
      debug_message_insert{*this};

    using _debug_message_callback_t = adapted_function<
      &gl_api::DebugMessageCallback,
      void(debug_callback_type*, const_void_ptr_type)>;

    struct : _debug_message_callback_t {
        using base = _debug_message_callback_t;
        using base::base;
        using base::operator();

        template <typename Log>
        requires(std::is_same_v<Log, gl_debug_logger>) constexpr auto operator()(
          const Log& log) const noexcept {
            return base::operator()(log.callback(), log.data());
        }
    } debug_message_callback{*this};

    adapted_function<
      &gl_api::PushDebugGroup,
      void(debug_output_source, uint_type, string_view)>
      push_debug_group{*this};

    adapted_function<&gl_api::PopDebugGroup> pop_debug_group{*this};

    using _object_label_t = adapted_function<
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

    adapted_function<&gl_api::Flush> flush{*this};
    adapted_function<&gl_api::Finish> finish{*this};

    basic_gl_operations(api_traits& traits);
};
//------------------------------------------------------------------------------
#undef OGLPAFP
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

#endif // EAGINE_OGLPLUS_GL_API_API_HPP
