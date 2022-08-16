/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include "gl_def.hpp"

export module eagine.oglplus:enum_types;
import eagine.core.types;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @ingroup gl_api_wrap
/// @see gl_bitfield_class
/// @see gl_ubyte_class
/// @see gl_bool_class
/// @see gl_any_enum_class
///
/// This wrapper uses the specified Id to group various GL constants logically
/// belonging together and prevents accidental mismatches and use of GL constants
/// from unrelated groups. For example using a shader type constant in place
/// of texture type constants. Such mismatches result in compilation errors.
template <typename Self, identifier_value Id>
using gl_enum_class = c_api::enum_class<Self, gl_types::enum_type, "GL", Id>;

/// @brief Typed wrapper class for GLbitfield constants/values.
/// @ingroup gl_api_wrap
/// @see gl_enum_class
/// @see gl_ubyte_class
/// @see gl_bool_class
/// @see gl_any_enum_class
///
/// This wrapper uses the specified Id to group various GL constants logically
/// belonging together and prevents accidental mismatches and use of GL constanst
/// from unrelated groups. For example using a context attribute bits in place
/// of memory barrier bit constants. Such mismatches result in compilation errors.
template <typename Self, identifier_value Id>
using gl_bitfield_class =
  c_api::enum_class<Self, gl_types::bitfield_type, "GL", Id>;

/// @brief Typed wrapper class for GLubyte constants/values.
/// @ingroup gl_api_wrap
/// @see gl_enum_class
/// @see gl_bitfield_class
/// @see gl_bool_class
/// @see gl_any_enum_class
///
/// This wrapper uses the specified Id to group various GL constants logically
/// belonging together and prevents accidental mismatches and use of GL constanst
/// from unrelated groups. Such mismatches result in compilation errors.
template <typename Self, identifier_value Id>
using gl_ubyte_class = c_api::enum_class<Self, gl_types::ubyte_type, "GL", Id>;

/// @brief Typed wrapper class for GLboolean constants/values.
/// @ingroup gl_api_wrap
/// @see gl_enum_class
/// @see gl_bitfield_class
/// @see gl_ubyte_class
/// @see gl_any_enum_class
template <typename Self, identifier_value Id>
using gl_bool_class = c_api::enum_class<Self, gl_types::bool_type, "GL", Id>;

/// @brief Type erasure alias for GL enum classes.
/// @ingroup gl_api_wrap
/// @see gl_enum_class
/// @see gl_bitfield_class
/// @see gl_ubyte_class
/// @see gl_bool_class
using gl_any_enum_class = c_api::any_enum_class<"GL">;

/// @brief Type erasure alias for GL enum values.
/// @ingroup gl_api_wrap
using gl_any_enum_value = c_api::any_enum_value<"GL">;

static constexpr auto same_enum_class(
  const gl_any_enum_class a,
  const gl_any_enum_class b) noexcept -> bool {
    return ::eagine::c_api::same_enum_class(a, b);
}
//------------------------------------------------------------------------------
/// @brief Wrapper for true, false GL enums.
/// @ingroup gl_api_wrap
export struct true_false : gl_bool_class<true_false, "TrueFalse"> {
    using enum_class::enum_class;

    /// @brief Explicit conversion to native bool.
    constexpr explicit operator bool() const noexcept {
#ifdef GL_TRUE
        return this->_value == GL_TRUE;
#else
        return false;
#endif
    }
};

/// @brief Typed enumeration for GL error code constants.
/// @ingroup gl_api_wrap
export struct error_code : gl_enum_class<error_code, "ErrorCode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL context flag bit constants.
/// @ingroup gl_api_wrap
export struct context_flag_bit
  : gl_bitfield_class<context_flag_bit, "CtxFlagBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL context profile bit constants.
/// @ingroup gl_api_wrap
export struct context_profile_bit
  : gl_bitfield_class<context_profile_bit, "CtxProfBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL context release behavior constants.
