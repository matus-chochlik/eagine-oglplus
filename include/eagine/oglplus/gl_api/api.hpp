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
#include <eagine/oglplus/utils/buffer_data.hpp>
#include <eagine/quantities.hpp>
#include <eagine/scope_exit.hpp>
#include <eagine/string_list.hpp>

namespace eagine::oglplus {
//------------------------------------------------------------------------------
#define OGLPAFP(FUNC) decltype(c_api::FUNC), &c_api::FUNC
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
    using c_api = basic_gl_c_api<ApiTraits>;

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

    using debug_callback_type = typename c_api::debug_callback_type;

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
    constexpr auto type_of(buffer_name) const noexcept {
#ifdef GL_BUFFER
        return object_type(GL_BUFFER);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(framebuffer_name) const noexcept {
#ifdef GL_FRAMEBUFFER
        return object_type(GL_FRAMEBUFFER);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(program_pipeline_name) const noexcept {
#ifdef GL_PROGRAM_PIPELINE
        return object_type(GL_PROGRAM_PIPELINE);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(program_name) const noexcept {
#ifdef GL_PROGRAM
        return object_type(GL_PROGRAM);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(query_name) const noexcept {
#ifdef GL_QUERY
        return object_type(GL_QUERY);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(renderbuffer_name) const noexcept {
#ifdef GL_RENDERBUFFER
        return object_type(GL_RENDERBUFFER);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(sampler_name) const noexcept {
#ifdef GL_SAMPLER
        return object_type(GL_SAMPLER);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(shader_name) const noexcept {
#ifdef GL_SHADER
        return object_type(GL_SHADER);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(texture_name) const noexcept {
#ifdef GL_TEXTURE
        return object_type(GL_TEXTURE);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(transform_feedback_name) const noexcept {
#ifdef GL_TRANSFORM_FEEDBACK
        return object_type(GL_TRANSFORM_FEEDBACK);
#else
        return object_type(0);
#endif
    }

    constexpr auto type_of(vertex_array_name) const noexcept {
#ifdef GL_VERTEX_ARRAY
        return object_type(GL_VERTEX_ARRAY);
#else
        return object_type(0);
#endif
    }

    template <typename W, W c_api::*F, typename Signature = typename W::signature>
    class func;

    template <typename W, W c_api::*F, typename RVC, typename... Params>
    class func<W, F, RVC(Params...)>
      : public wrapped_c_api_function<c_api, api_traits, nothing_t, W, F> {
        using base = wrapped_c_api_function<c_api, api_traits, nothing_t, W, F>;

    public:
        using base::base;

        constexpr auto operator()(Params... params) const noexcept {
            return this->_chkcall(_conv(params)...)
              .cast_to(type_identity<RVC>{});
        }

        auto bind(Params... params) const noexcept {
            return [=] {
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

    template <typename W, W c_api::*F, typename Signature = typename W::signature>
    class unck_func;

    template <typename W, W c_api::*F, typename RVC, typename... Params>
    class unck_func<W, F, RVC(Params...)>
      : public wrapped_c_api_function<c_api, api_traits, nothing_t, W, F> {
        using base = wrapped_c_api_function<c_api, api_traits, nothing_t, W, F>;

    public:
        using base::base;

        constexpr auto operator()(Params... params) const noexcept {
            return this->_call(_conv(params)...).cast_to(type_identity<RVC>{});
        }

        auto bind(Params... params) const noexcept {
            return [=] {
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
      W c_api::*F>
    struct query_func;

    template <
      typename... PreParams,
      typename... QueryClasses,
      typename... PostParams,
      typename QueryResult,
      typename W,
      W c_api::*F>
    struct query_func<
      mp_list<PreParams...>,
      mp_list<QueryClasses...>,
      mp_list<PostParams...>,
      QueryResult,
      W,
      F> : func<W, F> {
        using func<W, F>::func;

        template <
          typename Query,
          typename = std::enable_if_t<
            (true || ... || is_enum_class_value_v<QueryClasses, Query>)>,
          typename = std::enable_if_t<!std::is_array_v<typename Query::tag_type>>>
        constexpr auto operator()(
          PreParams... pre_params,
          Query query,
          PostParams... post_params) const noexcept {
            using RV = typename Query::tag_type;
            QueryResult result{};
            return this
              ->_cnvchkcall(
                pre_params..., enum_type(query), post_params..., &result)
              .replaced_with(result)
              .cast_to(type_identity<RV>{});
        }

        template <
          typename Query,
          typename = std::enable_if_t<
            (true || ... || is_enum_class_value_v<QueryClasses, Query>)>>
        auto operator()(
          PreParams... pre_params,
          Query query,
          PostParams... post_params,
          span<QueryResult> dest) const noexcept {
            EAGINE_ASSERT(dest.size());
            return this->_cnvchkcall(
              pre_params..., enum_type(query), post_params..., dest.data());
        }
    };

    // generate / create objects
    struct : func<OGLPAFP(FenceSync)> {
        using func<OGLPAFP(FenceSync)>::func;

        constexpr auto operator()(sync_condition cond) const noexcept {
            return this->_cnvchkcall(cond, bitfield_type(0));
        }

        constexpr auto operator()(
          sync_condition cond,
          enum_bitfield<sync_flag_bit> flags) const noexcept {
            return this->_cnvchkcall(cond, bitfield_type(flags));
        }
    } fence_sync;

    template <typename ObjTag, typename W, W c_api::*GenObjects>
    struct make_object_func : func<W, GenObjects> {
        using func<W, GenObjects>::func;

        constexpr auto operator()(span<name_type> names) const noexcept {
            return this->_chkcall(sizei_type(names.size()), names.data());
        }

        constexpr auto operator()(
          gl_object_name_span<gl_object_name<ObjTag>> names) const noexcept {
            return (*this)(names.raw_handles());
        }

        constexpr auto operator()() const noexcept {
            name_type n{};
            return this->_chkcall(1, &n).replaced_with(n).cast_to(
              type_identity<gl_owned_object_name<ObjTag>>{});
        }
    };

    struct : func<OGLPAFP(CreateShader)> {
        using func<OGLPAFP(CreateShader)>::func;

        constexpr auto operator()(shader_type type) const noexcept {
            return this->_cnvchkcall(type).cast_to(
              type_identity<owned_shader_name>{});
        }
    } create_shader;

    struct : func<OGLPAFP(CreateProgram)> {
        using func<OGLPAFP(CreateProgram)>::func;

        constexpr auto operator()() const noexcept {
            return this->_chkcall().cast_to(
              type_identity<owned_program_name>{});
        }
    } create_program;

    make_object_func<buffer_tag, OGLPAFP(GenBuffers)> gen_buffers;

    make_object_func<buffer_tag, OGLPAFP(CreateBuffers)> create_buffers;

    make_object_func<framebuffer_tag, OGLPAFP(GenFramebuffers)> gen_framebuffers;

    make_object_func<framebuffer_tag, OGLPAFP(CreateFramebuffers)>
      create_framebuffers;

    make_object_func<program_pipeline_tag, OGLPAFP(GenProgramPipelines)>
      gen_program_pipelines;

    make_object_func<program_pipeline_tag, OGLPAFP(CreateProgramPipelines)>
      create_program_pipelines;

    make_object_func<query_tag, OGLPAFP(GenQueries)> gen_queries;

    make_object_func<query_tag, OGLPAFP(CreateQueries)> create_queries;

    make_object_func<renderbuffer_tag, OGLPAFP(GenRenderbuffers)>
      gen_renderbuffers;

    make_object_func<renderbuffer_tag, OGLPAFP(CreateRenderbuffers)>
      create_renderbuffers;

    make_object_func<sampler_tag, OGLPAFP(GenSamplers)> gen_samplers;

    make_object_func<sampler_tag, OGLPAFP(CreateSamplers)> create_samplers;

    make_object_func<texture_tag, OGLPAFP(GenTextures)> gen_textures;

    make_object_func<texture_tag, OGLPAFP(CreateTextures)> create_textures;

    make_object_func<transform_feedback_tag, OGLPAFP(GenTransformFeedbacks)>
      gen_transform_feedbacks;

    make_object_func<transform_feedback_tag, OGLPAFP(CreateTransformFeedbacks)>
      create_transform_feedbacks;

    make_object_func<vertex_array_tag, OGLPAFP(GenVertexArrays)>
      gen_vertex_arrays;

    make_object_func<vertex_array_tag, OGLPAFP(CreateVertexArrays)>
      create_vertex_arrays;

    struct : func<OGLPAFP(GenPathsNV)> {
        using func<OGLPAFP(GenPathsNV)>::func;

        constexpr auto operator()(sizei_type count = 1) const noexcept {
            return this->_chkcall(count).cast_to(
              type_identity<owned_path_nv_name>{});
        }
    } create_paths_nv;

    // delete objects
    struct : func<OGLPAFP(DeleteSync)> {
        using func<OGLPAFP(DeleteSync)>::func;

        constexpr auto operator()(sync_type sync) const noexcept {
            return this->_chkcall(sync);
        }

        auto bind(sync_type sync) const noexcept {
            return [this, sync] {
                return (*this)(sync);
            };
        }

        auto later_by(cleanup_group& cleanup, sync_type sync) const -> auto& {
            return cleanup.add_ret(bind(sync));
        }

        auto raii(sync_type& sync) const noexcept {
            return eagine::finally(bind(sync));
        }
    } delete_sync;

    template <typename ObjTag, typename W, W c_api::*DeleteObjects>
    struct delete_object_func : func<W, DeleteObjects> {
        using func<W, DeleteObjects>::func;

        constexpr auto operator()(span<const name_type> names) const noexcept {
            return this->_chkcall(sizei_type(names.size()), names.data());
        }

        constexpr auto operator()(
          gl_object_name_view<gl_object_name<ObjTag>> names) const noexcept {
            return (*this)(names.raw_handles());
        }

        constexpr auto operator()(
          gl_owned_object_name<ObjTag> name) const noexcept {
            auto n = name.release();
            return this->_chkcall(1, &n);
        }

        auto bind(gl_owned_object_name<ObjTag>& name) const noexcept {
            return [this, &name] {
                (*this)(std::move(name));
            };
        }

        auto later_by(
          cleanup_group& cleanup,
          gl_owned_object_name<ObjTag>& name) const -> auto& {
            return cleanup.add_ret(bind(name));
        }

        auto raii(gl_owned_object_name<ObjTag>& name) const noexcept {
            return eagine::finally(bind(name));
        }
    };

    struct : func<OGLPAFP(DeleteShader)> {
        using func<OGLPAFP(DeleteShader)>::func;

        constexpr auto operator()(owned_shader_name name) const noexcept {
            return this->_chkcall(name.release());
        }

        auto bind(owned_shader_name& name) const noexcept {
            return [this, &name] {
                return (*this)(std::move(name));
            };
        }

        auto later_by(cleanup_group& cleanup, owned_shader_name& name) const
          -> auto& {
            return cleanup.add_ret(bind(name));
        }

        auto raii(owned_shader_name& name) const noexcept {
            return eagine::finally(bind(name));
        }
    } delete_shader;

    struct : func<OGLPAFP(DeleteProgram)> {
        using func<OGLPAFP(DeleteProgram)>::func;

        constexpr auto operator()(owned_program_name name) const noexcept {
            return this->_chkcall(name.release());
        }

        auto bind(owned_program_name& name) const noexcept {
            return [this, &name] {
                return (*this)(std::move(name));
            };
        }

        auto later_by(cleanup_group& cleanup, owned_program_name& name) const
          -> auto& {
            return cleanup.add_ret(bind(name));
        }

        auto raii(owned_program_name& name) const noexcept {
            return eagine::finally(bind(name));
        }
    } delete_program;

    delete_object_func<buffer_tag, OGLPAFP(DeleteBuffers)> delete_buffers;

    delete_object_func<framebuffer_tag, OGLPAFP(DeleteFramebuffers)>
      delete_framebuffers;

    delete_object_func<program_pipeline_tag, OGLPAFP(DeleteProgramPipelines)>
      delete_program_pipelines;

    delete_object_func<query_tag, OGLPAFP(DeleteQueries)> delete_queries;

    delete_object_func<renderbuffer_tag, OGLPAFP(DeleteRenderbuffers)>
      delete_renderbuffers;

    delete_object_func<sampler_tag, OGLPAFP(DeleteSamplers)> delete_samplers;

    delete_object_func<texture_tag, OGLPAFP(DeleteTextures)> delete_textures;

    delete_object_func<transform_feedback_tag, OGLPAFP(DeleteTransformFeedbacks)>
      delete_transform_feedbacks;

    delete_object_func<vertex_array_tag, OGLPAFP(DeleteVertexArrays)>
      delete_vertex_arrays;

    struct : func<OGLPAFP(DeletePathsNV)> {
        using func<OGLPAFP(DeletePathsNV)>::func;

        auto bind(owned_path_nv_name& name, sizei_type count = 1)
          const noexcept {
            return [this, &name, count] {
                (*this)(std::move(name), count);
            };
        }

        constexpr auto operator()(owned_path_nv_name name, sizei_type count = 1)
          const noexcept {
            return this->_chkcall(name.release(), count);
        }

        auto raii(owned_path_nv_name& name, sizei_type count = 1)
          const noexcept {
            return eagine::finally(bind(name, count));
        }
    } delete_paths_nv;

    // is_object
    func<OGLPAFP(IsSync), true_false(sync_type)> is_sync;

    template <typename ObjTag, typename W, W c_api::*IsObject>
    using is_object_func =
      func<W, IsObject, true_false(gl_object_name<ObjTag>)>;

    is_object_func<buffer_tag, OGLPAFP(IsBuffer)> is_buffer;

    is_object_func<framebuffer_tag, OGLPAFP(IsFramebuffer)> is_framebuffer;

    is_object_func<program_pipeline_tag, OGLPAFP(IsProgramPipeline)>
      is_program_pipeline;

    is_object_func<program_tag, OGLPAFP(IsProgram)> is_program;

    is_object_func<query_tag, OGLPAFP(IsQuery)> is_query;

    is_object_func<renderbuffer_tag, OGLPAFP(IsRenderbuffer)> is_renderbuffer;

    is_object_func<sampler_tag, OGLPAFP(IsSampler)> is_sampler;

    is_object_func<shader_tag, OGLPAFP(IsShader)> is_shader;

    is_object_func<texture_tag, OGLPAFP(IsTexture)> is_texture;

    is_object_func<transform_feedback_tag, OGLPAFP(IsTransformFeedback)>
      is_transform_feedback;

    is_object_func<vertex_array_tag, OGLPAFP(IsVertexArray)> is_vertex_array;

    is_object_func<path_nv_tag, OGLPAFP(IsPathNV)> is_path_nv;

    // enable
    func<OGLPAFP(Enable), void(capability)> enable;
    func<OGLPAFP(Enablei), void(capability, uint_type)> enablei;

    // disable
    func<OGLPAFP(Disable), void(capability)> disable;
    func<OGLPAFP(Disablei), void(capability, uint_type)> disablei;

    // is_enabled
    func<OGLPAFP(IsEnabled), true_false(capability)> is_enabled;
    func<OGLPAFP(IsEnabledi), true_false(capability, uint_type)> is_enabledi;

    // memory barrier
    func<OGLPAFP(MemoryBarrier), void(enum_bitfield<memory_barrier_bit>)>
      memory_barrier;

    func<OGLPAFP(MemoryBarrierByRegion), void(enum_bitfield<memory_barrier_bit>)>
      memory_barrier_by_region;

    // viewport
    struct : func<OGLPAFP(Viewport)> {
        using base = func<OGLPAFP(Viewport)>;

        using base::base;
        using base::operator();

        constexpr auto operator()(sizei_type w, sizei_type h) const noexcept {
            return base::operator()(0, 0, w, h);
        }

        constexpr auto operator()(
          std::tuple<sizei_type, sizei_type> wh) const noexcept {
            return base::operator()(0, 0, std::get<0>(wh), std::get<1>(wh));
        }

        constexpr auto operator()(
          std::tuple<int_type, int_type, sizei_type, sizei_type> c)
          const noexcept {
            return base::operator()(
              std::get<0>(c), std::get<1>(c), std::get<2>(c), std::get<3>(c));
        }
    } viewport;

    // stencil func
    func<OGLPAFP(StencilFunc), void(compare_function, int_type, uint_type)>
      stencil_func;

    func<
      OGLPAFP(StencilFuncSeparate),
      void(face_mode, compare_function, int_type, uint_type)>
      stencil_func_separate;

    // stencil op
    func<
      OGLPAFP(StencilOp),
      void(stencil_operation, stencil_operation, stencil_operation)>
      stencil_op;

    func<
      OGLPAFP(StencilOpSeparate),
      void(face_mode, stencil_operation, stencil_operation, stencil_operation)>
      stencil_op_separate;

    // depth func
    func<OGLPAFP(DepthFunc), void(compare_function)> depth_func;

    // buffer masks
    func<OGLPAFP(ColorMask), void(true_false, true_false, true_false, true_false)>
      color_mask;

    func<
      OGLPAFP(ColorMaski),
      void(uint_type, true_false, true_false, true_false, true_false)>
      color_mask_i;

    func<OGLPAFP(DepthMask), void(true_false)> depth_mask;

    func<OGLPAFP(StencilMask), void(uint_type)> stencil_mask;

    func<OGLPAFP(StencilMaskSeparate), void(face_mode, uint_type)>
      stencil_mask_separate;

    // clear
    func<OGLPAFP(ClearColor)> clear_color;
    func<OGLPAFP(ClearDepth)> clear_depth;
    func<OGLPAFP(ClearStencil)> clear_stencil;
    func<OGLPAFP(Clear), void(enum_bitfield<buffer_clear_bit>)> clear;

    // shader ops
    struct : func<OGLPAFP(ShaderSource)> {
        using func<OGLPAFP(ShaderSource)>::func;

        constexpr auto operator()(
          shader_name shdr,
          const glsl_source_ref& source) const noexcept {
            return this->_chkcall(
              name_type(shdr), source.count(), source.parts(), source.lengths());
        }
    } shader_source;

    func<OGLPAFP(CompileShader), void(shader_name)> compile_shader;

    struct : func<OGLPAFP(CompileShaderInclude)> {
        using func<OGLPAFP(CompileShaderInclude)>::func;

        constexpr auto operator()(
          shader_name shdr,
          const glsl_source_ref& paths) const noexcept {
            return this->_chkcall(
              name_type(shdr), paths.count(), paths.parts(), paths.lengths());
        }
    } compile_shader_include;

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

    // program ops
    func<OGLPAFP(AttachShader), void(program_name, shader_name)> attach_shader;

    func<OGLPAFP(DetachShader), void(program_name, shader_name)> detach_shader;

    func<OGLPAFP(LinkProgram), void(program_name)> link_program;

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

    func<OGLPAFP(UseProgram), void(program_name)> use_program;

    func<
      OGLPAFP(GetProgramResourceIndex),
      uint_type(program_name, program_interface, string_view)>
      get_program_resource_index;

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

    func<
      OGLPAFP(GetProgramResourceLocation),
      program_resource_location(program_name, program_interface, string_view)>
      get_program_resource_location;

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
                props.size(),
                props.raw_enums().data(),
                dest.size(),
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
                props.size(),
                props.raw_enums().data(),
                dest.size(),
                &real_len,
                dest.data())
              .replaced_with(head(dest, span_size(real_len)));
        }
    } get_program_resource_f;

    func<
      OGLPAFP(BindAttribLocation),
      void(program_name, vertex_attrib_location, string_view)>
      bind_attrib_location;

    func<
      OGLPAFP(GetAttribLocation),
      vertex_attrib_location(program_name, string_view)>
      get_attrib_location;

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

    func<
      OGLPAFP(BindFragDataLocation),
      void(program_name, frag_data_location, string_view)>
      bind_frag_data_location;

    func<
      OGLPAFP(GetFragDataLocation),
      frag_data_location(program_name, string_view)>
      get_frag_data_location;

    func<OGLPAFP(GetFragDataIndex), int_type(program_name, string_view)>
      get_frag_data_index;

    func<
      OGLPAFP(BindFragDataLocationIndexed),
      void(program_name, uint_type, frag_data_location, string_view)>
      bind_frag_data_location_indexed;

    func<OGLPAFP(GetUniformLocation), uniform_location(program_name, string_view)>
      get_uniform_location;

    func<
      OGLPAFP(GetUniformBlockIndex),
      uniform_block_index(program_name, string_view)>
      get_uniform_block_index;

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

    func<
      OGLPAFP(GetSubroutineUniformLocation),
      subroutine_uniform_location(program_name, shader_type, string_view)>
      get_subroutine_uniform_location;

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

    func<
      OGLPAFP(GetSubroutineIndex),
      subroutine_location(program_name, shader_type, string_view)>
      get_subroutine_index;

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
                dest.size(),
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
            for(const auto [su, s] : subrs._bindings) {
                idcs[su.index()] = s.index();
            }
            return this->_cnvchkcall(
              shdr_type, limit_cast<sizei_type>(idcs.size()), idcs.data());
        }
    } uniform_subroutines;

    // uniform
    // uint
    func<OGLPAFP(Uniform1ui), void(uniform_location, uint_type)> uniform1ui;
    func<OGLPAFP(Uniform2ui), void(uniform_location, uint_type, uint_type)>
      uniform2ui;
    func<
      OGLPAFP(Uniform3ui),
      void(uniform_location, uint_type, uint_type, uint_type)>
      uniform3ui;
    func<
      OGLPAFP(Uniform4ui),
      void(uniform_location, uint_type, uint_type, uint_type, uint_type)>
      uniform4ui;

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
    func<OGLPAFP(Uniform1i), void(uniform_location, int_type)> uniform1i;
    func<OGLPAFP(Uniform2i), void(uniform_location, int_type, int_type)>
      uniform2i;
    func<OGLPAFP(Uniform3i), void(uniform_location, int_type, int_type, int_type)>
      uniform3i;
    func<
      OGLPAFP(Uniform4i),
      void(uniform_location, int_type, int_type, int_type, int_type)>
      uniform4i;

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
    func<OGLPAFP(Uniform1f), void(uniform_location, float_type)> uniform1f;
    func<OGLPAFP(Uniform2f), void(uniform_location, float_type, float_type)>
      uniform2f;
    func<
      OGLPAFP(Uniform3f),
      void(uniform_location, float_type, float_type, float_type)>
      uniform3f;
    func<
      OGLPAFP(Uniform4f),
      void(uniform_location, float_type, float_type, float_type, float_type)>
      uniform4f;

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
    func<
      OGLPAFP(ProgramUniform1ui),
      void(program_name, uniform_location, uint_type)>
      program_uniform1ui;

    func<
      OGLPAFP(ProgramUniform2ui),
      void(program_name, uniform_location, uint_type, uint_type)>
      program_uniform2ui;

    func<
      OGLPAFP(ProgramUniform3ui),
      void(program_name, uniform_location, uint_type, uint_type, uint_type)>
      program_uniform3ui;

    func<
      OGLPAFP(ProgramUniform4ui),
      void(
        program_name,
        uniform_location,
        uint_type,
        uint_type,
        uint_type,
        uint_type)>
      program_uniform4ui;

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
    func<
      OGLPAFP(ProgramUniform1i),
      void(program_name, uniform_location, int_type)>
      program_uniform1i;

    func<
      OGLPAFP(ProgramUniform2i),
      void(program_name, uniform_location, int_type, int_type)>
      program_uniform2i;

    func<
      OGLPAFP(ProgramUniform3i),
      void(program_name, uniform_location, int_type, int_type, int_type)>
      program_uniform3i;

    func<
      OGLPAFP(ProgramUniform4i),
      void(program_name, uniform_location, int_type, int_type, int_type, int_type)>
      program_uniform4i;

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
    func<
      OGLPAFP(ProgramUniform1f),
      void(program_name, uniform_location, float_type)>
      program_uniform1f;

    func<
      OGLPAFP(ProgramUniform2f),
      void(program_name, uniform_location, float_type, float_type)>
      program_uniform2f;

    func<
      OGLPAFP(ProgramUniform3f),
      void(program_name, uniform_location, float_type, float_type, float_type)>
      program_uniform3f;

    func<
      OGLPAFP(ProgramUniform4f),
      void(
        program_name,
        uniform_location,
        float_type,
        float_type,
        float_type,
        float_type)>
      program_uniform4f;

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

    // shader block ops
    func<
      OGLPAFP(UniformBlockBinding),
      void(program_name, uniform_block_index, uint_type)>
      uniform_block_binding;

    func<
      OGLPAFP(ShaderStorageBlockBinding),
      void(program_name, shader_storage_block_index, uint_type)>
      shader_storage_block_binding;

    // buffer ops
    func<OGLPAFP(BindBuffer), void(buffer_target, buffer_name)> bind_buffer;

    func<OGLPAFP(BindBufferBase), void(buffer_target, uint_type, buffer_name)>
      bind_buffer_base;

    func<
      OGLPAFP(BindBufferRange),
      void(buffer_target, uint_type, buffer_name, intptr_type, sizeiptr_type)>
      bind_buffer_range;

    struct : func<OGLPAFP(BufferStorage)> {
        using func<OGLPAFP(BufferStorage)>::func;

        constexpr auto operator()(
          buffer_target tgt,
          sizeiptr_type size,
          const_void_ptr_type data,
          enum_bitfield<buffer_storage_bit> flags) const noexcept {
            return this->_cnvchkcall(tgt, size, data, flags);
        }

        constexpr auto operator()(buffer_target tgt, sizeiptr_type size)
          const noexcept {
            return (*this)(tgt, size, nullptr, {});
        }

    } buffer_storage;

    struct : func<OGLPAFP(NamedBufferStorage)> {
        using func<OGLPAFP(NamedBufferStorage)>::func;

        constexpr auto operator()(
          buffer_name buf,
          sizeiptr_type size,
          const_void_ptr_type data,
          enum_bitfield<buffer_storage_bit> flags) const noexcept {
            return this->_cnvchkcall(buf, size, data, flags);
        }

        constexpr auto operator()(buffer_name buf, sizeiptr_type size)
          const noexcept {
            return (*this)(buf, size, nullptr, {});
        }
    } named_buffer_storage;

    struct : func<OGLPAFP(BufferData)> {
        using func<OGLPAFP(BufferData)>::func;

        constexpr auto operator()(
          buffer_target tgt,
          const buffer_data_spec& values,
          buffer_usage usg) const noexcept {
            return this->_cnvchkcall(
              tgt, sizei_type(values.size()), values.data(), usg);
        }
    } buffer_data;

    struct : func<OGLPAFP(NamedBufferData)> {
        using func<OGLPAFP(NamedBufferData)>::func;

        constexpr auto operator()(
          buffer_name buf,
          const buffer_data_spec& values,
          buffer_usage usg) const noexcept {
            return this->_cnvchkcall(
              buf, sizei_type(values.size()), values.data(), usg);
        }
    } named_buffer_data;

    struct : func<OGLPAFP(BufferSubData)> {
        using func<OGLPAFP(BufferSubData)>::func;

        constexpr auto operator()(
          buffer_target tgt,
          intptr_type offs,
          const buffer_data_spec& values) const noexcept {
            return this->_cnvchkcall(
              tgt, offs, sizei_type(values.size()), values.data());
        }
    } buffer_sub_data;

    struct : func<OGLPAFP(NamedBufferSubData)> {
        using func<OGLPAFP(NamedBufferSubData)>::func;

        constexpr auto operator()(
          buffer_name buf,
          intptr_type offs,
          const buffer_data_spec& values) const noexcept {
            return this->_cnvchkcall(
              buf, offs, sizei_type(values.size()), values.data());
        }
    } named_buffer_sub_data;

    struct : func<OGLPAFP(ClearBufferData)> {
        using func<OGLPAFP(ClearBufferData)>::func;

        constexpr auto operator()(
          buffer_target tgt,
          pixel_internal_format ifmt,
          pixel_format fmt,
          pixel_data_type type,
          const_void_ptr_type data) const noexcept {
            return this->_cnvchkcall(tgt, ifmt, fmt, type, data);
        }

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
    } clear_buffer_data;

    struct : func<OGLPAFP(ClearNamedBufferData)> {
        using func<OGLPAFP(ClearNamedBufferData)>::func;

        constexpr auto operator()(
          buffer_name buf,
          pixel_internal_format ifmt,
          pixel_format fmt,
          pixel_data_type type,
          const_void_ptr_type data) const noexcept {
            return this->_cnvchkcall(buf, ifmt, fmt, type, data);
        }

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
    } clear_named_buffer_data;

    struct : func<OGLPAFP(ClearBufferSubData)> {
        using func<OGLPAFP(ClearBufferSubData)>::func;

        constexpr auto operator()(
          buffer_target tgt,
          pixel_internal_format ifmt,
          intptr_type offs,
          sizeiptr_type size,
          pixel_format fmt,
          pixel_data_type type,
          const_void_ptr_type data) const noexcept {
            return this->_cnvchkcall(tgt, ifmt, offs, size, fmt, type, data);
        }

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
    } clear_buffer_sub_data;

    struct : func<OGLPAFP(ClearNamedBufferSubData)> {
        using func<OGLPAFP(ClearNamedBufferSubData)>::func;

        constexpr auto operator()(
          buffer_name buf,
          pixel_internal_format ifmt,
          intptr_type offs,
          sizeiptr_type size,
          pixel_format fmt,
          pixel_data_type type,
          const_void_ptr_type data) const noexcept {
            return this->_cnvchkcall(buf, ifmt, offs, size, fmt, type, data);
        }

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
    } clear_named_buffer_sub_data;

    func<
      OGLPAFP(MapBuffer),
      void_ptr_type(buffer_target, enum_bitfield<buffer_map_access_bit>)>
      map_buffer;

    func<
      OGLPAFP(MapNamedBuffer),
      void_ptr_type(buffer_name, enum_bitfield<buffer_map_access_bit>)>
      map_named_buffer;

    func<
      OGLPAFP(MapBufferRange),
      void_ptr_type(
        buffer_target,
        intptr_type,
        sizeiptr_type,
        enum_bitfield<buffer_map_access_bit>)>
      map_buffer_range;

    func<
      OGLPAFP(MapNamedBufferRange),
      void_ptr_type(
        buffer_name,
        intptr_type,
        sizeiptr_type,
        enum_bitfield<buffer_map_access_bit>)>
      map_named_buffer_range;

    func<
      OGLPAFP(FlushMappedBufferRange),
      void_ptr_type(buffer_target, intptr_type, sizeiptr_type)>
      flush_mapped_buffer_range;

    func<
      OGLPAFP(FlushMappedNamedBufferRange),
      void_ptr_type(buffer_name, intptr_type, sizeiptr_type)>
      flush_mapped_named_buffer_range;

    func<OGLPAFP(UnmapBuffer), void_ptr_type(buffer_target)> unmap_buffer;

    func<OGLPAFP(UnmapNamedBuffer), void_ptr_type(buffer_name)>
      unmap_named_buffer;

    func<OGLPAFP(InvalidateBufferData), void(buffer_name)>
      invalidate_buffer_data;

    func<
      OGLPAFP(InvalidateBufferData),
      void(buffer_name, intptr_type, sizeiptr_type)>
      invalidate_buffer_sub_data;

    func<
      OGLPAFP(CopyBufferSubData),
      void(buffer_target, buffer_target, intptr_type, intptr_type, sizeiptr_type)>
      copy_buffer_sub_data;

    func<
      OGLPAFP(CopyNamedBufferSubData),
      void(buffer_name, buffer_name, intptr_type, intptr_type, sizeiptr_type)>
      copy_named_buffer_sub_data;

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
    func<OGLPAFP(BindVertexArray), void(vertex_array_name)> bind_vertex_array;

    func<
      OGLPAFP(BindVertexBuffer),
      void(vertex_buffer_binding, buffer_name, intptr_type, sizei_type)>
      bind_vertex_buffer;

    func<
      OGLPAFP(VertexArrayVertexBuffer),
      void(
        vertex_array_name,
        vertex_buffer_binding,
        buffer_name,
        intptr_type,
        sizei_type)>
      vertex_array_vertex_buffer;

    func<OGLPAFP(VertexArrayElementBuffer), void(vertex_array_name, buffer_name)>
      vertex_array_element_buffer;

    func<OGLPAFP(EnableVertexAttribArray), void(vertex_attrib_location)>
      enable_vertex_attrib_array;

    func<
      OGLPAFP(EnableVertexArrayAttrib),
      void(vertex_array_name, vertex_attrib_location)>
      enable_vertex_array_attrib;

    func<OGLPAFP(DisableVertexAttribArray), void(vertex_attrib_location)>
      disable_vertex_attrib_array;

    func<
      OGLPAFP(DisableVertexArrayAttrib),
      void(vertex_array_name, vertex_attrib_location)>
      disable_vertex_array_attrib;

    func<
      OGLPAFP(VertexAttribFormat),
      void(vertex_attrib_location, int_type, data_type, true_false, uint_type)>
      vertex_attrib_format;

    func<
      OGLPAFP(VertexAttribIFormat),
      void(vertex_attrib_location, int_type, data_type, uint_type)>
      vertex_attrib_iformat;

    func<
      OGLPAFP(VertexAttribLFormat),
      void(vertex_attrib_location, int_type, data_type, uint_type)>
      vertex_attrib_lformat;

    func<
      OGLPAFP(VertexArrayAttribFormat),
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        true_false,
        uint_type)>
      vertex_array_attrib_format;

    func<
      OGLPAFP(VertexArrayAttribIFormat),
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        uint_type)>
      vertex_array_attrib_iformat;

    func<
      OGLPAFP(VertexArrayAttribLFormat),
      void(
        vertex_array_name,
        vertex_attrib_location,
        int_type,
        data_type,
        uint_type)>
      vertex_array_attrib_lformat;

    struct : func<OGLPAFP(VertexAttribPointer)> {
        using func<OGLPAFP(VertexAttribPointer)>::func;

        constexpr auto operator()(
          vertex_attrib_location loc,
          int_type size,
          data_type type,
          true_false norm) const noexcept {
            return this->_cnvchkcall(loc, size, type, norm, 0, nullptr);
        }

        constexpr auto operator()(
          vertex_attrib_location loc,
          int_type size,
          data_type type,
          true_false norm,
          sizei_type stride,
          const_void_ptr_type pointer) const noexcept {
            return this->_cnvchkcall(loc, size, type, norm, stride, pointer);
        }
    } vertex_attrib_pointer;

    struct : func<OGLPAFP(VertexAttribIPointer)> {
        using func<OGLPAFP(VertexAttribIPointer)>::func;

        constexpr auto operator()(
          vertex_attrib_location loc,
          int_type size,
          data_type type) const noexcept {
            return this->_cnvchkcall(loc, size, type, 0, nullptr);
        }

        constexpr auto operator()(
          vertex_attrib_location loc,
          int_type size,
          data_type type,
          sizei_type stride,
          const_void_ptr_type pointer) const noexcept {
            return this->_cnvchkcall(loc, size, type, stride, pointer);
        }
    } vertex_attrib_ipointer;

    struct : func<OGLPAFP(VertexAttribLPointer)> {
        using func<OGLPAFP(VertexAttribLPointer)>::func;

        constexpr auto operator()(
          vertex_attrib_location loc,
          int_type size,
          data_type type) const noexcept {
            return this->_cnvchkcall(loc, size, type, 0, nullptr);
        }

        constexpr auto operator()(
          vertex_attrib_location loc,
          int_type size,
          data_type type,
          sizei_type stride,
          const_void_ptr_type pointer) const noexcept {
            return this->_cnvchkcall(loc, size, type, stride, pointer);
        }
    } vertex_attrib_lpointer;

    func<
      OGLPAFP(VertexAttribBinding),
      void(vertex_attrib_location, vertex_buffer_binding)>
      vertex_attrib_binding;

    func<
      OGLPAFP(VertexArrayAttribBinding),
      void(vertex_array_name, vertex_attrib_location, vertex_buffer_binding)>
      vertex_array_attrib_binding;

    func<OGLPAFP(VertexBindingDivisor), void(vertex_buffer_binding, uint_type)>
      vertex_binding_divisor;

    func<
      OGLPAFP(VertexArrayBindingDivisor),
      void(vertex_buffer_binding, uint_type)>
      vertex_array_binding_divisor;

    func<OGLPAFP(VertexAttribDivisor), void(vertex_attrib_location, uint_type)>
      vertex_attrib_divisor;

    // texture ops
    func<OGLPAFP(ActiveTexture), void(texture_unit)> active_texture;
    func<OGLPAFP(BindTexture), void(texture_target, texture_name)> bind_texture;

    struct : func<OGLPAFP(BindTextures), void(uint_type, sizei_type, const name_type*)> {
        using base = func<
          OGLPAFP(BindTextures),
          void(uint_type, sizei_type, const name_type*)>;

        using base::base;

        constexpr auto operator()(uint_type first, span<const name_type> texs)
          const noexcept {
            return base::operator()(
              first, sizei_type(texs.size()), texs.data());
        }
    } bind_textures;

    func<OGLPAFP(BindTextureUnit), void(uint_type, texture_name)>
      bind_texture_unit;

    func<
      OGLPAFP(BindImageTexture),
      void(
        uint_type,
        texture_name,
        int_type,
        true_false,
        int_type,
        access_specifier,
        image_unit_format)>
      bind_image_texture;

    func<
      OGLPAFP(TexStorage3D),
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type)>
      tex_storage3d;

    func<
      OGLPAFP(TextureStorage3D),
      void(
        texture_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type)>
      texture_storage3d;

    func<
      OGLPAFP(TexStorage2D),
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      tex_storage2d;

    func<
      OGLPAFP(TextureStorage2D),
      void(texture_name, sizei_type, pixel_internal_format, sizei_type, sizei_type)>
      texture_storage2d;

    func<
      OGLPAFP(TexStorage1D),
      void(texture_target, sizei_type, pixel_internal_format, sizei_type)>
      tex_storage1d;

    func<
      OGLPAFP(TextureStorage1D),
      void(texture_name, sizei_type, pixel_internal_format, sizei_type)>
      texture_storage1d;

    func<
      OGLPAFP(TexStorage3DMultisample),
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type,
        bool_type)>
      tex_storage3d_multisample;

    func<
      OGLPAFP(TextureStorage3DMultisample),
      void(
        texture_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        sizei_type,
        bool_type)>
      texture_storage3d_multisample;

    func<
      OGLPAFP(TexStorage2DMultisample),
      void(
        texture_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        bool_type)>
      tex_storage2d_multisample;

    func<
      OGLPAFP(TextureStorage2DMultisample),
      void(
        texture_name,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type,
        bool_type)>
      texture_storage2d_multisample;

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

    func<
      OGLPAFP(TexSubImage3D),
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
      tex_sub_image3d;

    func<
      OGLPAFP(TextureSubImage3D),
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
      texture_sub_image3d;

    func<
      OGLPAFP(TexSubImage2D),
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
      tex_sub_image2d;

    func<
      OGLPAFP(TextureSubImage2D),
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
      texture_sub_image2d;

    func<
      OGLPAFP(TexSubImage1D),
      void(
        texture_target,
        int_type,
        int_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      tex_sub_image1d;

    func<
      OGLPAFP(TexSubImage1D),
      void(
        texture_name,
        int_type,
        int_type,
        sizei_type,
        pixel_format,
        pixel_data_type,
        memory::const_block)>
      texture_sub_image1d;

    func<
      OGLPAFP(CopyTexImage2D),
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        int_type)>
      copy_tex_image2d;

    func<
      OGLPAFP(CopyTexImage1D),
      void(
        texture_target,
        int_type,
        pixel_internal_format,
        int_type,
        int_type,
        sizei_type,
        int_type)>
      copy_tex_image1d;

    func<
      OGLPAFP(CopyTexSubImage3D),
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
      copy_tex_sub_image3d;

    func<
      OGLPAFP(CopyTextureSubImage3D),
      void(
        texture_name,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type)>
      copy_texture_sub_image3d;

    func<
      OGLPAFP(CopyTexSubImage2D),
      void(
        texture_target,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type)>
      copy_tex_sub_image2d;

    func<
      OGLPAFP(CopyTextureSubImage2D),
      void(
        texture_name,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type)>
      copy_texture_sub_image2d;

    func<
      OGLPAFP(CopyTexSubImage1D),
      void(texture_target, int_type, int_type, int_type, int_type, sizei_type)>
      copy_tex_sub_image1d;

    func<
      OGLPAFP(CopyTextureSubImage1D),
      void(texture_name, int_type, int_type, int_type, int_type, sizei_type)>
      copy_texture_sub_image1d;

    struct : func<OGLPAFP(CompressedTexImage3D)> {
        using func<OGLPAFP(CompressedTexImage3D)>::func;

        constexpr auto operator()(
          texture_target tgt,
          int_type level,
          pixel_internal_format ifmt,
          sizei_type width,
          sizei_type height,
          sizei_type depth,
          int_type border,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tgt,
              level,
              ifmt,
              width,
              height,
              depth,
              border,
              data.size(),
              data.data());
        }
    } compressed_tex_image3d;

    struct : func<OGLPAFP(CompressedTexImage2D)> {
        using func<OGLPAFP(CompressedTexImage2D)>::func;

        constexpr auto operator()(
          texture_target tgt,
          int_type level,
          pixel_internal_format ifmt,
          sizei_type width,
          sizei_type height,
          int_type border,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tgt, level, ifmt, width, height, border, data.size(), data.data());
        }
    } compressed_tex_image2d;

    struct : func<OGLPAFP(CompressedTexImage1D)> {
        using func<OGLPAFP(CompressedTexImage1D)>::func;

        constexpr auto operator()(
          texture_target tgt,
          int_type level,
          pixel_internal_format ifmt,
          sizei_type width,
          int_type border,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tgt, level, ifmt, width, border, data.size(), data.data());
        }
    } compressed_tex_image1d;

    struct : func<OGLPAFP(CompressedTexSubImage3D)> {
        using func<OGLPAFP(CompressedTexSubImage3D)>::func;
        constexpr auto operator()(
          texture_target tgt,
          int_type level,
          int_type xoffset,
          int_type yoffset,
          int_type zoffset,
          sizei_type width,
          sizei_type height,
          sizei_type depth,
          pixel_format fmt,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tgt,
              level,
              xoffset,
              yoffset,
              zoffset,
              width,
              height,
              depth,
              fmt,
              data.size(),
              data.data());
        }
    } compressed_tex_sub_image3d;

    struct : func<OGLPAFP(CompressedTextureSubImage3D)> {
        using func<OGLPAFP(CompressedTextureSubImage3D)>::func;
        constexpr auto operator()(
          texture_name tex,
          int_type level,
          int_type xoffset,
          int_type yoffset,
          int_type zoffset,
          sizei_type width,
          sizei_type height,
          sizei_type depth,
          pixel_format fmt,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tex,
              level,
              xoffset,
              yoffset,
              zoffset,
              width,
              height,
              depth,
              fmt,
              data.size(),
              data.data());
        }
    } compressed_texture_sub_image3d;

    struct : func<OGLPAFP(CompressedTexSubImage2D)> {
        using func<OGLPAFP(CompressedTexSubImage2D)>::func;
        constexpr auto operator()(
          texture_target tgt,
          int_type level,
          int_type xoffset,
          int_type yoffset,
          sizei_type width,
          sizei_type height,
          pixel_format fmt,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tgt,
              level,
              xoffset,
              yoffset,
              width,
              height,
              fmt,
              data.size(),
              data.data());
        }
    } compressed_tex_sub_image2d;

