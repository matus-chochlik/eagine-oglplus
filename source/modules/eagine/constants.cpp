module;

#include "gl_def.hpp"

export module eagine.oglplus:constants;
import std;
import eagine.core.types;
import eagine.core.c_api;
import eagine.core.memory;
import eagine.core.valid_if;
import :config;
import :enum_types;
import :objects;
import :math;
import :c_api;

namespace eagine {
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::buffer_target, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::buffer_usage, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::capability, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::object_type, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::pixel_data_type, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<
  oglplus::pixel_internal_format,
  oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::pixel_format, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::shader_type, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::texture_target, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::texture_min_filter, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::texture_mag_filter, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::texture_swizzle_mode, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::texture_wrap_mode, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<oglplus::true_false, oglplus::gl_types::enum_type> {
    auto check(oglplus::gl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
namespace oglplus {
export auto gl_enum_by_name(const string_view name) noexcept
  -> optionally_valid<gl_types::enum_type>;
//------------------------------------------------------------------------------
using c_api::opt_constant;
/// @brief Class wrapping the constants from the GL API.
/// @ingroup gl_api_wrap
/// @see basic_gl_c_api
/// @see basic_gl_operations
export template <typename ApiTraits>
class basic_gl_constants {
public:
    //
    /// @brief Constant wrapper that can also be used to construct instances.
    template <typename Wrap, typename T = typename Wrap::tag_type>
    struct type_constructor_constant : Wrap {
        using Wrap::Wrap;

        /// @brief Creates an instance of the constant type with the specified value.
        template <typename X>
            requires(std::is_convertible_v<X, T>)
        auto operator()(X&& x) const noexcept -> T {
            return T(std::forward<X>(x));
        }

        /// @var array
        /// @brief Helper that can be used to create arrays of the constant type.
        struct {
            /// @brief Creates an array of the constant type with the specified values.
            template <typename... X>
            auto operator()(X&&... x) const noexcept
              -> std::array<T, sizeof...(X)>
                requires(
                  (sizeof...(X) > 0) and ... and
                  std::is_convertible_v<std::decay_t<X>, T>)
            {
                return {{T(std::forward<X>(x))...}};
            }

            template <std::size_t L>
            auto operator()(size_constant<L> = {}) const noexcept
              -> std::array<T, L> {
                return {{}};
            }
        } array;
    };

    template <typename Wrap, typename T, std::size_t N>
    struct type_constructor_constant<Wrap, T[N]> : Wrap {
        using Wrap::Wrap;

        template <typename... X>
        auto operator()(X&&... x) const noexcept -> vector<T, N>
            requires((sizeof...(X) == N) and ... and std::is_convertible_v<X, T>)
        {
            return {T(std::forward<X>(x))...};
        }
    };

    template <typename Wrap, typename T, std::size_t C, std::size_t R>
    struct type_constructor_constant<Wrap, T[C][R]> : Wrap {
        using Wrap::Wrap;

        template <typename... X>
        auto operator()(X&&... x) const noexcept -> matrix<T, C, R, true>
            requires(
              (sizeof...(X) == C * R) and ... and std::is_convertible_v<X, T>)
        {
            return {T(std::forward<X>(x))...};
        }
    };

    using enum_type = typename gl_types::enum_type;
    using enum_type_i = std::type_identity<enum_type>;
    template <enum_type value>
    using enum_type_c = std::integral_constant<enum_type, value>;

    using bitfield_type = typename gl_types::bitfield_type;
    using bitfield_type_i = std::type_identity<bitfield_type>;
    template <bitfield_type value>
    using bitfield_type_c = std::integral_constant<bitfield_type, value>;

    using ubyte_type = typename gl_types::ubyte_type;
    using ubyte_type_i = std::type_identity<ubyte_type>;
    template <ubyte_type value>
    using ubyte_type_c = std::integral_constant<ubyte_type, value>;

    using bool_type = typename gl_types::bool_type;
    using bool_type_i = std::type_identity<bool_type>;
    template <bool_type value>
    using bool_type_c = std::integral_constant<bool_type, value>;

    /// @var no_error
    /// @glconstwrap{NO_ERROR}
    opt_constant<
      mp_list<error_code, graphics_reset_status>,
#ifdef GL_NO_ERROR
      enum_type_c<GL_NO_ERROR>>
#else
      enum_type_i>
#endif
      no_error;

    /// @var invalid_enum
    /// @glconstwrap{INVALID_ENUM}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_INVALID_ENUM
      enum_type_c<GL_INVALID_ENUM>>
#else
      enum_type_i>
#endif
      invalid_enum;

    /// @var invalid_value
    /// @glconstwrap{INVALID_VALUE}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_INVALID_VALUE
      enum_type_c<GL_INVALID_VALUE>>
#else
      enum_type_i>
#endif
      invalid_value;

    /// @var invalid_operation
    /// @glconstwrap{INVALID_OPERATION}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_INVALID_OPERATION
      enum_type_c<GL_INVALID_OPERATION>>
#else
      enum_type_i>
#endif
      invalid_operation;

    /// @var invalid_framebuffer_operation
    /// @glconstwrap{INVALID_FRAMEBUFFER_OPERATION}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
      enum_type_c<GL_INVALID_FRAMEBUFFER_OPERATION>>
#else
      enum_type_i>
#endif
      invalid_framebuffer_operation;

    /// @var stack_overflow
    /// @glconstwrap{STACK_OVERFLOW}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_STACK_OVERFLOW
      enum_type_c<GL_STACK_OVERFLOW>>
#else
      enum_type_i>
#endif
      stack_overflow;

    /// @var stack_underflow
    /// @glconstwrap{STACK_UNDERFLOW}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_STACK_UNDERFLOW
      enum_type_c<GL_STACK_UNDERFLOW>>
#else
      enum_type_i>
#endif
      stack_underflow;

    /// @var table_too_large
    /// @glconstwrap{TABLE_TOO_LARGE}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_TABLE_TOO_LARGE
      enum_type_c<GL_TABLE_TOO_LARGE>>
#else
      enum_type_i>
#endif
      table_too_large;

    /// @var context_lost
    /// @glconstwrap{CONTEXT_LOST}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_CONTEXT_LOST
      enum_type_c<GL_CONTEXT_LOST>>
#else
      enum_type_i>
#endif
      context_lost;

    /// @var out_of_memory
    /// @glconstwrap{OUT_OF_MEMORY}
    opt_constant<
      mp_list<error_code>,
#ifdef GL_OUT_OF_MEMORY
      enum_type_c<GL_OUT_OF_MEMORY>>
#else
      enum_type_i>
#endif
      out_of_memory;

    /// @var true_
    /// @glconstwrap{TRUE}
    opt_constant<
      mp_list<oglplus::true_false>,
#ifdef GL_TRUE
      bool_type_c<GL_TRUE>>
#else
      bool_type_i>
#endif
      true_;

    /// @var false_
    /// @glconstwrap{FALSE}
    opt_constant<
      mp_list<oglplus::true_false>,
#ifdef GL_FALSE
      bool_type_c<GL_FALSE>>
#else
      bool_type_i>
#endif
      false_;

    /// @var context_flag_forward_compatible_bit
    /// @glconstwrap{CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT}
    opt_constant<
      mp_list<context_flag_bit>,
#ifdef GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT
      bitfield_type_c<GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT>>
#else
      bitfield_type_i>
#endif
      context_flag_forward_compatible_bit;

    /// @var context_flag_debug_bit
    /// @glconstwrap{CONTEXT_FLAG_FORWARD_DEBUG_BIT}
    opt_constant<
      mp_list<context_flag_bit>,
#ifdef GL_CONTEXT_FLAG_DEBUG_BIT
      bitfield_type_c<GL_CONTEXT_FLAG_DEBUG_BIT>>
#else
      bitfield_type_i>
#endif
      context_flag_debug_bit;

    /// @var context_flag_robust_access_bit
    /// @glconstwrap{CONTEXT_FLAG_ROBUST_ACCESS_BIT}
    opt_constant<
      mp_list<context_flag_bit>,
#ifdef GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT
      bitfield_type_c<GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT>>
#else
      bitfield_type_i>
#endif
      context_flag_robust_access_bit;

    /// @var context_flag_no_error_bit
    /// @glconstwrap{CONTEXT_FLAG_NO_ERROR_BIT}
    opt_constant<
      mp_list<context_flag_bit>,
#ifdef GL_CONTEXT_FLAG_NO_ERROR_BIT
      bitfield_type_c<GL_CONTEXT_FLAG_NO_ERROR_BIT>>
#else
      bitfield_type_i>
#endif
      context_flag_no_error_bit;

    /// @var context_core_profile_bit
    /// @glconstwrap{CONTEXT_CORE_PROFILE_BIT}
    opt_constant<
      mp_list<context_profile_bit>,
#ifdef GL_CONTEXT_CORE_PROFILE_BIT
      bitfield_type_c<GL_CONTEXT_CORE_PROFILE_BIT>>
#else
      bitfield_type_i>
#endif
      context_core_profile_bit;

    /// @var context_compatibility_profile_bit
    /// @glconstwrap{CONTEXT_COMPATIBILITY_PROFILE_BIT}
    opt_constant<
      mp_list<context_profile_bit>,
#ifdef GL_CONTEXT_COMPATIBILITY_PROFILE_BIT
      bitfield_type_c<GL_CONTEXT_COMPATIBILITY_PROFILE_BIT>>
#else
      bitfield_type_i>
#endif
      context_compatibility_profile_bit;

    /// @var no_reset_notification
    /// @glconstwrap{NO_RESET_NOTIFICATION}
    opt_constant<
      mp_list<oglplus::reset_notification_strategy>,
#ifdef GL_NO_RESET_NOTIFICATION
      enum_type_c<GL_NO_RESET_NOTIFICATION>>
#else
      enum_type_i>
#endif
      no_reset_notification;

    /// @var lose_context_on_reset
    /// @glconstwrap{LOSE_CONTEXT_ON_RESET}
    opt_constant<
      mp_list<oglplus::reset_notification_strategy>,
#ifdef GL_LOSE_CONTEXT_ON_RESET
      enum_type_c<GL_LOSE_CONTEXT_ON_RESET>>
#else
      enum_type_i>
#endif
      lose_context_on_reset;

    /// @var context_release_behavior_flush
    /// @glconstwrap{CONTEXT_RELEASE_BEHAVIOR_FLUSH}
    opt_constant<
      mp_list<context_release_behavior>,
#ifdef GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
      enum_type_c<GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH>>
#else
      enum_type_i>
#endif
      context_release_behavior_flush;

    /// @var guilty_context_reset
    /// @glconstwrap{GUILTY_CONTEXT_RESET}
    opt_constant<
      mp_list<graphics_reset_status>,
#ifdef GL_GUILTY_CONTEXT_RESET
      enum_type_c<GL_GUILTY_CONTEXT_RESET>>
#else
      enum_type_i>
#endif
      guilty_context_reset;

    /// @var innocent_context_reset
    /// @glconstwrap{INNOCENT_CONTEXT_RESET}
    opt_constant<
      mp_list<graphics_reset_status>,
#ifdef GL_INNOCENT_CONTEXT_RESET
      enum_type_c<GL_INNOCENT_CONTEXT_RESET>>
#else
      enum_type_i>
#endif
      innocent_context_reset;

    /// @var graphics_reset_status
    /// @glconstwrap{GRAPHICS_RESET_STATUS}
    opt_constant<
      mp_list<graphics_reset_status>,
#ifdef GL_UNKNOWN_CONTEXT_RESET
      enum_type_c<GL_UNKNOWN_CONTEXT_RESET>>
#else
      enum_type_i>
#endif
      unknown_context_reset;

    /// @var vertex_attrib_array_barrier_bit
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT
      bitfield_type_c<GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      vertex_attrib_array_barrier_bit;

    /// @var element_array_barrier_bit
    /// @glconstwrap{ELEMENT_ARRAY_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_ELEMENT_ARRAY_BARRIER_BIT
      bitfield_type_c<GL_ELEMENT_ARRAY_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      element_array_barrier_bit;

    /// @var uniform_barrier_bit
    /// @glconstwrap{UNIFORM_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_UNIFORM_BARRIER_BIT
      bitfield_type_c<GL_UNIFORM_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      uniform_barrier_bit;

    /// @var texture_fetch_barrier_bit
    /// @glconstwrap{TEXTURE_FETCH_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_TEXTURE_FETCH_BARRIER_BIT
      bitfield_type_c<GL_TEXTURE_FETCH_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      texture_fetch_barrier_bit;

    /// @var shader_image_access_barrier_bit
    /// @glconstwrap{SHADER_IMAGE_ACCESS_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
      bitfield_type_c<GL_SHADER_IMAGE_ACCESS_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      shader_image_access_barrier_bit;

    /// @var command_barrier_bit
    /// @glconstwrap{COMMAND_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_COMMAND_BARRIER_BIT
      bitfield_type_c<GL_COMMAND_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      command_barrier_bit;

    /// @var pixel_buffer_barrier_bit
    /// @glconstwrap{PIXEL_BUFFER_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_PIXEL_BUFFER_BARRIER_BIT
      bitfield_type_c<GL_PIXEL_BUFFER_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      pixel_buffer_barrier_bit;

    /// @var texture_update_barrier_bit
    /// @glconstwrap{TEXTURE_UPDATE_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_TEXTURE_UPDATE_BARRIER_BIT
      bitfield_type_c<GL_TEXTURE_UPDATE_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      texture_update_barrier_bit;

    /// @var buffer_update_barrier_bit
    /// @glconstwrap{BUFFER_UPDATE_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_BUFFER_UPDATE_BARRIER_BIT
      bitfield_type_c<GL_BUFFER_UPDATE_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      buffer_update_barrier_bit;

    /// @var client_mapped_buffer_barrier_bit
    /// @glconstwrap{CLIENT_MAPPED_BUFFER_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT
      bitfield_type_c<GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      client_mapped_buffer_barrier_bit;

    /// @var query_buffer_barrier_bit
    /// @glconstwrap{QUERY_BUFFER_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_QUERY_BUFFER_BARRIER_BIT
      bitfield_type_c<GL_QUERY_BUFFER_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      query_buffer_barrier_bit;

    /// @var framebuffer_barrier_bit
    /// @glconstwrap{FRAMEBUFFER_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_FRAMEBUFFER_BARRIER_BIT
      bitfield_type_c<GL_FRAMEBUFFER_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      framebuffer_barrier_bit;

    /// @var transform_feedback_barrier_bit
    /// @glconstwrap{TRANSFORM_FEEDBACK_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_TRANSFORM_FEEDBACK_BARRIER_BIT
      bitfield_type_c<GL_TRANSFORM_FEEDBACK_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      transform_feedback_barrier_bit;

    /// @var atomic_counter_barrier_bit
    /// @glconstwrap{ATOMIC_COUNTER_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_ATOMIC_COUNTER_BARRIER_BIT
      bitfield_type_c<GL_ATOMIC_COUNTER_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      atomic_counter_barrier_bit;

    /// @var shader_storage_barrier_bit
    /// @glconstwrap{SHADER_STORAGE_BARRIER_BIT}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_SHADER_STORAGE_BARRIER_BIT
      bitfield_type_c<GL_SHADER_STORAGE_BARRIER_BIT>>
#else
      bitfield_type_i>
#endif
      shader_storage_barrier_bit;

    /// @var all_barrier_bits
    /// @glconstwrap{ALL_BARRIER_BITS}
    opt_constant<
      mp_list<memory_barrier_bit>,
#ifdef GL_ALL_BARRIER_BITS
      bitfield_type_c<GL_ALL_BARRIER_BITS>>
#else
      bitfield_type_i>
#endif
      all_barrier_bits;

    /// @var read_only
    /// @glconstwrap{READ_ONLY}
    opt_constant<
      mp_list<access_specifier>,
#ifdef GL_READ_ONLY
      enum_type_c<GL_READ_ONLY>>
#else
      enum_type_i>
#endif
      read_only;

    /// @var write_only
    /// @glconstwrap{WRITE_ONLY}
    opt_constant<
      mp_list<access_specifier>,
#ifdef GL_WRITE_ONLY
      enum_type_c<GL_WRITE_ONLY>>
#else
      enum_type_i>
#endif
      write_only;

    /// @var read_Write
    /// @glconstwrap{READ_WRITE}
    opt_constant<
      mp_list<access_specifier>,
#ifdef GL_READ_WRITE
      enum_type_c<GL_READ_WRITE>>
#else
      enum_type_i>
#endif
      read_write;

    /// @var low_float
    /// @glconstwrap{LOW_FLOAT}
    opt_constant<
      mp_list<precision_type>,
#ifdef GL_LOW_FLOAT
      enum_type_c<GL_LOW_FLOAT>>
#else
      enum_type_i>
#endif
      low_float;

    /// @var medium_float
    /// @glconstwrap{MEDIUM_FLOAT}
    opt_constant<
      mp_list<precision_type>,
#ifdef GL_MEDIUM_FLOAT
      enum_type_c<GL_MEDIUM_FLOAT>>
#else
      enum_type_i>
#endif
      medium_float;

    /// @var high_float
    /// @glconstwrap{HIGH_FLOAT}
    opt_constant<
      mp_list<precision_type>,
#ifdef GL_HIGH_FLOAT
      enum_type_c<GL_HIGH_FLOAT>>
#else
      enum_type_i>
#endif
      high_float;

    /// @var low_int
    /// @glconstwrap{LOW_INT}
    opt_constant<
      mp_list<precision_type>,
#ifdef GL_LOW_INT
      enum_type_c<GL_LOW_INT>>
#else
      enum_type_i>
#endif
      low_int;

    /// @var medium_int
    /// @glconstwrap{MEDIUM_INT}
    opt_constant<
      mp_list<precision_type>,
#ifdef GL_MEDIUM_INT
      enum_type_c<GL_MEDIUM_INT>>
#else
      enum_type_i>
#endif
      medium_int;

    /// @var high_int
    /// @glconstwrap{HIGH_INT}
    opt_constant<
      mp_list<precision_type>,
#ifdef GL_HIGH_INT
      enum_type_c<GL_HIGH_INT>>
#else
      enum_type_i>
#endif
      high_int;

    /// @var buffer
    /// @glconstwrap{BUFFER}
    opt_constant<
      mp_list<oglplus::object_type>,
#ifdef GL_BUFFER
      enum_type_c<GL_BUFFER>>
#else
      enum_type_i>
#endif
      buffer;

    /// @var framebuffer
    /// @glconstwrap{FRAMEBUFFER}
    opt_constant<
      mp_list<oglplus::object_type>,
#ifdef GL_FRAMEBUFFER
      enum_type_c<GL_FRAMEBUFFER>>
#else
      enum_type_i>
#endif
      framebuffer;

    /// @var program_pipeline
    /// @glconstwrap{PROGRAM_PIPELINE}
    opt_constant<
      mp_list<oglplus::object_type>,
#ifdef GL_PROGRAM_PIPELINE
      enum_type_c<GL_PROGRAM_PIPELINE>>
#else
      enum_type_i>
#endif
      program_pipeline;

    /// @var program
    /// @glconstwrap{PROGRAM}
    opt_constant<
      mp_list<oglplus::object_type>,
#ifdef GL_PROGRAM
      enum_type_c<GL_PROGRAM>>
#else
      enum_type_i>
#endif
      program;

    /// @var query
    /// @glconstwrap{QUERY}
    opt_constant<
      mp_list<oglplus::object_type>,
#ifdef GL_QUERY
      enum_type_c<GL_QUERY>>
#else
      enum_type_i>
#endif
      query;

    /// @var renderbuffer
    /// @glconstwrap{RENDERBUFFER}
    opt_constant<
      mp_list<oglplus::object_type, renderbuffer_target>,
#ifdef GL_RENDERBUFFER
      enum_type_c<GL_RENDERBUFFER>>
#else
      enum_type_i>
#endif
      renderbuffer;

    /// @var sampler
    /// @glconstwrap{SAMPLER}
    opt_constant<
      mp_list<oglplus::object_type>,
#ifdef GL_SAMPLER
      enum_type_c<GL_SAMPLER>>
#else
      enum_type_i>
#endif
      sampler;

    /// @var shader
    /// @glconstwrap{SHADER}
    opt_constant<
      mp_list<oglplus::object_type>,
#ifdef GL_SHADER
      enum_type_c<GL_SHADER>>
#else
      enum_type_i>
#endif
      shader;

    /// @var texture
    /// @glconstwrap{TEXTURE}
    opt_constant<
      mp_list<oglplus::object_type, matrix_mode>,
#ifdef GL_TEXTURE
      enum_type_c<GL_TEXTURE>>
#else
      enum_type_i>
#endif
      texture;

    /// @var transform_feedback
    /// @glconstwrap{TRANSFORM_FEEDBACK}
    opt_constant<
      mp_list<oglplus::object_type, transform_feedback_target>,
#ifdef GL_TRANSFORM_FEEDBACK
      enum_type_c<GL_TRANSFORM_FEEDBACK>>
#else
      enum_type_i>
#endif
      transform_feedback;

    /// @var vertex_array
    /// @glconstwrap{VERTEX_ARRAY}
    opt_constant<
      mp_list<oglplus::object_type, client_capability>,
#ifdef GL_VERTEX_ARRAY
      enum_type_c<GL_VERTEX_ARRAY>>
#else
      enum_type_i>
#endif
      vertex_array;

    /// @var vertex_shader
    /// @glconstwrap{VERTEX_SHADER}
    opt_constant<
      mp_list<oglplus::shader_type, program_pipeline_parameter>,
#ifdef GL_VERTEX_SHADER
      enum_type_c<GL_VERTEX_SHADER>>
#else
      enum_type_i>
#endif
      vertex_shader;

    /// @var tess_control_shader
    /// @glconstwrap{TESS_CONTROL_SHADER}
    opt_constant<
      mp_list<oglplus::shader_type, program_pipeline_parameter>,
#ifdef GL_TESS_CONTROL_SHADER
      enum_type_c<GL_TESS_CONTROL_SHADER>>
#else
      enum_type_i>
#endif
      tess_control_shader;

    /// @var tess_evaluation_shader
    /// @glconstwrap{TESS_EVALUATION_SHADER}
    opt_constant<
      mp_list<oglplus::shader_type, program_pipeline_parameter>,
#ifdef GL_TESS_EVALUATION_SHADER
      enum_type_c<GL_TESS_EVALUATION_SHADER>>
#else
      enum_type_i>
#endif
      tess_evaluation_shader;

    /// @var geometry_shader
    /// @glconstwrap{GEOMETRY_SHADER}
    opt_constant<
      mp_list<oglplus::shader_type, program_pipeline_parameter>,
#ifdef GL_GEOMETRY_SHADER
      enum_type_c<GL_GEOMETRY_SHADER>>
#else
      enum_type_i>
#endif
      geometry_shader;

    /// @var fragment_shader
    /// @glconstwrap{FRAGMENT_SHADER}
    opt_constant<
      mp_list<oglplus::shader_type, program_pipeline_parameter>,
#ifdef GL_FRAGMENT_SHADER
      enum_type_c<GL_FRAGMENT_SHADER>>
#else
      enum_type_i>
#endif
      fragment_shader;

    /// @var compute_shader
    /// @glconstwrap{COMPUTE_SHADER}
    opt_constant<
      mp_list<oglplus::shader_type>,
#ifdef GL_COMPUTE_SHADER
      enum_type_c<GL_COMPUTE_SHADER>>
#else
      enum_type_i>
#endif
      compute_shader;

    /// @var shader_include
    /// @glconstwrap{SHADER_INCLUDE}
    opt_constant<
      mp_list<named_string_kind>,
#ifdef GL_SHADER_INCLUDE_ARB
      enum_type_c<GL_SHADER_INCLUDE_ARB>>
#else
      enum_type_c<0x8DAE>>
#endif
      shader_include;

    /// @var sync_fence
    /// @glconstwrap{SYNC_FENCE}
    opt_constant<
      mp_list<sync_type>,
#ifdef GL_SYNC_FENCE
      enum_type_c<GL_SYNC_FENCE>>
#else
      enum_type_i>
#endif
      sync_fence;

    /// @var sync_gpu_commands_complete
    /// @glconstwrap{SYNC_GPU_COMMANDS_COMPLETE}
    opt_constant<
      mp_list<oglplus::sync_condition, sync_parameter>,
#ifdef GL_SYNC_GPU_COMMANDS_COMPLETE
      enum_type_c<GL_SYNC_GPU_COMMANDS_COMPLETE>>
#else
      enum_type_i>
#endif
      sync_gpu_commands_complete;

    /// @var signaled
    /// @glconstwrap{SIGNALED}
    opt_constant<
      mp_list<oglplus::sync_status>,
#ifdef GL_SIGNALED
      enum_type_c<GL_SIGNALED>>
#else
      enum_type_i>
#endif
      signaled;

    /// @var unsignaled
    /// @glconstwrap{UNSIGNALED}
    opt_constant<
      mp_list<oglplus::sync_status>,
#ifdef GL_UNSIGNALED
      enum_type_c<GL_UNSIGNALED>>
#else
      enum_type_i>
#endif
      unsignaled;

    /// @var object_type
    /// @glconstwrap{OBJECT_TYPE}
    opt_constant<
      mp_list<sync_parameter>,
#ifdef GL_OBJECT_TYPE
      enum_type_c<GL_OBJECT_TYPE>>
#else
      enum_type_i>
#endif
      object_type;

    /// @var sync_status
    /// @glconstwrap{SYNC_STATUS}
    opt_constant<
      mp_list<sync_parameter>,
#ifdef GL_SYNC_STATUS
      enum_type_c<GL_SYNC_STATUS>>
#else
      enum_type_i>
#endif
      sync_status;

    /// @var sync_condition
    /// @glconstwrap{SYNC_CONDITION}
    opt_constant<
      mp_list<sync_parameter>,
#ifdef GL_SYNC_CONDITION
      enum_type_c<GL_SYNC_CONDITION>>
#else
      enum_type_i>
#endif
      sync_condition;

    /// @var sync_wait_result
    /// @glconstwrap{SYNC_WAIT_RESULT}
    opt_constant<
      mp_list<sync_wait_result>,
#ifdef GL_CONDITION_SATISFIED
      enum_type_c<GL_CONDITION_SATISFIED>>
#else
      enum_type_i>
#endif
      condition_satisfied;

    /// @var already_signaled
    /// @glconstwrap{ALREADY_SIGNALED}
    opt_constant<
      mp_list<sync_wait_result>,
#ifdef GL_ALREADY_SIGNALED
      enum_type_c<GL_ALREADY_SIGNALED>>
#else
      enum_type_i>
#endif
      already_signaled;

    /// @var timeout_expired
    /// @glconstwrap{TIMEOUT_EXPIRED}
    opt_constant<
      mp_list<sync_wait_result>,
#ifdef GL_TIMEOUT_EXPIRED
      enum_type_c<GL_TIMEOUT_EXPIRED>>
#else
      enum_type_i>
#endif
      timeout_expired;

    /// @var wait_failed
    /// @glconstwrap{WAIT_FAILED}
    opt_constant<
      mp_list<sync_wait_result>,
#ifdef GL_WAIT_FAILED
      enum_type_c<GL_WAIT_FAILED>>
#else
      enum_type_i>
#endif
      wait_failed;

    /// @var shader_type
    /// @glconstwrap{SHADER_TYPE}
    opt_constant<
      mp_list<shader_parameter>,
#ifdef GL_SHADER_TYPE
      enum_type_c<GL_SHADER_TYPE>,
#else
      enum_type_i,
#endif
      oglplus::shader_type>
      shader_type;

    /// @var compute_shader_bit
    /// @glconstwrap{COMPUTE_SHADER_BIT}
    opt_constant<
      mp_list<program_stage_bit>,
#ifdef GL_COMPUTE_SHADER_BIT
      bitfield_type_c<GL_COMPUTE_SHADER_BIT>>
#else
      bitfield_type_i>
#endif
      compute_shader_bit;

    /// @var vertex_shader_bit
    /// @glconstwrap{VERTEX_SHADER_BIT}
    opt_constant<
      mp_list<program_stage_bit>,
#ifdef GL_VERTEX_SHADER_BIT
      bitfield_type_c<GL_VERTEX_SHADER_BIT>>
#else
      bitfield_type_i>
#endif
      vertex_shader_bit;

    /// @var tess_control_shader_bit
    /// @glconstwrap{TESS_CONTROL_SHADER_BIT}
    opt_constant<
      mp_list<program_stage_bit>,
#ifdef GL_TESS_CONTROL_SHADER_BIT
      bitfield_type_c<GL_TESS_CONTROL_SHADER_BIT>>
#else
      bitfield_type_i>
#endif
      tess_control_shader_bit;

    /// @var tess_evaluation_shader_bit
    /// @glconstwrap{TESS_EVALUATION_SHADER_BIT}
    opt_constant<
      mp_list<program_stage_bit>,
#ifdef GL_TESS_EVALUATION_SHADER_BIT
      bitfield_type_c<GL_TESS_EVALUATION_SHADER_BIT>>
#else
      bitfield_type_i>
#endif
      tess_evaluation_shader_bit;

    /// @var geometry_shader_bit
    /// @glconstwrap{GEOMETRY_SHADER_BIT}
    opt_constant<
      mp_list<program_stage_bit>,
#ifdef GL_GEOMETRY_SHADER_BIT
      bitfield_type_c<GL_GEOMETRY_SHADER_BIT>>
#else
      bitfield_type_i>
#endif
      geometry_shader_bit;

    /// @var fragment_shader_bit
    /// @glconstwrap{FRAGMENT_SHADER_BIT}
    opt_constant<
      mp_list<program_stage_bit>,
#ifdef GL_FRAGMENT_SHADER_BIT
      bitfield_type_c<GL_FRAGMENT_SHADER_BIT>>
#else
      bitfield_type_i>
#endif
      fragment_shader_bit;

    /// @var all_shader_bits
    /// @glconstwrap{ALL_SHADER_BITS}
    opt_constant<
      mp_list<program_stage_bit>,
#ifdef GL_ALL_SHADER_BITS
      bitfield_type_c<GL_ALL_SHADER_BITS>>
#else
      bitfield_type_i>
#endif
      all_shader_bits;

    /// @var active_subroutine_uniforms
    /// @glconstwrap{ACTIVE_SUBROUTINE_UNIFORMS}
    opt_constant<
      mp_list<program_stage_parameter>,
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORMS
      enum_type_c<GL_ACTIVE_SUBROUTINE_UNIFORMS>>
#else
      enum_type_i>
#endif
      active_subroutine_uniforms;

    /// @var active_subroutine_uniform_locations
    /// @glconstwrap{ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS}
    opt_constant<
      mp_list<program_stage_parameter>,
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS
      enum_type_c<GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS>>
#else
      enum_type_i>
#endif
      active_subroutine_uniform_locations;

    /// @var active_subroutines
    /// @glconstwrap{ACTIVE_SUBROUTINES}
    opt_constant<
      mp_list<program_stage_parameter>,
#ifdef GL_ACTIVE_SUBROUTINES
      enum_type_c<GL_ACTIVE_SUBROUTINES>>
#else
      enum_type_i>
#endif
      active_subroutines;

    /// @var active_subroutine_uniform_max_length
    /// @glconstwrap{ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH}
    opt_constant<
      mp_list<program_stage_parameter>,
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH
      enum_type_c<GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH>>
#else
      enum_type_i>
#endif
      active_subroutine_uniform_max_length;

    /// @var active_subroutine_max_length
    /// @glconstwrap{ACTIVE_SUBROUTINE_MAX_LENGTH}
    opt_constant<
      mp_list<program_stage_parameter>,
#ifdef GL_ACTIVE_SUBROUTINE_MAX_LENGTH
      enum_type_c<GL_ACTIVE_SUBROUTINE_MAX_LENGTH>>
#else
      enum_type_i>
#endif
      active_subroutine_max_length;

    /// @var delete_status
    /// @glconstwrap{DELETE_STATUS}
    opt_constant<
      mp_list<shader_parameter, program_parameter>,
#ifdef GL_DELETE_STATUS
      enum_type_c<GL_DELETE_STATUS>,
#else
      enum_type_i,
#endif
      true_false>
      delete_status;

    /// @var compile_status
    /// @glconstwrap{COMPILE_STATUS}
    opt_constant<
      mp_list<shader_parameter>,
#ifdef GL_COMPILE_STATUS
      enum_type_c<GL_COMPILE_STATUS>,
#else
      enum_type_i,
#endif
      true_false>
      compile_status;

    /// @var info_log_length
    /// @glconstwrap{INFO_LOG_LENGTH}
    opt_constant<
      mp_list<shader_parameter, program_parameter, program_pipeline_parameter>,
#ifdef GL_INFO_LOG_LENGTH
      enum_type_c<GL_INFO_LOG_LENGTH>>
#else
      enum_type_i>
#endif
      info_log_length;

    /// @var shader_source_length
    /// @glconstwrap{SHADER_SOURCE_LENGTH}
    opt_constant<
      mp_list<shader_parameter>,
#ifdef GL_SHADER_SOURCE_LENGTH
      enum_type_c<GL_SHADER_SOURCE_LENGTH>>
#else
      enum_type_i>
#endif
      shader_source_length;

    /// @var spir_v_binary
    /// @glconstwrap{SPIR_V_BINARY}
    opt_constant<
      mp_list<shader_parameter>,
#ifdef GL_SPIR_V_BINARY
      enum_type_c<GL_SPIR_V_BINARY>,
#else
      enum_type_i,
#endif
      true_false>
      spir_v_binary;

    /// @var program_separable
    /// @glconstwrap{PROGRAM_SEPARABLE}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_PROGRAM_SEPARABLE
      enum_type_c<GL_PROGRAM_SEPARABLE>,
#else
      enum_type_i,
#endif
      true_false>
      program_separable;

    /// @var completion_status
    /// @glconstwrap{COMPLETION_STATUS}
    opt_constant<
      mp_list<shader_parameter, program_parameter>,
#ifdef GL_COMPLETION_STATUS_ARB
      enum_type_c<GL_COMPLETION_STATUS_ARB>,
#else
      enum_type_i,
#endif
      true_false>
      completion_status;

    /// @var link_status
    /// @glconstwrap{LINK_STATUS}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_LINK_STATUS
      enum_type_c<GL_LINK_STATUS>,
#else
      enum_type_i,
#endif
      true_false>
      link_status;

    /// @var validate_status
    /// @glconstwrap{VALIDATE_STATUS}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_VALIDATE_STATUS
      enum_type_c<GL_VALIDATE_STATUS>,
#else
      enum_type_i,
#endif
      true_false>
      validate_status;

    /// @var attached_shaders
    /// @glconstwrap{ATTACHED_SHADERS}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_ATTACHED_SHADERS
      enum_type_c<GL_ATTACHED_SHADERS>>
#else
      enum_type_i>
#endif
      attached_shaders;

    /// @var active_atomic_counter_buffers
    /// @glconstwrap{ACTIVE_ATOMIC_COUNTER_BUFFERS}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_ACTIVE_ATOMIC_COUNTER_BUFFERS
      enum_type_c<GL_ACTIVE_ATOMIC_COUNTER_BUFFERS>>
#else
      enum_type_i>
#endif
      active_atomic_counter_buffers;

    /// @var active_attributes
    /// @glconstwrap{ACTIVE_ATTRIBUTES}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_ACTIVE_ATTRIBUTES
      enum_type_c<GL_ACTIVE_ATTRIBUTES>>
#else
      enum_type_i>
#endif
      active_attributes;

    /// @var active_attribute_max_length
    /// @glconstwrap{ACTIVE_ATTRIBUTE_MAX_LENGTH}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
      enum_type_c<GL_ACTIVE_ATTRIBUTE_MAX_LENGTH>>
#else
      enum_type_i>
#endif
      active_attribute_max_length;

    /// @var active_uniforms
    /// @glconstwrap{ACTIVE_UNIFORMS}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_ACTIVE_UNIFORMS
      enum_type_c<GL_ACTIVE_UNIFORMS>>
#else
      enum_type_i>
#endif
      active_uniforms;

    /// @var active_uniform_max_length
    /// @glconstwrap{ACTIVE_UNIFORM_MAX_LENGTH}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_ACTIVE_UNIFORM_MAX_LENGTH
      enum_type_c<GL_ACTIVE_UNIFORM_MAX_LENGTH>>
#else
      enum_type_i>
#endif
      active_uniform_max_length;

    /// @var program_binary_length
    /// @glconstwrap{PROGRAM_BINARY_LENGTH}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_PROGRAM_BINARY_LENGTH
      enum_type_c<GL_PROGRAM_BINARY_LENGTH>>
#else
      enum_type_i>
#endif
      program_binary_length;

    /// @var compute_work_group_size
    /// @glconstwrap{COMPUTE_WORK_GROUP_SIZE}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_COMPUTE_WORK_GROUP_SIZE
      enum_type_c<GL_COMPUTE_WORK_GROUP_SIZE>>
#else
      enum_type_i>
#endif
      compute_work_group_size;

    /// @var transform_feedback_buffer_mode
    /// @glconstwrap{TRANSFORM_FEEDBACK_BUFFER_MODE}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_MODE
      enum_type_c<GL_TRANSFORM_FEEDBACK_BUFFER_MODE>>
#else
      enum_type_i>
#endif
      transform_feedback_buffer_mode;

    /// @var transform_feedback_varyings
    /// @glconstwrap{TRANSFORM_FEEDBACK_VARYINGS}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_TRANSFORM_FEEDBACK_VARYINGS
      enum_type_c<GL_TRANSFORM_FEEDBACK_VARYINGS>>
#else
      enum_type_i>
#endif
      transform_feedback_varyings;

    /// @var transform_feedback_varying_max_length
    /// @glconstwrap{TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH
      enum_type_c<GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH>>
#else
      enum_type_i>
#endif
      transform_feedback_varying_max_length;

    /// @var geometry_vertices_out
    /// @glconstwrap{GEOMETRY_VERTICES_OUT}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_GEOMETRY_VERTICES_OUT
      enum_type_c<GL_GEOMETRY_VERTICES_OUT>>
#else
      enum_type_i>
#endif
      geometry_vertices_out;

    /// @var geometry_input_type
    /// @glconstwrap{GEOMETRY_INPUT_TYPE}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_GEOMETRY_INPUT_TYPE
      enum_type_c<GL_GEOMETRY_INPUT_TYPE>>
#else
      enum_type_i>
#endif
      geometry_input_type;

    /// @var geometry_output_type
    /// @glconstwrap{GEOMETRY_OUTPUT_TYPE}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_GEOMETRY_OUTPUT_TYPE
      enum_type_c<GL_GEOMETRY_OUTPUT_TYPE>>
#else
      enum_type_i>
#endif
      geometry_output_type;

    /// @var tess_gen_point_mode
    /// @glconstwrap{TESS_GEN_POINT_MODE}
    opt_constant<
      mp_list<program_parameter>,
#ifdef GL_TESS_GEN_POINT_MODE
      enum_type_c<GL_TESS_GEN_POINT_MODE>>
#else
      enum_type_i>
#endif
      tess_gen_point_mode;

    /// @var program_binary_format_mesa
    /// @glconstwrap{PROGRAM_BINARY_FORMAT_MESA}
    opt_constant<
      mp_list<program_binary_format>,
#ifdef GL_PROGRAM_BINARY_FORMAT_MESA
      enum_type_c<GL_PROGRAM_BINARY_FORMAT_MESA>>
#else
      enum_type_i>
#endif
      program_binary_format_mesa;

    /// @var active_program
    /// @glconstwrap{ACTIVE_PROGRAM}
    opt_constant<
      mp_list<program_pipeline_parameter>,
#ifdef GL_ACTIVE_PROGRAM
      enum_type_c<GL_ACTIVE_PROGRAM>>
#else
      enum_type_i>
#endif
      active_program;

    /// @var renderbuffer_width
    /// @glconstwrap{RENDERBUFFER_WIDTH}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_WIDTH
      enum_type_c<GL_RENDERBUFFER_WIDTH>>
#else
      enum_type_i>
#endif
      renderbuffer_width;

    /// @var renderbuffer_height
    /// @glconstwrap{RENDERBUFFER_HEIGHT}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_HEIGHT
      enum_type_c<GL_RENDERBUFFER_HEIGHT>>
#else
      enum_type_i>
#endif
      renderbuffer_height;

    /// @var renderbuffer_internal_format
    /// @glconstwrap{RENDERBUFFER_INTERNAL_FORMAT}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_INTERNAL_FORMAT
      enum_type_c<GL_RENDERBUFFER_INTERNAL_FORMAT>>
#else
      enum_type_i>
#endif
      renderbuffer_internal_format;

    /// @var renderbuffer_samples
    /// @glconstwrap{RENDERBUFFER_SAMPLES}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_SAMPLES
      enum_type_c<GL_RENDERBUFFER_SAMPLES>>
#else
      enum_type_i>
#endif
      renderbuffer_samples;

    /// @var renderbuffer_red_size
    /// @glconstwrap{RENDERBUFFER_RED_SIZE}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_RED_SIZE
      enum_type_c<GL_RENDERBUFFER_RED_SIZE>>
#else
      enum_type_i>
#endif
      renderbuffer_red_size;

    /// @var renderbuffer_green_size
    /// @glconstwrap{RENDERBUFFER_GREEN_SIZE}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_GREEN_SIZE
      enum_type_c<GL_RENDERBUFFER_GREEN_SIZE>>
#else
      enum_type_i>
#endif
      renderbuffer_green_size;

    /// @var renderbuffer_blue_size
    /// @glconstwrap{RENDERBUFFER_BLUE_SIZE}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_BLUE_SIZE
      enum_type_c<GL_RENDERBUFFER_BLUE_SIZE>>
#else
      enum_type_i>
#endif
      renderbuffer_blue_size;

    /// @var renderbuffer_alpha_size
    /// @glconstwrap{RENDERBUFFER_ALPHA_SIZE}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_ALPHA_SIZE
      enum_type_c<GL_RENDERBUFFER_ALPHA_SIZE>>
#else
      enum_type_i>
#endif
      renderbuffer_alpha_size;

    /// @var renderbuffer_depth_size
    /// @glconstwrap{RENDERBUFFER_DEPTH_SIZE}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_DEPTH_SIZE
      enum_type_c<GL_RENDERBUFFER_DEPTH_SIZE>>
#else
      enum_type_i>
#endif
      renderbuffer_depth_size;

    /// @var renderbuffer_stencil_size
    /// @glconstwrap{RENDERBUFFER_STENCIL_SIZE}
    opt_constant<
      mp_list<renderbuffer_parameter>,
#ifdef GL_RENDERBUFFER_STENCIL_SIZE
      enum_type_c<GL_RENDERBUFFER_STENCIL_SIZE>>
#else
      enum_type_i>
#endif
      renderbuffer_stencil_size;

    /// @var framebuffer_framebuffer
    /// @glconstwrap{FRAMEBUFFER_FRAMEBUFFER}
    opt_constant<
      mp_list<framebuffer_target>,
#ifdef GL_FRAMEBUFFER_FRAMEBUFFER
      enum_type_c<GL_FRAMEBUFFER_FRAMEBUFFER>>
#else
      enum_type_i>
#endif
      framebuffer_framebuffer;

    /// @var draw_framebuffer
    /// @glconstwrap{DRAW_FRAMEBUFFER}
    opt_constant<
      mp_list<framebuffer_target>,
#ifdef GL_DRAW_FRAMEBUFFER
      enum_type_c<GL_DRAW_FRAMEBUFFER>>
#else
      enum_type_i>
#endif
      draw_framebuffer;

    /// @var read_framebuffer
    /// @glconstwrap{READ_FRAMEBUFFER}
    opt_constant<
      mp_list<framebuffer_target>,
#ifdef GL_READ_FRAMEBUFFER
      enum_type_c<GL_READ_FRAMEBUFFER>>
#else
      enum_type_i>
#endif
      read_framebuffer;

    /// @var framebuffer_complete
    /// @glconstwrap{FRAMEBUFFER_COMPLETE}
    opt_constant<
      mp_list<framebuffer_status>,
#ifdef GL_FRAMEBUFFER_COMPLETE
      enum_type_c<GL_FRAMEBUFFER_COMPLETE>>
#else
      enum_type_i>
#endif
      framebuffer_complete;

    /// @var framebuffer_undefined
    /// @glconstwrap{FRAMEBUFFER_UNDEFINED}
    opt_constant<
      mp_list<framebuffer_status>,
#ifdef GL_FRAMEBUFFER_UNDEFINED
      enum_type_c<GL_FRAMEBUFFER_UNDEFINED>>
#else
      enum_type_i>
#endif
      framebuffer_undefined;

    /// @var framebuffer_incomplete_attachment
    /// @glconstwrap{FRAMEBUFFER_INCOMPLETE_ATTACHMENT}
    opt_constant<
      mp_list<framebuffer_status>,
#ifdef GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
      enum_type_c<GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT>>
#else
      enum_type_i>
#endif
      framebuffer_incomplete_attachment;

    /// @var framebuffer_incomplete_missing_attachment
    /// @glconstwrap{FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT}
    opt_constant<
      mp_list<framebuffer_status>,
#ifdef GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
      enum_type_c<GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT>>
#else
      enum_type_i>
#endif
      framebuffer_incomplete_missing_attachment;

    /// @var framebuffer_unsupported
    /// @glconstwrap{FRAMEBUFFER_UNSUPPORTED}
    opt_constant<
      mp_list<framebuffer_status>,
#ifdef GL_FRAMEBUFFER_UNSUPPORTED
      enum_type_c<GL_FRAMEBUFFER_UNSUPPORTED>>
#else
      enum_type_i>
#endif
      framebuffer_unsupported;

    /// @var framebuffer_incomplete_multisample
    /// @glconstwrap{FRAMEBUFFER_INCOMPLETE_MULTISAMPLE}
    opt_constant<
      mp_list<framebuffer_status>,
#ifdef GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
      enum_type_c<GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      framebuffer_incomplete_multisample;

    /// @var framebuffer_incomplete_layer_targets
    /// @glconstwrap{FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS}
    opt_constant<
      mp_list<framebuffer_status>,
#ifdef GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
      enum_type_c<GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS>>
#else
      enum_type_i>
#endif
      framebuffer_incomplete_layer_targets;

    /// @var framebuffer_default_width
    /// @glconstwrap{FRAMEBUFFER_DEFAULT_WIDTH}
    opt_constant<
      mp_list<framebuffer_parameter>,
#ifdef GL_FRAMEBUFFER_DEFAULT_WIDTH
      enum_type_c<GL_FRAMEBUFFER_DEFAULT_WIDTH>>
#else
      enum_type_i>
#endif
      framebuffer_default_width;

    /// @var framebuffer_default_height
    /// @glconstwrap{FRAMEBUFFER_DEFAULT_HEIGHT}
    opt_constant<
      mp_list<framebuffer_parameter>,
#ifdef GL_FRAMEBUFFER_DEFAULT_HEIGHT
      enum_type_c<GL_FRAMEBUFFER_DEFAULT_HEIGHT>>
#else
      enum_type_i>
#endif
      framebuffer_default_height;

    /// @var framebuffer_default_layers
    /// @glconstwrap{FRAMEBUFFER_DEFAULT_LAYERS}
    opt_constant<
      mp_list<framebuffer_parameter>,
#ifdef GL_FRAMEBUFFER_DEFAULT_LAYERS
      enum_type_c<GL_FRAMEBUFFER_DEFAULT_LAYERS>>
#else
      enum_type_i>
#endif
      framebuffer_default_layers;

    /// @var framebuffer_default_samples
    /// @glconstwrap{FRAMEBUFFER_DEFAULT_SAMPLES}
    opt_constant<
      mp_list<framebuffer_parameter>,
#ifdef GL_FRAMEBUFFER_DEFAULT_SAMPLES
      enum_type_c<GL_FRAMEBUFFER_DEFAULT_SAMPLES>>
#else
      enum_type_i>
#endif
      framebuffer_default_samples;

    /// @var framebuffer_default_fixed_sample_locations
    /// @glconstwrap{FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS}
    opt_constant<
      mp_list<framebuffer_parameter>,
#ifdef GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
      enum_type_c<GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS>>
#else
      enum_type_i>
#endif
      framebuffer_default_fixed_sample_locations;

    /// @var framebuffer_attachment_red_size
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_RED_SIZE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_red_size;

    /// @var framebuffer_attachment_green_size
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_GREEN_SIZE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_green_size;

    /// @var framebuffer_attachment_blue_size
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_BLUE_SIZE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_blue_size;

    /// @var framebuffer_attachment_alpha_size
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_alpha_size;

    /// @var framebuffer_attachment_depth_size
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_depth_size;

    /// @var framebuffer_attachment_stencil_size
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_stencil_size;

    /// @var framebuffer_attachment_component_type
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_component_type;

    /// @var framebuffer_attachment_color_encoding
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_color_encoding;

    /// @var framebuffer_attachment_object_type
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_object_type;

    /// @var framebuffer_attachment_object_name
    /// @glconstwrap{framebuffer_attachment_object_name}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_object_name;

    /// @var framebuffer_attachment_texture_level
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_texture_level;

    /// @var framebuffer_attachment_texture_cube_map_face
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_texture_cube_map_face;

    /// @var framebuffer_attachment_layered
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_LAYERED}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_LAYERED
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_LAYERED>,
#else
      enum_type_i,
#endif
      true_false>
      framebuffer_attachment_layered;

    /// @var framebuffer_attachment_texture_layer
    /// @glconstwrap{FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER}
    opt_constant<
      mp_list<framebuffer_attachment_parameter>,
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER
      enum_type_c<GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER>>
#else
      enum_type_i>
#endif
      framebuffer_attachment_texture_layer;

    /// @var color_attachment0
    /// @glconstwrap{COLOR_ATTACHMENT0}
    opt_constant<
      mp_list<framebuffer_attachment>,
#ifdef GL_COLOR_ATTACHMENT0
      enum_type_c<GL_COLOR_ATTACHMENT0>,
#else
      enum_type_i,
#endif
      nothing_t,
      true>
      color_attachment0;

    /// @var depth_attachment
    /// @glconstwrap{DEPTH_ATTACHMENT}
    opt_constant<
      mp_list<framebuffer_attachment>,
#ifdef GL_DEPTH_ATTACHMENT
      enum_type_c<GL_DEPTH_ATTACHMENT>>
#else
      enum_type_i>
#endif
      depth_attachment;

    /// @var stencil_attachment
    /// @glconstwrap{STENCIL_ATTACHMENT}
    opt_constant<
      mp_list<framebuffer_attachment>,
#ifdef GL_STENCIL_ATTACHMENT
      enum_type_c<GL_STENCIL_ATTACHMENT>>
#else
      enum_type_i>
#endif
      stencil_attachment;

    /// @var depth_stencil_attachment
    /// @glconstwrap{DEPTH_STENCIL_ATTACHMENT}
    opt_constant<
      mp_list<framebuffer_attachment>,
#ifdef GL_DEPTH_STENCIL_ATTACHMENT
      enum_type_c<GL_DEPTH_STENCIL_ATTACHMENT>>
#else
      enum_type_i>
#endif
      depth_stencil_attachment;

    /// @var color
    /// @glconstwrap{COLOR}
    opt_constant<
      mp_list<framebuffer_buffer, matrix_mode>,
#ifdef GL_COLOR
      enum_type_c<GL_COLOR>>
#else
      enum_type_i>
#endif
      color;

    /// @var depth
    /// @glconstwrap{DEPTH}
    opt_constant<
      mp_list<framebuffer_buffer, framebuffer_attachment>,
#ifdef GL_DEPTH
      enum_type_c<GL_DEPTH>>
#else
      enum_type_i>
#endif
      depth;

    /// @var stencil
    /// @glconstwrap{STENCIL}
    opt_constant<
      mp_list<framebuffer_buffer, framebuffer_attachment, pixel_format>,
#ifdef GL_STENCIL
      enum_type_c<GL_STENCIL>>
#else
      enum_type_i>
#endif
      stencil;

    /// @var array_buffer
    /// @glconstwrap{ARRAY_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_ARRAY_BUFFER
      enum_type_c<GL_ARRAY_BUFFER>>
#else
      enum_type_i>
#endif
      array_buffer;

    /// @var atomic_counter_buffer
    /// @glconstwrap{ATOMIC_COUNTER_BUFFER}
    opt_constant<
      mp_list<buffer_target, program_interface>,
#ifdef GL_ATOMIC_COUNTER_BUFFER
      enum_type_c<GL_ATOMIC_COUNTER_BUFFER>>
#else
      enum_type_i>
#endif
      atomic_counter_buffer;

    /// @var copy_read_buffer
    /// @glconstwrap{COPY_READ_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_COPY_READ_BUFFER
      enum_type_c<GL_COPY_READ_BUFFER>>
#else
      enum_type_i>
#endif
      copy_read_buffer;

    /// @var copy_write_buffer
    /// @glconstwrap{COPY_WRITE_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_COPY_WRITE_BUFFER
      enum_type_c<GL_COPY_WRITE_BUFFER>>
#else
      enum_type_i>
#endif
      copy_write_buffer;

    /// @var dispatch_indirect_buffer
    /// @glconstwrap{DISPATCH_INDIRECT_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_DISPATCH_INDIRECT_BUFFER
      enum_type_c<GL_DISPATCH_INDIRECT_BUFFER>>
#else
      enum_type_i>
#endif
      dispatch_indirect_buffer;

    /// @var draw_indirect_buffer
    /// @glconstwrap{DRAW_INDIRECT_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_DRAW_INDIRECT_BUFFER
      enum_type_c<GL_DRAW_INDIRECT_BUFFER>>
#else
      enum_type_i>
#endif
      draw_indirect_buffer;

    /// @var element_array_buffer
    /// @glconstwrap{ELEMENT_ARRAY_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_ELEMENT_ARRAY_BUFFER
      enum_type_c<GL_ELEMENT_ARRAY_BUFFER>>
#else
      enum_type_i>
#endif
      element_array_buffer;

    /// @var parameter_buffer
    /// @glconstwrap{PARAMETER_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_PARAMETER_BUFFER
      enum_type_c<GL_PARAMETER_BUFFER>>
#else
      enum_type_i>
#endif
      parameter_buffer;

    /// @var pixel_pack_buffer
    /// @glconstwrap{PIXEL_PACK_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_PIXEL_PACK_BUFFER
      enum_type_c<GL_PIXEL_PACK_BUFFER>>
#else
      enum_type_i>
#endif
      pixel_pack_buffer;

    /// @var pixel_unpack_buffer
    /// @glconstwrap{PIXEL_UNPACK_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_PIXEL_UNPACK_BUFFER
      enum_type_c<GL_PIXEL_UNPACK_BUFFER>>
#else
      enum_type_i>
#endif
      pixel_unpack_buffer;

    /// @var query_buffer
    /// @glconstwrap{QUERY_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_QUERY_BUFFER
      enum_type_c<GL_QUERY_BUFFER>>
#else
      enum_type_i>
#endif
      query_buffer;

    /// @var shader_storage_buffer
    /// @glconstwrap{SHADER_STORAGE_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_SHADER_STORAGE_BUFFER
      enum_type_c<GL_SHADER_STORAGE_BUFFER>>
#else
      enum_type_i>
#endif
      shader_storage_buffer;

    /// @var texture_buffer
    /// @glconstwrap{TEXTURE_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_TEXTURE_BUFFER
      enum_type_c<GL_TEXTURE_BUFFER>>
#else
      enum_type_i>
#endif
      texture_buffer;

    /// @var transform_feedback_buffer
    /// @glconstwrap{TRANSFORM_FEEDBACK_BUFFER}
    opt_constant<
      mp_list<buffer_target, program_interface>,
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER
      enum_type_c<GL_TRANSFORM_FEEDBACK_BUFFER>>
#else
      enum_type_i>
#endif
      transform_feedback_buffer;

    /// @var uniform_buffer
    /// @glconstwrap{UNIFORM_BUFFER}
    opt_constant<
      mp_list<buffer_target>,
#ifdef GL_UNIFORM_BUFFER
      enum_type_c<GL_UNIFORM_BUFFER>>
#else
      enum_type_i>
#endif
      uniform_buffer;

    /// @var buffer_access
    /// @glconstwrap{BUFFER_ACCESS}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_ACCESS
      enum_type_c<GL_BUFFER_ACCESS>,
#else
      enum_type_i,
#endif
      access_specifier>
      buffer_access;

    /// @var buffer_access_flags
    /// @glconstwrap{BUFFER_ACCESS_FLAGS}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_ACCESS_FLAGS
      enum_type_c<GL_BUFFER_ACCESS_FLAGS>,
#else
      enum_type_i,
#endif
      c_api::enum_bitfield<buffer_map_access_bit>>
      buffer_access_flags;

    /// @var buffer_immutable_storage
    /// @glconstwrap{BUFFER_IMMUTABLE_STORAGE}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_IMMUTABLE_STORAGE
      enum_type_c<GL_BUFFER_IMMUTABLE_STORAGE>,
#else
      enum_type_i,
#endif
      true_false>
      buffer_immutable_storage;

    /// @var buffer_mapped
    /// @glconstwrap{BUFFER_MAPPED}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_MAPPED
      enum_type_c<GL_BUFFER_MAPPED>,
#else
      enum_type_i,
#endif
      true_false>
      buffer_mapped;

    /// @var buffer_map_length
    /// @glconstwrap{buffer_map_length}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_MAP_LENGTH
      enum_type_c<GL_BUFFER_MAP_LENGTH>>
#else
      enum_type_i>
#endif
      buffer_map_length;

    /// @var buffer_map_offset
    /// @glconstwrap{BUFFER_MAP_OFFSET}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_MAP_OFFSET
      enum_type_c<GL_BUFFER_MAP_OFFSET>>
#else
      enum_type_i>
#endif
      buffer_map_offset;

    /// @var buffer_size
    /// @glconstwrap{BUFFER_SIZE}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_SIZE
      enum_type_c<GL_BUFFER_SIZE>>
#else
      enum_type_i>
#endif
      buffer_size;

    /// @var buffer_storage_flags
    /// @glconstwrap{BUFFER_STORAGE_FLAGS}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_STORAGE_FLAGS
      enum_type_c<GL_BUFFER_STORAGE_FLAGS>,
#else
      enum_type_i,
#endif
      c_api::enum_bitfield<buffer_storage_bit>>
      buffer_storage_flags;

    /// @var buffer_usage
    /// @glconstwrap{BUFFER_USAGE}
    opt_constant<
      mp_list<buffer_parameter>,
#ifdef GL_BUFFER_USAGE
      enum_type_c<GL_BUFFER_USAGE>,
#else
      enum_type_i,
#endif
      oglplus::buffer_usage>
      buffer_usage;

    /// @var stream_draw
    /// @glconstwrap{STREAM_DRAW}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_STREAM_DRAW
      enum_type_c<GL_STREAM_DRAW>>
#else
      enum_type_i>
#endif
      stream_draw;

    /// @var stream_read
    /// @glconstwrap{STREAM_READ}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_STREAM_READ
      enum_type_c<GL_STREAM_READ>>
#else
      enum_type_i>
#endif
      stream_read;

    /// @var stream_copy
    /// @glconstwrap{STREAM_COPY}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_STREAM_COPY
      enum_type_c<GL_STREAM_COPY>>
#else
      enum_type_i>
#endif
      stream_copy;

    /// @var static_draw
    /// @glconstwrap{STATIC_DRAW}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_STATIC_DRAW
      enum_type_c<GL_STATIC_DRAW>>
#else
      enum_type_i>
#endif
      static_draw;

    /// @var static_read
    /// @glconstwrap{STATIC_READ}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_STATIC_READ
      enum_type_c<GL_STATIC_READ>>
#else
      enum_type_i>
#endif
      static_read;

    /// @var static_copy
    /// @glconstwrap{STATIC_COPY}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_STATIC_COPY
      enum_type_c<GL_STATIC_COPY>>
#else
      enum_type_i>
#endif
      static_copy;

    /// @var dynamic_draw
    /// @glconstwrap{DYNAMIC_DRAW}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_DYNAMIC_DRAW
      enum_type_c<GL_DYNAMIC_DRAW>>
#else
      enum_type_i>
#endif
      dynamic_draw;

    /// @var dynamic_read
    /// @glconstwrap{DYNAMIC_READ}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_DYNAMIC_READ
      enum_type_c<GL_DYNAMIC_READ>>
#else
      enum_type_i>
#endif
      dynamic_read;

    /// @var dynamic_copy
    /// @glconstwrap{DYNAMIC_COPY}
    opt_constant<
      mp_list<oglplus::buffer_usage>,
#ifdef GL_DYNAMIC_COPY
      enum_type_c<GL_DYNAMIC_COPY>>
#else
      enum_type_i>
#endif
      dynamic_copy;

    /// @var map_read_bit
    /// @glconstwrap{MAP_READ_BIT}
    opt_constant<
      mp_list<buffer_map_access_bit, buffer_storage_bit>,
#ifdef GL_MAP_READ_BIT
      bitfield_type_c<GL_MAP_READ_BIT>>
#else
      bitfield_type_i>
#endif
      map_read_bit;

    /// @var map_write_bit
    /// @glconstwrap{MAP_WRITE_BIT}
    opt_constant<
      mp_list<buffer_map_access_bit, buffer_storage_bit>,
#ifdef GL_MAP_WRITE_BIT
      bitfield_type_c<GL_MAP_WRITE_BIT>>
#else
      bitfield_type_i>
#endif
      map_write_bit;

    /// @var map_persistent_bit
    /// @glconstwrap{MAP_PERSISTENT_BIT}
    opt_constant<
      mp_list<buffer_map_access_bit, buffer_storage_bit>,
#ifdef GL_MAP_PERSISTENT_BIT
      bitfield_type_c<GL_MAP_PERSISTENT_BIT>>
#else
      bitfield_type_i>
#endif
      map_persistent_bit;

    /// @var map_coherent_bit
    /// @glconstwrap{MAP_COHERENT_BIT}
    opt_constant<
      mp_list<buffer_map_access_bit, buffer_storage_bit>,
#ifdef GL_MAP_COHERENT_BIT
      bitfield_type_c<GL_MAP_COHERENT_BIT>>
#else
      bitfield_type_i>
#endif
      map_coherent_bit;

    /// @var map_invalidate_range_bit
    /// @glconstwrap{MAP_INVALIDATE_RANGE_BIT}
    opt_constant<
      mp_list<buffer_map_access_bit>,
#ifdef GL_MAP_INVALIDATE_RANGE_BIT
      bitfield_type_c<GL_MAP_INVALIDATE_RANGE_BIT>>
#else
      bitfield_type_i>
#endif
      map_invalidate_range_bit;

    /// @var map_invalidate_buffer_bit
    /// @glconstwrap{MAP_INVALIDATE_BUFFER_BIT}
    opt_constant<
      mp_list<buffer_map_access_bit>,
#ifdef GL_MAP_INVALIDATE_BUFFER_BIT
      bitfield_type_c<GL_MAP_INVALIDATE_BUFFER_BIT>>
#else
      bitfield_type_i>
#endif
      map_invalidate_buffer_bit;

    /// @var map_flush_explicit_bit
    /// @glconstwrap{MAP_FLUSH_EXPLICIT_BIT}
    opt_constant<
      mp_list<buffer_map_access_bit>,
#ifdef GL_MAP_FLUSH_EXPLICIT_BIT
      bitfield_type_c<GL_MAP_FLUSH_EXPLICIT_BIT>>
#else
      bitfield_type_i>
#endif
      map_flush_explicit_bit;

    /// @var map_unsynchronized_bit
    /// @glconstwrap{MAP_UNSYNCHRONIZED_BIT}
    opt_constant<
      mp_list<buffer_map_access_bit>,
#ifdef GL_MAP_UNSYNCHRONIZED_BIT
      bitfield_type_c<GL_MAP_UNSYNCHRONIZED_BIT>>
#else
      bitfield_type_i>
#endif
      map_unsynchronized_bit;

    /// @var dynamic_storage_bit
    /// @glconstwrap{DYNAMIC_STORAGE_BIT}
    opt_constant<
      mp_list<buffer_storage_bit>,
#ifdef GL_DYNAMIC_STORAGE_BIT
      bitfield_type_c<GL_DYNAMIC_STORAGE_BIT>>
#else
      bitfield_type_i>
#endif
      dynamic_storage_bit;

    /// @var client_storage_bit
    /// @glconstwrap{CLIENT_STORAGE_BIT}
    opt_constant<
      mp_list<buffer_storage_bit>,
#ifdef GL_CLIENT_STORAGE_BIT
      bitfield_type_c<GL_CLIENT_STORAGE_BIT>>
#else
      bitfield_type_i>
#endif
      client_storage_bit;

    /// @var sparse_storage_bit
    /// @glconstwrap{SPARSE_STORAGE_BIT}
    opt_constant<
      mp_list<buffer_storage_bit>,
#ifdef GL_SPARSE_STORAGE_BIT_ARB
      bitfield_type_c<GL_SPARSE_STORAGE_BIT_ARB>>
#else
      bitfield_type_i>
#endif
      sparse_storage_bit;

    /// @var texture0
    /// @glconstwrap{TEXTURE0}
    opt_constant<
      mp_list<oglplus::texture_unit>,
#ifdef GL_TEXTURE0
      enum_type_c<GL_TEXTURE0>,
#else
      enum_type_i,
#endif
      nothing_t,
      true>
      texture0;

    /// @var texture_3d
    /// @glconstwrap{TEXTURE_3D}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_3D
      enum_type_c<GL_TEXTURE_3D>>
#else
      enum_type_i>
#endif
      texture_3d;

    /// @var texture_2d
    /// @glconstwrap{TEXTURE_2D}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_2D
      enum_type_c<GL_TEXTURE_2D>>
#else
      enum_type_i>
#endif
      texture_2d;

    /// @var texture_1d
    /// @glconstwrap{TEXTURE_1D}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_1D
      enum_type_c<GL_TEXTURE_1D>>
#else
      enum_type_i>
#endif
      texture_1d;

    /// @var texture_2d_array
    /// @glconstwrap{TEXTURE_2D_ARRAY}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_2D_ARRAY
      enum_type_c<GL_TEXTURE_2D_ARRAY>>
#else
      enum_type_i>
#endif
      texture_2d_array;

    /// @var texture_1d_array
    /// @glconstwrap{TEXTURE_1D_ARRAY}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_1D_ARRAY
      enum_type_c<GL_TEXTURE_1D_ARRAY>>
#else
      enum_type_i>
#endif
      texture_1d_array;

    /// @var texture_rectangle
    /// @glconstwrap{TEXTURE_RECTANGLE}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_RECTANGLE
      enum_type_c<GL_TEXTURE_RECTANGLE>>
#else
      enum_type_i>
#endif
      texture_rectangle;

    /// @var texture_cube_map
    /// @glconstwrap{TEXTURE_CUBE_MAP}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_CUBE_MAP
      enum_type_c<GL_TEXTURE_CUBE_MAP>>
#else
      enum_type_i>
#endif
      texture_cube_map;

    /// @var texture_cube_map_array
    /// @glconstwrap{TEXTURE_CUBE_MAP_ARRAY}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_CUBE_MAP_ARRAY
      enum_type_c<GL_TEXTURE_CUBE_MAP_ARRAY>>
#else
      enum_type_i>
#endif
      texture_cube_map_array;

    /// @var texture_2d_multisample
    /// @glconstwrap{TEXTURE_2D_MULTISAMPLE}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_2D_MULTISAMPLE
      enum_type_c<GL_TEXTURE_2D_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      texture_2d_multisample;

    /// @var texture_2d_multisample_array
    /// @glconstwrap{TEXTURE_2D_MULTISAMPLE_ARRAY}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_2D_MULTISAMPLE_ARRAY
      enum_type_c<GL_TEXTURE_2D_MULTISAMPLE_ARRAY>>
#else
      enum_type_i>
#endif
      texture_2d_multisample_array;

    /// @var texture_cube_map_positive_x
    /// @glconstwrap{TEXTURE_CUBE_MAP_POSITIVE_X}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_X
      enum_type_c<GL_TEXTURE_CUBE_MAP_POSITIVE_X>>
#else
      enum_type_i>
#endif
      texture_cube_map_positive_x;

    /// @var texture_cube_map_negative_x
    /// @glconstwrap{TEXTURE_CUBE_MAP_NEGATIVE_X}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_X
      enum_type_c<GL_TEXTURE_CUBE_MAP_NEGATIVE_X>>
#else
      enum_type_i>
#endif
      texture_cube_map_negative_x;

    /// @var texture_cube_map_positive_y
    /// @glconstwrap{TEXTURE_CUBE_MAP_POSITIVE_Y}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_Y
      enum_type_c<GL_TEXTURE_CUBE_MAP_POSITIVE_Y>>
#else
      enum_type_i>
#endif
      texture_cube_map_positive_y;

    /// @var texture_cube_map_negative_y
    /// @glconstwrap{TEXTURE_CUBE_MAP_NEGATIVE_Y}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
      enum_type_c<GL_TEXTURE_CUBE_MAP_NEGATIVE_Y>>
#else
      enum_type_i>
#endif
      texture_cube_map_negative_y;

    /// @var texture_cube_map_positive_z
    /// @glconstwrap{TEXTURE_CUBE_MAP_POSITIVE_Z}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_Z
      enum_type_c<GL_TEXTURE_CUBE_MAP_POSITIVE_Z>>
#else
      enum_type_i>
#endif
      texture_cube_map_positive_z;

    /// @var texture_cube_map_negative_z
    /// @glconstwrap{TEXTURE_CUBE_MAP_NEGATIVE_Z}
    opt_constant<
      mp_list<oglplus::texture_target>,
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
      enum_type_c<GL_TEXTURE_CUBE_MAP_NEGATIVE_Z>>
#else
      enum_type_i>
#endif
      texture_cube_map_negative_z;

    /// @var texture_external
    /// @glconstwrap{TEXTURE_EXTERNAL}
    opt_constant<mp_list<oglplus::texture_target>, enum_type_c<0x8D65>>
      texture_external;

    /// @var compare_ref_to_texture
    /// @glconstwrap{COMPARE_REF_TO_TEXTURE}
    opt_constant<
      mp_list<oglplus::texture_compare_mode>,
#ifdef GL_COMPARE_REF_TO_TEXTURE
      enum_type_c<GL_COMPARE_REF_TO_TEXTURE>>
#else
      enum_type_i>
#endif
      compare_ref_to_texture;

    /// @var nearest
    /// @glconstwrap{NEAREST}
    opt_constant<
      mp_list<
        oglplus::texture_min_filter,
        oglplus::texture_mag_filter,
        oglplus::texture_filter,
        oglplus::blit_filter>,
#ifdef GL_NEAREST
      enum_type_c<GL_NEAREST>>
#else
      enum_type_i>
#endif
      nearest;

    /// @var linear
    /// @glconstwrap{LINEAR}
    opt_constant<
      mp_list<
        oglplus::texture_min_filter,
        oglplus::texture_mag_filter,
        oglplus::texture_filter,
        oglplus::blit_filter>,
#ifdef GL_LINEAR
      enum_type_c<GL_LINEAR>>
#else
      enum_type_i>
#endif
      linear;

    /// @var nearest_mipmap_linear
    /// @glconstwrap{NEAREST_MIPMAP_LINEAR}
    opt_constant<
      mp_list<oglplus::texture_min_filter>,
#ifdef GL_NEAREST_MIPMAP_NEAREST
      enum_type_c<GL_NEAREST_MIPMAP_NEAREST>>
#else
      enum_type_i>
#endif
      nearest_mipmap_nearest;

    /// @var nearest_mipmap_linear
    /// @glconstwrap{NEAREST_MIPMAP_LINEAR}
    opt_constant<
      mp_list<oglplus::texture_min_filter>,
#ifdef GL_NEAREST_MIPMAP_LINEAR
      enum_type_c<GL_NEAREST_MIPMAP_LINEAR>>
#else
      enum_type_i>
#endif
      nearest_mipmap_linear;

    /// @var linear_mipmap_nearest
    /// @glconstwrap{LINEAR_MIPMAP_NEAREST}
    opt_constant<
      mp_list<oglplus::texture_min_filter>,
#ifdef GL_LINEAR_MIPMAP_NEAREST
      enum_type_c<GL_LINEAR_MIPMAP_NEAREST>>
#else
      enum_type_i>
#endif
      linear_mipmap_nearest;

    /// @var linear_mipmap_linear
    /// @glconstwrap{LINEAR_MIPMAP_LINEAR}
    opt_constant<
      mp_list<oglplus::texture_min_filter>,
#ifdef GL_LINEAR_MIPMAP_LINEAR
      enum_type_c<GL_LINEAR_MIPMAP_LINEAR>>
#else
      enum_type_i>
#endif
      linear_mipmap_linear;

    /// @var texture_width
    /// @glconstwrap{TEXTURE_WIDTH}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_WIDTH
      enum_type_c<GL_TEXTURE_WIDTH>>
#else
      enum_type_i>
#endif
      texture_width;

    /// @var texture_height
    /// @glconstwrap{TEXTURE_HEIGHT}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_HEIGHT
      enum_type_c<GL_TEXTURE_HEIGHT>>
#else
      enum_type_i>
#endif
      texture_height;

    /// @var texture_depth
    /// @glconstwrap{TEXTURE_DEPTH}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_DEPTH
      enum_type_c<GL_TEXTURE_DEPTH>>
#else
      enum_type_i>
#endif
      texture_depth;

    /// @var texture_red_size
    /// @glconstwrap{TEXTURE_RED_SIZE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_RED_SIZE
      enum_type_c<GL_TEXTURE_RED_SIZE>>
#else
      enum_type_i>
#endif
      texture_red_size;

    /// @var texture_green_type
    /// @glconstwrap{TEXTURE_GREEN_TYPE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_GREEN_SIZE
      enum_type_c<GL_TEXTURE_GREEN_SIZE>>
#else
      enum_type_i>
#endif
      texture_green_size;

    /// @var texture_blue_size
    /// @glconstwrap{TEXTURE_BLUE_SIZE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_BLUE_SIZE
      enum_type_c<GL_TEXTURE_BLUE_SIZE>>
#else
      enum_type_i>
#endif
      texture_blue_size;

    /// @var texture_alpha_size
    /// @glconstwrap{TEXTURE_ALPHA_SIZE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_ALPHA_SIZE
      enum_type_c<GL_TEXTURE_ALPHA_SIZE>>
#else
      enum_type_i>
#endif
      texture_alpha_size;

    /// @var texture_depth_size
    /// @glconstwrap{TEXTURE_DEPTH_SIZE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_DEPTH_SIZE
      enum_type_c<GL_TEXTURE_DEPTH_SIZE>>
#else
      enum_type_i>
#endif
      texture_depth_size;

    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_STENCIL_SIZE
      enum_type_c<GL_TEXTURE_STENCIL_SIZE>>
#else
      enum_type_i>
#endif
      texture_stencil_size;

    /// @var texture_shared_size
    /// @glconstwrap{TEXTURE_SHARED_SIZE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_SHARED_SIZE
      enum_type_c<GL_TEXTURE_SHARED_SIZE>>
#else
      enum_type_i>
#endif
      texture_shared_size;

    /// @var texture_red_type
    /// @glconstwrap{texture_red_type}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_RED_TYPE
      enum_type_c<GL_TEXTURE_RED_TYPE>,
#else
      enum_type_i,
#endif
      pixel_data_type>
      texture_red_type;

    /// @var texture_green_type
    /// @glconstwrap{TEXTURE_GREEN_TYPE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_GREEN_TYPE
      enum_type_c<GL_TEXTURE_GREEN_TYPE>,
#else
      enum_type_i,
#endif
      pixel_data_type>
      texture_green_type;

    /// @var texture_blue_type
    /// @glconstwrap{TEXTURE_BLUE_TYPE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_BLUE_TYPE
      enum_type_c<GL_TEXTURE_BLUE_TYPE>,
#else
      enum_type_i,
#endif
      pixel_data_type>
      texture_blue_type;

    /// @var texture_alpha_type
    /// @glconstwrap{TEXTURE_ALPHA_TYPE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_ALPHA_TYPE
      enum_type_c<GL_TEXTURE_ALPHA_TYPE>,
#else
      enum_type_i,
#endif
      pixel_data_type>
      texture_alpha_type;

    /// @var texture_depth_type
    /// @glconstwrap{TEXTURE_DEPTH_TYPE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_DEPTH_TYPE
      enum_type_c<GL_TEXTURE_DEPTH_TYPE>,
#else
      enum_type_i,
#endif
      pixel_data_type>
      texture_depth_type;

    /// @var depth_stencil_texture_mode
    /// @glconstwrap{DEPTH_STENCIL_TEXTURE_MODE}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_DEPTH_STENCIL_TEXTURE_MODE
      enum_type_c<GL_DEPTH_STENCIL_TEXTURE_MODE>>
#else
      enum_type_i>
#endif
      depth_stencil_texture_mode;

    /// @var image_format_compatibility_type
    /// @glconstwrap{IMAGE_FORMAT_COMPATIBILITY_TYPE}
    opt_constant<
      mp_list<texture_parameter, internal_format_parameter>,
#ifdef GL_IMAGE_FORMAT_COMPATIBILITY_TYPE
      enum_type_c<GL_IMAGE_FORMAT_COMPATIBILITY_TYPE>>
#else
      enum_type_i>
#endif
      image_format_compatibility_type;

    /// @var texture_base_level
    /// @glconstwrap{TEXTURE_BASE_LEVEL}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_BASE_LEVEL
      enum_type_c<GL_TEXTURE_BASE_LEVEL>>
#else
      enum_type_i>
#endif
      texture_base_level;

    /// @var texture_border_color
    /// @glconstwrap{TEXTURE_BORDER_COLOR}
    opt_constant<
      mp_list<texture_parameter, sampler_parameter>,
#ifdef GL_TEXTURE_BORDER_COLOR
      enum_type_c<GL_TEXTURE_BORDER_COLOR>>
#else
      enum_type_i>
#endif
      texture_border_color;

    /// @var texture_compare_mode
    /// @glconstwrap{TEXTURE_COMPARE_MODE}
    opt_constant<
      mp_list<texture_parameter, sampler_parameter>,
#ifdef GL_TEXTURE_COMPARE_MODE
      enum_type_c<GL_TEXTURE_COMPARE_MODE>,
#else
      enum_type_i,
#endif
      oglplus::texture_compare_mode>
      texture_compare_mode;

    /// @var texture_compare_func
    /// @glconstwrap{TEXTURE_COMPARE_FUNC}
    opt_constant<
      mp_list<texture_parameter, sampler_parameter>,
#ifdef GL_TEXTURE_COMPARE_FUNC
      enum_type_c<GL_TEXTURE_COMPARE_FUNC>,
#else
      enum_type_i,
#endif
      oglplus::compare_function>
      texture_compare_func;

    /// @var texture_internal_format
    /// @glconstwrap{TEXTURE_INTERNAL_FORMAT}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_INTERNAL_FORMAT
      enum_type_c<GL_TEXTURE_INTERNAL_FORMAT>,
#else
      enum_type_i,
#endif
      pixel_internal_format>
      texture_internal_format;

    /// @var texture_immutable_format
    /// @glconstwrap{TEXTURE_IMMUTABLE_FORMAT}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_IMMUTABLE_FORMAT
      enum_type_c<GL_TEXTURE_IMMUTABLE_FORMAT>,
#else
      enum_type_i,
#endif
      true_false>
      texture_immutable_format;

    /// @var texture_immutable_levels
    /// @glconstwrap{TEXTURE_IMMUTABLE_LEVELS}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_IMMUTABLE_LEVELS
      enum_type_c<GL_TEXTURE_IMMUTABLE_LEVELS>>
#else
      enum_type_i>
#endif
      texture_immutable_levels;

    /// @var texture_lod_bias
    /// @glconstwrap{TEXTURE_LOD_BIAS}
    opt_constant<
      mp_list<texture_parameter, sampler_parameter>,
#ifdef GL_TEXTURE_LOD_BIAS
      enum_type_c<GL_TEXTURE_LOD_BIAS>>
#else
      enum_type_i>
#endif
      texture_lod_bias;

    /// @var texture_mag_filter
    /// @glconstwrap{TEXTURE_MAG_FILTER}
    opt_constant<
      mp_list<texture_parameter, sampler_parameter>,
#ifdef GL_TEXTURE_MAG_FILTER
      enum_type_c<GL_TEXTURE_MAG_FILTER>,
#else
      enum_type_i,
#endif
      oglplus::texture_mag_filter>
      texture_mag_filter;

    /// @var texture_max_level
    /// @glconstwrap{TEXTURE_MAX_LEVEL}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_MAX_LEVEL
      enum_type_c<GL_TEXTURE_MAX_LEVEL>>
#else
      enum_type_i>
#endif
      texture_max_level;

    /// @var texture_max_lod
    /// @glconstwrap{TEXTURE_MAX_LOD}
    opt_constant<
      mp_list<texture_parameter, sampler_parameter>,
#ifdef GL_TEXTURE_MAX_LOD
      enum_type_c<GL_TEXTURE_MAX_LOD>>
#else
      enum_type_i>
#endif
      texture_max_lod;

    /// @var texture_min_filter
    /// @glconstwrap{TEXTURE_MIN_FILTER}
    opt_constant<
      mp_list<texture_parameter, sampler_parameter>,
#ifdef GL_TEXTURE_MIN_FILTER
      enum_type_c<GL_TEXTURE_MIN_FILTER>,
#else
      enum_type_i,
#endif
      oglplus::texture_min_filter>
      texture_min_filter;

    /// @var texture_min_lod
    /// @glconstwrap{TEXTURE_MIN_LOD}
    opt_constant<
      mp_list<texture_parameter, sampler_parameter>,
#ifdef GL_TEXTURE_MIN_LOD
      enum_type_c<GL_TEXTURE_MIN_LOD>>
#else
      enum_type_i>
#endif
      texture_min_lod;

    /// @var texture_swizzle_r
    /// @glconstwrap{TEXTURE_SWIZZLE_R}
    opt_constant<
      mp_list<texture_parameter, texture_swizzle_mode>,
#ifdef GL_TEXTURE_SWIZZLE_R
      enum_type_c<GL_TEXTURE_SWIZZLE_R>,
#else
      enum_type_i,
#endif
      texture_swizzle_mode>
      texture_swizzle_r;

    /// @var texture_swizzle_g
    /// @glconstwrap{TEXTURE_SWIZZLE_G}
    opt_constant<
      mp_list<texture_parameter, texture_swizzle_mode>,
#ifdef GL_TEXTURE_SWIZZLE_G
      enum_type_c<GL_TEXTURE_SWIZZLE_G>,
#else
      enum_type_i,
#endif
      texture_swizzle_mode>
      texture_swizzle_g;

    /// @var texture_swizzle_b
    /// @glconstwrap{TEXTURE_SWIZZLE_B}
    opt_constant<
      mp_list<texture_parameter, texture_swizzle_mode>,
#ifdef GL_TEXTURE_SWIZZLE_B
      enum_type_c<GL_TEXTURE_SWIZZLE_B>,
#else
      enum_type_i,
#endif
      texture_swizzle_mode>
      texture_swizzle_b;

    /// @var texture_swizzle_a
    /// @glconstwrap{TEXTURE_SWIZZLE_A}
    opt_constant<
      mp_list<texture_parameter, texture_swizzle_mode>,
#ifdef GL_TEXTURE_SWIZZLE_A
      enum_type_c<GL_TEXTURE_SWIZZLE_A>,
#else
      enum_type_i,
#endif
      texture_swizzle_mode>
      texture_swizzle_a;

    /// @var texture_swizzle_rgba
    /// @glconstwrap{TEXTURE_SWIZZLE_RGBA}
    opt_constant<
      mp_list<texture_parameter, texture_swizzle_mode>,
#ifdef GL_TEXTURE_SWIZZLE_RGBA
      enum_type_c<GL_TEXTURE_SWIZZLE_RGBA>>
#else
      enum_type_i>
#endif
      texture_swizzle_rgba;

    /// @var texture_target
    /// @glconstwrap{TEXTURE_TARGET}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_TARGET
      enum_type_c<GL_TEXTURE_TARGET>,
#else
      enum_type_i,
#endif
      oglplus::texture_target>
      texture_target;

    /// @var texture_view_min_layer
    /// @glconstwrap{TEXTURE_VIEW_MIN_LAYER}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_VIEW_MIN_LAYER
      enum_type_c<GL_TEXTURE_VIEW_MIN_LAYER>>
#else
      enum_type_i>
#endif
      texture_view_min_layer;

    /// @var texture_view_min_level
    /// @glconstwrap{TEXTURE_VIEW_MIN_LEVEL}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_VIEW_MIN_LEVEL
      enum_type_c<GL_TEXTURE_VIEW_MIN_LEVEL>>
#else
      enum_type_i>
#endif
      texture_view_min_level;

    /// @var texture_view_num_layers
    /// @glconstwrap{TEXTURE_VIEW_NUM_LAYERS}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_VIEW_NUM_LAYERS
      enum_type_c<GL_TEXTURE_VIEW_NUM_LAYERS>>
#else
      enum_type_i>
#endif
      texture_view_num_layers;

    /// @var texture_view_num_levels
    /// @glconstwrap{TEXTURE_VIEW_NUM_LEVELS}
    opt_constant<
      mp_list<texture_parameter>,
#ifdef GL_TEXTURE_VIEW_NUM_LEVELS
      enum_type_c<GL_TEXTURE_VIEW_NUM_LEVELS>>
#else
      enum_type_i>
#endif
      texture_view_num_levels;

    /// @var texture_fixed_sample_locations
    /// @glconstwrap{TEXTURE_FIXED_SAMPLE_LOCATIONS}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_FIXED_SAMPLE_LOCATIONS
      enum_type_c<GL_TEXTURE_FIXED_SAMPLE_LOCATIONS>,
#else
      enum_type_i,
#endif
      true_false>
      texture_fixed_sample_locations;

    /// @var texture_wrap_s
    /// @glconstwrap{TEXTURE_WRAP_S}
    opt_constant<
      mp_list<texture_parameter, texture_wrap_coord, sampler_parameter>,
#ifdef GL_TEXTURE_WRAP_S
      enum_type_c<GL_TEXTURE_WRAP_S>,
#else
      enum_type_i,
#endif
      oglplus::texture_wrap_mode>
      texture_wrap_s;

    /// @var texture_wrap_t
    /// @glconstwrap{TEXTURE_WRAP_T}
    opt_constant<
      mp_list<texture_parameter, texture_wrap_coord, sampler_parameter>,
#ifdef GL_TEXTURE_WRAP_T
      enum_type_c<GL_TEXTURE_WRAP_T>,
#else
      enum_type_i,
#endif
      oglplus::texture_wrap_mode>
      texture_wrap_t;

    /// @var texture_wrap_r
    /// @glconstwrap{TEXTURE_WRAP_R}
    opt_constant<
      mp_list<texture_parameter, texture_wrap_coord, sampler_parameter>,
#ifdef GL_TEXTURE_WRAP_R
      enum_type_c<GL_TEXTURE_WRAP_R>,
#else
      enum_type_i,
#endif
      oglplus::texture_wrap_mode>
      texture_wrap_r;

    /// @var clamp_to_edge
    /// @glconstwrap{CLAMP_TO_EDGE}
    opt_constant<
      mp_list<texture_wrap_mode>,
#ifdef GL_CLAMP_TO_EDGE
      enum_type_c<GL_CLAMP_TO_EDGE>>
#else
      enum_type_i>
#endif
      clamp_to_edge;

    /// @var repeat
    /// @glconstwrap{REPEAT}
    opt_constant<
      mp_list<texture_wrap_mode>,
#ifdef GL_REPEAT
      enum_type_c<GL_REPEAT>>
#else
      enum_type_i>
#endif
      repeat;

    /// @var clamp_to_border
    /// @glconstwrap{CLAMP_TO_BORDER}
    opt_constant<
      mp_list<texture_wrap_mode>,
#ifdef GL_CLAMP_TO_BORDER
      enum_type_c<GL_CLAMP_TO_BORDER>>
#else
      enum_type_i>
#endif
      clamp_to_border;

    /// @var mirrored_repeat
    /// @glconstwrap{MIRRORED_REPEAT}
    opt_constant<
      mp_list<texture_wrap_mode>,
#ifdef GL_MIRRORED_REPEAT
      enum_type_c<GL_MIRRORED_REPEAT>>
#else
      enum_type_i>
#endif
      mirrored_repeat;

    /// @var mirror_clamp_to_edge
    /// @glconstwrap{MIRROR_CLAMP_TO_EDGE}
    opt_constant<
      mp_list<texture_wrap_mode>,
#ifdef GL_MIRROR_CLAMP_TO_EDGE
      enum_type_c<GL_MIRROR_CLAMP_TO_EDGE>>
#else
      enum_type_i>
#endif
      mirror_clamp_to_edge;

    /// @var red
    /// @glconstwrap{RED}
    opt_constant<
      mp_list<texture_swizzle_mode, pixel_internal_format, pixel_format>,
#ifdef GL_RED
      enum_type_c<GL_RED>>
#else
      enum_type_i>
#endif
      red;

    /// @var green
    /// @glconstwrap{GREEN}
    opt_constant<
      mp_list<texture_swizzle_mode, pixel_format>,
#ifdef GL_GREEN
      enum_type_c<GL_GREEN>>
#else
      enum_type_i>
#endif
      green;

    /// @var blue
    /// @glconstwrap{BLUE}
    opt_constant<
      mp_list<texture_swizzle_mode, pixel_format>,
#ifdef GL_BLUE
      enum_type_c<GL_BLUE>>
#else
      enum_type_i>
#endif
      blue;

    /// @var alpha
    /// @glconstwrap{ALPHA}
    opt_constant<
      mp_list<texture_swizzle_mode, path_color_format_nv>,
#ifdef GL_ALPHA
      enum_type_c<GL_ALPHA>>
#else
      enum_type_i>
#endif
      alpha;

    /// @var zero
    /// @glconstwrap{ZERO}
    opt_constant<
      mp_list<texture_swizzle_mode, blend_function, stencil_operation>,
#ifdef GL_ZERO
      enum_type_c<GL_ZERO>>
#else
      enum_type_i>
#endif
      zero;

    /// @var one
    /// @glconstwrap{ONE}
    opt_constant<
      mp_list<texture_swizzle_mode, blend_function>,
#ifdef GL_ONE
      enum_type_c<GL_ONE>>
#else
      enum_type_i>
#endif
      one;

    /// @var primitives_generated
    /// @glconstwrap{PRIMITIVES_GENERATED}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_PRIMITIVES_GENERATED
      enum_type_c<GL_PRIMITIVES_GENERATED>>
#else
      enum_type_i>
#endif
      primitives_generated;

    /// @var transform_feedback_primitives_written
    /// @glconstwrap{TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
      enum_type_c<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN>>
#else
      enum_type_i>
#endif
      transform_feedback_primitives_written;

    /// @var transform_feedback_overflow
    /// @glconstwrap{TRANSFORM_FEEDBACK_OVERFLOW}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_TRANSFORM_FEEDBACK_OVERFLOW
      enum_type_c<GL_TRANSFORM_FEEDBACK_OVERFLOW>>
#else
      enum_type_i>
#endif
      transform_feedback_overflow;

    /// @var transform_feedback_stream_overflow
    /// @glconstwrap{TRANSFORM_FEEDBACK_STREAM_OVERFLOW}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW
      enum_type_c<GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW>>
#else
      enum_type_i>
#endif
      transform_feedback_stream_overflow;

    /// @var samples_passed
    /// @glconstwrap{SAMPLES_PASSED}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_SAMPLES_PASSED
      enum_type_c<GL_SAMPLES_PASSED>>
#else
      enum_type_i>
#endif
      samples_passed;

    /// @var any_samples_passed
    /// @glconstwrap{ANY_SAMPLES_PASSED}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_ANY_SAMPLES_PASSED
      enum_type_c<GL_ANY_SAMPLES_PASSED>>
#else
      enum_type_i>
#endif
      any_samples_passed;

    /// @var any_samples_passed_conservative
    /// @glconstwrap{ANY_SAMPLES_PASSED_CONSERVATIVE}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_ANY_SAMPLES_PASSED_CONSERVATIVE
      enum_type_c<GL_ANY_SAMPLES_PASSED_CONSERVATIVE>>
#else
      enum_type_i>
#endif
      any_samples_passed_conservative;

    /// @var time_elapsed
    /// @glconstwrap{TIME_ELAPSED}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_TIME_ELAPSED
      enum_type_c<GL_TIME_ELAPSED>>
#else
      enum_type_i>
#endif
      time_elapsed;

    /// @var timestamp
    /// @glconstwrap{TIMESTAMP}
    opt_constant<
      mp_list<query_target, counter_query_target>,
#ifdef GL_TIMESTAMP
      enum_type_c<GL_TIMESTAMP>>
#else
      enum_type_i>
#endif
      timestamp;

    /// @var vertices_submitted
    /// @glconstwrap{VERTICES_SUBMITTED}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_VERTICES_SUBMITTED
      enum_type_c<GL_VERTICES_SUBMITTED>>
#else
      enum_type_i>
#endif
      vertices_submitted;

    /// @var primitives_submitted
    /// @glconstwrap{PRIMITIVES_SUBMITTED}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_PRIMITIVES_SUBMITTED
      enum_type_c<GL_PRIMITIVES_SUBMITTED>>
#else
      enum_type_i>
#endif
      primitives_submitted;

    /// @var vertex_shader_invocations
    /// @glconstwrap{VERTEX_SHADER_INVOCATIONS}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_VERTEX_SHADER_INVOCATIONS
      enum_type_c<GL_VERTEX_SHADER_INVOCATIONS>>
#else
      enum_type_i>
#endif
      vertex_shader_invocations;

    /// @var tess_control_shader_patches
    /// @glconstwrap{TESS_CONTROL_SHADER_PATCHES}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_TESS_CONTROL_SHADER_PATCHES
      enum_type_c<GL_TESS_CONTROL_SHADER_PATCHES>>
#else
      enum_type_i>
#endif
      tess_control_shader_patches;

    /// @var tess_evaluation_shader_invocations
    /// @glconstwrap{TESS_EVALUATION_SHADER_INVOCATIONS}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_TESS_EVALUATION_SHADER_INVOCATIONS
      enum_type_c<GL_TESS_EVALUATION_SHADER_INVOCATIONS>>
#else
      enum_type_i>
#endif
      tess_evaluation_shader_invocations;

    /// @var geometry_shader_invocations
    /// @glconstwrap{GEOMETRY_SHADER_INVOCATIONS}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_GEOMETRY_SHADER_INVOCATIONS
      enum_type_c<GL_GEOMETRY_SHADER_INVOCATIONS>>
#else
      enum_type_i>
#endif
      geometry_shader_invocations;

    /// @var geometry_shader_primitives_emitted
    /// @glconstwrap{GEOMETRY_SHADER_PRIMITIVES_EMITTED}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED
      enum_type_c<GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED>>
#else
      enum_type_i>
#endif
      geometry_shader_primitives_emitted;

    /// @var clipping_input_primitives
    /// @glconstwrap{CLIPPING_INPUT_PRIMITIVES}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_CLIPPING_INPUT_PRIMITIVES
      enum_type_c<GL_CLIPPING_INPUT_PRIMITIVES>>
#else
      enum_type_i>
#endif
      clipping_input_primitives;

    /// @var clipping_output_primitives
    /// @glconstwrap{CLIPPING_OUTPUT_PRIMITIVES}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_CLIPPING_OUTPUT_PRIMITIVES
      enum_type_c<GL_CLIPPING_OUTPUT_PRIMITIVES>>
#else
      enum_type_i>
#endif
      clipping_output_primitives;

    /// @var fragment_shader_invocations
    /// @glconstwrap{FRAGMENT_SHADER_INVOCATIONS}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_FRAGMENT_SHADER_INVOCATIONS
      enum_type_c<GL_FRAGMENT_SHADER_INVOCATIONS>>
#else
      enum_type_i>
#endif
      fragment_shader_invocations;

    /// @var compute_shader_invocations
    /// @glconstwrap{COMPUTE_SHADER_INVOCATIONS}
    opt_constant<
      mp_list<query_target>,
#ifdef GL_COMPUTE_SHADER_INVOCATIONS
      enum_type_c<GL_COMPUTE_SHADER_INVOCATIONS>>
#else
      enum_type_i>
#endif
      compute_shader_invocations;

    /// @var query_result
    /// @glconstwrap{QUERY_RESULT}
    opt_constant<
      mp_list<query_parameter>,
#ifdef GL_QUERY_RESULT
      enum_type_c<GL_QUERY_RESULT>>
#else
      enum_type_i>
#endif
      query_result;

    /// @var query_result_available
    /// @glconstwrap{QUERY_RESULT_AVAILABLE}
    opt_constant<
      mp_list<query_parameter>,
#ifdef GL_QUERY_RESULT_AVAILABLE
      enum_type_c<GL_QUERY_RESULT_AVAILABLE>,
#else
      enum_type_i,
#endif
      true_false>
      query_result_available;

    /// @var interleaved_attribs
    /// @glconstwrap{INTERLEAVED_ATTRIBS}
    opt_constant<
      mp_list<transform_feedback_mode>,
#ifdef GL_INTERLEAVED_ATTRIBS
      enum_type_c<GL_INTERLEAVED_ATTRIBS>>
#else
      enum_type_i>
#endif
      interleaved_attribs;

    /// @var separate_attribs
    /// @glconstwrap{SEPARATE_ATTRIBS}
    opt_constant<
      mp_list<transform_feedback_mode>,
#ifdef GL_SEPARATE_ATTRIBS
      enum_type_c<GL_SEPARATE_ATTRIBS>>
#else
      enum_type_i>
#endif
      separate_attribs;

    /// @var transform_feedback_buffer_start
    /// @glconstwrap{TRANSFORM_FEEDBACK_BUFFER_START}
    opt_constant<
      mp_list<transform_feedback_parameter>,
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_START
      enum_type_c<GL_TRANSFORM_FEEDBACK_BUFFER_START>>
#else
      enum_type_i>
#endif
      transform_feedback_buffer_start;

    /// @var transform_feedback_buffer_size
    /// @glconstwrap{TRANSFORM_FEEDBACK_BUFFER_SIZE}
    opt_constant<
      mp_list<transform_feedback_parameter>,
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_SIZE
      enum_type_c<GL_TRANSFORM_FEEDBACK_BUFFER_SIZE>>
#else
      enum_type_i>
#endif
      transform_feedback_buffer_size;

    /// @var transform_feedback_parameter
    /// @glconstwrap{TRANSFORM_FEEDBACK_PARAMETER}
    opt_constant<
      mp_list<transform_feedback_parameter>,
#ifdef GL_TRANSFORM_FEEDBACK_PAUSED
      enum_type_c<GL_TRANSFORM_FEEDBACK_PAUSED>,
#else
      enum_type_i,
#endif
      true_false>
      transform_feedback_paused;

    /// @var transform_feedback_active
    /// @glconstwrap{TRANSFORM_FEEDBACK_ACTIVE}
    opt_constant<
      mp_list<transform_feedback_parameter>,
#ifdef GL_TRANSFORM_FEEDBACK_ACTIVE
      enum_type_c<GL_TRANSFORM_FEEDBACK_ACTIVE>,
#else
      enum_type_i,
#endif
      true_false>
      transform_feedback_active;

    /// @var current_vertex_attrib
    /// @glconstwrap{CURRENT_VERTEX_ATTRIB}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_CURRENT_VERTEX_ATTRIB
      enum_type_c<GL_CURRENT_VERTEX_ATTRIB>>
#else
      enum_type_i>
#endif
      current_vertex_attrib;

    /// @var vertex_attrib_array_buffer_binding
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_BUFFER_BINDING}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING>>
#else
      enum_type_i>
#endif
      vertex_attrib_array_buffer_binding;

    /// @var vertex_attrib_array_divisor
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_DIVISOR}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_DIVISOR
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_DIVISOR>>
#else
      enum_type_i>
#endif
      vertex_attrib_array_divisor;

    /// @var vertex_attrib_array_enabled
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_ENABLED}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_ENABLED
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_ENABLED>,
#else
      enum_type_i,
#endif
      true_false>
      vertex_attrib_array_enabled;

    /// @var vertex_attrib_array_integer
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_INTEGER}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_INTEGER
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_INTEGER>,
#else
      enum_type_i,
#endif
      true_false>
      vertex_attrib_array_integer;

    /// @var vertex_attrib_array_integer_ext
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_INTEGER_EXT}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_INTEGER_EXT
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_INTEGER_EXT>>
#else
      enum_type_i>
#endif
      vertex_attrib_array_integer_ext;

    /// @var vertex_attrib_array_long
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_LONG}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_LONG
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_LONG>,
#else
      enum_type_i,
#endif
      true_false>
      vertex_attrib_array_long;

    /// @var vertex_attrib_array_normalized
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_NORMALIZED}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_NORMALIZED
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_NORMALIZED>,
#else
      enum_type_i,
#endif
      true_false>
      vertex_attrib_array_normalized;

    /// @var vertex_attrib_array_pointer
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_POINTER}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_POINTER
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_POINTER>>
#else
      enum_type_i>
#endif
      vertex_attrib_array_pointer;

    /// @var vertex_attrib_array_size
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_SIZE}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_SIZE
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_SIZE>>
#else
      enum_type_i>
#endif
      vertex_attrib_array_size;

    /// @var vertex_attrib_array_stride
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_STRIDE}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_STRIDE
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_STRIDE>>
#else
      enum_type_i>
#endif
      vertex_attrib_array_stride;

    /// @var vertex_attrib_array_type
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_TYPE}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_TYPE
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_TYPE>>
#else
      enum_type_i>
#endif
      vertex_attrib_array_type;

    /// @var vertex_attrib_binding
    /// @glconstwrap{VERTEX_ATTRIB_BINDING}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_BINDING
      enum_type_c<GL_VERTEX_ATTRIB_BINDING>>
#else
      enum_type_i>
#endif
      vertex_attrib_binding;

    /// @var vertex_attrib_relative_offset
    /// @glconstwrap{VERTEX_ATTRIB_RELATIVE_OFFSET}
    opt_constant<
      mp_list<vertex_attrib_parameter>,
#ifdef GL_VERTEX_ATTRIB_RELATIVE_OFFSET
      enum_type_c<GL_VERTEX_ATTRIB_RELATIVE_OFFSET>>
#else
      enum_type_i>
#endif
      vertex_attrib_relative_offset;

    /// @var uniform
    /// @glconstwrap{UNIFORM}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_UNIFORM
      enum_type_c<GL_UNIFORM>>
#else
      enum_type_i>
#endif
      uniform;

    /// @var uniform_block
    /// @glconstwrap{UNIFORM_BLOCK}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_UNIFORM_BLOCK
      enum_type_c<GL_UNIFORM_BLOCK>>
#else
      enum_type_i>
#endif
      uniform_block;

    /// @var program_input
    /// @glconstwrap{PROGRAM_INPUT}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_PROGRAM_INPUT
      enum_type_c<GL_PROGRAM_INPUT>>
#else
      enum_type_i>
#endif
      program_input;

    /// @var program_output
    /// @glconstwrap{PROGRAM_OUTPUT}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_PROGRAM_OUTPUT
      enum_type_c<GL_PROGRAM_OUTPUT>>
#else
      enum_type_i>
#endif
      program_output;

    /// @var vertex_subroutine
    /// @glconstwrap{VERTEX_SUBROUTINE}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_VERTEX_SUBROUTINE
      enum_type_c<GL_VERTEX_SUBROUTINE>>
#else
      enum_type_i>
#endif
      vertex_subroutine;

    /// @var tess_control_subroutine
    /// @glconstwrap{TESS_CONTROL_SUBROUTINE}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_TESS_CONTROL_SUBROUTINE
      enum_type_c<GL_TESS_CONTROL_SUBROUTINE>>
#else
      enum_type_i>
#endif
      tess_control_subroutine;

    /// @var tess_evaluation_subroutine
    /// @glconstwrap{TESS_EVALUATION_SUBROUTINE}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_TESS_EVALUATION_SUBROUTINE
      enum_type_c<GL_TESS_EVALUATION_SUBROUTINE>>
#else
      enum_type_i>
#endif
      tess_evaluation_subroutine;

    /// @var geometry_subroutine
    /// @glconstwrap{GEOMETRY_SUBROUTINE}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_GEOMETRY_SUBROUTINE
      enum_type_c<GL_GEOMETRY_SUBROUTINE>>
#else
      enum_type_i>
#endif
      geometry_subroutine;

    /// @var fragment_subroutine
    /// @glconstwrap{FRAGMENT_SUBROUTINE}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_FRAGMENT_SUBROUTINE
      enum_type_c<GL_FRAGMENT_SUBROUTINE>>
#else
      enum_type_i>
#endif
      fragment_subroutine;

    /// @var compute_subroutine
    /// @glconstwrap{COMPUTE_SUBROUTINE}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_COMPUTE_SUBROUTINE
      enum_type_c<GL_COMPUTE_SUBROUTINE>>
#else
      enum_type_i>
#endif
      compute_subroutine;

    /// @var vertex_subroutine_uniform
    /// @glconstwrap{VERTEX_SUBROUTINE_UNIFORM}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_VERTEX_SUBROUTINE_UNIFORM
      enum_type_c<GL_VERTEX_SUBROUTINE_UNIFORM>>
#else
      enum_type_i>
#endif
      vertex_subroutine_uniform;

    /// @var tess_control_subroutine_uniform
    /// @glconstwrap{TESS_CONTROL_SUBROUTINE_UNIFORM}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_TESS_CONTROL_SUBROUTINE_UNIFORM
      enum_type_c<GL_TESS_CONTROL_SUBROUTINE_UNIFORM>>
#else
      enum_type_i>
#endif
      tess_control_subroutine_uniform;

    /// @var tess_evaluation_subroutine_uniform
    /// @glconstwrap{TESS_EVALUATION_SUBROUTINE_UNIFORM}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_TESS_EVALUATION_SUBROUTINE_UNIFORM
      enum_type_c<GL_TESS_EVALUATION_SUBROUTINE_UNIFORM>>
#else
      enum_type_i>
#endif
      tess_evaluation_subroutine_uniform;

    /// @var geometry_subroutine_uniform
    /// @glconstwrap{GEOMETRY_SUBROUTINE_UNIFORM}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_GEOMETRY_SUBROUTINE_UNIFORM
      enum_type_c<GL_GEOMETRY_SUBROUTINE_UNIFORM>>
#else
      enum_type_i>
#endif
      geometry_subroutine_uniform;

    /// @var fragment_subroutine_uniform
    /// @glconstwrap{FRAGMENT_SUBROUTINE_UNIFORM}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_FRAGMENT_SUBROUTINE_UNIFORM
      enum_type_c<GL_FRAGMENT_SUBROUTINE_UNIFORM>>
#else
      enum_type_i>
#endif
      fragment_subroutine_uniform;

    /// @var compute_subroutine_uniform
    /// @glconstwrap{COMPUTE_SUBROUTINE_UNIFORM}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_COMPUTE_SUBROUTINE_UNIFORM
      enum_type_c<GL_COMPUTE_SUBROUTINE_UNIFORM>>
#else
      enum_type_i>
#endif
      compute_subroutine_uniform;

    /// @var transform_feedback_varying
    /// @glconstwrap{TRANSFORM_FEEDBACK_VARYING}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_TRANSFORM_FEEDBACK_VARYING
      enum_type_c<GL_TRANSFORM_FEEDBACK_VARYING>>
#else
      enum_type_i>
#endif
      transform_feedback_varying;

    /// @var buffer_variable
    /// @glconstwrap{BUFFER_VARIABLE}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_BUFFER_VARIABLE
      enum_type_c<GL_BUFFER_VARIABLE>>
#else
      enum_type_i>
#endif
      buffer_variable;

    /// @var buffer_storage_block
    /// @glconstwrap{BUFFER_STORAGE_BLOCK}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_BUFFER_STORAGE_BLOCK
      enum_type_c<GL_BUFFER_STORAGE_BLOCK>>
#else
      enum_type_i>
#endif
      buffer_storage_block;

    /// @var fragment_input_nv
    /// @glconstwrap{FRAGMENT_INPUT_NV}
    opt_constant<
      mp_list<program_interface>,
#ifdef GL_FRAGMENT_INPUT_NV
      enum_type_c<GL_FRAGMENT_INPUT_NV>>
#else
      enum_type_i>
#endif
      fragment_input_nv;

    /// @var active_variables
    /// @glconstwrap{ACTIVE_VARIABLES}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_ACTIVE_VARIABLES
      enum_type_c<GL_ACTIVE_VARIABLES>>
#else
      enum_type_i>
#endif
      active_variables;

    /// @var num_active_variables
    /// @glconstwrap{NUM_ACTIVE_VARIABLES}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_NUM_ACTIVE_VARIABLES
      enum_type_c<GL_NUM_ACTIVE_VARIABLES>>
#else
      enum_type_i>
#endif
      num_active_variables;

    /// @var array_size
    /// @glconstwrap{ARRAY_SIZE}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_ARRAY_SIZE
      enum_type_c<GL_ARRAY_SIZE>>
#else
      enum_type_i>
#endif
      array_size;

    /// @var array_stride
    /// @glconstwrap{ARRAY_STRIDE}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_ARRAY_STRIDE
      enum_type_c<GL_ARRAY_STRIDE>>
#else
      enum_type_i>
#endif
      array_stride;

    /// @var block_index
    /// @glconstwrap{BLOCK_INDEX}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_BLOCK_INDEX
      enum_type_c<GL_BLOCK_INDEX>>
#else
      enum_type_i>
#endif
      block_index;

    /// @var is_row_major
    /// @glconstwrap{IS_ROW_MAJOR}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_IS_ROW_MAJOR
      enum_type_c<GL_IS_ROW_MAJOR>>
#else
      enum_type_i>
#endif
      is_row_major;

    /// @var matrix_stride
    /// @glconstwrap{MATRIX_STRIDE}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_MATRIX_STRIDE
      enum_type_c<GL_MATRIX_STRIDE>>
#else
      enum_type_i>
#endif
      matrix_stride;

    /// @var atomic_counter_buffer_index
    /// @glconstwrap{ATOMIC_COUNTER_BUFFER_INDEX}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_ATOMIC_COUNTER_BUFFER_INDEX
      enum_type_c<GL_ATOMIC_COUNTER_BUFFER_INDEX>>
#else
      enum_type_i>
#endif
      atomic_counter_buffer_index;

    /// @var buffer_data_size
    /// @glconstwrap{BUFFER_DATA_SIZE}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_BUFFER_DATA_SIZE
      enum_type_c<GL_BUFFER_DATA_SIZE>>
#else
      enum_type_i>
#endif
      buffer_data_size;

    /// @var num_compatible_subroutines
    /// @glconstwrap{NUM_COMPATIBLE_SUBROUTINES}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_NUM_COMPATIBLE_SUBROUTINES
      enum_type_c<GL_NUM_COMPATIBLE_SUBROUTINES>>
#else
      enum_type_i>
#endif
      num_compatible_subroutines;

    /// @var compatible_subroutines
    /// @glconstwrap{COMPATIBLE_SUBROUTINES}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_COMPATIBLE_SUBROUTINES
      enum_type_c<GL_COMPATIBLE_SUBROUTINES>>
#else
      enum_type_i>
#endif
      compatible_subroutines;

    /// @var is_per_patch
    /// @glconstwrap{IS_PER_PATCH}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_IS_PER_PATCH
      enum_type_c<GL_IS_PER_PATCH>>
#else
      enum_type_i>
#endif
      is_per_patch;

    /// @var location
    /// @glconstwrap{LOCATION}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_LOCATION
      enum_type_c<GL_LOCATION>>
#else
      enum_type_i>
#endif
      location;

    /// @var location_component
    /// @glconstwrap{LOCATION_COMPONENT}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_LOCATION_COMPONENT
      enum_type_c<GL_LOCATION_COMPONENT>>
#else
      enum_type_i>
#endif
      location_component;

    /// @var location_index
    /// @glconstwrap{LOCATION_INDEX}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_LOCATION_INDEX
      enum_type_c<GL_LOCATION_INDEX>>
#else
      enum_type_i>
#endif
      location_index;

    /// @var name_lenght
    /// @glconstwrap{NAME_LENGHT}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_NAME_LENGTH
      enum_type_c<GL_NAME_LENGTH>>
#else
      enum_type_i>
#endif
      name_length;

    /// @var offset
    /// @glconstwrap{OFFSET}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_OFFSET
      enum_type_c<GL_OFFSET>>
#else
      enum_type_i>
#endif
      offset;

    /// @var referenced_by_vertex_shader
    /// @glconstwrap{REFERENCED_BY_VERTEX_SHADER}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_REFERENCED_BY_VERTEX_SHADER
      enum_type_c<GL_REFERENCED_BY_VERTEX_SHADER>>
#else
      enum_type_i>
#endif
      referenced_by_vertex_shader;

    /// @var referenced_by_tess_control_shader
    /// @glconstwrap{REFERENCED_BY_TESS_CONTROL_SHADER}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_REFERENCED_BY_TESS_CONTROL_SHADER
      enum_type_c<GL_REFERENCED_BY_TESS_CONTROL_SHADER>>
#else
      enum_type_i>
#endif
      referenced_by_tess_control_shader;

    /// @var referenced_by_tess_evaluation_shader
    /// @glconstwrap{REFERENCED_BY_TESS_EVALUATION_SHADER}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_REFERENCED_BY_TESS_EVALUATION_SHADER
      enum_type_c<GL_REFERENCED_BY_TESS_EVALUATION_SHADER>>
#else
      enum_type_i>
#endif
      referenced_by_tess_evaluation_shader;

    /// @var referenced_by_geometry_shader
    /// @glconstwrap{REFERENCED_BY_GEOMETRY_SHADER}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_REFERENCED_BY_GEOMETRY_SHADER
      enum_type_c<GL_REFERENCED_BY_GEOMETRY_SHADER>>
#else
      enum_type_i>
#endif
      referenced_by_geometry_shader;

    /// @var referenced_by_fragment_shader
    /// @glconstwrap{REFERENCED_BY_FRAGMENT_SHADER}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_REFERENCED_BY_FRAGMENT_SHADER
      enum_type_c<GL_REFERENCED_BY_FRAGMENT_SHADER>>
#else
      enum_type_i>
#endif
      referenced_by_fragment_shader;

    /// @var referenced_by_compute_shader
    /// @glconstwrap{REFERENCED_BY_COMPUTE_SHADER}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_REFERENCED_BY_COMPUTE_SHADER
      enum_type_c<GL_REFERENCED_BY_COMPUTE_SHADER>>
#else
      enum_type_i>
#endif
      referenced_by_compute_shader;

    /// @var transform_feedback_buffer_index
    /// @glconstwrap{TRANSFORM_FEEDBACK_BUFFER_INDEX}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_INDEX
      enum_type_c<GL_TRANSFORM_FEEDBACK_BUFFER_INDEX>>
#else
      enum_type_i>
#endif
      transform_feedback_buffer_index;

    /// @var transform_feedback_buffer_start
    /// @glconstwrap{TRANSFORM_FEEDBACK_BUFFER_START}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE
      enum_type_c<GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE>>
#else
      enum_type_i>
#endif
      transform_feedback_buffer_stride;

    /// @var top_level_array_size
    /// @glconstwrap{TOP_LEVEL_ARRAY_SIZE}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_TOP_LEVEL_ARRAY_SIZE
      enum_type_c<GL_TOP_LEVEL_ARRAY_SIZE>>
#else
      enum_type_i>
#endif
      top_level_array_size;

    /// @var top_level_array_stride
    /// @glconstwrap{TOP_LEVEL_ARRAY_STRIDE}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_TOP_LEVEL_ARRAY_STRIDE
      enum_type_c<GL_TOP_LEVEL_ARRAY_STRIDE>>
#else
      enum_type_i>
#endif
      top_level_array_stride;

    /// @var type
    /// @glconstwrap{TYPE}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_TYPE
      enum_type_c<GL_TYPE>>
#else
      enum_type_i>
#endif
      type;

    /// @var path_gen_mode_nv
    /// @glconstwrap{PATH_GEN_MODE_NV}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_PATH_GEN_MODE_NV
      enum_type_c<GL_PATH_GEN_MODE_NV>>
#else
      enum_type_i>
#endif
      path_gen_mode_nv;

    /// @var path_gen_components_nv
    /// @glconstwrap{PATH_GEN_COMPONENTS_NV}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_PATH_GEN_COMPONENTS_NV
      enum_type_c<GL_PATH_GEN_COMPONENTS_NV>>
#else
      enum_type_i>
#endif
      path_gen_components_nv;

    /// @var path_gen_coeff_nv
    /// @glconstwrap{PATH_GEN_COEFF_NV}
    opt_constant<
      mp_list<program_property>,
#ifdef GL_PATH_GEN_COEFF_NV
      enum_type_c<GL_PATH_GEN_COEFF_NV>>
#else
      enum_type_i>
#endif
      path_gen_coeff_nv;

    /// @var blend
    /// @glconstwrap{BLEND}
    opt_constant<
      mp_list<capability>,
#ifdef GL_BLEND
      enum_type_c<GL_BLEND>>
#else
      enum_type_i>
#endif
      blend;

    /// @var program_point_size
    /// @glconstwrap{PROGRAM_POINT_SIZE}
    opt_constant<
      mp_list<capability>,
#ifdef GL_PROGRAM_POINT_SIZE
      enum_type_c<GL_PROGRAM_POINT_SIZE>>
#else
      enum_type_i>
#endif
      program_point_size;

    /// @var primitive_restart
    /// @glconstwrap{PRIMITIVE_RESTART}
    opt_constant<
      mp_list<capability>,
#ifdef GL_PRIMITIVE_RESTART
      enum_type_c<GL_PRIMITIVE_RESTART>>
#else
      enum_type_i>
#endif
      primitive_restart;

    /// @var clip_distance0
    /// @glconstwrap{CLIP_DISTANCE0}
    opt_constant<
      mp_list<capability>,
#ifdef GL_CLIP_DISTANCE0
      enum_type_c<GL_CLIP_DISTANCE0>,
#else
      enum_type_i,
#endif
      nothing_t,
      true>
      clip_distance0;

    /// @var cull_face
    /// @glconstwrap{CULL_FACE}
    opt_constant<
      mp_list<capability>,
#ifdef GL_CULL_FACE
      enum_type_c<GL_CULL_FACE>>
#else
      enum_type_i>
#endif
      cull_face;

    /// @var depth_clamp
    /// @glconstwrap{DEPTH_CLAMP}
    opt_constant<
      mp_list<capability>,
#ifdef GL_DEPTH_CLAMP
      enum_type_c<GL_DEPTH_CLAMP>>
#else
      enum_type_i>
#endif
      depth_clamp;

    /// @var depth_test
    /// @glconstwrap{DEPTH_TEST}
    opt_constant<
      mp_list<capability>,
#ifdef GL_DEPTH_TEST
      enum_type_c<GL_DEPTH_TEST>>
#else
      enum_type_i>
#endif
      depth_test;

    /// @var scissor_test
    /// @glconstwrap{SCISSOR_TEST}
    opt_constant<
      mp_list<capability>,
#ifdef GL_SCISSOR_TEST
      enum_type_c<GL_SCISSOR_TEST>>
#else
      enum_type_i>
#endif
      scissor_test;

    /// @var stencil_test
    /// @glconstwrap{STENCIL_TEST}
    opt_constant<
      mp_list<capability>,
#ifdef GL_STENCIL_TEST
      enum_type_c<GL_STENCIL_TEST>>
#else
      enum_type_i>
#endif
      stencil_test;

    /// @var polygon_offset_fill
    /// @glconstwrap{POLYGON_OFFSET_FILL}
    opt_constant<
      mp_list<capability>,
#ifdef GL_POLYGON_OFFSET_FILL
      enum_type_c<GL_POLYGON_OFFSET_FILL>>
#else
      enum_type_i>
#endif
      polygon_offset_fill;

    /// @var polygon_offset_line
    /// @glconstwrap{POLYGON_OFFSET_LINE}
    opt_constant<
      mp_list<capability>,
#ifdef GL_POLYGON_OFFSET_LINE
      enum_type_c<GL_POLYGON_OFFSET_LINE>>
#else
      enum_type_i>
#endif
      polygon_offset_line;

    /// @var polygon_offset_point
    /// @glconstwrap{POLYGON_OFFSET_POINT}
    opt_constant<
      mp_list<capability>,
#ifdef GL_POLYGON_OFFSET_POINT
      enum_type_c<GL_POLYGON_OFFSET_POINT>>
#else
      enum_type_i>
#endif
      polygon_offset_point;

    /// @var rasterizer_discard
    /// @glconstwrap{RASTERIZER_DISCARD}
    opt_constant<
      mp_list<capability>,
#ifdef GL_RASTERIZER_DISCARD
      enum_type_c<GL_RASTERIZER_DISCARD>>
#else
      enum_type_i>
#endif
      rasterizer_discard;

    /// @var multisample
    /// @glconstwrap{MULTISAMPLE}
    opt_constant<
      mp_list<capability>,
#ifdef GL_MULTISAMPLE
      enum_type_c<GL_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      multisample;

    /// @var debug_output
    /// @glconstwrap{DEBUG_OUTPUT}
    opt_constant<
      mp_list<capability>,
#ifdef GL_DEBUG_OUTPUT
      enum_type_c<GL_DEBUG_OUTPUT>>
#elif defined(GL_DEBUG_OUTPUT_KHR)
      enum_type_c<GL_DEBUG_OUTPUT_KHR>>
#else
      enum_type_i>
#endif
      debug_output;

    /// @var debug_output_synchronous
    /// @glconstwrap{DEBUG_OUTPUT_SYNCHRONOUS}
    opt_constant<
      mp_list<capability>,
#ifdef GL_DEBUG_OUTPUT_SYNCHRONOUS
      enum_type_c<GL_DEBUG_OUTPUT_SYNCHRONOUS>>
#elif defined(GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR)
      enum_type_c<GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR>>
#else
      enum_type_i>
#endif
      debug_output_synchronous;

    /// @var blackhole_render
    /// @glconstwrap{BLACKHOLE_RENDER_INTEL}
    opt_constant<
      mp_list<capability>,
#ifdef GL_BLACKHOLE_RENDER_INTEL
      enum_type_c<GL_BLACKHOLE_RENDER_INTEL>>
#else
      enum_type_c<0x83FC>>
#endif
      blackhole_render;

    /// @var color_array
    /// @glconstwrap{COLOR_ARRAY}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_COLOR_ARRAY
      enum_type_c<GL_COLOR_ARRAY>>
#else
      enum_type_i>
#endif
      color_array;

    /// @var edge_flag_array
    /// @glconstwrap{EDGE_FLAG_ARRAY}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_EDGE_FLAG_ARRAY
      enum_type_c<GL_EDGE_FLAG_ARRAY>>
#else
      enum_type_i>
#endif
      edge_flag_array;

    /// @var fog_coord_array
    /// @glconstwrap{FOG_COORD_ARRAY}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_FOG_COORD_ARRAY
      enum_type_c<GL_FOG_COORD_ARRAY>>
#else
      enum_type_i>
#endif
      fog_coord_array;

    /// @var index_array
    /// @glconstwrap{INDEX_ARRAY}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_INDEX_ARRAY
      enum_type_c<GL_INDEX_ARRAY>>
#else
      enum_type_i>
#endif
      index_array;

    /// @var normal_array
    /// @glconstwrap{NORMAL_ARRAY}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_NORMAL_ARRAY
      enum_type_c<GL_NORMAL_ARRAY>>
#else
      enum_type_i>
#endif
      normal_array;

    /// @var secondary_color_array
    /// @glconstwrap{SECONDARY_COLOR_ARRAY}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_SECONDARY_COLOR_ARRAY
      enum_type_c<GL_SECONDARY_COLOR_ARRAY>>
#else
      enum_type_i>
#endif
      secondary_color_array;

    /// @var texture_coord_array
    /// @glconstwrap{TEXTURE_COORD_ARRAY}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_TEXTURE_COORD_ARRAY
      enum_type_c<GL_TEXTURE_COORD_ARRAY>>
#else
      enum_type_i>
#endif
      texture_coord_array;

    /// @var vertex_attrib_array_unified_nv
    /// @glconstwrap{VERTEX_ATTRIB_ARRAY_UNIFIED_NV}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV
      enum_type_c<GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV>>
#else
      enum_type_i>
#endif
      vertex_attrib_array_unified_nv;

    /// @var element_array_unified_nv
    /// @glconstwrap{ELEMENT_ARRAY_UNIFIED_NV}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_ELEMENT_ARRAY_UNIFIED_NV
      enum_type_c<GL_ELEMENT_ARRAY_UNIFIED_NV>>
#else
      enum_type_i>
#endif
      element_array_unified_nv;

    /// @var uniform_buffer_unified_nv
    /// @glconstwrap{UNIFORM_BUFFER_UNIFIED_NV}
    opt_constant<
      mp_list<client_capability>,
#ifdef GL_UNIFORM_BUFFER_UNIFIED_NV
      enum_type_c<GL_UNIFORM_BUFFER_UNIFIED_NV>>
#else
      enum_type_i>
#endif
      uniform_buffer_unified_nv;

    /// @var front_left
    /// @glconstwrap{FRONT_LEFT}
    opt_constant<
      mp_list<surface_buffer, framebuffer_attachment>,
#ifdef GL_FRONT_LEFT
      enum_type_c<GL_FRONT_LEFT>>
#else
      enum_type_i>
#endif
      front_left;

    /// @var front_right
    /// @glconstwrap{FRONT_RIGHT}
    opt_constant<
      mp_list<surface_buffer, framebuffer_attachment>,
#ifdef GL_FRONT_RIGHT
      enum_type_c<GL_FRONT_RIGHT>>
#else
      enum_type_i>
#endif
      front_right;

    /// @var back_left
    /// @glconstwrap{BACK_LEFT}
    opt_constant<
      mp_list<surface_buffer, framebuffer_attachment>,
#ifdef GL_BACK_LEFT
      enum_type_c<GL_BACK_LEFT>>
#else
      enum_type_i>
#endif
      back_left;

    /// @var back_right
    /// @glconstwrap{BACK_RIGHT}
    opt_constant<
      mp_list<surface_buffer, framebuffer_attachment>,
#ifdef GL_BACK_RIGHT
      enum_type_c<GL_BACK_RIGHT>>
#else
      enum_type_i>
#endif
      back_right;

    /// @var front
    /// @glconstwrap{FRONT}
    opt_constant<
      mp_list<surface_buffer, face_mode, framebuffer_attachment>,
#ifdef GL_FRONT
      enum_type_c<GL_FRONT>>
#else
      enum_type_i>
#endif
      front;

    /// @var back
    /// @glconstwrap{BACK}
    opt_constant<
      mp_list<surface_buffer, face_mode, framebuffer_attachment>,
#ifdef GL_BACK
      enum_type_c<GL_BACK>>
#else
      enum_type_i>
#endif
      back;

    /// @var left
    /// @glconstwrap{LEFT}
    opt_constant<
      mp_list<surface_buffer>,
#ifdef GL_LEFT
      enum_type_c<GL_LEFT>>
#else
      enum_type_i>
#endif
      left;

    /// @var right
    /// @glconstwrap{RIGHT}
    opt_constant<
      mp_list<surface_buffer>,
#ifdef GL_RIGHT
      enum_type_c<GL_RIGHT>>
#else
      enum_type_i>
#endif
      right;

    /// @var front_and_back
    /// @glconstwrap{FRONT_AND_BACK}
    opt_constant<
      mp_list<surface_buffer, face_mode>,
#ifdef GL_FRONT_AND_BACK
      enum_type_c<GL_FRONT_AND_BACK>>
#else
      enum_type_i>
#endif
      front_and_back;

    /// @var array_buffer_binding
    /// @glconstwrap{ARRAY_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query, program_property>,
#ifdef GL_ARRAY_BUFFER_BINDING
      enum_type_c<GL_ARRAY_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      array_buffer_binding;

    /// @var atomic_counter_buffer_binding
    /// @glconstwrap{ATOMIC_COUNTER_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_ATOMIC_COUNTER_BUFFER_BINDING
      enum_type_c<GL_ATOMIC_COUNTER_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      atomic_counter_buffer_binding;

    /// @var copy_read_buffer_binding
    /// @glconstwrap{COPY_READ_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_COPY_READ_BUFFER_BINDING
      enum_type_c<GL_COPY_READ_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      copy_read_buffer_binding;

    /// @var copy_write_buffer_binding
    /// @glconstwrap{COPY_WRITE_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_COPY_WRITE_BUFFER_BINDING
      enum_type_c<GL_COPY_WRITE_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      copy_write_buffer_binding;

    /// @var dispatch_indirect_buffer_binding
    /// @glconstwrap{DISPATCH_INDIRECT_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_DISPATCH_INDIRECT_BUFFER_BINDING
      enum_type_c<GL_DISPATCH_INDIRECT_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      dispatch_indirect_buffer_binding;

    /// @var draw_indirect_buffer_binding
    /// @glconstwrap{DRAW_INDIRECT_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_DRAW_INDIRECT_BUFFER_BINDING
      enum_type_c<GL_DRAW_INDIRECT_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      draw_indirect_buffer_binding;

    /// @var element_array_buffer_binding
    /// @glconstwrap{ELEMENT_ARRAY_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_ELEMENT_ARRAY_BUFFER_BINDING
      enum_type_c<GL_ELEMENT_ARRAY_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      element_array_buffer_binding;

    /// @var pixel_pack_buffer_binding
    /// @glconstwrap{PIXEL_PACK_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_PIXEL_PACK_BUFFER_BINDING
      enum_type_c<GL_PIXEL_PACK_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      pixel_pack_buffer_binding;

    /// @var pixel_unpack_buffer_binding
    /// @glconstwrap{PIXEL_UNPACK_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_PIXEL_UNPACK_BUFFER_BINDING
      enum_type_c<GL_PIXEL_UNPACK_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      pixel_unpack_buffer_binding;

    /// @var shader_storage_buffer_binding
    /// @glconstwrap{SHADER_STORAGE_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_SHADER_STORAGE_BUFFER_BINDING
      enum_type_c<GL_SHADER_STORAGE_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      shader_storage_buffer_binding;

    /// @var texture_buffer_binding
    /// @glconstwrap{TEXTURE_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BUFFER_BINDING
      enum_type_c<GL_TEXTURE_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      texture_buffer_binding;

    /// @var transform_feedback_buffer_binding
    /// @glconstwrap{TRANSFORM_FEEDBACK_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query, transform_feedback_parameter>,
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_BINDING
      enum_type_c<GL_TRANSFORM_FEEDBACK_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      transform_feedback_buffer_binding;

    /// @var uniform_buffer_binding
    /// @glconstwrap{UNIFORM_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_UNIFORM_BUFFER_BINDING
      enum_type_c<GL_UNIFORM_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      uniform_buffer_binding;

    /// @var query_buffer_binding
    /// @glconstwrap{QUERY_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_QUERY_BUFFER_BINDING
      enum_type_c<GL_QUERY_BUFFER_BINDING>,
#else
      enum_type_i,
#endif
      buffer_name>
      query_buffer_binding;

    /// @var parameter_buffer_binding
    /// @glconstwrap{PARAMETER_BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_PARAMETER_BUFFER_BINDING_ARB
      enum_type_c<GL_PARAMETER_BUFFER_BINDING_ARB>,
#else
      enum_type_i,
#endif
      buffer_name>
      parameter_buffer_binding;

    /// @var buffer_binding
    /// @glconstwrap{BUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_BUFFER_BINDING
      enum_type_c<GL_BUFFER_BINDING>>
#else
      enum_type_i>
#endif
      buffer_binding;

    /// @var draw_framebuffer_binding
    /// @glconstwrap{DRAW_FRAMEBUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_DRAW_FRAMEBUFFER_BINDING
      enum_type_c<GL_DRAW_FRAMEBUFFER_BINDING>,
#else
      enum_type_i,
#endif
      framebuffer_name>
      draw_framebuffer_binding;

    /// @var renderbuffer_binding
    /// @glconstwrap{RENDERBUFFER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_RENDERBUFFER_BINDING
      enum_type_c<GL_RENDERBUFFER_BINDING>,
#else
      enum_type_i,
#endif
      renderbuffer_name>
      renderbuffer_binding;

    /// @var sampler_binding
    /// @glconstwrap{SAMPLER_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_SAMPLER_BINDING
      enum_type_c<GL_SAMPLER_BINDING>,
#else
      enum_type_i,
#endif
      sampler_name>
      sampler_binding;

    /// @var texture_binding_1d
    /// @glconstwrap{TEXTURE_BINDING_1D}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_1D
      enum_type_c<GL_TEXTURE_BINDING_1D>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_1d;

    /// @var texture_binding_2d
    /// @glconstwrap{TEXTURE_BINDING_2D}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_2D
      enum_type_c<GL_TEXTURE_BINDING_2D>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_2d;

    /// @var texture_binding_3d
    /// @glconstwrap{TEXTURE_BINDING_3D}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_3D
      enum_type_c<GL_TEXTURE_BINDING_3D>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_3d;

    /// @var texture_binding_1d_array
    /// @glconstwrap{TEXTURE_BINDING_1D_ARRAY}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_1D_ARRAY
      enum_type_c<GL_TEXTURE_BINDING_1D_ARRAY>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_1d_array;

    /// @var texture_binding_2d_array
    /// @glconstwrap{TEXTURE_BINDING_2D_ARRAY}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_2D_ARRAY
      enum_type_c<GL_TEXTURE_BINDING_2D_ARRAY>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_2d_array;

    /// @var texture_binding_rectangle
    /// @glconstwrap{TEXTURE_BINDING_RECTANGLE}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_RECTANGLE
      enum_type_c<GL_TEXTURE_BINDING_RECTANGLE>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_rectangle;

    /// @var texture_binding_buffer
    /// @glconstwrap{TEXTURE_BINDING_BUFFER}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_BUFFER
      enum_type_c<GL_TEXTURE_BINDING_BUFFER>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_buffer;

    /// @var texture_binding_cube_map
    /// @glconstwrap{TEXTURE_BINDING_CUBE_MAP}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_CUBE_MAP
      enum_type_c<GL_TEXTURE_BINDING_CUBE_MAP>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_cube_map;

    /// @var texture_binding_cube_map_array
    /// @glconstwrap{TEXTURE_BINDING_CUBE_MAP_ARRAY}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_CUBE_MAP_ARRAY
      enum_type_c<GL_TEXTURE_BINDING_CUBE_MAP_ARRAY>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_cube_map_array;

    /// @var texture_binding_2d_multisample
    /// @glconstwrap{TEXTURE_BINDING_2D_MULTISAMPLE}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_2D_MULTISAMPLE
      enum_type_c<GL_TEXTURE_BINDING_2D_MULTISAMPLE>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_2d_multisample;

    /// @var texture_binding_2d_multisample_array
    /// @glconstwrap{TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY
      enum_type_c<GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY>,
#else
      enum_type_i,
#endif
      texture_name>
      texture_binding_2d_multisample_array;

    /// @var texture_binding_external
    /// @glconstwrap{TEXTURE_BINDING_EXTERNAL}
    opt_constant<mp_list<binding_query>, enum_type_c<0x8D67>, texture_name>
      texture_binding_external;

    /// @var transform_feedback_binding
    /// @glconstwrap{TRANSFORM_FEEDBACK_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_TRANSFORM_FEEDBACK_BINDING
      enum_type_c<GL_TRANSFORM_FEEDBACK_BINDING>,
#else
      enum_type_i,
#endif
      transform_feedback_name>
      transform_feedback_binding;

    /// @var vertex_array_binding
    /// @glconstwrap{VERTEX_ARRAY_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_VERTEX_ARRAY_BINDING
      enum_type_c<GL_VERTEX_ARRAY_BINDING>,
#else
      enum_type_i,
#endif
      vertex_array_name>
      vertex_array_binding;

    /// @var program_pipeline_binding
    /// @glconstwrap{PROGRAM_PIPELINE_BINDING}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_PROGRAM_PIPELINE_BINDING
      enum_type_c<GL_PROGRAM_PIPELINE_BINDING>,
#else
      enum_type_i,
#endif
      program_pipeline_name>
      program_pipeline_binding;

    /// @var current_program
    /// @glconstwrap{CURRENT_PROGRAM}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_CURRENT_PROGRAM
      enum_type_c<GL_CURRENT_PROGRAM>,
#else
      enum_type_i,
#endif
      program_name>
      current_program;

    /// @var draw_buffer0
    /// @glconstwrap{DRAW_BUFFER0}
    opt_constant<
      mp_list<binding_query>,
#ifdef GL_DRAW_BUFFER0
      enum_type_c<GL_DRAW_BUFFER0>,
#else
      enum_type_i,
#endif
      nothing_t,
      true>
      draw_buffer0;

    /// @var major_version
    /// @glconstwrap{MAJOR_VERSION}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAJOR_VERSION
      enum_type_c<GL_MAJOR_VERSION>>
#else
      enum_type_i>
#endif
      major_version;

    /// @var minor_version
    /// @glconstwrap{MINOR_VERSION}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MINOR_VERSION
      enum_type_c<GL_MINOR_VERSION>>
#else
      enum_type_i>
#endif
      minor_version;

    /// @var reset_notification_strategy
    /// @glconstwrap{RESET_NOTIFICATION_STRATEGY}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_RESET_NOTIFICATION_STRATEGY
      enum_type_c<GL_RESET_NOTIFICATION_STRATEGY>,
#else
      enum_type_i,
#endif
      oglplus::reset_notification_strategy>
      reset_notification_strategy;

    /// @var num_shading_language_versions
    /// @glconstwrap{NUM_SHADING_LANGUAGE_VERSIONS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_NUM_SHADING_LANGUAGE_VERSIONS
      enum_type_c<GL_NUM_SHADING_LANGUAGE_VERSIONS>>
#else
      enum_type_i>
#endif
      num_shading_language_versions;

    /// @var num_extensions
    /// @glconstwrap{NUM_EXTENSIONS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_NUM_EXTENSIONS
      enum_type_c<GL_NUM_EXTENSIONS>>
#else
      enum_type_i>
#endif
      num_extensions;

    /// @var num_spir_v_extensions
    /// @glconstwrap{NUM_SPIR_V_EXTENSIONS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_NUM_SPIR_V_EXTENSIONS
      enum_type_c<GL_NUM_SPIR_V_EXTENSIONS>>
#else
      enum_type_c<0x9554>>
#endif
      num_spir_v_extensions;

    /// @var context_flags
    /// @glconstwrap{CONTEXT_FLAGS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_CONTEXT_FLAGS
      enum_type_c<GL_CONTEXT_FLAGS>,
#else
      enum_type_i,
#endif
      c_api::enum_bitfield<context_flag_bit>>
      context_flags;

    /// @var context_profile_mask
    /// @glconstwrap{CONTEXT_PROFILE_MASK}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_CONTEXT_PROFILE_MASK
      enum_type_c<GL_CONTEXT_PROFILE_MASK>,
#else
      enum_type_i,
#endif
      c_api::enum_bitfield<context_profile_bit>>
      context_profile_mask;

    /// @var doublebuffer
    /// @glconstwrap{DOUBLEBUFFER}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_DOUBLEBUFFER
      enum_type_c<GL_DOUBLEBUFFER>>
#else
      enum_type_i>
#endif
      doublebuffer;

    /// @var stereo
    /// @glconstwrap{STEREO}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STEREO
      enum_type_c<GL_STEREO>>
#else
      enum_type_i>
#endif
      stereo;

    /// @var clip_origin
    /// @glconstwrap{CLIP_ORIGIN}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_CLIP_ORIGIN
      enum_type_c<GL_CLIP_ORIGIN>>
#else
      enum_type_i>
#endif
      clip_origin;

    /// @var clip_depth_mode
    /// @glconstwrap{CLIP_DEPTH_MODE}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_CLIP_DEPTH_MODE
      enum_type_c<GL_CLIP_DEPTH_MODE>>
#else
      enum_type_i>
#endif
      clip_depth_mode;

    /// @var clamp_read_color
    /// @glconstwrap{CLAMP_READ_COLOR}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_CLAMP_READ_COLOR
      enum_type_c<GL_CLAMP_READ_COLOR>>
#else
      enum_type_i>
#endif
      clamp_read_color;

    /// @var provoking_vertex
    /// @glconstwrap{PROVOKING_VERTEX}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_PROVOKING_VERTEX
      enum_type_c<GL_PROVOKING_VERTEX>,
#else
      enum_type_i,
#endif
      provoke_mode>
      provoking_vertex;

    /// @var layer_provoking_vertex
    /// @glconstwrap{LAYER_PROVOKING_VERTEX}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_LAYER_PROVOKING_VERTEX
      enum_type_c<GL_LAYER_PROVOKING_VERTEX>,
#else
      enum_type_i,
#endif
      provoke_mode>
      layer_provoking_vertex;

    /// @var viewport_index_provoking_vertex
    /// @glconstwrap{VIEWPORT_INDEX_PROVOKING_VERTEX}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_VIEWPORT_INDEX_PROVOKING_VERTEX
      enum_type_c<GL_VIEWPORT_INDEX_PROVOKING_VERTEX>,
#else
      enum_type_i,
#endif
      provoke_mode>
      viewport_index_provoking_vertex;

    /// @var cull_face_mode
    /// @glconstwrap{CULL_FACE_MODE}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_CULL_FACE_MODE
      enum_type_c<GL_CULL_FACE_MODE>,
#else
      enum_type_i,
#endif
      face_mode>
      cull_face_mode;

    /// @var front_face
    /// @glconstwrap{FRONT_FACE}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_FRONT_FACE
      enum_type_c<GL_FRONT_FACE>,
#else
      enum_type_i,
#endif
      face_orientation>
      front_face;

    /// @var polygon_mode
    /// @glconstwrap{POLYGON_MODE}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_POLYGON_MODE
      enum_type_c<GL_POLYGON_MODE>,
#else
      enum_type_i,
#endif
      oglplus::polygon_mode>
      polygon_mode;

    /// @var active_texture
    /// @glconstwrap{ACTIVE_TEXTURE}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_ACTIVE_TEXTURE
      enum_type_c<GL_ACTIVE_TEXTURE>,
#else
      enum_type_i,
#endif
      texture_unit>
      active_texture;

    /// @var stencil_func
    /// @glconstwrap{STENCIL_FUNC}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_FUNC
      enum_type_c<GL_STENCIL_FUNC>>
#else
      enum_type_i>
#endif
      stencil_func;

    /// @var stencil_value_mask
    /// @glconstwrap{STENCIL_VALUE_MASK}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_VALUE_MASK
      enum_type_c<GL_STENCIL_VALUE_MASK>>
#else
      enum_type_i>
#endif
      stencil_value_mask;

    /// @var stencil_ref
    /// @glconstwrap{STENCIL_REF}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_REF
      enum_type_c<GL_STENCIL_REF>>
#else
      enum_type_i>
#endif
      stencil_ref;

    /// @var stencil_fail
    /// @glconstwrap{STENCIL_FAIL}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_FAIL
      enum_type_c<GL_STENCIL_FAIL>>
#else
      enum_type_i>
#endif
      stencil_fail;

    /// @var stencil_pass_depth_pass
    /// @glconstwrap{STENCIL_PASS_DEPTH_PASS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_PASS_DEPTH_FAIL
      enum_type_c<GL_STENCIL_PASS_DEPTH_FAIL>>
#else
      enum_type_i>
#endif
      stencil_pass_depth_fail;

    /// @var stencil_pass_depth_pass
    /// @glconstwrap{STENCIL_PASS_DEPTH_PASS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_PASS_DEPTH_PASS
      enum_type_c<GL_STENCIL_PASS_DEPTH_PASS>>
#else
      enum_type_i>
#endif
      stencil_pass_depth_pass;

    /// @var stencil_back_func
    /// @glconstwrap{STENCIL_BACK_FUNC}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_BACK_FUNC
      enum_type_c<GL_STENCIL_BACK_FUNC>>
#else
      enum_type_i>
#endif
      stencil_back_func;

    /// @var stencil_back_value_mask
    /// @glconstwrap{STENCIL_BACK_VALUE_MASK}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_BACK_VALUE_MASK
      enum_type_c<GL_STENCIL_BACK_VALUE_MASK>>
#else
      enum_type_i>
#endif
      stencil_back_value_mask;

    /// @var stencil_back_ref
    /// @glconstwrap{STENCIL_BACK_REF}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_BACK_REF
      enum_type_c<GL_STENCIL_BACK_REF>>
#else
      enum_type_i>
#endif
      stencil_back_ref;

    /// @var stencil_back_fail
    /// @glconstwrap{STENCIL_BACK_FAIL}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_BACK_FAIL
      enum_type_c<GL_STENCIL_BACK_FAIL>>
#else
      enum_type_i>
#endif
      stencil_back_fail;

    /// @var stencil_back_pass_depth_fail
    /// @glconstwrap{STENCIL_BACK_PASS_DEPTH_FAIL}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_BACK_PASS_DEPTH_FAIL
      enum_type_c<GL_STENCIL_BACK_PASS_DEPTH_FAIL>>
#else
      enum_type_i>
#endif
      stencil_back_pass_depth_fail;

    /// @var stencil_back_pass_depth_pass
    /// @glconstwrap{STENCIL_BACK_PASS_DEPTH_PASS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_BACK_PASS_DEPTH_PASS
      enum_type_c<GL_STENCIL_BACK_PASS_DEPTH_PASS>>
#else
      enum_type_i>
#endif
      stencil_back_pass_depth_pass;

    /// @var stencil_writemask
    /// @glconstwrap{STENCIL_WRITEMASK}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_WRITEMASK
      enum_type_c<GL_STENCIL_WRITEMASK>>
#else
      enum_type_i>
#endif
      stencil_writemask;

    /// @var stencil_back_writemask
    /// @glconstwrap{STENCIL_BACK_WRITEMASK}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_BACK_WRITEMASK
      enum_type_c<GL_STENCIL_BACK_WRITEMASK>>
#else
      enum_type_i>
#endif
      stencil_back_writemask;

    /// @var stencil_clear_value
    /// @glconstwrap{STENCIL_CLEAR_VALUE}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_STENCIL_CLEAR_VALUE
      enum_type_c<GL_STENCIL_CLEAR_VALUE>>
#else
      enum_type_i>
#endif
      stencil_clear_value;

    /// @var depth_func
    /// @glconstwrap{DEPTH_FUNC}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_DEPTH_FUNC
      enum_type_c<GL_DEPTH_FUNC>>
#else
      enum_type_i>
#endif
      depth_func;

    /// @var logic_op_mode
    /// @glconstwrap{LOGIC_OP_MODE}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_LOGIC_OP_MODE
      enum_type_c<GL_LOGIC_OP_MODE>>
#else
      enum_type_i>
#endif
      logic_op_mode;

    /// @var sample_buffers
    /// @glconstwrap{SAMPLE_BUFFERS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_SAMPLE_BUFFERS
      enum_type_c<GL_SAMPLE_BUFFERS>>
#else
      enum_type_i>
#endif
      sample_buffers;

    /// @var subpixel_bits
    /// @glconstwrap{SUBPIXEL_BITS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_SUBPIXEL_BITS
      enum_type_c<GL_SUBPIXEL_BITS>>
#else
      enum_type_i>
#endif
      subpixel_bits;

    /// @var viewport_subpixel_bits
    /// @glconstwrap{VIEWPORT_SUBPIXEL_BITS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_VIEWPORT_SUBPIXEL_BITS
      enum_type_c<GL_VIEWPORT_SUBPIXEL_BITS>>
#else
      enum_type_i>
#endif
      viewport_subpixel_bits;

    /// @var num_compressed_texture_formats
    /// @glconstwrap{NUM_COMPRESSED_TEXTURE_FORMATS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_NUM_COMPRESSED_TEXTURE_FORMATS
      enum_type_c<GL_NUM_COMPRESSED_TEXTURE_FORMATS>>
#else
      enum_type_i>
#endif
      num_compressed_texture_formats;

    /// @var compressed_texture_formats
    /// @glconstwrap{COMPRESSED_TEXTURE_FORMATS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_COMPRESSED_TEXTURE_FORMATS
      enum_type_c<GL_COMPRESSED_TEXTURE_FORMATS>>
#else
      enum_type_i>
#endif
      compressed_texture_formats;

    /// @var num_program_binary_formats
    /// @glconstwrap{NUM_PROGRAM_BINARY_FORMATS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_NUM_PROGRAM_BINARY_FORMATS
      enum_type_c<GL_NUM_PROGRAM_BINARY_FORMATS>>
#else
      enum_type_i>
#endif
      num_program_binary_formats;

    /// @var program_binary_formats
    /// @glconstwrap{PROGRAM_BINARY_FORMATS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_PROGRAM_BINARY_FORMATS
      enum_type_c<GL_PROGRAM_BINARY_FORMATS>>
#else
      enum_type_i>
#endif
      program_binary_formats;

    /// @var num_shader_binary_formats
    /// @glconstwrap{NUM_SHADER_BINARY_FORMATS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_NUM_SHADER_BINARY_FORMATS
      enum_type_c<GL_NUM_SHADER_BINARY_FORMATS>>
#else
      enum_type_i>
#endif
      num_shader_binary_formats;

    /// @var shader_binary_formats
    /// @glconstwrap{SHADER_BINARY_FORMATS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_SHADER_BINARY_FORMATS
      enum_type_c<GL_SHADER_BINARY_FORMATS>>
#else
      enum_type_i>
#endif
      shader_binary_formats;

    /// @var texture_buffer_offset_alignment
    /// @glconstwrap{TEXTURE_BUFFER_OFFSET_ALIGNMENT}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT
      enum_type_c<GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT>>
#else
      enum_type_i>
#endif
      texture_buffer_offset_alignment;

    /// @var max_vertex_uniform_blocks
    /// @glconstwrap{MAX_VERTEX_UNIFORM_BLOCKS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_VERTEX_UNIFORM_BLOCKS
      enum_type_c<GL_MAX_VERTEX_UNIFORM_BLOCKS>>
#else
      enum_type_i>
#endif
      max_vertex_uniform_blocks;

    /// @var max_tess_control_uniform_blocks
    /// @glconstwrap{MAX_TESS_CONTROL_UNIFORM_BLOCKS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS
      enum_type_c<GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS>>
#else
      enum_type_i>
#endif
      max_tess_control_uniform_blocks;

    /// @var max_tess_evaluation_uniform_blocks
    /// @glconstwrap{MAX_TESS_EVALUATION_UNIFORM_BLOCKS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS
      enum_type_c<GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS>>
#else
      enum_type_i>
#endif
      max_tess_evaluation_uniform_blocks;

    /// @var max_geometry_uniform_blocks
    /// @glconstwrap{MAX_GEOMETRY_UNIFORM_BLOCKS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_GEOMETRY_UNIFORM_BLOCKS
      enum_type_c<GL_MAX_GEOMETRY_UNIFORM_BLOCKS>>
#else
      enum_type_i>
#endif
      max_geometry_uniform_blocks;

    /// @var max_fragment_uniform_blocks
    /// @glconstwrap{MAX_FRAGMENT_UNIFORM_BLOCKS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_FRAGMENT_UNIFORM_BLOCKS
      enum_type_c<GL_MAX_FRAGMENT_UNIFORM_BLOCKS>>
#else
      enum_type_i>
#endif
      max_fragment_uniform_blocks;

    /// @var max_compute_uniform_blocks
    /// @glconstwrap{MAX_COMPUTE_UNIFORM_BLOCKS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_COMPUTE_UNIFORM_BLOCKS
      enum_type_c<GL_MAX_COMPUTE_UNIFORM_BLOCKS>>
#else
      enum_type_i>
#endif
      max_compute_uniform_blocks;

    /// @var max_combined_uniform_blocks
    /// @glconstwrap{MAX_COMBINED_UNIFORM_BLOCKS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_COMBINED_UNIFORM_BLOCKS
      enum_type_c<GL_MAX_COMBINED_UNIFORM_BLOCKS>>
#else
      enum_type_i>
#endif
      max_combined_uniform_blocks;

    /// @var max_uniform_block_size
    /// @glconstwrap{MAX_UNIFORM_BLOCK_SIZE}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_UNIFORM_BLOCK_SIZE
      enum_type_c<GL_MAX_UNIFORM_BLOCK_SIZE>>
#else
      enum_type_i>
#endif
      max_uniform_block_size;

    /// @var max_debug_message_length
    /// @glconstwrap{MAX_DEBUG_MESSAGE_LENGTH}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_DEBUG_MESSAGE_LENGTH
      enum_type_c<GL_MAX_DEBUG_MESSAGE_LENGTH>>
#elif defined(GL_MAX_DEBUG_MESSAGE_LENGTH_KHR)
      enum_type_c<GL_MAX_DEBUG_MESSAGE_LENGTH_KHR>>
#else
      enum_type_i>
#endif
      max_debug_message_length;

    /// @var max_debug_logged_messages
    /// @glconstwrap{MAX_DEBUG_LOGGED_MESSAGES}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_DEBUG_LOGGED_MESSAGES
      enum_type_c<GL_MAX_DEBUG_LOGGED_MESSAGES>>
#elif defined(GL_MAX_DEBUG_LOGGED_MESSAGES_KHR)
      enum_type_c<GL_MAX_DEBUG_LOGGED_MESSAGES_KHR>>
#else
      enum_type_i>
#endif
      max_debug_logged_messages;

    /// @var debug_logged_messages
    /// @glconstwrap{DEBUG_LOGGED_MESSAGES}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_DEBUG_LOGGED_MESSAGES
      enum_type_c<GL_DEBUG_LOGGED_MESSAGES>>
#elif defined(GL_DEBUG_LOGGED_MESSAGES_KHR)
      enum_type_c<GL_DEBUG_LOGGED_MESSAGES_KHR>>
#else
      enum_type_i>
#endif
      debug_logged_messages;

    /// @var debug_next_logged_message_length
    /// @glconstwrap{DEBUG_NEXT_LOGGED_MESSAGE_LENGTH}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH
      enum_type_c<GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH>>
#elif defined(GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR)
      enum_type_c<GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR>>
#else
      enum_type_i>
#endif
      debug_next_logged_message_length;

    /// @var max_debug_group_stack_depth
    /// @glconstwrap{MAX_DEBUG_GROUP_STACK_DEPTH}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_DEBUG_GROUP_STACK_DEPTH
      enum_type_c<GL_MAX_DEBUG_GROUP_STACK_DEPTH>>
#elif defined(GL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR)
      enum_type_c<GL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR>>
#else
      enum_type_i>
#endif
      max_debug_group_stack_depth;

    /// @var debug_group_stack_depth
    /// @glconstwrap{DEBUG_GROUP_STACK_DEPTH}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_DEBUG_GROUP_STACK_DEPTH
      enum_type_c<GL_DEBUG_GROUP_STACK_DEPTH>>
#elif defined(GL_DEBUG_GROUP_STACK_DEPTH_KHR)
      enum_type_c<GL_DEBUG_GROUP_STACK_DEPTH_KHR>>
#else
      enum_type_i>
#endif
      debug_group_stack_depth;

    /// @var max_label_length
    /// @glconstwrap{MAX_LABEL_LENGTH}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_LABEL_LENGTH
      enum_type_c<GL_MAX_LABEL_LENGTH>>
#elif defined(GL_MAX_LABEL_LENGTH_KHR)
      enum_type_c<GL_MAX_LABEL_LENGTH_KHR>>
#else
      enum_type_i>
#endif
      max_label_length;

    /// @var shader_compiler
    /// @glconstwrap{SHADER_COMPILER}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_SHADER_COMPILER
      enum_type_c<GL_SHADER_COMPILER>,
#else
      enum_type_i,
#endif
      true_false>
      shader_compiler;

    /// @var max_shader_compiler_threads
    /// @glconstwrap{MAX_SHADER_COMPILER_THREADS}
    opt_constant<
      mp_list<integer_query>,
#ifdef GL_MAX_SHADER_COMPILER_THREADS_ARB
      enum_type_c<GL_MAX_SHADER_COMPILER_THREADS_ARB>>
#else
      enum_type_i>
#endif
      max_shader_compiler_threads;

    /// @var line_width
    /// @glconstwrap{LINE_WIDTH}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_LINE_WIDTH
      enum_type_c<GL_LINE_WIDTH>>
#else
      enum_type_i>
#endif
      line_width;

    /// @var point_size
    /// @glconstwrap{POINT_SIZE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_POINT_SIZE
      enum_type_c<GL_POINT_SIZE>>
#else
      enum_type_i>
#endif
      point_size;

    /// @var polygon_offset_clamp
    /// @glconstwrap{POLYGON_OFFSET_CLAMP}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_POLYGON_OFFSET_CLAMP
      enum_type_c<GL_POLYGON_OFFSET_CLAMP>>
#else
      enum_type_i>
#endif
      polygon_offset_clamp;

    /// @var polygon_offset_factor
    /// @glconstwrap{POLYGON_OFFSET_FACTOR}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_POLYGON_OFFSET_FACTOR
      enum_type_c<GL_POLYGON_OFFSET_FACTOR>>
#else
      enum_type_i>
#endif
      polygon_offset_factor;

    /// @var polygon_offset_units
    /// @glconstwrap{POLYGON_OFFSET_UNITS}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_POLYGON_OFFSET_UNITS
      enum_type_c<GL_POLYGON_OFFSET_UNITS>>
#else
      enum_type_i>
#endif
      polygon_offset_units;

    /// @var sample_coverage_value
    /// @glconstwrap{SAMPLE_COVERAGE_VALUE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_SAMPLE_COVERAGE_VALUE
      enum_type_c<GL_SAMPLE_COVERAGE_VALUE>>
#else
      enum_type_i>
#endif
      sample_coverage_value;

    /// @var blend_color
    /// @glconstwrap{BLEND_COLOR}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_BLEND_COLOR
      enum_type_c<GL_BLEND_COLOR>>
#else
      enum_type_i>
#endif
      blend_color;

    /// @var color_clear_value
    /// @glconstwrap{COLOR_CLEAR_VALUE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_COLOR_CLEAR_VALUE
      enum_type_c<GL_COLOR_CLEAR_VALUE>>
#else
      enum_type_i>
#endif
      color_clear_value;

    /// @var depth_clear_value
    /// @glconstwrap{DEPTH_CLEAR_VALUE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_DEPTH_CLEAR_VALUE
      enum_type_c<GL_DEPTH_CLEAR_VALUE>>
#else
      enum_type_i>
#endif
      depth_clear_value;

    /// @var viewport_bounds_range
    /// @glconstwrap{VIEWPORT_BOUNDS_RANGE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_VIEWPORT_BOUNDS_RANGE
      enum_type_c<GL_VIEWPORT_BOUNDS_RANGE>>
#else
      enum_type_i>
#endif
      viewport_bounds_range;

    /// @var point_size_range
    /// @glconstwrap{POINT_SIZE_RANGE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_POINT_SIZE_RANGE
      enum_type_c<GL_POINT_SIZE_RANGE>>
#else
      enum_type_i>
#endif
      point_size_range;

    /// @var point_size_granularity
    /// @glconstwrap{POINT_SIZE_GRANULARITY}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_POINT_SIZE_GRANULARITY
      enum_type_c<GL_POINT_SIZE_GRANULARITY>>
#else
      enum_type_i>
#endif
      point_size_granularity;

    /// @var aliased_line_width_range
    /// @glconstwrap{ALIASED_LINE_WIDTH_RANGE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_ALIASED_LINE_WIDTH_RANGE
      enum_type_c<GL_ALIASED_LINE_WIDTH_RANGE>>
#else
      enum_type_i>
#endif
      aliased_line_width_range;

    /// @var smooth_line_width_range
    /// @glconstwrap{SMOOTH_LINE_WIDTH_RANGE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_SMOOTH_LINE_WIDTH_RANGE
      enum_type_c<GL_SMOOTH_LINE_WIDTH_RANGE>>
#else
      enum_type_i>
#endif
      smooth_line_width_range;

    /// @var smooth_line_width_granularity
    /// @glconstwrap{SMOOTH_LINE_WIDTH_GRANULARITY}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_SMOOTH_LINE_WIDTH_GRANULARITY
      enum_type_c<GL_SMOOTH_LINE_WIDTH_GRANULARITY>>
#else
      enum_type_i>
#endif
      smooth_line_width_granularity;

    /// @var min_sample_shading_value
    /// @glconstwrap{MIN_SAMPLE_SHADING_VALUE}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_MIN_SAMPLE_SHADING_VALUE
      enum_type_c<GL_MIN_SAMPLE_SHADING_VALUE>>
#else
      enum_type_i>
#endif
      min_sample_shading_value;

    /// @var min_fragment_interpolation_offset
    /// @glconstwrap{MIN_FRAGMENT_INTERPOLATION_OFFSET}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_MIN_FRAGMENT_INTERPOLATION_OFFSET
      enum_type_c<GL_MIN_FRAGMENT_INTERPOLATION_OFFSET>>
#else
      enum_type_i>
#endif
      min_fragment_interpolation_offset;

    /// @var max_fragment_interpolation_offset
    /// @glconstwrap{MAX_FRAGMENT_INTERPOLATION_OFFSET}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_MAX_FRAGMENT_INTERPOLATION_OFFSET
      enum_type_c<GL_MAX_FRAGMENT_INTERPOLATION_OFFSET>>
#else
      enum_type_i>
#endif
      max_fragment_interpolation_offset;

    /// @var max_texture_lod_bias
    /// @glconstwrap{MAX_TEXTURE_LOD_BIAS}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_MAX_TEXTURE_LOD_BIAS
      enum_type_c<GL_MAX_TEXTURE_LOD_BIAS>>
#else
      enum_type_i>
#endif
      max_texture_lod_bias;

    /// @var max_texture_max_anisotropy
    /// @glconstwrap{MAX_TEXTURE_MAX_ANISOTROPY}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_MAX_TEXTURE_MAX_ANISOTROPY
      enum_type_c<GL_MAX_TEXTURE_MAX_ANISOTROPY>>
#else
      enum_type_i>
#endif
      max_texture_max_anisotropy;

    /// @var max_viewport_dims
    /// @glconstwrap{MAX_VIEWPORT_DIMS}
    opt_constant<
      mp_list<float_query>,
#ifdef GL_MAX_VIEWPORT_DIMS
      enum_type_c<GL_MAX_VIEWPORT_DIMS>>
#else
      enum_type_i>
#endif
      max_viewport_dims;

    /// @var vendor
    /// @glconstwrap{VENDOR}
    opt_constant<
      mp_list<string_query>,
#ifdef GL_VENDOR
      enum_type_c<GL_VENDOR>>
#else
      enum_type_i>
#endif
      vendor;

    /// @var renderer
    /// @glconstwrap{RENDERER}
    opt_constant<
      mp_list<string_query>,
#ifdef GL_RENDERER
      enum_type_c<GL_RENDERER>>
#else
      enum_type_i>
#endif
      renderer;

    /// @var version
    /// @glconstwrap{VERSION}
    opt_constant<
      mp_list<string_query>,
#ifdef GL_VERSION
      enum_type_c<GL_VERSION>>
#else
      enum_type_i>
#endif
      version;

    /// @var shading_language_version
    /// @glconstwrap{SHADING_LANGUAGE_VERSION}
    opt_constant<
      mp_list<string_query>,
#ifdef GL_SHADING_LANGUAGE_VERSION
      enum_type_c<GL_SHADING_LANGUAGE_VERSION>>
#else
      enum_type_i>
#endif
      shading_language_version;

    /// @var extensions
    /// @glconstwrap{EXTENSIONS}
    opt_constant<
      mp_list<string_query>,
#ifdef GL_EXTENSIONS
      enum_type_c<GL_EXTENSIONS>>
#else
      enum_type_i>
#endif
      extensions;

    /// @var spir_v_extensions
    /// @glconstwrap{SPIR_V_EXTENSIONS}
    opt_constant<
      mp_list<string_query>,
#ifdef GL_SPIR_V_EXTENSIONS
      enum_type_c<GL_SPIR_V_EXTENSIONS>>
#else
      enum_type_c<0x9553>>
#endif
      spir_v_extensions;

    /// @var named_string_length
    /// @glconstwrap{NAMED_STRING_LENGTH_ARB}
    opt_constant<
      mp_list<named_string_query>,
#ifdef GL_NAMED_STRING_LENGTH_ARB
      enum_type_c<GL_NAMED_STRING_LENGTH_ARB>>
#else
      enum_type_c<0x8DE9>>
#endif
      named_string_length;

    /// @var named_string_type
    /// @glconstwrap{NAMED_STRING_TYPE_ARB}
    opt_constant<
      mp_list<named_string_query>,
#ifdef GL_NAMED_STRING_TYPE_ARB
      enum_type_c<GL_NAMED_STRING_TYPE_ARB>,
#else
      enum_type_c<0x8DEA>,
#endif
      named_string_kind>
      named_string_type;

    /// @var color_buffer_bit
    /// @glconstwrap{COLOR_BUFFER_BIT}
    opt_constant<
      mp_list<buffer_clear_bit, buffer_blit_bit>,
#ifdef GL_COLOR_BUFFER_BIT
      bitfield_type_c<GL_COLOR_BUFFER_BIT>>
#else
      bitfield_type_i>
#endif
      color_buffer_bit;

    /// @var depth_buffer_bit
    /// @glconstwrap{DEPTH_BUFFER_BIT}
    opt_constant<
      mp_list<buffer_clear_bit, buffer_blit_bit>,
#ifdef GL_DEPTH_BUFFER_BIT
      bitfield_type_c<GL_DEPTH_BUFFER_BIT>>
#else
      bitfield_type_i>
#endif
      depth_buffer_bit;

    /// @var stencil_buffer_bit
    /// @glconstwrap{STENCIL_BUFFER_BIT}
    opt_constant<
      mp_list<buffer_clear_bit, buffer_blit_bit>,
#ifdef GL_STENCIL_BUFFER_BIT
      bitfield_type_c<GL_STENCIL_BUFFER_BIT>>
#else
      bitfield_type_i>
#endif
      stencil_buffer_bit;

    /// @var lequal
    /// @glconstwrap{LEQUAL}
    opt_constant<
      mp_list<compare_function>,
#ifdef GL_LEQUAL
      enum_type_c<GL_LEQUAL>>
#else
      enum_type_i>
#endif
      lequal;

    /// @var gequal
    /// @glconstwrap{GEQUAL}
    opt_constant<
      mp_list<compare_function>,
#ifdef GL_GEQUAL
      enum_type_c<GL_GEQUAL>>
#else
      enum_type_i>
#endif
      gequal;

    /// @var less
    /// @glconstwrap{LESS}
    opt_constant<
      mp_list<compare_function>,
#ifdef GL_LESS
      enum_type_c<GL_LESS>>
#else
      enum_type_i>
#endif
      less;

    /// @var greater
    /// @glconstwrap{GREATER}
    opt_constant<
      mp_list<compare_function>,
#ifdef GL_GREATER
      enum_type_c<GL_GREATER>>
#else
      enum_type_i>
#endif
      greater;

    /// @var equal
    /// @glconstwrap{EQUAL}
    opt_constant<
      mp_list<compare_function, tess_gen_primitive_spacing>,
#ifdef GL_EQUAL
      enum_type_c<GL_EQUAL>>
#else
      enum_type_i>
#endif
      equal;

    /// @var notequal
    /// @glconstwrap{NOTEQUAL}
    opt_constant<
      mp_list<compare_function>,
#ifdef GL_NOTEQUAL
      enum_type_c<GL_NOTEQUAL>>
#else
      enum_type_i>
#endif
      notequal;

    /// @var always
    /// @glconstwrap{ALWAYS}
    opt_constant<
      mp_list<compare_function>,
#ifdef GL_ALWAYS
      enum_type_c<GL_ALWAYS>>
#else
      enum_type_i>
#endif
      always;

    /// @var never
    /// @glconstwrap{NEVER}
    opt_constant<
      mp_list<compare_function>,
#ifdef GL_NEVER
      enum_type_c<GL_NEVER>>
#else
      enum_type_i>
#endif
      never;

    /// @var float_
    /// @glconstwrap{FLOAT}
    type_constructor_constant<opt_constant<
      mp_list<data_type, sl_data_type, pixel_data_type>,
#ifdef GL_FLOAT
      enum_type_c<GL_FLOAT>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type>>
      float_;

    /// @var float_vec2
    /// @glconstwrap{FLOAT_VEC2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_VEC2
      enum_type_c<GL_FLOAT_VEC2>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[2]>>
      float_vec2;

    /// @var float_vec3
    /// @glconstwrap{FLOAT_VEC3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_VEC3
      enum_type_c<GL_FLOAT_VEC3>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[3]>>
      float_vec3;

    /// @var float_vec4
    /// @glconstwrap{FLOAT_VEC4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_VEC4
      enum_type_c<GL_FLOAT_VEC4>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[4]>>
      float_vec4;

    /// @var double_
    /// @glconstwrap{DOUBLE}
    type_constructor_constant<opt_constant<
      mp_list<data_type, sl_data_type>,
#ifdef GL_DOUBLE
      enum_type_c<GL_DOUBLE>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type>>
      double_;

    /// @var double_vec2
    /// @glconstwrap{DOUBLE_VEC2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_VEC2
      enum_type_c<GL_DOUBLE_VEC2>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[2]>>
      double_vec2;

    /// @var double_vec3
    /// @glconstwrap{DOUBLE_VEC3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_VEC3
      enum_type_c<GL_DOUBLE_VEC3>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[3]>>
      double_vec3;

    /// @var double_vec4
    /// @glconstwrap{DOUBLE_VEC4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_VEC4
      enum_type_c<GL_DOUBLE_VEC4>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[4]>>
      double_vec4;

    /// @var int_
    /// @glconstwrap{INT}
    type_constructor_constant<opt_constant<
      mp_list<data_type, sl_data_type, pixel_data_type>,
#ifdef GL_INT
      enum_type_c<GL_INT>,
#else
      enum_type_i,
#endif
      typename gl_types::int_type>>
      int_;

    /// @var int_vec2
    /// @glconstwrap{INT_VEC2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_VEC2
      enum_type_c<GL_INT_VEC2>,
#else
      enum_type_i,
#endif
      typename gl_types::int_type[2]>>
      int_vec2;

    /// @var int_vec3
    /// @glconstwrap{INT_VEC3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_VEC3
      enum_type_c<GL_INT_VEC3>,
#else
      enum_type_i,
#endif
      typename gl_types::int_type[3]>>
      int_vec3;

    /// @var int_vec4
    /// @glconstwrap{INT_VEC4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_VEC4
      enum_type_c<GL_INT_VEC4>,
#else
      enum_type_i,
#endif
      typename gl_types::int_type[4]>>
      int_vec4;

    /// @var unsigned_int_
    /// @glconstwrap{UNSIGNED_INT}
    type_constructor_constant<opt_constant<
      mp_list<data_type, sl_data_type, pixel_data_type, index_data_type>,
#ifdef GL_UNSIGNED_INT
      enum_type_c<GL_UNSIGNED_INT>,
#else
      enum_type_i,
#endif
      typename gl_types::uint_type>>
      unsigned_int_;

    /// @var unsigned_int_vec2
    /// @glconstwrap{UNSIGNED_INT_VEC2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_VEC2
      enum_type_c<GL_UNSIGNED_INT_VEC2>,
#else
      enum_type_i,
#endif
      typename gl_types::uint_type[2]>>
      unsigned_int_vec2;

    /// @var unsigned_int_vec3
    /// @glconstwrap{UNSIGNED_INT_VEC3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_VEC3
      enum_type_c<GL_UNSIGNED_INT_VEC3>,
#else
      enum_type_i,
#endif
      typename gl_types::uint_type[3]>>
      unsigned_int_vec3;

    /// @var unsigned_int_vec4
    /// @glconstwrap{UNSIGNED_INT_VEC4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_VEC4
      enum_type_c<GL_UNSIGNED_INT_VEC4>,
#else
      enum_type_i,
#endif
      typename gl_types::uint_type[4]>>
      unsigned_int_vec4;

    /// @var bool_
    /// @glconstwrap{BOOL}
    type_constructor_constant<opt_constant<
      mp_list<data_type, sl_data_type>,
#ifdef GL_BOOL
      enum_type_c<GL_BOOL>,
#else
      enum_type_i,
#endif
      typename gl_types::bool_type>>
      bool_;

    /// @var bool_vec2
    /// @glconstwrap{BOOL_VEC2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_BOOL_VEC2
      enum_type_c<GL_BOOL_VEC2>,
#else
      enum_type_i,
#endif
      typename gl_types::bool_type[2]>>
      bool_vec2;

    /// @var bool_vec3
    /// @glconstwrap{BOOL_VEC3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_BOOL_VEC3
      enum_type_c<GL_BOOL_VEC3>,
#else
      enum_type_i,
#endif
      typename gl_types::bool_type[3]>>
      bool_vec3;

    /// @var bool_vec4
    /// @glconstwrap{BOOL_VEC4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_BOOL_VEC4
      enum_type_c<GL_BOOL_VEC4>,
#else
      enum_type_i,
#endif
      typename gl_types::bool_type[4]>>
      bool_vec4;

    /// @var float_mat2
    /// @glconstwrap{FLOAT_MAT2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT2
      enum_type_c<GL_FLOAT_MAT2>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[2][2]>>
      float_mat2;

    /// @var float_mat3
    /// @glconstwrap{FLOAT_MAT3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT3
      enum_type_c<GL_FLOAT_MAT3>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[3][3]>>
      float_mat3;

    /// @var float_mat4
    /// @glconstwrap{FLOAT_MAT4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT4
      enum_type_c<GL_FLOAT_MAT4>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[4][4]>>
      float_mat4;

    /// @var float_mat2x3
    /// @glconstwrap{FLOAT_MAT2x3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT2x3
      enum_type_c<GL_FLOAT_MAT2x3>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[2][3]>>
      float_mat2x3;

    /// @var float_mat2x4
    /// @glconstwrap{FLOAT_MAT2x4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT2x4
      enum_type_c<GL_FLOAT_MAT2x4>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[2][4]>>
      float_mat2x4;

    /// @var float_mat3x2
    /// @glconstwrap{FLOAT_MAT3x2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT3x2
      enum_type_c<GL_FLOAT_MAT3x2>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[3][2]>>
      float_mat3x2;

    /// @var float_mat3x4
    /// @glconstwrap{FLOAT_MAT3x4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT3x4
      enum_type_c<GL_FLOAT_MAT3x4>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[3][4]>>
      float_mat3x4;

    /// @var float_mat4x2
    /// @glconstwrap{FLOAT_MAT4x2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT4x2
      enum_type_c<GL_FLOAT_MAT4x2>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[4][2]>>
      float_mat4x2;

    /// @var float_mat4x3
    /// @glconstwrap{FLOAT_MAT4x3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_FLOAT_MAT4x3
      enum_type_c<GL_FLOAT_MAT4x3>,
#else
      enum_type_i,
#endif
      typename gl_types::float_type[4][3]>>
      float_mat4x3;

    /// @var double_mat2
    /// @glconstwrap{DOUBLE_MAT2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT2
      enum_type_c<GL_DOUBLE_MAT2>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[2][2]>>
      double_mat2;

    /// @var double_mat3
    /// @glconstwrap{DOUBLE_MAT3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT3
      enum_type_c<GL_DOUBLE_MAT3>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[3][3]>>
      double_mat3;

    /// @var double_mat4
    /// @glconstwrap{DOUBLE_MAT4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT4
      enum_type_c<GL_DOUBLE_MAT4>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[4][4]>>
      double_mat4;

    /// @var double_mat2x3
    /// @glconstwrap{DOUBLE_MAT2x3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT2x3
      enum_type_c<GL_DOUBLE_MAT2x3>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[2][3]>>
      double_mat2x3;

    /// @var double_mat2x4
    /// @glconstwrap{DOUBLE_MAT2x4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT2x4
      enum_type_c<GL_DOUBLE_MAT2x4>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[2][4]>>
      double_mat2x4;

    /// @var double_mat3x2
    /// @glconstwrap{DOUBLE_MAT3x2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT3x2
      enum_type_c<GL_DOUBLE_MAT3x2>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[3][2]>>
      double_mat3x2;

    /// @var double_mat3x4
    /// @glconstwrap{DOUBLE_MAT3x4}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT3x4
      enum_type_c<GL_DOUBLE_MAT3x4>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[3][4]>>
      double_mat3x4;

    /// @var double_mat4x2
    /// @glconstwrap{DOUBLE_MAT4x2}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT4x2
      enum_type_c<GL_DOUBLE_MAT4x2>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[4][2]>>
      double_mat4x2;

    /// @var double_mat4x3
    /// @glconstwrap{DOUBLE_MAT4x3}
    type_constructor_constant<opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_DOUBLE_MAT4x3
      enum_type_c<GL_DOUBLE_MAT4x3>,
#else
      enum_type_i,
#endif
      typename gl_types::double_type[4][3]>>
      double_mat4x3;

    /// @var sampler_1d
    /// @glconstwrap{SAMPLER_1D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_1D
      enum_type_c<GL_SAMPLER_1D>>
#else
      enum_type_i>
#endif
      sampler_1d;

    /// @var sampler_2d
    /// @glconstwrap{SAMPLER_2D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_2D
      enum_type_c<GL_SAMPLER_2D>>
#else
      enum_type_i>
#endif
      sampler_2d;

    /// @var sampler_3d
    /// @glconstwrap{SAMPLER_3D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_3D
      enum_type_c<GL_SAMPLER_3D>>
#else
      enum_type_i>
#endif
      sampler_3d;

    /// @var sampler_cube
    /// @glconstwrap{SAMPLER_CUBE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_CUBE
      enum_type_c<GL_SAMPLER_CUBE>>
#else
      enum_type_i>
#endif
      sampler_cube;

    /// @var sampler_1d_shadow
    /// @glconstwrap{SAMPLER_1D_SHADOW}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_1D_SHADOW
      enum_type_c<GL_SAMPLER_1D_SHADOW>>
#else
      enum_type_i>
#endif
      sampler_1d_shadow;

    /// @var sampler_2d_shadow
    /// @glconstwrap{SAMPLER_2D_SHADOW}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_2D_SHADOW
      enum_type_c<GL_SAMPLER_2D_SHADOW>>
#else
      enum_type_i>
#endif
      sampler_2d_shadow;

    /// @var sampler_1d_array
    /// @glconstwrap{SAMPLER_1D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_1D_ARRAY
      enum_type_c<GL_SAMPLER_1D_ARRAY>>
#else
      enum_type_i>
#endif
      sampler_1d_array;

    /// @var sampler_2d_array
    /// @glconstwrap{SAMPLER_2D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_2D_ARRAY
      enum_type_c<GL_SAMPLER_2D_ARRAY>>
#else
      enum_type_i>
#endif
      sampler_2d_array;

    /// @var sampler_cube_map_array
    /// @glconstwrap{SAMPLER_CUBE_MAP_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_CUBE_MAP_ARRAY
      enum_type_c<GL_SAMPLER_CUBE_MAP_ARRAY>>
#else
      enum_type_i>
#endif
      sampler_cube_map_array;

    /// @var sampler_1d_array_shadow
    /// @glconstwrap{SAMPLER_1D_ARRAY_SHADOW}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_1D_ARRAY_SHADOW
      enum_type_c<GL_SAMPLER_1D_ARRAY_SHADOW>>
#else
      enum_type_i>
#endif
      sampler_1d_array_shadow;

    /// @var sampler_2d_array_shadow
    /// @glconstwrap{SAMPLER_2D_ARRAY_SHADOW}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_2D_ARRAY_SHADOW
      enum_type_c<GL_SAMPLER_2D_ARRAY_SHADOW>>
#else
      enum_type_i>
#endif
      sampler_2d_array_shadow;

    /// @var sampler_2d_multisample
    /// @glconstwrap{SAMPLER_2D_MULTISAMPLE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_2D_MULTISAMPLE
      enum_type_c<GL_SAMPLER_2D_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      sampler_2d_multisample;

    /// @var sampler_2d_multisample_array
    /// @glconstwrap{SAMPLER_2D_MULTISAMPLE_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_2D_MULTISAMPLE_ARRAY
      enum_type_c<GL_SAMPLER_2D_MULTISAMPLE_ARRAY>>
#else
      enum_type_i>
#endif
      sampler_2d_multisample_array;

    /// @var sampler_cube_shadow
    /// @glconstwrap{SAMPLER_CUBE_SHADOW}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_CUBE_SHADOW
      enum_type_c<GL_SAMPLER_CUBE_SHADOW>>
#else
      enum_type_i>
#endif
      sampler_cube_shadow;

    /// @var sampler_cube_map_array_shadow
    /// @glconstwrap{SAMPLER_CUBE_MAP_ARRAY_SHADOW}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW
      enum_type_c<GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW>>
#else
      enum_type_i>
#endif
      sampler_cube_map_array_shadow;

    /// @var sampler_buffer
    /// @glconstwrap{SAMPLER_BUFFER}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_BUFFER
      enum_type_c<GL_SAMPLER_BUFFER>>
#else
      enum_type_i>
#endif
      sampler_buffer;

    /// @var sampler_2d_rect
    /// @glconstwrap{SAMPLER_2D_RECT}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_2D_RECT
      enum_type_c<GL_SAMPLER_2D_RECT>>
#else
      enum_type_i>
#endif
      sampler_2d_rect;

    /// @var sampler_2d_rect_shadow
    /// @glconstwrap{SAMPLER_2D_RECT_SHADOW}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_SAMPLER_2D_RECT_SHADOW
      enum_type_c<GL_SAMPLER_2D_RECT_SHADOW>>
#else
      enum_type_i>
#endif
      sampler_2d_rect_shadow;

    /// @var int_sampler_1d
    /// @glconstwrap{INT_SAMPLER_1D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_1D
      enum_type_c<GL_INT_SAMPLER_1D>>
#else
      enum_type_i>
#endif
      int_sampler_1d;

    /// @var int_sampler_2d
    /// @glconstwrap{INT_SAMPLER_2D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_2D
      enum_type_c<GL_INT_SAMPLER_2D>>
#else
      enum_type_i>
#endif
      int_sampler_2d;

    /// @var int_sampler_3d
    /// @glconstwrap{INT_SAMPLER_3D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_3D
      enum_type_c<GL_INT_SAMPLER_3D>>
#else
      enum_type_i>
#endif
      int_sampler_3d;

    /// @var int_sampler_cube
    /// @glconstwrap{INT_SAMPLER_CUBE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_CUBE
      enum_type_c<GL_INT_SAMPLER_CUBE>>
#else
      enum_type_i>
#endif
      int_sampler_cube;

    /// @var int_sampler_1d_array
    /// @glconstwrap{INT_SAMPLER_1D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_1D_ARRAY
      enum_type_c<GL_INT_SAMPLER_1D_ARRAY>>
#else
      enum_type_i>
#endif
      int_sampler_1d_array;

    /// @var int_sampler_2d_array
    /// @glconstwrap{INT_SAMPLER_2D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_2D_ARRAY
      enum_type_c<GL_INT_SAMPLER_2D_ARRAY>>
#else
      enum_type_i>
#endif
      int_sampler_2d_array;

    /// @var int_sampler_cube_map_array
    /// @glconstwrap{INT_SAMPLER_CUBE_MAP_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_CUBE_MAP_ARRAY
      enum_type_c<GL_INT_SAMPLER_CUBE_MAP_ARRAY>>
#else
      enum_type_i>
#endif
      int_sampler_cube_map_array;

    /// @var int_sampler_2d_multisample
    /// @glconstwrap{INT_SAMPLER_2D_MULTISAMPLE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_2D_MULTISAMPLE
      enum_type_c<GL_INT_SAMPLER_2D_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      int_sampler_2d_multisample;

    /// @var int_sampler_2d_multisample_array
    /// @glconstwrap{INT_SAMPLER_2D_MULTISAMPLE_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
      enum_type_c<GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY>>
#else
      enum_type_i>
#endif
      int_sampler_2d_multisample_array;

    /// @var int_sampler_buffer
    /// @glconstwrap{INT_SAMPLER_BUFFER}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_BUFFER
      enum_type_c<GL_INT_SAMPLER_BUFFER>>
#else
      enum_type_i>
#endif
      int_sampler_buffer;

    /// @var int_sampler_2d_rect
    /// @glconstwrap{INT_SAMPLER_2D_RECT}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_SAMPLER_2D_RECT
      enum_type_c<GL_INT_SAMPLER_2D_RECT>>
#else
      enum_type_i>
#endif
      int_sampler_2d_rect;

    /// @var unsigned_int_sampler_1d
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_1D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_1D
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_1D>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_1d;

    /// @var unsigned_int_sampler_2d
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_2D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_2D
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_2D>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_2d;

    /// @var unsigned_int_sampler_3d
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_3D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_3D
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_3D>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_3d;

    /// @var unsigned_int_sampler_cube
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_CUBE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_CUBE
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_CUBE>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_cube;

    /// @var unsigned_int_sampler_1d_array
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_1D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_1D_ARRAY
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_1D_ARRAY>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_1d_array;

    /// @var unsigned_int_sampler_2d_array
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_2D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_2D_ARRAY>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_2d_array;

    /// @var unsigned_int_sampler_cube_map_array
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_cube_map_array;

    /// @var unsigned_int_sampler_2d_multisample
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_2d_multisample;

    /// @var unsigned_int_sampler_2d_multisample_array
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_2d_multisample_array;

    /// @var unsigned_int_sampler_buffer
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_BUFFER}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_BUFFER
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_BUFFER>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_buffer;

    /// @var unsigned_int_sampler_2d_rect
    /// @glconstwrap{UNSIGNED_INT_SAMPLER_2D_RECT}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_RECT
      enum_type_c<GL_UNSIGNED_INT_SAMPLER_2D_RECT>>
#else
      enum_type_i>
#endif
      unsigned_int_sampler_2d_rect;

    /// @var image_1d
    /// @glconstwrap{IMAGE_1D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_1D
      enum_type_c<GL_IMAGE_1D>>
#else
      enum_type_i>
#endif
      image_1d;

    /// @var image_2d
    /// @glconstwrap{IMAGE_2D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_2D
      enum_type_c<GL_IMAGE_2D>>
#else
      enum_type_i>
#endif
      image_2d;

    /// @var image_3d
    /// @glconstwrap{IMAGE_3D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_3D
      enum_type_c<GL_IMAGE_3D>>
#else
      enum_type_i>
#endif
      image_3d;

    /// @var image_2d_rect
    /// @glconstwrap{IMAGE_2D_RECT}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_2D_RECT
      enum_type_c<GL_IMAGE_2D_RECT>>
#else
      enum_type_i>
#endif
      image_2d_rect;

    /// @var image_cube
    /// @glconstwrap{IMAGE_CUBE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_CUBE
      enum_type_c<GL_IMAGE_CUBE>>
#else
      enum_type_i>
#endif
      image_cube;

    /// @var image_buffer
    /// @glconstwrap{IMAGE_BUFFER}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_BUFFER
      enum_type_c<GL_IMAGE_BUFFER>>
#else
      enum_type_i>
#endif
      image_buffer;

    /// @var image_1d_array
    /// @glconstwrap{IMAGE_1D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_1D_ARRAY
      enum_type_c<GL_IMAGE_1D_ARRAY>>
#else
      enum_type_i>
#endif
      image_1d_array;

    /// @var image_2d_array
    /// @glconstwrap{IMAGE_2D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_2D_ARRAY
      enum_type_c<GL_IMAGE_2D_ARRAY>>
#else
      enum_type_i>
#endif
      image_2d_array;

    /// @var image_2d_multisample
    /// @glconstwrap{IMAGE_2D_MULTISAMPLE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_2D_MULTISAMPLE
      enum_type_c<GL_IMAGE_2D_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      image_2d_multisample;

    /// @var image_2d_multisample_array
    /// @glconstwrap{IMAGE_2D_MULTISAMPLE_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_IMAGE_2D_MULTISAMPLE_ARRAY
      enum_type_c<GL_IMAGE_2D_MULTISAMPLE_ARRAY>>
#else
      enum_type_i>
#endif
      image_2d_multisample_array;

    /// @var int_image_1d
    /// @glconstwrap{INT_IMAGE_1D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_1D
      enum_type_c<GL_INT_IMAGE_1D>>
#else
      enum_type_i>
#endif
      int_image_1d;

    /// @var int_image_2d
    /// @glconstwrap{INT_IMAGE_2D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_2D
      enum_type_c<GL_INT_IMAGE_2D>>
#else
      enum_type_i>
#endif
      int_image_2d;

    /// @var int_image_3d
    /// @glconstwrap{INT_IMAGE_3D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_3D
      enum_type_c<GL_INT_IMAGE_3D>>
#else
      enum_type_i>
#endif
      int_image_3d;

    /// @var int_image_2d_rect
    /// @glconstwrap{INT_IMAGE_2D_RECT}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_2D_RECT
      enum_type_c<GL_INT_IMAGE_2D_RECT>>
#else
      enum_type_i>
#endif
      int_image_2d_rect;

    /// @var int_image_cube
    /// @glconstwrap{INT_IMAGE_CUBE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_CUBE
      enum_type_c<GL_INT_IMAGE_CUBE>>
#else
      enum_type_i>
#endif
      int_image_cube;

    /// @var int_image_buffer
    /// @glconstwrap{INT_IMAGE_BUFFER}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_BUFFER
      enum_type_c<GL_INT_IMAGE_BUFFER>>
#else
      enum_type_i>
#endif
      int_image_buffer;

    /// @var int_image_1d_array
    /// @glconstwrap{INT_IMAGE_1D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_1D_ARRAY
      enum_type_c<GL_INT_IMAGE_1D_ARRAY>>
#else
      enum_type_i>
#endif
      int_image_1d_array;

    /// @var int_image_2d_array
    /// @glconstwrap{INT_IMAGE_2D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_2D_ARRAY
      enum_type_c<GL_INT_IMAGE_2D_ARRAY>>
#else
      enum_type_i>
#endif
      int_image_2d_array;

    /// @var int_image_2d_multisample
    /// @glconstwrap{INT_IMAGE_2D_multisample}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_2D_MULTISAMPLE
      enum_type_c<GL_INT_IMAGE_2D_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      int_image_2d_multisample;

    /// @var int_image_2d_multisample_array
    /// @glconstwrap{INT_IMAGE_2D_multisample_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY
      enum_type_c<GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY>>
#else
      enum_type_i>
#endif
      int_image_2d_multisample_array;

    /// @var unsigned_int_image_1d
    /// @glconstwrap{UNSIGNED_INT_IMAGE_1D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_1D
      enum_type_c<GL_UNSIGNED_INT_IMAGE_1D>>
#else
      enum_type_i>
#endif
      unsigned_int_image_1d;

    /// @var unsigned_int_image_2d
    /// @glconstwrap{UNSIGNED_INT_IMAGE_2D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_2D
      enum_type_c<GL_UNSIGNED_INT_IMAGE_2D>>
#else
      enum_type_i>
#endif
      unsigned_int_image_2d;

    /// @var unsigned_int_image_3d
    /// @glconstwrap{UNSIGNED_INT_IMAGE_3D}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_3D
      enum_type_c<GL_UNSIGNED_INT_IMAGE_3D>>
#else
      enum_type_i>
#endif
      unsigned_int_image_3d;

    /// @var unsigned_int_image_2d_rect
    /// @glconstwrap{UNSIGNED_INT_IMAGE_2D_RECT}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_2D_RECT
      enum_type_c<GL_UNSIGNED_INT_IMAGE_2D_RECT>>
#else
      enum_type_i>
#endif
      unsigned_int_image_2d_rect;

    /// @var unsigned_int_image_cube
    /// @glconstwrap{UNSIGNED_INT_IMAGE_CUBE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_CUBE
      enum_type_c<GL_UNSIGNED_INT_IMAGE_CUBE>>
#else
      enum_type_i>
#endif
      unsigned_int_image_cube;

    /// @var unsigned_int_image_buffer
    /// @glconstwrap{UNSIGNED_INT_IMAGE_BUFFER}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_BUFFER
      enum_type_c<GL_UNSIGNED_INT_IMAGE_BUFFER>>
#else
      enum_type_i>
#endif
      unsigned_int_image_buffer;

    /// @var unsigned_int_image_1d_array
    /// @glconstwrap{UNSIGNED_INT_IMAGE_1D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_1D_ARRAY
      enum_type_c<GL_UNSIGNED_INT_IMAGE_1D_ARRAY>>
#else
      enum_type_i>
#endif
      unsigned_int_image_1d_array;

    /// @var unsigned_int_image_2d_array
    /// @glconstwrap{UNSIGNED_INT_IMAGE_2D_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_2D_ARRAY
      enum_type_c<GL_UNSIGNED_INT_IMAGE_2D_ARRAY>>
#else
      enum_type_i>
#endif
      unsigned_int_image_2d_array;

    /// @var unsigned_int_image_2d_multisample
    /// @glconstwrap{UNSIGNED_INT_IMAGE_2D_MULTISAMPLE}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE
      enum_type_c<GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE>>
#else
      enum_type_i>
#endif
      unsigned_int_image_2d_multisample;

    /// @var unsigned_int_image_2d_multisample_array
    /// @glconstwrap{UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY
      enum_type_c<GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY>>
#else
      enum_type_i>
#endif
      unsigned_int_image_2d_multisample_array;

    /// @var unsigned_int_atomic_counter
    /// @glconstwrap{UNSIGNED_INT_ATOMIC_COUNTER}
    opt_constant<
      mp_list<sl_data_type>,
#ifdef GL_UNSIGNED_INT_ATOMIC_COUNTER
      enum_type_c<GL_UNSIGNED_INT_ATOMIC_COUNTER>>
#else
      enum_type_i>
#endif
      unsigned_int_atomic_counter;

    /// @var points
    /// @glconstwrap{POINTS}
    opt_constant<
      mp_list<primitive_type, transform_feedback_primitive_type, old_primitive_type>,
#ifdef GL_POINTS
      enum_type_c<GL_POINTS>>
#else
      enum_type_i>
#endif
      points;

    /// @var line_strip
    /// @glconstwrap{LINE_STRIP}
    opt_constant<
      mp_list<primitive_type, old_primitive_type>,
#ifdef GL_LINE_STRIP
      enum_type_c<GL_LINE_STRIP>>
#else
      enum_type_i>
#endif
      line_strip;

    /// @var line_loop
    /// @glconstwrap{LINE_LOOP}
    opt_constant<
      mp_list<primitive_type, old_primitive_type>,
#ifdef GL_LINE_LOOP
      enum_type_c<GL_LINE_LOOP>>
#else
      enum_type_i>
#endif
      line_loop;

    /// @var lines
    /// @glconstwrap{LINES}
    opt_constant<
      mp_list<primitive_type, old_primitive_type, transform_feedback_primitive_type>,
#ifdef GL_LINES
      enum_type_c<GL_LINES>>
#else
      enum_type_i>
#endif
      lines;

    /// @var triangle_strip
    /// @glconstwrap{triangle_strip}
    opt_constant<
      mp_list<primitive_type, old_primitive_type>,
#ifdef GL_TRIANGLE_STRIP
      enum_type_c<GL_TRIANGLE_STRIP>>
#else
      enum_type_i>
#endif
      triangle_strip;

    /// @var triangle_fan
    /// @glconstwrap{TRIANGLE_FAN}
    opt_constant<
      mp_list<primitive_type, old_primitive_type>,
#ifdef GL_TRIANGLE_FAN
      enum_type_c<GL_TRIANGLE_FAN>>
#else
      enum_type_i>
#endif
      triangle_fan;

    /// @var triangles
    /// @glconstwrap{TRIANGLES}
    opt_constant<
      mp_list<
        primitive_type,
        old_primitive_type,
        tess_gen_primitive_type,
        transform_feedback_primitive_type>,
#ifdef GL_TRIANGLES
      enum_type_c<GL_TRIANGLES>>
#else
      enum_type_i>
#endif
      triangles;

    /// @var quads
    /// @glconstwrap{QUADS}
    opt_constant<
      mp_list<old_primitive_type, tess_gen_primitive_type>,
#ifdef GL_QUADS
      enum_type_c<GL_QUADS>>
#else
      enum_type_i>
#endif
      quads;

    /// @var quad_strip
    /// @glconstwrap{QUAD_STRIP}
    opt_constant<
      mp_list<old_primitive_type>,
#ifdef GL_QUAD_STRIP
      enum_type_c<GL_QUAD_STRIP>>
#else
      enum_type_i>
#endif
      quad_strip;

    /// @var polygon
    /// @glconstwrap{POLYGON}
    opt_constant<
      mp_list<old_primitive_type>,
#ifdef GL_POLYGON
      enum_type_c<GL_POLYGON>>
#else
      enum_type_i>
#endif
      polygon;

    /// @var lines_adjacency
    /// @glconstwrap{LINES_ADJACENCY}
    opt_constant<
      mp_list<primitive_type>,
#ifdef GL_LINES_ADJACENCY
      enum_type_c<GL_LINES_ADJACENCY>>
#else
      enum_type_i>
#endif
      lines_adjacency;

    /// @var line_strip_adjacency
    /// @glconstwrap{LINE_STRIP_ADJACENCY}
    opt_constant<
      mp_list<primitive_type>,
#ifdef GL_LINE_STRIP_ADJACENCY
      enum_type_c<GL_LINE_STRIP_ADJACENCY>>
#else
      enum_type_i>
#endif
      line_strip_adjacency;

    /// @var triangles_adjacency
    /// @glconstwrap{TRIANGLES_ADJACENCY}
    opt_constant<
      mp_list<primitive_type>,
#ifdef GL_TRIANGLES_ADJACENCY
      enum_type_c<GL_TRIANGLES_ADJACENCY>>
#else
      enum_type_i>
#endif
      triangles_adjacency;

    /// @var triangle_strip_adjacency
    /// @glconstwrap{TRIANGLE_STRIP_ADJACENCY}
    opt_constant<
      mp_list<primitive_type>,
#ifdef GL_TRIANGLE_STRIP_ADJACENCY
      enum_type_c<GL_TRIANGLE_STRIP_ADJACENCY>>
#else
      enum_type_i>
#endif
      triangle_strip_adjacency;

    /// @var patches
    /// @glconstwrap{PATCHES}
    opt_constant<
      mp_list<primitive_type>,
#ifdef GL_PATCHES
      enum_type_c<GL_PATCHES>>
#else
      enum_type_i>
#endif
      patches;

    /// @var isolines
    /// @glconstwrap{ISOLINES}
    opt_constant<
      mp_list<tess_gen_primitive_type>,
#ifdef GL_ISOLINES
      enum_type_c<GL_ISOLINES>>
#else
      enum_type_i>
#endif
      isolines;

    /// @var fractional_even
    /// @glconstwrap{FRACTIONAL_EVEN}
    opt_constant<
      mp_list<tess_gen_primitive_spacing>,
#ifdef GL_FRACTIONAL_EVEN
      enum_type_c<GL_FRACTIONAL_EVEN>>
#else
      enum_type_i>
#endif
      fractional_even;

    /// @var fractional_odd
    /// @glconstwrap{FRACTIONAL_ODD}
    opt_constant<
      mp_list<tess_gen_primitive_spacing>,
#ifdef GL_FRACTIONAL_ODD
      enum_type_c<GL_FRACTIONAL_ODD>>
#else
      enum_type_i>
#endif
      fractional_odd;

    /// @var patch_vertices
    /// @glconstwrap{PATCH_VERTICES}
    opt_constant<
      mp_list<patch_parameter, integer_query>,
#ifdef GL_PATCH_VERTICES
      enum_type_c<GL_PATCH_VERTICES>>
#else
      enum_type_i>
#endif
      patch_vertices;

    /// @var patch_default_outer_level
    /// @glconstwrap{PATCH_DEFAULT_OUTER_LEVEL}
    opt_constant<
      mp_list<patch_parameter, float_query>,
#ifdef GL_PATCH_DEFAULT_OUTER_LEVEL
      enum_type_c<GL_PATCH_DEFAULT_OUTER_LEVEL>>
#else
      enum_type_i>
#endif
      patch_default_outer_level;

    /// @var patch_default_inner_level
    /// @glconstwrap{PATCH_DEFAULT_INNER_LEVEL}
    opt_constant<
      mp_list<patch_parameter, float_query>,
#ifdef GL_PATCH_DEFAULT_INNER_LEVEL
      enum_type_c<GL_PATCH_DEFAULT_INNER_LEVEL>>
#else
      enum_type_i>
#endif
      patch_default_inner_level;

    /// @var cw
    /// @glconstwrap{CW}
    opt_constant<
      mp_list<face_orientation>,
#ifdef GL_CW
      enum_type_c<GL_CW>>
#else
      enum_type_i>
#endif
      cw;

    /// @var ccw
    /// @glconstwrap{CCW}
    opt_constant<
      mp_list<face_orientation>,
#ifdef GL_CCW
      enum_type_c<GL_CCW>>
#else
      enum_type_i>
#endif
      ccw;

    /// @var first_vertex_convention
    /// @glconstwrap{FIRST_VERTEX_CONVENTION}
    opt_constant<
      mp_list<provoke_mode>,
#ifdef GL_FIRST_VERTEX_CONVENTION
      enum_type_c<GL_FIRST_VERTEX_CONVENTION>>
#else
      enum_type_i>
#endif
      first_vertex_convention;

    /// @var last_vertex_convention
    /// @glconstwrap{LAST_VERTEX_CONVENTION}
    opt_constant<
      mp_list<provoke_mode>,
#ifdef GL_LAST_VERTEX_CONVENTION
      enum_type_c<GL_LAST_VERTEX_CONVENTION>>
#else
      enum_type_i>
#endif
      last_vertex_convention;

    /// @var query_wait
    /// @glconstwrap{QUERY_WAIT}
    opt_constant<
      mp_list<conditional_render_mode>,
#ifdef GL_QUERY_WAIT
      enum_type_c<GL_QUERY_WAIT>>
#else
      enum_type_i>
#endif
      query_wait;

    /// @var query_no_wait
    /// @glconstwrap{QUERY_NO_WAIT}
    opt_constant<
      mp_list<conditional_render_mode>,
#ifdef GL_QUERY_NO_WAIT
      enum_type_c<GL_QUERY_NO_WAIT>>
#else
      enum_type_i>
#endif
      query_no_wait;

    /// @var query_by_region_wait
    /// @glconstwrap{QUERY_BY_REGION_WAIT}
    opt_constant<
      mp_list<conditional_render_mode>,
#ifdef GL_QUERY_BY_REGION_WAIT
      enum_type_c<GL_QUERY_BY_REGION_WAIT>>
#else
      enum_type_i>
#endif
      query_by_region_wait;

    /// @var query_by_region_no_wait
    /// @glconstwrap{QUERY_BY_REGION_NO_WAIT}
    opt_constant<
      mp_list<conditional_render_mode>,
#ifdef GL_QUERY_BY_REGION_NO_WAIT
      enum_type_c<GL_QUERY_BY_REGION_NO_WAIT>>
#else
      enum_type_i>
#endif
      query_by_region_no_wait;

    /// @var query_wait_inverted
    /// @glconstwrap{QUERY_WAIT_INVERTED}
    opt_constant<
      mp_list<conditional_render_mode>,
#ifdef GL_QUERY_WAIT_INVERTED
      enum_type_c<GL_QUERY_WAIT_INVERTED>>
#else
      enum_type_i>
#endif
      query_wait_inverted;

    /// @var query_no_wait_inverted
    /// @glconstwrap{QUERY_NO_WAIT_INVERTED}
    opt_constant<
      mp_list<conditional_render_mode>,
#ifdef GL_QUERY_NO_WAIT_INVERTED
      enum_type_c<GL_QUERY_NO_WAIT_INVERTED>>
#else
      enum_type_i>
#endif
      query_no_wait_inverted;

    /// @var query_by_region_wait_inverted
    /// @glconstwrap{QUERY_BY_REGION_WAIT_INVERTED}
    opt_constant<
      mp_list<conditional_render_mode>,
#ifdef GL_QUERY_BY_REGION_WAIT_INVERTED
      enum_type_c<GL_QUERY_BY_REGION_WAIT_INVERTED>>
#else
      enum_type_i>
#endif
      query_by_region_wait_inverted;

    /// @var query_by_region_no_wait_inverted
    /// @glconstwrap{QUERY_BY_REGION_NO_WAIT_INVERTED}
    opt_constant<
      mp_list<conditional_render_mode>,
#ifdef GL_QUERY_BY_REGION_NO_WAIT_INVERTED
      enum_type_c<GL_QUERY_BY_REGION_NO_WAIT_INVERTED>>
#else
      enum_type_i>
#endif
      query_by_region_no_wait_inverted;

    /// @var point_size_min
    /// @glconstwrap{POINT_SIZE_MIN}
    opt_constant<
      mp_list<point_parameter>,
#ifdef GL_POINT_SIZE_MIN
      enum_type_c<GL_POINT_SIZE_MIN>>
#else
      enum_type_i>
#endif
      point_size_min;

    /// @var point_size_max
    /// @glconstwrap{POINT_SIZE_MAX}
    opt_constant<
      mp_list<point_parameter>,
#ifdef GL_POINT_SIZE_MAX
      enum_type_c<GL_POINT_SIZE_MAX>>
#else
      enum_type_i>
#endif
      point_size_max;

    /// @var point_fade_threshold_size
    /// @glconstwrap{POINT_FADE_THRESHOLD_SIZE}
    opt_constant<
      mp_list<point_parameter, float_query>,
#ifdef GL_POINT_FADE_THRESHOLD_SIZE
      enum_type_c<GL_POINT_FADE_THRESHOLD_SIZE>>
#else
      enum_type_i>
#endif
      point_fade_threshold_size;

    /// @var point_sprite_coord_origin
    /// @glconstwrap{POINT_SPRITE_COORD_ORIGIN}
    opt_constant<
      mp_list<point_parameter, integer_query>,
#ifdef GL_POINT_SPRITE_COORD_ORIGIN
      enum_type_c<GL_POINT_SPRITE_COORD_ORIGIN>,
#else
      enum_type_i,
#endif
      oglplus::point_sprite_coord_origin>
      point_sprite_coord_origin;

    /// @var lower_left
    /// @glconstwrap{LOWER_LEFT}
    opt_constant<
      mp_list<oglplus::point_sprite_coord_origin>,
#ifdef GL_LOWER_LEFT
      enum_type_c<GL_LOWER_LEFT>>
#else
      enum_type_i>
#endif
      lower_left;

    /// @var upper_left
    /// @glconstwrap{UPPER_LEFT}
    opt_constant<
      mp_list<oglplus::point_sprite_coord_origin>,
#ifdef GL_UPPER_LEFT
      enum_type_c<GL_UPPER_LEFT>>
#else
      enum_type_i>
#endif
      upper_left;

    /// @var point
    /// @glconstwrap{POINT}
    opt_constant<
      mp_list<oglplus::polygon_mode>,
#ifdef GL_POINT
      enum_type_c<GL_POINT>>
#else
      enum_type_i>
#endif
      point;

    /// @var line
    /// @glconstwrap{LINE}
    opt_constant<
      mp_list<oglplus::polygon_mode>,
#ifdef GL_LINE
      enum_type_c<GL_LINE>>
#else
      enum_type_i>
#endif
      line;

    /// @var fill
    /// @glconstwrap{FILL}
    opt_constant<
      mp_list<oglplus::polygon_mode>,
#ifdef GL_FILL
      enum_type_c<GL_FILL>>
#else
      enum_type_i>
#endif
      fill;

    /// @var fill_rectangle_nv
    /// @glconstwrap{FILL_RECTANGLE_NV}
    opt_constant<
      mp_list<oglplus::polygon_mode>,
#ifdef GL_FILL_RECTANGLE_NV
      enum_type_c<GL_FILL_RECTANGLE_NV>>
#else
      enum_type_i>
#endif
      fill_rectangle_nv;

    /// @var keep
    /// @glconstwrap{KEEP}
    opt_constant<
      mp_list<stencil_operation>,
#ifdef GL_KEEP
      enum_type_c<GL_KEEP>>
#else
      enum_type_i>
#endif
      keep;

    /// @var replace
    /// @glconstwrap{REPLACE}
    opt_constant<
      mp_list<stencil_operation>,
#ifdef GL_REPLACE
      enum_type_c<GL_REPLACE>>
#else
      enum_type_i>
#endif
      replace;

    /// @var incr
    /// @glconstwrap{INCR}
    opt_constant<
      mp_list<stencil_operation>,
#ifdef GL_INCR
      enum_type_c<GL_INCR>>
#else
      enum_type_i>
#endif
      incr;

    /// @var decr
    /// @glconstwrap{DECR}
    opt_constant<
      mp_list<stencil_operation>,
#ifdef GL_DECR
      enum_type_c<GL_DECR>>
#else
      enum_type_i>
#endif
      decr;

    /// @var invert
    /// @glconstwrap{INVERT}
    opt_constant<
      mp_list<stencil_operation, logic_operation, oglplus::path_fill_mode_nv>,
#ifdef GL_INVERT
      enum_type_c<GL_INVERT>>
#else
      enum_type_i>
#endif
      invert;

    /// @var incr_wrap
    /// @glconstwrap{INCR_WRAP}
    opt_constant<
      mp_list<stencil_operation>,
#ifdef GL_INCR_WRAP
      enum_type_c<GL_INCR_WRAP>>
#else
      enum_type_i>
#endif
      incr_wrap;

    /// @var decr_wrap
    /// @glconstwrap{DECR_WRAP}
    opt_constant<
      mp_list<stencil_operation>,
#ifdef GL_DECR_WRAP
      enum_type_c<GL_DECR_WRAP>>
#else
      enum_type_i>
#endif
      decr_wrap;

    /// @var clear
    /// @glconstwrap{CLEAR}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_CLEAR
      enum_type_c<GL_CLEAR>>
#else
      enum_type_i>
#endif
      clear_;

    /// @var and_
    /// @glconstwrap{AND}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_AND
      enum_type_c<GL_AND>>
#else
      enum_type_i>
#endif
      and_;

    /// @var and_reverse
    /// @glconstwrap{AND_REVERSE}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_AND_REVERSE
      enum_type_c<GL_AND_REVERSE>>
#else
      enum_type_i>
#endif
      and_reverse;

    /// @var copy
    /// @glconstwrap{COPY}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_COPY
      enum_type_c<GL_COPY>>
#else
      enum_type_i>
#endif
      copy;

    /// @var and_inverted
    /// @glconstwrap{AND_INVERTED}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_AND_INVERTED
      enum_type_c<GL_AND_INVERTED>>
#else
      enum_type_i>
#endif
      and_inverted;

    /// @var noop
    /// @glconstwrap{NOOP}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_NOOP
      enum_type_c<GL_NOOP>>
#else
      enum_type_i>
#endif
      noop;

    /// @var xor_
    /// @glconstwrap{XOR}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_XOR
      enum_type_c<GL_XOR>>
#else
      enum_type_i>
#endif
      xor_;

    /// @var or_
    /// @glconstwrap{OR}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_OR
      enum_type_c<GL_OR>>
#else
      enum_type_i>
#endif
      or_;

    /// @var nor
    /// @glconstwrap{NOR}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_NOR
      enum_type_c<GL_NOR>>
#else
      enum_type_i>
#endif
      nor;

    /// @var equiv
    /// @glconstwrap{EQUIV}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_EQUIV
      enum_type_c<GL_EQUIV>>
#else
      enum_type_i>
#endif
      equiv;

    /// @var or_reverse
    /// @glconstwrap{OR_REVERSE}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_OR_REVERSE
      enum_type_c<GL_OR_REVERSE>>
#else
      enum_type_i>
#endif
      or_reverse;

    /// @var copy_inverted
    /// @glconstwrap{COPY_INVERTED}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_COPY_INVERTED
      enum_type_c<GL_COPY_INVERTED>>
#else
      enum_type_i>
#endif
      copy_inverted;

    /// @var or_inverted
    /// @glconstwrap{OR_INVERTED}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_OR_INVERTED
      enum_type_c<GL_OR_INVERTED>>
#else
      enum_type_i>
#endif
      or_inverted;

    /// @var nand
    /// @glconstwrap{NAND}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_NAND
      enum_type_c<GL_NAND>>
#else
      enum_type_i>
#endif
      nand;

    /// @var set
    /// @glconstwrap{SET}
    opt_constant<
      mp_list<logic_operation>,
#ifdef GL_SET
      enum_type_c<GL_SET>>
#else
      enum_type_i>
#endif
      set;

    /// @var func_add
    /// @glconstwrap{FUNC_ADD}
    opt_constant<
      mp_list<blend_equation>,
#ifdef GL_FUNC_ADD
      enum_type_c<GL_FUNC_ADD>>
#else
      enum_type_i>
#endif
      func_add;

    /// @var func_subtract
    /// @glconstwrap{FUNC_SUBTRACT}
    opt_constant<
      mp_list<blend_equation>,
#ifdef GL_FUNC_SUBTRACT
      enum_type_c<GL_FUNC_SUBTRACT>>
#else
      enum_type_i>
#endif
      func_subtract;

    /// @var func_reverse_subtract
    /// @glconstwrap{FUNC_REVERSE_SUBTRACT}
    opt_constant<
      mp_list<blend_equation>,
#ifdef GL_FUNC_REVERSE_SUBTRACT
      enum_type_c<GL_FUNC_REVERSE_SUBTRACT>>
#else
      enum_type_i>
#endif
      func_reverse_subtract;

    /// @var min
    /// @glconstwrap{MIN}
    opt_constant<
      mp_list<blend_equation>,
#ifdef GL_MIN
      enum_type_c<GL_MIN>>
#else
      enum_type_i>
#endif
      min;

    /// @var max
    /// @glconstwrap{MAX}
    opt_constant<
      mp_list<blend_equation>,
#ifdef GL_MAX
      enum_type_c<GL_MAX>>
#else
      enum_type_i>
#endif
      max;

    /// @var multiply_khr
    /// @glconstwrap{MULTIPLY_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_MULTIPLY_KHR
      enum_type_c<GL_MULTIPLY_KHR>>
#else
      enum_type_i>
#endif
      multiply_khr;

    /// @var screen_khr
    /// @glconstwrap{SCREEN_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_SCREEN_KHR
      enum_type_c<GL_SCREEN_KHR>>
#else
      enum_type_i>
#endif
      screen_khr;

    /// @var overlay_khr
    /// @glconstwrap{OVERLAY_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_OVERLAY_KHR
      enum_type_c<GL_OVERLAY_KHR>>
#else
      enum_type_i>
#endif
      overlay_khr;

    /// @var darken_khr
    /// @glconstwrap{DARKEN_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_DARKEN_KHR
      enum_type_c<GL_DARKEN_KHR>>
#else
      enum_type_i>
#endif
      darken_khr;

    /// @var lighten_khr
    /// @glconstwrap{LIGHTEN_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_LIGHTEN_KHR
      enum_type_c<GL_LIGHTEN_KHR>>
#else
      enum_type_i>
#endif
      lighten_khr;

    /// @var colordodge_khr
    /// @glconstwrap{COLORDODGE_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_COLORDODGE_KHR
      enum_type_c<GL_COLORDODGE_KHR>>
#else
      enum_type_i>
#endif
      colordodge_khr;

    /// @var colorburn_khr
    /// @glconstwrap{COLORBURN_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_COLORBURN_KHR
      enum_type_c<GL_COLORBURN_KHR>>
#else
      enum_type_i>
#endif
      colorburn_khr;

    /// @var hardlight_khr
    /// @glconstwrap{HARDLIGHT_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_HARDLIGHT_KHR
      enum_type_c<GL_HARDLIGHT_KHR>>
#else
      enum_type_i>
#endif
      hardlight_khr;

    /// @var softlight_khr
    /// @glconstwrap{SOFTLIGHT_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_SOFTLIGHT_KHR
      enum_type_c<GL_SOFTLIGHT_KHR>>
#else
      enum_type_i>
#endif
      softlight_khr;

    /// @var difference_khr
    /// @glconstwrap{DIFFERENCE_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_DIFFERENCE_KHR
      enum_type_c<GL_DIFFERENCE_KHR>>
#else
      enum_type_i>
#endif
      difference_khr;

    /// @var exclusion_khr
    /// @glconstwrap{EXCLUSION_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_EXCLUSION_KHR
      enum_type_c<GL_EXCLUSION_KHR>>
#else
      enum_type_i>
#endif
      exclusion_khr;

    /// @var hsl_hue_khr
    /// @glconstwrap{HSL_HUE_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_HSL_HUE_KHR
      enum_type_c<GL_HSL_HUE_KHR>>
#else
      enum_type_i>
#endif
      hsl_hue_khr;

    /// @var hsl_saturation_khr
    /// @glconstwrap{HSL_SATURATION_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_HSL_SATURATION_KHR
      enum_type_c<GL_HSL_SATURATION_KHR>>
#else
      enum_type_i>
#endif
      hsl_saturation_khr;

    /// @var hsl_color_khr
    /// @glconstwrap{HSL_COLOR_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_HSL_COLOR_KHR
      enum_type_c<GL_HSL_COLOR_KHR>>
#else
      enum_type_i>
#endif
      hsl_color_khr;

    /// @var hsl_luminosity_khr
    /// @glconstwrap{HSL_LUMINOSITY_KHR}
    opt_constant<
      mp_list<blend_equation_advanced>,
#ifdef GL_HSL_LUMINOSITY_KHR
      enum_type_c<GL_HSL_LUMINOSITY_KHR>>
#else
      enum_type_i>
#endif
      hsl_luminosity_khr;

    /// @var src_color
    /// @glconstwrap{SRC_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_SRC_COLOR
      enum_type_c<GL_SRC_COLOR>>
#else
      enum_type_i>
#endif
      src_color;

    /// @var one_minus_src_color
    /// @glconstwrap{ONE_MINUS_SRC_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_ONE_MINUS_SRC_COLOR
      enum_type_c<GL_ONE_MINUS_SRC_COLOR>>
#else
      enum_type_i>
#endif
      one_minus_src_color;

    /// @var dst_color
    /// @glconstwrap{DST_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_DST_COLOR
      enum_type_c<GL_DST_COLOR>>
#else
      enum_type_i>
#endif
      dst_color;

    /// @var one_minus_dst_color
    /// @glconstwrap{ONE_MINUS_DST_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_ONE_MINUS_DST_COLOR
      enum_type_c<GL_ONE_MINUS_DST_COLOR>>
#else
      enum_type_i>
#endif
      one_minus_dst_color;

    /// @var src_alpha
    /// @glconstwrap{SRC_ALPHA}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_SRC_ALPHA
      enum_type_c<GL_SRC_ALPHA>>
#else
      enum_type_i>
#endif
      src_alpha;

    /// @var one_minus_src_alpha
    /// @glconstwrap{ONE_MINUS_SRC_ALPHA}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_ONE_MINUS_SRC_ALPHA
      enum_type_c<GL_ONE_MINUS_SRC_ALPHA>>
#else
      enum_type_i>
#endif
      one_minus_src_alpha;

    /// @var dst_alpha
    /// @glconstwrap{DST_ALPHA}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_DST_ALPHA
      enum_type_c<GL_DST_ALPHA>>
#else
      enum_type_i>
#endif
      dst_alpha;

    /// @var one_minus_dst_alpha
    /// @glconstwrap{ONE_MINUS_DST_ALPHA}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_ONE_MINUS_DST_ALPHA
      enum_type_c<GL_ONE_MINUS_DST_ALPHA>>
#else
      enum_type_i>
#endif
      one_minus_dst_alpha;

    /// @var constant_color
    /// @glconstwrap{CONSTANT_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_CONSTANT_COLOR
      enum_type_c<GL_CONSTANT_COLOR>>
#else
      enum_type_i>
#endif
      constant_color;

    /// @var one_minus_constant_color
    /// @glconstwrap{ONE_MINUS_CONSTANT_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_ONE_MINUS_CONSTANT_COLOR
      enum_type_c<GL_ONE_MINUS_CONSTANT_COLOR>>
#else
      enum_type_i>
#endif
      one_minus_constant_color;

    /// @var constant_alpha
    /// @glconstwrap{CONSTANT_ALPHA}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_CONSTANT_ALPHA
      enum_type_c<GL_CONSTANT_ALPHA>>
#else
      enum_type_i>
#endif
      constant_alpha;

    /// @var one_minus_constant_alpha
    /// @glconstwrap{ONE_MINUS_CONSTANT_ALPHA}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_ONE_MINUS_CONSTANT_ALPHA
      enum_type_c<GL_ONE_MINUS_CONSTANT_ALPHA>>
#else
      enum_type_i>
#endif
      one_minus_constant_alpha;

    /// @var src_alpha_saturate
    /// @glconstwrap{SRC_ALPHA_SATURATE}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_SRC_ALPHA_SATURATE
      enum_type_c<GL_SRC_ALPHA_SATURATE>>
#else
      enum_type_i>
#endif
      src_alpha_saturate;

    /// @var src1_color
    /// @glconstwrap{SRC1_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_SRC1_COLOR
      enum_type_c<GL_SRC1_COLOR>>
#else
      enum_type_i>
#endif
      src1_color;

    /// @var one_minus_src1_color
    /// @glconstwrap{ONE_MINUS_SRC1_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_ONE_MINUS_SRC1_COLOR
      enum_type_c<GL_ONE_MINUS_SRC1_COLOR>>
#else
      enum_type_i>
#endif
      one_minus_src1_color;

    /// @var src1_alpha
    /// @glconstwrap{SRC1_ALPHA}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_SRC1_ALPHA
      enum_type_c<GL_SRC1_ALPHA>>
#else
      enum_type_i>
#endif
      src1_alpha;

    /// @var one_minus_src1_color
    /// @glconstwrap{ONE_MINUS_SRC1_COLOR}
    opt_constant<
      mp_list<blend_function>,
#ifdef GL_ONE_MINUS_SRC1_ALPHA
      enum_type_c<GL_ONE_MINUS_SRC1_ALPHA>>
#else
      enum_type_i>
#endif
      one_minus_src1_alpha;

    /// @var unsigned_byte_
    /// @glconstwrap{UNSIGNED_BYTE}
    type_constructor_constant<opt_constant<
      mp_list<data_type, pixel_data_type, index_data_type>,
#ifdef GL_UNSIGNED_BYTE
      enum_type_c<GL_UNSIGNED_BYTE>,
#else
      enum_type_i,
#endif
      typename gl_types::ubyte_type>>
      unsigned_byte_;

    /// @var byte_
    /// @glconstwrap{BYTE}
    opt_constant<
      mp_list<data_type, pixel_data_type>,
#ifdef GL_BYTE
      enum_type_c<GL_BYTE>>
#else
      enum_type_i>
#endif
      byte_;

    /// @var unsigned_short_
    /// @glconstwrap{UNSIGNED_SHORT}
    opt_constant<
      mp_list<pixel_data_type, data_type, index_data_type>,
#ifdef GL_UNSIGNED_SHORT
      enum_type_c<GL_UNSIGNED_SHORT>>
#else
      enum_type_i>
#endif
      unsigned_short_;

    /// @var short_
    /// @glconstwrap{SHORT}
    type_constructor_constant<opt_constant<
      mp_list<pixel_data_type, data_type>,
#ifdef GL_SHORT
      enum_type_c<GL_SHORT>,
#else
      enum_type_i,
#endif
      typename gl_types::short_type>>
      short_;

    /// @var half_float_
    /// @glconstwrap{HALF_FLOAT}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_HALF_FLOAT
      enum_type_c<GL_HALF_FLOAT>>
#else
      enum_type_i>
#endif
      half_float_;

    /// @var unsigned_byte_3_3_2
    /// @glconstwrap{UNSIGNED_BYTE_3_3_2}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_BYTE_3_3_2
      enum_type_c<GL_UNSIGNED_BYTE_3_3_2>>
#else
      enum_type_i>
#endif
      unsigned_byte_3_3_2;

    /// @var unsigned_byte_2_3_3_rev
    /// @glconstwrap{UNSIGNED_BYTE_2_3_3_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_BYTE_2_3_3_REV
      enum_type_c<GL_UNSIGNED_BYTE_2_3_3_REV>>
#else
      enum_type_i>
#endif
      unsigned_byte_2_3_3_rev;

    /// @var unsigned_short_5_6_5
    /// @glconstwrap{UNSIGNED_SHORT_5_6_5}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_SHORT_5_6_5
      enum_type_c<GL_UNSIGNED_SHORT_5_6_5>>
#else
      enum_type_i>
#endif
      unsigned_short_5_6_5;

    /// @var unsigned_short_5_6_5_rev
    /// @glconstwrap{UNSIGNED_SHORT_5_6_5_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_SHORT_5_6_5_REV
      enum_type_c<GL_UNSIGNED_SHORT_5_6_5_REV>>
#else
      enum_type_i>
#endif
      unsigned_short_5_6_5_rev;

    /// @var unsigned_short_4_4_4_4
    /// @glconstwrap{UNSIGNED_SHORT_4_4_4_4}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_SHORT_4_4_4_4
      enum_type_c<GL_UNSIGNED_SHORT_4_4_4_4>>
#else
      enum_type_i>
#endif
      unsigned_short_4_4_4_4;

    /// @var unsigned_short_4_4_4_4_rev
    /// @glconstwrap{UNSIGNED_SHORT_4_4_4_4_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_SHORT_4_4_4_4_REV
      enum_type_c<GL_UNSIGNED_SHORT_4_4_4_4_REV>>
#else
      enum_type_i>
#endif
      unsigned_short_4_4_4_4_rev;

    /// @var unsigned_short_5_5_5_1
    /// @glconstwrap{UNSIGNED_SHORT_5_5_5_1}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_SHORT_5_5_5_1
      enum_type_c<GL_UNSIGNED_SHORT_5_5_5_1>>
#else
      enum_type_i>
#endif
      unsigned_short_5_5_5_1;

    /// @var unsigned_short_5_5_5_1_rev
    /// @glconstwrap{UNSIGNED_SHORT_5_5_5_1_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_SHORT_1_5_5_5_REV
      enum_type_c<GL_UNSIGNED_SHORT_1_5_5_5_REV>>
#else
      enum_type_i>
#endif
      unsigned_short_1_5_5_5_rev;

    /// @var unsigned_int_8_8_8_8
    /// @glconstwrap{UNSIGNED_INT_8_8_8_8}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_INT_8_8_8_8
      enum_type_c<GL_UNSIGNED_INT_8_8_8_8>>
#else
      enum_type_i>
#endif
      unsigned_int_8_8_8_8;

    /// @var unsigned_int_8_8_8_8_rev
    /// @glconstwrap{UNSIGNED_INT_8_8_8_8_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_INT_8_8_8_8_REV
      enum_type_c<GL_UNSIGNED_INT_8_8_8_8_REV>>
#else
      enum_type_i>
#endif
      unsigned_int_8_8_8_8_rev;

    /// @var unsigned_int_10_10_10_2
    /// @glconstwrap{UNSIGNED_INT_10_10_10_2}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_INT_10_10_10_2
      enum_type_c<GL_UNSIGNED_INT_10_10_10_2>>
#else
      enum_type_i>
#endif
      unsigned_int_10_10_10_2;

    /// @var unsigned_int_10_10_10_2_rev
    /// @glconstwrap{UNSIGNED_INT_10_10_10_2_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_INT_2_10_10_10_REV
      enum_type_c<GL_UNSIGNED_INT_2_10_10_10_REV>>
#else
      enum_type_i>
#endif
      unsigned_int_2_10_10_10_rev;

    /// @var unsigned_int_24_8
    /// @glconstwrap{UNSIGNED_INT_24_8}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_INT_24_8
      enum_type_c<GL_UNSIGNED_INT_24_8>>
#else
      enum_type_i>
#endif
      unsigned_int_24_8;

    /// @var unsigned_int_10f_11f_11f_rev
    /// @glconstwrap{UNSIGNED_INT_10F_11F_11F_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_INT_10F_11F_11F_REV
      enum_type_c<GL_UNSIGNED_INT_10F_11F_11F_REV>>
#else
      enum_type_i>
#endif
      unsigned_int_10f_11f_11f_rev;

    /// @var unsigned_int_5_9_9_9_rev
    /// @glconstwrap{UNSIGNED_INT_5_9_9_9_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_UNSIGNED_INT_5_9_9_9_REV
      enum_type_c<GL_UNSIGNED_INT_5_9_9_9_REV>>
#else
      enum_type_i>
#endif
      unsigned_int_5_9_9_9_rev;

    /// @var float_32_unsigned_int_24_8_rev
    /// @glconstwrap{FLOAT_32_UNSIGNED_INT_24_8_REV}
    opt_constant<
      mp_list<pixel_data_type>,
#ifdef GL_FLOAT_32_UNSIGNED_INT_24_8_REV
      enum_type_c<GL_FLOAT_32_UNSIGNED_INT_24_8_REV>>
#else
      enum_type_i>
#endif
      float_32_unsigned_int_24_8_rev;

    /// @var stencil_index8
    /// @glconstwrap{STENCIL_INDEX8}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_STENCIL_INDEX
      enum_type_c<GL_STENCIL_INDEX>>
#else
      enum_type_i>
#endif
      stencil_index;

    /// @var bgr
    /// @glconstwrap{BGR}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_BGR
      enum_type_c<GL_BGR>>
#else
      enum_type_i>
#endif
      bgr;

    /// @var bgra
    /// @glconstwrap{BGRA}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_BGRA
      enum_type_c<GL_BGRA>>
#else
      enum_type_i>
#endif
      bgra;

    /// @var red_integer
    /// @glconstwrap{RED_INTEGER}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_RED_INTEGER
      enum_type_c<GL_RED_INTEGER>>
#else
      enum_type_i>
#endif
      red_integer;

    /// @var green_integer
    /// @glconstwrap{GREEN_INTEGER}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_GREEN_INTEGER
      enum_type_c<GL_GREEN_INTEGER>>
#else
      enum_type_i>
#endif
      green_integer;

    /// @var blue_integer
    /// @glconstwrap{BLUE_INTEGER}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_BLUE_INTEGER
      enum_type_c<GL_BLUE_INTEGER>>
#else
      enum_type_i>
#endif
      blue_integer;

    /// @var rg_integer
    /// @glconstwrap{RG_INTEGER}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_RG_INTEGER
      enum_type_c<GL_RG_INTEGER>>
#else
      enum_type_i>
#endif
      rg_integer;

    /// @var rgb_integer
    /// @glconstwrap{RGB_INTEGER}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_RGB_INTEGER
      enum_type_c<GL_RGB_INTEGER>>
#else
      enum_type_i>
#endif
      rgb_integer;

    /// @var rgba_integer
    /// @glconstwrap{RGBA_INTEGER}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_RGBA_INTEGER
      enum_type_c<GL_RGBA_INTEGER>>
#else
      enum_type_i>
#endif
      rgba_integer;

    /// @var bgr_integer
    /// @glconstwrap{BGR_INTEGER}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_BGR_INTEGER
      enum_type_c<GL_BGR_INTEGER>>
#else
      enum_type_i>
#endif
      bgr_integer;

    /// @var bgra_integer
    /// @glconstwrap{BGRA_INTEGER}
    opt_constant<
      mp_list<pixel_format>,
#ifdef GL_BGRA_INTEGER
      enum_type_c<GL_BGRA_INTEGER>>
#else
      enum_type_i>
#endif
      bgra_integer;

    /// @var depth_component
    /// @glconstwrap{DEPTH_COMPONENT}
    opt_constant<
      mp_list<pixel_internal_format, pixel_format>,
#ifdef GL_DEPTH_COMPONENT
      enum_type_c<GL_DEPTH_COMPONENT>>
#else
      enum_type_i>
#endif
      depth_component;

    /// @var depth_stencil
    /// @glconstwrap{DEPTH_STENCIL}
    opt_constant<
      mp_list<pixel_internal_format, pixel_format, framebuffer_buffer>,
#ifdef GL_DEPTH_STENCIL
      enum_type_c<GL_DEPTH_STENCIL>>
#else
      enum_type_i>
#endif
      depth_stencil;

    /// @var depth_component16
    /// @glconstwrap{DEPTH_COMPONENT16}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_DEPTH_COMPONENT16
      enum_type_c<GL_DEPTH_COMPONENT16>>
#else
      enum_type_i>
#endif
      depth_component16;

    /// @var depth_component24
    /// @glconstwrap{DEPTH_COMPONENT24}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_DEPTH_COMPONENT24
      enum_type_c<GL_DEPTH_COMPONENT24>>
#else
      enum_type_i>
#endif
      depth_component24;

    /// @var depth_component32f
    /// @glconstwrap{DEPTH_COMPONENT32F}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_DEPTH_COMPONENT32F
      enum_type_c<GL_DEPTH_COMPONENT32F>>
#else
      enum_type_i>
#endif
      depth_component32f;

    /// @var stencil_index8
    /// @glconstwrap{STENCIL_INDEX8}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_STENCIL_INDEX8
      enum_type_c<GL_STENCIL_INDEX8>>
#else
      enum_type_i>
#endif
      stencil_index8;

    /// @var rg
    /// @glconstwrap{RG}
    opt_constant<
      mp_list<pixel_internal_format, pixel_format>,
#ifdef GL_RG
      enum_type_c<GL_RG>>
#else
      enum_type_i>
#endif
      rg;

    /// @var rgb
    /// @glconstwrap{RGB}
    opt_constant<
      mp_list<pixel_internal_format, pixel_format, path_color_format_nv>,
#ifdef GL_RGB
      enum_type_c<GL_RGB>>
#else
      enum_type_i>
#endif
      rgb;

    /// @var rgba
    /// @glconstwrap{RGBA}
    opt_constant<
      mp_list<pixel_internal_format, pixel_format, path_color_format_nv>,
#ifdef GL_RGBA
      enum_type_c<GL_RGBA>>
#else
      enum_type_i>
#endif
      rgba;

    /// @var r8
    /// @glconstwrap{R8}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R8
      enum_type_c<GL_R8>>
#else
      enum_type_i>
#endif
      r8;

    /// @var r8_snorm
    /// @glconstwrap{R8_SNORM}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R8_SNORM
      enum_type_c<GL_R8_SNORM>>
#else
      enum_type_i>
#endif
      r8_snorm;

    /// @var r16
    /// @glconstwrap{R16}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_R16
      enum_type_c<GL_R16>>
#else
      enum_type_i>
#endif
      r16;

    /// @var r16_snorm
    /// @glconstwrap{R16_SNORM}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R16_SNORM
      enum_type_c<GL_R16_SNORM>>
#else
      enum_type_i>
#endif
      r16_snorm;

    /// @var rg8
    /// @glconstwrap{RG8}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RG8
      enum_type_c<GL_RG8>>
#else
      enum_type_i>
#endif
      rg8;

    /// @var rg8ui
    /// @glconstwrap{RG8UI}
    opt_constant<
      mp_list<image_unit_format>,
#ifdef GL_RG8UI
      enum_type_c<GL_RG8UI>>
#else
      enum_type_i>
#endif
      rg8ui;

    /// @var rg8_snorm
    /// @glconstwrap{RG8_SNORM}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RG8_SNORM
      enum_type_c<GL_RG8_SNORM>>
#else
      enum_type_i>
#endif
      rg8_snorm;

    /// @var rg16
    /// @glconstwrap{RG16}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RG16
      enum_type_c<GL_RG16>>
#else
      enum_type_i>
#endif
      rg16;

    /// @var rg16ui
    /// @glconstwrap{RG16UI}
    opt_constant<
      mp_list<image_unit_format>,
#ifdef GL_RG16UI
      enum_type_c<GL_RG16UI>>
#else
      enum_type_i>
#endif
      rg16ui;

    /// @var rg16_snorm
    /// @glconstwrap{RG16_SNORM}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RG16_SNORM
      enum_type_c<GL_RG16_SNORM>>
#else
      enum_type_i>
#endif
      rg16_snorm;

    /// @var rg32ui
    /// @glconstwrap{RG32UI}
    opt_constant<
      mp_list<image_unit_format>,
#ifdef GL_RG32UI
      enum_type_c<GL_RG32UI>>
#else
      enum_type_i>
#endif
      rg32ui;

    /// @var r3_g3_b2
    /// @glconstwrap{R3_G3_B2}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_R3_G3_B2
      enum_type_c<GL_R3_G3_B2>>
#else
      enum_type_i>
#endif
      r3_g3_b2;

    /// @var rgb4
    /// @glconstwrap{RGB4}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB4
      enum_type_c<GL_RGB4>>
#else
      enum_type_i>
#endif
      rgb4;

    /// @var rgb5
    /// @glconstwrap{RGB5}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB5
      enum_type_c<GL_RGB5>>
#else
      enum_type_i>
#endif
      rgb5;

    /// @var rgb8
    /// @glconstwrap{RGB8}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB8
      enum_type_c<GL_RGB8>>
#else
      enum_type_i>
#endif
      rgb8;

    /// @var rgb8_snorm
    /// @glconstwrap{RGB8_SNORM}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB8_SNORM
      enum_type_c<GL_RGB8_SNORM>>
#else
      enum_type_i>
#endif
      rgb8_snorm;

    /// @var rgb10
    /// @glconstwrap{RGB10}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB10
      enum_type_c<GL_RGB10>>
#else
      enum_type_i>
#endif
      rgb10;

    /// @var rgb12
    /// @glconstwrap{RGB12}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB12
      enum_type_c<GL_RGB12>>
#else
      enum_type_i>
#endif
      rgb12;

    /// @var rgb16
    /// @glconstwrap{RGB16}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB16
      enum_type_c<GL_RGB16>>
#else
      enum_type_i>
#endif
      rgb16;

    /// @var rgb16_snorm
    /// @glconstwrap{RGB16_SNORM}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB16_SNORM
      enum_type_c<GL_RGB16_SNORM>>
#else
      enum_type_i>
#endif
      rgb16_snorm;

    /// @var rgba2
    /// @glconstwrap{RGBA2}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGBA2
      enum_type_c<GL_RGBA2>>
#else
      enum_type_i>
#endif
      rgba2;

    /// @var rgba4
    /// @glconstwrap{RGBA4}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGBA4
      enum_type_c<GL_RGBA4>>
#else
      enum_type_i>
#endif
      rgba4;

    /// @var rgb5_a1
    /// @glconstwrap{RGB5_A1}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB5_A1
      enum_type_c<GL_RGB5_A1>>
#else
      enum_type_i>
#endif
      rgb5_a1;

    /// @var rgba8
    /// @glconstwrap{RGBA8}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGBA8
      enum_type_c<GL_RGBA8>>
#else
      enum_type_i>
#endif
      rgba8;

    /// @var rgba8ui
    /// @glconstwrap{RGBA8UI}
    opt_constant<
      mp_list<image_unit_format>,
#ifdef GL_RGBA8
      enum_type_c<GL_RGBA8UI>>
#else
      enum_type_i>
#endif
      rgba8ui;

    /// @var rgba8_snorm
    /// @glconstwrap{RGBA8_SNORM}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RGBA8_SNORM
      enum_type_c<GL_RGBA8_SNORM>>
#else
      enum_type_i>
#endif
      rgba8_snorm;

    /// @var rgb10_a2
    /// @glconstwrap{RGB10_A2}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB10_A2
      enum_type_c<GL_RGB10_A2>>
#else
      enum_type_i>
#endif
      rgb10_a2;

    /// @var rgb10_a2ui
    /// @glconstwrap{RGB10_A2UI}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RGB10_A2UI
      enum_type_c<GL_RGB10_A2UI>>
#else
      enum_type_i>
#endif
      rgb10_a2ui;

    /// @var rgba12
    /// @glconstwrap{RGBA12}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGBA12
      enum_type_c<GL_RGBA12>>
#else
      enum_type_i>
#endif
      rgba12;

    /// @var rgba16
    /// @glconstwrap{RGBA16}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RGBA16
      enum_type_c<GL_RGBA16>>
#else
      enum_type_i>
#endif
      rgba16;

    /// @var rgba16ui
    /// @glconstwrap{RGBA16UI}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RGBA16UI
      enum_type_c<GL_RGBA16UI>>
#else
      enum_type_i>
#endif
      rgba16ui;

    /// @var rgba16_snorm
    /// @glconstwrap{RGBA16_SNORM}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RGBA16_SNORM
      enum_type_c<GL_RGBA16_SNORM>>
#else
      enum_type_i>
#endif
      rgba16_snorm;

    /// @var r16f
    /// @glconstwrap{R16F}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R16F
      enum_type_c<GL_R16F>>
#else
      enum_type_i>
#endif
      r16f;

    /// @var rg16f
    /// @glconstwrap{RG16F}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RG16F
      enum_type_c<GL_RG16F>>
#else
      enum_type_i>
#endif
      rg16f;

    /// @var rgb16f
    /// @glconstwrap{RGB16F}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB16F
      enum_type_c<GL_RGB16F>>
#else
      enum_type_i>
#endif
      rgb16f;

    /// @var rgba16f
    /// @glconstwrap{RGBA16F}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RGBA16F
      enum_type_c<GL_RGBA16F>>
#else
      enum_type_i>
#endif
      rgba16f;

    /// @var r32f
    /// @glconstwrap{R32F}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R32F
      enum_type_c<GL_R32F>>
#else
      enum_type_i>
#endif
      r32f;

    /// @var rg32f
    /// @glconstwrap{RG32F}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RG32F
      enum_type_c<GL_RG32F>>
#else
      enum_type_i>
#endif
      rg32f;

    /// @var rgb32f
    /// @glconstwrap{RGB32F}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB32F
      enum_type_c<GL_RGB32F>>
#else
      enum_type_i>
#endif
      rgb32f;

    /// @var rgba32f
    /// @glconstwrap{RGBA32F}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RGBA32F
      enum_type_c<GL_RGBA32F>>
#else
      enum_type_i>
#endif
      rgba32f;

    /// @var rgba32ui
    /// @glconstwrap{RGBA32UI}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_RGBA32UI
      enum_type_c<GL_RGBA32UI>>
#else
      enum_type_i>
#endif
      rgba32ui;

    /// @var r11f_g11f_b10f
    /// @glconstwrap{R11F_G11F_B10F}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R11F_G11F_B10F
      enum_type_c<GL_R11F_G11F_B10F>>
#else
      enum_type_i>
#endif
      r11f_g11f_b10f;

    /// @var rgb9_e5
    /// @glconstwrap{RGB9_E5}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_RGB9_E5
      enum_type_c<GL_RGB9_E5>>
#else
      enum_type_i>
#endif
      rgb9_e5;

    /// @var r8i
    /// @glconstwrap{R8I}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_R8I
      enum_type_c<GL_R8I>>
#else
      enum_type_i>
#endif
      r8i;

    /// @var r8ui
    /// @glconstwrap{R8UI}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R8UI
      enum_type_c<GL_R8UI>>
#else
      enum_type_i>
#endif
      r8ui;

    /// @var r16i
    /// @glconstwrap{R16I}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_R16I
      enum_type_c<GL_R16I>>
#else
      enum_type_i>
#endif
      r16i;

    /// @var r16ui
    /// @glconstwrap{R16UI}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R16UI
      enum_type_c<GL_R16UI>>
#else
      enum_type_i>
#endif
      r16ui;

    /// @var r32i
    /// @glconstwrap{R32I}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R32I
      enum_type_c<GL_R32I>>
#else
      enum_type_i>
#endif
      r32i;

    /// @var r32ui
    /// @glconstwrap{R32UI}
    opt_constant<
      mp_list<pixel_internal_format, image_unit_format>,
#ifdef GL_R16UI
      enum_type_c<GL_R32UI>>
#else
      enum_type_i>
#endif
      r32ui;

    /// @var srgb
    /// @glconstwrap{SRGB}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_SRGB
      enum_type_c<GL_SRGB>>
#else
      enum_type_i>
#endif
      srgb;

    /// @var srgb8
    /// @glconstwrap{SRGB8}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_SRGB8
      enum_type_c<GL_SRGB8>>
#else
      enum_type_i>
#endif
      srgb8;

    /// @var srgb_alpha
    /// @glconstwrap{SRGB_ALPHA}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_SRGB_ALPHA
      enum_type_c<GL_SRGB_ALPHA>>
#else
      enum_type_i>
#endif
      srgb_alpha;

    /// @var srgb8_alpha8
    /// @glconstwrap{SRGB8_ALPHA8}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_SRGB8_ALPHA8
      enum_type_c<GL_SRGB8_ALPHA8>>
#else
      enum_type_i>
#endif
      srgb8_alpha8;

    /// @var compressed_srgb
    /// @glconstwrap{COMPRESSED_SRGB}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_COMPRESSED_SRGB
      enum_type_c<GL_COMPRESSED_SRGB>>
#else
      enum_type_i>
#endif
      compressed_srgb;

    /// @var compressed_srgb8_etc2
    /// @glconstwrap{COMPRESSED_SRGB8_ETC2}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_COMPRESSED_SRGB8_ETC2
      enum_type_c<GL_COMPRESSED_SRGB8_ETC2>>
#else
      enum_type_i>
#endif
      compressed_srgb8_etc2;

    /// @var compressed_srgb_alpha
    /// @glconstwrap{COMPRESSED_SRGB_ALPHA}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_COMPRESSED_SRGB_ALPHA
      enum_type_c<GL_COMPRESSED_SRGB_ALPHA>>
#else
      enum_type_i>
#endif
      compressed_srgb_alpha;

    /// @var compressed_srgb8_alpha8_etc2_eac
    /// @glconstwrap{COMPRESSED_SRGB8_ALPHA8_ETC2_EAC}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
      enum_type_c<GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC>>
#else
      enum_type_i>
#endif
      compressed_srgb8_alpha8_etc2_eac;

    /// @var compressed_srgb8_punchthrough_alpha1_etc2
    /// @glconstwrap{COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2
      enum_type_c<GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2>>
#else
      enum_type_i>
#endif
      compressed_srgb8_punchthrough_alpha1_etc2;

    /// @var compressed_srgb_alpha_bptc_unorm
    /// @glconstwrap{COMPRESSED_SRGB_ALPHA_BPTC_UNORM}
    opt_constant<
      mp_list<pixel_internal_format>,
#ifdef GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM
      enum_type_c<GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM>>
#else
      enum_type_i>
#endif
      compressed_srgb_alpha_bptc_unorm;

    /// @var pack_swap_bytes
    /// @glconstwrap{PACK_SWAP_BYTES}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_SWAP_BYTES
      enum_type_c<GL_PACK_SWAP_BYTES>,
#else
      enum_type_i,
#endif
      true_false>
      pack_swap_bytes;

    /// @var pack_lsb_first
    /// @glconstwrap{PACK_LSB_FIRST}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_LSB_FIRST
      enum_type_c<GL_PACK_LSB_FIRST>,
#else
      enum_type_i,
#endif
      true_false>
      pack_lsb_first;

    /// @var pack_row_length
    /// @glconstwrap{PACK_ROW_LENGTH}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_ROW_LENGTH
      enum_type_c<GL_PACK_ROW_LENGTH>>
#else
      enum_type_i>
#endif
      pack_row_length;

    /// @var pack_skip_rows
    /// @glconstwrap{PACK_SKIP_ROWS}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_SKIP_ROWS
      enum_type_c<GL_PACK_SKIP_ROWS>>
#else
      enum_type_i>
#endif
      pack_skip_rows;

    /// @var pack_skip_pixels
    /// @glconstwrap{PACK_SKIP_PIXELS}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_SKIP_PIXELS
      enum_type_c<GL_PACK_SKIP_PIXELS>>
#else
      enum_type_i>
#endif
      pack_skip_pixels;

    /// @var pack_alignment
    /// @glconstwrap{PACK_ALIGNMENT}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_ALIGNMENT
      enum_type_c<GL_PACK_ALIGNMENT>>
#else
      enum_type_i>
#endif
      pack_alignment;

    /// @var pack_image_height
    /// @glconstwrap{PACK_IMAGE_HEIGHT}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_IMAGE_HEIGHT
      enum_type_c<GL_PACK_IMAGE_HEIGHT>>
#else
      enum_type_i>
#endif
      pack_image_height;

    /// @var pack_skip_images
    /// @glconstwrap{PACK_SKIP_IMAGES}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_SKIP_IMAGES
      enum_type_c<GL_PACK_SKIP_IMAGES>>
#else
      enum_type_i>
#endif
      pack_skip_images;

    /// @var pack_compressed_block_width
    /// @glconstwrap{PACK_COMPRESSED_BLOCK_WIDTH}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_COMPRESSED_BLOCK_WIDTH
      enum_type_c<GL_PACK_COMPRESSED_BLOCK_WIDTH>>
#else
      enum_type_i>
#endif
      pack_compressed_block_width;

    /// @var pack_compressed_block_height
    /// @glconstwrap{PACK_COMPRESSED_BLOCK_HEIGHT}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_COMPRESSED_BLOCK_HEIGHT
      enum_type_c<GL_PACK_COMPRESSED_BLOCK_HEIGHT>>
#else
      enum_type_i>
#endif
      pack_compressed_block_height;

    /// @var pack_compressed_block_depth
    /// @glconstwrap{PACK_COMPRESSED_BLOCK_DEPTH}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_COMPRESSED_BLOCK_DEPTH
      enum_type_c<GL_PACK_COMPRESSED_BLOCK_DEPTH>>
#else
      enum_type_i>
#endif
      pack_compressed_block_depth;

    /// @var pack_compressed_block_size
    /// @glconstwrap{PACK_COMPRESSED_BLOCK_SIZE}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_PACK_COMPRESSED_BLOCK_SIZE
      enum_type_c<GL_PACK_COMPRESSED_BLOCK_SIZE>>
#else
      enum_type_i>
#endif
      pack_compressed_block_size;

    /// @var unpack_swap_bytes
    /// @glconstwrap{UNPACK_SWAP_BYTES}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_SWAP_BYTES
      enum_type_c<GL_UNPACK_SWAP_BYTES>,
#else
      enum_type_i,
#endif
      true_false>
      unpack_swap_bytes;

    /// @var unpack_lsb_first
    /// @glconstwrap{UNPACK_LSB_FIRST}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_LSB_FIRST
      enum_type_c<GL_UNPACK_LSB_FIRST>,
#else
      enum_type_i,
#endif
      true_false>
      unpack_lsb_first;

    /// @var unpack_row_length
    /// @glconstwrap{UNPACK_ROW_LENGTH}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_ROW_LENGTH
      enum_type_c<GL_UNPACK_ROW_LENGTH>>
#else
      enum_type_i>
#endif
      unpack_row_length;

    /// @var unpack_skip_rows
    /// @glconstwrap{UNPACK_SKIP_ROWS}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_SKIP_ROWS
      enum_type_c<GL_UNPACK_SKIP_ROWS>>
#else
      enum_type_i>
#endif
      unpack_skip_rows;

    /// @var unpack_skip_pixels
    /// @glconstwrap{UNPACK_SKIP_PIXELS}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_SKIP_PIXELS
      enum_type_c<GL_UNPACK_SKIP_PIXELS>>
#else
      enum_type_i>
#endif
      unpack_skip_pixels;

    /// @var unpack_alignment
    /// @glconstwrap{UNPACK_ALIGNMENT}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_ALIGNMENT
      enum_type_c<GL_UNPACK_ALIGNMENT>>
#else
      enum_type_i>
#endif
      unpack_alignment;

    /// @var unpack_image_height
    /// @glconstwrap{UNPACK_IMAGE_HEIGHT}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_IMAGE_HEIGHT
      enum_type_c<GL_UNPACK_IMAGE_HEIGHT>>
#else
      enum_type_i>
#endif
      unpack_image_height;

    /// @var unpack_skip_images
    /// @glconstwrap{UNPACK_SKIP_IMAGES}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_SKIP_IMAGES
      enum_type_c<GL_UNPACK_SKIP_IMAGES>>
#else
      enum_type_i>
#endif
      unpack_skip_images;

    /// @var unpack_compressed_block_width
    /// @glconstwrap{UNPACK_COMPRESSED_BLOCK_WIDTH}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_COMPRESSED_BLOCK_WIDTH
      enum_type_c<GL_UNPACK_COMPRESSED_BLOCK_WIDTH>>
#else
      enum_type_i>
#endif
      unpack_compressed_block_width;

    /// @var unpack_compressed_block_height
    /// @glconstwrap{UNPACK_COMPRESSED_BLOCK_HEIGHT}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_COMPRESSED_BLOCK_HEIGHT
      enum_type_c<GL_UNPACK_COMPRESSED_BLOCK_HEIGHT>>
#else
      enum_type_i>
#endif
      unpack_compressed_block_height;

    /// @var unpack_compressed_block_depth
    /// @glconstwrap{UNPACK_COMPRESSED_BLOCK_DEPTH}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_COMPRESSED_BLOCK_DEPTH
      enum_type_c<GL_UNPACK_COMPRESSED_BLOCK_DEPTH>>
#else
      enum_type_i>
#endif
      unpack_compressed_block_depth;

    /// @var unpack_compressed_block_size
    /// @glconstwrap{UNPACK_COMPRESSED_BLOCK_SIZE}
    opt_constant<
      mp_list<pixel_store_parameter>,
#ifdef GL_UNPACK_COMPRESSED_BLOCK_SIZE
      enum_type_c<GL_UNPACK_COMPRESSED_BLOCK_SIZE>>
#else
      enum_type_i>
#endif
      unpack_compressed_block_size;

    /// @var image_class_4_x_32
    /// @glconstwrap{IMAGE_CLASS_4_X_32}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_4_X_32
      enum_type_c<GL_IMAGE_CLASS_4_X_32>>
#else
      enum_type_i>
#endif
      image_class_4_x_32;

    /// @var image_class_2_x_32
    /// @glconstwrap{IMAGE_CLASS_2_X_32}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_2_X_32
      enum_type_c<GL_IMAGE_CLASS_2_X_32>>
#else
      enum_type_i>
#endif
      image_class_2_x_32;

    /// @var image_class_1_x_32
    /// @glconstwrap{IMAGE_CLASS_1_X_32}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_1_X_32
      enum_type_c<GL_IMAGE_CLASS_1_X_32>>
#else
      enum_type_i>
#endif
      image_class_1_x_32;

    /// @var image_class_4_x_16
    /// @glconstwrap{IMAGE_CLASS_4_X_16}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_4_X_16
      enum_type_c<GL_IMAGE_CLASS_4_X_16>>
#else
      enum_type_i>
#endif
      image_class_4_x_16;

    /// @var image_class_2_x_16
    /// @glconstwrap{IMAGE_CLASS_2_X_16}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_2_X_16
      enum_type_c<GL_IMAGE_CLASS_2_X_16>>
#else
      enum_type_i>
#endif
      image_class_2_x_16;

    /// @var image_class_1_x_16
    /// @glconstwrap{IMAGE_CLASS_1_X_16}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_1_X_16
      enum_type_c<GL_IMAGE_CLASS_1_X_16>>
#else
      enum_type_i>
#endif
      image_class_1_x_16;

    /// @var image_class_4_x_8
    /// @glconstwrap{IMAGE_CLASS_4_X_8}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_4_X_8
      enum_type_c<GL_IMAGE_CLASS_4_X_8>>
#else
      enum_type_i>
#endif
      image_class_4_x_8;

    /// @var image_class_2_x_8
    /// @glconstwrap{IMAGE_CLASS_2_X_8}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_2_X_8
      enum_type_c<GL_IMAGE_CLASS_2_X_8>>
#else
      enum_type_i>
#endif
      image_class_2_x_8;

    /// @var image_class_1_x_8
    /// @glconstwrap{IMAGE_CLASS_1_X_8}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_1_X_8
      enum_type_c<GL_IMAGE_CLASS_1_X_8>>
#else
      enum_type_i>
#endif
      image_class_1_x_8;

    /// @var image_class_11_11_10
    /// @glconstwrap{IMAGE_CLASS_11_11_10}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_11_11_10
      enum_type_c<GL_IMAGE_CLASS_11_11_10>>
#else
      enum_type_i>
#endif
      image_class_11_11_10;

    /// @var image_class_10_10_10_2
    /// @glconstwrap{IMAGE_CLASS_10_10_10_2}
    opt_constant<
      mp_list<oglplus::image_compatibility_class>,
#ifdef GL_IMAGE_CLASS_10_10_10_2
      enum_type_c<GL_IMAGE_CLASS_10_10_10_2>>
#else
      enum_type_i>
#endif
      image_class_10_10_10_2;

    /// @var view_class_128_bits
    /// @glconstwrap{VIEW_CLASS_128_BITS}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_128_BITS
      enum_type_c<GL_VIEW_CLASS_128_BITS>>
#else
      enum_type_i>
#endif
      view_class_128_bits;

    /// @var view_class_96_bits
    /// @glconstwrap{VIEW_CLASS_96_BITS}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_96_BITS
      enum_type_c<GL_VIEW_CLASS_96_BITS>>
#else
      enum_type_i>
#endif
      view_class_96_bits;

    /// @var view_class_64_bits
    /// @glconstwrap{VIEW_CLASS_64_BITS}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_64_BITS
      enum_type_c<GL_VIEW_CLASS_64_BITS>>
#else
      enum_type_i>
#endif
      view_class_64_bits;

    /// @var view_class_48_bits
    /// @glconstwrap{VIEW_CLASS_48_BITS}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_48_BITS
      enum_type_c<GL_VIEW_CLASS_48_BITS>>
#else
      enum_type_i>
#endif
      view_class_48_bits;

    /// @var view_class_32_bits
    /// @glconstwrap{VIEW_CLASS_32_BITS}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_32_BITS
      enum_type_c<GL_VIEW_CLASS_32_BITS>>
#else
      enum_type_i>
#endif
      view_class_32_bits;

    /// @var view_class_24_bits
    /// @glconstwrap{VIEW_CLASS_24_BITS}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_24_BITS
      enum_type_c<GL_VIEW_CLASS_24_BITS>>
#else
      enum_type_i>
#endif
      view_class_24_bits;

    /// @var view_class_16_bits
    /// @glconstwrap{VIEW_CLASS_16_BITS}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_16_BITS
      enum_type_c<GL_VIEW_CLASS_16_BITS>>
#else
      enum_type_i>
#endif
      view_class_16_bits;

    /// @var view_class_8_bits
    /// @glconstwrap{VIEW_CLASS_8_BITS}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_8_BITS
      enum_type_c<GL_VIEW_CLASS_8_BITS>>
#else
      enum_type_i>
#endif
      view_class_8_bits;

    /// @var view_class_s3tc_dxt1_rgb
    /// @glconstwrap{VIEW_CLASS_S3TC_DXT1_RGB}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_S3TC_DXT1_RGB
      enum_type_c<GL_VIEW_CLASS_S3TC_DXT1_RGB>>
#else
      enum_type_i>
#endif
      view_class_s3tc_dxt1_rgb;

    /// @var view_class_s3tc_dxt1_rgba
    /// @glconstwrap{VIEW_CLASS_S3TC_DXT1_RGBA}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_S3TC_DXT1_RGBA
      enum_type_c<GL_VIEW_CLASS_S3TC_DXT1_RGBA>>
#else
      enum_type_i>
#endif
      view_class_s3tc_dxt1_rgba;

    /// @var view_class_s3tc_dxt3_rgba
    /// @glconstwrap{VIEW_CLASS_S3TC_DXT3_RGBA}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_S3TC_DXT3_RGBA
      enum_type_c<GL_VIEW_CLASS_S3TC_DXT3_RGBA>>
#else
      enum_type_i>
#endif
      view_class_s3tc_dxt3_rgba;

    /// @var view_class_s3tc_dxt5_rgba
    /// @glconstwrap{VIEW_CLASS_S3TC_DXT5_RGBA}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_S3TC_DXT5_RGBA
      enum_type_c<GL_VIEW_CLASS_S3TC_DXT5_RGBA>>
#else
      enum_type_i>
#endif
      view_class_s3tc_dxt5_rgba;

    /// @var view_class_rgtc1_red
    /// @glconstwrap{VIEW_CLASS_RGTC1_RED}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_RGTC1_RED
      enum_type_c<GL_VIEW_CLASS_RGTC1_RED>>
#else
      enum_type_i>
#endif
      view_class_rgtc1_red;

    /// @var view_class_rgtc2_rg
    /// @glconstwrap{VIEW_CLASS_RGTC2_RG}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_RGTC2_RG
      enum_type_c<GL_VIEW_CLASS_RGTC2_RG>>
#else
      enum_type_i>
#endif
      view_class_rgtc2_rg;

    /// @var view_class_bptc_unorm
    /// @glconstwrap{VIEW_CLASS_BPTC_UNORM}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_BPTC_UNORM
      enum_type_c<GL_VIEW_CLASS_BPTC_UNORM>>
#else
      enum_type_i>
#endif
      view_class_bptc_unorm;

    /// @var view_class_bptc_float
    /// @glconstwrap{VIEW_CLASS_BPTC_FLOAT}
    opt_constant<
      mp_list<oglplus::view_compatibility_class>,
#ifdef GL_VIEW_CLASS_BPTC_FLOAT
      enum_type_c<GL_VIEW_CLASS_BPTC_FLOAT>>
#else
      enum_type_i>
#endif
      view_class_bptc_float;

    /// @var num_sample_counts
    /// @glconstwrap{NUM_SAMPLE_COUNTS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_NUM_SAMPLE_COUNTS
      enum_type_c<GL_NUM_SAMPLE_COUNTS>>
#else
      enum_type_i>
#endif
      num_sample_counts;

    /// @var samples
    /// @glconstwrap{SAMPLES}
    opt_constant<
      mp_list<internal_format_parameter, integer_query>,
#ifdef GL_SAMPLES
      enum_type_c<GL_SAMPLES>>
#else
      enum_type_i>
#endif
      samples;

    /// @var internalformat_supported
    /// @glconstwrap{INTERNALFORMAT_SUPPORTED}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_SUPPORTED
      enum_type_c<GL_INTERNALFORMAT_SUPPORTED>>
#else
      enum_type_i>
#endif
      internalformat_supported;

    /// @var internalformat_preferred
    /// @glconstwrap{INTERNALFORMAT_PREFERRED}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_PREFERRED
      enum_type_c<GL_INTERNALFORMAT_PREFERRED>>
#else
      enum_type_i>
#endif
      internalformat_preferred;

    /// @var internalformat_red_size
    /// @glconstwrap{INTERNALFORMAT_RED_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_RED_SIZE
      enum_type_c<GL_INTERNALFORMAT_RED_SIZE>>
#else
      enum_type_i>
#endif
      internalformat_red_size;

    /// @var internalformat_green_size
    /// @glconstwrap{INTERNALFORMAT_GREEN_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_GREEN_SIZE
      enum_type_c<GL_INTERNALFORMAT_GREEN_SIZE>>
#else
      enum_type_i>
#endif
      internalformat_green_size;

    /// @var internalformat_blue_size
    /// @glconstwrap{INTERNALFORMAT_BLUE_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_BLUE_SIZE
      enum_type_c<GL_INTERNALFORMAT_BLUE_SIZE>>
#else
      enum_type_i>
#endif
      internalformat_blue_size;

    /// @var internalformat_alpha_size
    /// @glconstwrap{INTERNALFORMAT_ALPHA_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_ALPHA_SIZE
      enum_type_c<GL_INTERNALFORMAT_ALPHA_SIZE>>
#else
      enum_type_i>
#endif
      internalformat_alpha_size;

    /// @var internalformat_depth_size
    /// @glconstwrap{INTERNALFORMAT_DEPTH_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_DEPTH_SIZE
      enum_type_c<GL_INTERNALFORMAT_DEPTH_SIZE>>
#else
      enum_type_i>
#endif
      internalformat_depth_size;

    /// @var internalformat_stencil_size
    /// @glconstwrap{INTERNALFORMAT_STENCIL_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_STENCIL_SIZE
      enum_type_c<GL_INTERNALFORMAT_STENCIL_SIZE>>
#else
      enum_type_i>
#endif
      internalformat_stencil_size;

    /// @var internalformat_shared_size
    /// @glconstwrap{INTERNALFORMAT_SHARED_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_SHARED_SIZE
      enum_type_c<GL_INTERNALFORMAT_SHARED_SIZE>>
#else
      enum_type_i>
#endif
      internalformat_shared_size;

    /// @var internalformat_red_type
    /// @glconstwrap{INTERNALFORMAT_RED_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_RED_TYPE
      enum_type_c<GL_INTERNALFORMAT_RED_TYPE>>
#else
      enum_type_i>
#endif
      internalformat_red_type;

    /// @var internalformat_green_type
    /// @glconstwrap{INTERNALFORMAT_GREEN_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_GREEN_TYPE
      enum_type_c<GL_INTERNALFORMAT_GREEN_TYPE>>
#else
      enum_type_i>
#endif
      internalformat_green_type;

    /// @var internalformat_blue_type
    /// @glconstwrap{INTERNALFORMAT_BLUE_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_BLUE_TYPE
      enum_type_c<GL_INTERNALFORMAT_BLUE_TYPE>>
#else
      enum_type_i>
#endif
      internalformat_blue_type;

    /// @var internalformat_alpha_type
    /// @glconstwrap{INTERNALFORMAT_ALPHA_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_ALPHA_TYPE
      enum_type_c<GL_INTERNALFORMAT_ALPHA_TYPE>>
#else
      enum_type_i>
#endif
      internalformat_alpha_type;

    /// @var internalformat_depth_type
    /// @glconstwrap{INTERNALFORMAT_DEPTH_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_DEPTH_TYPE
      enum_type_c<GL_INTERNALFORMAT_DEPTH_TYPE>>
#else
      enum_type_i>
#endif
      internalformat_depth_type;

    /// @var internalformat_stencil_type
    /// @glconstwrap{INTERNALFORMAT_STENCIL_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_INTERNALFORMAT_STENCIL_TYPE
      enum_type_c<GL_INTERNALFORMAT_STENCIL_TYPE>>
#else
      enum_type_i>
#endif
      internalformat_stencil_type;

    /// @var max_width
    /// @glconstwrap{MAX_WIDTH}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_MAX_WIDTH
      enum_type_c<GL_MAX_WIDTH>>
#else
      enum_type_i>
#endif
      max_width;

    /// @var max_height
    /// @glconstwrap{MAX_HEIGHT}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_MAX_HEIGHT
      enum_type_c<GL_MAX_HEIGHT>>
#else
      enum_type_i>
#endif
      max_height;

    /// @var max_depth
    /// @glconstwrap{MAX_DEPTH}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_MAX_DEPTH
      enum_type_c<GL_MAX_DEPTH>>
#else
      enum_type_i>
#endif
      max_depth;

    /// @var max_layers
    /// @glconstwrap{MAX_LAYERS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_MAX_LAYERS
      enum_type_c<GL_MAX_LAYERS>>
#else
      enum_type_i>
#endif
      max_layers;

    /// @var max_combined_dimensions
    /// @glconstwrap{MAX_COMBINED_DIMENSIONS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_MAX_COMBINED_DIMENSIONS
      enum_type_c<GL_MAX_COMBINED_DIMENSIONS>>
#else
      enum_type_i>
#endif
      max_combined_dimensions;

    /// @var color_components
    /// @glconstwrap{COLOR_COMPONENTS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_COLOR_COMPONENTS
      enum_type_c<GL_COLOR_COMPONENTS>>
#else
      enum_type_i>
#endif
      color_components;

    /// @var depth_components
    /// @glconstwrap{DEPTH_COMPONENTS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_DEPTH_COMPONENTS
      enum_type_c<GL_DEPTH_COMPONENTS>>
#else
      enum_type_i>
#endif
      depth_components;

    /// @var stencil_components
    /// @glconstwrap{STENCIL_COMPONENTS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_STENCIL_COMPONENTS
      enum_type_c<GL_STENCIL_COMPONENTS>>
#else
      enum_type_i>
#endif
      stencil_components;

    /// @var color_renderable
    /// @glconstwrap{COLOR_RENDERABLE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_COLOR_RENDERABLE
      enum_type_c<GL_COLOR_RENDERABLE>>
#else
      enum_type_i>
#endif
      color_renderable;

    /// @var depth_renderable
    /// @glconstwrap{DEPTH_RENDERABLE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_DEPTH_RENDERABLE
      enum_type_c<GL_DEPTH_RENDERABLE>>
#else
      enum_type_i>
#endif
      depth_renderable;

    /// @var stencil_renderable
    /// @glconstwrap{STENCIL_RENDERABLE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_STENCIL_RENDERABLE
      enum_type_c<GL_STENCIL_RENDERABLE>>
#else
      enum_type_i>
#endif
      stencil_renderable;

    /// @var framebuffer_renderable
    /// @glconstwrap{FRAMEBUFFER_RENDERABLE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_FRAMEBUFFER_RENDERABLE
      enum_type_c<GL_FRAMEBUFFER_RENDERABLE>>
#else
      enum_type_i>
#endif
      framebuffer_renderable;

    /// @var framebuffer_renderable_layered
    /// @glconstwrap{FRAMEBUFFER_RENDERABLE_LAYERED}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_FRAMEBUFFER_RENDERABLE_LAYERED
      enum_type_c<GL_FRAMEBUFFER_RENDERABLE_LAYERED>>
#else
      enum_type_i>
#endif
      framebuffer_renderable_layered;

    /// @var framebuffer_buffer
    /// @glconstwrap{FRAMEBUFFER_BUFFER}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_FRAMEBUFFER_BLEND
      enum_type_c<GL_FRAMEBUFFER_BLEND>>
#else
      enum_type_i>
#endif
      framebuffer_blend;

    /// @var read_pixels
    /// @glconstwrap{READ_PIXELS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_READ_PIXELS
      enum_type_c<GL_READ_PIXELS>>
#else
      enum_type_i>
#endif
      read_pixels;

    /// @var read_pixels_format
    /// @glconstwrap{READ_PIXELS_FORMAT}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_READ_PIXELS_FORMAT
      enum_type_c<GL_READ_PIXELS_FORMAT>>
#else
      enum_type_i>
#endif
      read_pixels_format;

    /// @var read_pixels_type
    /// @glconstwrap{READ_PIXELS_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_READ_PIXELS_TYPE
      enum_type_c<GL_READ_PIXELS_TYPE>>
#else
      enum_type_i>
#endif
      read_pixels_type;

    /// @var texture_image_format
    /// @glconstwrap{TEXTURE_IMAGE_FORMAT}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_IMAGE_FORMAT
      enum_type_c<GL_TEXTURE_IMAGE_FORMAT>>
#else
      enum_type_i>
#endif
      texture_image_format;

    /// @var texture_image_type
    /// @glconstwrap{TEXTURE_IMAGE_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_IMAGE_TYPE
      enum_type_c<GL_TEXTURE_IMAGE_TYPE>>
#else
      enum_type_i>
#endif
      texture_image_type;

    /// @var texture_image_format
    /// @glconstwrap{TEXTURE_IMAGE_FORMAT}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_GET_TEXTURE_IMAGE_FORMAT
      enum_type_c<GL_GET_TEXTURE_IMAGE_FORMAT>>
#else
      enum_type_i>
#endif
      get_texture_image_format;

    /// @var get_texture_image_type
    /// @glconstwrap{GET_TEXTURE_IMAGE_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_GET_TEXTURE_IMAGE_TYPE
      enum_type_c<GL_GET_TEXTURE_IMAGE_TYPE>>
#else
      enum_type_i>
#endif
      get_texture_image_type;

    /// @var mipmap
    /// @glconstwrap{MIPMAP}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_MIPMAP
      enum_type_c<GL_MIPMAP>>
#else
      enum_type_i>
#endif
      mipmap;

    /// @var generate_mipmap
    /// @glconstwrap{GENERATE_MIPMAP}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_GENERATE_MIPMAP
      enum_type_c<GL_GENERATE_MIPMAP>>
#else
      enum_type_i>
#endif
      generate_mipmap;

    /// @var auto_generate_mipmap
    /// @glconstwrap{AUTO_GENERATE_MIPMAP}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_AUTO_GENERATE_MIPMAP
      enum_type_c<GL_AUTO_GENERATE_MIPMAP>>
#else
      enum_type_i>
#endif
      auto_generate_mipmap;

    /// @var color_encoding
    /// @glconstwrap{COLOR_ENCODING}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_COLOR_ENCODING
      enum_type_c<GL_COLOR_ENCODING>>
#else
      enum_type_i>
#endif
      color_encoding;

    /// @var srgb_read
    /// @glconstwrap{SRGB_READ}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SRGB_READ
      enum_type_c<GL_SRGB_READ>>
#else
      enum_type_i>
#endif
      srgb_read;

    /// @var srgb_write
    /// @glconstwrap{SRGB_WRITE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SRGB_WRITE
      enum_type_c<GL_SRGB_WRITE>>
#else
      enum_type_i>
#endif
      srgb_write;

    /// @var filter
    /// @glconstwrap{FILTER}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_FILTER
      enum_type_c<GL_FILTER>>
#else
      enum_type_i>
#endif
      filter;

    /// @var vertex_texture
    /// @glconstwrap{VERTEX_TEXTURE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_VERTEX_TEXTURE
      enum_type_c<GL_VERTEX_TEXTURE>>
#else
      enum_type_i>
#endif
      vertex_texture;

    /// @var tess_control_texture
    /// @glconstwrap{TESS_CONTROL_TEXTURE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TESS_CONTROL_TEXTURE
      enum_type_c<GL_TESS_CONTROL_TEXTURE>>
#else
      enum_type_i>
#endif
      tess_control_texture;

    /// @var tess_evaluation_texture
    /// @glconstwrap{TESS_EVALUATION_TEXTURE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TESS_EVALUATION_TEXTURE
      enum_type_c<GL_TESS_EVALUATION_TEXTURE>>
#else
      enum_type_i>
#endif
      tess_evaluation_texture;

    /// @var geometry_texture
    /// @glconstwrap{GEOMETRY_TEXTURE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_GEOMETRY_TEXTURE
      enum_type_c<GL_GEOMETRY_TEXTURE>>
#else
      enum_type_i>
#endif
      geometry_texture;

    /// @var fragment_texture
    /// @glconstwrap{FRAGMENT_TEXTURE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_FRAGMENT_TEXTURE
      enum_type_c<GL_FRAGMENT_TEXTURE>>
#else
      enum_type_i>
#endif
      fragment_texture;

    /// @var compute_texture
    /// @glconstwrap{COMPUTE_TEXTURE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_COMPUTE_TEXTURE
      enum_type_c<GL_COMPUTE_TEXTURE>>
#else
      enum_type_i>
#endif
      compute_texture;

    /// @var texture_shadow
    /// @glconstwrap{TEXTURE_SHADOW}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_SHADOW
      enum_type_c<GL_TEXTURE_SHADOW>>
#else
      enum_type_i>
#endif
      texture_shadow;

    /// @var texture_gather
    /// @glconstwrap{TEXTURE_GATHER}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_GATHER
      enum_type_c<GL_TEXTURE_GATHER>>
#else
      enum_type_i>
#endif
      texture_gather;

    /// @var texture_gather_shadow
    /// @glconstwrap{TEXTURE_GATHER_SHADOW}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_GATHER_SHADOW
      enum_type_c<GL_TEXTURE_GATHER_SHADOW>>
#else
      enum_type_i>
#endif
      texture_gather_shadow;

    /// @var shader_image_load
    /// @glconstwrap{SHADER_IMAGE_LOAD}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SHADER_IMAGE_LOAD
      enum_type_c<GL_SHADER_IMAGE_LOAD>>
#else
      enum_type_i>
#endif
      shader_image_load;

    /// @var shader_image_store
    /// @glconstwrap{SHADER_IMAGE_STORE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SHADER_IMAGE_STORE
      enum_type_c<GL_SHADER_IMAGE_STORE>>
#else
      enum_type_i>
#endif
      shader_image_store;

    /// @var shader_image_atomic
    /// @glconstwrap{SHADER_IMAGE_ATOMIC}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SHADER_IMAGE_ATOMIC
      enum_type_c<GL_SHADER_IMAGE_ATOMIC>>
#else
      enum_type_i>
#endif
      shader_image_atomic;

    /// @var image_texel_size
    /// @glconstwrap{IMAGE_TEXEL_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_IMAGE_TEXEL_SIZE
      enum_type_c<GL_IMAGE_TEXEL_SIZE>>
#else
      enum_type_i>
#endif
      image_texel_size;

    /// @var image_compatibility_class
    /// @glconstwrap{IMAGE_COMPATIBILITY_CLASS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_IMAGE_COMPATIBILITY_CLASS
      enum_type_c<GL_IMAGE_COMPATIBILITY_CLASS>>
#else
      enum_type_i>
#endif
      image_compatibility_class;

    /// @var image_pixel_format
    /// @glconstwrap{IMAGE_PIXEL_FORMAT}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_IMAGE_PIXEL_FORMAT
      enum_type_c<GL_IMAGE_PIXEL_FORMAT>>
#else
      enum_type_i>
#endif
      image_pixel_format;

    /// @var image_pixel_type
    /// @glconstwrap{IMAGE_PIXEL_TYPE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_IMAGE_PIXEL_TYPE
      enum_type_c<GL_IMAGE_PIXEL_TYPE>>
#else
      enum_type_i>
#endif
      image_pixel_type;

    /// @var simultaneous_texture_and_depth_test
    /// @glconstwrap{SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST
      enum_type_c<GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST>>
#else
      enum_type_i>
#endif
      simultaneous_texture_and_depth_test;

    /// @var simultaneous_texture_and_stencil_test
    /// @glconstwrap{SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST
      enum_type_c<GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST>>
#else
      enum_type_i>
#endif
      simultaneous_texture_and_stencil_test;

    /// @var simultaneous_texture_and_depth_write
    /// @glconstwrap{SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE
      enum_type_c<GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE>>
#else
      enum_type_i>
#endif
      simultaneous_texture_and_depth_write;

    /// @var simultaneous_texture_and_stencil_write
    /// @glconstwrap{SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE
      enum_type_c<GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE>>
#else
      enum_type_i>
#endif
      simultaneous_texture_and_stencil_write;

    /// @var texture_compressed
    /// @glconstwrap{TEXTURE_COMPRESSED}
    opt_constant<
      mp_list<internal_format_parameter, texture_level_parameter>,
#ifdef GL_TEXTURE_COMPRESSED
      enum_type_c<GL_TEXTURE_COMPRESSED>,
#else
      enum_type_i,
#endif
      true_false>
      texture_compressed;

    /// @var texture_compressed_image_size
    /// @glconstwrap{TEXTURE_COMPRESSED_IMAGE_SIZE}
    opt_constant<
      mp_list<texture_level_parameter>,
#ifdef GL_TEXTURE_COMPRESSED_IMAGE_SIZE
      enum_type_c<GL_TEXTURE_COMPRESSED_IMAGE_SIZE>>
#else
      enum_type_i>
#endif
      texture_compressed_image_size;

    /// @var texture_compressed_block_width
    /// @glconstwrap{TEXTURE_COMPRESSED_BLOCK_WIDTH}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_WIDTH
      enum_type_c<GL_TEXTURE_COMPRESSED_BLOCK_WIDTH>>
#else
      enum_type_i>
#endif
      texture_compressed_block_width;

    /// @var texture_compressed_block_height
    /// @glconstwrap{TEXTURE_COMPRESSED_BLOCK_HEIGHT}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT
      enum_type_c<GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT>>
#else
      enum_type_i>
#endif
      texture_compressed_block_height;

    /// @var texture_compressed_block_size
    /// @glconstwrap{TEXTURE_COMPRESSED_BLOCK_SIZE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_SIZE
      enum_type_c<GL_TEXTURE_COMPRESSED_BLOCK_SIZE>>
#else
      enum_type_i>
#endif
      texture_compressed_block_size;

    /// @var clear_buffer
    /// @glconstwrap{CLEAR_BUFFER}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_CLEAR_BUFFER
      enum_type_c<GL_CLEAR_BUFFER>>
#else
      enum_type_i>
#endif
      clear_buffer;

    /// @var clear_texture
    /// @glconstwrap{CLEAR_TEXTURE}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_CLEAR_TEXTURE
      enum_type_c<GL_CLEAR_TEXTURE>>
#else
      enum_type_i>
#endif
      clear_texture;

    /// @var texture_view
    /// @glconstwrap{TEXTURE_VIEW}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_TEXTURE_VIEW
      enum_type_c<GL_TEXTURE_VIEW>>
#else
      enum_type_i>
#endif
      texture_view;

    /// @var view_compatibility_class
    /// @glconstwrap{VIEW_COMPATIBILITY_CLASS}
    opt_constant<
      mp_list<internal_format_parameter>,
#ifdef GL_VIEW_COMPATIBILITY_CLASS
      enum_type_c<GL_VIEW_COMPATIBILITY_CLASS>>
#else
      enum_type_i>
#endif
      view_compatibility_class;

    /// @var sample_position
    /// @glconstwrap{SAMPLE_POSITION}
    opt_constant<
      mp_list<sample_parameter>,
#ifdef GL_SAMPLE_POSITION
      enum_type_c<GL_SAMPLE_POSITION>>
#else
      enum_type_i>
#endif
      sample_position;

    /// @var projection
    /// @glconstwrap{PROJECTION}
    opt_constant<
      mp_list<matrix_mode>,
#ifdef GL_PROJECTION
      enum_type_c<GL_PROJECTION>>
#else
      enum_type_i>
#endif
      projection;

    /// @var modelview
    /// @glconstwrap{MODELVIEW}
    opt_constant<
      mp_list<matrix_mode>,
#ifdef GL_MODELVIEW
      enum_type_c<GL_MODELVIEW>>
#else
      enum_type_i>
#endif
      modelview;

    /// @var debug_severity_high
    /// @glconstwrap{DEBUG_SEVERITY_HIGH}
    opt_constant<
      mp_list<debug_output_severity>,
#ifdef GL_DEBUG_SEVERITY_HIGH
      enum_type_c<GL_DEBUG_SEVERITY_HIGH>>
#elif defined(GL_DEBUG_SEVERITY_HIGH_KHR)
      enum_type_c<GL_DEBUG_SEVERITY_HIGH_KHR>>
#else
      enum_type_i>
#endif
      debug_severity_high;

    /// @var debug_severity_medium
    /// @glconstwrap{DEBUG_SEVERITY_MEDIUM}
    opt_constant<
      mp_list<debug_output_severity>,
#ifdef GL_DEBUG_SEVERITY_MEDIUM
      enum_type_c<GL_DEBUG_SEVERITY_MEDIUM>>
#elif defined(GL_DEBUG_SEVERITY_MEDIUM_KHR)
      enum_type_c<GL_DEBUG_SEVERITY_MEDIUM_KHR>>
#else
      enum_type_i>
#endif
      debug_severity_medium;

    /// @var debug_severity_low
    /// @glconstwrap{DEBUG_SEVERITY_LOW}
    opt_constant<
      mp_list<debug_output_severity>,
#ifdef GL_DEBUG_SEVERITY_LOW
      enum_type_c<GL_DEBUG_SEVERITY_LOW>>
#elif defined(GL_DEBUG_SEVERITY_LOW_KHR)
      enum_type_c<GL_DEBUG_SEVERITY_LOW_KHR>>
#else
      enum_type_i>
#endif
      debug_severity_low;

    /// @var debug_severity_notification
    /// @glconstwrap{DEBUG_SEVERITY_NOTIFICATION}
    opt_constant<
      mp_list<debug_output_severity>,
#ifdef GL_DEBUG_SEVERITY_NOTIFICATION
      enum_type_c<GL_DEBUG_SEVERITY_NOTIFICATION>>
#elif defined(GL_DEBUG_SEVERITY_NOTIFICATION_KHR)
      enum_type_c<GL_DEBUG_SEVERITY_NOTIFICATION_KHR>>
#else
      enum_type_i>
#endif
      debug_severity_notification;

    /// @var debug_source_api
    /// @glconstwrap{DEBUG_SOURCE_API}
    opt_constant<
      mp_list<debug_output_source>,
#ifdef GL_DEBUG_SOURCE_API
      enum_type_c<GL_DEBUG_SOURCE_API>>
#elif defined(GL_DEBUG_SOURCE_API_KHR)
      enum_type_c<GL_DEBUG_SOURCE_API_KHR>>
#else
      enum_type_i>
#endif
      debug_source_api;

    /// @var debug_source_window_system
    /// @glconstwrap{DEBUG_SOURCE_WINDOW_SYSTEM}
    opt_constant<
      mp_list<debug_output_source>,
#ifdef GL_DEBUG_SOURCE_WINDOW_SYSTEM
      enum_type_c<GL_DEBUG_SOURCE_WINDOW_SYSTEM>>
#elif defined(GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR)
      enum_type_c<GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR>>
#else
      enum_type_i>
#endif
      debug_source_window_system;

    /// @var debug_source_shader_compiler
    /// @glconstwrap{DEBUG_SOURCE_SHADER_COMPILER}
    opt_constant<
      mp_list<debug_output_source>,
#ifdef GL_DEBUG_SOURCE_SHADER_COMPILER
      enum_type_c<GL_DEBUG_SOURCE_SHADER_COMPILER>>
#elif defined(GL_DEBUG_SOURCE_SHADER_COMPILER_KHR)
      enum_type_c<GL_DEBUG_SOURCE_SHADER_COMPILER_KHR>>
#else
      enum_type_i>
#endif
      debug_source_shader_compiler;

    /// @var debug_source_third_party
    /// @glconstwrap{DEBUG_SOURCE_THIRD_PARTY}
    opt_constant<
      mp_list<debug_output_source>,
#ifdef GL_DEBUG_SOURCE_THIRD_PARTY
      enum_type_c<GL_DEBUG_SOURCE_THIRD_PARTY>>
#elif defined(GL_DEBUG_SOURCE_THIRD_PARTY_KHR)
      enum_type_c<GL_DEBUG_SOURCE_THIRD_PARTY_KHR>>
#else
      enum_type_i>
#endif
      debug_source_third_party;

    /// @var debug_source_application
    /// @glconstwrap{DEBUG_SOURCE_APPLICATION}
    opt_constant<
      mp_list<debug_output_source>,
#ifdef GL_DEBUG_SOURCE_APPLICATION
      enum_type_c<GL_DEBUG_SOURCE_APPLICATION>>
#elif defined(GL_DEBUG_SOURCE_APPLICATION_KHR)
      enum_type_c<GL_DEBUG_SOURCE_APPLICATION_KHR>>
#else
      enum_type_i>
#endif
      debug_source_application;

    /// @var debug_source_other
    /// @glconstwrap{DEBUG_SOURCE_OTHER}
    opt_constant<
      mp_list<debug_output_source>,
#ifdef GL_DEBUG_SOURCE_OTHER
      enum_type_c<GL_DEBUG_SOURCE_OTHER>>
#elif defined(GL_DEBUG_SOURCE_OTHER_KHR)
      enum_type_c<GL_DEBUG_SOURCE_OTHER_KHR>>
#else
      enum_type_i>
#endif
      debug_source_other;

    /// @var debug_type_error
    /// @glconstwrap{DEBUG_TYPE_ERROR}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_ERROR
      enum_type_c<GL_DEBUG_TYPE_ERROR>>
#elif defined(GL_DEBUG_TYPE_ERROR_KHR)
      enum_type_c<GL_DEBUG_TYPE_ERROR_KHR>>
#else
      enum_type_i>
#endif
      debug_type_error;

    /// @var debug_type_deprecated_behavior
    /// @glconstwrap{DEBUG_TYPE_DEPRECATED_BEHAVIOR}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR
      enum_type_c<GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR>>
#elif defined(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR)
      enum_type_c<GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR>>
#else
      enum_type_i>
#endif
      debug_type_deprecated_behavior;

    /// @var debug_type_undefined_behavior
    /// @glconstwrap{DEBUG_TYPE_UNDEFINED_BEHAVIOR}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR
      enum_type_c<GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR>>
#elif defined(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR)
      enum_type_c<GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR>>
#else
      enum_type_i>
#endif
      debug_type_undefined_behavior;

    /// @var debug_type_portability
    /// @glconstwrap{DEBUG_TYPE_PORTABILITY}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_PORTABILITY
      enum_type_c<GL_DEBUG_TYPE_PORTABILITY>>
#elif defined(GL_DEBUG_TYPE_PORTABILITY_KHR)
      enum_type_c<GL_DEBUG_TYPE_PORTABILITY_KHR>>
#else
      enum_type_i>
#endif
      debug_type_portability;

    /// @var debug_type_performance
    /// @glconstwrap{DEBUG_TYPE_PERFORMANCE}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_PERFORMANCE
      enum_type_c<GL_DEBUG_TYPE_PERFORMANCE>>
#elif defined(GL_DEBUG_TYPE_PERFORMANCE_KHR)
      enum_type_c<GL_DEBUG_TYPE_PERFORMANCE_KHR>>
#else
      enum_type_i>
#endif
      debug_type_performance;

    /// @var debug_type_marker
    /// @glconstwrap{DEBUG_TYPE_MARKER}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_MARKER
      enum_type_c<GL_DEBUG_TYPE_MARKER>>
#elif defined(GL_DEBUG_TYPE_MARKER_KHR)
      enum_type_c<GL_DEBUG_TYPE_MARKER_KHR>>
#else
      enum_type_i>
#endif
      debug_type_marker;

    /// @var debug_type_push_group
    /// @glconstwrap{DEBUG_TYPE_PUSH_GROUP}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_PUSH_GROUP
      enum_type_c<GL_DEBUG_TYPE_PUSH_GROUP>>
#elif defined(GL_DEBUG_TYPE_PUSH_GROUP_KHR)
      enum_type_c<GL_DEBUG_TYPE_PUSH_GROUP_KHR>>
#else
      enum_type_i>
#endif
      debug_type_push_group;

    /// @var debug_type_pop_group
    /// @glconstwrap{DEBUG_TYPE_POP_GROUP}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_POP_GROUP
      enum_type_c<GL_DEBUG_TYPE_POP_GROUP>>
#elif defined(GL_DEBUG_TYPE_POP_GROUP_KHR)
      enum_type_c<GL_DEBUG_TYPE_POP_GROUP_KHR>>
#else
      enum_type_i>
#endif
      debug_type_pop_group;

    /// @var debug_type_other
    /// @glconstwrap{DEBUG_TYPE_OTHER}
    opt_constant<
      mp_list<debug_output_type>,
#ifdef GL_DEBUG_TYPE_OTHER
      enum_type_c<GL_DEBUG_TYPE_OTHER>>
#elif defined(GL_DEBUG_TYPE_OTHER_KHR)
      enum_type_c<GL_DEBUG_TYPE_OTHER_KHR>>
#else
      enum_type_i>
#endif
      debug_type_other;

    /// @var line_smooth_hint
    /// @glconstwrap{LINE_SMOOTH_HINT}
    opt_constant<
      mp_list<hint_target>,
#ifdef GL_LINE_SMOOTH_HINT
      enum_type_c<GL_LINE_SMOOTH_HINT>,
#else
      enum_type_i,
#endif
      hint_option>
      line_smooth_hint;

    /// @var polygon_smooth_hint
    /// @glconstwrap{POLYGON_SMOOTH_HINT}
    opt_constant<
      mp_list<hint_target>,
#ifdef GL_POLYGON_SMOOTH_HINT
      enum_type_c<GL_POLYGON_SMOOTH_HINT>,
#else
      enum_type_i,
#endif
      hint_option>
      polygon_smooth_hint;

    /// @var texture_compression_hint
    /// @glconstwrap{TEXTURE_COMPRESSION_HINT}
    opt_constant<
      mp_list<hint_target>,
#ifdef GL_TEXTURE_COMPRESSION_HINT
      enum_type_c<GL_TEXTURE_COMPRESSION_HINT>,
#else
      enum_type_i,
#endif
      hint_option>
      texture_compression_hint;

    /// @var fragment_shader_derivative_hint
    /// @glconstwrap{FRAGMENT_SHADER_DERIVATIVE_HINT}
    opt_constant<
      mp_list<hint_target>,
#ifdef GL_FRAGMENT_SHADER_DERIVATIVE_HINT
      enum_type_c<GL_FRAGMENT_SHADER_DERIVATIVE_HINT>,
#else
      enum_type_i,
#endif
      hint_option>
      fragment_shader_derivative_hint;

    /// @var fastest
    /// @glconstwrap{FASTEST}
    opt_constant<
      mp_list<hint_option>,
#ifdef GL_FASTEST
      enum_type_c<GL_FASTEST>>
#else
      enum_type_i>
#endif
      fastest;

    /// @var nicest
    /// @glconstwrap{NICEST}
    opt_constant<
      mp_list<hint_option>,
#ifdef GL_NICEST
      enum_type_c<GL_NICEST>>
#else
      enum_type_i>
#endif
      nicest;

    /// @var dont_care
    /// @glconstwrap{DONT_CARE}
    opt_constant<
      mp_list<
        debug_output_severity,
        debug_output_source,
        debug_output_type,
        hint_option>,
#ifdef GL_DONT_CARE
      enum_type_c<GL_DONT_CARE>>
#else
      enum_type_i>
#endif
      dont_care;

    /// @var full_support
    /// @glconstwrap{FULL_SUPPORT}
    opt_constant<
      mp_list<support_level>,
#ifdef GL_FULL_SUPPORT
      enum_type_c<GL_FULL_SUPPORT>>
#else
      enum_type_i>
#endif
      full_support;

    /// @var caveat_support
    /// @glconstwrap{CAVEAT_SUPPORT}
    opt_constant<
      mp_list<support_level>,
#ifdef GL_CAVEAT_SUPPORT
      enum_type_c<GL_CAVEAT_SUPPORT>>
#else
      enum_type_i>
#endif
      caveat_support;

    /// @var close_path_nv
    /// @glconstwrap{CLOSE_PATH_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_CLOSE_PATH_NV
      ubyte_type_c<GL_CLOSE_PATH_NV>>
#else
      ubyte_type_i>
#endif
      close_path_nv;

    /// @var move_to_nv
    /// @glconstwrap{MOVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_MOVE_TO_NV
      ubyte_type_c<GL_MOVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      move_to_nv;

    /// @var relative_move_to_nv
    /// @glconstwrap{RELATIVE_MOVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_MOVE_TO_NV
      ubyte_type_c<GL_RELATIVE_MOVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_move_to_nv;

    /// @var line_to_nv
    /// @glconstwrap{LINE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_LINE_TO_NV
      ubyte_type_c<GL_LINE_TO_NV>>
#else
      ubyte_type_i>
#endif
      line_to_nv;

    /// @var relative_line_to_nv
    /// @glconstwrap{RELATIVE_LINE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_LINE_TO_NV
      ubyte_type_c<GL_RELATIVE_LINE_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_line_to_nv;

    /// @var horizontal_line_to_nv
    /// @glconstwrap{HORIZONTAL_LINE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_HORIZONTAL_LINE_TO_NV
      ubyte_type_c<GL_HORIZONTAL_LINE_TO_NV>>
#else
      ubyte_type_i>
#endif
      horizontal_line_to_nv;

    /// @var relative_horizontal_line_to_nv
    /// @glconstwrap{RELATIVE_HORIZONTAL_LINE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_HORIZONTAL_LINE_TO_NV
      ubyte_type_c<GL_RELATIVE_HORIZONTAL_LINE_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_horizontal_line_to_nv;

    /// @var vertical_line_to_nv
    /// @glconstwrap{VERTICAL_LINE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_VERTICAL_LINE_TO_NV
      ubyte_type_c<GL_VERTICAL_LINE_TO_NV>>
#else
      ubyte_type_i>
#endif
      vertical_line_to_nv;

    /// @var relative_vertical_line_to_nv
    /// @glconstwrap{RELATIVE_VERTICAL_LINE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_VERTICAL_LINE_TO_NV
      ubyte_type_c<GL_RELATIVE_VERTICAL_LINE_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_vertical_line_to_nv;

    /// @var quadratic_curve_to_nv
    /// @glconstwrap{QUADRATIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_QUADRATIC_CURVE_TO_NV
      ubyte_type_c<GL_QUADRATIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      quadratic_curve_to_nv;

    /// @var relative_quadratic_curve_to_nv
    /// @glconstwrap{RELATIVE_QUADRATIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_QUADRATIC_CURVE_TO_NV
      ubyte_type_c<GL_RELATIVE_QUADRATIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_quadratic_curve_to_nv;

    /// @var cubic_curve_to_nv
    /// @glconstwrap{CUBIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_CUBIC_CURVE_TO_NV
      ubyte_type_c<GL_CUBIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      cubic_curve_to_nv;

    /// @var relative_cubic_curve_to_nv
    /// @glconstwrap{RELATIVE_CUBIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_CUBIC_CURVE_TO_NV
      ubyte_type_c<GL_RELATIVE_CUBIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_cubic_curve_to_nv;

    /// @var smooth_quadratic_curve_to_nv
    /// @glconstwrap{SMOOTH_QUADRATIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_SMOOTH_QUADRATIC_CURVE_TO_NV
      ubyte_type_c<GL_SMOOTH_QUADRATIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      smooth_quadratic_curve_to_nv;

    /// @var relative_smooth_quadratic_curve_to_nv
    /// @glconstwrap{RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV
      ubyte_type_c<GL_RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_smooth_quadratic_curve_to_nv;

    /// @var smooth_cubic_curve_to_nv
    /// @glconstwrap{SMOOTH_CUBIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_SMOOTH_CUBIC_CURVE_TO_NV
      ubyte_type_c<GL_SMOOTH_CUBIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      smooth_cubic_curve_to_nv;

    /// @var relative_smooth_cubic_curve_to_nv
    /// @glconstwrap{RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV
      ubyte_type_c<GL_RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_smooth_cubic_curve_to_nv;

    /// @var small_ccw_arc_to_nv
    /// @glconstwrap{SMALL_CCW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_SMALL_CCW_ARC_TO_NV
      ubyte_type_c<GL_SMALL_CCW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      small_ccw_arc_to_nv;

    /// @var relative_small_ccw_arc_to_nv
    /// @glconstwrap{RELATIVE_SMALL_CCW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_SMALL_CCW_ARC_TO_NV
      ubyte_type_c<GL_RELATIVE_SMALL_CCW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_small_ccw_arc_to_nv;

    /// @var small_cw_arc_to_nv
    /// @glconstwrap{SMALL_CW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_SMALL_CW_ARC_TO_NV
      ubyte_type_c<GL_SMALL_CW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      small_cw_arc_to_nv;

    /// @var relative_small_cw_arc_to_nv
    /// @glconstwrap{RELATIVE_SMALL_CW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_SMALL_CW_ARC_TO_NV
      ubyte_type_c<GL_RELATIVE_SMALL_CW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_small_cw_arc_to_nv;

    /// @var large_ccw_arc_to_nv
    /// @glconstwrap{LARGE_CCW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_LARGE_CCW_ARC_TO_NV
      ubyte_type_c<GL_LARGE_CCW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      large_ccw_arc_to_nv;

    /// @var relative_large_ccw_arc_to_nv
    /// @glconstwrap{RELATIVE_LARGE_CCW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_LARGE_CCW_ARC_TO_NV
      ubyte_type_c<GL_RELATIVE_LARGE_CCW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_large_ccw_arc_to_nv;

    /// @var large_cw_arc_to_nv
    /// @glconstwrap{LARGE_CW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_LARGE_CW_ARC_TO_NV
      ubyte_type_c<GL_LARGE_CW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      large_cw_arc_to_nv;

    /// @var relative_large_ccw_arc_to_nv
    /// @glconstwrap{RELATIVE_LARGE_CCW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_LARGE_CW_ARC_TO_NV
      ubyte_type_c<GL_RELATIVE_LARGE_CW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_large_cw_arc_to_nv;

    /// @var restart_path_nv
    /// @glconstwrap{RESTART_PATH_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RESTART_PATH_NV
      ubyte_type_c<GL_RESTART_PATH_NV>>
#else
      ubyte_type_i>
#endif
      restart_path_nv;

    /// @var dup_first_cubic_curve_to_nv
    /// @glconstwrap{DUP_FIRST_CUBIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_DUP_FIRST_CUBIC_CURVE_TO_NV
      ubyte_type_c<GL_DUP_FIRST_CUBIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      dup_first_cubic_curve_to_nv;

    /// @var dup_last_cubic_curve_to_nv
    /// @glconstwrap{DUP_LAST_CUBIC_CURVE_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_DUP_LAST_CUBIC_CURVE_TO_NV
      ubyte_type_c<GL_DUP_LAST_CUBIC_CURVE_TO_NV>>
#else
      ubyte_type_i>
#endif
      dup_last_cubic_curve_to_nv;

    /// @var rect_nv
    /// @glconstwrap{RECT_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RECT_NV
      ubyte_type_c<GL_RECT_NV>>
#else
      ubyte_type_i>
#endif
      rect_nv;

    /// @var circular_ccw_arc_to_nv
    /// @glconstwrap{CIRCULAR_CCW_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_CIRCULAR_CCW_ARC_TO_NV
      ubyte_type_c<GL_CIRCULAR_CCW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      circular_ccw_arc_to_nv;

    /// @var circular_cw_arc_to_nv
    /// @glconstwrap{circular_cw_arc_to_nv}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_CIRCULAR_CW_ARC_TO_NV
      ubyte_type_c<GL_CIRCULAR_CW_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      circular_cw_arc_to_nv;

    /// @var circular_tangent_arc_to_nv
    /// @glconstwrap{CIRCULAR_TANGENT_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_CIRCULAR_TANGENT_ARC_TO_NV
      ubyte_type_c<GL_CIRCULAR_TANGENT_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      circular_tangent_arc_to_nv;

    /// @var arc_to_nv
    /// @glconstwrap{ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_ARC_TO_NV
      ubyte_type_c<GL_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      arc_to_nv;

    /// @var relative_arc_to_nv
    /// @glconstwrap{RELATIVE_ARC_TO_NV}
    opt_constant<
      mp_list<path_command_nv>,
#ifdef GL_RELATIVE_ARC_TO_NV
      ubyte_type_c<GL_RELATIVE_ARC_TO_NV>>
#else
      ubyte_type_i>
#endif
      relative_arc_to_nv;

    /// @var flat
    /// @glconstwrap{FLAT}
    opt_constant<
      mp_list<path_cap_style_nv>,
#ifdef GL_FLAT
      enum_type_c<GL_FLAT>>
#else
      enum_type_i>
#endif
      flat;

    /// @var square_nv
    /// @glconstwrap{SQUARE_NV}
    opt_constant<
      mp_list<path_cap_style_nv>,
#ifdef GL_SQUARE_NV
      enum_type_c<GL_SQUARE_NV>>
#else
      enum_type_i>
#endif
      square_nv;

    /// @var round_nv
    /// @glconstwrap{ROUND_NV}
    opt_constant<
      mp_list<path_cap_style_nv, oglplus::path_join_style_nv>,
#ifdef GL_ROUND_NV
      enum_type_c<GL_ROUND_NV>>
#else
      enum_type_i>
#endif
      round_nv;

    /// @var triangular_nv
    /// @glconstwrap{TRIANGULAR_NV}
    opt_constant<
      mp_list<path_cap_style_nv>,
#ifdef GL_TRIANGULAR_NV
      enum_type_c<GL_TRIANGULAR_NV>>
#else
      enum_type_i>
#endif
      triangular_nv;

    /// @var luminance
    /// @glconstwrap{LUMINANCE}
    opt_constant<
      mp_list<path_color_format_nv>,
#ifdef GL_LUMINANCE
      enum_type_c<GL_LUMINANCE>>
#else
      enum_type_i>
#endif
      luminance;

    /// @var intensity
    /// @glconstwrap{INTENSITY}
    opt_constant<
      mp_list<path_color_format_nv>,
#ifdef GL_INTENSITY
      enum_type_c<GL_INTENSITY>>
#else
      enum_type_i>
#endif
      intensity;

    /// @var luminance_alpha
    /// @glconstwrap{LUMINANCE_ALPHA}
    opt_constant<
      mp_list<path_color_format_nv>,
#ifdef GL_LUMINANCE_ALPHA
      enum_type_c<GL_LUMINANCE_ALPHA>>
#else
      enum_type_i>
#endif
      luminance_alpha;

    /// @var primary_color_nv
    /// @glconstwrap{PRIMARY_COLOR_NV}
    opt_constant<
      mp_list<path_color_nv>,
#ifdef GL_PRIMARY_COLOR_NV
      enum_type_c<GL_PRIMARY_COLOR_NV>>
#else
      enum_type_i>
#endif
      primary_color_nv;

    /// @var secondary_color_nv
    /// @glconstwrap{SECONDARY_COLOR_NV}
    opt_constant<
      mp_list<path_color_nv>,
#ifdef GL_SECONDARY_COLOR_NV
      enum_type_c<GL_SECONDARY_COLOR_NV>>
#else
      enum_type_i>
#endif
      secondary_color_nv;

    /// @var move_to_resets_nv
    /// @glconstwrap{MOVE_TO_RESETS_NV}
    opt_constant<
      mp_list<oglplus::path_dash_offset_reset_nv>,
#ifdef GL_MOVE_TO_RESETS_NV
      enum_type_c<GL_MOVE_TO_RESETS_NV>>
#else
      enum_type_i>
#endif
      move_to_resets_nv;

    /// @var move_to_continues_nv
    /// @glconstwrap{MOVE_TO_CONTINUES_NV}
    opt_constant<
      mp_list<oglplus::path_dash_offset_reset_nv>,
#ifdef GL_MOVE_TO_CONTINUES_NV
      enum_type_c<GL_MOVE_TO_CONTINUES_NV>>
#else
      enum_type_i>
#endif
      move_to_continues_nv;

    /// @var convex_hull_nv
    /// @glconstwrap{CONVEX_HULL_NV}
    opt_constant<
      mp_list<oglplus::path_stroke_cover_mode_nv, oglplus::path_fill_cover_mode_nv>,
#ifdef GL_CONVEX_HULL_NV
      enum_type_c<GL_CONVEX_HULL_NV>>
#else
      enum_type_i>
#endif
      convex_hull_nv;

    /// @var bounding_box_nv
    /// @glconstwrap{BOUNDING_BOX_NV}
    opt_constant<
      mp_list<oglplus::path_stroke_cover_mode_nv, oglplus::path_fill_cover_mode_nv>,
#ifdef GL_BOUNDING_BOX_NV
      enum_type_c<GL_BOUNDING_BOX_NV>>
#else
      enum_type_i>
#endif
      bounding_box_nv;

    /// @var bounding_box_of_bounding_boxes_nv
    /// @glconstwrap{BOUNDING_BOX_OF_BOUNDING_BOXES_NV}
    opt_constant<
      mp_list<oglplus::path_stroke_cover_mode_nv, oglplus::path_fill_cover_mode_nv>,
#ifdef GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV
      enum_type_c<GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV>>
#else
      enum_type_i>
#endif
      bounding_box_of_bounding_boxes_nv;

    /// @var count_up_nv
    /// @glconstwrap{COUNT_UP_NV}
    opt_constant<
      mp_list<oglplus::path_fill_mode_nv>,
#ifdef GL_COUNT_UP_NV
      enum_type_c<GL_COUNT_UP_NV>>
#else
      enum_type_i>
#endif
      count_up_nv;

    /// @var count_down_nv
    /// @glconstwrap{COUNT_DOWN_NV}
    opt_constant<
      mp_list<oglplus::path_fill_mode_nv>,
#ifdef GL_COUNT_DOWN_NV
      enum_type_c<GL_COUNT_DOWN_NV>>
#else
      enum_type_i>
#endif
      count_down_nv;

    /// @var bevel_nv
    /// @glconstwrap{BEVEL_NV}
    opt_constant<
      mp_list<oglplus::path_join_style_nv>,
#ifdef GL_BEVEL_NV
      enum_type_c<GL_BEVEL_NV>>
#else
      enum_type_i>
#endif
      bevel_nv;

    /// @var miter_revert_nv
    /// @glconstwrap{MITER_REVERT_NV}
    opt_constant<
      mp_list<oglplus::path_join_style_nv>,
#ifdef GL_MITER_REVERT_NV
      enum_type_c<GL_MITER_REVERT_NV>>
#else
      enum_type_i>
#endif
      miter_revert_nv;

    /// @var miter_truncate_nv
    /// @glconstwrap{MITER_TRUNCATE_NV}
    opt_constant<
      mp_list<oglplus::path_join_style_nv>,
#ifdef GL_MITER_TRUNCATE_NV
      enum_type_c<GL_MITER_TRUNCATE_NV>>
#else
      enum_type_i>
#endif
      miter_truncate_nv;

    /// @var bold_bit_nv
    /// @glconstwrap{BOLD_BIT_NV}
    opt_constant<
      mp_list<path_font_style_nv>,
#ifdef GL_BOLD_BIT_NV
      bitfield_type_c<GL_BOLD_BIT_NV>>
#else
      bitfield_type_i>
#endif
      bold_bit_nv;

    /// @var italic_bit_nv
    /// @glconstwrap{ITALIC_BIT_NV}
    opt_constant<
      mp_list<path_font_style_nv>,
#ifdef GL_ITALIC_BIT_NV
      bitfield_type_c<GL_ITALIC_BIT_NV>>
#else
      bitfield_type_i>
#endif
      italic_bit_nv;

    /// @var standard_font_name_nv
    /// @glconstwrap{STANDARD_FONT_NAME_NV}
    opt_constant<
      mp_list<path_font_target_nv>,
#ifdef GL_STANDARD_FONT_NAME_NV
      enum_type_c<GL_STANDARD_FONT_NAME_NV>>
#else
      enum_type_i>
#endif
      standard_font_name_nv;

    /// @var system_font_name_nv
    /// @glconstwrap{SYSTEM_FONT_NAME_NV}
    opt_constant<
      mp_list<path_font_target_nv>,
#ifdef GL_SYSTEM_FONT_NAME_NV
      enum_type_c<GL_SYSTEM_FONT_NAME_NV>>
#else
      enum_type_i>
#endif
      system_font_name_nv;

    /// @var file_name_nv
    /// @glconstwrap{file_name_nv}
    opt_constant<
      mp_list<path_font_target_nv>,
#ifdef GL_FILE_NAME_NV
      enum_type_c<GL_FILE_NAME_NV>>
#else
      enum_type_i>
#endif
      file_name_nv;

    /// @var path_format_svg_nv
    /// @glconstwrap{PATH_FORMAT_SVG_NV}
    opt_constant<
      mp_list<path_format_nv>,
#ifdef GL_PATH_FORMAT_SVG_NV
      enum_type_c<GL_PATH_FORMAT_SVG_NV>>
#else
      enum_type_i>
#endif
      path_format_svg_nv;

    /// @var path_format_ps_nv
    /// @glconstwrap{PATH_FORMAT_PS_NV}
    opt_constant<
      mp_list<path_format_nv>,
#ifdef GL_PATH_FORMAT_PS_NV
      enum_type_c<GL_PATH_FORMAT_PS_NV>>
#else
      enum_type_i>
#endif
      path_format_ps_nv;

    /// @var eye_linear
    /// @glconstwrap{EYE_LINEAR}
    opt_constant<
      mp_list<oglplus::path_gen_mode_nv>,
#ifdef GL_EYE_LINEAR
      enum_type_c<GL_EYE_LINEAR>>
#else
      enum_type_i>
#endif
      eye_linear;

    /// @var object_linear
    /// @glconstwrap{OBJECT_LINEAR}
    opt_constant<
      mp_list<oglplus::path_gen_mode_nv>,
#ifdef GL_OBJECT_LINEAR
      enum_type_c<GL_OBJECT_LINEAR>>
#else
      enum_type_i>
#endif
      object_linear;

    /// @var path_object_bounding_box_nv
    /// @glconstwrap{PATH_OBJECT_BOUNDING_BOX_NV}
    opt_constant<
      mp_list<oglplus::path_gen_mode_nv, path_parameter_nv>,
#ifdef GL_PATH_OBJECT_BOUNDING_BOX_NV
      enum_type_c<GL_PATH_OBJECT_BOUNDING_BOX_NV>>
#else
      enum_type_i>
#endif
      path_object_bounding_box_nv;

    /// @var accum_adjacent_pairs_nv
    /// @glconstwrap{ACCUM_ADJACENT_PAIRS_NV}
    opt_constant<
      mp_list<path_list_mode_nv>,
#ifdef GL_ACCUM_ADJACENT_PAIRS_NV
      enum_type_c<GL_ACCUM_ADJACENT_PAIRS_NV>>
#else
      enum_type_i>
#endif
      accum_adjacent_pairs_nv;

    /// @var adjacent_pairs_nv
    /// @glconstwrap{ADJACENT_PAIRS_NV}
    opt_constant<
      mp_list<path_list_mode_nv>,
#ifdef GL_ADJACENT_PAIRS_NV
      enum_type_c<GL_ADJACENT_PAIRS_NV>>
#else
      enum_type_i>
#endif
      adjacent_pairs_nv;

    /// @var first_to_rest_nv
    /// @glconstwrap{FIRST_TO_REST_NV}
    opt_constant<
      mp_list<path_list_mode_nv>,
#ifdef GL_FIRST_TO_REST_NV
      enum_type_c<GL_FIRST_TO_REST_NV>>
#else
      enum_type_i>
#endif
      first_to_rest_nv;

    /// @var glyph_width_bit_nv
    /// @glconstwrap{GLYPH_WIDTH_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_WIDTH_BIT_NV
      bitfield_type_c<GL_GLYPH_WIDTH_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_width_bit_nv;

    /// @var glyph_height_bit_nv
    /// @glconstwrap{GLYPH_HEIGHT_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_HEIGHT_BIT_NV
      bitfield_type_c<GL_GLYPH_HEIGHT_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_height_bit_nv;

    /// @var glyph_horizontal_bearing_x_bit_nv
    /// @glconstwrap{GLYPH_HORIZONTAL_BEARING_X_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV
      bitfield_type_c<GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_horizontal_bearing_x_bit_nv;

    /// @var glyph_horizontal_bearing_y_bit_nv
    /// @glconstwrap{GLYPH_HORIZONTAL_BEARING_Y_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV
      bitfield_type_c<GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_horizontal_bearing_y_bit_nv;

    /// @var glyph_horizontal_bearing_advance_bit_nv
    /// @glconstwrap{GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV
      bitfield_type_c<GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_horizontal_bearing_advance_bit_nv;

    /// @var glyph_vertical_bearing_x_bit_nv
    /// @glconstwrap{GLYPH_VERTICAL_BEARING_X_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_VERTICAL_BEARING_X_BIT_NV
      bitfield_type_c<GL_GLYPH_VERTICAL_BEARING_X_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_vertical_bearing_x_bit_nv;

    /// @var glyph_vertical_bearing_y_bit_nv
    /// @glconstwrap{GLYPH_VERTICAL_BEARING_Y_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV
      bitfield_type_c<GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_vertical_bearing_y_bit_nv;

    /// @var glyph_vertical_bearing_advance_bit_nv
    /// @glconstwrap{GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV
      bitfield_type_c<GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_vertical_bearing_advance_bit_nv;

    /// @var glyph_has_kerning_bit_nv
    /// @glconstwrap{GLYPH_HAS_KERNING_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_GLYPH_HAS_KERNING_BIT_NV
      bitfield_type_c<GL_GLYPH_HAS_KERNING_BIT_NV>>
#else
      bitfield_type_i>
#endif
      glyph_has_kerning_bit_nv;

    /// @var font_x_max_bounds_bit_nv
    /// @glconstwrap{FONT_X_MAX_BOUNDS_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_X_MIN_BOUNDS_BIT_NV
      bitfield_type_c<GL_FONT_X_MIN_BOUNDS_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_x_min_bounds_bit_nv;

    /// @var font_y_min_bounds_bit_nv
    /// @glconstwrap{FONT_Y_MIN_BOUNDS_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_Y_MIN_BOUNDS_BIT_NV
      bitfield_type_c<GL_FONT_Y_MIN_BOUNDS_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_y_min_bounds_bit_nv;

    /// @var font_x_max_bounds_bit_nv
    /// @glconstwrap{FONT_X_MAX_BOUNDS_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_X_MAX_BOUNDS_BIT_NV
      bitfield_type_c<GL_FONT_X_MAX_BOUNDS_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_x_max_bounds_bit_nv;

    /// @var font_y_max_bounds_bit_nv
    /// @glconstwrap{FONT_Y_MAX_BOUNDS_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_Y_MAX_BOUNDS_BIT_NV
      bitfield_type_c<GL_FONT_Y_MAX_BOUNDS_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_y_max_bounds_bit_nv;

    /// @var font_units_per_em_bit_nv
    /// @glconstwrap{FONT_UNITS_PER_EM_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_UNITS_PER_EM_BIT_NV
      bitfield_type_c<GL_FONT_UNITS_PER_EM_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_units_per_em_bit_nv;

    /// @var font_ascender_bit_nv
    /// @glconstwrap{FONT_ASCENDER_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_ASCENDER_BIT_NV
      bitfield_type_c<GL_FONT_ASCENDER_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_ascender_bit_nv;

    /// @var font_descender_bit_nv
    /// @glconstwrap{FONT_DESCENDER_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_DESCENDER_BIT_NV
      bitfield_type_c<GL_FONT_DESCENDER_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_descender_bit_nv;

    /// @var font_height_bit_nv
    /// @glconstwrap{FONT_HEIGHT_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_HEIGHT_BIT_NV
      bitfield_type_c<GL_FONT_HEIGHT_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_height_bit_nv;

    /// @var font_max_advance_width_bit_nv
    /// @glconstwrap{FONT_MAX_ADVANCE_WIDTH_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_MAX_ADVANCE_WIDTH_BIT_NV
      bitfield_type_c<GL_FONT_MAX_ADVANCE_WIDTH_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_max_advance_width_bit_nv;

    /// @var font_max_advance_height_bit_nv
    /// @glconstwrap{FONT_MAX_ADVANCE_HEIGHT_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_MAX_ADVANCE_HEIGHT_BIT_NV
      bitfield_type_c<GL_FONT_MAX_ADVANCE_HEIGHT_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_max_advance_height_bit_nv;

    /// @var font_underline_position_bit_nv
    /// @glconstwrap{FONT_UNDERLINE_POSITION_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_UNDERLINE_POSITION_BIT_NV
      bitfield_type_c<GL_FONT_UNDERLINE_POSITION_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_underline_position_bit_nv;

    /// @var font_underline_thickness_bit_nv
    /// @glconstwrap{font_underline_thickness_bit_nv}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_UNDERLINE_THICKNESS_BIT_NV
      bitfield_type_c<GL_FONT_UNDERLINE_THICKNESS_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_underline_thickness_bit_nv;

    /// @var font_has_kerning_bit_nv
    /// @glconstwrap{FONT_HAS_KERNING_BIT_NV}
    opt_constant<
      mp_list<path_metric_query_nv>,
#ifdef GL_FONT_HAS_KERNING_BIT_NV
      bitfield_type_c<GL_FONT_HAS_KERNING_BIT_NV>>
#else
      bitfield_type_i>
#endif
      font_has_kerning_bit_nv;

    /// @var skip_missing_glyph_nv
    /// @glconstwrap{SKIP_MISSING_GLYPH_NV}
    opt_constant<
      mp_list<path_missing_glyph_nv>,
#ifdef GL_SKIP_MISSING_GLYPH_NV
      enum_type_c<GL_SKIP_MISSING_GLYPH_NV>>
#else
      enum_type_i>
#endif
      skip_missing_glyph_nv;

    /// @var use_missing_glyph_nv
    /// @glconstwrap{USE_MISSING_GLYPH_NV}
    opt_constant<
      mp_list<path_missing_glyph_nv>,
#ifdef GL_USE_MISSING_GLYPH_NV
      enum_type_c<GL_USE_MISSING_GLYPH_NV>>
#else
      enum_type_i>
#endif
      use_missing_glyph_nv;

    /// @var path_command_count_nv
    /// @glconstwrap{PATH_COMMAND_COUNT_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_COMMAND_COUNT_NV
      enum_type_c<GL_PATH_COMMAND_COUNT_NV>>
#else
      enum_type_i>
#endif
      path_command_count_nv;

    /// @var path_coord_count_nv
    /// @glconstwrap{PATH_COORD_COUNT_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_COORD_COUNT_NV
      enum_type_c<GL_PATH_COORD_COUNT_NV>>
#else
      enum_type_i>
#endif
      path_coord_count_nv;

    /// @var path_computed_length_nv
    /// @glconstwrap{PATH_COMPUTED_LENGTH_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_COMPUTED_LENGTH_NV
      enum_type_c<GL_PATH_COMPUTED_LENGTH_NV>>
#else
      enum_type_i>
#endif
      path_computed_length_nv;

    /// @var path_stroke_width_nv
    /// @glconstwrap{PATH_STROKE_WIDTH_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_STROKE_WIDTH_NV
      enum_type_c<GL_PATH_STROKE_WIDTH_NV>>
#else
      enum_type_i>
#endif
      path_stroke_width_nv;

    /// @var path_initial_end_cap_nv
    /// @glconstwrap{PATH_INITIAL_END_CAP_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_INITIAL_END_CAP_NV
      enum_type_c<GL_PATH_INITIAL_END_CAP_NV>>
#else
      enum_type_i>
#endif
      path_initial_end_cap_nv;

    /// @var path_terminal_end_cap_nv
    /// @glconstwrap{PATH_TERMINAL_END_CAP_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_TERMINAL_END_CAP_NV
      enum_type_c<GL_PATH_TERMINAL_END_CAP_NV>>
#else
      enum_type_i>
#endif
      path_terminal_end_cap_nv;

    /// @var path_join_style_nv
    /// @glconstwrap{PATH_JOIN_STYLE_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_JOIN_STYLE_NV
      enum_type_c<GL_PATH_JOIN_STYLE_NV>>
#else
      enum_type_i>
#endif
      path_join_style_nv;

    /// @var path_miter_limit_nv
    /// @glconstwrap{PATH_MITER_LIMIT_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_MITER_LIMIT_NV
      enum_type_c<GL_PATH_MITER_LIMIT_NV>>
#else
      enum_type_i>
#endif
      path_miter_limit_nv;

    /// @var path_dash_array_count_nv
    /// @glconstwrap{PATH_DASH_ARRAY_COUNT_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_DASH_ARRAY_COUNT_NV
      enum_type_c<GL_PATH_DASH_ARRAY_COUNT_NV>>
#else
      enum_type_i>
#endif
      path_dash_array_count_nv;

    /// @var path_dash_offset_nv
    /// @glconstwrap{PATH_DASH_OFFSET_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_DASH_OFFSET_NV
      enum_type_c<GL_PATH_DASH_OFFSET_NV>>
#else
      enum_type_i>
#endif
      path_dash_offset_nv;

    /// @var path_dash_offset_reset_nv
    /// @glconstwrap{PATH_DASH_OFFSET_RESET_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_DASH_OFFSET_RESET_NV
      enum_type_c<GL_PATH_DASH_OFFSET_RESET_NV>>
#else
      enum_type_i>
#endif
      path_dash_offset_reset_nv;

    /// @var path_client_length_nv
    /// @glconstwrap{PATH_CLIENT_LENGTH_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_CLIENT_LENGTH_NV
      enum_type_c<GL_PATH_CLIENT_LENGTH_NV>>
#else
      enum_type_i>
#endif
      path_client_length_nv;

    /// @var path_initial_dash_cap_nv
    /// @glconstwrap{PATH_INITIAL_DASH_CAP_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_INITIAL_DASH_CAP_NV
      enum_type_c<GL_PATH_INITIAL_DASH_CAP_NV>>
#else
      enum_type_i>
#endif
      path_initial_dash_cap_nv;

    /// @var path_terminal_dash_cap_nv
    /// @glconstwrap{PATH_TERMINAL_DASH_CAP_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_TERMINAL_DASH_CAP_NV
      enum_type_c<GL_PATH_TERMINAL_DASH_CAP_NV>>
#else
      enum_type_i>
#endif
      path_terminal_dash_cap_nv;

    /// @var path_fill_mode_nv
    /// @glconstwrap{PATH_FILL_MODE_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_FILL_MODE_NV
      enum_type_c<GL_PATH_FILL_MODE_NV>>
#else
      enum_type_i>
#endif
      path_fill_mode_nv;

    /// @var path_fill_mask_nv
    /// @glconstwrap{PATH_FILL_MASK_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_FILL_MASK_NV
      enum_type_c<GL_PATH_FILL_MASK_NV>>
#else
      enum_type_i>
#endif
      path_fill_mask_nv;

    /// @var path_fill_cover_mode_nv
    /// @glconstwrap{PATH_FILL_COVER_MODE_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_FILL_COVER_MODE_NV
      enum_type_c<GL_PATH_FILL_COVER_MODE_NV>>
#else
      enum_type_i>
#endif
      path_fill_cover_mode_nv;

    /// @var path_stroke_cover_mode_nv
    /// @glconstwrap{PATH_STROKE_COVER_MODE_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_STROKE_COVER_MODE_NV
      enum_type_c<GL_PATH_STROKE_COVER_MODE_NV>>
#else
      enum_type_i>
#endif
      path_stroke_cover_mode_nv;

    /// @var path_stroke_mask_nv
    /// @glconstwrap{PATH_STROKE_MASK_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_STROKE_MASK_NV
      enum_type_c<GL_PATH_STROKE_MASK_NV>>
#else
      enum_type_i>
#endif
      path_stroke_mask_nv;

    /// @var path_stroke_bound_nv
    /// @glconstwrap{PATH_STROKE_BOUND_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_STROKE_BOUND_NV
      enum_type_c<GL_PATH_STROKE_BOUND_NV>>
#else
      enum_type_i>
#endif
      path_stroke_bound_nv;

    /// @var path_fill_bounding_box_nv
    /// @glconstwrap{PATH_FILL_BOUNDING_BOX_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_FILL_BOUNDING_BOX_NV
      enum_type_c<GL_PATH_FILL_BOUNDING_BOX_NV>>
#else
      enum_type_i>
#endif
      path_fill_bounding_box_nv;

    /// @var path_stroke_bounding_box_nv
    /// @glconstwrap{PATH_STROKE_BOUNDING_BOX_NV}
    opt_constant<
      mp_list<path_parameter_nv>,
#ifdef GL_PATH_STROKE_BOUNDING_BOX_NV
      enum_type_c<GL_PATH_STROKE_BOUNDING_BOX_NV>>
#else
      enum_type_i>
#endif
      path_stroke_bounding_box_nv;

    /// @var translate_x_nv
    /// @glconstwrap{TRANSLATE_X_NV}
    opt_constant<
      mp_list<path_transform_type_nv>,
#ifdef GL_TRANSLATE_X_NV
      enum_type_c<GL_TRANSLATE_X_NV>>
#else
      enum_type_i>
#endif
      translate_x_nv;

    /// @var translate_y_nv
    /// @glconstwrap{TRANSLATE_Y_NV}
    opt_constant<
      mp_list<path_transform_type_nv>,
#ifdef GL_TRANSLATE_Y_NV
      enum_type_c<GL_TRANSLATE_Y_NV>>
#else
      enum_type_i>
#endif
      translate_y_nv;

    /// @var translate_2d_nv
    /// @glconstwrap{TRANSLATE_2D_NV}
    opt_constant<
      mp_list<path_transform_type_nv>,
#ifdef GL_TRANSLATE_2D_NV
      enum_type_c<GL_TRANSLATE_2D_NV>>
#else
      enum_type_i>
#endif
      translate_2d_nv;

    /// @var translate_3d_nv
    /// @glconstwrap{TRANSLATE_3D_NV}
    opt_constant<
      mp_list<path_transform_type_nv>,
#ifdef GL_TRANSLATE_3D_NV
      enum_type_c<GL_TRANSLATE_3D_NV>>
#else
      enum_type_i>
#endif
      translate_3d_nv;

    /// @var affine_2d_nv
    /// @glconstwrap{AFFINE_2D_NV}
    opt_constant<
      mp_list<path_transform_type_nv>,
#ifdef GL_AFFINE_2D_NV
      enum_type_c<GL_AFFINE_2D_NV>>
#else
      enum_type_i>
#endif
      affine_2d_nv;

    /// @var affine_3d_nv
    /// @glconstwrap{AFFINE_3D_NV}
    opt_constant<
      mp_list<path_transform_type_nv>,
#ifdef GL_AFFINE_3D_NV
      enum_type_c<GL_AFFINE_3D_NV>>
#else
      enum_type_i>
#endif
      affine_3d_nv;

    /// @var transpose_affine_2d_nv
    /// @glconstwrap{TRANSPOSE_AFFINE_2D_NV}
    opt_constant<
      mp_list<path_transform_type_nv>,
#ifdef GL_TRANSPOSE_AFFINE_2D_NV
      enum_type_c<GL_TRANSPOSE_AFFINE_2D_NV>>
#else
      enum_type_i>
#endif
      transpose_affine_2d_nv;

    /// @var transpose_affine_3d_nv
    /// @glconstwrap{TRANSPOSE_AFFINE_3D_NV}
    opt_constant<
      mp_list<path_transform_type_nv>,
#ifdef GL_TRANSPOSE_AFFINE_3D_NV
      enum_type_c<GL_TRANSPOSE_AFFINE_3D_NV>>
#else
      enum_type_i>
#endif
      transpose_affine_3d_nv;

    /// @var utf8_nv
    /// @glconstwrap{UTF8_NV}
    opt_constant<
      mp_list<path_text_encoding_nv>,
#ifdef GL_UTF8_NV
      enum_type_c<GL_UTF8_NV>>
#else
      enum_type_i>
#endif
      utf8_nv;

    /// @var utf16_nv
    /// @glconstwrap{UTF16_NV}
    opt_constant<
      mp_list<path_text_encoding_nv>,
#ifdef GL_UTF16_NV
      enum_type_c<GL_UTF16_NV>>
#else
      enum_type_i>
#endif
      utf16_nv;

    /// @var none
    /// @glconstwrap{NONE}
    opt_constant<
      mp_list<
        support_level,
        surface_buffer,
        sl_data_type,
        index_data_type,
        oglplus::texture_compare_mode,
        oglplus::context_release_behavior,
        oglplus::path_join_style_nv,
        oglplus::path_gen_mode_nv,
        oglplus::path_transform_type_nv>,
#ifdef GL_NONE
      bitfield_type_c<GL_NONE>>
#else
      bitfield_type_i>
#endif
      none;

    basic_gl_constants(ApiTraits& traits, basic_gl_c_api<ApiTraits>& api);
};
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_gl_constants<ApiTraits>::basic_gl_constants(
  ApiTraits& traits,
  basic_gl_c_api<ApiTraits>& api)
  : no_error("NO_ERROR", traits, api)
  , invalid_enum("INVALID_ENUM", traits, api)
  , invalid_value("INVALID_VALUE", traits, api)
  , invalid_operation("INVALID_OPERATION", traits, api)
  , invalid_framebuffer_operation("INVALID_FRAMEBUFFER_OPERATION", traits, api)
  , stack_overflow("STACK_OVERFLOW", traits, api)
  , stack_underflow("STACK_UNDERFLOW", traits, api)
  , table_too_large("TABLE_TOO_LARGE", traits, api)
  , context_lost("CONTEXT_LOST", traits, api)
  , out_of_memory("OUT_OF_MEMORY", traits, api)
  , true_("TRUE", traits, api)
  , false_("FALSE", traits, api)
  , context_flag_forward_compatible_bit(
      "CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT",
      traits,
      api)
  , context_flag_debug_bit("CONTEXT_FLAG_DEBUG_BIT", traits, api)
  , context_flag_robust_access_bit("CONTEXT_FLAG_ROBUST_ACCESS_BIT", traits, api)
  , context_flag_no_error_bit("CONTEXT_FLAG_NO_ERROR_BIT", traits, api)
  , context_core_profile_bit("CONTEXT_CORE_PROFILE_BIT", traits, api)
  , context_compatibility_profile_bit(
      "CONTEXT_COMPATIBILITY_PROFILE_BIT",
      traits,
      api)
  , no_reset_notification("NO_RESET_NOTIFICATION", traits, api)
  , lose_context_on_reset("LOSE_CONTEXT_ON_RESET", traits, api)
  , context_release_behavior_flush("CONTEXT_RELEASE_BEHAVIOR_FLUSH", traits, api)
  , guilty_context_reset("GUILTY_CONTEXT_RESET", traits, api)
  , innocent_context_reset("INNOCENT_CONTEXT_RESET", traits, api)
  , unknown_context_reset("UNKNOWN_CONTEXT_RESET", traits, api)
  , vertex_attrib_array_barrier_bit(
      "VERTEX_ATTRIB_ARRAY_BARRIER_BIT",
      traits,
      api)
  , element_array_barrier_bit("ELEMENT_ARRAY_BARRIER_BIT", traits, api)
  , uniform_barrier_bit("UNIFORM_BARRIER_BIT", traits, api)
  , texture_fetch_barrier_bit("TEXTURE_FETCH_BARRIER_BIT", traits, api)
  , shader_image_access_barrier_bit(
      "SHADER_IMAGE_ACCESS_BARRIER_BIT",
      traits,
      api)
  , command_barrier_bit("COMMAND_BARRIER_BIT", traits, api)
  , pixel_buffer_barrier_bit("PIXEL_BUFFER_BARRIER_BIT", traits, api)
  , texture_update_barrier_bit("TEXTURE_UPDATE_BARRIER_BIT", traits, api)
  , buffer_update_barrier_bit("BUFFER_UPDATE_BARRIER_BIT", traits, api)
  , client_mapped_buffer_barrier_bit(
      "CLIENT_MAPPED_BUFFER_BARRIER_BIT",
      traits,
      api)
  , query_buffer_barrier_bit("QUERY_BUFFER_BARRIER_BIT", traits, api)
  , framebuffer_barrier_bit("FRAMEBUFFER_BARRIER_BIT", traits, api)
  , transform_feedback_barrier_bit("TRANSFORM_FEEDBACK_BARRIER_BIT", traits, api)
  , atomic_counter_barrier_bit("ATOMIC_COUNTER_BARRIER_BIT", traits, api)
  , shader_storage_barrier_bit("SHADER_STORAGE_BARRIER_BIT", traits, api)
  , all_barrier_bits("ALL_BARRIER_BITS", traits, api)
  , read_only("READ_ONLY", traits, api)
  , write_only("WRITE_ONLY", traits, api)
  , read_write("READ_WRITE", traits, api)
  , low_float("LOW_FLOAT", traits, api)
  , medium_float("MEDIUM_FLOAT", traits, api)
  , high_float("HIGH_FLOAT", traits, api)
  , low_int("LOW_INT", traits, api)
  , medium_int("MEDIUM_INT", traits, api)
  , high_int("HIGH_INT", traits, api)
  , buffer("BUFFER", traits, api)
  , framebuffer("FRAMEBUFFER", traits, api)
  , program_pipeline("PROGRAM_PIPELINE", traits, api)
  , program("PROGRAM", traits, api)
  , query("QUERY", traits, api)
  , renderbuffer("RENDERBUFFER", traits, api)
  , sampler("SAMPLER", traits, api)
  , shader("SHADER", traits, api)
  , texture("TEXTURE", traits, api)
  , transform_feedback("TRANSFORM_FEEDBACK", traits, api)
  , vertex_array("VERTEX_ARRAY", traits, api)
  , vertex_shader("VERTEX_SHADER", traits, api)
  , tess_control_shader("TESS_CONTROL_SHADER", traits, api)
  , tess_evaluation_shader("TESS_EVALUATION_SHADER", traits, api)
  , geometry_shader("GEOMETRY_SHADER", traits, api)
  , fragment_shader("FRAGMENT_SHADER", traits, api)
  , compute_shader("COMPUTE_SHADER", traits, api)
  , shader_include("SHADER_INCLUDE_ARB", traits, api)
  , sync_fence("SYNC_FENCE", traits, api)
  , sync_gpu_commands_complete("SYNC_GPU_COMMANDS_COMPLETE", traits, api)
  , signaled("SIGNALED", traits, api)
  , unsignaled("UNSIGNALED", traits, api)
  , object_type("OBJECT_TYPE", traits, api)
  , sync_status("SYNC_STATUS", traits, api)
  , sync_condition("SYNC_CONDITION", traits, api)
  , condition_satisfied("CONDITION_SATISFIED", traits, api)
  , already_signaled("ALREADY_SIGNALED", traits, api)
  , timeout_expired("TIMEOUT_EXPIRED", traits, api)
  , wait_failed("WAIT_FAILED", traits, api)
  , shader_type("SHADER_TYPE", traits, api)
  , compute_shader_bit("COMPUTE_SHADER_BIT", traits, api)
  , vertex_shader_bit("VERTEX_SHADER_BIT", traits, api)
  , tess_control_shader_bit("TESS_CONTROL_SHADER_BIT", traits, api)
  , tess_evaluation_shader_bit("TESS_EVALUATION_SHADER_BIT", traits, api)
  , geometry_shader_bit("GEOMETRY_SHADER_BIT", traits, api)
  , fragment_shader_bit("FRAGMENT_SHADER_BIT", traits, api)
  , all_shader_bits("ALL_SHADER_BITS", traits, api)
  , active_subroutine_uniforms("ACTIVE_SUBROUTINE_UNIFORMS", traits, api)
  , active_subroutine_uniform_locations(
      "ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS",
      traits,
      api)
  , active_subroutines("ACTIVE_SUBROUTINES", traits, api)
  , active_subroutine_uniform_max_length(
      "ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH",
      traits,
      api)
  , active_subroutine_max_length("ACTIVE_SUBROUTINE_MAX_LENGTH", traits, api)
  , delete_status("DELETE_STATUS", traits, api)
  , compile_status("COMPILE_STATUS", traits, api)
  , info_log_length("INFO_LOG_LENGTH", traits, api)
  , shader_source_length("SHADER_SOURCE_LENGTH", traits, api)
  , spir_v_binary("SPIR_V_BINARY", traits, api)
  , program_separable("PROGRAM_SEPARABLE", traits, api)
  , completion_status("COMPLETION_STATUS", traits, api)
  , link_status("LINK_STATUS", traits, api)
  , validate_status("VALIDATE_STATUS", traits, api)
  , attached_shaders("ATTACHED_SHADERS", traits, api)
  , active_atomic_counter_buffers("ACTIVE_ATOMIC_COUNTER_BUFFERS", traits, api)
  , active_attributes("ACTIVE_ATTRIBUTES", traits, api)
  , active_attribute_max_length("ACTIVE_ATTRIBUTE_MAX_LENGTH", traits, api)
  , active_uniforms("ACTIVE_UNIFORMS", traits, api)
  , active_uniform_max_length("ACTIVE_UNIFORM_MAX_LENGTH", traits, api)
  , program_binary_length("PROGRAM_BINARY_LENGTH", traits, api)
  , compute_work_group_size("COMPUTE_WORK_GROUP_SIZE", traits, api)
  , transform_feedback_buffer_mode("TRANSFORM_FEEDBACK_BUFFER_MODE", traits, api)
  , transform_feedback_varyings("TRANSFORM_FEEDBACK_VARYINGS", traits, api)
  , transform_feedback_varying_max_length(
      "TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH",
      traits,
      api)
  , geometry_vertices_out("GEOMETRY_VERTICES_OUT", traits, api)
  , geometry_input_type("GEOMETRY_INPUT_TYPE", traits, api)
  , geometry_output_type("GEOMETRY_OUTPUT_TYPE", traits, api)
  , tess_gen_point_mode("TESS_GEN_POINT_MODE", traits, api)
  , program_binary_format_mesa("PROGRAM_BINARY_FORMAT_MESA", traits, api)
  , active_program("ACTIVE_PROGRAM", traits, api)
  , renderbuffer_width("RENDERBUFFER_WIDTH", traits, api)
  , renderbuffer_height("RENDERBUFFER_HEIGHT", traits, api)
  , renderbuffer_internal_format("RENDERBUFFER_INTERNAL_FORMAT", traits, api)
  , renderbuffer_samples("RENDERBUFFER_SAMPLES", traits, api)
  , renderbuffer_red_size("RENDERBUFFER_RED_SIZE", traits, api)
  , renderbuffer_green_size("RENDERBUFFER_GREEN_SIZE", traits, api)
  , renderbuffer_blue_size("RENDERBUFFER_BLUE_SIZE", traits, api)
  , renderbuffer_alpha_size("RENDERBUFFER_ALPHA_SIZE", traits, api)
  , renderbuffer_depth_size("RENDERBUFFER_DEPTH_SIZE", traits, api)
  , renderbuffer_stencil_size("RENDERBUFFER_STENCIL_SIZE", traits, api)
  , framebuffer_framebuffer("FRAMEBUFFER_FRAMEBUFFER", traits, api)
  , draw_framebuffer("DRAW_FRAMEBUFFER", traits, api)
  , read_framebuffer("READ_FRAMEBUFFER", traits, api)
  , framebuffer_complete("FRAMEBUFFER_COMPLETE", traits, api)
  , framebuffer_undefined("FRAMEBUFFER_UNDEFINED", traits, api)
  , framebuffer_incomplete_attachment(
      "FRAMEBUFFER_INCOMPLETE_ATTACHMENT",
      traits,
      api)
  , framebuffer_incomplete_missing_attachment(
      "FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT",
      traits,
      api)
  , framebuffer_unsupported("FRAMEBUFFER_UNSUPPORTED", traits, api)
  , framebuffer_incomplete_multisample(
      "FRAMEBUFFER_INCOMPLETE_MULTISAMPLE",
      traits,
      api)
  , framebuffer_incomplete_layer_targets(
      "FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS",
      traits,
      api)
  , framebuffer_default_width("FRAMEBUFFER_DEFAULT_WIDTH", traits, api)
  , framebuffer_default_height("FRAMEBUFFER_DEFAULT_HEIGHT", traits, api)
  , framebuffer_default_layers("FRAMEBUFFER_DEFAULT_LAYERS", traits, api)
  , framebuffer_default_samples("FRAMEBUFFER_DEFAULT_SAMPLES", traits, api)
  , framebuffer_default_fixed_sample_locations(
      "FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS",
      traits,
      api)
  , framebuffer_attachment_red_size(
      "FRAMEBUFFER_ATTACHMENT_RED_SIZE",
      traits,
      api)
  , framebuffer_attachment_green_size(
      "FRAMEBUFFER_ATTACHMENT_GREEN_SIZE",
      traits,
      api)
  , framebuffer_attachment_blue_size(
      "FRAMEBUFFER_ATTACHMENT_BLUE_SIZE",
      traits,
      api)
  , framebuffer_attachment_alpha_size(
      "FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE",
      traits,
      api)
  , framebuffer_attachment_depth_size(
      "FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE",
      traits,
      api)
  , framebuffer_attachment_stencil_size(
      "FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE",
      traits,
      api)
  , framebuffer_attachment_component_type(
      "FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE",
      traits,
      api)
  , framebuffer_attachment_color_encoding(
      "FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING",
      traits,
      api)
  , framebuffer_attachment_object_type(
      "FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE",
      traits,
      api)
  , framebuffer_attachment_object_name(
      "FRAMEBUFFER_ATTACHMENT_OBJECT_NAME",
      traits,
      api)
  , framebuffer_attachment_texture_level(
      "FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL",
      traits,
      api)
  , framebuffer_attachment_texture_cube_map_face(
      "FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE",
      traits,
      api)
  , framebuffer_attachment_layered("FRAMEBUFFER_ATTACHMENT_LAYERED", traits, api)
  , framebuffer_attachment_texture_layer(
      "FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER",
      traits,
      api)
  , color_attachment0("COLOR_ATTACHMENT0", traits, api)
  , depth_attachment("DEPTH_ATTACHMENT", traits, api)
  , stencil_attachment("STENCIL_ATTACHMENT", traits, api)
  , depth_stencil_attachment("DEPTH_STENCIL_ATTACHMENT", traits, api)
  , color("COLOR", traits, api)
  , depth("DEPTH", traits, api)
  , stencil("STENCIL", traits, api)
  , array_buffer("ARRAY_BUFFER", traits, api)
  , atomic_counter_buffer("ATOMIC_COUNTER_BUFFER", traits, api)
  , copy_read_buffer("COPY_READ_BUFFER", traits, api)
  , copy_write_buffer("COPY_WRITE_BUFFER", traits, api)
  , dispatch_indirect_buffer("DISPATCH_INDIRECT_BUFFER", traits, api)
  , draw_indirect_buffer("DRAW_INDIRECT_BUFFER", traits, api)
  , element_array_buffer("ELEMENT_ARRAY_BUFFER", traits, api)
  , parameter_buffer("PARAMETER_BUFFER", traits, api)
  , pixel_pack_buffer("PIXEL_PACK_BUFFER", traits, api)
  , pixel_unpack_buffer("PIXEL_UNPACK_BUFFER", traits, api)
  , query_buffer("QUERY_BUFFER", traits, api)
  , shader_storage_buffer("SHADER_STORAGE_BUFFER", traits, api)
  , texture_buffer("TEXTURE_BUFFER", traits, api)
  , transform_feedback_buffer("TRANSFORM_FEEDBACK_BUFFER", traits, api)
  , uniform_buffer("UNIFORM_BUFFER", traits, api)
  , buffer_access("BUFFER_ACCESS", traits, api)
  , buffer_access_flags("BUFFER_ACCESS_FLAGS", traits, api)
  , buffer_immutable_storage("BUFFER_IMMUTABLE_STORAGE", traits, api)
  , buffer_mapped("BUFFER_MAPPED", traits, api)
  , buffer_map_length("BUFFER_MAP_LENGTH", traits, api)
  , buffer_map_offset("BUFFER_MAP_OFFSET", traits, api)
  , buffer_size("BUFFER_SIZE", traits, api)
  , buffer_storage_flags("BUFFER_STORAGE_FLAGS", traits, api)
  , buffer_usage("BUFFER_USAGE", traits, api)
  , stream_draw("STREAM_DRAW", traits, api)
  , stream_read("STREAM_READ", traits, api)
  , stream_copy("STREAM_COPY", traits, api)
  , static_draw("STATIC_DRAW", traits, api)
  , static_read("STATIC_READ", traits, api)
  , static_copy("STATIC_COPY", traits, api)
  , dynamic_draw("DYNAMIC_DRAW", traits, api)
  , dynamic_read("DYNAMIC_READ", traits, api)
  , dynamic_copy("DYNAMIC_COPY", traits, api)
  , map_read_bit("MAP_READ_BIT", traits, api)
  , map_write_bit("MAP_WRITE_BIT", traits, api)
  , map_persistent_bit("MAP_PERSISTENT_BIT", traits, api)
  , map_coherent_bit("MAP_COHERENT_BIT", traits, api)
  , map_invalidate_range_bit("MAP_INVALIDATE_RANGE_BIT", traits, api)
  , map_invalidate_buffer_bit("MAP_INVALIDATE_BUFFER_BIT", traits, api)
  , map_flush_explicit_bit("MAP_FLUSH_EXPLICIT_BIT", traits, api)
  , map_unsynchronized_bit("MAP_UNSYNCHRONIZED_BIT", traits, api)
  , dynamic_storage_bit("DYNAMIC_STORAGE_BIT", traits, api)
  , client_storage_bit("CLIENT_STORAGE_BIT", traits, api)
  , sparse_storage_bit("SPARSE_STORAGE_BIT_ARB", traits, api)
  , texture0("TEXTURE0", traits, api)
  , texture_3d("TEXTURE_3D", traits, api)
  , texture_2d("TEXTURE_2D", traits, api)
  , texture_1d("TEXTURE_1D", traits, api)
  , texture_2d_array("TEXTURE_2D_ARRAY", traits, api)
  , texture_1d_array("TEXTURE_1D_ARRAY", traits, api)
  , texture_rectangle("TEXTURE_RECTANGLE", traits, api)
  , texture_cube_map("TEXTURE_CUBE_MAP", traits, api)
  , texture_cube_map_array("TEXTURE_CUBE_MAP_ARRAY", traits, api)
  , texture_2d_multisample("TEXTURE_2D_MULTISAMPLE", traits, api)
  , texture_2d_multisample_array("TEXTURE_2D_MULTISAMPLE_ARRAY", traits, api)
  , texture_cube_map_positive_x("TEXTURE_CUBE_MAP_POSITIVE_X", traits, api)
  , texture_cube_map_negative_x("TEXTURE_CUBE_MAP_NEGATIVE_X", traits, api)
  , texture_cube_map_positive_y("TEXTURE_CUBE_MAP_POSITIVE_Y", traits, api)
  , texture_cube_map_negative_y("TEXTURE_CUBE_MAP_NEGATIVE_Y", traits, api)
  , texture_cube_map_positive_z("TEXTURE_CUBE_MAP_POSITIVE_Z", traits, api)
  , texture_cube_map_negative_z("TEXTURE_CUBE_MAP_NEGATIVE_Z", traits, api)
  , texture_external("TEXTURE_EXTERNAL_OES", traits, api)
  , compare_ref_to_texture("COMPARE_REF_TO_TEXTURE", traits, api)
  , nearest("NEAREST", traits, api)
  , linear("LINEAR", traits, api)
  , nearest_mipmap_nearest("NEAREST_MIPMAP_NEAREST", traits, api)
  , nearest_mipmap_linear("NEAREST_MIPMAP_LINEAR", traits, api)
  , linear_mipmap_nearest("LINEAR_MIPMAP_NEAREST", traits, api)
  , linear_mipmap_linear("LINEAR_MIPMAP_LINEAR", traits, api)
  , texture_width("TEXTURE_WIDTH", traits, api)
  , texture_height("TEXTURE_HEIGHT", traits, api)
  , texture_depth("TEXTURE_DEPTH", traits, api)
  , texture_red_size("TEXTURE_RED_SIZE", traits, api)
  , texture_green_size("TEXTURE_GREEN_SIZE", traits, api)
  , texture_blue_size("TEXTURE_BLUE_SIZE", traits, api)
  , texture_alpha_size("TEXTURE_ALPHA_SIZE", traits, api)
  , texture_depth_size("TEXTURE_DEPTH_SIZE", traits, api)
  , texture_stencil_size("TEXTURE_STENCIL_SIZE", traits, api)
  , texture_shared_size("TEXTURE_SHARED_SIZE", traits, api)
  , texture_red_type("TEXTURE_RED_TYPE", traits, api)
  , texture_green_type("TEXTURE_GREEN_TYPE", traits, api)
  , texture_blue_type("TEXTURE_BLUE_TYPE", traits, api)
  , texture_alpha_type("TEXTURE_ALPHA_TYPE", traits, api)
  , texture_depth_type("TEXTURE_DEPTH_TYPE", traits, api)
  , depth_stencil_texture_mode("DEPTH_STENCIL_TEXTURE_MODE", traits, api)
  , image_format_compatibility_type(
      "IMAGE_FORMAT_COMPATIBILITY_TYPE",
      traits,
      api)
  , texture_base_level("TEXTURE_BASE_LEVEL", traits, api)
  , texture_border_color("TEXTURE_BORDER_COLOR", traits, api)
  , texture_compare_mode("TEXTURE_COMPARE_MODE", traits, api)
  , texture_compare_func("TEXTURE_COMPARE_FUNC", traits, api)
  , texture_internal_format("TEXTURE_INTERNAL_FORMAT", traits, api)
  , texture_immutable_format("TEXTURE_IMMUTABLE_FORMAT", traits, api)
  , texture_immutable_levels("TEXTURE_IMMUTABLE_LEVELS", traits, api)
  , texture_lod_bias("TEXTURE_LOD_BIAS", traits, api)
  , texture_mag_filter("TEXTURE_MAG_FILTER", traits, api)
  , texture_max_level("TEXTURE_MAX_LEVEL", traits, api)
  , texture_max_lod("TEXTURE_MAX_LOD", traits, api)
  , texture_min_filter("TEXTURE_MIN_FILTER", traits, api)
  , texture_min_lod("TEXTURE_MIN_LOD", traits, api)
  , texture_swizzle_r("TEXTURE_SWIZZLE_R", traits, api)
  , texture_swizzle_g("TEXTURE_SWIZZLE_G", traits, api)
  , texture_swizzle_b("TEXTURE_SWIZZLE_B", traits, api)
  , texture_swizzle_a("TEXTURE_SWIZZLE_A", traits, api)
  , texture_swizzle_rgba("TEXTURE_SWIZZLE_RGBA", traits, api)
  , texture_target("TEXTURE_TARGET", traits, api)
  , texture_view_min_layer("TEXTURE_VIEW_MIN_LAYER", traits, api)
  , texture_view_min_level("TEXTURE_VIEW_MIN_LEVEL", traits, api)
  , texture_view_num_layers("TEXTURE_VIEW_NUM_LAYERS", traits, api)
  , texture_view_num_levels("TEXTURE_VIEW_NUM_LEVELS", traits, api)
  , texture_fixed_sample_locations("TEXTURE_FIXED_SAMPLE_LOCATIONS", traits, api)
  , texture_wrap_s("TEXTURE_WRAP_S", traits, api)
  , texture_wrap_t("TEXTURE_WRAP_T", traits, api)
  , texture_wrap_r("TEXTURE_WRAP_R", traits, api)
  , clamp_to_edge("CLAMP_TO_EDGE", traits, api)
  , repeat("REPEAT", traits, api)
  , clamp_to_border("CLAMP_TO_BORDER", traits, api)
  , mirrored_repeat("MIRRORED_REPEAT", traits, api)
  , mirror_clamp_to_edge("MIRROR_CLAMP_TO_EDGE", traits, api)
  , red("RED", traits, api)
  , green("GREEN", traits, api)
  , blue("BLUE", traits, api)
  , alpha("ALPHA", traits, api)
  , zero("ZERO", traits, api)
  , one("ONE", traits, api)
  , primitives_generated("PRIMITIVES_GENERATED", traits, api)
  , transform_feedback_primitives_written(
      "TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN",
      traits,
      api)
  , transform_feedback_overflow("TRANSFORM_FEEDBACK_OVERFLOW", traits, api)
  , transform_feedback_stream_overflow(
      "TRANSFORM_FEEDBACK_STREAM_OVERFLOW",
      traits,
      api)
  , samples_passed("SAMPLES_PASSED", traits, api)
  , any_samples_passed("ANY_SAMPLES_PASSED", traits, api)
  , any_samples_passed_conservative(
      "ANY_SAMPLES_PASSED_CONSERVATIVE",
      traits,
      api)
  , time_elapsed("TIME_ELAPSED", traits, api)
  , timestamp("TIMESTAMP", traits, api)
  , vertices_submitted("VERTICES_SUBMITTED", traits, api)
  , primitives_submitted("PRIMITIVES_SUBMITTED", traits, api)
  , vertex_shader_invocations("VERTEX_SHADER_INVOCATIONS", traits, api)
  , tess_control_shader_patches("TESS_CONTROL_SHADER_PATCHES", traits, api)
  , tess_evaluation_shader_invocations(
      "TESS_EVALUATION_SHADER_INVOCATIONS",
      traits,
      api)
  , geometry_shader_invocations("GEOMETRY_SHADER_INVOCATIONS", traits, api)
  , geometry_shader_primitives_emitted(
      "GEOMETRY_SHADER_PRIMITIVES_EMITTED",
      traits,
      api)
  , clipping_input_primitives("CLIPPING_INPUT_PRIMITIVES", traits, api)
  , clipping_output_primitives("CLIPPING_OUTPUT_PRIMITIVES", traits, api)
  , fragment_shader_invocations("FRAGMENT_SHADER_INVOCATIONS", traits, api)
  , compute_shader_invocations("COMPUTE_SHADER_INVOCATIONS", traits, api)
  , query_result("QUERY_RESULT", traits, api)
  , query_result_available("QUERY_RESULT_AVAILABLE", traits, api)
  , interleaved_attribs("INTERLEAVED_ATTRIBS", traits, api)
  , separate_attribs("SEPARATE_ATTRIBS", traits, api)
  , transform_feedback_buffer_start(
      "TRANSFORM_FEEDBACK_BUFFER_START",
      traits,
      api)
  , transform_feedback_buffer_size("TRANSFORM_FEEDBACK_BUFFER_SIZE", traits, api)
  , transform_feedback_paused("TRANSFORM_FEEDBACK_PAUSED", traits, api)
  , transform_feedback_active("TRANSFORM_FEEDBACK_ACTIVE", traits, api)
  , current_vertex_attrib("CURRENT_VERTEX_ATTRIB", traits, api)
  , vertex_attrib_array_buffer_binding(
      "VERTEX_ATTRIB_ARRAY_BUFFER_BINDING",
      traits,
      api)
  , vertex_attrib_array_divisor("VERTEX_ATTRIB_ARRAY_DIVISOR", traits, api)
  , vertex_attrib_array_enabled("VERTEX_ATTRIB_ARRAY_ENABLED", traits, api)
  , vertex_attrib_array_integer("VERTEX_ATTRIB_ARRAY_INTEGER", traits, api)
  , vertex_attrib_array_integer_ext(
      "VERTEX_ATTRIB_ARRAY_INTEGER_EXT",
      traits,
      api)
  , vertex_attrib_array_long("VERTEX_ATTRIB_ARRAY_LONG", traits, api)
  , vertex_attrib_array_normalized("VERTEX_ATTRIB_ARRAY_NORMALIZED", traits, api)
  , vertex_attrib_array_pointer("VERTEX_ATTRIB_ARRAY_POINTER", traits, api)
  , vertex_attrib_array_size("VERTEX_ATTRIB_ARRAY_SIZE", traits, api)
  , vertex_attrib_array_stride("VERTEX_ATTRIB_ARRAY_STRIDE", traits, api)
  , vertex_attrib_array_type("VERTEX_ATTRIB_ARRAY_TYPE", traits, api)
  , vertex_attrib_binding("VERTEX_ATTRIB_BINDING", traits, api)
  , vertex_attrib_relative_offset("VERTEX_ATTRIB_RELATIVE_OFFSET", traits, api)
  , uniform("UNIFORM", traits, api)
  , uniform_block("UNIFORM_BLOCK", traits, api)
  , program_input("PROGRAM_INPUT", traits, api)
  , program_output("PROGRAM_OUTPUT", traits, api)
  , vertex_subroutine("VERTEX_SUBROUTINE", traits, api)
  , tess_control_subroutine("TESS_CONTROL_SUBROUTINE", traits, api)
  , tess_evaluation_subroutine("TESS_EVALUATION_SUBROUTINE", traits, api)
  , geometry_subroutine("GEOMETRY_SUBROUTINE", traits, api)
  , fragment_subroutine("FRAGMENT_SUBROUTINE", traits, api)
  , compute_subroutine("COMPUTE_SUBROUTINE", traits, api)
  , vertex_subroutine_uniform("VERTEX_SUBROUTINE_UNIFORM", traits, api)
  , tess_control_subroutine_uniform(
      "TESS_CONTROL_SUBROUTINE_UNIFORM",
      traits,
      api)
  , tess_evaluation_subroutine_uniform(
      "TESS_EVALUATION_SUBROUTINE_UNIFORM",
      traits,
      api)
  , geometry_subroutine_uniform("GEOMETRY_SUBROUTINE_UNIFORM", traits, api)
  , fragment_subroutine_uniform("FRAGMENT_SUBROUTINE_UNIFORM", traits, api)
  , compute_subroutine_uniform("COMPUTE_SUBROUTINE_UNIFORM", traits, api)
  , transform_feedback_varying("GL_TRANSFORM_FEEDBACK_VARYING", traits, api)
  , buffer_variable("BUFFER_VARIABLE", traits, api)
  , buffer_storage_block("BUFFER_STORAGE_BLOCK", traits, api)
  , fragment_input_nv("FRAGMENT_INPUT_NV", traits, api)
  , active_variables("ACTIVE_VARIABLES", traits, api)
  , num_active_variables("NUM_ACTIVE_VARIABLES", traits, api)
  , array_size("ARRAY_SIZE", traits, api)
  , array_stride("ARRAY_STRIDE", traits, api)
  , block_index("BLOCK_INDEX", traits, api)
  , is_row_major("IS_ROW_MAJOR", traits, api)
  , matrix_stride("MATRIX_STRIDE", traits, api)
  , atomic_counter_buffer_index("ATOMIC_COUNTER_BUFFER_INDEX", traits, api)
  , buffer_data_size("BUFFER_DATA_SIZE", traits, api)
  , num_compatible_subroutines("NUM_COMPATIBLE_SUBROUTINES", traits, api)
  , compatible_subroutines("COMPATIBLE_SUBROUTINES", traits, api)
  , is_per_patch("IS_PER_PATCH", traits, api)
  , location("LOCATION", traits, api)
  , location_component("LOCATION_COMPONENT", traits, api)
  , location_index("LOCATION_INDEX", traits, api)
  , name_length("NAME_LENGTH", traits, api)
  , offset("OFFSET", traits, api)
  , referenced_by_vertex_shader("REFERENCED_BY_VERTEX_SHADER", traits, api)
  , referenced_by_tess_control_shader(
      "REFERENCED_BY_TESS_CONTROL_SHADER",
      traits,
      api)
  , referenced_by_tess_evaluation_shader(
      "REFERENCED_BY_TESS_EVALUATION_SHADER",
      traits,
      api)
  , referenced_by_geometry_shader("REFERENCED_BY_GEOMETRY_SHADER", traits, api)
  , referenced_by_fragment_shader("REFERENCED_BY_FRAGMENT_SHADER", traits, api)
  , referenced_by_compute_shader("REFERENCED_BY_COMPUTE_SHADER", traits, api)
  , transform_feedback_buffer_index(
      "TRANSFORM_FEEDBACK_BUFFER_INDEX",
      traits,
      api)
  , transform_feedback_buffer_stride(
      "TRANSFORM_FEEDBACK_BUFFER_STRIDE",
      traits,
      api)
  , top_level_array_size("TOP_LEVEL_ARRAY_SIZE", traits, api)
  , top_level_array_stride("TOP_LEVEL_ARRAY_STRIDE", traits, api)
  , type("TYPE", traits, api)
  , path_gen_mode_nv("PATH_GEN_MODE_NV", traits, api)
  , path_gen_components_nv("PATH_GEN_COMPONENTS_NV", traits, api)
  , path_gen_coeff_nv("PATH_GEN_COEFF_NV", traits, api)
  , blend("BLEND", traits, api)
  , program_point_size("PROGRAM_POINT_SIZE", traits, api)
  , primitive_restart("PRIMITIVE_RESTART", traits, api)
  , clip_distance0("CLIP_DISTANCE0", traits, api)
  , cull_face("CULL_FACE", traits, api)
  , depth_clamp("DEPTH_CLAMP", traits, api)
  , depth_test("DEPTH_TEST", traits, api)
  , scissor_test("SCISSOR_TEST", traits, api)
  , stencil_test("STENCIL_TEST", traits, api)
  , polygon_offset_fill("POLYGON_OFFSET_FILL", traits, api)
  , polygon_offset_line("POLYGON_OFFSET_LINE", traits, api)
  , polygon_offset_point("POLYGON_OFFSET_POINT", traits, api)
  , rasterizer_discard("RASTERIZER_DISCARD", traits, api)
  , multisample("MULTISAMPLE", traits, api)
  , debug_output("DEBUG_OUTPUT", traits, api)
  , debug_output_synchronous("DEBUG_OUTPUT_SYNCHRONOUS", traits, api)
  , blackhole_render("BLACKHOLE_RENDER_INTEL", traits, api)
  , color_array("COLOR_ARRAY", traits, api)
  , edge_flag_array("EDGE_FLAG_ARRAY", traits, api)
  , fog_coord_array("FOG_COORD_ARRAY", traits, api)
  , index_array("INDEX_ARRAY", traits, api)
  , normal_array("NORMAL_ARRAY", traits, api)
  , secondary_color_array("SECONDARY_COLOR_ARRAY", traits, api)
  , texture_coord_array("TEXTURE_COORD_ARRAY", traits, api)
  , vertex_attrib_array_unified_nv("VERTEX_ATTRIB_ARRAY_UNIFIED_NV", traits, api)
  , element_array_unified_nv("ELEMENT_ARRAY_UNIFIED_NV", traits, api)
  , uniform_buffer_unified_nv("UNIFORM_BUFFER_UNIFIED_NV", traits, api)
  , front_left("FRONT_LEFT", traits, api)
  , front_right("FRONT_RIGHT", traits, api)
  , back_left("BACK_LEFT", traits, api)
  , back_right("BACK_RIGHT", traits, api)
  , front("FRONT", traits, api)
  , back("BACK", traits, api)
  , left("LEFT", traits, api)
  , right("RIGHT", traits, api)
  , front_and_back("FRONT_AND_BACK", traits, api)
  , array_buffer_binding("ARRAY_BUFFER_BINDING", traits, api)
  , atomic_counter_buffer_binding("ATOMIC_COUNTER_BUFFER_BINDING", traits, api)
  , copy_read_buffer_binding("COPY_READ_BUFFER_BINDING", traits, api)
  , copy_write_buffer_binding("COPY_WRITE_BUFFER_BINDING", traits, api)
  , dispatch_indirect_buffer_binding(
      "DISPATCH_INDIRECT_BUFFER_BINDING",
      traits,
      api)
  , draw_indirect_buffer_binding("DRAW_INDIRECT_BUFFER_BINDING", traits, api)
  , element_array_buffer_binding("ELEMENT_ARRAY_BUFFER_BINDING", traits, api)
  , pixel_pack_buffer_binding("PIXEL_PACK_BUFFER_BINDING", traits, api)
  , pixel_unpack_buffer_binding("PIXEL_UNPACK_BUFFER_BINDING", traits, api)
  , shader_storage_buffer_binding("SHADER_STORAGE_BUFFER_BINDING", traits, api)
  , texture_buffer_binding("TEXTURE_BUFFER_BINDING", traits, api)
  , transform_feedback_buffer_binding(
      "TRANSFORM_FEEDBACK_BUFFER_BINDING",
      traits,
      api)
  , uniform_buffer_binding("UNIFORM_BUFFER_BINDING", traits, api)
  , query_buffer_binding("QUERY_BUFFER_BINDING", traits, api)
  , parameter_buffer_binding("PARAMETER_BUFFER_BINDING_ARB", traits, api)
  , buffer_binding("BUFFER_BINDING", traits, api)
  , draw_framebuffer_binding("DRAW_FRAMEBUFFER_BINDING", traits, api)
  , renderbuffer_binding("RENDERBUFFER_BINDING", traits, api)
  , sampler_binding("SAMPLER_BINDING", traits, api)
  , texture_binding_1d("TEXTURE_BINDING_1D", traits, api)
  , texture_binding_2d("TEXTURE_BINDING_2D", traits, api)
  , texture_binding_3d("TEXTURE_BINDING_3D", traits, api)
  , texture_binding_1d_array("TEXTURE_BINDING_1D_ARRAY", traits, api)
  , texture_binding_2d_array("TEXTURE_BINDING_2D_ARRAY", traits, api)
  , texture_binding_rectangle("TEXTURE_BINDING_RECTANGLE", traits, api)
  , texture_binding_buffer("TEXTURE_BINDING_BUFFER", traits, api)
  , texture_binding_cube_map("TEXTURE_BINDING_CUBE_MAP", traits, api)
  , texture_binding_cube_map_array("TEXTURE_BINDING_CUBE_MAP_ARRAY", traits, api)
  , texture_binding_2d_multisample("TEXTURE_BINDING_2D_MULTISAMPLE", traits, api)
  , texture_binding_2d_multisample_array(
      "TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY",
      traits,
      api)
  , texture_binding_external("TEXTURE_BINDING_EXTERNAL_OES", traits, api)
  , transform_feedback_binding("TRANSFORM_FEEDBACK_BINDING", traits, api)
  , vertex_array_binding("VERTEX_ARRAY_BINDING", traits, api)
  , program_pipeline_binding("PROGRAM_PIPELINE_BINDING", traits, api)
  , current_program("CURRENT_PROGRAM", traits, api)
  , draw_buffer0("DRAW_BUFFER0", traits, api)
  , major_version("MAJOR_VERSION", traits, api)
  , minor_version("MINOR_VERSION", traits, api)
  , reset_notification_strategy("RESET_NOTIFICATION_STRATEGY", traits, api)
  , num_shading_language_versions("NUM_SHADING_LANGUAGE_VERSIONS", traits, api)
  , num_extensions("NUM_EXTENSIONS", traits, api)
  , num_spir_v_extensions("NUM_SPIR_V_EXTENSIONS", traits, api)
  , context_flags("CONTEXT_FLAGS", traits, api)
  , context_profile_mask("CONTEXT_PROFILE_MASK", traits, api)
  , doublebuffer("DOUBLEBUFFER", traits, api)
  , stereo("STEREO", traits, api)
  , clip_origin("CLIP_ORIGIN", traits, api)
  , clip_depth_mode("CLIP_DEPTH_MODE", traits, api)
  , clamp_read_color("CLAMP_READ_COLOR", traits, api)
  , provoking_vertex("PROVOKING_VERTEX", traits, api)
  , layer_provoking_vertex("LAYER_PROVOKING_VERTEX", traits, api)
  , viewport_index_provoking_vertex(
      "VIEWPORT_INDEX_PROVOKING_VERTEX",
      traits,
      api)
  , cull_face_mode("CULL_FACE_MODE", traits, api)
  , front_face("FRONT_FACE", traits, api)
  , polygon_mode("POLYGON_MODE", traits, api)
  , active_texture("ACTIVE_TEXTURE", traits, api)
  , stencil_func("STENCIL_FUNC", traits, api)
  , stencil_value_mask("STENCIL_VALUE_MASK", traits, api)
  , stencil_ref("STENCIL_REF", traits, api)
  , stencil_fail("STENCIL_FAIL", traits, api)
  , stencil_pass_depth_fail("STENCIL_PASS_DEPTH_FAIL", traits, api)
  , stencil_pass_depth_pass("STENCIL_PASS_DEPTH_PASS", traits, api)
  , stencil_back_func("STENCIL_BACK_FUNC", traits, api)
  , stencil_back_value_mask("STENCIL_BACK_VALUE_MASK", traits, api)
  , stencil_back_ref("STENCIL_BACK_REF", traits, api)
  , stencil_back_fail("STENCIL_BACK_FAIL", traits, api)
  , stencil_back_pass_depth_fail("STENCIL_BACK_PASS_DEPTH_FAIL", traits, api)
  , stencil_back_pass_depth_pass("STENCIL_BACK_PASS_DEPTH_PASS", traits, api)
  , stencil_writemask("STENCIL_WRITEMASK", traits, api)
  , stencil_back_writemask("STENCIL_BACK_WRITEMASK", traits, api)
  , stencil_clear_value("STENCIL_CLEAR_VALUE", traits, api)
  , depth_func("DEPTH_FUNC", traits, api)
  , logic_op_mode("LOGIC_OP_MODE", traits, api)
  , sample_buffers("SAMPLE_BUFFERS", traits, api)
  , subpixel_bits("SUBPIXEL_BITS", traits, api)
  , viewport_subpixel_bits("VIEWPORT_SUBPIXEL_BITS", traits, api)
  , num_compressed_texture_formats("NUM_COMPRESSED_TEXTURE_FORMATS", traits, api)
  , compressed_texture_formats("COMPRESSED_TEXTURE_FORMATS", traits, api)
  , num_program_binary_formats("NUM_PROGRAM_BINARY_FORMATS", traits, api)
  , program_binary_formats("PROGRAM_BINARY_FORMATS", traits, api)
  , num_shader_binary_formats("NUM_SHADER_BINARY_FORMATS", traits, api)
  , shader_binary_formats("SHADER_BINARY_FORMATS", traits, api)
  , texture_buffer_offset_alignment(
      "TEXTURE_BUFFER_OFFSET_ALIGNMENT",
      traits,
      api)
  , max_vertex_uniform_blocks("MAX_VERTEX_UNIFORM_BLOCKS", traits, api)
  , max_tess_control_uniform_blocks(
      "MAX_TESS_CONTROL_UNIFORM_BLOCKS",
      traits,
      api)
  , max_tess_evaluation_uniform_blocks(
      "MAX_TESS_EVALUATION_UNIFORM_BLOCKS",
      traits,
      api)
  , max_geometry_uniform_blocks("MAX_GEOMETRY_UNIFORM_BLOCKS", traits, api)
  , max_fragment_uniform_blocks("MAX_FRAGMENT_UNIFORM_BLOCKS", traits, api)
  , max_compute_uniform_blocks("MAX_COMPUTE_UNIFORM_BLOCKS", traits, api)
  , max_combined_uniform_blocks("MAX_COMBINED_UNIFORM_BLOCKS", traits, api)
  , max_uniform_block_size("MAX_UNIFORM_BLOCK_SIZE", traits, api)
  , max_debug_message_length("MAX_DEBUG_MESSAGE_LENGTH", traits, api)
  , max_debug_logged_messages("MAX_DEBUG_LOGGED_MESSAGES", traits, api)
  , debug_logged_messages("DEBUG_LOGGED_MESSAGES", traits, api)
  , debug_next_logged_message_length(
      "DEBUG_NEXT_LOGGED_MESSAGE_LENGTH",
      traits,
      api)
  , max_debug_group_stack_depth("MAX_DEBUG_GROUP_STACK_DEPTH", traits, api)
  , debug_group_stack_depth("DEBUG_GROUP_STACK_DEPTH", traits, api)
  , max_label_length("MAX_LABEL_LENGTH", traits, api)
  , shader_compiler("SHADER_COMPILER", traits, api)
  , max_shader_compiler_threads("MAX_SHADER_COMPILER_THREADS_ARB", traits, api)
  , line_width("LINE_WIDTH", traits, api)
  , point_size("POINT_SIZE", traits, api)
  , polygon_offset_clamp("POLYGON_OFFSET_CLAMP", traits, api)
  , polygon_offset_factor("POLYGON_OFFSET_FACTOR", traits, api)
  , polygon_offset_units("POLYGON_OFFSET_UNITS", traits, api)
  , sample_coverage_value("SAMPLE_COVERAGE_VALUE", traits, api)
  , blend_color("BLEND_COLOR", traits, api)
  , color_clear_value("COLOR_CLEAR_VALUE", traits, api)
  , depth_clear_value("DEPTH_CLEAR_VALUE", traits, api)
  , viewport_bounds_range("VIEWPORT_BOUNDS_RANGE", traits, api)
  , point_size_range("POINT_SIZE_RANGE", traits, api)
  , point_size_granularity("POINT_SIZE_GRANULARITY", traits, api)
  , aliased_line_width_range("ALIASED_LINE_WIDTH_RANGE", traits, api)
  , smooth_line_width_range("SMOOTH_LINE_WIDTH_RANGE", traits, api)
  , smooth_line_width_granularity("SMOOTH_LINE_WIDTH_GRANULARITY", traits, api)
  , min_sample_shading_value("MIN_SAMPLE_SHADING_VALUE", traits, api)
  , min_fragment_interpolation_offset(
      "MIN_FRAGMENT_INTERPOLATION_OFFSET",
      traits,
      api)
  , max_fragment_interpolation_offset(
      "MAX_FRAGMENT_INTERPOLATION_OFFSET",
      traits,
      api)
  , max_texture_lod_bias("MAX_TEXTURE_LOD_BIAS", traits, api)
  , max_texture_max_anisotropy("MAX_TEXTURE_MAX_ANISOTROPY", traits, api)
  , max_viewport_dims("MAX_VIEWPORT_DIMS", traits, api)
  , vendor("VENDOR", traits, api)
  , renderer("RENDERER", traits, api)
  , version("VERSION", traits, api)
  , shading_language_version("SHADING_LANGUAGE_VERSION", traits, api)
  , extensions("EXTENSIONS", traits, api)
  , spir_v_extensions("SPIR_V_EXTENSIONS", traits, api)
  , named_string_length("NAMED_STRING_LENGTH_ARB", traits, api)
  , named_string_type("NAMED_STRING_TYPE_ARB", traits, api)
  , color_buffer_bit("COLOR_BUFFER_BIT", traits, api)
  , depth_buffer_bit("DEPTH_BUFFER_BIT", traits, api)
  , stencil_buffer_bit("STENCIL_BUFFER_BIT", traits, api)
  , lequal("LEQUAL", traits, api)
  , gequal("GEQUAL", traits, api)
  , less("LESS", traits, api)
  , greater("GREATER", traits, api)
  , equal("EQUAL", traits, api)
  , notequal("NOTEQUAL", traits, api)
  , always("ALWAYS", traits, api)
  , never("NEVER", traits, api)
  , float_("FLOAT", traits, api)
  , float_vec2("FLOAT_VEC2", traits, api)
  , float_vec3("FLOAT_VEC3", traits, api)
  , float_vec4("FLOAT_VEC4", traits, api)
  , double_("DOUBLE", traits, api)
  , double_vec2("DOUBLE_VEC2", traits, api)
  , double_vec3("DOUBLE_VEC3", traits, api)
  , double_vec4("DOUBLE_VEC4", traits, api)
  , int_("INT", traits, api)
  , int_vec2("INT_VEC2", traits, api)
  , int_vec3("INT_VEC3", traits, api)
  , int_vec4("INT_VEC4", traits, api)
  , unsigned_int_("UNSIGNED_INT", traits, api)
  , unsigned_int_vec2("UNSIGNED_INT_VEC2", traits, api)
  , unsigned_int_vec3("UNSIGNED_INT_VEC3", traits, api)
  , unsigned_int_vec4("UNSIGNED_INT_VEC4", traits, api)
  , bool_("BOOL", traits, api)
  , bool_vec2("BOOL_VEC2", traits, api)
  , bool_vec3("BOOL_VEC3", traits, api)
  , bool_vec4("BOOL_VEC4", traits, api)
  , float_mat2("FLOAT_MAT2", traits, api)
  , float_mat3("FLOAT_MAT3", traits, api)
  , float_mat4("FLOAT_MAT4", traits, api)
  , float_mat2x3("FLOAT_MAT2x3", traits, api)
  , float_mat2x4("FLOAT_MAT2x4", traits, api)
  , float_mat3x2("FLOAT_MAT3x2", traits, api)
  , float_mat3x4("FLOAT_MAT3x4", traits, api)
  , float_mat4x2("FLOAT_MAT4x2", traits, api)
  , float_mat4x3("FLOAT_MAT4x3", traits, api)
  , double_mat2("DOUBLE_MAT2", traits, api)
  , double_mat3("DOUBLE_MAT3", traits, api)
  , double_mat4("DOUBLE_MAT4", traits, api)
  , double_mat2x3("DOUBLE_MAT2x3", traits, api)
  , double_mat2x4("DOUBLE_MAT2x4", traits, api)
  , double_mat3x2("DOUBLE_MAT3x2", traits, api)
  , double_mat3x4("DOUBLE_MAT3x4", traits, api)
  , double_mat4x2("DOUBLE_MAT4x2", traits, api)
  , double_mat4x3("DOUBLE_MAT4x3", traits, api)
  , sampler_1d("SAMPLER_1D", traits, api)
  , sampler_2d("SAMPLER_2D", traits, api)
  , sampler_3d("SAMPLER_3D", traits, api)
  , sampler_cube("SAMPLER_CUBE", traits, api)
  , sampler_1d_shadow("SAMPLER_1D_SHADOW", traits, api)
  , sampler_2d_shadow("SAMPLER_2D_SHADOW", traits, api)
  , sampler_1d_array("SAMPLER_1D_ARRAY", traits, api)
  , sampler_2d_array("SAMPLER_2D_ARRAY", traits, api)
  , sampler_cube_map_array("SAMPLER_CUBE_MAP_ARRAY", traits, api)
  , sampler_1d_array_shadow("SAMPLER_1D_ARRAY_SHADOW", traits, api)
  , sampler_2d_array_shadow("SAMPLER_2D_ARRAY_SHADOW", traits, api)
  , sampler_2d_multisample("SAMPLER_2D_MULTISAMPLE", traits, api)
  , sampler_2d_multisample_array("SAMPLER_2D_MULTISAMPLE_ARRAY", traits, api)
  , sampler_cube_shadow("SAMPLER_CUBE_SHADOW", traits, api)
  , sampler_cube_map_array_shadow("SAMPLER_CUBE_MAP_ARRAY_SHADOW", traits, api)
  , sampler_buffer("SAMPLER_BUFFER", traits, api)
  , sampler_2d_rect("SAMPLER_2D_RECT", traits, api)
  , sampler_2d_rect_shadow("SAMPLER_2D_RECT_SHADOW", traits, api)
  , int_sampler_1d("INT_SAMPLER_1D", traits, api)
  , int_sampler_2d("INT_SAMPLER_2D", traits, api)
  , int_sampler_3d("INT_SAMPLER_3D", traits, api)
  , int_sampler_cube("INT_SAMPLER_CUBE", traits, api)
  , int_sampler_1d_array("INT_SAMPLER_1D_ARRAY", traits, api)
  , int_sampler_2d_array("INT_SAMPLER_2D_ARRAY", traits, api)
  , int_sampler_cube_map_array("INT_SAMPLER_CUBE_MAP_ARRAY", traits, api)
  , int_sampler_2d_multisample("INT_SAMPLER_2D_MULTISAMPLE", traits, api)
  , int_sampler_2d_multisample_array(
      "INT_SAMPLER_2D_MULTISAMPLE_ARRAY",
      traits,
      api)
  , int_sampler_buffer("INT_SAMPLER_BUFFER", traits, api)
  , int_sampler_2d_rect("INT_SAMPLER_2D_RECT", traits, api)
  , unsigned_int_sampler_1d("UNSIGNED_INT_SAMPLER_1D", traits, api)
  , unsigned_int_sampler_2d("UNSIGNED_INT_SAMPLER_2D", traits, api)
  , unsigned_int_sampler_3d("UNSIGNED_INT_SAMPLER_3D", traits, api)
  , unsigned_int_sampler_cube("UNSIGNED_INT_SAMPLER_CUBE", traits, api)
  , unsigned_int_sampler_1d_array("UNSIGNED_INT_SAMPLER_1D_ARRAY", traits, api)
  , unsigned_int_sampler_2d_array("UNSIGNED_INT_SAMPLER_2D_ARRAY", traits, api)
  , unsigned_int_sampler_cube_map_array(
      "UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY",
      traits,
      api)
  , unsigned_int_sampler_2d_multisample(
      "UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE",
      traits,
      api)
  , unsigned_int_sampler_2d_multisample_array(
      "UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY",
      traits,
      api)
  , unsigned_int_sampler_buffer("UNSIGNED_INT_SAMPLER_BUFFER", traits, api)
  , unsigned_int_sampler_2d_rect("UNSIGNED_INT_SAMPLER_2D_RECT", traits, api)
  , image_1d("IMAGE_1D", traits, api)
  , image_2d("IMAGE_2D", traits, api)
  , image_3d("IMAGE_3D", traits, api)
  , image_2d_rect("IMAGE_2D_RECT", traits, api)
  , image_cube("IMAGE_CUBE", traits, api)
  , image_buffer("IMAGE_BUFFER", traits, api)
  , image_1d_array("IMAGE_1D_ARRAY", traits, api)
  , image_2d_array("IMAGE_2D_ARRAY", traits, api)
  , image_2d_multisample("IMAGE_2D_MULTISAMPLE", traits, api)
  , image_2d_multisample_array("IMAGE_2D_MULTISAMPLE_ARRAY", traits, api)
  , int_image_1d("INT_IMAGE_1D", traits, api)
  , int_image_2d("INT_IMAGE_2D", traits, api)
  , int_image_3d("INT_IMAGE_3D", traits, api)
  , int_image_2d_rect("INT_IMAGE_2D_RECT", traits, api)
  , int_image_cube("INT_IMAGE_CUBE", traits, api)
  , int_image_buffer("INT_IMAGE_BUFFER", traits, api)
  , int_image_1d_array("INT_IMAGE_1D_ARRAY", traits, api)
  , int_image_2d_array("INT_IMAGE_2D_ARRAY", traits, api)
  , int_image_2d_multisample("INT_IMAGE_2D_MULTISAMPLE", traits, api)
  , int_image_2d_multisample_array("INT_IMAGE_2D_MULTISAMPLE_ARRAY", traits, api)
  , unsigned_int_image_1d("UNSIGNED_INT_IMAGE_1D", traits, api)
  , unsigned_int_image_2d("UNSIGNED_INT_IMAGE_2D", traits, api)
  , unsigned_int_image_3d("UNSIGNED_INT_IMAGE_3D", traits, api)
  , unsigned_int_image_2d_rect("UNSIGNED_INT_IMAGE_2D_RECT", traits, api)
  , unsigned_int_image_cube("UNSIGNED_INT_IMAGE_CUBE", traits, api)
  , unsigned_int_image_buffer("UNSIGNED_INT_IMAGE_BUFFER", traits, api)
  , unsigned_int_image_1d_array("UNSIGNED_INT_IMAGE_1D_ARRAY", traits, api)
  , unsigned_int_image_2d_array("UNSIGNED_INT_IMAGE_2D_ARRAY", traits, api)
  , unsigned_int_image_2d_multisample(
      "UNSIGNED_INT_IMAGE_2D_MULTISAMPLE",
      traits,
      api)
  , unsigned_int_image_2d_multisample_array(
      "UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY",
      traits,
      api)
  , unsigned_int_atomic_counter("UNSIGNED_INT_ATOMIC_COUNTER", traits, api)
  , points("POINTS", traits, api)
  , line_strip("LINE_STRIP", traits, api)
  , line_loop("LINE_LOOP", traits, api)
  , lines("LINES", traits, api)
  , triangle_strip("TRIANGLE_STRIP", traits, api)
  , triangle_fan("TRIANGLE_FAN", traits, api)
  , triangles("TRIANGLES", traits, api)
  , quads("QUADS", traits, api)
  , quad_strip("QUAD_STRIP", traits, api)
  , polygon("POLYGON", traits, api)
  , lines_adjacency("LINES_ADJACENCY", traits, api)
  , line_strip_adjacency("LINE_STRIP_ADJACENCY", traits, api)
  , triangles_adjacency("TRIANGLES_ADJACENCY", traits, api)
  , triangle_strip_adjacency("TRIANGLE_STRIP_ADJACENCY", traits, api)
  , patches("PATCHES", traits, api)
  , isolines("ISOLINES", traits, api)
  , fractional_even("FRACTIONAL_EVEN", traits, api)
  , fractional_odd("FRACTIONAL_ODD", traits, api)
  , patch_vertices("PATCH_VERTICES", traits, api)
  , patch_default_outer_level("PATCH_DEFAULT_OUTER_LEVEL", traits, api)
  , patch_default_inner_level("PATCH_DEFAULT_INNER_LEVEL", traits, api)
  , cw("CW", traits, api)
  , ccw("CCW", traits, api)
  , first_vertex_convention("FIRST_VERTEX_CONVENTION", traits, api)
  , last_vertex_convention("LAST_VERTEX_CONVENTION", traits, api)
  , query_wait("QUERY_WAIT", traits, api)
  , query_no_wait("QUERY_NO_WAIT", traits, api)
  , query_by_region_wait("QUERY_BY_REGION_WAIT", traits, api)
  , query_by_region_no_wait("QUERY_BY_REGION_NO_WAIT", traits, api)
  , query_wait_inverted("QUERY_WAIT_INVERTED", traits, api)
  , query_no_wait_inverted("QUERY_NO_WAIT_INVERTED", traits, api)
  , query_by_region_wait_inverted("QUERY_BY_REGION_WAIT_INVERTED", traits, api)
  , query_by_region_no_wait_inverted(
      "QUERY_BY_REGION_NO_WAIT_INVERTED",
      traits,
      api)
  , point_size_min("POINT_SIZE_MIN", traits, api)
  , point_size_max("POINT_SIZE_MAX", traits, api)
  , point_fade_threshold_size("POINT_FADE_THRESHOLD_SIZE", traits, api)
  , point_sprite_coord_origin("POINT_SPRITE_COORD_ORIGIN", traits, api)
  , lower_left("LOWER_LEFT", traits, api)
  , upper_left("UPPER_LEFT", traits, api)
  , point("POINT", traits, api)
  , line("LINE", traits, api)
  , fill("FILL", traits, api)
  , fill_rectangle_nv("FILL_RECTANGLE_NV", traits, api)
  , keep("KEEP", traits, api)
  , replace("REPLACE", traits, api)
  , incr("INCR", traits, api)
  , decr("DECR", traits, api)
  , invert("INVERT", traits, api)
  , incr_wrap("INCR_WRAP", traits, api)
  , decr_wrap("DECR_WRAP", traits, api)
  , clear_("CLEAR", traits, api)
  , and_("AND", traits, api)
  , and_reverse("AND_REVERSE", traits, api)
  , copy("COPY", traits, api)
  , and_inverted("AND_INVERTED", traits, api)
  , noop("NOOP", traits, api)
  , xor_("XOR", traits, api)
  , or_("OR", traits, api)
  , nor("NOR", traits, api)
  , equiv("EQUIV", traits, api)
  , or_reverse("OR_REVERSE", traits, api)
  , copy_inverted("COPY_INVERTED", traits, api)
  , or_inverted("OR_INVERTED", traits, api)
  , nand("NAND", traits, api)
  , set("SET", traits, api)
  , func_add("FUNC_ADD", traits, api)
  , func_subtract("FUNC_SUBTRACT", traits, api)
  , func_reverse_subtract("FUNC_REVERSE_SUBTRACT", traits, api)
  , min("MIN", traits, api)
  , max("MAX", traits, api)
  , multiply_khr("MULTIPLY_KHR", traits, api)
  , screen_khr("SCREEN_KHR", traits, api)
  , overlay_khr("OVERLAY_KHR", traits, api)
  , darken_khr("DARKEN_KHR", traits, api)
  , lighten_khr("LIGHTEN_KHR", traits, api)
  , colordodge_khr("COLORDODGE_KHR", traits, api)
  , colorburn_khr("COLORBURN_KHR", traits, api)
  , hardlight_khr("HARDLIGHT_KHR", traits, api)
  , softlight_khr("SOFTLIGHT_KHR", traits, api)
  , difference_khr("DIFFERENCE_KHR", traits, api)
  , exclusion_khr("EXCLUSION_KHR", traits, api)
  , hsl_hue_khr("HSL_HUE_KHR", traits, api)
  , hsl_saturation_khr("HSL_SATURATION_KHR", traits, api)
  , hsl_color_khr("HSL_COLOR_KHR", traits, api)
  , hsl_luminosity_khr("HSL_LUMINOSITY_KHR", traits, api)
  , src_color("SRC_COLOR", traits, api)
  , one_minus_src_color("ONE_MINUS_SRC_COLOR", traits, api)
  , dst_color("DST_COLOR", traits, api)
  , one_minus_dst_color("ONE_MINUS_DST_COLOR", traits, api)
  , src_alpha("SRC_ALPHA", traits, api)
  , one_minus_src_alpha("ONE_MINUS_SRC_ALPHA", traits, api)
  , dst_alpha("DST_ALPHA", traits, api)
  , one_minus_dst_alpha("ONE_MINUS_DST_ALPHA", traits, api)
  , constant_color("CONSTANT_COLOR", traits, api)
  , one_minus_constant_color("ONE_MINUS_CONSTANT_COLOR", traits, api)
  , constant_alpha("CONSTANT_ALPHA", traits, api)
  , one_minus_constant_alpha("ONE_MINUS_CONSTANT_ALPHA", traits, api)
  , src_alpha_saturate("SRC_ALPHA_SATURATE", traits, api)
  , src1_color("SRC1_COLOR", traits, api)
  , one_minus_src1_color("ONE_MINUS_SRC1_COLOR", traits, api)
  , src1_alpha("SRC1_ALPHA", traits, api)
  , one_minus_src1_alpha("ONE_MINUS_SRC1_ALPHA", traits, api)
  , unsigned_byte_("UNSIGNED_BYTE", traits, api)
  , byte_("BYTE", traits, api)
  , unsigned_short_("UNSIGNED_SHORT", traits, api)
  , short_("SHORT", traits, api)
  , half_float_("HALF_FLOAT", traits, api)
  , unsigned_byte_3_3_2("UNSIGNED_BYTE_3_3_2", traits, api)
  , unsigned_byte_2_3_3_rev("UNSIGNED_BYTE_2_3_3_REV", traits, api)
  , unsigned_short_5_6_5("UNSIGNED_SHORT_5_6_5", traits, api)
  , unsigned_short_5_6_5_rev("UNSIGNED_SHORT_5_6_5_REV", traits, api)
  , unsigned_short_4_4_4_4("UNSIGNED_SHORT_4_4_4_4", traits, api)
  , unsigned_short_4_4_4_4_rev("UNSIGNED_SHORT_4_4_4_4_REV", traits, api)
  , unsigned_short_5_5_5_1("UNSIGNED_SHORT_5_5_5_1", traits, api)
  , unsigned_short_1_5_5_5_rev("UNSIGNED_SHORT_1_5_5_5_REV", traits, api)
  , unsigned_int_8_8_8_8("UNSIGNED_INT_8_8_8_8", traits, api)
  , unsigned_int_8_8_8_8_rev("UNSIGNED_INT_8_8_8_8_REV", traits, api)
  , unsigned_int_10_10_10_2("UNSIGNED_INT_10_10_10_2", traits, api)
  , unsigned_int_2_10_10_10_rev("UNSIGNED_INT_2_10_10_10_REV", traits, api)
  , unsigned_int_24_8("UNSIGNED_INT_24_8", traits, api)
  , unsigned_int_10f_11f_11f_rev("UNSIGNED_INT_10F_11F_11F_REV", traits, api)
  , unsigned_int_5_9_9_9_rev("UNSIGNED_INT_5_9_9_9_REV", traits, api)
  , float_32_unsigned_int_24_8_rev("FLOAT_32_UNSIGNED_INT_24_8_REV", traits, api)
  , stencil_index("STENCIL_INDEX", traits, api)
  , bgr("BGR", traits, api)
  , bgra("BGRA", traits, api)
  , red_integer("RED_INTEGER", traits, api)
  , green_integer("GREEN_INTEGER", traits, api)
  , blue_integer("BLUE_INTEGER", traits, api)
  , rg_integer("RG_INTEGER", traits, api)
  , rgb_integer("RGB_INTEGER", traits, api)
  , rgba_integer("RGBA_INTEGER", traits, api)
  , bgr_integer("BGR_INTEGER", traits, api)
  , bgra_integer("BGRA_INTEGER", traits, api)
  , depth_component("DEPTH_COMPONENT", traits, api)
  , depth_stencil("DEPTH_STENCIL", traits, api)
  , depth_component16("DEPTH_COMPONENT16", traits, api)
  , depth_component24("DEPTH_COMPONENT24", traits, api)
  , depth_component32f("DEPTH_COMPONENT32F", traits, api)
  , stencil_index8("STENCIL_INDEX8", traits, api)
  , rg("RG", traits, api)
  , rgb("RGB", traits, api)
  , rgba("RGBA", traits, api)
  , r8("R8", traits, api)
  , r8_snorm("R8_SNORM", traits, api)
  , r16("R16", traits, api)
  , r16_snorm("R16_SNORM", traits, api)
  , rg8("RG8", traits, api)
  , rg8ui("RG8UI", traits, api)
  , rg8_snorm("RG8_SNORM", traits, api)
  , rg16("RG16", traits, api)
  , rg16ui("RG16UI", traits, api)
  , rg16_snorm("RG16_SNORM", traits, api)
  , rg32ui("RG32UI", traits, api)
  , r3_g3_b2("R3_G3_B2", traits, api)
  , rgb4("RGB4", traits, api)
  , rgb5("RGB5", traits, api)
  , rgb8("RGB8", traits, api)
  , rgb8_snorm("RGB8_SNORM", traits, api)
  , rgb10("RGB10", traits, api)
  , rgb12("RGB12", traits, api)
  , rgb16("RGB16", traits, api)
  , rgb16_snorm("RGB16_SNORM", traits, api)
  , rgba2("RGBA2", traits, api)
  , rgba4("RGBA4", traits, api)
  , rgb5_a1("RGB5_A1", traits, api)
  , rgba8("RGBA8", traits, api)
  , rgba8ui("RGBA8UI", traits, api)
  , rgba8_snorm("RGBA8_SNORM", traits, api)
  , rgb10_a2("RGB10_A2", traits, api)
  , rgb10_a2ui("RGB10_A2UI", traits, api)
  , rgba12("RGBA12", traits, api)
  , rgba16("RGBA16", traits, api)
  , rgba16ui("RGBA16UI", traits, api)
  , rgba16_snorm("RGBA16_SNORM", traits, api)
  , r16f("R16F", traits, api)
  , rg16f("RG16F", traits, api)
  , rgb16f("RGB16F", traits, api)
  , rgba16f("RGBA16F", traits, api)
  , r32f("R32F", traits, api)
  , rg32f("RG32F", traits, api)
  , rgb32f("RGB32F", traits, api)
  , rgba32f("RGBA32F", traits, api)
  , rgba32ui("RGBA32UI", traits, api)
  , r11f_g11f_b10f("R11F_G11F_B10F", traits, api)
  , rgb9_e5("RGB9_E5", traits, api)
  , r8i("R8I", traits, api)
  , r8ui("R8UI", traits, api)
  , r16i("R16I", traits, api)
  , r16ui("R16UI", traits, api)
  , r32i("R32I", traits, api)
  , r32ui("R32UI", traits, api)
  , srgb("SRGB", traits, api)
  , srgb8("SRGB8", traits, api)
  , srgb_alpha("SRGB_ALPHA", traits, api)
  , srgb8_alpha8("SRGB8_ALPHA8", traits, api)
  , compressed_srgb("COMPRESSED_SRGB", traits, api)
  , compressed_srgb8_etc2("COMPRESSED_SRGB8_ETC2", traits, api)
  , compressed_srgb_alpha("COMPRESSED_SRGB_ALPHA", traits, api)
  , compressed_srgb8_alpha8_etc2_eac(
      "COMPRESSED_SRGB8_ALPHA8_ETC2_EAC",
      traits,
      api)
  , compressed_srgb8_punchthrough_alpha1_etc2(
      "COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2",
      traits,
      api)
  , compressed_srgb_alpha_bptc_unorm(
      "COMPRESSED_SRGB_ALPHA_BPTC_UNORM",
      traits,
      api)
  , pack_swap_bytes("PACK_SWAP_BYTES", traits, api)
  , pack_lsb_first("PACK_LSB_FIRST", traits, api)
  , pack_row_length("PACK_ROW_LENGTH", traits, api)
  , pack_skip_rows("PACK_SKIP_ROWS", traits, api)
  , pack_skip_pixels("PACK_SKIP_PIXELS", traits, api)
  , pack_alignment("PACK_ALIGNMENT", traits, api)
  , pack_image_height("PACK_IMAGE_HEIGHT", traits, api)
  , pack_skip_images("PACK_SKIP_IMAGES", traits, api)
  , pack_compressed_block_width("PACK_COMPRESSED_BLOCK_WIDTH", traits, api)
  , pack_compressed_block_height("PACK_COMPRESSED_BLOCK_HEIGHT", traits, api)
  , pack_compressed_block_depth("PACK_COMPRESSED_BLOCK_DEPTH", traits, api)
  , pack_compressed_block_size("PACK_COMPRESSED_BLOCK_SIZE", traits, api)
  , unpack_swap_bytes("UNPACK_SWAP_BYTES", traits, api)
  , unpack_lsb_first("UNPACK_LSB_FIRST", traits, api)
  , unpack_row_length("UNPACK_ROW_LENGTH", traits, api)
  , unpack_skip_rows("UNPACK_SKIP_ROWS", traits, api)
  , unpack_skip_pixels("UNPACK_SKIP_PIXELS", traits, api)
  , unpack_alignment("UNPACK_ALIGNMENT", traits, api)
  , unpack_image_height("UNPACK_IMAGE_HEIGHT", traits, api)
  , unpack_skip_images("UNPACK_SKIP_IMAGES", traits, api)
  , unpack_compressed_block_width("UNPACK_COMPRESSED_BLOCK_WIDTH", traits, api)
  , unpack_compressed_block_height("UNPACK_COMPRESSED_BLOCK_HEIGHT", traits, api)
  , unpack_compressed_block_depth("UNPACK_COMPRESSED_BLOCK_DEPTH", traits, api)
  , unpack_compressed_block_size("UNPACK_COMPRESSED_BLOCK_SIZE", traits, api)
  , image_class_4_x_32("IMAGE_CLASS_4_X_32", traits, api)
  , image_class_2_x_32("IMAGE_CLASS_2_X_32", traits, api)
  , image_class_1_x_32("IMAGE_CLASS_1_X_32", traits, api)
  , image_class_4_x_16("IMAGE_CLASS_4_X_16", traits, api)
  , image_class_2_x_16("IMAGE_CLASS_2_X_16", traits, api)
  , image_class_1_x_16("IMAGE_CLASS_1_X_16", traits, api)
  , image_class_4_x_8("IMAGE_CLASS_4_X_8", traits, api)
  , image_class_2_x_8("IMAGE_CLASS_2_X_8", traits, api)
  , image_class_1_x_8("IMAGE_CLASS_1_X_8", traits, api)
  , image_class_11_11_10("IMAGE_CLASS_11_11_10", traits, api)
  , image_class_10_10_10_2("IMAGE_CLASS_10_10_10_2", traits, api)
  , view_class_128_bits("VIEW_CLASS_128_BITS", traits, api)
  , view_class_96_bits("VIEW_CLASS_96_BITS", traits, api)
  , view_class_64_bits("VIEW_CLASS_64_BITS", traits, api)
  , view_class_48_bits("VIEW_CLASS_48_BITS", traits, api)
  , view_class_32_bits("VIEW_CLASS_32_BITS", traits, api)
  , view_class_24_bits("VIEW_CLASS_24_BITS", traits, api)
  , view_class_16_bits("VIEW_CLASS_16_BITS", traits, api)
  , view_class_8_bits("VIEW_CLASS_8_BITS", traits, api)
  , view_class_s3tc_dxt1_rgb("VIEW_CLASS_S3TC_DXT1_RGB", traits, api)
  , view_class_s3tc_dxt1_rgba("VIEW_CLASS_S3TC_DXT1_RGBA", traits, api)
  , view_class_s3tc_dxt3_rgba("VIEW_CLASS_S3TC_DXT3_RGBA", traits, api)
  , view_class_s3tc_dxt5_rgba("VIEW_CLASS_S3TC_DXT5_RGBA", traits, api)
  , view_class_rgtc1_red("VIEW_CLASS_RGTC1_RED", traits, api)
  , view_class_rgtc2_rg("VIEW_CLASS_RGTC2_RG", traits, api)
  , view_class_bptc_unorm("VIEW_CLASS_BPTC_UNORM", traits, api)
  , view_class_bptc_float("VIEW_CLASS_BPTC_FLOAT", traits, api)
  , num_sample_counts("NUM_SAMPLE_COUNTS", traits, api)
  , samples("SAMPLES", traits, api)
  , internalformat_supported("INTERNALFORMAT_SUPPORTED", traits, api)
  , internalformat_preferred("INTERNALFORMAT_PREFERRED", traits, api)
  , internalformat_red_size("INTERNALFORMAT_RED_SIZE", traits, api)
  , internalformat_green_size("INTERNALFORMAT_GREEN_SIZE", traits, api)
  , internalformat_blue_size("INTERNALFORMAT_BLUE_SIZE", traits, api)
  , internalformat_alpha_size("INTERNALFORMAT_ALPHA_SIZE", traits, api)
  , internalformat_depth_size("INTERNALFORMAT_DEPTH_SIZE", traits, api)
  , internalformat_stencil_size("INTERNALFORMAT_STENCIL_SIZE", traits, api)
  , internalformat_shared_size("INTERNALFORMAT_SHARED_SIZE", traits, api)
  , internalformat_red_type("INTERNALFORMAT_RED_TYPE", traits, api)
  , internalformat_green_type("INTERNALFORMAT_GREEN_TYPE", traits, api)
  , internalformat_blue_type("INTERNALFORMAT_BLUE_TYPE", traits, api)
  , internalformat_alpha_type("INTERNALFORMAT_ALPHA_TYPE", traits, api)
  , internalformat_depth_type("INTERNALFORMAT_DEPTH_TYPE", traits, api)
  , internalformat_stencil_type("INTERNALFORMAT_STENCIL_TYPE", traits, api)
  , max_width("MAX_WIDTH", traits, api)
  , max_height("MAX_HEIGHT", traits, api)
  , max_depth("MAX_DEPTH", traits, api)
  , max_layers("MAX_LAYERS", traits, api)
  , max_combined_dimensions("MAX_COMBINED_DIMENSIONS", traits, api)
  , color_components("COLOR_COMPONENTS", traits, api)
  , depth_components("DEPTH_COMPONENTS", traits, api)
  , stencil_components("STENCIL_COMPONENTS", traits, api)
  , color_renderable("COLOR_RENDERABLE", traits, api)
  , depth_renderable("DEPTH_RENDERABLE", traits, api)
  , stencil_renderable("STENCIL_RENDERABLE", traits, api)
  , framebuffer_renderable("FRAMEBUFFER_RENDERABLE", traits, api)
  , framebuffer_renderable_layered("FRAMEBUFFER_RENDERABLE_LAYERED", traits, api)
  , framebuffer_blend("FRAMEBUFFER_BLEND", traits, api)
  , read_pixels("READ_PIXELS", traits, api)
  , read_pixels_format("READ_PIXELS_FORMAT", traits, api)
  , read_pixels_type("READ_PIXELS_TYPE", traits, api)
  , texture_image_format("TEXTURE_IMAGE_FORMAT", traits, api)
  , texture_image_type("TEXTURE_IMAGE_TYPE", traits, api)
  , get_texture_image_format("GET_TEXTURE_IMAGE_FORMAT", traits, api)
  , get_texture_image_type("GET_TEXTURE_IMAGE_TYPE", traits, api)
  , mipmap("MIPMAP", traits, api)
  , generate_mipmap("GENERATE_MIPMAP", traits, api)
  , auto_generate_mipmap("AUTO_GENERATE_MIPMAP", traits, api)
  , color_encoding("COLOR_ENCODING", traits, api)
  , srgb_read("SRGB_READ", traits, api)
  , srgb_write("SRGB_WRITE", traits, api)
  , filter("FILTER", traits, api)
  , vertex_texture("VERTEX_TEXTURE", traits, api)
  , tess_control_texture("TESS_CONTROL_TEXTURE", traits, api)
  , tess_evaluation_texture("TESS_EVALUATION_TEXTURE", traits, api)
  , geometry_texture("GEOMETRY_TEXTURE", traits, api)
  , fragment_texture("FRAGMENT_TEXTURE", traits, api)
  , compute_texture("COMPUTE_TEXTURE", traits, api)
  , texture_shadow("TEXTURE_SHADOW", traits, api)
  , texture_gather("TEXTURE_GATHER", traits, api)
  , texture_gather_shadow("TEXTURE_GATHER_SHADOW", traits, api)
  , shader_image_load("SHADER_IMAGE_LOAD", traits, api)
  , shader_image_store("SHADER_IMAGE_STORE", traits, api)
  , shader_image_atomic("SHADER_IMAGE_ATOMIC", traits, api)
  , image_texel_size("IMAGE_TEXEL_SIZE", traits, api)
  , image_compatibility_class("IMAGE_COMPATIBILITY_CLASS", traits, api)
  , image_pixel_format("IMAGE_PIXEL_FORMAT", traits, api)
  , image_pixel_type("IMAGE_PIXEL_TYPE", traits, api)
  , simultaneous_texture_and_depth_test(
      "SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST",
      traits,
      api)
  , simultaneous_texture_and_stencil_test(
      "SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST",
      traits,
      api)
  , simultaneous_texture_and_depth_write(
      "SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE",
      traits,
      api)
  , simultaneous_texture_and_stencil_write(
      "SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE",
      traits,
      api)
  , texture_compressed("TEXTURE_COMPRESSED", traits, api)
  , texture_compressed_image_size("TEXTURE_COMPRESSED_IMAGE_SIZE", traits, api)
  , texture_compressed_block_width("TEXTURE_COMPRESSED_BLOCK_WIDTH", traits, api)
  , texture_compressed_block_height(
      "TEXTURE_COMPRESSED_BLOCK_HEIGHT",
      traits,
      api)
  , texture_compressed_block_size("TEXTURE_COMPRESSED_BLOCK_SIZE", traits, api)
  , clear_buffer("CLEAR_BUFFER", traits, api)
  , clear_texture("CLEAR_TEXTURE", traits, api)
  , texture_view("TEXTURE_VIEW", traits, api)
  , view_compatibility_class("VIEW_COMPATIBILITY_CLASS", traits, api)
  , sample_position("SAMPLE_POSITION", traits, api)
  , projection("PROJECTION", traits, api)
  , modelview("MODELVIEW", traits, api)
  , debug_severity_high("DEBUG_SEVERITY_HIGH", traits, api)
  , debug_severity_medium("DEBUG_SEVERITY_MEDIUM", traits, api)
  , debug_severity_low("DEBUG_SEVERITY_LOW", traits, api)
  , debug_severity_notification("DEBUG_SEVERITY_NOTIFICATION", traits, api)
  , debug_source_api("DEBUG_SOURCE_API", traits, api)
  , debug_source_window_system("DEBUG_SOURCE_WINDOW_SYSTEM", traits, api)
  , debug_source_shader_compiler("DEBUG_SOURCE_SHADER_COMPILER", traits, api)
  , debug_source_third_party("DEBUG_SOURCE_THIRD_PARTY", traits, api)
  , debug_source_application("DEBUG_SOURCE_APPLICATION", traits, api)
  , debug_source_other("DEBUG_SOURCE_OTHER", traits, api)
  , debug_type_error("DEBUG_TYPE_ERROR", traits, api)
  , debug_type_deprecated_behavior("DEBUG_TYPE_DEPRECATED_BEHAVIOR", traits, api)
  , debug_type_undefined_behavior("DEBUG_TYPE_UNDEFINED_BEHAVIOR", traits, api)
  , debug_type_portability("DEBUG_TYPE_PORTABILITY", traits, api)
  , debug_type_performance("DEBUG_TYPE_PERFORMANCE", traits, api)
  , debug_type_marker("DEBUG_TYPE_MARKER", traits, api)
  , debug_type_push_group("DEBUG_TYPE_PUSH_GROUP", traits, api)
  , debug_type_pop_group("DEBUG_TYPE_POP_GROUP", traits, api)
  , debug_type_other("DEBUG_TYPE_OTHER", traits, api)
  , line_smooth_hint("LINE_SMOOTH_HINT", traits, api)
  , polygon_smooth_hint("POLYGON_SMOOTH_HINT", traits, api)
  , texture_compression_hint("TEXTURE_COMPRESSION_HINT", traits, api)
  , fragment_shader_derivative_hint(
      "FRAGMENT_SHADER_DERIVATIVE_HINT",
      traits,
      api)
  , fastest("FASTEST", traits, api)
  , nicest("NICEST", traits, api)
  , dont_care("DONT_CARE", traits, api)
  , full_support("FULL_SUPPORT", traits, api)
  , caveat_support("CAVEAT_SUPPORT", traits, api)
  , close_path_nv("CLOSE_PATH_NV", traits, api)
  , move_to_nv("MOVE_TO_NV", traits, api)
  , relative_move_to_nv("RELATIVE_MOVE_TO_NV", traits, api)
  , line_to_nv("LINE_TO_NV", traits, api)
  , relative_line_to_nv("RELATIVE_LINE_TO_NV", traits, api)
  , horizontal_line_to_nv("HORIZONTAL_LINE_TO_NV", traits, api)
  , relative_horizontal_line_to_nv("RELATIVE_HORIZONTAL_LINE_TO_NV", traits, api)
  , vertical_line_to_nv("VERTICAL_LINE_TO_NV", traits, api)
  , relative_vertical_line_to_nv("RELATIVE_VERTICAL_LINE_TO_NV", traits, api)
  , quadratic_curve_to_nv("QUADRATIC_CURVE_TO_NV", traits, api)
  , relative_quadratic_curve_to_nv("RELATIVE_QUADRATIC_CURVE_TO_NV", traits, api)
  , cubic_curve_to_nv("CUBIC_CURVE_TO_NV", traits, api)
  , relative_cubic_curve_to_nv("RELATIVE_CUBIC_CURVE_TO_NV", traits, api)
  , smooth_quadratic_curve_to_nv("SMOOTH_QUADRATIC_CURVE_TO_NV", traits, api)
  , relative_smooth_quadratic_curve_to_nv(
      "RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV",
      traits,
      api)
  , smooth_cubic_curve_to_nv("SMOOTH_CUBIC_CURVE_TO_NV", traits, api)
  , relative_smooth_cubic_curve_to_nv(
      "RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV",
      traits,
      api)
  , small_ccw_arc_to_nv("SMALL_CCW_ARC_TO_NV", traits, api)
  , relative_small_ccw_arc_to_nv("RELATIVE_SMALL_CCW_ARC_TO_NV", traits, api)
  , small_cw_arc_to_nv("SMALL_CW_ARC_TO_NV", traits, api)
  , relative_small_cw_arc_to_nv("RELATIVE_SMALL_CW_ARC_TO_NV", traits, api)
  , large_ccw_arc_to_nv("LARGE_CCW_ARC_TO_NV", traits, api)
  , relative_large_ccw_arc_to_nv("RELATIVE_LARGE_CCW_ARC_TO_NV", traits, api)
  , large_cw_arc_to_nv("LARGE_CW_ARC_TO_NV", traits, api)
  , relative_large_cw_arc_to_nv("RELATIVE_LARGE_CW_ARC_TO_NV", traits, api)
  , restart_path_nv("RESTART_PATH_NV", traits, api)
  , dup_first_cubic_curve_to_nv("DUP_FIRST_CUBIC_CURVE_TO_NV", traits, api)
  , dup_last_cubic_curve_to_nv("DUP_LAST_CUBIC_CURVE_TO_NV", traits, api)
  , rect_nv("RECT_NV", traits, api)
  , circular_ccw_arc_to_nv("CIRCULAR_CCW_ARC_TO_NV", traits, api)
  , circular_cw_arc_to_nv("CIRCULAR_CW_ARC_TO_NV", traits, api)
  , circular_tangent_arc_to_nv("CIRCULAR_TANGENT_ARC_TO_NV", traits, api)
  , arc_to_nv("ARC_TO_NV", traits, api)
  , relative_arc_to_nv("RELATIVE_ARC_TO_NV", traits, api)
  , flat("FLAT", traits, api)
  , square_nv("SQUARE_NV", traits, api)
  , round_nv("ROUND_NV", traits, api)
  , triangular_nv("TRIANGULAR_NV", traits, api)
  , luminance("LUMINANCE", traits, api)
  , intensity("INTENSITY", traits, api)
  , luminance_alpha("LUMINANCE_ALPHA", traits, api)
  , primary_color_nv("PRIMARY_COLOR_NV", traits, api)
  , secondary_color_nv("SECONDARY_COLOR_NV", traits, api)
  , move_to_resets_nv("MOVE_TO_RESETS_NV", traits, api)
  , move_to_continues_nv("MOVE_TO_CONTINUES_NV", traits, api)
  , convex_hull_nv("CONVEX_HULL_NV", traits, api)
  , bounding_box_nv("BOUNDING_BOX_NV", traits, api)
  , bounding_box_of_bounding_boxes_nv(
      "BOUNDING_BOX_OF_BOUNDING_BOXES_NV",
      traits,
      api)
  , count_up_nv("COUNT_UP_NV", traits, api)
  , count_down_nv("COUNT_DOWN_NV", traits, api)
  , bevel_nv("BEVEL_NV", traits, api)
  , miter_revert_nv("MITER_REVERT_NV", traits, api)
  , miter_truncate_nv("MITER_TRUNCATE_NV", traits, api)
  , bold_bit_nv("BOLD_BIT_NV", traits, api)
  , italic_bit_nv("ITALIC_BIT_NV", traits, api)
  , standard_font_name_nv("STANDARD_FONT_NAME_NV", traits, api)
  , system_font_name_nv("SYSTEM_FONT_NAME_NV", traits, api)
  , file_name_nv("FILE_NAME_NV", traits, api)
  , path_format_svg_nv("PATH_FORMAT_SVG_NV", traits, api)
  , path_format_ps_nv("PATH_FORMAT_PS_NV", traits, api)
  , eye_linear("EYE_LINEAR", traits, api)
  , object_linear("OBJECT_LINEAR", traits, api)
  , path_object_bounding_box_nv("PATH_OBJECT_BOUNDING_BOX_NV", traits, api)
  , accum_adjacent_pairs_nv("ACCUM_ADJACENT_PAIRS_NV", traits, api)
  , adjacent_pairs_nv("ADJACENT_PAIRS_NV", traits, api)
  , first_to_rest_nv("FIRST_TO_REST_NV", traits, api)
  , glyph_width_bit_nv("GLYPH_WIDTH_BIT_NV", traits, api)
  , glyph_height_bit_nv("GLYPH_HEIGHT_BIT_NV", traits, api)
  , glyph_horizontal_bearing_x_bit_nv(
      "GLYPH_HORIZONTAL_BEARING_X_BIT_NV",
      traits,
      api)
  , glyph_horizontal_bearing_y_bit_nv(
      "GLYPH_HORIZONTAL_BEARING_Y_BIT_NV",
      traits,
      api)
  , glyph_horizontal_bearing_advance_bit_nv(
      "GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV",
      traits,
      api)
  , glyph_vertical_bearing_x_bit_nv(
      "GLYPH_VERTICAL_BEARING_X_BIT_NV",
      traits,
      api)
  , glyph_vertical_bearing_y_bit_nv(
      "GLYPH_VERTICAL_BEARING_Y_BIT_NV",
      traits,
      api)
  , glyph_vertical_bearing_advance_bit_nv(
      "GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV",
      traits,
      api)
  , glyph_has_kerning_bit_nv("GLYPH_HAS_KERNING_BIT_NV", traits, api)
  , font_x_min_bounds_bit_nv("FONT_X_MIN_BOUNDS_BIT_NV", traits, api)
  , font_y_min_bounds_bit_nv("FONT_Y_MIN_BOUNDS_BIT_NV", traits, api)
  , font_x_max_bounds_bit_nv("FONT_X_MAX_BOUNDS_BIT_NV", traits, api)
  , font_y_max_bounds_bit_nv("FONT_Y_MAX_BOUNDS_BIT_NV", traits, api)
  , font_units_per_em_bit_nv("FONT_UNITS_PER_EM_BIT_NV", traits, api)
  , font_ascender_bit_nv("FONT_ASCENDER_BIT_NV", traits, api)
  , font_descender_bit_nv("FONT_DESCENDER_BIT_NV", traits, api)
  , font_height_bit_nv("FONT_HEIGHT_BIT_NV", traits, api)
  , font_max_advance_width_bit_nv("FONT_MAX_ADVANCE_WIDTH_BIT_NV", traits, api)
  , font_max_advance_height_bit_nv("FONT_MAX_ADVANCE_HEIGHT_BIT_NV", traits, api)
  , font_underline_position_bit_nv("FONT_UNDERLINE_POSITION_BIT_NV", traits, api)
  , font_underline_thickness_bit_nv(
      "FONT_UNDERLINE_THICKNESS_BIT_NV",
      traits,
      api)
  , font_has_kerning_bit_nv("FONT_HAS_KERNING_BIT_NV", traits, api)
  , skip_missing_glyph_nv("SKIP_MISSING_GLYPH_NV", traits, api)
  , use_missing_glyph_nv("USE_MISSING_GLYPH_NV", traits, api)
  , path_command_count_nv("PATH_COMMAND_COUNT_NV", traits, api)
  , path_coord_count_nv("PATH_COORD_COUNT_NV", traits, api)
  , path_computed_length_nv("PATH_COMPUTED_LENGTH_NV", traits, api)
  , path_stroke_width_nv("PATH_STROKE_WIDTH_NV", traits, api)
  , path_initial_end_cap_nv("PATH_INITIAL_END_CAP_NV", traits, api)
  , path_terminal_end_cap_nv("PATH_TERMINAL_END_CAP_NV", traits, api)
  , path_join_style_nv("PATH_JOIN_STYLE_NV", traits, api)
  , path_miter_limit_nv("PATH_MITER_LIMIT_NV", traits, api)
  , path_dash_array_count_nv("PATH_DASH_ARRAY_COUNT_NV", traits, api)
  , path_dash_offset_nv("PATH_DASH_OFFSET_NV", traits, api)
  , path_dash_offset_reset_nv("PATH_DASH_OFFSET_RESET_NV", traits, api)
  , path_client_length_nv("PATH_CLIENT_LENGTH_NV", traits, api)
  , path_initial_dash_cap_nv("PATH_INITIAL_DASH_CAP_NV", traits, api)
  , path_terminal_dash_cap_nv("PATH_TERMINAL_DASH_CAP_NV", traits, api)
  , path_fill_mode_nv("PATH_FILL_MODE_NV", traits, api)
  , path_fill_mask_nv("PATH_FILL_MASK_NV", traits, api)
  , path_fill_cover_mode_nv("PATH_FILL_COVER_MODE_NV", traits, api)
  , path_stroke_cover_mode_nv("PATH_STROKE_COVER_MODE_NV", traits, api)
  , path_stroke_mask_nv("PATH_STROKE_MASK_NV", traits, api)
  , path_stroke_bound_nv("PATH_STROKE_BOUND_NV", traits, api)
  , path_fill_bounding_box_nv("PATH_FILL_BOUNDING_BOX_NV", traits, api)
  , path_stroke_bounding_box_nv("PATH_STROKE_BOUNDING_BOX_NV", traits, api)
  , translate_x_nv("TRANSLATE_X_NV", traits, api)
  , translate_y_nv("TRANSLATE_Y_NV", traits, api)
  , translate_2d_nv("TRANSLATE_2D_NV", traits, api)
  , translate_3d_nv("TRANSLATE_3D_NV", traits, api)
  , affine_2d_nv("AFFINE_2D_NV", traits, api)
  , affine_3d_nv("AFFINE_3D_NV", traits, api)
  , transpose_affine_2d_nv("TRANSPOSE_AFFINE_2D_NV", traits, api)
  , transpose_affine_3d_nv("TRANSPOSE_AFFINE_3D_NV", traits, api)
  , utf8_nv("UTF8_NV", traits, api)
  , utf16_nv("UTF16_NV", traits, api)
  , none("NONE", traits, api) {}
//------------------------------------------------------------------------------
} // namespace oglplus
} // namespace eagine