/// @ingroup gl_api_wrap
export struct context_release_behavior
  : gl_enum_class<context_release_behavior, "CtxRlsBhvr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL context reset notification strategy constants.
/// @ingroup gl_api_wrap
export struct reset_notification_strategy
  : gl_enum_class<reset_notification_strategy, "RstNtfStgy"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL capability constants.
/// @ingroup gl_api_wrap
export struct capability : gl_enum_class<capability, "Capability"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL client capability constants.
/// @ingroup gl_api_wrap
export struct client_capability
  : gl_enum_class<client_capability, "ClientCap"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL graphics reset status constants.
/// @ingroup gl_api_wrap
export struct graphics_reset_status
  : gl_enum_class<graphics_reset_status, "GrphRstStt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL memory barrier bit constants.
/// @ingroup gl_api_wrap
export struct memory_barrier_bit
  : gl_bitfield_class<memory_barrier_bit, "MemBrirBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL access specifier constants.
/// @ingroup gl_api_wrap
export struct access_specifier : gl_enum_class<access_specifier, "AccessSpec"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL precision type constants.
/// @ingroup gl_api_wrap
export struct precision_type : gl_enum_class<precision_type, "PrecisType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL object type constants.
/// @ingroup gl_api_wrap
export struct object_type : gl_enum_class<object_type, "ObjectType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL sync type constants.
/// @ingroup gl_api_wrap
export struct sync_type : gl_enum_class<sync_type, "SyncType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL sync status constants.
/// @ingroup gl_api_wrap
export struct sync_status : gl_enum_class<sync_status, "SyncStatus"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL sync condition constants.
/// @ingroup gl_api_wrap
export struct sync_condition : gl_enum_class<sync_condition, "SyncCondtn"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL sync flag bit constants.
/// @ingroup gl_api_wrap
export struct sync_flag_bit : gl_bitfield_class<sync_flag_bit, "SyncFlgBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL sync parameter constants.
/// @ingroup gl_api_wrap
export struct sync_parameter : gl_enum_class<sync_parameter, "SynParamtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL sync wait result constants.
/// @ingroup gl_api_wrap
export struct sync_wait_result : gl_enum_class<sync_wait_result, "SynWaitRes"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL shader type constants.
/// @ingroup gl_api_wrap
export struct shader_type : gl_enum_class<shader_type, "ShaderType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL shader parameter constants.
/// @ingroup gl_api_wrap
export struct shader_parameter : gl_enum_class<shader_parameter, "ShdrPrmter"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL program stage bit constants.
/// @ingroup gl_api_wrap
export struct program_stage_bit
  : gl_bitfield_class<program_stage_bit, "PrgStgeBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL program stage parameter constants.
/// @ingroup gl_api_wrap
export struct program_stage_parameter
  : gl_enum_class<program_stage_parameter, "PrgStgePrm"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL program parameter constants.
/// @ingroup gl_api_wrap
export struct program_parameter
  : gl_enum_class<program_parameter, "ProgPrmter"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL program binary format constants.
/// @ingroup gl_api_wrap
export struct program_binary_format
  : gl_enum_class<program_binary_format, "ProgBinFmt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL program pipeline parameter constants.
/// @ingroup gl_api_wrap
export struct program_pipeline_parameter
  : gl_enum_class<program_pipeline_parameter, "PiplPrmter"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL buffer bind target constants.
/// @ingroup gl_api_wrap
export struct buffer_target : gl_enum_class<buffer_target, "BufferTgt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL buffer parameter constants.
/// @ingroup gl_api_wrap
export struct buffer_parameter : gl_enum_class<buffer_parameter, "BufParmtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL buffer usage constants.
/// @ingroup gl_api_wrap
export struct buffer_usage : gl_enum_class<buffer_usage, "BufferUsge"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL buffer map access bit constants.
/// @ingroup gl_api_wrap
export struct buffer_map_access_bit
  : gl_bitfield_class<buffer_map_access_bit, "BufMapAccB"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL buffer storage bit constants.