    struct : func<OGLPAFP(CompressedTextureSubImage2D)> {
        using func<OGLPAFP(CompressedTextureSubImage2D)>::func;
        constexpr auto operator()(
          texture_name tex,
          int_type level,
          int_type xoffset,
          int_type yoffset,
          sizei_type width,
          sizei_type height,
          pixel_format fmt,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tex,
              level,
              xoffset,
              yoffset,
              width,
              height,
              fmt,
              data.size(),
              data.data());
        }
    } compressed_texture_sub_image2d;

    struct : func<OGLPAFP(CompressedTexSubImage1D)> {
        using func<OGLPAFP(CompressedTexSubImage1D)>::func;
        constexpr auto operator()(
          texture_target tgt,
          int_type level,
          int_type xoffset,
          sizei_type width,
          pixel_format fmt,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tgt, level, xoffset, width, fmt, data.size(), data.data());
        }
    } compressed_tex_sub_image1d;

    struct : func<OGLPAFP(CompressedTextureSubImage1D)> {
        using func<OGLPAFP(CompressedTextureSubImage1D)>::func;
        constexpr auto operator()(
          texture_name tex,
          int_type level,
          int_type xoffset,
          sizei_type width,
          pixel_format fmt,
          memory::const_block data) const noexcept {
            return this->_cnvchkcall(
              tex, level, xoffset, width, fmt, data.size(), data.data());
        }
    } compressed_texture_sub_image1d;

    func<
      OGLPAFP(TexBuffer),
      void(texture_target, pixel_internal_format, buffer_name)>
      tex_buffer;

    func<
      OGLPAFP(TextureBuffer),
      void(texture_name, pixel_internal_format, buffer_name)>
      texture_buffer;

    func<
      OGLPAFP(TexBufferRange),
      void(
        texture_target,
        pixel_internal_format,
        buffer_name,
        intptr_type,
        sizeiptr_type)>
      tex_buffer_range;

    func<
      OGLPAFP(TextureBufferRange),
      void(
        texture_name,
        pixel_internal_format,
        buffer_name,
        intptr_type,
        sizeiptr_type)>
      texture_buffer_range;

    func<
      OGLPAFP(TexParameterf),
      void(texture_target, texture_parameter, float_type)>
      tex_parameter_f;

    func<
      OGLPAFP(TextureParameterf),
      void(texture_name, texture_parameter, float_type)>
      texture_parameter_f;

    struct : func<OGLPAFP(TexParameteri)> {
        using func<OGLPAFP(TexParameteri)>::func;

        template <
          typename TexParam,
          typename Value,
          typename = std::enable_if_t<
            is_enum_parameter_value_v<texture_parameter, TexParam, int_type, Value>>>
        constexpr auto operator()(
          texture_target tgt,
          TexParam param,
          Value value) const noexcept {
            return this->_chkcall(
              enum_type(tgt), enum_type(param), enum_type(value));
        }
    } tex_parameter_i;

    struct : func<OGLPAFP(TextureParameteri)> {
        using func<OGLPAFP(TextureParameteri)>::func;

        template <
          typename TexParam,
          typename Value,
          typename = std::enable_if_t<
            is_enum_parameter_value_v<texture_parameter, TexParam, int_type, Value>>>
        constexpr auto operator()(texture_name tex, TexParam param, Value value)
          const noexcept {
            return this->_chkcall(
              name_type(tex), enum_type(param), enum_type(value));
        }
    } texture_parameter_i;

    struct : func<OGLPAFP(TexParameterfv)> {
        using func<OGLPAFP(TexParameterfv)>::func;

        constexpr auto operator()(
          texture_target tgt,
          texture_parameter param,
          span<const float_type> values) const noexcept {
            return this->_cnvchkcall(tgt, param, values.data());
        }
    } tex_parameter_fv;

    struct : func<OGLPAFP(TextureParameterfv)> {
        using func<OGLPAFP(TextureParameterfv)>::func;

        constexpr auto operator()(
          texture_name tex,
          texture_parameter param,
          span<const float_type> values) const noexcept {
            return this->_cnvchkcall(tex, param, values.data());
        }
    } texture_parameter_fv;

    struct : func<OGLPAFP(TexParameteriv)> {
        using func<OGLPAFP(TexParameteriv)>::func;

        constexpr auto operator()(
          texture_target tgt,
          texture_parameter param,
          span<const int_type> values) const noexcept {
            return this->_cnvchkcall(tgt, param, values.data());
        }
    } tex_parameter_iv;

    struct : func<OGLPAFP(TextureParameteriv)> {
        using func<OGLPAFP(TextureParameteriv)>::func;

        constexpr auto operator()(
          texture_name tex,
          texture_parameter param,
          span<const int_type> values) const noexcept {
            return this->_cnvchkcall(tex, param, values.data());
        }
    } texture_parameter_iv;

    struct : func<OGLPAFP(TexParameterIiv)> {
        using func<OGLPAFP(TexParameterIiv)>::func;

        constexpr auto operator()(
          texture_target tgt,
          texture_parameter param,
          span<const int_type> values) const noexcept {
            return this->_cnvchkcall(tgt, param, values.data());
        }
    } tex_parameter_iiv;

    struct : func<OGLPAFP(TextureParameterIiv)> {
        using func<OGLPAFP(TextureParameterIiv)>::func;

        constexpr auto operator()(
          texture_name tex,
          texture_parameter param,
          span<const int_type> values) const noexcept {
            return this->_cnvchkcall(tex, param, values.data());
        }
    } texture_parameter_iiv;

    struct : func<OGLPAFP(TexParameterIuiv)> {
        using func<OGLPAFP(TexParameterIuiv)>::func;

        constexpr auto operator()(
          texture_target tgt,
          texture_parameter param,
          span<const uint_type> values) const noexcept {
            return this->_cnvchkcall(tgt, param, values.data());
        }
    } tex_parameter_iuiv;

    struct : func<OGLPAFP(TextureParameterIuiv)> {
        using func<OGLPAFP(TextureParameterIuiv)>::func;

        constexpr auto operator()(
          texture_name tex,
          texture_parameter param,
          span<const uint_type> values) const noexcept {
            return this->_cnvchkcall(tex, param, values.data());
        }
    } texture_parameter_iuiv;

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

    func<OGLPAFP(GenerateMipmap), void(texture_target)> generate_mipmap;

    func<OGLPAFP(GenerateTextureMipmap), void(texture_name)>
      generate_texture_mipmap;

    // sampler ops
    func<OGLPAFP(BindSampler), void(uint_type, sampler_name)> bind_sampler;

    func<
      OGLPAFP(SamplerParameterf),
      void(sampler_name, sampler_parameter, float_type)>
      sampler_parameter_f;

    func<
      OGLPAFP(SamplerParameteri),
      void(sampler_name, sampler_parameter, int_type)>
      sampler_parameter_i;

    struct : func<OGLPAFP(SamplerParameterfv)> {
        using func<OGLPAFP(SamplerParameterfv)>::func;

        constexpr auto operator()(
          sampler_name sam,
          sampler_parameter param,
          span<const float_type> values) const noexcept {
            return this->_cnvchkcall(sam, param, values.data());
        }
    } sampler_parameter_fv;

    struct : func<OGLPAFP(SamplerParameteriv)> {
        using func<OGLPAFP(SamplerParameteriv)>::func;

        constexpr auto operator()(
          sampler_name sam,
          sampler_parameter param,
          span<const int_type> values) const noexcept {
            return this->_cnvchkcall(sam, param, values.data());
        }
    } sampler_parameter_iv;

    struct : func<OGLPAFP(SamplerParameterIiv)> {
        using func<OGLPAFP(SamplerParameterIiv)>::func;

        constexpr auto operator()(
          sampler_name sam,
          sampler_parameter param,
          span<const int_type> values) const noexcept {
            return this->_cnvchkcall(sam, param, values.data());
        }
    } sampler_parameter_iiv;

    struct : func<OGLPAFP(SamplerParameterIuiv)> {
        using func<OGLPAFP(SamplerParameterIuiv)>::func;

        constexpr auto operator()(
          sampler_name sam,
          sampler_parameter param,
          span<const uint_type> values) const noexcept {
            return this->_cnvchkcall(sam, param, values.data());
        }
    } sampler_parameter_iuiv;

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
    func<OGLPAFP(BindRenderbuffer), void(renderbuffer_target, renderbuffer_name)>
      bind_renderbuffer;

    func<
      OGLPAFP(RenderbufferStorage),
      void(renderbuffer_target, pixel_internal_format, sizei_type, sizei_type)>
      renderbuffer_storage;

    func<
      OGLPAFP(NamedRenderbufferStorage),
      void(renderbuffer_target, pixel_internal_format, sizei_type, sizei_type)>
      named_renderbuffer_storage;

    func<
      OGLPAFP(RenderbufferStorageMultisample),
      void(
        renderbuffer_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      renderbuffer_storage_multisample;

    func<
      OGLPAFP(NamedRenderbufferStorageMultisample),
      void(
        renderbuffer_target,
        sizei_type,
        pixel_internal_format,
        sizei_type,
        sizei_type)>
      named_renderbuffer_storage_multisample;

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
          path_list_mode_nv mode,
          string_view glyphs,
          path_nv_name pth,
          float_type advance_scale,
          float_type kerning_scale,
          path_transform_type_nv transf,
          span<float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              mode,
              glyphs.size(),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              advance_scale,
              kerning_scale,
              transf,
              dst.data());