/// @ingroup gl_api_wrap
export struct buffer_storage_bit
  : gl_bitfield_class<buffer_storage_bit, "BufStrgBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL program interface constants.
/// @ingroup gl_api_wrap
export struct program_interface
  : gl_enum_class<program_interface, "ProgrmIntf"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL program property constants.
/// @ingroup gl_api_wrap
export struct program_property : gl_enum_class<program_property, "ProgrmProp"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL buffer clear bit constants.
/// @ingroup gl_api_wrap
export struct buffer_clear_bit
  : gl_bitfield_class<buffer_clear_bit, "BufClerBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL buffer blit bit constants.
/// @ingroup gl_api_wrap
export struct buffer_blit_bit
  : gl_bitfield_class<buffer_blit_bit, "BufBlitBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture unit constants.
/// @ingroup gl_api_wrap
export struct texture_unit : gl_enum_class<texture_unit, "TexUnit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture bind target constants.
/// @ingroup gl_api_wrap
export struct texture_target : gl_enum_class<texture_target, "TexTarget"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture compare mode constants.
/// @ingroup gl_api_wrap
export struct texture_compare_mode
  : gl_enum_class<texture_compare_mode, "TexCmpMode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture minification filter constants.
/// @ingroup gl_api_wrap
export struct texture_min_filter
  : gl_enum_class<texture_min_filter, "TexMinFltr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture magnification filter constants.
/// @ingroup gl_api_wrap
export struct texture_mag_filter
  : gl_enum_class<texture_mag_filter, "TexMagFltr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture filter constants.
/// @ingroup gl_api_wrap
export struct texture_filter : gl_enum_class<texture_filter, "TexFilter"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture level parameter constants.
/// @ingroup gl_api_wrap
export struct texture_level_parameter
  : gl_enum_class<texture_level_parameter, "TexLvlParm"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture parameter constants.
/// @ingroup gl_api_wrap
export struct texture_parameter
  : gl_enum_class<texture_parameter, "TexParamtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture swizzle coordinate constants.
/// @ingroup gl_api_wrap
export struct texture_swizzle_coord
  : gl_enum_class<texture_swizzle_coord, "TexSwzCord"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture swizzle mode constants.
/// @ingroup gl_api_wrap
export struct texture_swizzle_mode
  : gl_enum_class<texture_swizzle_mode, "TexSwzMode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture wrap coordinate constants.
/// @ingroup gl_api_wrap
export struct texture_wrap_coord
  : gl_enum_class<texture_wrap_coord, "TexWrpCord"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL texture wrap mode constants.
/// @ingroup gl_api_wrap
export struct texture_wrap_mode
  : gl_enum_class<texture_wrap_mode, "TexWrpMode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL renderbuffer bind target constants.
/// @ingroup gl_api_wrap
export struct renderbuffer_target
  : gl_enum_class<renderbuffer_target, "RboTarget"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL renderbuffer parameter constants.
/// @ingroup gl_api_wrap
export struct renderbuffer_parameter
  : gl_enum_class<renderbuffer_parameter, "RboParamtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL framebuffer bind target constants.
/// @ingroup gl_api_wrap
export struct framebuffer_target
  : gl_enum_class<framebuffer_target, "FboTarget"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL framebuffer status constants.
/// @ingroup gl_api_wrap
export struct framebuffer_status
  : gl_enum_class<framebuffer_status, "FboStatus"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL framebuffer parameter constants.
/// @ingroup gl_api_wrap
export struct framebuffer_parameter
  : gl_enum_class<framebuffer_parameter, "FboParamtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL framebuffer attachment parameter constants.
/// @ingroup gl_api_wrap
export struct framebuffer_attachment_parameter
  : gl_enum_class<framebuffer_attachment_parameter, "FboAtchPar"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL framebuffer draw buffer constants.
/// @ingroup gl_api_wrap
export struct framebuffer_buffer
  : gl_enum_class<framebuffer_buffer, "FboBuffer"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL framebuffer attachment constants.
/// @ingroup gl_api_wrap
export struct framebuffer_attachment
  : gl_enum_class<framebuffer_attachment, "FboAttchmt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL sampler parameter constants.
/// @ingroup gl_api_wrap
export struct sampler_parameter
  : gl_enum_class<sampler_parameter, "SamParamtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL query target constants.
/// @ingroup gl_api_wrap
export struct query_target : gl_enum_class<query_target, "QryTarget"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL counter query target constants.
/// @ingroup gl_api_wrap
export struct counter_query_target
  : gl_enum_class<counter_query_target, "CntrQryTgt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL query parameter constants.
/// @ingroup gl_api_wrap
export struct query_parameter : gl_enum_class<query_parameter, "QryParamtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL transform feedback target constants.
/// @ingroup gl_api_wrap
export struct transform_feedback_target
  : gl_enum_class<transform_feedback_target, "XfbTarget"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL transform feedback primitive type constants.
/// @ingroup gl_api_wrap
export struct transform_feedback_primitive_type
  : gl_enum_class<transform_feedback_primitive_type, "XfbPrimTyp"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL transform feedback mode constants.
/// @ingroup gl_api_wrap
export struct transform_feedback_mode
  : gl_enum_class<transform_feedback_mode, "XfbMode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL transform feedback parameter constants.
/// @ingroup gl_api_wrap
export struct transform_feedback_parameter
  : gl_enum_class<transform_feedback_parameter, "XfbParamtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL vertex attribute parameter constants.
/// @ingroup gl_api_wrap
export struct vertex_attrib_parameter
  : gl_enum_class<vertex_attrib_parameter, "VAtrParmtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL primitive type constants.
/// @ingroup gl_api_wrap
export struct primitive_type : gl_enum_class<primitive_type, "PrmtveType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL legacy primitive type constants.
/// @ingroup gl_api_wrap
export struct old_primitive_type
  : gl_enum_class<old_primitive_type, "OldPrmType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL tessellation generator primitive type constants.
/// @ingroup gl_api_wrap
export struct tess_gen_primitive_type
  : gl_enum_class<tess_gen_primitive_type, "TsGnPrmTyp"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL tessellation generator primitive spacing constants.
/// @ingroup gl_api_wrap
export struct tess_gen_primitive_spacing
  : gl_enum_class<tess_gen_primitive_spacing, "TsGnPrmSpc"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL patch parameter constants.
/// @ingroup gl_api_wrap
export struct patch_parameter : gl_enum_class<patch_parameter, "PtchParmtr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL provoke mode constants.
/// @ingroup gl_api_wrap
export struct provoke_mode : gl_enum_class<provoke_mode, "ProvkeMode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL conditional render mode constants.
/// @ingroup gl_api_wrap
export struct conditional_render_mode
  : gl_enum_class<conditional_render_mode, "CndRndrMod"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL face mode constants.
/// @ingroup gl_api_wrap
export struct face_mode : gl_enum_class<face_mode, "FaceMode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL face orientation constants.
/// @ingroup gl_api_wrap
export struct face_orientation : gl_enum_class<face_orientation, "FaceOrient"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL draw surface buffer constants.
/// @ingroup gl_api_wrap
export struct surface_buffer : gl_enum_class<surface_buffer, "SrfceBuffr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL compare function constants.
/// @ingroup gl_api_wrap
export struct compare_function : gl_enum_class<compare_function, "ComparFunc"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL blit filter constants.
/// @ingroup gl_api_wrap
export struct blit_filter : gl_enum_class<blit_filter, "BlitFilter"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL binding query constants.
/// @ingroup gl_api_wrap
export struct binding_query : gl_enum_class<binding_query, "BindQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL integer query constants.
/// @ingroup gl_api_wrap
export struct integer_query : gl_enum_class<integer_query, "IntQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL floating-point query constants.
/// @ingroup gl_api_wrap
export struct float_query : gl_enum_class<float_query, "FloatQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL string query constants.
/// @ingroup gl_api_wrap
export struct string_query : gl_enum_class<string_query, "StrQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL named string query constants.
/// @ingroup gl_api_wrap
export struct named_string_query
  : gl_enum_class<named_string_query, "NmdStrQury"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL data type constants.