#else
            EAGINE_MAYBE_UNUSED(mode);
            EAGINE_MAYBE_UNUSED(glyphs);
            EAGINE_MAYBE_UNUSED(pth);
            EAGINE_MAYBE_UNUSED(advance_scale);
            EAGINE_MAYBE_UNUSED(kerning_scale);
            EAGINE_MAYBE_UNUSED(transf);
            EAGINE_MAYBE_UNUSED(dst);
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
          string_view glyphs,
          path_nv_name pth,
          path_fill_mode_nv mode,
          uint_type mask,
          path_transform_type_nv transf,
          span<const float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              glyphs.size(),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              mode,
              mask,
              transf,
              dst.data());
#else
            EAGINE_MAYBE_UNUSED(glyphs);
            EAGINE_MAYBE_UNUSED(pth);
            EAGINE_MAYBE_UNUSED(mode);
            EAGINE_MAYBE_UNUSED(mask);
            EAGINE_MAYBE_UNUSED(transf);
            EAGINE_MAYBE_UNUSED(dst);
            return this->_fake();
#endif
        }
    } stencil_fill_path_instanced_nv;

    struct : func<OGLPAFP(StencilStrokePathInstancedNV)> {
        using func<OGLPAFP(StencilStrokePathInstancedNV)>::func;
        constexpr auto operator()(
          string_view glyphs,
          path_nv_name pth,
          int_type reference,
          uint_type mask,
          path_transform_type_nv transf,
          span<const float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              glyphs.size(),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              reference,
              mask,
              transf,
              dst.data());
#else
            EAGINE_MAYBE_UNUSED(glyphs);
            EAGINE_MAYBE_UNUSED(pth);
            EAGINE_MAYBE_UNUSED(reference);
            EAGINE_MAYBE_UNUSED(mask);
            EAGINE_MAYBE_UNUSED(transf);
            EAGINE_MAYBE_UNUSED(dst);
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
          string_view glyphs,
          path_nv_name pth,
          path_fill_cover_mode_nv mode,
          path_transform_type_nv transf,
          span<const float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              glyphs.size(),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              mode,
              transf,
              dst.data());