/// @ingroup gl_api_wrap
export struct data_type : gl_enum_class<data_type, "DataType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL index data type constants.
/// @ingroup gl_api_wrap
export struct index_data_type : gl_enum_class<index_data_type, "IdxDtaType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL shading language data type constants.
/// @ingroup gl_api_wrap
export struct sl_data_type : gl_enum_class<sl_data_type, "SLDataType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL point parameter constants.
/// @ingroup gl_api_wrap
export struct point_parameter : gl_enum_class<point_parameter, "PtParametr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL point sprite coord origin constants.
/// @ingroup gl_api_wrap
export struct point_sprite_coord_origin
  : gl_enum_class<point_sprite_coord_origin, "PtSprCrdOr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL polygon mode constants.
/// @ingroup gl_api_wrap
export struct polygon_mode : gl_enum_class<polygon_mode, "PolygnMode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL stencil operation constants.
/// @ingroup gl_api_wrap
export struct stencil_operation
  : gl_enum_class<stencil_operation, "StencilOp"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL logic operation constants.
/// @ingroup gl_api_wrap
export struct logic_operation : gl_enum_class<logic_operation, "LogicOp"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL blend equation constants.
/// @ingroup gl_api_wrap
export struct blend_equation : gl_enum_class<blend_equation, "BlendEqtn"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL advanced blend equation constants.
/// @ingroup gl_api_wrap
export struct blend_equation_advanced
  : gl_enum_class<blend_equation_advanced, "BlndEqAdvn"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL blend function constants.
/// @ingroup gl_api_wrap
export struct blend_function : gl_enum_class<blend_function, "BlendFunc"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL pixel data type constants.
/// @ingroup gl_api_wrap
export struct pixel_data_type : gl_enum_class<pixel_data_type, "PixDataTyp"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL pixel format constants.
/// @ingroup gl_api_wrap
export struct pixel_format : gl_enum_class<pixel_format, "PixelFrmat"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL image unit format constants.
/// @ingroup gl_api_wrap
export struct image_unit_format
  : gl_enum_class<image_unit_format, "ImgUnitFmt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL pixel internal format constants.
/// @ingroup gl_api_wrap
export struct pixel_internal_format
  : gl_enum_class<pixel_internal_format, "PixIntlFmt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL pixel store parameter constants.
/// @ingroup gl_api_wrap
export struct pixel_store_parameter
  : gl_enum_class<pixel_store_parameter, "PixStorPrm"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL internal format parameter constants.
/// @ingroup gl_api_wrap
export struct internal_format_parameter
  : gl_enum_class<internal_format_parameter, "IntlFmtPrm"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL image compatibility class constants.
/// @ingroup gl_api_wrap
export struct image_compatibility_class
  : gl_enum_class<image_compatibility_class, "ImCompClss"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL view compatibility class constants.
/// @ingroup gl_api_wrap
export struct view_compatibility_class
  : gl_enum_class<view_compatibility_class, "VwCompClss"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL sample parameter constants.
/// @ingroup gl_api_wrap
export struct sample_parameter : gl_enum_class<sample_parameter, "SampleParm"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL hint option constants.
/// @ingroup gl_api_wrap
export struct hint_option : gl_enum_class<hint_option, "HintOption"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL hint target constants.
/// @ingroup gl_api_wrap
export struct hint_target : gl_enum_class<hint_target, "HintTarget"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL debug output severity constants.
/// @ingroup gl_api_wrap
export struct debug_output_severity
  : gl_enum_class<debug_output_severity, "DbgOutSvrt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL debug output source constants.
/// @ingroup gl_api_wrap
export struct debug_output_source
  : gl_enum_class<debug_output_source, "DbgOutSrce"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL debug output type constants.