#else
            EAGINE_MAYBE_UNUSED(glyphs);
            EAGINE_MAYBE_UNUSED(pth);
            EAGINE_MAYBE_UNUSED(mode);
            EAGINE_MAYBE_UNUSED(transf);
            EAGINE_MAYBE_UNUSED(dst);
            return this->_fake();
#endif
        }
    } cover_fill_path_instanced_nv;

    struct : func<OGLPAFP(CoverStrokePathInstancedNV)> {
        using func<OGLPAFP(CoverStrokePathInstancedNV)>::func;
        constexpr auto operator()(
          string_view glyphs,
          path_nv_name pth,
          path_stroke_cover_mode_nv mode,
          path_transform_type_nv transf,
          span<const float_type> dst) const noexcept {
#ifdef GL_UTF8_NV
            return this->_cnvchkcall(
              glyphs.size(),
              GL_UTF8_NV,
              static_cast<const char*>(c_str(glyphs)),
              pth,
              mode,
              transf,
              dst.data());
#else
            EAGINE_MAYBE_UNUSED(glyphs);
            EAGINE_MAYBE_UNUSED(pth);
            EAGINE_MAYBE_UNUSED(mode);
            EAGINE_MAYBE_UNUSED(transf);
            EAGINE_MAYBE_UNUSED(dst);
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
            return this->_cnvchkcall(query).transformed([](auto src) {
                return src ? string_view{reinterpret_cast<const char*>(src)}
                           : string_view{};
            });
        }

        constexpr auto operator()() const noexcept {
            return this->_fake_empty_c_str().cast_to(
              type_identity<string_view>{});
        }
    } get_string;

    // get_strings
    auto get_strings(string_query query, char separator) const noexcept {
        return get_string(query).transformed([separator](auto src) {
            return split_into_string_list(src, separator);
        });
    }

    // get_extensions
    auto get_extensions() const noexcept {
#ifdef GL_EXTENSIONS
        return get_string(string_query(GL_EXTENSIONS))
#else
        return get_string()
#endif
          .transformed(
            [](auto src) { return split_into_string_list(src, ' '); });
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
    struct : func<OGLPAFP(NamedString)> {
        using func<OGLPAFP(NamedString)>::func;

        constexpr auto operator()(
          named_string_kind kind,
          string_view name,
          string_view str) const noexcept {
            return this->_cnvchkcall(
              kind, name.size(), name.data(), str.size(), str.data());
        }
    } named_string;

    struct : func<OGLPAFP(DeleteNamedString)> {
        using func<OGLPAFP(DeleteNamedString)>::func;

        constexpr auto operator()(string_view name) const noexcept {
            return this->_cnvchkcall(name.size(), name.data());
        }
    } delete_named_string;

    struct : func<OGLPAFP(IsNamedString)> {
        using func<OGLPAFP(IsNamedString)>::func;

        constexpr auto operator()(string_view name) const noexcept {
            return this->_cnvchkcall(name.size(), name.data())
              .cast_to(type_identity<true_false>{});
        }
    } is_named_string;

    // arb compatibility
    unck_func<OGLPAFP(Begin), void(old_primitive_type)> begin;
    func<OGLPAFP(End)> end;

    unck_func<OGLPAFP(Vertex2i)> vertex2i;
    unck_func<OGLPAFP(Vertex3i)> vertex3i;
    unck_func<OGLPAFP(Vertex4i)> vertex4i;
    unck_func<OGLPAFP(Vertex2f)> vertex2f;
    unck_func<OGLPAFP(Vertex3f)> vertex3f;
    unck_func<OGLPAFP(Vertex4f)> vertex4f;

    unck_func<OGLPAFP(Color3i)> color3i;
    unck_func<OGLPAFP(Color4i)> color4i;
    unck_func<OGLPAFP(Color3f)> color3f;
    unck_func<OGLPAFP(Color4f)> color4f;

    unck_func<OGLPAFP(SecondaryColor3i)> secondary_color3i;
    unck_func<OGLPAFP(SecondaryColor4i)> secondary_color4i;
    unck_func<OGLPAFP(SecondaryColor3f)> secondary_color3f;
    unck_func<OGLPAFP(SecondaryColor4f)> secondary_color4f;

    unck_func<OGLPAFP(TexCoord1i)> tex_coord1i;
    unck_func<OGLPAFP(TexCoord2i)> tex_coord2i;
    unck_func<OGLPAFP(TexCoord3i)> tex_coord3i;
    unck_func<OGLPAFP(TexCoord4i)> tex_coord4i;
    unck_func<OGLPAFP(TexCoord1f)> tex_coord1f;
    unck_func<OGLPAFP(TexCoord2f)> tex_coord2f;
    unck_func<OGLPAFP(TexCoord3f)> tex_coord3f;
    unck_func<OGLPAFP(TexCoord4f)> tex_coord4f;

    unck_func<OGLPAFP(MultiTexCoord1i), void(texture_unit, int_type)>
      multi_tex_coord1i;
    unck_func<OGLPAFP(MultiTexCoord2i), void(texture_unit, int_type, int_type)>
      multi_tex_coord2i;
    unck_func<
      OGLPAFP(MultiTexCoord3i),
      void(texture_unit, int_type, int_type, int_type)>
      multi_tex_coord3i;
    unck_func<
      OGLPAFP(MultiTexCoord4i),
      void(texture_unit, int_type, int_type, int_type, int_type)>
      multi_tex_coord4i;
    unck_func<OGLPAFP(MultiTexCoord1f), void(texture_unit, float_type)>
      multi_tex_coord1f;
    unck_func<
      OGLPAFP(MultiTexCoord2f),
      void(texture_unit, float_type, float_type)>
      multi_tex_coord2f;
    unck_func<
      OGLPAFP(MultiTexCoord3f),
      void(texture_unit, float_type, float_type, float_type)>
      multi_tex_coord3f;
    unck_func<
      OGLPAFP(MultiTexCoord4f),
      void(texture_unit, float_type, float_type, float_type, float_type)>
      multi_tex_coord4f;

    func<OGLPAFP(MatrixMode), void(matrix_mode)> matrix_mode;
    func<OGLPAFP(PushMatrix)> push_matrix;
    func<OGLPAFP(PopMatrix)> pop_matrix;

    func<OGLPAFP(LoadIdentity)> load_identity;

    func<OGLPAFP(Translatef)> translate_f;
    func<OGLPAFP(Translated)> translate_d;

    func<
      OGLPAFP(Rotatef),
      void(degrees_t<float_type>, float_type, float_type, float_type)>
      rotate_f;

    func<
      OGLPAFP(Rotated),
      void(degrees_t<double_type>, double_type, double_type, double_type)>
      rotate_d;

    func<OGLPAFP(Scalef)> scale_f;
    func<OGLPAFP(Scaled)> scale_d;

    func<OGLPAFP(Frustum)> frustum;
    func<OGLPAFP(Ortho)> ortho;

    func<OGLPAFP(LoadMatrixf)> load_matrix_f;
    func<OGLPAFP(LoadMatrixd)> load_matrix_d;

    func<OGLPAFP(MultMatrixf)> mult_matrix_f;
    func<OGLPAFP(MultMatrixd)> mult_matrix_d;

    func<OGLPAFP(LoadTransposeMatrixf)> load_transpose_matrix_f;
    func<OGLPAFP(LoadTransposeMatrixd)> load_transpose_matrix_d;

    func<OGLPAFP(MultTransposeMatrixf)> mult_transpose_matrix_f;
    func<OGLPAFP(MultTransposeMatrixd)> mult_transpose_matrix_d;

    struct : func<OGLPAFP(DebugMessageControl)> {
        using func<OGLPAFP(DebugMessageControl)>::func;

        constexpr auto operator()(
          debug_output_source source,
          debug_output_type type,
          debug_output_severity severity,
          span<const uint_type> ids,
          true_false enabled) const noexcept {
            return this->_cnvchkcall(
              source, type, severity, ids.size(), ids.data(), enabled);
        }

        constexpr auto operator()(
          debug_output_source source,
          debug_output_type type,
          debug_output_severity severity,
          true_false enabled) const noexcept {
            return (*this)(source, type, severity, {}, enabled);
        }

    } debug_message_control;

    struct : func<OGLPAFP(DebugMessageInsert)> {
        using func<OGLPAFP(DebugMessageInsert)>::func;

        constexpr auto operator()(
          debug_output_source source,
          debug_output_type type,
          debug_output_severity severity,
          uint_type id,
          string_view message) const noexcept {
            return this->_cnvchkcall(
              source, type, id, severity, message.size(), message.data());
        }

    } debug_message_insert;

    struct : func<OGLPAFP(DebugMessageCallback)> {
        using func<OGLPAFP(DebugMessageCallback)>::func;

        constexpr auto operator()(
          debug_callback_type* callback,
          const_void_ptr_type user_data) const noexcept {
            return this->_chkcall(callback, user_data);
        }

        constexpr auto operator()(
          std::tuple<debug_callback_type*, const_void_ptr_type> callback)
          const noexcept {
            return this->_chkcall(std::get<0>(callback), std::get<1>(callback));
        }

    } debug_message_callback;

    struct : func<OGLPAFP(PushDebugGroup)> {
        using func<OGLPAFP(PushDebugGroup)>::func;

        constexpr auto operator()(
          debug_output_source source,
          uint_type id,
          string_view message) const noexcept {
            return this->_cnvchkcall(
              source, id, message.size(), message.data());
        }

    } push_debug_group;

    func<OGLPAFP(PopDebugGroup)> pop_debug_group;

    struct : func<OGLPAFP(ObjectLabel)> {
        using func<OGLPAFP(ObjectLabel)>::func;

        template <typename ObjTag>
        constexpr auto operator()(
          gl_object_name<ObjTag> name,
          string_view message) const noexcept {
            return this->_cnvchkcall(
              type_of(name), name, message.size(), message.data());
        }

    } object_label;

    func<OGLPAFP(Flush)> flush;
    func<OGLPAFP(Finish)> finish;

    basic_gl_operations(api_traits& traits);
};
//------------------------------------------------------------------------------
#undef OGLPAFP
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

#endif // EAGINE_OGLPLUS_GL_API_API_HPP