/// @ingroup gl_api_wrap
export struct debug_output_type
  : gl_enum_class<debug_output_type, "DbgOutType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL feature support level constants.
/// @ingroup gl_api_wrap
export struct support_level : gl_enum_class<support_level, "SupportLvl"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL named string kind constants.
/// @ingroup gl_api_wrap
export struct named_string_kind
  : gl_enum_class<named_string_kind, "NmdStrKind"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL legacy matrix mode constants.
/// @ingroup gl_api_wrap
export struct matrix_mode : gl_enum_class<matrix_mode, "MatrixMode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path command constants.
/// @ingroup gl_api_wrap
export struct path_command_nv : gl_ubyte_class<path_command_nv, "PathComand"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path cap style constants.
/// @ingroup gl_api_wrap
export struct path_cap_style_nv
  : gl_enum_class<path_cap_style_nv, "PathCapSty"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path color format constants.
/// @ingroup gl_api_wrap
export struct path_color_format_nv
  : gl_enum_class<path_color_format_nv, "PathClrFmt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path color constants.
/// @ingroup gl_api_wrap
export struct path_color_nv : gl_enum_class<path_color_nv, "PathColor"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path dash offset constants.
/// @ingroup gl_api_wrap
export struct path_dash_offset_reset_nv
  : gl_enum_class<path_dash_offset_reset_nv, "PathDsORst"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path stroke cover mode constants.
/// @ingroup gl_api_wrap
export struct path_stroke_cover_mode_nv
  : gl_enum_class<path_stroke_cover_mode_nv, "PathStCvrM"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path fill cover mode constants.
/// @ingroup gl_api_wrap
export struct path_fill_cover_mode_nv
  : gl_enum_class<path_fill_cover_mode_nv, "PathFlCvrM"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path fill mode constants.
/// @ingroup gl_api_wrap
export struct path_fill_mode_nv
  : gl_enum_class<path_fill_mode_nv, "PathFillMd"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path font style constants.
/// @ingroup gl_api_wrap
export struct path_font_style_nv
  : gl_bitfield_class<path_font_style_nv, "PathFntSty"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path join style constants.
/// @ingroup gl_api_wrap
export struct path_join_style_nv
  : gl_bitfield_class<path_join_style_nv, "PathJinSty"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path font target constants.
/// @ingroup gl_api_wrap
export struct path_font_target_nv
  : gl_enum_class<path_font_target_nv, "PathFntTgt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path format constants.
/// @ingroup gl_api_wrap
export struct path_format_nv : gl_enum_class<path_format_nv, "PathFormat"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path gen mode constants.
/// @ingroup gl_api_wrap
export struct path_gen_mode_nv : gl_enum_class<path_gen_mode_nv, "PathGenMod"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path list mode constants.
/// @ingroup gl_api_wrap
export struct path_list_mode_nv
  : gl_enum_class<path_list_mode_nv, "PathLstMod"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path metric query constants.
/// @ingroup gl_api_wrap
export struct path_metric_query_nv
  : gl_bitfield_class<path_metric_query_nv, "PathMrcQry"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path missing glyph constants.
/// @ingroup gl_api_wrap
export struct path_missing_glyph_nv
  : gl_bitfield_class<path_missing_glyph_nv, "PathMsnGph"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path parameter constants.
/// @ingroup gl_api_wrap
export struct path_parameter_nv
  : gl_bitfield_class<path_parameter_nv, "PathPrmter"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path text encoding constants.
/// @ingroup gl_api_wrap
export struct path_text_encoding_nv
  : gl_bitfield_class<path_text_encoding_nv, "PathTxtEnc"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for GL path transform type constants.
/// @ingroup gl_api_wrap
export struct path_transform_type_nv
  : gl_bitfield_class<path_transform_type_nv, "PathTrnsfT"> {
    using enum_class::enum_class;
};
//------------------------------------------------------------------------------
} // namespace eagine::oglplus

