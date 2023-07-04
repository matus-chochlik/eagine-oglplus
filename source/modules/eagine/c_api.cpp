/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#include "gl_def.hpp"

export module eagine.oglplus:c_api;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :result;

#ifndef OGLPLUS_GL_STATIC_FUNC
#if EAGINE_HAS_GL
#if defined(__GLEW_H__)
#define OGLPLUS_GL_STATIC_FUNC(NAME) nullptr
#else
#define OGLPLUS_GL_STATIC_FUNC(NAME) &gl##NAME
#endif
#else
#define OGLPLUS_GL_STATIC_FUNC(NAME) nullptr
#endif
#endif

namespace eagine::oglplus {
//------------------------------------------------------------------------------
/// @brief Class wrapping the C-functions from the GL API.
/// @ingroup gl_api_wrap
/// @see basic_gl_constants
/// @see basic_gl_operations
export template <typename ApiTraits>
class basic_gl_c_api {
    ApiTraits& _traits;

public:
    using this_api = basic_gl_c_api;

    /// @brief Alias for the API traits policy type passed as template argument.
    using api_traits = ApiTraits;

    /// @brief Untyped non-const pointer type.
    using void_ptr_type = typename gl_types::void_ptr_type;
    /// @brief Untyped const pointer type.
    using const_void_ptr_type = typename gl_types::const_void_ptr_type;
    /// @brief Size integer type.
    using sizei_type = typename gl_types::sizei_type;
    /// @brief Size integer type.
    using sizeiptr_type = typename gl_types::sizeiptr_type;
    /// @brief Integer type that can represent pointer.
    using intptr_type = typename gl_types::intptr_type;
    /// @brief Boolean type.
    using bool_type = typename gl_types::bool_type;
    /// @brief String character type.
    using char_type = typename gl_types::char_type;
    /// @brief Byte type.
    using byte_type = typename gl_types::byte_type;
    /// @brief Unsigned byte type.
    using ubyte_type = typename gl_types::ubyte_type;
    /// @brief Signed short integer type.
    using short_type = typename gl_types::short_type;
    /// @brief Unsigned short integer type.
    using ushort_type = typename gl_types::ushort_type;
    /// @brief Signed integer type.
    using int_type = typename gl_types::int_type;
    /// @brief Unsigned integer type.
    using uint_type = typename gl_types::uint_type;
    /// @brief Signed 64-bit integer type.
    using int64_type = typename gl_types::int64_type;
    /// @brief Unsigned 64-bit integer type.
    using uint64_type = typename gl_types::uint64_type;
    /// @brief Enumerator value type.
    using enum_type = typename gl_types::enum_type;
    /// @brief Floating-point type.
    using float_type = typename gl_types::float_type;
    /// @brief Double-precision floating-point type.
    using double_type = typename gl_types::double_type;
    /// @brief Bitfield/bitset value types.
    using bitfield_type = typename gl_types::bitfield_type;
    /// @brief Sync handler type.
    using sync_type = typename gl_types::sync_type;

    /// @brief Alias for the debug callback function type.
    using debug_callback_type = void(
      enum_type,
      enum_type,
      uint_type,
      enum_type,
      sizei_type,
      const char_type*,
      const_void_ptr_type);

    /// @brief Alias for GL C-API function wrapper template.
    template <
      typename Signature,
      c_api::function_ptr<api_traits, nothing_t, Signature> Function>
    using gl_api_function = c_api::opt_function<
      api_traits,
      nothing_t,
      Signature,
      Function,
      gl_types::has_api,
      gl_types::has_static_api>;

    template <typename Result, typename... U>
    constexpr auto check_result(Result res, U&&...) const noexcept {
        res.error_code(this->GetError());
        return res;
    }

    /// @var GetError
    /// @glfuncwrap{GetError}
    gl_api_function<enum_type(), OGLPLUS_GL_STATIC_FUNC(GetError)> GetError{
      "GetError",
      *this};

    /// @var GetGraphicsResetStatus
    /// @glfuncwrap{GetGraphicsResetStatus}
    gl_api_function<enum_type(), OGLPLUS_GL_STATIC_FUNC(GetGraphicsResetStatus)>
      GetGraphicsResetStatus{"GetGraphicsResetStatus", *this};

    /// @var Enable
    /// @glfuncwrap{Enable}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(Enable)> Enable{
      "Enable",
      *this};

    /// @var Enablei
    /// @glfuncwrap{Enablei}
    gl_api_function<void(enum_type, uint_type), OGLPLUS_GL_STATIC_FUNC(Enablei)>
      Enablei{"Enablei", *this};

    /// @var Disable
    /// @glfuncwrap{Disable}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(Disable)> Disable{
      "Disable",
      *this};

    /// @var Disablei
    /// @glfuncwrap{Disablei}
    gl_api_function<void(enum_type, uint_type), OGLPLUS_GL_STATIC_FUNC(Disablei)>
      Disablei{"Disablei", *this};

    /// @var IsEnabled
    /// @glfuncwrap{IsEnabled}
    gl_api_function<bool_type(enum_type), OGLPLUS_GL_STATIC_FUNC(IsEnabled)>
      IsEnabled{"IsEnabled", *this};

    /// @var IsEnabledi
    /// @glfuncwrap{IsEnabledi}
    gl_api_function<
      bool_type(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(IsEnabledi)>
      IsEnabledi{"IsEnabledi", *this};

    /// @var MemoryBarrier
    /// @glfuncwrap{MemoryBarrier}
    gl_api_function<void(bitfield_type), OGLPLUS_GL_STATIC_FUNC(MemoryBarrier)>
      MemoryBarrier{"MemoryBarrier", *this};

    /// @var MemoryBarrierByRegion
    /// @glfuncwrap{MemoryBarrierByRegion}
    gl_api_function<
      void(bitfield_type),
      OGLPLUS_GL_STATIC_FUNC(MemoryBarrierByRegion)>
      MemoryBarrierByRegion{"MemoryBarrierByRegion", *this};

    // object ops

    /// @var FenceSync
    /// @glfuncwrap{FenceSync}
    gl_api_function<
      sync_type(enum_type, bitfield_type),
      OGLPLUS_GL_STATIC_FUNC(FenceSync)>
      FenceSync{"FenceSync", *this};

    /// @var DeleteSync
    /// @glfuncwrap{DeleteSync}
    gl_api_function<void(sync_type), OGLPLUS_GL_STATIC_FUNC(DeleteSync)>
      DeleteSync{"DeleteSync", *this};

    /// @var IsSync
    /// @glfuncwrap{IsSync}
    gl_api_function<bool_type(sync_type), OGLPLUS_GL_STATIC_FUNC(IsSync)> IsSync{
      "IsSync",
      *this};

    /// @var GetSynciv
    /// @glfuncwrap{GetSynciv}
    gl_api_function<
      void(sync_type, enum_type, sizei_type, sizei_type*, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetSynciv)>
      GetSynciv{"GetSynciv", *this};

    /// @var WaitSync
    /// @glfuncwrap{WaitSync}
    gl_api_function<
      void(sync_type, bitfield_type, uint64_type),
      OGLPLUS_GL_STATIC_FUNC(WaitSync)>
      WaitSync{"WaitSync", *this};

    /// @var ClientWaitSync
    /// @glfuncwrap{ClientWaitSync}
    gl_api_function<
      enum_type(sync_type, bitfield_type, uint64_type),
      OGLPLUS_GL_STATIC_FUNC(ClientWaitSync)>
      ClientWaitSync{"ClientWaitSync", *this};

    /// @var GenVertexArrays
    /// @glfuncwrap{GenVertexArrays}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenVertexArrays)>
      GenVertexArrays{"GenVertexArrays", *this};

    /// @var CreateVertexArrays
    /// @glfuncwrap{CreateVertexArrays}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateVertexArrays)>
      CreateVertexArrays{"CreateVertexArrays", *this};

    /// @var DeleteVertexArrays
    /// @glfuncwrap{DeleteVertexArrays}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteVertexArrays)>
      DeleteVertexArrays{"DeleteVertexArrays", *this};

    /// @var IsVertexArray
    /// @glfuncwrap{IsVertexArray}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsVertexArray)>
      IsVertexArray{"IsVertexArray", *this};

    /// @var BindVertexArray
    /// @glfuncwrap{BindVertexArray}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(BindVertexArray)>
      BindVertexArray{"BindVertexArray", *this};

    /// @var VertexArrayElementBuffer
    /// @glfuncwrap{VertexArrayElementBuffer}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexArrayElementBuffer)>
      VertexArrayElementBuffer{"VertexArrayElementBuffer", *this};

    /// @var BindVertexBuffer
    /// @glfuncwrap{BindVertexBuffer}
    gl_api_function<
      void(uint_type, uint_type, intptr_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(BindVertexBuffer)>
      BindVertexBuffer{"BindVertexBuffer", *this};

    /// @var VertexArrayVertexBuffer
    /// @glfuncwrap{VertexArrayVertexBuffer}
    gl_api_function<
      void(uint_type, uint_type, uint_type, intptr_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(VertexArrayVertexBuffer)>
      VertexArrayVertexBuffer{"VertexArrayVertexBuffer", *this};

    /// @var BindVertexBuffers
    /// @glfuncwrap{BindVertexBuffers}
    gl_api_function<
      void(
        uint_type,
        sizei_type,
        const uint_type*,
        const intptr_type*,
        const sizei_type*),
      OGLPLUS_GL_STATIC_FUNC(BindVertexBuffers)>
      BindVertexBuffers{"BindVertexBuffers", *this};

    /// @var VertexArrayVertexBuffers
    /// @glfuncwrap{VertexArrayVertexBuffers}
    gl_api_function<
      void(
        uint_type,
        uint_type,
        sizei_type,
        const uint_type*,
        const intptr_type*,
        const sizei_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexArrayVertexBuffers)>
      VertexArrayVertexBuffers{"VertexArrayVertexBuffers", *this};

    /// @var VertexAttribBinding
    /// @glfuncwrap{VertexAttribBinding}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribBinding)>
      VertexAttribBinding{"VertexAttribBinding", *this};

    /// @var VertexArrayAttribBinding
    /// @glfuncwrap{VertexArrayAttribBinding}
    gl_api_function<
      void(uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexArrayAttribBinding)>
      VertexArrayAttribBinding{"VertexArrayAttribBinding", *this};

    /// @var EnableVertexAttribArray
    /// @glfuncwrap{EnableVertexAttribArray}
    gl_api_function<
      void(uint_type),
      OGLPLUS_GL_STATIC_FUNC(EnableVertexAttribArray)>
      EnableVertexAttribArray{"EnableVertexAttribArray", *this};

    /// @var EnableVertexArrayAttrib
    /// @glfuncwrap{EnableVertexArrayAttrib}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(EnableVertexArrayAttrib)>
      EnableVertexArrayAttrib{"EnableVertexArrayAttrib", *this};

    /// @var DisableVertexAttribArray
    /// @glfuncwrap{DisableVertexAttribArray}
    gl_api_function<
      void(uint_type),
      OGLPLUS_GL_STATIC_FUNC(DisableVertexAttribArray)>
      DisableVertexAttribArray{"DisableVertexAttribArray", *this};

    /// @var DisableVertexArrayAttrib
    /// @glfuncwrap{DisableVertexArrayAttrib}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(DisableVertexArrayAttrib)>
      DisableVertexArrayAttrib{"DisableVertexArrayAttrib", *this};

    /// @var VertexBindingDivisor
    /// @glfuncwrap{VertexBindingDivisor}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexBindingDivisor)>
      VertexBindingDivisor{"VertexBindingDivisor", *this};

    /// @var VertexArrayBindingDivisor
    /// @glfuncwrap{VertexArrayBindingDivisor}
    gl_api_function<
      void(uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexArrayBindingDivisor)>
      VertexArrayBindingDivisor{"VertexArrayBindingDivisor", *this};

    /// @var VertexAttribDivisor
    /// @glfuncwrap{VertexAttribDivisor}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribDivisor)>
      VertexAttribDivisor{"VertexAttribDivisor", *this};

    /// @var GenBuffers
    /// @glfuncwrap{GenBuffers}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenBuffers)>
      GenBuffers{"GenBuffers", *this};

    /// @var CreateBuffers
    /// @glfuncwrap{CreateBuffers}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateBuffers)>
      CreateBuffers{"CreateBuffers", *this};

    /// @var DeleteBuffers
    /// @glfuncwrap{DeleteBuffers}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteBuffers)>
      DeleteBuffers{"DeleteBuffers", *this};

    /// @var IsBuffer
    /// @glfuncwrap{IsBuffer}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsBuffer)>
      IsBuffer{"IsBuffer", *this};

    /// @var BindBuffer
    /// @glfuncwrap{BindBuffer}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BindBuffer)>
      BindBuffer{"BindBuffer", *this};

    /// @var BindBufferBase
    /// @glfuncwrap{BindBufferBase}
    gl_api_function<
      void(enum_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BindBufferBase)>
      BindBufferBase{"BindBufferBase", *this};

    /// @var BindBufferRange
    /// @glfuncwrap{BindBufferRange}
    gl_api_function<
      void(enum_type, uint_type, uint_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(BindBufferRange)>
      BindBufferRange{"BindBufferRange", *this};

    /// @var BufferStorage
    /// @glfuncwrap{BufferStorage}
    gl_api_function<
      void(enum_type, sizeiptr_type, const_void_ptr_type, bitfield_type),
      OGLPLUS_GL_STATIC_FUNC(BufferStorage)>
      BufferStorage{"BufferStorage", *this};

    /// @var NamedBufferStorage
    /// @glfuncwrap{NamedBufferStorage}
    gl_api_function<
      void(uint_type, sizeiptr_type, const_void_ptr_type, bitfield_type),
      OGLPLUS_GL_STATIC_FUNC(BufferStorage)>
      NamedBufferStorage{"NamedBufferStorage", *this};

    /// @var BufferData
    /// @glfuncwrap{BufferData}
    gl_api_function<
      void(enum_type, sizeiptr_type, const_void_ptr_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BufferData)>
      BufferData{"BufferData", *this};

    /// @var NamedBufferData
    /// @glfuncwrap{NamedBufferData}
    gl_api_function<
      void(uint_type, sizeiptr_type, const_void_ptr_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(NamedBufferData)>
      NamedBufferData{"NamedBufferData", *this};

    /// @var BufferSubData
    /// @glfuncwrap{BufferSubData}
    gl_api_function<
      void(enum_type, intptr_type, sizeiptr_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(BufferSubData)>
      BufferSubData{"BufferSubData", *this};

    /// @var NamedBufferSubData
    /// @glfuncwrap{NamedBufferSubData}
    gl_api_function<
      void(uint_type, intptr_type, sizeiptr_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(NamedBufferSubData)>
      NamedBufferSubData{"NamedBufferSubData", *this};

    /// @var ClearBufferSubData
    /// @glfuncwrap{ClearBufferSubData}
    gl_api_function<
      void(enum_type, enum_type, enum_type, enum_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(ClearBufferData)>
      ClearBufferData{"ClearBufferData", *this};

    /// @var ClearNamedBufferData
    /// @glfuncwrap{ClearNamedBufferData}
    gl_api_function<
      void(uint_type, enum_type, enum_type, enum_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(ClearNamedBufferData)>
      ClearNamedBufferData{"ClearNamedBufferData", *this};

    /// @var ClearBufferSubData
    /// @glfuncwrap{ClearBufferSubData}
    gl_api_function<
      void(
        enum_type,
        enum_type,
        intptr_type,
        sizeiptr_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(ClearBufferSubData)>
      ClearBufferSubData{"ClearBufferSubData", *this};

    /// @var ClearNamedBufferSubData
    /// @glfuncwrap{ClearNamedBufferSubData}
    gl_api_function<
      void(
        uint_type,
        enum_type,
        intptr_type,
        sizeiptr_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(ClearNamedBufferSubData)>
      ClearNamedBufferSubData{"ClearNamedBufferSubData", *this};

    /// @var MapBuffer
    /// @glfuncwrap{MapBuffer}
    gl_api_function<
      void_ptr_type(enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(MapBuffer)>
      MapBuffer{"MapBuffer", *this};

    /// @var MapNamedBuffer
    /// @glfuncwrap{MapNamedBuffer}
    gl_api_function<
      void_ptr_type(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(MapNamedBuffer)>
      MapNamedBuffer{"MapNamedBuffer", *this};

    /// @var MapBufferRange
    /// @glfuncwrap{MapBufferRange}
    gl_api_function<
      void_ptr_type(enum_type, intptr_type, sizeiptr_type, bitfield_type),
      OGLPLUS_GL_STATIC_FUNC(MapBufferRange)>
      MapBufferRange{"MapBufferRange", *this};

    /// @var MapNamedBufferRange
    /// @glfuncwrap{MapNamedBufferRange}
    gl_api_function<
      void_ptr_type(uint_type, intptr_type, sizeiptr_type, bitfield_type),
      OGLPLUS_GL_STATIC_FUNC(MapNamedBufferRange)>
      MapNamedBufferRange{"MapNamedBufferRange", *this};

    /// @var FlushMappedBufferRange
    /// @glfuncwrap{FlushMappedBufferRange}
    gl_api_function<
      void(enum_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(FlushMappedBufferRange)>
      FlushMappedBufferRange{"FlushMappedBufferRange", *this};

    /// @var FlushMappedNamedBufferRange
    /// @glfuncwrap{FlushMappedNamedBufferRange}
    gl_api_function<
      void(uint_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(FlushMappedNamedBufferRange)>
      FlushMappedNamedBufferRange{"FlushMappedNamedBufferRange", *this};

    /// @var UnmapBuffer
    /// @glfuncwrap{UnmapBuffer}
    gl_api_function<bool_type(enum_type), OGLPLUS_GL_STATIC_FUNC(UnmapBuffer)>
      UnmapBuffer{"UnmapBuffer", *this};

    /// @var UnmapNamedBuffer
    /// @glfuncwrap{UnmapNamedBuffer}
    gl_api_function<
      bool_type(uint_type),
      OGLPLUS_GL_STATIC_FUNC(UnmapNamedBuffer)>
      UnmapNamedBuffer{"UnmapNamedBuffer", *this};

    /// @var InvalidateBufferData
    /// @glfuncwrap{InvalidateBufferData}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(InvalidateBufferData)>
      InvalidateBufferData{"InvalidateBufferData", *this};

    /// @var InvalidateBufferSubData
    /// @glfuncwrap{InvalidateBufferSubData}
    gl_api_function<
      void(uint_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(InvalidateBufferSubData)>
      InvalidateBufferSubData{"InvalidateBufferSubData", *this};

    /// @var CopyBufferSubData
    /// @glfuncwrap{CopyBufferSubData}
    gl_api_function<
      void(enum_type, enum_type, intptr_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(CopyBufferSubData)>
      CopyBufferSubData{"CopyBufferSubData", *this};

    /// @var CopyNamedBufferSubData
    /// @glfuncwrap{CopyNamedBufferSubData}
    gl_api_function<
      void(uint_type, uint_type, intptr_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(CopyNamedBufferSubData)>
      CopyNamedBufferSubData{"CopyNamedBufferSubData", *this};

    /// @var GetBufferParameteriv
    /// @glfuncwrap{GetBufferParameteriv}
    gl_api_function<
      void(enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetBufferParameteriv)>
      GetBufferParameteriv{"GetBufferParameteriv", *this};

    /// @var GetBufferParameteri64v
    /// @glfuncwrap{GetBufferParameteri64v}
    gl_api_function<
      void(enum_type, enum_type, int64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetBufferParameteri64v)>
      GetBufferParameteri64v{"GetBufferParameteri64v", *this};

    /// @var GetNamedBufferParameteriv
    /// @glfuncwrap{GetNamedBufferParameteriv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetNamedBufferParameteriv)>
      GetNamedBufferParameteriv{"GetNamedBufferParameteriv", *this};

    /// @var GetNamedBufferParameteri64v
    /// @glfuncwrap{GetNamedBufferParameteri64v}
    gl_api_function<
      void(uint_type, enum_type, int64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetNamedBufferParameteri64v)>
      GetNamedBufferParameteri64v{"GetNamedBufferParameteri64v", *this};

    /// @var GetBufferSubData
    /// @glfuncwrap{GetBufferSubData}
    gl_api_function<
      void(enum_type, intptr_type, sizeiptr_type, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetBufferSubData)>
      GetBufferSubData{"GetBufferSubData", *this};

    /// @var GetNamedBufferSubData
    /// @glfuncwrap{GetNamedBufferSubData}
    gl_api_function<
      void(uint_type, intptr_type, sizeiptr_type, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetNamedBufferSubData)>
      GetNamedBufferSubData{"GetNamedBufferSubData", *this};

    /// @var GenTextures
    /// @glfuncwrap{GenTextures}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenTextures)>
      GenTextures{"GenTextures", *this};

    /// @var CreateTextures
    /// @glfuncwrap{CreateTextures}
    gl_api_function<
      void(enum_type, sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateTextures)>
      CreateTextures{"CreateTextures", *this};

    /// @var DeleteTextures
    /// @glfuncwrap{DeleteTextures}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteTextures)>
      DeleteTextures{"DeleteTextures", *this};

    /// @var IsTexture
    /// @glfuncwrap{IsTexture}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsTexture)>
      IsTexture{"IsTexture", *this};

    /// @var ActiveTexture
    /// @glfuncwrap{ActiveTexture}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(ActiveTexture)>
      ActiveTexture{"ActiveTexture", *this};

    /// @var BindTexture
    /// @glfuncwrap{BindTexture}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BindTexture)>
      BindTexture{"BindTexture", *this};

    /// @var BindTextures
    /// @glfuncwrap{BindTextures}
    gl_api_function<
      void(uint_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(BindTextures)>
      BindTextures{"BindTextures", *this};

    /// @var BindTextureUnit
    /// @glfuncwrap{BindTextureUnit}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BindTextureUnit)>
      BindTextureUnit{"BindTextureUnit", *this};

    /// @var BindImageTexture
    /// @glfuncwrap{BindImageTexture}
    gl_api_function<
      void(uint_type, uint_type, int_type, bool_type, int_type, enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BindImageTexture)>
      BindImageTexture{"BindImageTexture", *this};

    /// @var BindImageTextures
    /// @glfuncwrap{BindImageTextures}
    gl_api_function<
      void(uint_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(BindImageTextures)>
      BindImageTextures{"BindImageTextures", *this};

    /// @var TexStorage3D
    /// @glfuncwrap{TexStorage3D}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, sizei_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(TexStorage3D)>
      TexStorage3D{"TexStorage3D", *this};

    /// @var TexStorage2D
    /// @glfuncwrap{TexStorage2D}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(TexStorage2D)>
      TexStorage2D{"TexStorage2D", *this};

    /// @var TexStorage1D
    /// @glfuncwrap{TexStorage1D}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(TexStorage1D)>
      TexStorage1D{"TexStorage1D", *this};

    /// @var TexStorage3DMultisample
    /// @glfuncwrap{TexStorage3DMultisample}
    gl_api_function<
      void(
        enum_type,
        sizei_type,
        enum_type,
        sizei_type,
        sizei_type,
        sizei_type,
        bool_type),
      OGLPLUS_GL_STATIC_FUNC(TexStorage3DMultisample)>
      TexStorage3DMultisample{"TexStorage3DMultisample", *this};

    /// @var TexStorage2DMultisample
    /// @glfuncwrap{TexStorage2DMultisample}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, sizei_type, sizei_type, bool_type),
      OGLPLUS_GL_STATIC_FUNC(TexStorage2DMultisample)>
      TexStorage2DMultisample{"TexStorage2DMultisample", *this};

    /// @var TexImage3D
    /// @glfuncwrap{TexImage3D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        int_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TexImage3D)>
      TexImage3D{"TexImage3D", *this};

    /// @var TexImage2D
    /// @glfuncwrap{TexImage2D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        int_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TexImage2D)>
      TexImage2D{"TexImage2D", *this};

    /// @var TexImage1D
    /// @glfuncwrap{TexImage1D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        sizei_type,
        int_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TexImage1D)>
      TexImage1D{"TexImage1D", *this};

    /// @var CopyTexImage2D
    /// @glfuncwrap{CopyTexImage2D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        enum_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        int_type),
      OGLPLUS_GL_STATIC_FUNC(CopyTexImage2D)>
      CopyTexImage2D{"CopyTexImage2D", *this};

    /// @var CopyTexImage1D
    /// @glfuncwrap{CopyTexImage1D}
    gl_api_function<
      void(enum_type, int_type, enum_type, int_type, int_type, sizei_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(CopyTexImage1D)>
      CopyTexImage1D{"CopyTexImage1D", *this};

    /// @var TexSubImage3D
    /// @glfuncwrap{TexSubImage3D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TexSubImage3D)>
      TexSubImage3D{"TexSubImage3D", *this};

    /// @var TexSubImage2D
    /// @glfuncwrap{TexSubImage2D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TexSubImage2D)>
      TexSubImage2D{"TexSubImage2D", *this};

    /// @var TexSubImage1D
    /// @glfuncwrap{TexSubImage1D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        sizei_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TexSubImage1D)>
      TexSubImage1D{"TexSubImage1D", *this};

    /// @var CopyTexSubImage3D
    /// @glfuncwrap{CopyTexSubImage3D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(CopyTexSubImage3D)>
      CopyTexSubImage3D{"CopyTexSubImage3D", *this};

    /// @var CopyTexSubImage2D
    /// @glfuncwrap{CopyTexSubImage2D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(CopyTexSubImage2D)>
      CopyTexSubImage2D{"CopyTexSubImage2D", *this};

    /// @var CopyTexSubImage1D
    /// @glfuncwrap{CopyTexSubImage1D}
    gl_api_function<
      void(enum_type, int_type, int_type, int_type, int_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(CopyTexSubImage1D)>
      CopyTexSubImage1D{"CopyTexSubImage1D", *this};

    /// @var TextureStorage3D
    /// @glfuncwrap{TextureStorage3D}
    gl_api_function<
      void(uint_type, sizei_type, enum_type, sizei_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(TextureStorage3D)>
      TextureStorage3D{"TextureStorage3D", *this};

    /// @var TextureStorage2D
    /// @glfuncwrap{TextureStorage2D}
    gl_api_function<
      void(uint_type, sizei_type, enum_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(TextureStorage2D)>
      TextureStorage2D{"TextureStorage2D", *this};

    /// @var TextureStorage1D
    /// @glfuncwrap{TextureStorage1D}
    gl_api_function<
      void(uint_type, sizei_type, enum_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(TextureStorage1D)>
      TextureStorage1D{"TextureStorage1D", *this};

    /// @var TextureStorage3DMultisample
    /// @glfuncwrap{TextureStorage3DMultisample}
    gl_api_function<
      void(
        uint_type,
        sizei_type,
        enum_type,
        sizei_type,
        sizei_type,
        sizei_type,
        bool_type),
      OGLPLUS_GL_STATIC_FUNC(TextureStorage3DMultisample)>
      TextureStorage3DMultisample{"TextureStorage3DMultisample", *this};

    /// @var TextureStorage2DMultisample
    /// @glfuncwrap{TextureStorage2DMultisample}
    gl_api_function<
      void(uint_type, sizei_type, enum_type, sizei_type, sizei_type, bool_type),
      OGLPLUS_GL_STATIC_FUNC(TextureStorage2DMultisample)>
      TextureStorage2DMultisample{"TextureStorage2DMultisample", *this};

    /// @var TextureSubImage3D
    /// @glfuncwrap{TextureSubImage3D}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TextureSubImage3D)>
      TextureSubImage3D{"TextureSubImage3D", *this};

    /// @var TextureSubImage2D
    /// @glfuncwrap{TextureSubImage2D}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TextureSubImage2D)>
      TextureSubImage2D{"TextureSubImage2D", *this};

    /// @var TextureSubImage1D
    /// @glfuncwrap{TextureSubImage1D}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        sizei_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(TextureSubImage1D)>
      TextureSubImage1D{"TextureSubImage1D", *this};

    /// @var CopyTextureSubImage3D
    /// @glfuncwrap{CopyTextureSubImage3D}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(CopyTextureSubImage3D)>
      CopyTextureSubImage3D{"CopyTextureSubImage3D", *this};

    /// @var CopyTextureSubImage2D
    /// @glfuncwrap{CopyTextureSubImage2D}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(CopyTextureSubImage2D)>
      CopyTextureSubImage2D{"CopyTextureSubImage2D", *this};

    /// @var CopyTextureSubImage1D
    /// @glfuncwrap{CopyTextureSubImage1D}
    gl_api_function<
      void(uint_type, int_type, int_type, int_type, int_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(CopyTextureSubImage1D)>
      CopyTextureSubImage1D{"CopyTextureSubImage1D", *this};

    /// @var CompressedTexImage3D
    /// @glfuncwrap{CompressedTexImage3D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        enum_type,
        sizei_type,
        sizei_type,
        sizei_type,
        int_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTexImage3D)>
      CompressedTexImage3D{"CompressedTexImage3D", *this};

    /// @var CompressedTexImage2D
    /// @glfuncwrap{CompressedTexImage2D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        enum_type,
        sizei_type,
        sizei_type,
        int_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTexImage2D)>
      CompressedTexImage2D{"CompressedTexImage2D", *this};

    /// @var CompressedTexImage1D
    /// @glfuncwrap{CompressedTexImage1D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        enum_type,
        sizei_type,
        int_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTexImage1D)>
      CompressedTexImage1D{"CompressedTexImage1D", *this};

    /// @var CompressedTexSubImage3D
    /// @glfuncwrap{CompressedTexSubImage3D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        enum_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTexSubImage3D)>
      CompressedTexSubImage3D{"CompressedTexSubImage3D", *this};

    /// @var CompressedTexSubImage2D
    /// @glfuncwrap{CompressedTexSubImage2D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        enum_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTexSubImage2D)>
      CompressedTexSubImage2D{"CompressedTexSubImage2D", *this};

    /// @var CompressedTexSubImage1D
    /// @glfuncwrap{CompressedTexSubImage1D}
    gl_api_function<
      void(
        enum_type,
        int_type,
        int_type,
        sizei_type,
        enum_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTexSubImage1D)>
      CompressedTexSubImage1D{"CompressedTexSubImage1D", *this};

    /// @var CompressedTextureSubImage3D
    /// @glfuncwrap{CompressedTextureSubImage3D}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        enum_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTextureSubImage3D)>
      CompressedTextureSubImage3D{"CompressedTextureSubImage3D", *this};

    /// @var CompressedTextureSubImage2D
    /// @glfuncwrap{CompressedTextureSubImage2D}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        enum_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTextureSubImage2D)>
      CompressedTextureSubImage2D{"CompressedTextureSubImage2D", *this};

    /// @var CompressedTextureSubImage1D
    /// @glfuncwrap{CompressedTextureSubImage1D}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        sizei_type,
        enum_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(CompressedTextureSubImage1D)>
      CompressedTextureSubImage1D{"CompressedTextureSubImage1D", *this};

    /// @var TexImage3DMultisample
    /// @glfuncwrap{TexImage3DMultisample}
    gl_api_function<
      void(
        enum_type,
        sizei_type,
        enum_type,
        sizei_type,
        sizei_type,
        sizei_type,
        bool_type),
      OGLPLUS_GL_STATIC_FUNC(TexImage3DMultisample)>
      TexImage3DMultisample{"TexImage3DMultisample", *this};

    /// @var TexImage2DMultisample
    /// @glfuncwrap{TexImage2DMultisample}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, sizei_type, sizei_type, bool_type),
      OGLPLUS_GL_STATIC_FUNC(TexImage2DMultisample)>
      TexImage2DMultisample{"TexImage2DMultisample", *this};

    /// @var TexBuffer
    /// @glfuncwrap{TexBuffer}
    gl_api_function<
      void(enum_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(TexBuffer)>
      TexBuffer{"TexBuffer", *this};

    /// @var TexBufferRange
    /// @glfuncwrap{TexBufferRange}
    gl_api_function<
      void(enum_type, enum_type, uint_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(TexBufferRange)>
      TexBufferRange{"TexBufferRange", *this};

    /// @var TextureBuffer
    /// @glfuncwrap{TextureBuffer}
    gl_api_function<
      void(uint_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(TextureBuffer)>
      TextureBuffer{"TextureBuffer", *this};

    /// @var TextureBufferRange
    /// @glfuncwrap{TextureBufferRange}
    gl_api_function<
      void(uint_type, enum_type, uint_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(TextureBufferRange)>
      TextureBufferRange{"TextureBufferRange", *this};

    /// @var TexParameterf
    /// @glfuncwrap{TexParameterf}
    gl_api_function<
      void(enum_type, enum_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(TexParameterf)>
      TexParameterf{"TexParameterf", *this};

    /// @var TexParameteri
    /// @glfuncwrap{TexParameteri}
    gl_api_function<
      void(enum_type, enum_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(TexParameteri)>
      TexParameteri{"TexParameteri", *this};

    /// @var TexParameterfv
    /// @glfuncwrap{TexParameterfv}
    gl_api_function<
      void(enum_type, enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(TexParameterfv)>
      TexParameterfv{"TexParameterfv", *this};

    /// @var TexParameteriv
    /// @glfuncwrap{TexParameteriv}
    gl_api_function<
      void(enum_type, enum_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(TexParameteriv)>
      TexParameteriv{"TexParameteriv", *this};

    /// @var TexParameterIiv
    /// @glfuncwrap{TexParameterIiv}
    gl_api_function<
      void(enum_type, enum_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(TexParameterIiv)>
      TexParameterIiv{"TexParameterIiv", *this};

    /// @var TexParameterIuiv
    /// @glfuncwrap{TexParameterIuiv}
    gl_api_function<
      void(enum_type, enum_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(TexParameterIuiv)>
      TexParameterIuiv{"TexParameterIuiv", *this};

    /// @var TextureParameterf
    /// @glfuncwrap{TextureParameterf}
    gl_api_function<
      void(uint_type, enum_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(TextureParameterf)>
      TextureParameterf{"TextureParameterf", *this};

    /// @var TextureParameteri
    /// @glfuncwrap{TextureParameteri}
    gl_api_function<
      void(uint_type, enum_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(TextureParameteri)>
      TextureParameteri{"TextureParameteri", *this};

    /// @var TextureParameterfv
    /// @glfuncwrap{TextureParameterfv}
    gl_api_function<
      void(uint_type, enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(TextureParameterfv)>
      TextureParameterfv{"TextureParameterfv", *this};

    /// @var TextureParameteriv
    /// @glfuncwrap{TextureParameteriv}
    gl_api_function<
      void(uint_type, enum_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(TextureParameteriv)>
      TextureParameteriv{"TextureParameteriv", *this};

    /// @var TextureParameterIiv
    /// @glfuncwrap{TextureParameterIiv}
    gl_api_function<
      void(uint_type, enum_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(TextureParameterIiv)>
      TextureParameterIiv{"TextureParameterIiv", *this};

    /// @var TextureParameterIuiv
    /// @glfuncwrap{TextureParameterIuiv}
    gl_api_function<
      void(uint_type, enum_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(TextureParameterIuiv)>
      TextureParameterIuiv{"TextureParameterIuiv", *this};

    /// @var GetTexParameterfv
    /// @glfuncwrap{GetTexParameterfv}
    gl_api_function<
      void(enum_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTexParameterfv)>
      GetTexParameterfv{"GetTexParameterfv", *this};

    /// @var GetTexParameteriv
    /// @glfuncwrap{GetTexParameteriv}
    gl_api_function<
      void(enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTexParameteriv)>
      GetTexParameteriv{"GetTexParameteriv", *this};

    /// @var GetTexParameterIiv
    /// @glfuncwrap{GetTexParameterIiv}
    gl_api_function<
      void(enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTexParameterIiv)>
      GetTexParameterIiv{"GetTexParameterIiv", *this};

    /// @var GetTexParameterIuiv
    /// @glfuncwrap{GetTexParameterIuiv}
    gl_api_function<
      void(enum_type, enum_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTexParameterIuiv)>
      GetTexParameterIuiv{"GetTexParameterIuiv", *this};

    /// @var GetTexLevelParameterfv
    /// @glfuncwrap{GetTexLevelParameterfv}
    gl_api_function<
      void(enum_type, int_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTexLevelParameterfv)>
      GetTexLevelParameterfv{"GetTexLevelParameterfv", *this};

    /// @var GetTexLevelParameteriv
    /// @glfuncwrap{GetTexLevelParameteriv}
    gl_api_function<
      void(enum_type, int_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTexLevelParameteriv)>
      GetTexLevelParameteriv{"GetTexLevelParameteriv", *this};

    /// @var GetTexImage
    /// @glfuncwrap{GetTexImage}
    gl_api_function<
      void(enum_type, int_type, enum_type, enum_type, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetTexImage)>
      GetTexImage{"GetTexImage", *this};

    /// @var GetnTexImage
    /// @glfuncwrap{GetnTexImage}
    gl_api_function<
      void(enum_type, int_type, enum_type, enum_type, sizei_type, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetnTexImage)>
      GetnTexImage{"GetnTexImage", *this};

    /// @var GetCompressedTexImage
    /// @glfuncwrap{GetCompressedTexImage}
    gl_api_function<
      void(enum_type, int_type, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetCompressedTexImage)>
      GetCompressedTexImage{"GetCompressedTexImage", *this};

    /// @var GetnCompressedTexImage
    /// @glfuncwrap{GetnCompressedTexImage}
    gl_api_function<
      void(enum_type, int_type, sizei_type, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetnCompressedTexImage)>
      GetnCompressedTexImage{"GetnCompressedTexImage", *this};

    /// @var GetTextureParameterfv
    /// @glfuncwrap{GetTextureParameterfv}
    gl_api_function<
      void(uint_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTextureParameterfv)>
      GetTextureParameterfv{"GetTextureParameterfv", *this};

    /// @var GetTextureParameteriv
    /// @glfuncwrap{GetTextureParameteriv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTextureParameteriv)>
      GetTextureParameteriv{"GetTextureParameteriv", *this};

    /// @var GetTextureParameterIiv
    /// @glfuncwrap{GetTextureParameterIiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTextureParameterIiv)>
      GetTextureParameterIiv{"GetTextureParameterIiv", *this};

    /// @var GetTextureParameterIuiv
    /// @glfuncwrap{GetTextureParameterIuiv}
    gl_api_function<
      void(uint_type, enum_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTextureParameterIuiv)>
      GetTextureParameterIuiv{"GetTextureParameterIuiv", *this};

    /// @var GetTextureLevelParameterfv
    /// @glfuncwrap{GetTextureLevelParameterfv}
    gl_api_function<
      void(uint_type, int_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTextureLevelParameterfv)>
      GetTextureLevelParameterfv{"GetTextureLevelParameterfv", *this};

    /// @var GetTextureLevelParameteriv
    /// @glfuncwrap{GetTextureLevelParameteriv}
    gl_api_function<
      void(uint_type, int_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTextureLevelParameteriv)>
      GetTextureLevelParameteriv{"GetTextureLevelParameteriv", *this};

    /// @var GetTextureImage
    /// @glfuncwrap{GetTextureImage}
    gl_api_function<
      void(uint_type, int_type, enum_type, enum_type, sizei_type, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetTextureImage)>
      GetTextureImage{"GetTextureImage", *this};

    /// @var GetTextureSubImage
    /// @glfuncwrap{GetTextureSubImage}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        enum_type,
        enum_type,
        sizei_type,
        void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetTextureSubImage)>
      GetTextureSubImage{"GetTextureSubImage", *this};

    /// @var GetCompressedTextureImage
    /// @glfuncwrap{GetCompressedTextureImage}
    gl_api_function<
      void(uint_type, int_type, sizei_type, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetCompressedTextureImage)>
      GetCompressedTextureImage{"GetCompressedTextureImage", *this};

    /// @var GetCompressedTextureSubImage
    /// @glfuncwrap{GetCompressedTextureSubImage}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        sizei_type,
        void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetCompressedTextureSubImage)>
      GetCompressedTextureSubImage{"GetCompressedTextureSubImage", *this};

    /// @var GenerateMipmap
    /// @glfuncwrap{GenerateMipmap}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(GenerateMipmap)>
      GenerateMipmap{"GenerateMipmap", *this};

    /// @var GenerateTextureMipmap
    /// @glfuncwrap{GenerateTextureMipmap}
    gl_api_function<
      void(uint_type),
      OGLPLUS_GL_STATIC_FUNC(GenerateTextureMipmap)>
      GenerateTextureMipmap{"GenerateTextureMipmap", *this};

    /// @var TextureView
    /// @glfuncwrap{TextureView}
    gl_api_function<
      void(
        uint_type,
        enum_type,
        uint_type,
        enum_type,
        uint_type,
        uint_type,
        uint_type,
        uint_type),
      OGLPLUS_GL_STATIC_FUNC(TextureView)>
      TextureView{"TextureView", *this};

    /// @var InvalidateTexSubImage
    /// @glfuncwrap{InvalidateTexSubImage}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(InvalidateTexSubImage)>
      InvalidateTexSubImage{"InvalidateTexSubImage", *this};

    /// @var InvalidateTexImage
    /// @glfuncwrap{InvalidateTexImage}
    gl_api_function<
      void(uint_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(InvalidateTexImage)>
      InvalidateTexImage{"InvalidateTexImage", *this};

    /// @var ClearTexSubImage
    /// @glfuncwrap{ClearTexSubImage}
    gl_api_function<
      void(
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type,
        enum_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(ClearTexSubImage)>
      ClearTexSubImage{"ClearTexSubImage", *this};

    /// @var ClearTexImage
    /// @glfuncwrap{ClearTexImage}
    gl_api_function<
      void(uint_type, int_type, enum_type, enum_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(ClearTexImage)>
      ClearTexImage{"ClearTexImage", *this};

    /// @var TextureBarrier
    /// @glfuncwrap{TextureBarrier}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(TextureBarrier)>
      TextureBarrier{"TextureBarrier", *this};

    /// @var GenSamplers
    /// @glfuncwrap{GenSamplers}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenSamplers)>
      GenSamplers{"GenSamplers", *this};

    /// @var CreateSamplers
    /// @glfuncwrap{CreateSamplers}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateSamplers)>
      CreateSamplers{"CreateSamplers", *this};

    /// @var DeleteSamplers
    /// @glfuncwrap{DeleteSamplers}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteSamplers)>
      DeleteSamplers{"DeleteSamplers", *this};

    /// @var IsSampler
    /// @glfuncwrap{IsSampler}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsSampler)>
      IsSampler{"IsSampler", *this};

    /// @var BindSampler
    /// @glfuncwrap{BindSampler}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BindSampler)>
      BindSampler{"BindSampler", *this};

    /// @var BindSamplers
    /// @glfuncwrap{BindSamplers}
    gl_api_function<
      void(uint_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(BindSamplers)>
      BindSamplers{"BindSamplers", *this};

    /// @var SamplerParameterf
    /// @glfuncwrap{SamplerParameterf}
    gl_api_function<
      void(uint_type, enum_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(SamplerParameterf)>
      SamplerParameterf{"SamplerParameterf", *this};

    /// @var SamplerParameteri
    /// @glfuncwrap{SamplerParameteri}
    gl_api_function<
      void(uint_type, enum_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(SamplerParameteri)>
      SamplerParameteri{"SamplerParameteri", *this};

    /// @var SamplerParameterfv
    /// @glfuncwrap{SamplerParameterfv}
    gl_api_function<
      void(uint_type, enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(SamplerParameterfv)>
      SamplerParameterfv{"SamplerParameterfv", *this};

    /// @var SamplerParameteriv
    /// @glfuncwrap{SamplerParameteriv}
    gl_api_function<
      void(uint_type, enum_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(SamplerParameteriv)>
      SamplerParameteriv{"SamplerParameteriv", *this};

    /// @var SamplerParameterIiv
    /// @glfuncwrap{SamplerParameterIiv}
    gl_api_function<
      void(uint_type, enum_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(SamplerParameterIiv)>
      SamplerParameterIiv{"SamplerParameterIiv", *this};

    /// @var SamplerParameterIuiv
    /// @glfuncwrap{SamplerParameterIuiv}
    gl_api_function<
      void(uint_type, enum_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(SamplerParameterIuiv)>
      SamplerParameterIuiv{"SamplerParameterIuiv", *this};

    /// @var GetSamplerParameterfv
    /// @glfuncwrap{GetSamplerParameterfv}
    gl_api_function<
      void(uint_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetSamplerParameterfv)>
      GetSamplerParameterfv{"GetSamplerParameterfv", *this};

    /// @var GetSamplerParameteriv
    /// @glfuncwrap{GetSamplerParameteriv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetSamplerParameteriv)>
      GetSamplerParameteriv{"GetSamplerParameteriv", *this};

    /// @var GetSamplerParameterIiv
    /// @glfuncwrap{GetSamplerParameterIiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetSamplerParameterIiv)>
      GetSamplerParameterIiv{"GetSamplerParameterIiv", *this};

    /// @var GetSamplerParameterIuiv
    /// @glfuncwrap{GetSamplerParameterIuiv}
    gl_api_function<
      void(uint_type, enum_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetSamplerParameterIuiv)>
      GetSamplerParameterIuiv{"GetSamplerParameterIuiv", *this};

    /// @var GenRenderbuffers
    /// @glfuncwrap{GenRenderbuffers}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenRenderbuffers)>
      GenRenderbuffers{"GenRenderbuffers", *this};

    /// @var CreateRenderbuffers
    /// @glfuncwrap{CreateRenderbuffers}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateRenderbuffers)>
      CreateRenderbuffers{"CreateRenderbuffers", *this};

    /// @var DeleteRenderbuffers
    /// @glfuncwrap{DeleteRenderbuffers}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteRenderbuffers)>
      DeleteRenderbuffers{"DeleteRenderbuffers", *this};

    /// @var IsRenderbuffer
    /// @glfuncwrap{IsRenderbuffer}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsRenderbuffer)>
      IsRenderbuffer{"IsRenderbuffer", *this};

    /// @var BindRenderbuffer
    /// @glfuncwrap{BindRenderbuffer}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BindRenderbuffer)>
      BindRenderbuffer{"BindRenderbuffer", *this};

    /// @var RenderbufferStorage
    /// @glfuncwrap{RenderbufferStorage}
    gl_api_function<
      void(enum_type, enum_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(RenderbufferStorage)>
      RenderbufferStorage{"RenderbufferStorage", *this};

    /// @var NamedRenderbufferStorage
    /// @glfuncwrap{NamedRenderbufferStorage}
    gl_api_function<
      void(uint_type, enum_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(NamedRenderbufferStorage)>
      NamedRenderbufferStorage{"NamedRenderbufferStorage", *this};

    /// @var RenderbufferStorageMultisample
    /// @glfuncwrap{RenderbufferStorageMultisample}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(RenderbufferStorageMultisample)>
      RenderbufferStorageMultisample{"RenderbufferStorageMultisample", *this};

    /// @var NamedRenderbufferStorageMultisample
    /// @glfuncwrap{NamedRenderbufferStorageMultisample}
    gl_api_function<
      void(uint_type, sizei_type, enum_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(NamedRenderbufferStorageMultisample)>
      NamedRenderbufferStorageMultisample{
        "NamedRenderbufferStorageMultisample",
        *this};

    /// @var GetRenderbufferParameteriv
    /// @glfuncwrap{GetRenderbufferParameteriv}
    gl_api_function<
      void(enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetRenderbufferParameteriv)>
      GetRenderbufferParameteriv{"GetRenderbufferParameteriv", *this};

    /// @var GetNamedRenderbufferParameteriv
    /// @glfuncwrap{GetNamedRenderbufferParameteriv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetNamedRenderbufferParameteriv)>
      GetNamedRenderbufferParameteriv{"GetNamedRenderbufferParameteriv", *this};

    /// @var GenFramebuffers
    /// @glfuncwrap{GenFramebuffers}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenFramebuffers)>
      GenFramebuffers{"GenFramebuffers", *this};

    /// @var CreateFramebuffers
    /// @glfuncwrap{CreateFramebuffers}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateFramebuffers)>
      CreateFramebuffers{"CreateFramebuffers", *this};

    /// @var DeleteFramebuffers
    /// @glfuncwrap{DeleteFramebuffers}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteFramebuffers)>
      DeleteFramebuffers{"DeleteFramebuffers", *this};

    /// @var IsFramebuffer
    /// @glfuncwrap{IsFramebuffer}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsFramebuffer)>
      IsFramebuffer{"IsFramebuffer", *this};

    /// @var BindFramebuffer
    /// @glfuncwrap{BindFramebuffer}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BindFramebuffer)>
      BindFramebuffer{"BindFramebuffer", *this};

    /// @var DrawBuffers
    /// @glfuncwrap{DrawBuffers}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(DrawBuffer)>
      DrawBuffer{"DrawBuffer", *this};

    /// @var NamedFramebufferDrawBuffer
    /// @glfuncwrap{NamedFramebufferDrawBuffer}
    gl_api_function<
      void(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(NamedFramebufferDrawBuffer)>
      NamedFramebufferDrawBuffer{"NamedFramebufferDrawBuffer", *this};

    /// @var DrawBuffers
    /// @glfuncwrap{DrawBuffers}
    gl_api_function<
      void(sizei_type, const enum_type*),
      OGLPLUS_GL_STATIC_FUNC(DrawBuffers)>
      DrawBuffers{"DrawBuffers", *this};

    /// @var NamedFramebufferDrawBuffer
    /// @glfuncwrap{NamedFramebufferDrawBuffer}
    gl_api_function<
      void(uint_type, sizei_type, const enum_type*),
      OGLPLUS_GL_STATIC_FUNC(NamedFramebufferDrawBuffers)>
      NamedFramebufferDrawBuffers{"NamedFramebufferDrawBuffers", *this};

    /// @var ClearBufferfv
    /// @glfuncwrap{ClearBufferfv}
    gl_api_function<
      void(enum_type, int_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ClearBufferfv)>
      ClearBufferfv{"ClearBufferfv", *this};

    /// @var ClearBufferiv
    /// @glfuncwrap{ClearBufferiv}
    gl_api_function<
      void(enum_type, int_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ClearBufferiv)>
      ClearBufferiv{"ClearBufferiv", *this};

    /// @var ClearBufferuiv
    /// @glfuncwrap{ClearBufferuiv}
    gl_api_function<
      void(enum_type, int_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(ClearBufferuiv)>
      ClearBufferuiv{"ClearBufferuiv", *this};

    /// @var ClearBufferfi
    /// @glfuncwrap{ClearBufferfi}
    gl_api_function<
      void(enum_type, int_type, float_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(ClearBufferfi)>
      ClearBufferfi{"ClearBufferfi", *this};

    /// @var ClearNamedFramebufferfv
    /// @glfuncwrap{ClearNamedFramebufferfv}
    gl_api_function<
      void(uint_type, enum_type, int_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ClearNamedFramebufferfv)>
      ClearNamedFramebufferfv{"ClearNamedFramebufferfv", *this};

    /// @var ClearNamedFramebufferiv
    /// @glfuncwrap{ClearNamedFramebufferiv}
    gl_api_function<
      void(uint_type, enum_type, int_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ClearNamedFramebufferiv)>
      ClearNamedFramebufferiv{"ClearNamedFramebufferiv", *this};

    /// @var ClearNamedFramebufferuiv
    /// @glfuncwrap{ClearNamedFramebufferuiv}
    gl_api_function<
      void(uint_type, enum_type, int_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(ClearNamedFramebufferuiv)>
      ClearNamedFramebufferuiv{"ClearNamedFramebufferuiv", *this};

    /// @var ClearNamedFramebufferfi
    /// @glfuncwrap{ClearNamedFramebufferfi}
    gl_api_function<
      void(uint_type, enum_type, int_type, float_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(ClearNamedFramebufferfi)>
      ClearNamedFramebufferfi{"ClearNamedFramebufferfi", *this};

    /// @var InvalidateFramebuffer
    /// @glfuncwrap{InvalidateFramebuffer}
    gl_api_function<
      void(enum_type, sizei_type, const enum_type*),
      OGLPLUS_GL_STATIC_FUNC(InvalidateFramebuffer)>
      InvalidateFramebuffer{"InvalidateFramebuffer", *this};

    /// @var InvalidateSubFramebuffer
    /// @glfuncwrap{InvalidateSubFramebuffer}
    gl_api_function<
      void(
        enum_type,
        sizei_type,
        const enum_type*,
        int_type,
        int_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(InvalidateSubFramebuffer)>
      InvalidateSubFramebuffer{"InvalidateSubFramebuffer", *this};

    /// @var InvalidateNamedFramebufferData
    /// @glfuncwrap{InvalidateNamedFramebufferData}
    gl_api_function<
      void(uint_type, sizei_type, const enum_type*),
      OGLPLUS_GL_STATIC_FUNC(InvalidateFramebuffer)>
      InvalidateNamedFramebufferData{"InvalidateNamedFramebufferData", *this};

    /// @var InvalidateNamedFramebufferSubData
    /// @glfuncwrap{InvalidateNamedFramebufferSubData}
    gl_api_function<
      void(
        uint_type,
        sizei_type,
        const enum_type*,
        int_type,
        int_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(InvalidateNamedFramebufferSubData)>
      InvalidateNamedFramebufferSubData{
        "InvalidateNamedFramebufferSubData",
        *this};

    /// @var FramebufferParameteri
    /// @glfuncwrap{FramebufferParameteri}
    gl_api_function<
      void(enum_type, enum_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(FramebufferParameteri)>
      FramebufferParameteri{"FramebufferParameteri", *this};

    /// @var NamedFramebufferParameteri
    /// @glfuncwrap{NamedFramebufferParameteri}
    gl_api_function<
      void(uint_type, enum_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(NamedFramebufferParameteri)>
      NamedFramebufferParameteri{"NamedFramebufferParameteri", *this};

    /// @var GetFramebufferParameteriv
    /// @glfuncwrap{GetFramebufferParameteriv}
    gl_api_function<
      void(enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetFramebufferParameteriv)>
      GetFramebufferParameteriv{"GetFramebufferParameteriv", *this};

    /// @var GetNamedFramebufferParameteriv
    /// @glfuncwrap{GetNamedFramebufferParameteriv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetNamedFramebufferParameteriv)>
      GetNamedFramebufferParameteriv{"GetNamedFramebufferParameteriv", *this};

    /// @var GetFramebufferAttachmentParameteriv
    /// @glfuncwrap{GetFramebufferAttachmentParameteriv}
    gl_api_function<
      void(enum_type, enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetFramebufferAttachmentParameteriv)>
      GetFramebufferAttachmentParameteriv{
        "GetFramebufferAttachmentParameteriv",
        *this};

    /// @var GetNamedFramebufferAttachmentParameteriv
    /// @glfuncwrap{GetNamedFramebufferAttachmentParameteriv}
    gl_api_function<
      void(uint_type, enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetNamedFramebufferAttachmentParameteriv)>
      GetNamedFramebufferAttachmentParameteriv{
        "GetNamedFramebufferAttachmentParameteriv",
        *this};

    /// @var FramebufferRenderbuffer
    /// @glfuncwrap{FramebufferRenderbuffer}
    gl_api_function<
      void(enum_type, enum_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(FramebufferRenderbuffer)>
      FramebufferRenderbuffer{"FramebufferRenderbuffer", *this};

    /// @var NamedFramebufferRenderbuffer
    /// @glfuncwrap{NamedFramebufferRenderbuffer}
    gl_api_function<
      void(uint_type, enum_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(NamedFramebufferRenderbuffer)>
      NamedFramebufferRenderbuffer{"NamedFramebufferRenderbuffer", *this};

    /// @var FramebufferTexture
    /// @glfuncwrap{FramebufferTexture}
    gl_api_function<
      void(enum_type, enum_type, uint_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(FramebufferTexture)>
      FramebufferTexture{"FramebufferTexture", *this};

    /// @var NamedFramebufferTexture
    /// @glfuncwrap{NamedFramebufferTexture}
    gl_api_function<
      void(uint_type, enum_type, uint_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(NamedFramebufferTexture)>
      NamedFramebufferTexture{"NamedFramebufferTexture", *this};

    /// @var FramebufferTexture1D
    /// @glfuncwrap{FramebufferTexture1D}
    gl_api_function<
      void(enum_type, enum_type, enum_type, uint_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(FramebufferTexture1D)>
      FramebufferTexture1D{"FramebufferTexture1D", *this};

    /// @var FramebufferTexture2D
    /// @glfuncwrap{FramebufferTexture2D}
    gl_api_function<
      void(enum_type, enum_type, enum_type, uint_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(FramebufferTexture2D)>
      FramebufferTexture2D{"FramebufferTexture2D", *this};

    /// @var FramebufferTexture3D
    /// @glfuncwrap{FramebufferTexture3D}
    gl_api_function<
      void(enum_type, enum_type, enum_type, uint_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(FramebufferTexture3D)>
      FramebufferTexture3D{"FramebufferTexture3D", *this};

    /// @var FramebufferTextureLayer
    /// @glfuncwrap{FramebufferTextureLayer}
    gl_api_function<
      void(enum_type, enum_type, uint_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(FramebufferTextureLayer)>
      FramebufferTextureLayer{"FramebufferTextureLayer", *this};

    /// @var NamedFramebufferTextureLayer
    /// @glfuncwrap{NamedFramebufferTextureLayer}
    gl_api_function<
      void(uint_type, enum_type, uint_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(NamedFramebufferTextureLayer)>
      NamedFramebufferTextureLayer{"NamedFramebufferTextureLayer", *this};

    /// @var CheckFramebufferStatus
    /// @glfuncwrap{CheckFramebufferStatus}
    gl_api_function<
      enum_type(enum_type),
      OGLPLUS_GL_STATIC_FUNC(CheckFramebufferStatus)>
      CheckFramebufferStatus{"CheckFramebufferStatus", *this};

    /// @var CheckNamedFramebufferStatus
    /// @glfuncwrap{CheckNamedFramebufferStatus}
    gl_api_function<
      enum_type(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(CheckNamedFramebufferStatus)>
      CheckNamedFramebufferStatus{"CheckNamedFramebufferStatus", *this};

    /// @var ReadBuffer
    /// @glfuncwrap{ReadBuffer}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(ReadBuffer)>
      ReadBuffer{"ReadBuffer", *this};

    /// @var NamedFramebufferReadBuffer
    /// @glfuncwrap{NamedFramebufferReadBuffer}
    gl_api_function<
      void(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(NamedFramebufferReadBuffer)>
      NamedFramebufferReadBuffer{"NamedFramebufferReadBuffer", *this};

    /// @var BlitFramebuffer
    /// @glfuncwrap{BlitFramebuffer}
    gl_api_function<
      void(
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        bitfield_type,
        enum_type),
      OGLPLUS_GL_STATIC_FUNC(BlitFramebuffer)>
      BlitFramebuffer{"BlitFramebuffer", *this};

    /// @var BlitNamedFramebuffer
    /// @glfuncwrap{BlitNamedFramebuffer}
    gl_api_function<
      void(
        uint_type,
        uint_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        int_type,
        bitfield_type,
        enum_type),
      OGLPLUS_GL_STATIC_FUNC(BlitNamedFramebuffer)>
      BlitNamedFramebuffer{"BlitNamedFramebuffer", *this};

    /// @var CopyImageSubData
    /// @glfuncwrap{CopyImageSubData}
    gl_api_function<
      void(
        uint_type,
        enum_type,
        int_type,
        int_type,
        int_type,
        int_type,
        uint_type,
        enum_type,
        int_type,
        int_type,
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(CopyImageSubData)>
      CopyImageSubData{"CopyImageSubData", *this};

    /// @var GenTransformFeedbacks
    /// @glfuncwrap{GenTransformFeedbacks}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenTransformFeedbacks)>
      GenTransformFeedbacks{"GenTransformFeedbacks", *this};

    /// @var CreateTransformFeedbacks
    /// @glfuncwrap{CreateTransformFeedbacks}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateTransformFeedbacks)>
      CreateTransformFeedbacks{"CreateTransformFeedbacks", *this};

    /// @var DeleteTransformFeedbacks
    /// @glfuncwrap{DeleteTransformFeedbacks}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteTransformFeedbacks)>
      DeleteTransformFeedbacks{"DeleteTransformFeedbacks", *this};

    /// @var IsTransformFeedback
    /// @glfuncwrap{IsTransformFeedback}
    gl_api_function<
      bool_type(uint_type),
      OGLPLUS_GL_STATIC_FUNC(IsTransformFeedback)>
      IsTransformFeedback{"IsTransformFeedback", *this};

    /// @var BindTransformFeedback
    /// @glfuncwrap{BindTransformFeedback}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BindTransformFeedback)>
      BindTransformFeedback{"BindTransformFeedback", *this};

    /// @var BeginTransformFeedback
    /// @glfuncwrap{BeginTransformFeedback}
    gl_api_function<
      void(enum_type),
      OGLPLUS_GL_STATIC_FUNC(BeginTransformFeedback)>
      BeginTransformFeedback{"BeginTransformFeedback", *this};

    /// @var PauseTransformFeedback
    /// @glfuncwrap{PauseTransformFeedback}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(PauseTransformFeedback)>
      PauseTransformFeedback{"PauseTransformFeedback", *this};

    /// @var ResumeTransformFeedback
    /// @glfuncwrap{ResumeTransformFeedback}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(ResumeTransformFeedback)>
      ResumeTransformFeedback{"ResumeTransformFeedback", *this};

    /// @var EndTransformFeedback
    /// @glfuncwrap{EndTransformFeedback}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(EndTransformFeedback)>
      EndTransformFeedback{"EndTransformFeedback", *this};

    /// @var TransformFeedbackBufferBase
    /// @glfuncwrap{TransformFeedbackBufferBase}
    gl_api_function<
      void(uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(TransformFeedbackBufferBase)>
      TransformFeedbackBufferBase{"TransformFeedbackBufferBase", *this};

    /// @var TransformFeedbackBufferRange
    /// @glfuncwrap{TransformFeedbackBufferRange}
    gl_api_function<
      void(uint_type, uint_type, uint_type, intptr_type, sizeiptr_type),
      OGLPLUS_GL_STATIC_FUNC(TransformFeedbackBufferRange)>
      TransformFeedbackBufferRange{"TransformFeedbackBufferRange", *this};

    /// @var GetTransformFeedbackiv
    /// @glfuncwrap{GetTransformFeedbackiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTransformFeedbackiv)>
      GetTransformFeedbackiv{"GetTransformFeedbackiv", *this};

    /// @var GetTransformFeedbacki_v
    /// @glfuncwrap{GetTransformFeedbacki_v}
    gl_api_function<
      void(uint_type, enum_type, uint_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTransformFeedbacki_v)>
      GetTransformFeedbacki_v{"GetTransformFeedbacki_v", *this};

    /// @var GetTransformFeedbacki64_v
    /// @glfuncwrap{GetTransformFeedbacki64_v}
    gl_api_function<
      void(uint_type, enum_type, uint_type, int64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTransformFeedbacki64_v)>
      GetTransformFeedbacki64_v{"GetTransformFeedbacki64_v", *this};

    /// @var GenQueries
    /// @glfuncwrap{GenQueries}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenQueries)>
      GenQueries{"GenQueries", *this};

    /// @var CreateQueries
    /// @glfuncwrap{CreateQueries}
    gl_api_function<
      void(enum_type, sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateQueries)>
      CreateQueries{"CreateQueries", *this};

    /// @var DeleteQueries
    /// @glfuncwrap{DeleteQueries}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteQueries)>
      DeleteQueries{"DeleteQueries", *this};

    /// @var IsQuery
    /// @glfuncwrap{IsQuery}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsQuery)>
      IsQuery{"IsQuery", *this};

    /// @var GetQueryiv
    /// @glfuncwrap{GetQueryiv}
    gl_api_function<
      void(enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetQueryiv)>
      GetQueryiv{"GetQueryiv", *this};

    /// @var GetQueryIndexediv
    /// @glfuncwrap{GetQueryIndexediv}
    gl_api_function<
      void(enum_type, uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetQueryIndexediv)>
      GetQueryIndexediv{"GetQueryIndexediv", *this};

    /// @var GetQueryObjectiv
    /// @glfuncwrap{GetQueryObjectiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetQueryObjectiv)>
      GetQueryObjectiv{"GetQueryObjectiv", *this};

    /// @var GetQueryObjectuiv
    /// @glfuncwrap{GetQueryObjectuiv}
    gl_api_function<
      void(uint_type, enum_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetQueryObjectuiv)>
      GetQueryObjectuiv{"GetQueryObjectuiv", *this};

    /// @var GetQueryObjecti64v
    /// @glfuncwrap{GetQueryObjecti64v}
    gl_api_function<
      void(uint_type, enum_type, int64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetQueryObjecti64v)>
      GetQueryObjecti64v{"GetQueryObjecti64v", *this};

    /// @var GetQueryObjectui64v
    /// @glfuncwrap{GetQueryObjectui64v}
    gl_api_function<
      void(uint_type, enum_type, uint64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetQueryObjectui64v)>
      GetQueryObjectui64v{"GetQueryObjectui64v", *this};

    /// @var GetQueryBufferObjectiv
    /// @glfuncwrap{GetQueryBufferObjectiv}
    gl_api_function<
      void(uint_type, uint_type, enum_type, intptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetQueryBufferObjectiv)>
      GetQueryBufferObjectiv{"GetQueryBufferObjectiv", *this};

    /// @var GetQueryBufferObjectuiv
    /// @glfuncwrap{GetQueryBufferObjectuiv}
    gl_api_function<
      void(uint_type, uint_type, enum_type, intptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetQueryBufferObjectuiv)>
      GetQueryBufferObjectuiv{"GetQueryBufferObjectuiv", *this};

    /// @var GetQueryBufferObjecti64v
    /// @glfuncwrap{GetQueryBufferObjecti64v}
    gl_api_function<
      void(uint_type, uint_type, enum_type, intptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetQueryBufferObjecti64v)>
      GetQueryBufferObjecti64v{"GetQueryBufferObjecti64v", *this};

    /// @var GetQueryBufferObjectui64v
    /// @glfuncwrap{GetQueryBufferObjectui64v}
    gl_api_function<
      void(uint_type, uint_type, enum_type, intptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetQueryBufferObjectui64v)>
      GetQueryBufferObjectui64v{"GetQueryBufferObjectui64v", *this};

    /// @var BeginQuery
    /// @glfuncwrap{BeginQuery}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BeginQuery)>
      BeginQuery{"BeginQuery", *this};

    /// @var BeginQueryIndexed
    /// @glfuncwrap{BeginQueryIndexed}
    gl_api_function<
      void(enum_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(BeginQueryIndexed)>
      BeginQueryIndexed{"BeginQueryIndexed", *this};

    /// @var EndQuery
    /// @glfuncwrap{EndQuery}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(EndQuery)> EndQuery{
      "EndQuery",
      *this};

    /// @var EndQueryIndexed
    /// @glfuncwrap{EndQueryIndexed}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(EndQueryIndexed)>
      EndQueryIndexed{"EndQueryIndexed", *this};

    /// @var QueryCounter
    /// @glfuncwrap{QueryCounter}
    gl_api_function<
      void(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(QueryCounter)>
      QueryCounter{"QueryCounter", *this};

    /// @var BeginConditionalRender
    /// @glfuncwrap{BeginConditionalRender}
    gl_api_function<
      void(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BeginConditionalRender)>
      BeginConditionalRender{"BeginConditionalRender", *this};

    /// @var EndConditionalRender
    /// @glfuncwrap{EndConditionalRender}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(EndConditionalRender)>
      EndConditionalRender{"EndConditionalRender", *this};

    /// @var GenProgramPipelines
    /// @glfuncwrap{GenProgramPipelines}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GenProgramPipelines)>
      GenProgramPipelines{"GenProgramPipelines", *this};

    /// @var CreateProgramPipelines
    /// @glfuncwrap{CreateProgramPipelines}
    gl_api_function<
      void(sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(CreateProgramPipelines)>
      CreateProgramPipelines{"CreateProgramPipelines", *this};

    /// @var DeleteProgramPipelines
    /// @glfuncwrap{DeleteProgramPipelines}
    gl_api_function<
      void(sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(DeleteProgramPipelines)>
      DeleteProgramPipelines{"DeleteProgramPipelines", *this};

    /// @var IsProgramPipeline
    /// @glfuncwrap{IsProgramPipeline}
    gl_api_function<
      bool_type(uint_type),
      OGLPLUS_GL_STATIC_FUNC(IsProgramPipeline)>
      IsProgramPipeline{"IsProgramPipeline", *this};

    /// @var BindProgramPipeline
    /// @glfuncwrap{BindProgramPipeline}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(BindProgramPipeline)>
      BindProgramPipeline{"BindProgramPipeline", *this};

    /// @var ValidateProgramPipeline
    /// @glfuncwrap{ValidateProgramPipeline}
    gl_api_function<
      void(uint_type),
      OGLPLUS_GL_STATIC_FUNC(ValidateProgramPipeline)>
      ValidateProgramPipeline{"ValidateProgramPipeline", *this};

    /// @var UseProgramStages
    /// @glfuncwrap{UseProgramStages}
    gl_api_function<
      void(uint_type, bitfield_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(UseProgramStages)>
      UseProgramStages{"UseProgramStages", *this};

    /// @var GetProgramStageiv
    /// @glfuncwrap{GetProgramStageiv}
    gl_api_function<
      void(uint_type, enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramStageiv)>
      GetProgramStageiv{"GetProgramStageiv", *this};

    /// @var GetProgramPipelineiv
    /// @glfuncwrap{GetProgramPipelineiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramPipelineiv)>
      GetProgramPipelineiv{"GetProgramPipelineiv", *this};

    /// @var GetProgramPipelineInfoLog
    /// @glfuncwrap{GetProgramPipelineInfoLog}
    gl_api_function<
      void(uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramPipelineInfoLog)>
      GetProgramPipelineInfoLog{"GetProgramPipelineInfoLog", *this};

    /// @var ActiveShaderProgram
    /// @glfuncwrap{ActiveShaderProgram}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(ActiveShaderProgram)>
      ActiveShaderProgram{"ActiveShaderProgram", *this};

    /// @var CreateShader
    /// @glfuncwrap{CreateShader}
    gl_api_function<uint_type(enum_type), OGLPLUS_GL_STATIC_FUNC(CreateShader)>
      CreateShader{"CreateShader", *this};

    /// @var DeleteShader
    /// @glfuncwrap{DeleteShader}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(DeleteShader)>
      DeleteShader{"DeleteShader", *this};

    /// @var IsShader
    /// @glfuncwrap{IsShader}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsShader)>
      IsShader{"IsShader", *this};

    /// @var ShaderSource
    /// @glfuncwrap{ShaderSource}
    gl_api_function<
      void(uint_type, sizei_type, const char_type* const*, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ShaderSource)>
      ShaderSource{"ShaderSource", *this};

    /// @var CompileShader
    /// @glfuncwrap{CompileShader}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(CompileShader)>
      CompileShader{"CompileShader", *this};

    /// @var CompileShaderInclude
    /// @glfuncwrap{CompileShaderIncludeARB}
    gl_api_function<
      void(uint_type, sizei_type, const char_type* const*, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(nullptr)>
      CompileShaderInclude{"CompileShaderIncludeARB", *this};

    /// @var ShaderBinary
    /// @glfuncwrap{ShaderBinary}
    gl_api_function<
      void(sizei_type, const uint_type*, enum_type, const_void_ptr_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(ShaderBinary)>
      ShaderBinary{"ShaderBinary", *this};

    /// @var SpecializeShader
    /// @glfuncwrap{SpecializeShader}
    gl_api_function<
      void(
        uint_type,
        const char_type*,
        uint_type,
        const uint_type*,
        const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(SpecializeShader)>
      SpecializeShader{"SpecializeShader", *this};

    /// @var GetShaderiv
    /// @glfuncwrap{GetShaderiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetShaderiv)>
      GetShaderiv{"GetShaderiv", *this};

    /// @var GetShaderInfoLog
    /// @glfuncwrap{GetShaderInfoLog}
    gl_api_function<
      void(uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetShaderInfoLog)>
      GetShaderInfoLog{"GetShaderInfoLog", *this};

    /// @var GetShaderSource
    /// @glfuncwrap{GetShaderSource}
    gl_api_function<
      void(uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetShaderSource)>
      GetShaderSource{"GetShaderSource", *this};

    /// @var GetShaderPrecisionFormat
    /// @glfuncwrap{GetShaderPrecisionFormat}
    gl_api_function<
      void(enum_type, enum_type, int_type*, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetShaderPrecisionFormat)>
      GetShaderPrecisionFormat{"GetShaderPrecisionFormat", *this};

    /// @var ReleaseShaderCompiler
    /// @glfuncwrap{ReleaseShaderCompiler}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(ReleaseShaderCompiler)>
      ReleaseShaderCompiler{"ReleaseShaderCompiler", *this};

    /// @var CreateProgram
    /// @glfuncwrap{CreateProgram}
    gl_api_function<uint_type(), OGLPLUS_GL_STATIC_FUNC(CreateProgram)>
      CreateProgram{"CreateProgram", *this};

    /// @var CreateShaderProgramv
    /// @glfuncwrap{CreateShaderProgramv}
    gl_api_function<
      uint_type(enum_type, sizei_type, const char_type* const*),
      OGLPLUS_GL_STATIC_FUNC(CreateShaderProgramv)>
      CreateShaderProgramv{"CreateShaderProgramv", *this};

    /// @var DeleteProgram
    /// @glfuncwrap{DeleteProgram}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(DeleteProgram)>
      DeleteProgram{"DeleteProgram", *this};

    /// @var IsProgram
    /// @glfuncwrap{IsProgram}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsProgram)>
      IsProgram{"IsProgram", *this};

    /// @var AttachShader
    /// @glfuncwrap{AttachShader}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(AttachShader)>
      AttachShader{"AttachShader", *this};

    /// @var DetachShader
    /// @glfuncwrap{DetachShader}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(DetachShader)>
      DetachShader{"DetachShader", *this};

    /// @var GetAttachedShaders
    /// @glfuncwrap{GetAttachedShaders}
    gl_api_function<
      void(uint_type, sizei_type, sizei_type*, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetAttachedShaders)>
      GetAttachedShaders{"GetAttachedShaders", *this};

    /// @var ValidateProgram
    /// @glfuncwrap{ValidateProgram}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(ValidateProgram)>
      ValidateProgram{"ValidateProgram", *this};

    /// @var LinkProgram
    /// @glfuncwrap{LinkProgram}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(LinkProgram)>
      LinkProgram{"LinkProgram", *this};

    /// @var UseProgram
    /// @glfuncwrap{UseProgram}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(UseProgram)>
      UseProgram{"UseProgram", *this};

    /// @var ProgramBinary
    /// @glfuncwrap{ProgramBinary}
    gl_api_function<
      void(uint_type, enum_type, const_void_ptr_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramBinary)>
      ProgramBinary{"ProgramBinary", *this};

    /// @var GetProgramBinary
    /// @glfuncwrap{GetProgramBinary}
    gl_api_function<
      void(uint_type, sizei_type, sizei_type*, enum_type*, void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(GetProgramBinary)>
      GetProgramBinary{"GetProgramBinary", *this};

    /// @var GetProgramiv
    /// @glfuncwrap{GetProgramiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramiv)>
      GetProgramiv{"GetProgramiv", *this};

    /// @var GetProgramInfoLog
    /// @glfuncwrap{GetProgramInfoLog}
    gl_api_function<
      void(uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramInfoLog)>
      GetProgramInfoLog{"GetProgramInfoLog", *this};

    /// @var GetProgramInterfaceiv
    /// @glfuncwrap{GetProgramInterfaceiv}
    gl_api_function<
      void(uint_type, enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramInterfaceiv)>
      GetProgramInterfaceiv{"GetProgramInterfaceiv", *this};

    /// @var GetProgramResourceIndex
    /// @glfuncwrap{GetProgramResourceIndex}
    gl_api_function<
      uint_type(uint_type, enum_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramResourceIndex)>
      GetProgramResourceIndex{"GetProgramResourceIndex", *this};

    /// @var GetProgramResourceName
    /// @glfuncwrap{GetProgramResourceName}
    gl_api_function<
      void(uint_type, enum_type, uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramResourceName)>
      GetProgramResourceName{"GetProgramResourceName", *this};

    /// @var GetProgramResourceLocation
    /// @glfuncwrap{GetProgramResourceLocation}
    gl_api_function<
      int_type(uint_type, enum_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramResourceLocation)>
      GetProgramResourceLocation{"GetProgramResourceLocation", *this};

    /// @var GetProgramResourceLocationIndex
    /// @glfuncwrap{GetProgramResourceLocationIndex}
    gl_api_function<
      int_type(uint_type, enum_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramResourceLocationIndex)>
      GetProgramResourceLocationIndex{"GetProgramResourceLocationIndex", *this};

    /// @var GetProgramResourceiv
    /// @glfuncwrap{GetProgramResourceiv}
    gl_api_function<
      void(
        uint_type,
        enum_type,
        uint_type,
        sizei_type,
        const enum_type*,
        sizei_type,
        sizei_type*,
        int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramResourceiv)>
      GetProgramResourceiv{"GetProgramResourceiv", *this};

    /// @var GetProgramResourcefvNV
    /// @glfuncwrap{GetProgramResourcefvNV}
    gl_api_function<
      void(
        uint_type,
        enum_type,
        uint_type,
        sizei_type,
        const enum_type*,
        sizei_type,
        sizei_type*,
        float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetProgramResourcefvNV)>
      GetProgramResourcefvNV{"GetProgramResourcefvNV", *this};

    /// @var BindAttribLocation
    /// @glfuncwrap{BindAttribLocation}
    gl_api_function<
      void(uint_type, uint_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(BindAttribLocation)>
      BindAttribLocation{"BindAttribLocation", *this};

    /// @var GetAttribLocation
    /// @glfuncwrap{GetAttribLocation}
    gl_api_function<
      int_type(uint_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetAttribLocation)>
      GetAttribLocation{"GetAttribLocation", *this};

    /// @var GetActiveAttrib
    /// @glfuncwrap{GetActiveAttrib}
    gl_api_function<
      void(
        uint_type,
        uint_type,
        sizei_type,
        sizei_type*,
        int_type*,
        enum_type*,
        char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetActiveAttrib)>
      GetActiveAttrib{"GetActiveAttrib", *this};

    /// @var GetActiveUniformLocation
    /// @glfuncwrap{GetActiveUniformLocation}
    gl_api_function<
      int_type(uint_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetUniformLocation)>
      GetUniformLocation{"GetUniformLocation", *this};

    /// @var GetUniformBlockIndex
    /// @glfuncwrap{GetUniformBlockIndex}
    gl_api_function<
      int_type(uint_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetUniformBlockIndex)>
      GetUniformBlockIndex{"GetUniformBlockIndex", *this};

    /// @var GetActiveUniformName
    /// @glfuncwrap{GetActiveUniformName}
    gl_api_function<
      void(uint_type, uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetActiveUniformName)>
      GetActiveUniformName{"GetActiveUniformName", *this};

    /// @var GetSubroutineIndex
    /// @glfuncwrap{GetSubroutineIndex}
    gl_api_function<
      uint_type(uint_type, enum_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetSubroutineIndex)>
      GetSubroutineIndex{"GetSubroutineIndex", *this};

    /// @var GetActiveSubroutineName
    /// @glfuncwrap{GetActiveSubroutineName}
    gl_api_function<
      void(uint_type, enum_type, uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetActiveSubroutineName)>
      GetActiveSubroutineName{"GetActiveSubroutineName", *this};

    /// @var GetActiveSubroutineUniformName
    /// @glfuncwrap{GetActiveSubroutineUniformName}
    gl_api_function<
      void(uint_type, enum_type, uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetActiveSubroutineUniformName)>
      GetActiveSubroutineUniformName{"GetActiveSubroutineUniformName", *this};

    /// @var GetSubroutineUniformLocation
    /// @glfuncwrap{GetSubroutineUniformLocation}
    gl_api_function<
      int_type(uint_type, enum_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetSubroutineUniformLocation)>
      GetSubroutineUniformLocation{"GetSubroutineUniformLocation", *this};

    /// @var GetActiveSubroutineUniformiv
    /// @glfuncwrap{GetActiveSubroutineUniformiv}
    gl_api_function<
      void(uint_type, enum_type, uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetActiveSubroutineUniformiv)>
      GetActiveSubroutineUniformiv{"GetActiveSubroutineUniformiv", *this};

    /// @var TransformFeedbackVaryings
    /// @glfuncwrap{TransformFeedbackVaryings}
    gl_api_function<
      void(uint_type, sizei_type, const char_type* const*, enum_type),
      OGLPLUS_GL_STATIC_FUNC(TransformFeedbackVaryings)>
      TransformFeedbackVaryings{"TransformFeedbackVaryings", *this};

    /// @var GetTransformFeedbackVarying
    /// @glfuncwrap{GetTransformFeedbackVarying}
    gl_api_function<
      void(
        uint_type,
        uint_type,
        sizei_type,
        sizei_type*,
        sizei_type*,
        enum_type*,
        char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetTransformFeedbackVarying)>
      GetTransformFeedbackVarying{"GetTransformFeedbackVarying", *this};

    /// @var BindFragDataLocation
    /// @glfuncwrap{BindFragDataLocation}
    gl_api_function<
      void(uint_type, uint_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(BindFragDataLocation)>
      BindFragDataLocation{"BindFragDataLocation", *this};

    /// @var BindFragDataLocationIndexed
    /// @glfuncwrap{BindFragDataLocationIndexed}
    gl_api_function<
      void(uint_type, uint_type, uint_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(BindFragDataLocationIndexed)>
      BindFragDataLocationIndexed{"BindFragDataLocationIndexed", *this};

    /// @var GetFragDataLocation
    /// @glfuncwrap{GetFragDataLocation}
    gl_api_function<
      int_type(uint_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetFragDataLocation)>
      GetFragDataLocation{"GetFragDataLocation", *this};

    /// @var GetFragDataIndex
    /// @glfuncwrap{GetFragDataIndex}
    gl_api_function<
      int_type(uint_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetFragDataIndex)>
      GetFragDataIndex{"GetFragDataIndex", *this};

    /// @var UniformSubroutinesuiv
    /// @glfuncwrap{UniformSubroutinesuiv}
    gl_api_function<
      void(enum_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformSubroutinesuiv)>
      UniformSubroutinesuiv{"UniformSubroutinesuiv", *this};

    /// @var GetUniformSubroutineuiv
    /// @glfuncwrap{GetUniformSubroutineuiv}
    gl_api_function<
      void(enum_type, int_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetUniformSubroutineuiv)>
      GetUniformSubroutineuiv{"GetUniformSubroutineuiv", *this};

    /// @var Uniform1i
    /// @glfuncwrap{Uniform1i}
    gl_api_function<void(int_type, int_type), OGLPLUS_GL_STATIC_FUNC(Uniform1i)>
      Uniform1i{"Uniform1i", *this};

    /// @var Uniform2i
    /// @glfuncwrap{Uniform2i}
    gl_api_function<
      void(int_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform2i)>
      Uniform2i{"Uniform2i", *this};

    /// @var Uniform3i
    /// @glfuncwrap{Uniform3i}
    gl_api_function<
      void(int_type, int_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform3i)>
      Uniform3i{"Uniform3i", *this};

    /// @var Uniform4i
    /// @glfuncwrap{Uniform4i}
    gl_api_function<
      void(int_type, int_type, int_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform4i)>
      Uniform4i{"Uniform4i", *this};

    /// @var Uniform1iv
    /// @glfuncwrap{Uniform1iv}
    gl_api_function<
      void(int_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform1iv)>
      Uniform1iv{"Uniform1iv", *this};

    /// @var Uniform2iv
    /// @glfuncwrap{Uniform2iv}
    gl_api_function<
      void(int_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform2iv)>
      Uniform2iv{"Uniform2iv", *this};

    /// @var Uniform3iv
    /// @glfuncwrap{Uniform3iv}
    gl_api_function<
      void(int_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform3iv)>
      Uniform3iv{"Uniform3iv", *this};

    /// @var Uniform4iv
    /// @glfuncwrap{Uniform4iv}
    gl_api_function<
      void(int_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform4iv)>
      Uniform4iv{"Uniform4iv", *this};

    /// @var Uniform1ui
    /// @glfuncwrap{Uniform1ui}
    gl_api_function<void(int_type, uint_type), OGLPLUS_GL_STATIC_FUNC(Uniform1ui)>
      Uniform1ui{"Uniform1ui", *this};

    /// @var Uniform2ui
    /// @glfuncwrap{Uniform2ui}
    gl_api_function<
      void(int_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform2ui)>
      Uniform2ui{"Uniform2ui", *this};

    /// @var Uniform3ui
    /// @glfuncwrap{Uniform3ui}
    gl_api_function<
      void(int_type, uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform3ui)>
      Uniform3ui{"Uniform3ui", *this};

    /// @var Uniform4ui
    /// @glfuncwrap{Uniform4ui}
    gl_api_function<
      void(int_type, uint_type, uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform4ui)>
      Uniform4ui{"Uniform4ui", *this};

    /// @var Uniform1uiv
    /// @glfuncwrap{Uniform1uiv}
    gl_api_function<
      void(int_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform1uiv)>
      Uniform1uiv{"Uniform1uiv", *this};

    /// @var Uniform2uiv
    /// @glfuncwrap{Uniform2uiv}
    gl_api_function<
      void(int_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform2uiv)>
      Uniform2uiv{"Uniform2uiv", *this};

    /// @var Uniform3uiv
    /// @glfuncwrap{Uniform3uiv}
    gl_api_function<
      void(int_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform3uiv)>
      Uniform3uiv{"Uniform3uiv", *this};

    /// @var Uniform4uiv
    /// @glfuncwrap{Uniform4uiv}
    gl_api_function<
      void(int_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform4uiv)>
      Uniform4uiv{"Uniform4uiv", *this};

    /// @var Uniform1f
    /// @glfuncwrap{Uniform1f}
    gl_api_function<void(int_type, float_type), OGLPLUS_GL_STATIC_FUNC(Uniform1f)>
      Uniform1f{"Uniform1f", *this};

    /// @var Uniform2f
    /// @glfuncwrap{Uniform2f}
    gl_api_function<
      void(int_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform2f)>
      Uniform2f{"Uniform2f", *this};

    /// @var Uniform3f
    /// @glfuncwrap{Uniform3f}
    gl_api_function<
      void(int_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform3f)>
      Uniform3f{"Uniform3f", *this};

    /// @var Uniform4f
    /// @glfuncwrap{Uniform4f}
    gl_api_function<
      void(int_type, float_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(Uniform4f)>
      Uniform4f{"Uniform4f", *this};

    /// @var Uniform1fv
    /// @glfuncwrap{Uniform1fv}
    gl_api_function<
      void(int_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform1fv)>
      Uniform1fv{"Uniform1fv", *this};

    /// @var Uniform2fv
    /// @glfuncwrap{Uniform2fv}
    gl_api_function<
      void(int_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform2fv)>
      Uniform2fv{"Uniform2fv", *this};

    /// @var Uniform3fv
    /// @glfuncwrap{Uniform3fv}
    gl_api_function<
      void(int_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform3fv)>
      Uniform3fv{"Uniform3fv", *this};

    /// @var Uniform4fv
    /// @glfuncwrap{Uniform4fv}
    gl_api_function<
      void(int_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(Uniform4fv)>
      Uniform4fv{"Uniform4fv", *this};

    /// @var UniformMatrix2fv
    /// @glfuncwrap{UniformMatrix2fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix2fv)>
      UniformMatrix2fv{"UniformMatrix2fv", *this};

    /// @var UniformMatrix3fv
    /// @glfuncwrap{UniformMatrix3fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix3fv)>
      UniformMatrix3fv{"UniformMatrix3fv", *this};

    /// @var UniformMatrix4fv
    /// @glfuncwrap{UniformMatrix4fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix4fv)>
      UniformMatrix4fv{"UniformMatrix4fv", *this};

    /// @var UniformMatrix2x3fv
    /// @glfuncwrap{UniformMatrix2x3fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix2x3fv)>
      UniformMatrix2x3fv{"UniformMatrix2x3fv", *this};

    /// @var UniformMatrix3x2fv
    /// @glfuncwrap{UniformMatrix3x2fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix3x2fv)>
      UniformMatrix3x2fv{"UniformMatrix3x2fv", *this};

    /// @var UniformMatrix2x4fv
    /// @glfuncwrap{UniformMatrix2x4fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix2x4fv)>
      UniformMatrix2x4fv{"UniformMatrix2x4fv", *this};

    /// @var UniformMatrix4x2fv
    /// @glfuncwrap{UniformMatrix4x2fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix4x2fv)>
      UniformMatrix4x2fv{"UniformMatrix4x2fv", *this};

    /// @var UniformMatrix3x4fv
    /// @glfuncwrap{UniformMatrix3x4fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix3x4fv)>
      UniformMatrix3x4fv{"UniformMatrix3x4fv", *this};

    /// @var UniformMatrix4x3fv
    /// @glfuncwrap{UniformMatrix4x3fv}
    gl_api_function<
      void(int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(UniformMatrix4x3fv)>
      UniformMatrix4x3fv{"UniformMatrix4x3fv", *this};

    /// @var GetUniformfv
    /// @glfuncwrap{GetUniformfv}
    gl_api_function<
      void(uint_type, int_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetUniformfv)>
      GetUniformfv{"GetUniformfv", *this};

    /// @var GetUniformdv
    /// @glfuncwrap{GetUniformdv}
    gl_api_function<
      void(uint_type, int_type, double_type*),
      OGLPLUS_GL_STATIC_FUNC(GetUniformdv)>
      GetUniformdv{"GetUniformdv", *this};

    /// @var GetUniformiv
    /// @glfuncwrap{GetUniformiv}
    gl_api_function<
      void(uint_type, int_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetUniformiv)>
      GetUniformiv{"GetUniformiv", *this};

    /// @var GetUniformuiv
    /// @glfuncwrap{GetUniformuiv}
    gl_api_function<
      void(uint_type, int_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetUniformuiv)>
      GetUniformuiv{"GetUniformuiv", *this};

    /// @var GetnUniformfv
    /// @glfuncwrap{GetnUniformfv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetnUniformfv)>
      GetnUniformfv{"GetnUniformfv", *this};

    /// @var GetnUniformdv
    /// @glfuncwrap{GetnUniformdv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, double_type*),
      OGLPLUS_GL_STATIC_FUNC(GetnUniformdv)>
      GetnUniformdv{"GetnUniformdv", *this};

    /// @var GetnUniformiv
    /// @glfuncwrap{GetnUniformiv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetnUniformiv)>
      GetnUniformiv{"GetnUniformiv", *this};

    /// @var GetnUniformuiv
    /// @glfuncwrap{GetnUniformuiv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetnUniformuiv)>
      GetnUniformuiv{"GetnUniformuiv", *this};

    /// @var ProgramUniform1i
    /// @glfuncwrap{ProgramUniform1i}
    gl_api_function<
      void(uint_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform1i)>
      ProgramUniform1i{"ProgramUniform1i", *this};

    /// @var ProgramUniform2i
    /// @glfuncwrap{ProgramUniform2i}
    gl_api_function<
      void(uint_type, int_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform2i)>
      ProgramUniform2i{"ProgramUniform2i", *this};

    /// @var ProgramUniform3i
    /// @glfuncwrap{ProgramUniform3i}
    gl_api_function<
      void(uint_type, int_type, int_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform3i)>
      ProgramUniform3i{"ProgramUniform3i", *this};

    /// @var ProgramUniform4i
    /// @glfuncwrap{ProgramUniform4i}
    gl_api_function<
      void(uint_type, int_type, int_type, int_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform4i)>
      ProgramUniform4i{"ProgramUniform4i", *this};

    /// @var ProgramUniform1iv
    /// @glfuncwrap{ProgramUniform1iv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform1iv)>
      ProgramUniform1iv{"ProgramUniform1iv", *this};

    /// @var ProgramUniform2iv
    /// @glfuncwrap{ProgramUniform2iv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform2iv)>
      ProgramUniform2iv{"ProgramUniform2iv", *this};

    /// @var ProgramUniform3iv
    /// @glfuncwrap{ProgramUniform3iv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform3iv)>
      ProgramUniform3iv{"ProgramUniform3iv", *this};

    /// @var ProgramUniform4iv
    /// @glfuncwrap{ProgramUniform4iv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform4iv)>
      ProgramUniform4iv{"ProgramUniform4iv", *this};

    /// @var ProgramUniform1ui
    /// @glfuncwrap{ProgramUniform1ui}
    gl_api_function<
      void(uint_type, int_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform1ui)>
      ProgramUniform1ui{"ProgramUniform1ui", *this};

    /// @var ProgramUniform2ui
    /// @glfuncwrap{ProgramUniform2ui}
    gl_api_function<
      void(uint_type, int_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform2ui)>
      ProgramUniform2ui{"ProgramUniform2ui", *this};

    /// @var ProgramUniform3ui
    /// @glfuncwrap{ProgramUniform3ui}
    gl_api_function<
      void(uint_type, int_type, uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform3ui)>
      ProgramUniform3ui{"ProgramUniform3ui", *this};

    /// @var ProgramUniform4ui
    /// @glfuncwrap{ProgramUniform4ui}
    gl_api_function<
      void(uint_type, int_type, uint_type, uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform4ui)>
      ProgramUniform4ui{"ProgramUniform4ui", *this};

    /// @var ProgramUniform1uiv
    /// @glfuncwrap{ProgramUniform1uiv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform1uiv)>
      ProgramUniform1uiv{"ProgramUniform1uiv", *this};

    /// @var ProgramUniform2uiv
    /// @glfuncwrap{ProgramUniform2uiv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform2uiv)>
      ProgramUniform2uiv{"ProgramUniform2uiv", *this};

    /// @var ProgramUniform3uiv
    /// @glfuncwrap{ProgramUniform3uiv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform3uiv)>
      ProgramUniform3uiv{"ProgramUniform3uiv", *this};

    /// @var ProgramUniform4uiv
    /// @glfuncwrap{ProgramUniform4uiv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform4uiv)>
      ProgramUniform4uiv{"ProgramUniform4uiv", *this};

    /// @var ProgramUniform1f
    /// @glfuncwrap{ProgramUniform1f}
    gl_api_function<
      void(uint_type, int_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform1f)>
      ProgramUniform1f{"ProgramUniform1f", *this};

    /// @var ProgramUniform2f
    /// @glfuncwrap{ProgramUniform2f}
    gl_api_function<
      void(uint_type, int_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform2f)>
      ProgramUniform2f{"ProgramUniform2f", *this};

    /// @var ProgramUniform3f
    /// @glfuncwrap{ProgramUniform3f}
    gl_api_function<
      void(uint_type, int_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform3f)>
      ProgramUniform3f{"ProgramUniform3f", *this};

    /// @var ProgramUniform4f
    /// @glfuncwrap{ProgramUniform4f}
    gl_api_function<
      void(uint_type, int_type, float_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform4f)>
      ProgramUniform4f{"ProgramUniform4f", *this};

    /// @var ProgramUniform1fv
    /// @glfuncwrap{ProgramUniform1fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform1fv)>
      ProgramUniform1fv{"ProgramUniform1fv", *this};

    /// @var ProgramUniform2fv
    /// @glfuncwrap{ProgramUniform2fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform2fv)>
      ProgramUniform2fv{"ProgramUniform2fv", *this};

    /// @var ProgramUniform3fv
    /// @glfuncwrap{ProgramUniform3fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform3fv)>
      ProgramUniform3fv{"ProgramUniform3fv", *this};

    /// @var ProgramUniform4fv
    /// @glfuncwrap{ProgramUniform4fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniform4fv)>
      ProgramUniform4fv{"ProgramUniform4fv", *this};

    /// @var ProgramUniformMatrix2fv
    /// @glfuncwrap{ProgramUniformMatrix2fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix2fv)>
      ProgramUniformMatrix2fv{"ProgramUniformMatrix2fv", *this};

    /// @var ProgramUniformMatrix3fv
    /// @glfuncwrap{ProgramUniformMatrix3fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix3fv)>
      ProgramUniformMatrix3fv{"ProgramUniformMatrix3fv", *this};

    /// @var ProgramUniformMatrix4fv
    /// @glfuncwrap{ProgramUniformMatrix4fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix4fv)>
      ProgramUniformMatrix4fv{"ProgramUniformMatrix4fv", *this};

    /// @var ProgramUniformMatrix2x3fv
    /// @glfuncwrap{ProgramUniformMatrix2x3fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix2x3fv)>
      ProgramUniformMatrix2x3fv{"ProgramUniformMatrix2x3fv", *this};

    /// @var ProgramUniformMatrix3x2fv
    /// @glfuncwrap{ProgramUniformMatrix3x2fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix3x2fv)>
      ProgramUniformMatrix3x2fv{"ProgramUniformMatrix3x2fv", *this};

    /// @var ProgramUniformMatrix2x4fv
    /// @glfuncwrap{ProgramUniformMatrix2x4fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix2x4fv)>
      ProgramUniformMatrix2x4fv{"ProgramUniformMatrix2x4fv", *this};

    /// @var ProgramUniformMatrix4x2fv
    /// @glfuncwrap{ProgramUniformMatrix4x2fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix4x2fv)>
      ProgramUniformMatrix4x2fv{"ProgramUniformMatrix4x2fv", *this};

    /// @var ProgramUniformMatrix3x4fv
    /// @glfuncwrap{ProgramUniformMatrix3x4fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix3x4fv)>
      ProgramUniformMatrix3x4fv{"ProgramUniformMatrix3x4fv", *this};

    /// @var ProgramUniformMatrix4x3fv
    /// @glfuncwrap{ProgramUniformMatrix4x3fv}
    gl_api_function<
      void(uint_type, int_type, sizei_type, bool_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramUniformMatrix4x3fv)>
      ProgramUniformMatrix4x3fv{"ProgramUniformMatrix4x3fv", *this};

    /// @var UniformBlockBinding
    /// @glfuncwrap{UniformBlockBinding}
    gl_api_function<
      void(uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(UniformBlockBinding)>
      UniformBlockBinding{"UniformBlockBinding", *this};

    /// @var ShaderStorageBlockBinding
    /// @glfuncwrap{ShaderStorageBlockBinding}
    gl_api_function<
      void(uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(ShaderStorageBlockBinding)>
      ShaderStorageBlockBinding{"ShaderStorageBlockBinding", *this};

    /// @var VertexAttrib1f
    /// @glfuncwrap{VertexAttrib1f}
    gl_api_function<
      void(uint_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib1f)>
      VertexAttrib1f{"VertexAttrib1f", *this};

    /// @var VertexAttrib2f
    /// @glfuncwrap{VertexAttrib2f}
    gl_api_function<
      void(uint_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib2f)>
      VertexAttrib2f{"VertexAttrib2f", *this};

    /// @var VertexAttrib3f
    /// @glfuncwrap{VertexAttrib3f}
    gl_api_function<
      void(uint_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib3f)>
      VertexAttrib3f{"VertexAttrib3f", *this};

    /// @var VertexAttrib4f
    /// @glfuncwrap{VertexAttrib4f}
    gl_api_function<
      void(uint_type, float_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4f)>
      VertexAttrib4f{"VertexAttrib4f", *this};

    /// @var VertexAttrib1fv
    /// @glfuncwrap{VertexAttrib1fv}
    gl_api_function<
      void(uint_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib1fv)>
      VertexAttrib1fv{"VertexAttrib1fv", *this};

    /// @var VertexAttrib2fv
    /// @glfuncwrap{VertexAttrib2fv}
    gl_api_function<
      void(uint_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib2fv)>
      VertexAttrib2fv{"VertexAttrib2fv", *this};

    /// @var VertexAttrib3fv
    /// @glfuncwrap{VertexAttrib3fv}
    gl_api_function<
      void(uint_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib3fv)>
      VertexAttrib3fv{"VertexAttrib3fv", *this};

    /// @var VertexAttrib4fv
    /// @glfuncwrap{VertexAttrib4fv}
    gl_api_function<
      void(uint_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4fv)>
      VertexAttrib4fv{"VertexAttrib4fv", *this};

    /// @var VertexAttrib1d
    /// @glfuncwrap{VertexAttrib1d}
    gl_api_function<
      void(uint_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib1d)>
      VertexAttrib1d{"VertexAttrib1d", *this};

    /// @var VertexAttrib2d
    /// @glfuncwrap{VertexAttrib2d}
    gl_api_function<
      void(uint_type, double_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib2d)>
      VertexAttrib2d{"VertexAttrib2d", *this};

    /// @var VertexAttrib3d
    /// @glfuncwrap{VertexAttrib3d}
    gl_api_function<
      void(uint_type, double_type, double_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib3d)>
      VertexAttrib3d{"VertexAttrib3d", *this};

    /// @var VertexAttrib4d
    /// @glfuncwrap{VertexAttrib4d}
    gl_api_function<
      void(uint_type, double_type, double_type, double_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4d)>
      VertexAttrib4d{"VertexAttrib4d", *this};

    /// @var VertexAttrib1dv
    /// @glfuncwrap{VertexAttrib1dv}
    gl_api_function<
      void(uint_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib1dv)>
      VertexAttrib1dv{"VertexAttrib1dv", *this};

    /// @var VertexAttrib2dv
    /// @glfuncwrap{VertexAttrib2dv}
    gl_api_function<
      void(uint_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib2dv)>
      VertexAttrib2dv{"VertexAttrib2dv", *this};

    /// @var VertexAttrib3dv
    /// @glfuncwrap{VertexAttrib3dv}
    gl_api_function<
      void(uint_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib3dv)>
      VertexAttrib3dv{"VertexAttrib3dv", *this};

    /// @var VertexAttrib4dv
    /// @glfuncwrap{VertexAttrib4dv}
    gl_api_function<
      void(uint_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4dv)>
      VertexAttrib4dv{"VertexAttrib4dv", *this};

    /// @var VertexAttrib1s
    /// @glfuncwrap{VertexAttrib1s}
    gl_api_function<
      void(uint_type, short_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib1s)>
      VertexAttrib1s{"VertexAttrib1s", *this};

    /// @var VertexAttrib2s
    /// @glfuncwrap{VertexAttrib2s}
    gl_api_function<
      void(uint_type, short_type, short_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib2s)>
      VertexAttrib2s{"VertexAttrib2s", *this};

    /// @var VertexAttrib3s
    /// @glfuncwrap{VertexAttrib3s}
    gl_api_function<
      void(uint_type, short_type, short_type, short_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib3s)>
      VertexAttrib3s{"VertexAttrib3s", *this};

    /// @var VertexAttrib4s
    /// @glfuncwrap{VertexAttrib4s}
    gl_api_function<
      void(uint_type, short_type, short_type, short_type, short_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4s)>
      VertexAttrib4s{"VertexAttrib4s", *this};

    /// @var VertexAttrib1sv
    /// @glfuncwrap{VertexAttrib1sv}
    gl_api_function<
      void(uint_type, const short_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib1sv)>
      VertexAttrib1sv{"VertexAttrib1sv", *this};

    /// @var VertexAttrib2sv
    /// @glfuncwrap{VertexAttrib2sv}
    gl_api_function<
      void(uint_type, const short_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib2sv)>
      VertexAttrib2sv{"VertexAttrib2sv", *this};

    /// @var VertexAttrib3sv
    /// @glfuncwrap{VertexAttrib3sv}
    gl_api_function<
      void(uint_type, const short_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib3sv)>
      VertexAttrib3sv{"VertexAttrib3sv", *this};

    /// @var VertexAttrib4sv
    /// @glfuncwrap{VertexAttrib4sv}
    gl_api_function<
      void(uint_type, const short_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4sv)>
      VertexAttrib4sv{"VertexAttrib4sv", *this};

    /// @var VertexAttribI1i
    /// @glfuncwrap{VertexAttribI1i}
    gl_api_function<
      void(uint_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI1i)>
      VertexAttribI1i{"VertexAttribI1i", *this};

    /// @var VertexAttribI2i
    /// @glfuncwrap{VertexAttribI2i}
    gl_api_function<
      void(uint_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI2i)>
      VertexAttribI2i{"VertexAttribI2i", *this};

    /// @var VertexAttribI3i
    /// @glfuncwrap{VertexAttribI3i}
    gl_api_function<
      void(uint_type, int_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI3i)>
      VertexAttribI3i{"VertexAttribI3i", *this};

    /// @var VertexAttribI4i
    /// @glfuncwrap{VertexAttribI4i}
    gl_api_function<
      void(uint_type, int_type, int_type, int_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI4i)>
      VertexAttribI4i{"VertexAttribI4i", *this};

    /// @var VertexAttribI1iv
    /// @glfuncwrap{VertexAttribI1iv}
    gl_api_function<
      void(uint_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI1iv)>
      VertexAttribI1iv{"VertexAttribI1iv", *this};

    /// @var VertexAttribI2iv
    /// @glfuncwrap{VertexAttribI2iv}
    gl_api_function<
      void(uint_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI2iv)>
      VertexAttribI2iv{"VertexAttribI2iv", *this};

    /// @var VertexAttribI3iv
    /// @glfuncwrap{VertexAttribI3iv}
    gl_api_function<
      void(uint_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI3iv)>
      VertexAttribI3iv{"VertexAttribI3iv", *this};

    /// @var VertexAttribI4iv
    /// @glfuncwrap{VertexAttribI4iv}
    gl_api_function<
      void(uint_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI4iv)>
      VertexAttribI4iv{"VertexAttribI4iv", *this};

    /// @var VertexAttribI1ui
    /// @glfuncwrap{VertexAttribI1ui}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI1ui)>
      VertexAttribI1ui{"VertexAttribI1ui", *this};

    /// @var VertexAttribI2ui
    /// @glfuncwrap{VertexAttribI2ui}
    gl_api_function<
      void(uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI2ui)>
      VertexAttribI2ui{"VertexAttribI2ui", *this};

    /// @var VertexAttribI3ui
    /// @glfuncwrap{VertexAttribI3ui}
    gl_api_function<
      void(uint_type, uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI3ui)>
      VertexAttribI3ui{"VertexAttribI3ui", *this};

    /// @var VertexAttribI4ui
    /// @glfuncwrap{VertexAttribI4ui}
    gl_api_function<
      void(uint_type, uint_type, uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI4ui)>
      VertexAttribI4ui{"VertexAttribI4ui", *this};

    /// @var VertexAttribI1uiv
    /// @glfuncwrap{VertexAttribI1uiv}
    gl_api_function<
      void(uint_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI1uiv)>
      VertexAttribI1uiv{"VertexAttribI1uiv", *this};

    /// @var VertexAttribI2uiv
    /// @glfuncwrap{VertexAttribI2uiv}
    gl_api_function<
      void(uint_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI2uiv)>
      VertexAttribI2uiv{"VertexAttribI2uiv", *this};

    /// @var VertexAttribI3uiv
    /// @glfuncwrap{VertexAttribI3uiv}
    gl_api_function<
      void(uint_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI3uiv)>
      VertexAttribI3uiv{"VertexAttribI3uiv", *this};

    /// @var VertexAttribI4uiv
    /// @glfuncwrap{VertexAttribI4uiv}
    gl_api_function<
      void(uint_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI4uiv)>
      VertexAttribI4uiv{"VertexAttribI4uiv", *this};

    /// @var VertexAttribI4bv
    /// @glfuncwrap{VertexAttribI4bv}
    gl_api_function<
      void(uint_type, const byte_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI4bv)>
      VertexAttribI4bv{"VertexAttribI4bv", *this};

    /// @var VertexAttribI4ubv
    /// @glfuncwrap{VertexAttribI4ubv}
    gl_api_function<
      void(uint_type, const ubyte_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI4ubv)>
      VertexAttribI4ubv{"VertexAttribI4ubv", *this};

    /// @var VertexAttribI4sv
    /// @glfuncwrap{VertexAttribI4sv}
    gl_api_function<
      void(uint_type, const short_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI4sv)>
      VertexAttribI4sv{"VertexAttribI4sv", *this};

    /// @var VertexAttribI4usv
    /// @glfuncwrap{VertexAttribI4usv}
    gl_api_function<
      void(uint_type, const ushort_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribI4usv)>
      VertexAttribI4usv{"VertexAttribI4usv", *this};

    /// @var VertexAttrib4bv
    /// @glfuncwrap{VertexAttrib4bv}
    gl_api_function<
      void(uint_type, const byte_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4bv)>
      VertexAttrib4bv{"VertexAttrib4bv", *this};

    /// @var VertexAttrib4ubv
    /// @glfuncwrap{VertexAttrib4ubv}
    gl_api_function<
      void(uint_type, const ubyte_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4ubv)>
      VertexAttrib4ubv{"VertexAttrib4ubv", *this};

    /// @var VertexAttrib4usv
    /// @glfuncwrap{VertexAttrib4usv}
    gl_api_function<
      void(uint_type, const ushort_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4usv)>
      VertexAttrib4usv{"VertexAttrib4usv", *this};

    /// @var VertexAttrib4iv
    /// @glfuncwrap{VertexAttrib4iv}
    gl_api_function<
      void(uint_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4iv)>
      VertexAttrib4iv{"VertexAttrib4iv", *this};

    /// @var VertexAttrib4uiv
    /// @glfuncwrap{VertexAttrib4uiv}
    gl_api_function<
      void(uint_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4uiv)>
      VertexAttrib4uiv{"VertexAttrib4uiv", *this};

    /// @var VertexAttrib4Nub
    /// @glfuncwrap{VertexAttrib4Nub}
    gl_api_function<
      void(uint_type, ubyte_type, ubyte_type, ubyte_type, ubyte_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4Nub)>
      VertexAttrib4Nub{"VertexAttrib4Nub", *this};

    /// @var VertexAttrib4Nbv
    /// @glfuncwrap{VertexAttrib4Nbv}
    gl_api_function<
      void(uint_type, const byte_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4Nbv)>
      VertexAttrib4Nbv{"VertexAttrib4Nbv", *this};

    /// @var VertexAttrib4Nubv
    /// @glfuncwrap{VertexAttrib4Nubv}
    gl_api_function<
      void(uint_type, const ubyte_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4Nubv)>
      VertexAttrib4Nubv{"VertexAttrib4Nubv", *this};

    /// @var VertexAttrib4Nsv
    /// @glfuncwrap{VertexAttrib4Nsv}
    gl_api_function<
      void(uint_type, const short_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4Nsv)>
      VertexAttrib4Nsv{"VertexAttrib4Nsv", *this};

    /// @var VertexAttrib4Nusv
    /// @glfuncwrap{VertexAttrib4Nusv}
    gl_api_function<
      void(uint_type, const ushort_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4Nusv)>
      VertexAttrib4Nusv{"VertexAttrib4Nusv", *this};

    /// @var VertexAttrib4Niv
    /// @glfuncwrap{VertexAttrib4Niv}
    gl_api_function<
      void(uint_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4Niv)>
      VertexAttrib4Niv{"VertexAttrib4Niv", *this};

    /// @var VertexAttrib4Nuiv
    /// @glfuncwrap{VertexAttrib4Nuiv}
    gl_api_function<
      void(uint_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttrib4Nuiv)>
      VertexAttrib4Nuiv{"VertexAttrib4Nuiv", *this};

    /// @var VertexAttribL1d
    /// @glfuncwrap{VertexAttribL1d}
    gl_api_function<
      void(uint_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribL1d)>
      VertexAttribL1d{"VertexAttribL1d", *this};

    /// @var VertexAttribL2d
    /// @glfuncwrap{VertexAttribL2d}
    gl_api_function<
      void(uint_type, double_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribL2d)>
      VertexAttribL2d{"VertexAttribL2d", *this};

    /// @var VertexAttribL3d
    /// @glfuncwrap{VertexAttribL3d}
    gl_api_function<
      void(uint_type, double_type, double_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribL3d)>
      VertexAttribL3d{"VertexAttribL3d", *this};

    /// @var VertexAttribL4d
    /// @glfuncwrap{VertexAttribL4d}
    gl_api_function<
      void(uint_type, double_type, double_type, double_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribL4d)>
      VertexAttribL4d{"VertexAttribL4d", *this};

    /// @var VertexAttribL1dv
    /// @glfuncwrap{VertexAttribL1dv}
    gl_api_function<
      void(uint_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribL1dv)>
      VertexAttribL1dv{"VertexAttribL1dv", *this};

    /// @var VertexAttribL2dv
    /// @glfuncwrap{VertexAttribL2dv}
    gl_api_function<
      void(uint_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribL2dv)>
      VertexAttribL2dv{"VertexAttribL2dv", *this};

    /// @var VertexAttribL3dv
    /// @glfuncwrap{VertexAttribL3dv}
    gl_api_function<
      void(uint_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribL3dv)>
      VertexAttribL3dv{"VertexAttribL3dv", *this};

    /// @var VertexAttribL4dv
    /// @glfuncwrap{VertexAttribL4dv}
    gl_api_function<
      void(uint_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribL4dv)>
      VertexAttribL4dv{"VertexAttribL4dv", *this};

    /// @var VertexAttrib4P1ui
    /// @glfuncwrap{VertexAttrib4P1ui}
    gl_api_function<
      void(uint_type, enum_type, bool_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribP1ui)>
      VertexAttribP1ui{"VertexAttribP1ui", *this};

    /// @var VertexAttribP2ui
    /// @glfuncwrap{VertexAttribP2ui}
    gl_api_function<
      void(uint_type, enum_type, bool_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribP2ui)>
      VertexAttribP2ui{"VertexAttribP2ui", *this};

    /// @var VertexAttribP3ui
    /// @glfuncwrap{VertexAttribP3ui}
    gl_api_function<
      void(uint_type, enum_type, bool_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribP3ui)>
      VertexAttribP3ui{"VertexAttribP3ui", *this};

    /// @var VertexAttribP4ui
    /// @glfuncwrap{VertexAttribP4ui}
    gl_api_function<
      void(uint_type, enum_type, bool_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribP4ui)>
      VertexAttribP4ui{"VertexAttribP4ui", *this};

    /// @var VertexAttribP1uiv
    /// @glfuncwrap{VertexAttribP1uiv}
    gl_api_function<
      void(uint_type, enum_type, bool_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribP1uiv)>
      VertexAttribP1uiv{"VertexAttribP1uiv", *this};

    /// @var VertexAttribP2uiv
    /// @glfuncwrap{VertexAttribP2uiv}
    gl_api_function<
      void(uint_type, enum_type, bool_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribP2uiv)>
      VertexAttribP2uiv{"VertexAttribP2uiv", *this};

    /// @var VertexAttribP3uiv
    /// @glfuncwrap{VertexAttribP3uiv}
    gl_api_function<
      void(uint_type, enum_type, bool_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribP3uiv)>
      VertexAttribP3uiv{"VertexAttribP3uiv", *this};

    /// @var VertexAttribP4uiv
    /// @glfuncwrap{VertexAttribP4uiv}
    gl_api_function<
      void(uint_type, enum_type, bool_type, const uint_type*),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribP4uiv)>
      VertexAttribP4uiv{"VertexAttribP4uiv", *this};

    /// @var VertexAttribFormat
    /// @glfuncwrap{VertexAttribFormat}
    gl_api_function<
      void(uint_type, int_type, enum_type, bool_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribFormat)>
      VertexAttribFormat{"VertexAttribFormat", *this};

    /// @var VertexAttribIFormat
    /// @glfuncwrap{VertexAttribIFormat}
    gl_api_function<
      void(uint_type, int_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribIFormat)>
      VertexAttribIFormat{"VertexAttribIFormat", *this};

    /// @var VertexAttribLFormat
    /// @glfuncwrap{VertexAttribLFormat}
    gl_api_function<
      void(uint_type, int_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribLFormat)>
      VertexAttribLFormat{"VertexAttribLFormat", *this};

    /// @var VertexArrayAttribFormat
    /// @glfuncwrap{VertexArrayAttribFormat}
    gl_api_function<
      void(uint_type, uint_type, int_type, enum_type, bool_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexArrayAttribFormat)>
      VertexArrayAttribFormat{"VertexArrayAttribFormat", *this};

    /// @var VertexArrayAttribIFormat
    /// @glfuncwrap{VertexArrayAttribIFormat}
    gl_api_function<
      void(uint_type, uint_type, int_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexArrayAttribIFormat)>
      VertexArrayAttribIFormat{"VertexArrayAttribIFormat", *this};

    /// @var VertexArrayAttribLFormat
    /// @glfuncwrap{VertexArrayAttribLFormat}
    gl_api_function<
      void(uint_type, uint_type, int_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(VertexArrayAttribLFormat)>
      VertexArrayAttribLFormat{"VertexArrayAttribLFormat", *this};

    /// @var VertexAttribPointer
    /// @glfuncwrap{VertexAttribPointer}
    gl_api_function<
      void(
        uint_type,
        int_type,
        enum_type,
        bool_type,
        sizei_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribPointer)>
      VertexAttribPointer{"VertexAttribPointer", *this};

    /// @var VertexAttribIPointer
    /// @glfuncwrap{VertexAttribIPointer}
    gl_api_function<
      void(uint_type, int_type, enum_type, sizei_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribIPointer)>
      VertexAttribIPointer{"VertexAttribIPointer", *this};

    /// @var VertexAttribLPointer
    /// @glfuncwrap{VertexAttribLPointer}
    gl_api_function<
      void(uint_type, int_type, enum_type, sizei_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(VertexAttribLPointer)>
      VertexAttribLPointer{"VertexAttribLPointer", *this};

    /// @var GetVertexArrayiv
    /// @glfuncwrap{GetVertexArrayiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexArrayiv)>
      GetVertexArrayiv{"GetVertexArrayiv", *this};

    /// @var GetVertexArrayIndexediv
    /// @glfuncwrap{GetVertexArrayIndexediv}
    gl_api_function<
      void(uint_type, uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexArrayIndexediv)>
      GetVertexArrayIndexediv{"GetVertexArrayIndexediv", *this};

    /// @var GetVertexArrayIndexed64iv
    /// @glfuncwrap{GetVertexArrayIndexed64iv}
    gl_api_function<
      void(uint_type, uint_type, enum_type, int64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexArrayIndexed64iv)>
      GetVertexArrayIndexed64iv{"GetVertexArrayIndexed64iv", *this};

    /// @var GetVertexAttribdv
    /// @glfuncwrap{GetVertexAttribdv}
    gl_api_function<
      void(uint_type, enum_type, double_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexAttribdv)>
      GetVertexAttribdv{"GetVertexAttribdv", *this};

    /// @var GetVertexAttribfv
    /// @glfuncwrap{GetVertexAttribfv}
    gl_api_function<
      void(uint_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexAttribfv)>
      GetVertexAttribfv{"GetVertexAttribfv", *this};

    /// @var GetVertexAttribiv
    /// @glfuncwrap{GetVertexAttribiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexAttribiv)>
      GetVertexAttribiv{"GetVertexAttribiv", *this};

    /// @var GetVertexAttribIiv
    /// @glfuncwrap{GetVertexAttribIiv}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexAttribIiv)>
      GetVertexAttribIiv{"GetVertexAttribIiv", *this};

    /// @var GetVertexAttribIuiv
    /// @glfuncwrap{GetVertexAttribIuiv}
    gl_api_function<
      void(uint_type, enum_type, uint_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexAttribIuiv)>
      GetVertexAttribIuiv{"GetVertexAttribIuiv", *this};

    /// @var GetVertexAttribLdv
    /// @glfuncwrap{GetVertexAttribLdv}
    gl_api_function<
      void(uint_type, enum_type, double_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexAttribLdv)>
      GetVertexAttribLdv{"GetVertexAttribLdv", *this};

    /// @var GetVertexAttribPointerv
    /// @glfuncwrap{GetVertexAttribPointerv}
    gl_api_function<
      void(uint_type, enum_type, void_ptr_type*),
      OGLPLUS_GL_STATIC_FUNC(GetVertexAttribPointerv)>
      GetVertexAttribPointerv{"GetVertexAttribPointerv", *this};

    /// @var ClipControl
    /// @glfuncwrap{ClipControl}
    gl_api_function<
      void(enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(ClipControl)>
      ClipControl{"ClipControl", *this};

    /// @var DepthRange
    /// @glfuncwrap{DepthRange}
    gl_api_function<
      void(double_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(DepthRange)>
      DepthRange{"DepthRange", *this};

    /// @var DepthRangef
    /// @glfuncwrap{DepthRangef}
    gl_api_function<
      void(float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(DepthRangef)>
      DepthRangef{"DepthRangef", *this};

    /// @var DepthRangeArrayv
    /// @glfuncwrap{DepthRangeArrayv}
    gl_api_function<
      void(uint_type, sizei_type, const double_type*),
      OGLPLUS_GL_STATIC_FUNC(DepthRangeArrayv)>
      DepthRangeArrayv{"DepthRangeArrayv", *this};

    /// @var DepthRangeIndexed
    /// @glfuncwrap{DepthRangeIndexed}
    gl_api_function<
      void(uint_type, double_type, double_type),
      OGLPLUS_GL_STATIC_FUNC(DepthRangeIndexed)>
      DepthRangeIndexed{"DepthRangeIndexed", *this};

    /// @var Viewport
    /// @glfuncwrap{Viewport}
    gl_api_function<
      void(int_type, int_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(Viewport)>
      Viewport{"Viewport", *this};

    /// @var ViewportArrayv
    /// @glfuncwrap{ViewportArrayv}
    gl_api_function<
      void(uint_type, sizei_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ViewportArrayv)>
      ViewportArrayv{"ViewportArrayv", *this};

    /// @var ViewportIndexedf
    /// @glfuncwrap{ViewportIndexedf}
    gl_api_function<
      void(uint_type, float_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(ViewportIndexedf)>
      ViewportIndexedf{"ViewportIndexedf", *this};

    /// @var ViewportIndexedfv
    /// @glfuncwrap{ViewportIndexedfv}
    gl_api_function<
      void(uint_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ViewportIndexedfv)>
      ViewportIndexedfv{"ViewportIndexedfv", *this};

    /// @var Scissor
    /// @glfuncwrap{Scissor}
    gl_api_function<
      void(int_type, int_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(Scissor)>
      Scissor{"Scissor", *this};

    /// @var ScissorArrayv
    /// @glfuncwrap{ScissorArrayv}
    gl_api_function<
      void(uint_type, sizei_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ScissorArrayv)>
      ScissorArrayv{"ScissorArrayv", *this};

    /// @var ScissorIndexed
    /// @glfuncwrap{ScissorIndexed}
    gl_api_function<
      void(uint_type, int_type, int_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(ScissorIndexed)>
      ScissorIndexed{"ScissorIndexed", *this};

    /// @var ScissorIndexedv
    /// @glfuncwrap{ScissorIndexedv}
    gl_api_function<
      void(uint_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(ScissorIndexedv)>
      ScissorIndexedv{"ScissorIndexedv", *this};

    /// @var StencilFunc
    /// @glfuncwrap{StencilFunc}
    gl_api_function<
      void(enum_type, int_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(StencilFunc)>
      StencilFunc{"StencilFunc", *this};

    /// @var StencilFuncSeparate
    /// @glfuncwrap{StencilFuncSeparate}
    gl_api_function<
      void(enum_type, enum_type, int_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(StencilFuncSeparate)>
      StencilFuncSeparate{"StencilFuncSeparate", *this};

    /// @var StencilOp
    /// @glfuncwrap{StencilOp}
    gl_api_function<
      void(enum_type, enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(StencilOp)>
      StencilOp{"StencilOp", *this};

    /// @var StencilOpSeparate
    /// @glfuncwrap{StencilOpSeparate}
    gl_api_function<
      void(enum_type, enum_type, enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(StencilOpSeparate)>
      StencilOpSeparate{"StencilOpSeparate", *this};

    /// @var DepthFunc
    /// @glfuncwrap{DepthFunc}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(DepthFunc)>
      DepthFunc{"DepthFunc", *this};

    /// @var ColorMask
    /// @glfuncwrap{ColorMask}
    gl_api_function<
      void(bool_type, bool_type, bool_type, bool_type),
      OGLPLUS_GL_STATIC_FUNC(ColorMask)>
      ColorMask{"ColorMask", *this};

    /// @var ColorMaski
    /// @glfuncwrap{ColorMaski}
    gl_api_function<
      void(uint_type, bool_type, bool_type, bool_type, bool_type),
      OGLPLUS_GL_STATIC_FUNC(ColorMaski)>
      ColorMaski{"ColorMaski", *this};

    /// @var DepthMask
    /// @glfuncwrap{DepthMask}
    gl_api_function<void(bool_type), OGLPLUS_GL_STATIC_FUNC(DepthMask)>
      DepthMask{"DepthMask", *this};

    /// @var StencilMask
    /// @glfuncwrap{StencilMask}
    gl_api_function<void(uint_type), OGLPLUS_GL_STATIC_FUNC(StencilMask)>
      StencilMask{"StencilMask", *this};

    /// @var StencilMaskSeparate
    /// @glfuncwrap{StencilMaskSeparate}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(StencilMaskSeparate)>
      StencilMaskSeparate{"StencilMaskSeparate", *this};

    /// @var ClearColor
    /// @glfuncwrap{ClearColor}
    gl_api_function<
      void(float_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(ClearColor)>
      ClearColor{"ClearColor", *this};

    /// @var ClearDepthf
    /// @glfuncwrap{ClearDepthf}
    gl_api_function<void(float_type), OGLPLUS_GL_STATIC_FUNC(ClearDepthf)>
      ClearDepthf{"ClearDepthf", *this};

    /// @var ClearDepth
    /// @glfuncwrap{ClearDepth}
    gl_api_function<void(double_type), OGLPLUS_GL_STATIC_FUNC(ClearDepth)>
      ClearDepth{"ClearDepth", *this};

    /// @var ClearStencil
    /// @glfuncwrap{ClearStencil}
    gl_api_function<void(int_type), OGLPLUS_GL_STATIC_FUNC(ClearStencil)>
      ClearStencil{"ClearStencil", *this};

    /// @var Clear
    /// @glfuncwrap{Clear}
    gl_api_function<void(bitfield_type), OGLPLUS_GL_STATIC_FUNC(Clear)> Clear{
      "Clear",
      *this};

    /// @var PrimitiveRestartIndex
    /// @glfuncwrap{PrimitiveRestartIndex}
    gl_api_function<
      void(uint_type),
      OGLPLUS_GL_STATIC_FUNC(PrimitiveRestartIndex)>
      PrimitiveRestartIndex{"PrimitiveRestartIndex", *this};

    /// @var ProvokingVertex
    /// @glfuncwrap{ProvokingVertex}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(ProvokingVertex)>
      ProvokingVertex{"ProvokingVertex", *this};

    /// @var LineWidth
    /// @glfuncwrap{LineWidth}
    gl_api_function<void(float_type), OGLPLUS_GL_STATIC_FUNC(LineWidth)>
      LineWidth{"LineWidth", *this};

    /// @var PointSize
    /// @glfuncwrap{PointSize}
    gl_api_function<void(float_type), OGLPLUS_GL_STATIC_FUNC(PointSize)>
      PointSize{"PointSize", *this};

    /// @var PointParameteri
    /// @glfuncwrap{PointParameteri}
    gl_api_function<
      void(enum_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(PointParameteri)>
      PointParameteri{"PointParameteri", *this};

    /// @var PointParameterf
    /// @glfuncwrap{PointParameterf}
    gl_api_function<
      void(enum_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(PointParameterf)>
      PointParameterf{"PointParameterf", *this};

    /// @var PointParameteriv
    /// @glfuncwrap{PointParameteriv}
    gl_api_function<
      void(enum_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(PointParameteriv)>
      PointParameteriv{"PointParameteriv", *this};

    /// @var PointParameterfv
    /// @glfuncwrap{PointParameterfv}
    gl_api_function<
      void(enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(PointParameterfv)>
      PointParameterfv{"PointParameterfv", *this};

    /// @var PatchParameteri
    /// @glfuncwrap{PatchParameteri}
    gl_api_function<
      void(enum_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(PatchParameteri)>
      PatchParameteri{"PatchParameteri", *this};

    /// @var PatchParameterfv
    /// @glfuncwrap{PatchParameterfv}
    gl_api_function<
      void(enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(PatchParameterfv)>
      PatchParameterfv{"PatchParameterfv", *this};

    /// @var FrontFace
    /// @glfuncwrap{FrontFace}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(FrontFace)>
      FrontFace{"FrontFace", *this};

    /// @var CullFace
    /// @glfuncwrap{CullFace}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(CullFace)> CullFace{
      "CullFace",
      *this};

    /// @var PolygonMode
    /// @glfuncwrap{PolygonMode}
    gl_api_function<
      void(enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(PolygonMode)>
      PolygonMode{"PolygonMode", *this};

    /// @var PolygonOffset
    /// @glfuncwrap{PolygonOffset}
    gl_api_function<
      void(float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(PolygonOffset)>
      PolygonOffset{"PolygonOffset", *this};

    /// @var PolygonOffsetClamp
    /// @glfuncwrap{PolygonOffsetClamp}
    gl_api_function<
      void(float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(PolygonOffsetClamp)>
      PolygonOffsetClamp{"PolygonOffsetClamp", *this};

    /// @var SampleCoverage
    /// @glfuncwrap{SampleCoverage}
    gl_api_function<
      void(float_type, bool_type),
      OGLPLUS_GL_STATIC_FUNC(SampleCoverage)>
      SampleCoverage{"SampleCoverage", *this};

    /// @var SampleMaski
    /// @glfuncwrap{SampleMaski}
    gl_api_function<
      void(uint_type, bitfield_type),
      OGLPLUS_GL_STATIC_FUNC(SampleMaski)>
      SampleMaski{"SampleMaski", *this};

    /// @var MinSampleShading
    /// @glfuncwrap{MinSampleShading}
    gl_api_function<void(float_type), OGLPLUS_GL_STATIC_FUNC(MinSampleShading)>
      MinSampleShading{"MinSampleShading", *this};

    /// @var GetMultisamplefv
    /// @glfuncwrap{GetMultisamplefv}
    gl_api_function<
      void(enum_type, uint_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetMultisamplefv)>
      GetMultisamplefv{"GetMultisamplefv", *this};

    /// @var BlendEquation
    /// @glfuncwrap{BlendEquation}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(BlendEquation)>
      BlendEquation{"BlendEquation", *this};

    /// @var BlendEquationSeparate
    /// @glfuncwrap{BlendEquationSeparate}
    gl_api_function<
      void(enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BlendEquationSeparate)>
      BlendEquationSeparate{"BlendEquationSeparate", *this};

    /// @var BlendEquationi
    /// @glfuncwrap{BlendEquationi}
    gl_api_function<
      void(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BlendEquationi)>
      BlendEquationi{"BlendEquationi", *this};

    /// @var BlendEquationSeparatei
    /// @glfuncwrap{BlendEquationSeparatei}
    gl_api_function<
      void(uint_type, enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BlendEquationSeparatei)>
      BlendEquationSeparatei{"BlendEquationSeparatei", *this};

    /// @var BlendFunc
    /// @glfuncwrap{BlendFunc}
    gl_api_function<void(enum_type, enum_type), OGLPLUS_GL_STATIC_FUNC(BlendFunc)>
      BlendFunc{"BlendFunc", *this};

    /// @var BlendFuncSeparate
    /// @glfuncwrap{BlendFuncSeparate}
    gl_api_function<
      void(enum_type, enum_type, enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BlendFuncSeparate)>
      BlendFuncSeparate{"BlendFuncSeparate", *this};

    /// @var BlendFunci
    /// @glfuncwrap{BlendFunci}
    gl_api_function<
      void(uint_type, enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BlendFunci)>
      BlendFunci{"BlendFunci", *this};

    /// @var BlendFuncSeparatei
    /// @glfuncwrap{BlendFuncSeparatei}
    gl_api_function<
      void(uint_type, enum_type, enum_type, enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(BlendFuncSeparatei)>
      BlendFuncSeparatei{"BlendFuncSeparatei", *this};

    /// @var BlendColor
    /// @glfuncwrap{BlendColor}
    gl_api_function<
      void(float_type, float_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(BlendColor)>
      BlendColor{"BlendColor", *this};

    /// @var LogicOp
    /// @glfuncwrap{LogicOp}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(LogicOp)> LogicOp{
      "LogicOp",
      *this};

    /// @var DrawArrays
    /// @glfuncwrap{DrawArrays}
    gl_api_function<
      void(enum_type, int_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(DrawArrays)>
      DrawArrays{"DrawArrays", *this};

    /// @var DrawArraysInstancedBaseInstance
    /// @glfuncwrap{DrawArraysInstancedBaseInstance}
    gl_api_function<
      void(enum_type, int_type, sizei_type, sizei_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(DrawArraysInstancedBaseInstance)>
      DrawArraysInstancedBaseInstance{"DrawArraysInstancedBaseInstance", *this};

    /// @var DrawArraysInstanced
    /// @glfuncwrap{DrawArraysInstanced}
    gl_api_function<
      void(enum_type, int_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(DrawArraysInstanced)>
      DrawArraysInstanced{"DrawArraysInstanced", *this};

    /// @var DrawArraysIndirect
    /// @glfuncwrap{DrawArraysIndirect}
    gl_api_function<
      void(enum_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(DrawArraysIndirect)>
      DrawArraysIndirect{"DrawArraysIndirect", *this};

    /// @var MultiDrawArrays
    /// @glfuncwrap{MultiDrawArrays}
    gl_api_function<
      void(enum_type, const int_type*, const sizei_type*, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(MultiDrawArrays)>
      MultiDrawArrays{"MultiDrawArrays", *this};

    /// @var MultiDrawArraysIndirect
    /// @glfuncwrap{MultiDrawArraysIndirect}
    gl_api_function<
      void(enum_type, const_void_ptr_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(MultiDrawArraysIndirect)>
      MultiDrawArraysIndirect{"MultiDrawArraysIndirect", *this};

    /// @var MultiDrawArraysIndirectCount
    /// @glfuncwrap{MultiDrawArraysIndirectCount}
    gl_api_function<
      void(enum_type, const_void_ptr_type, intptr_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(MultiDrawArraysIndirectCount)>
      MultiDrawArraysIndirectCount{"MultiDrawArraysIndirectCount", *this};

    /// @var DrawElements
    /// @glfuncwrap{DrawElements}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(DrawElements)>
      DrawElements{"DrawElements", *this};

    /// @var DrawRangeElements
    /// @glfuncwrap{DrawRangeElements}
    gl_api_function<
      void(
        enum_type,
        uint_type,
        uint_type,
        sizei_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(DrawRangeElements)>
      DrawRangeElements{"DrawRangeElements", *this};

    /// @var DrawElementsInstancedBaseInstance
    /// @glfuncwrap{DrawElementsInstancedBaseInstance}
    gl_api_function<
      void(
        enum_type,
        sizei_type,
        enum_type,
        const_void_ptr_type,
        sizei_type,
        uint_type),
      OGLPLUS_GL_STATIC_FUNC(DrawElementsInstancedBaseInstance)>
      DrawElementsInstancedBaseInstance{
        "DrawElementsInstancedBaseInstance",
        *this};

    /// @var DrawElementsInstanced
    /// @glfuncwrap{DrawElementsInstanced}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, const_void_ptr_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(DrawElementsInstanced)>
      DrawElementsInstanced{"DrawElementsInstanced", *this};

    /// @var DrawElementsBaseVertex
    /// @glfuncwrap{DrawElementsBaseVertex}
    gl_api_function<
      void(enum_type, sizei_type, enum_type, const_void_ptr_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(DrawElementsBaseVertex)>
      DrawElementsBaseVertex{"DrawElementsBaseVertex", *this};

    /// @var DrawRangeElementsBaseVertex
    /// @glfuncwrap{DrawRangeElementsBaseVertex}
    gl_api_function<
      void(
        enum_type,
        uint_type,
        uint_type,
        sizei_type,
        enum_type,
        const_void_ptr_type,
        int_type),
      OGLPLUS_GL_STATIC_FUNC(DrawRangeElementsBaseVertex)>
      DrawRangeElementsBaseVertex{"DrawRangeElementsBaseVertex", *this};

    /// @var DrawElementsInstancedBaseVertex
    /// @glfuncwrap{DrawElementsInstancedBaseVertex}
    gl_api_function<
      void(
        enum_type,
        sizei_type,
        enum_type,
        const_void_ptr_type,
        sizei_type,
        int_type),
      OGLPLUS_GL_STATIC_FUNC(DrawElementsInstancedBaseVertex)>
      DrawElementsInstancedBaseVertex{"DrawElementsInstancedBaseVertex", *this};

    /// @var DrawElementsInstancedBaseVertexBaseInstance
    /// @glfuncwrap{DrawElementsInstancedBaseVertexBaseInstance}
    gl_api_function<
      void(
        enum_type,
        sizei_type,
        enum_type,
        const_void_ptr_type,
        sizei_type,
        int_type,
        uint_type),
      OGLPLUS_GL_STATIC_FUNC(DrawElementsInstancedBaseVertexBaseInstance)>
      DrawElementsInstancedBaseVertexBaseInstance{
        "DrawElementsInstancedBaseVertexBaseInstance",
        *this};

    /// @var DrawElementsIndirect
    /// @glfuncwrap{DrawElementsIndirect}
    gl_api_function<
      void(enum_type, enum_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(DrawElementsIndirect)>
      DrawElementsIndirect{"DrawElementsIndirect", *this};

    /// @var MultiDrawElements
    /// @glfuncwrap{MultiDrawElements}
    gl_api_function<
      void(
        enum_type,
        const sizei_type*,
        enum_type,
        const const_void_ptr_type*,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(MultiDrawElements)>
      MultiDrawElements{"MultiDrawElements", *this};

    /// @var MultiDrawElementsIndirect
    /// @glfuncwrap{MultiDrawElementsIndirect}
    gl_api_function<
      void(enum_type, enum_type, const_void_ptr_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(MultiDrawElementsIndirect)>
      MultiDrawElementsIndirect{"MultiDrawElementsIndirect", *this};

    /// @var MultiDrawElementsIndirectCount
    /// @glfuncwrap{MultiDrawElementsIndirectCount}
    gl_api_function<
      void(
        enum_type,
        enum_type,
        const_void_ptr_type,
        intptr_type,
        sizei_type,
        sizei_type),
      OGLPLUS_GL_STATIC_FUNC(MultiDrawElementsIndirectCount)>
      MultiDrawElementsIndirectCount{"MultiDrawElementsIndirectCount", *this};

    /// @var MultiDrawElementsBaseVertex
    /// @glfuncwrap{MultiDrawElementsBaseVertex}
    gl_api_function<
      void(
        enum_type,
        const sizei_type*,
        enum_type,
        const const_void_ptr_type*,
        sizei_type,
        const int_type*),
      OGLPLUS_GL_STATIC_FUNC(MultiDrawElementsBaseVertex)>
      MultiDrawElementsBaseVertex{"MultiDrawElementsBaseVertex", *this};

    /// @var DrawTransformFeedback
    /// @glfuncwrap{DrawTransformFeedback}
    gl_api_function<
      void(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(DrawTransformFeedback)>
      DrawTransformFeedback{"DrawTransformFeedback", *this};

    /// @var DrawTransformFeedbackInstanced
    /// @glfuncwrap{DrawTransformFeedbackInstanced}
    gl_api_function<
      void(enum_type, uint_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(DrawTransformFeedbackInstanced)>
      DrawTransformFeedbackInstanced{"DrawTransformFeedbackInstanced", *this};

    /// @var DrawTransformFeedbackStream
    /// @glfuncwrap{DrawTransformFeedbackStream}
    gl_api_function<
      void(enum_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(DrawTransformFeedbackStream)>
      DrawTransformFeedbackStream{"DrawTransformFeedbackStream", *this};

    /// @var DrawTransformFeedbackStreamInstanced
    /// @glfuncwrap{DrawTransformFeedbackStreamInstanced}
    gl_api_function<
      void(enum_type, uint_type, uint_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(DrawTransformFeedbackStreamInstanced)>
      DrawTransformFeedbackStreamInstanced{
        "DrawTransformFeedbackStreamInstanced",
        *this};

    /// @var DispatchCompute
    /// @glfuncwrap{DispatchCompute}
    gl_api_function<
      void(uint_type, uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(DispatchCompute)>
      DispatchCompute{"DispatchCompute", *this};

    /// @var DispatchComputeIndirect
    /// @glfuncwrap{DispatchComputeIndirect}
    gl_api_function<
      void(intptr_type),
      OGLPLUS_GL_STATIC_FUNC(DispatchComputeIndirect)>
      DispatchComputeIndirect{"DispatchComputeIndirect", *this};

    /// @var ClampColor
    /// @glfuncwrap{ClampColor}
    gl_api_function<
      void(enum_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(ClampColor)>
      ClampColor{"ClampColor", *this};

    /// @var ReadPixels
    /// @glfuncwrap{ReadPixels}
    gl_api_function<
      void(
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        enum_type,
        enum_type,
        void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(ReadPixels)>
      ReadPixels{"ReadPixels", *this};

    /// @var ReadnPixels
    /// @glfuncwrap{ReadnPixels}
    gl_api_function<
      void(
        int_type,
        int_type,
        sizei_type,
        sizei_type,
        enum_type,
        enum_type,
        sizei_type,
        void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(ReadnPixels)>
      ReadnPixels{"ReadnPixels", *this};

    /// @var GetBooleanv
    /// @glfuncwrap{GetBooleanv}
    gl_api_function<
      void(enum_type, bool_type*),
      OGLPLUS_GL_STATIC_FUNC(GetBooleanv)>
      GetBooleanv{"GetBooleanv", *this};

    /// @var GetBooleani_v
    /// @glfuncwrap{GetBooleani_v}
    gl_api_function<
      void(enum_type, uint_type, bool_type*),
      OGLPLUS_GL_STATIC_FUNC(GetBooleani_v)>
      GetBooleani_v{"GetBooleani_v", *this};

    /// @var GetIntegerv
    /// @glfuncwrap{GetIntegerv}
    gl_api_function<
      void(enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetIntegerv)>
      GetIntegerv{"GetIntegerv", *this};

    /// @var GetIntegeri_v
    /// @glfuncwrap{GetIntegeri_v}
    gl_api_function<
      void(enum_type, uint_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetIntegeri_v)>
      GetIntegeri_v{"GetIntegeri_v", *this};

    /// @var GetInteger64v
    /// @glfuncwrap{GetInteger64v}
    gl_api_function<
      void(enum_type, int64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetInteger64v)>
      GetInteger64v{"GetInteger64v", *this};

    /// @var GetInteger64i_v
    /// @glfuncwrap{GetInteger64i_v}
    gl_api_function<
      void(enum_type, uint_type, int64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetInteger64i_v)>
      GetInteger64i_v{"GetInteger64i_v", *this};

    /// @var GetFloatv
    /// @glfuncwrap{GetFloatv}
    gl_api_function<
      void(enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetFloatv)>
      GetFloatv{"GetFloatv", *this};

    /// @var GetFloati_v
    /// @glfuncwrap{GetFloati_v}
    gl_api_function<
      void(enum_type, uint_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetFloati_v)>
      GetFloati_v{"GetFloati_v", *this};

    /// @var GetDoublev
    /// @glfuncwrap{GetDoublev}
    gl_api_function<
      void(enum_type, double_type*),
      OGLPLUS_GL_STATIC_FUNC(GetDoublev)>
      GetDoublev{"GetDoublev", *this};

    /// @var GetDoublei_v
    /// @glfuncwrap{GetDoublei_v}
    gl_api_function<
      void(enum_type, uint_type, double_type*),
      OGLPLUS_GL_STATIC_FUNC(GetDoublei_v)>
      GetDoublei_v{"GetDoublei_v", *this};

    /// @var GetInternalformativ
    /// @glfuncwrap{GetInternalformativ}
    gl_api_function<
      void(enum_type, enum_type, enum_type, sizei_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetInternalformativ)>
      GetInternalformativ{"GetInternalformativ", *this};

    /// @var GetInternalformati64v
    /// @glfuncwrap{GetInternalformati64v}
    gl_api_function<
      void(enum_type, enum_type, enum_type, sizei_type, int64_type*),
      OGLPLUS_GL_STATIC_FUNC(GetInternalformati64v)>
      GetInternalformati64v{"GetInternalformati64v", *this};

    /// @var GetPointerv
    /// @glfuncwrap{GetPointerv}
    gl_api_function<
      void(enum_type, void_ptr_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPointerv)>
      GetPointerv{"GetPointerv", *this};

    /// @var GetStringi
    /// @glfuncwrap{GetStringi}
    gl_api_function<
      const ubyte_type*(enum_type),
      OGLPLUS_GL_STATIC_FUNC(GetString)>
      GetString{"GetString", *this};

    /// @var GetStringi
    /// @glfuncwrap{GetStringi}
    gl_api_function<
      const ubyte_type*(enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(GetStringi)>
      GetStringi{"GetStringi", *this};

    /// @var NamedString
    /// @glfuncwrap{NamedStringARB}
    gl_api_function<
      void(enum_type, int_type, const char_type*, int_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(nullptr)>
      NamedString{"NamedStringARB", *this};

    /// @var DeleteNamedString
    /// @glfuncwrap{DeleteNamedStringARB}
    gl_api_function<
      void(int_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(nullptr)>
      DeleteNamedString{"DeleteNamedStringARB", *this};

    /// @var IsNamedString
    /// @glfuncwrap{IsNamedStringARB}
    gl_api_function<
      bool_type(int_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(nullptr)>
      IsNamedString{"IsNamedStringARB", *this};

    /// @var GetNamedStringiv
    /// @glfuncwrap{GetNamedStringivARB}
    gl_api_function<
      void(int_type, const char_type*, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(nullptr)>
      GetNamedStringiv{"GetNamedStringivARB", *this};

    /// @var GetNamedString
    /// @glfuncwrap{GetNamedStringARB}
    gl_api_function<
      void(int_type, const char_type*, sizei_type, int_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(nullptr)>
      GetNamedString{"GetNamedStringARB", *this};

    /// @var DebugMessageCallback
    /// @glfuncwrap{DebugMessageCallback}
    gl_api_function<
      void(debug_callback_type*, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(DebugMessageCallback)>
      DebugMessageCallback{"DebugMessageCallback", *this};

    /// @var DebugMessageControl
    /// @glfuncwrap{DebugMessageControl}
    gl_api_function<
      void(enum_type, enum_type, enum_type, sizei_type, const uint_type*, bool_type),
      OGLPLUS_GL_STATIC_FUNC(DebugMessageControl)>
      DebugMessageControl{"DebugMessageControl", *this};

    /// @var DebugMessageInsert
    /// @glfuncwrap{DebugMessageInsert}
    gl_api_function<
      void(enum_type, enum_type, uint_type, enum_type, int_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(DebugMessageInsert)>
      DebugMessageInsert{"DebugMessageInsert", *this};

    /// @var PushDebugGroup
    /// @glfuncwrap{PushDebugGroup}
    gl_api_function<
      void(enum_type, uint_type, sizei_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(PushDebugGroup)>
      PushDebugGroup{"PushDebugGroup", *this};

    /// @var PopDebugGroup
    /// @glfuncwrap{PopDebugGroup}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(PopDebugGroup)> PopDebugGroup{
      "PopDebugGroup",
      *this};

    /// @var ObjectLabel
    /// @glfuncwrap{ObjectLabel}
    gl_api_function<
      void(enum_type, uint_type, sizei_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(ObjectLabel)>
      ObjectLabel{"ObjectLabel", *this};

    /// @var ObjectPtrLabel
    /// @glfuncwrap{ObjectPtrLabel}
    gl_api_function<
      void(const_void_ptr_type, sizei_type, const char_type*),
      OGLPLUS_GL_STATIC_FUNC(ObjectPtrLabel)>
      ObjectPtrLabel{"ObjectPtrLabel", *this};

    /// @var GetObjectLabel
    /// @glfuncwrap{GetObjectLabel}
    gl_api_function<
      void(enum_type, uint_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetObjectLabel)>
      GetObjectLabel{"GetObjectLabel", *this};

    /// @var GetObjectPtrLabel
    /// @glfuncwrap{GetObjectPtrLabel}
    gl_api_function<
      void(const_void_ptr_type, sizei_type, sizei_type*, char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetObjectPtrLabel)>
      GetObjectPtrLabel{"GetObjectPtrLabel", *this};

    /// @var GetDebugMessageLog
    /// @glfuncwrap{GetDebugMessageLog}
    gl_api_function<
      uint_type(
        uint_type,
        sizei_type,
        enum_type*,
        enum_type*,
        uint_type*,
        enum_type*,
        sizei_type*,
        char_type*),
      OGLPLUS_GL_STATIC_FUNC(GetDebugMessageLog)>
      GetDebugMessageLog{"GetDebugMessageLog", *this};

    /// @var Begin
    /// @glfuncwrap{Begin}
    gl_api_function<void(enum_type), nullptr> Begin{"Begin", *this};

    /// @var End
    /// @glfuncwrap{End}
    gl_api_function<void(), nullptr> End{"End", *this};

    /// @var Vertex2i
    /// @glfuncwrap{Vertex2i}
    gl_api_function<void(int_type, int_type), nullptr> Vertex2i{
      "Vertex2i",
      *this};

    /// @var Vertex3i
    /// @glfuncwrap{Vertex3i}
    gl_api_function<void(int_type, int_type, int_type), nullptr> Vertex3i{
      "Vertex3i",
      *this};

    /// @var Vertex4i
    /// @glfuncwrap{Vertex4i}
    gl_api_function<void(int_type, int_type, int_type, int_type), nullptr>
      Vertex4i{"Vertex4i", *this};

    /// @var Vertex2f
    /// @glfuncwrap{Vertex2f}
    gl_api_function<void(float_type, float_type), nullptr> Vertex2f{
      "Vertex2f",
      *this};

    /// @var Vertex3f
    /// @glfuncwrap{Vertex3f}
    gl_api_function<void(float_type, float_type, float_type), nullptr> Vertex3f{
      "Vertex3f",
      *this};

    /// @var Vertex4f
    /// @glfuncwrap{Vertex4f}
    gl_api_function<void(float_type, float_type, float_type, float_type), nullptr>
      Vertex4f{"Vertex4f", *this};

    /// @var Color3i
    /// @glfuncwrap{Color3i}
    gl_api_function<void(int_type, int_type, int_type), nullptr> Color3i{
      "Color3i",
      *this};

    /// @var Color4i
    /// @glfuncwrap{Color4i}
    gl_api_function<void(int_type, int_type, int_type, int_type), nullptr>
      Color4i{"Color4i", *this};

    /// @var Color3f
    /// @glfuncwrap{Color3f}
    gl_api_function<void(float_type, float_type, float_type), nullptr> Color3f{
      "Color3f",
      *this};

    /// @var Color4f
    /// @glfuncwrap{Color4f}
    gl_api_function<void(float_type, float_type, float_type, float_type), nullptr>
      Color4f{"Color4f", *this};

    /// @var SecondaryColor3i
    /// @glfuncwrap{SecondaryColor3i}
    gl_api_function<void(int_type, int_type, int_type), nullptr>
      SecondaryColor3i{"SecondaryColor3i", *this};

    /// @var SecondaryColor4i
    /// @glfuncwrap{SecondaryColor4i}
    gl_api_function<void(int_type, int_type, int_type, int_type), nullptr>
      SecondaryColor4i{"SecondaryColor4i", *this};

    /// @var SecondaryColor3f
    /// @glfuncwrap{SecondaryColor3f}
    gl_api_function<void(float_type, float_type, float_type), nullptr>
      SecondaryColor3f{"SecondaryColor3f", *this};

    /// @var SecondaryColor4f
    /// @glfuncwrap{SecondaryColor4f}
    gl_api_function<void(float_type, float_type, float_type, float_type), nullptr>
      SecondaryColor4f{"SecondaryColor4f", *this};

    /// @var TexCoord1i
    /// @glfuncwrap{TexCoord1i}
    gl_api_function<void(int_type), nullptr> TexCoord1i{"TexCoord1i", *this};

    /// @var TexCoord2i
    /// @glfuncwrap{TexCoord2i}
    gl_api_function<void(int_type, int_type), nullptr> TexCoord2i{
      "TexCoord2i",
      *this};

    /// @var TexCoord3i
    /// @glfuncwrap{TexCoord3i}
    gl_api_function<void(int_type, int_type, int_type), nullptr> TexCoord3i{
      "TexCoord3i",
      *this};

    /// @var TexCoord4i
    /// @glfuncwrap{TexCoord4i}
    gl_api_function<void(int_type, int_type, int_type, int_type), nullptr>
      TexCoord4i{"TexCoord4i", *this};

    /// @var TexCoord1f
    /// @glfuncwrap{TexCoord1f}
    gl_api_function<void(float_type), nullptr> TexCoord1f{"TexCoord1f", *this};

    /// @var TexCoord2f
    /// @glfuncwrap{TexCoord2f}
    gl_api_function<void(float_type, float_type), nullptr> TexCoord2f{
      "TexCoord2f",
      *this};

    /// @var TexCoord3f
    /// @glfuncwrap{TexCoord3f}
    gl_api_function<void(float_type, float_type, float_type), nullptr>
      TexCoord3f{"TexCoord3f", *this};

    /// @var TexCoord4f
    /// @glfuncwrap{TexCoord4f}
    gl_api_function<void(float_type, float_type, float_type, float_type), nullptr>
      TexCoord4f{"TexCoord4f", *this};

    /// @var MultiTexCoord1i
    /// @glfuncwrap{MultiTexCoord1i}
    gl_api_function<void(enum_type, int_type), nullptr> MultiTexCoord1i{
      "MultiTexCoord1i",
      *this};

    /// @var MultiTexCoord2i
    /// @glfuncwrap{MultiTexCoord2i}
    gl_api_function<void(enum_type, int_type, int_type), nullptr>
      MultiTexCoord2i{"MultiTexCoord2i", *this};

    /// @var MultiTexCoord3i
    /// @glfuncwrap{MultiTexCoord3i}
    gl_api_function<void(enum_type, int_type, int_type, int_type), nullptr>
      MultiTexCoord3i{"MultiTexCoord3i", *this};

    /// @var MultiTexCoord4i
    /// @glfuncwrap{MultiTexCoord4i}
    gl_api_function<
      void(enum_type, int_type, int_type, int_type, int_type),
      nullptr>
      MultiTexCoord4i{"MultiTexCoord4i", *this};

    /// @var MultiTexCoord1f
    /// @glfuncwrap{MultiTexCoord1f}
    gl_api_function<void(enum_type, float_type), nullptr> MultiTexCoord1f{
      "MultiTexCoord1f",
      *this};

    /// @var MultiTexCoord2f
    /// @glfuncwrap{MultiTexCoord2f}
    gl_api_function<void(enum_type, float_type, float_type), nullptr>
      MultiTexCoord2f{"MultiTexCoord2f", *this};

    /// @var MultiTexCoord3f
    /// @glfuncwrap{MultiTexCoord3f}
    gl_api_function<void(enum_type, float_type, float_type, float_type), nullptr>
      MultiTexCoord3f{"MultiTexCoord3f", *this};

    /// @var MultiTexCoord4f
    /// @glfuncwrap{MultiTexCoord4f}
    gl_api_function<
      void(enum_type, float_type, float_type, float_type, float_type),
      nullptr>
      MultiTexCoord4f{"MultiTexCoord4f", *this};

    /// @var MatrixMode
    /// @glfuncwrap{MatrixMode}
    gl_api_function<void(enum_type), nullptr> MatrixMode{"MatrixMode", *this};

    /// @var PushMatrix
    /// @glfuncwrap{PushMatrix}
    gl_api_function<void(void), nullptr> PushMatrix{"PushMatrix", *this};

    /// @var PopMatrix
    /// @glfuncwrap{PopMatrix}
    gl_api_function<void(void), nullptr> PopMatrix{"PopMatrix", *this};

    /// @var MatrixPushEXT
    /// @glfuncwrap{MatrixPushEXT}
    gl_api_function<void(enum_type), nullptr> MatrixPushEXT{
      "MatrixPushEXT",
      *this};

    /// @var MatrixPopEXT
    /// @glfuncwrap{MatrixPopEXT}
    gl_api_function<void(enum_type), nullptr> MatrixPopEXT{
      "MatrixPopEXT",
      *this};

    /// @var LoadIdentity
    /// @glfuncwrap{LoadIdentity}
    gl_api_function<void(), nullptr> LoadIdentity{"LoadIdentity", *this};

    /// @var MatrixLoadIdentityEXT
    /// @glfuncwrap{MatrixLoadIdentityEXT}
    gl_api_function<void(enum_type), nullptr> MatrixLoadIdentityEXT{
      "MatrixLoadIdentityEXT",
      *this};

    /// @var Translatef
    /// @glfuncwrap{Translatef}
    gl_api_function<void(float_type, float_type, float_type), nullptr>
      Translatef{"Translatef", *this};

    /// @var Translated
    /// @glfuncwrap{Translated}
    gl_api_function<void(double_type, double_type, double_type), nullptr>
      Translated{"Translated", *this};

    /// @var MatrixTranslatefEXT
    /// @glfuncwrap{MatrixTranslatefEXT}
    gl_api_function<void(enum_type, float_type, float_type, float_type), nullptr>
      MatrixTranslatefEXT{"MatrixTranslatefEXT", *this};

    /// @var MatrixTranslatedEXT
    /// @glfuncwrap{MatrixTranslatedEXT}
    gl_api_function<
      void(enum_type, double_type, double_type, double_type),
      nullptr>
      MatrixTranslatedEXT{"MatrixTranslatedEXT", *this};

    /// @var Rotatef
    /// @glfuncwrap{Rotatef}
    gl_api_function<void(float_type, float_type, float_type, float_type), nullptr>
      Rotatef{"Rotatef", *this};

    /// @var Rotated
    /// @glfuncwrap{Rotated}
    gl_api_function<
      void(double_type, double_type, double_type, double_type),
      nullptr>
      Rotated{"Rotated", *this};

    /// @var MatrixRotatefEXT
    /// @glfuncwrap{MatrixRotatefEXT}
    gl_api_function<
      void(enum_type, float_type, float_type, float_type, float_type),
      nullptr>
      MatrixRotatefEXT{"MatrixRotatefEXT", *this};

    /// @var MatrixRotatedEXT
    /// @glfuncwrap{MatrixRotatedEXT}
    gl_api_function<
      void(enum_type, double_type, double_type, double_type, double_type),
      nullptr>
      MatrixRotatedEXT{"MatrixRotatedEXT", *this};

    /// @var Scalef
    /// @glfuncwrap{Scalef}
    gl_api_function<void(float_type, float_type, float_type), nullptr> Scalef{
      "Scalef",
      *this};

    /// @var Scaled
    /// @glfuncwrap{Scaled}
    gl_api_function<void(double_type, double_type, double_type), nullptr> Scaled{
      "Scaled",
      *this};

    /// @var MatrixScalefEXT
    /// @glfuncwrap{MatrixScalefEXT}
    gl_api_function<void(enum_type, float_type, float_type, float_type), nullptr>
      MatrixScalefEXT{"MatrixScalefEXT", *this};

    /// @var MatrixScaledEXT
    /// @glfuncwrap{MatrixScaledEXT}
    gl_api_function<
      void(enum_type, double_type, double_type, double_type),
      nullptr>
      MatrixScaledEXT{"MatrixScaledEXT", *this};

    /// @var Frustum
    /// @glfuncwrap{Frustum}
    gl_api_function<
      void(
        double_type,
        double_type,
        double_type,
        double_type,
        double_type,
        double_type),
      nullptr>
      Frustum{"Frustum", *this};

    /// @var Ortho
    /// @glfuncwrap{Ortho}
    gl_api_function<
      void(
        double_type,
        double_type,
        double_type,
        double_type,
        double_type,
        double_type),
      nullptr>
      Ortho{"Ortho", *this};

    /// @var MatrixFrustumEXT
    /// @glfuncwrap{MatrixFrustumEXT}
    gl_api_function<
      void(
        enum_type,
        double_type,
        double_type,
        double_type,
        double_type,
        double_type),
      nullptr>
      MatrixFrustumEXT{"MatrixFrustumEXT", *this};

    /// @var MatrixOrthoEXT
    /// @glfuncwrap{MatrixOrthoEXT}
    gl_api_function<
      void(
        enum_type,
        double_type,
        double_type,
        double_type,
        double_type,
        double_type),
      nullptr>
      MatrixOrthoEXT{"MatrixOrthoEXT", *this};

    /// @var LoadMatrixf
    /// @glfuncwrap{LoadMatrixf}
    gl_api_function<void(const float_type[16]), nullptr> LoadMatrixf{
      "LoadMatrixf",
      *this};

    /// @var LoadMatrixd
    /// @glfuncwrap{LoadMatrixd}
    gl_api_function<void(const double_type[16]), nullptr> LoadMatrixd{
      "LoadMatrixd",
      *this};

    /// @var MatrixLoadfEXT
    /// @glfuncwrap{MatrixLoadfEXT}
    gl_api_function<void(enum_type, const float_type[16]), nullptr>
      MatrixLoadfEXT{"MatrixLoadfEXT", *this};

    /// @var MatrixLoaddEXT
    /// @glfuncwrap{MatrixLoaddEXT}
    gl_api_function<void(enum_type, const double_type[16]), nullptr>
      MatrixLoaddEXT{"MatrixLoaddEXT", *this};

    /// @var MultMatrixf
    /// @glfuncwrap{MultMatrixf}
    gl_api_function<void(const float_type[16]), nullptr> MultMatrixf{
      "MultMatrixf",
      *this};

    /// @var MultMatrixd
    /// @glfuncwrap{MultMatrixd}
    gl_api_function<void(const double_type[16]), nullptr> MultMatrixd{
      "MultMatrixd",
      *this};

    /// @var MatrixMultfEXT
    /// @glfuncwrap{MatrixMultfEXT}
    gl_api_function<void(enum_type, const float_type[16]), nullptr>
      MatrixMultfEXT{"MatrixMultfEXT", *this};

    /// @var MatrixMultdEXT
    /// @glfuncwrap{MatrixMultdEXT}
    gl_api_function<void(enum_type, const double_type[16]), nullptr>
      MatrixMultdEXT{"MatrixMultdEXT", *this};

    /// @var LoadTransposeMatrixf
    /// @glfuncwrap{LoadTransposeMatrixf}
    gl_api_function<void(const float_type[16]), nullptr> LoadTransposeMatrixf{
      "LoadTransposeMatrixf",
      *this};

    /// @var LoadTransposeMatrixd
    /// @glfuncwrap{LoadTransposeMatrixd}
    gl_api_function<void(const double_type[16]), nullptr> LoadTransposeMatrixd{
      "LoadTransposeMatrixd",
      *this};

    /// @var MatrixLoadTransposefEXT
    /// @glfuncwrap{MatrixLoadTransposefEXT}
    gl_api_function<void(enum_type, const float_type[16]), nullptr>
      MatrixLoadTransposefEXT{"MatrixLoadTransposefEXT", *this};

    /// @var MatrixLoadTransposedEXT
    /// @glfuncwrap{MatrixLoadTransposedEXT}
    gl_api_function<void(enum_type, const double_type[16]), nullptr>
      MatrixLoadTransposedEXT{"MatrixLoadTransposedEXT", *this};

    /// @var MultTransposeMatrixf
    /// @glfuncwrap{MultTransposeMatrixf}
    gl_api_function<void(const float_type[16]), nullptr> MultTransposeMatrixf{
      "MultTransposeMatrixf",
      *this};

    /// @var MultTransposeMatrixd
    /// @glfuncwrap{MultTransposeMatrixd}
    gl_api_function<void(const double_type[16]), nullptr> MultTransposeMatrixd{
      "MultTransposeMatrixd",
      *this};

    /// @var MatrixMultTransposefEXT
    /// @glfuncwrap{MatrixMultTransposefEXT}
    gl_api_function<void(enum_type, const float_type[16]), nullptr>
      MatrixMultTransposefEXT{"MatrixMultTransposefEXT", *this};

    /// @var MatrixMultTransposedEXT
    /// @glfuncwrap{MatrixMultTransposedEXT}
    gl_api_function<void(enum_type, const double_type[16]), nullptr>
      MatrixMultTransposedEXT{"MatrixMultTransposedEXT", *this};

    /// @var MatrixLoad3x3fNV
    /// @glfuncwrap{MatrixLoad3x3fNV}
    gl_api_function<
      void(enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(MatrixLoad3x2fNV)>
      MatrixLoad3x2fNV{"MatrixLoad3x2fNV", *this};

    /// @var MatrixLoad3x3fNV
    /// @glfuncwrap{MatrixLoad3x3fNV}
    gl_api_function<
      void(enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(MatrixLoad3x3fNV)>
      MatrixLoad3x3fNV{"MatrixLoad3x3fNV", *this};

    /// @var MatrixLoadTranspose3x3fNV
    /// @glfuncwrap{MatrixLoadTranspose3x3fNV}
    gl_api_function<
      void(enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(MatrixLoadTranspose3x3fNV)>
      MatrixLoadTranspose3x3fNV{"MatrixLoadTranspose3x3fNV", *this};

    /// @var MatrixMult3x2fNV
    /// @glfuncwrap{MatrixMult3x2fNV}
    gl_api_function<
      void(enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(MatrixMult3x2fNV)>
      MatrixMult3x2fNV{"MatrixMult3x2fNV", *this};

    /// @var MatrixMult3x3fNV
    /// @glfuncwrap{MatrixMult3x3fNV}
    gl_api_function<
      void(enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(MatrixMult3x3fNV)>
      MatrixMult3x3fNV{"MatrixMult3x3fNV", *this};

    /// @var MatrixMultTranspose3x3fNV
    /// @glfuncwrap{MatrixMultTranspose3x3fNV}
    gl_api_function<
      void(enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(MatrixMultTranspose3x3fNV)>
      MatrixMultTranspose3x3fNV{"MatrixMultTranspose3x3fNV", *this};

    /// @var GenPathsNV
    /// @glfuncwrap{GenPathsNV}
    gl_api_function<uint_type(sizei_type), OGLPLUS_GL_STATIC_FUNC(GenPathsNV)>
      GenPathsNV{"GenPathsNV", *this};

    /// @var DeletePathsNV
    /// @glfuncwrap{DeletePathsNV}
    gl_api_function<
      void(uint_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(DeletePathsNV)>
      DeletePathsNV{"DeletePathsNV", *this};

    /// @var IsPathNV
    /// @glfuncwrap{IsPathNV}
    gl_api_function<bool_type(uint_type), OGLPLUS_GL_STATIC_FUNC(IsPathNV)>
      IsPathNV{"IsPathNV", *this};

    /// @var PathParameterivNV
    /// @glfuncwrap{PathParameterivNV}
    gl_api_function<
      void(uint_type, enum_type, const int_type*),
      OGLPLUS_GL_STATIC_FUNC(PathParameterivNV)>
      PathParameterivNV{"PathParameterivNV", *this};

    /// @var PathParameteriNV
    /// @glfuncwrap{PathParameteriNV}
    gl_api_function<
      void(uint_type, enum_type, int_type),
      OGLPLUS_GL_STATIC_FUNC(PathParameteriNV)>
      PathParameteriNV{"PathParameteriNV", *this};

    /// @var PathParameterfvNV
    /// @glfuncwrap{PathParameterfvNV}
    gl_api_function<
      void(uint_type, enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(PathParameterfvNV)>
      PathParameterfvNV{"PathParameterfvNV", *this};

    /// @var PathParameterfNV
    /// @glfuncwrap{PathParameterfNV}
    gl_api_function<
      void(uint_type, enum_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(PathParameterfNV)>
      PathParameterfNV{"PathParameterfNV", *this};

    /// @var PathCommandsNV
    /// @glfuncwrap{PathCommandsNV}
    gl_api_function<
      void(
        uint_type,
        sizei_type,
        const ubyte_type*,
        sizei_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(PathCommandsNV)>
      PathCommandsNV{"PathCommandsNV", *this};

    /// @var PathSubCommandsNV
    /// @glfuncwrap{PathSubCommandsNV}
    gl_api_function<
      void(
        uint_type,
        sizei_type,
        sizei_type,
        sizei_type,
        const ubyte_type*,
        sizei_type,
        enum_type,
        const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(PathSubCommandsNV)>
      PathSubCommandsNV{"PathSubCommandsNV", *this};

    /// @var PathCoordsNV
    /// @glfuncwrap{PathCoordsNV}
    gl_api_function<
      void(uint_type, sizei_type, enum_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(PathCoordsNV)>
      PathCoordsNV{"PathCoordsNV", *this};

    /// @var PathSubCoordsNV
    /// @glfuncwrap{PathSubCoordsNV}
    gl_api_function<
      void(uint_type, sizei_type, sizei_type, enum_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(PathSubCoordsNV)>
      PathSubCoordsNV{"PathSubCoordsNV", *this};

    /// @var PathStringNV
    /// @glfuncwrap{PathStringNV}
    gl_api_function<
      void(uint_type, enum_type, sizei_type, const_void_ptr_type),
      OGLPLUS_GL_STATIC_FUNC(PathStringNV)>
      PathStringNV{"PathStringNV", *this};

    /// @var PathGlyphsNV
    /// @glfuncwrap{PathGlyphsNV}
    gl_api_function<
      void(
        uint_type,
        enum_type,
        const_void_ptr_type,
        bitfield_type,
        sizei_type,
        enum_type,
        const_void_ptr_type,
        enum_type,
        uint_type,
        float_type),
      OGLPLUS_GL_STATIC_FUNC(PathGlyphsNV)>
      PathGlyphsNV{"PathGlyphsNV", *this};

    /// @var PathGlyphRangeNV
    /// @glfuncwrap{PathGlyphRangeNV}
    gl_api_function<
      void(
        uint_type,
        enum_type,
        const_void_ptr_type,
        bitfield_type,
        uint_type,
        sizei_type,
        enum_type,
        uint_type,
        float_type),
      OGLPLUS_GL_STATIC_FUNC(PathGlyphRangeNV)>
      PathGlyphRangeNV{"PathGlyphRangeNV", *this};

    /// @var PathGlyphIndexArrayNV
    /// @glfuncwrap{PathGlyphIndexArrayNV}
    gl_api_function<
      enum_type(
        uint_type,
        enum_type,
        const_void_ptr_type,
        bitfield_type,
        uint_type,
        sizei_type,
        uint_type,
        float_type),
      OGLPLUS_GL_STATIC_FUNC(PathGlyphIndexArrayNV)>
      PathGlyphIndexArrayNV{"PathGlyphIndexArrayNV", *this};

    /// @var PathMemoryGlyphIndexArrayNV
    /// @glfuncwrap{PathMemoryGlyphIndexArrayNV}
    gl_api_function<
      enum_type(
        uint_type,
        enum_type,
        sizeiptr_type,
        const_void_ptr_type,
        sizei_type,
        uint_type,
        sizei_type,
        uint_type,
        float_type),
      OGLPLUS_GL_STATIC_FUNC(PathMemoryGlyphIndexArrayNV)>
      PathMemoryGlyphIndexArrayNV{"PathMemoryGlyphIndexArrayNV", *this};

    /// @var PathGlyphIndexRangeNV
    /// @glfuncwrap{PathGlyphIndexRangeNV}
    gl_api_function<
      enum_type(
        enum_type,
        const_void_ptr_type,
        bitfield_type,
        uint_type,
        float_type,
        uint_type[2]),
      OGLPLUS_GL_STATIC_FUNC(PathGlyphIndexRangeNV)>
      PathGlyphIndexRangeNV{"PathGlyphIndexRangeNV", *this};

    /// @var CopyPathNV
    /// @glfuncwrap{CopyPathNV}
    gl_api_function<
      void(uint_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(CopyPathNV)>
      CopyPathNV{"CopyPathNV", *this};

    /// @var InterpolatePathsNV
    /// @glfuncwrap{InterpolatePathsNV}
    gl_api_function<
      void(uint_type, uint_type, uint_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(InterpolatePathsNV)>
      InterpolatePathsNV{"InterpolatePathsNV", *this};

    /// @var WeightPathsNV
    /// @glfuncwrap{WeightPathsNV}
    gl_api_function<
      void(uint_type, sizei_type, const uint_type[], const float_type[]),
      OGLPLUS_GL_STATIC_FUNC(WeightPathsNV)>
      WeightPathsNV{"WeightPathsNV", *this};

    /// @var TransformPathNV
    /// @glfuncwrap{TransformPathNV}
    gl_api_function<
      void(uint_type, uint_type, enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(TransformPathNV)>
      TransformPathNV{"TransformPathNV", *this};

    /// @var PathStencilFuncNV
    /// @glfuncwrap{PathStencilFuncNV}
    gl_api_function<
      void(enum_type, int_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(PathStencilFuncNV)>
      PathStencilFuncNV{"PathStencilFuncNV", *this};

    /// @var PathStencilDepthOffsetNV
    /// @glfuncwrap{PathStencilDepthOffsetNV}
    gl_api_function<
      void(float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(PathStencilDepthOffsetNV)>
      PathStencilDepthOffsetNV{"PathStencilDepthOffsetNV", *this};

    /// @var StencilFillPathNV
    /// @glfuncwrap{StencilFillPathNV}
    gl_api_function<
      void(uint_type, enum_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(StencilFillPathNV)>
      StencilFillPathNV{"StencilFillPathNV", *this};

    /// @var StencilStrokePathNV
    /// @glfuncwrap{StencilStrokePathNV}
    gl_api_function<
      void(uint_type, int_type, uint_type),
      OGLPLUS_GL_STATIC_FUNC(StencilStrokePathNV)>
      StencilStrokePathNV{"StencilStrokePathNV", *this};

    /// @var StencilFillPathInstancedNV
    /// @glfuncwrap{StencilFillPathInstancedNV}
    gl_api_function<
      void(
        sizei_type,
        enum_type,
        const_void_ptr_type,
        uint_type,
        enum_type,
        uint_type,
        enum_type,
        const float_type*),
      OGLPLUS_GL_STATIC_FUNC(StencilFillPathInstancedNV)>
      StencilFillPathInstancedNV{"StencilFillPathInstancedNV", *this};

    /// @var StencilStrokePathInstancedNV
    /// @glfuncwrap{StencilStrokePathInstancedNV}
    gl_api_function<
      void(
        sizei_type,
        enum_type,
        const_void_ptr_type,
        uint_type,
        int_type,
        uint_type,
        enum_type,
        const float_type*),
      OGLPLUS_GL_STATIC_FUNC(StencilStrokePathInstancedNV)>
      StencilStrokePathInstancedNV{"StencilStrokePathInstancedNV", *this};

    /// @var PathCoverDepthFuncNV
    /// @glfuncwrap{PathCoverDepthFuncNV}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(PathCoverDepthFuncNV)>
      PathCoverDepthFuncNV{"PathCoverDepthFuncNV", *this};

    /// @var PathColorGenNV
    /// @glfuncwrap{PathColorGenNV}
    gl_api_function<
      void(enum_type, enum_type, enum_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(PathColorGenNV)>
      PathColorGenNV{"PathColorGenNV", *this};

    /// @var PathTexGenNV
    /// @glfuncwrap{PathTexGenNV}
    gl_api_function<
      void(enum_type, enum_type, int_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(PathTexGenNV)>
      PathTexGenNV{"PathTexGenNV", *this};

    /// @var PathFogGenNV
    /// @glfuncwrap{PathFogGenNV}
    gl_api_function<void(enum_type), OGLPLUS_GL_STATIC_FUNC(PathFogGenNV)>
      PathFogGenNV{"PathFogGenNV", *this};

    /// @var ProgramPathFragmentInputGenNV
    /// @glfuncwrap{ProgramPathFragmentInputGenNV}
    gl_api_function<
      void(uint_type, int_type, enum_type, int_type, const float_type*),
      OGLPLUS_GL_STATIC_FUNC(ProgramPathFragmentInputGenNV)>
      ProgramPathFragmentInputGenNV{"ProgramPathFragmentInputGenNV", *this};

    /// @var CoverFillPathNV
    /// @glfuncwrap{CoverFillPathNV}
    gl_api_function<
      void(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(CoverFillPathNV)>
      CoverFillPathNV{"CoverFillPathNV", *this};

    /// @var CoverStrokePathNV
    /// @glfuncwrap{CoverStrokePathNV}
    gl_api_function<
      void(uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(CoverStrokePathNV)>
      CoverStrokePathNV{"CoverStrokePathNV", *this};

    /// @var CoverFillPathInstancedNV
    /// @glfuncwrap{CoverFillPathInstancedNV}
    gl_api_function<
      void(
        sizei_type,
        enum_type,
        const_void_ptr_type,
        uint_type,
        enum_type,
        enum_type,
        const float_type*),
      OGLPLUS_GL_STATIC_FUNC(CoverFillPathInstancedNV)>
      CoverFillPathInstancedNV{"CoverFillPathInstancedNV", *this};

    /// @var CoverStrokePathInstancedNV
    /// @glfuncwrap{CoverStrokePathInstancedNV}
    gl_api_function<
      void(
        sizei_type,
        enum_type,
        const_void_ptr_type,
        uint_type,
        enum_type,
        enum_type,
        const float_type*),
      OGLPLUS_GL_STATIC_FUNC(CoverStrokePathInstancedNV)>
      CoverStrokePathInstancedNV{"CoverStrokePathInstancedNV", *this};

    /// @var StencilThenCoverFillPathNV
    /// @glfuncwrap{StencilThenCoverFillPathNV}
    gl_api_function<
      void(uint_type, enum_type, uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(StencilThenCoverFillPathNV)>
      StencilThenCoverFillPathNV{"StencilThenCoverFillPathNV", *this};

    /// @var StencilThenCoverStrokePathNV
    /// @glfuncwrap{StencilThenCoverStrokePathNV}
    gl_api_function<
      void(uint_type, int_type, uint_type, enum_type),
      OGLPLUS_GL_STATIC_FUNC(StencilThenCoverStrokePathNV)>
      StencilThenCoverStrokePathNV{"StencilThenCoverStrokePathNV", *this};

    /// @var StencilThenCoverFillPathInstancedNV
    /// @glfuncwrap{StencilThenCoverFillPathInstancedNV}
    gl_api_function<
      void(
        sizei_type,
        enum_type,
        const_void_ptr_type,
        uint_type,
        enum_type,
        uint_type,
        enum_type,
        enum_type,
        const float_type*),
      OGLPLUS_GL_STATIC_FUNC(StencilThenCoverFillPathInstancedNV)>
      StencilThenCoverFillPathInstancedNV{
        "StencilThenCoverFillPathInstancedNV",
        *this};

    /// @var StencilThenCoverStrokePathInstancedNV
    /// @glfuncwrap{StencilThenCoverStrokePathInstancedNV}
    gl_api_function<
      void(
        sizei_type,
        enum_type,
        const_void_ptr_type,
        uint_type,
        int_type,
        uint_type,
        enum_type,
        enum_type,
        const float_type*),
      OGLPLUS_GL_STATIC_FUNC(StencilThenCoverStrokePathInstancedNV)>
      StencilThenCoverStrokePathInstancedNV{
        "StencilThenCoverStrokePathInstancedNV",
        *this};

    /// @var GetPathParameterivNV
    /// @glfuncwrap{GetPathParameterivNV}
    gl_api_function<
      void(uint_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathParameterivNV)>
      GetPathParameterivNV{"GetPathParameterivNV", *this};

    /// @var GetPathParameterfvNV
    /// @glfuncwrap{GetPathParameterfvNV}
    gl_api_function<
      void(uint_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathParameterfvNV)>
      GetPathParameterfvNV{"GetPathParameterfvNV", *this};

    /// @var GetPathCommandsNV
    /// @glfuncwrap{GetPathCommandsNV}
    gl_api_function<
      void(uint_type, ubyte_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathCommandsNV)>
      GetPathCommandsNV{"GetPathCommandsNV", *this};

    /// @var GetPathCoordsNV
    /// @glfuncwrap{GetPathCoordsNV}
    gl_api_function<
      void(uint_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathCoordsNV)>
      GetPathCoordsNV{"GetPathCoordsNV", *this};

    /// @var GetPathDashArrayNV
    /// @glfuncwrap{GetPathDashArrayNV}
    gl_api_function<
      void(uint_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathDashArrayNV)>
      GetPathDashArrayNV{"GetPathDashArrayNV", *this};

    /// @var GetPathMetricsNV
    /// @glfuncwrap{GetPathMetricsNV}
    gl_api_function<
      void(
        bitfield_type,
        sizei_type,
        enum_type,
        const_void_ptr_type,
        uint_type,
        sizei_type,
        float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathMetricsNV)>
      GetPathMetricsNV{"GetPathMetricsNV", *this};

    /// @var GetPathMetricRangeNV
    /// @glfuncwrap{GetPathMetricRangeNV}
    gl_api_function<
      void(bitfield_type, uint_type, sizei_type, sizei_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathMetricRangeNV)>
      GetPathMetricRangeNV{"GetPathMetricRangeNV", *this};

    /// @var GetPathSpacingNV
    /// @glfuncwrap{GetPathSpacingNV}
    gl_api_function<
      void(
        enum_type,
        sizei_type,
        enum_type,
        const_void_ptr_type,
        uint_type,
        float_type,
        float_type,
        enum_type,
        float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathSpacingNV)>
      GetPathSpacingNV{"GetPathSpacingNV", *this};

    /// @var GetPathColorGenivNV
    /// @glfuncwrap{GetPathColorGenivNV}
    gl_api_function<
      void(enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathColorGenivNV)>
      GetPathColorGenivNV{"GetPathColorGenivNV", *this};

    /// @var GetPathColorGenfvNV
    /// @glfuncwrap{GetPathColorGenfvNV}
    gl_api_function<
      void(enum_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathColorGenfvNV)>
      GetPathColorGenfvNV{"GetPathColorGenfvNV", *this};

    /// @var GetPathTexGenivNV
    /// @glfuncwrap{GetPathTexGenivNV}
    gl_api_function<
      void(enum_type, enum_type, int_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathTexGenivNV)>
      GetPathTexGenivNV{"GetPathTexGenivNV", *this};

    /// @var GetPathTexGenfvNV
    /// @glfuncwrap{GetPathTexGenfvNV}
    gl_api_function<
      void(enum_type, enum_type, float_type*),
      OGLPLUS_GL_STATIC_FUNC(GetPathTexGenfvNV)>
      GetPathTexGenfvNV{"GetPathTexGenfvNV", *this};

    /// @var GetPathLengthNV
    /// @glfuncwrap{GetPathLengthNV}
    gl_api_function<
      float_type(uint_type, sizei_type, sizei_type),
      OGLPLUS_GL_STATIC_FUNC(GetPathLengthNV)>
      GetPathLengthNV{"GetPathLengthNV", *this};

    /// @var IsPointInFillPathNV
    /// @glfuncwrap{IsPointInFillPathNV}
    gl_api_function<
      bool_type(uint_type, uint_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(IsPointInFillPathNV)>
      IsPointInFillPathNV{"IsPointInFillPathNV", *this};

    /// @var IsPointInStrokePathNV
    /// @glfuncwrap{IsPointInStrokePathNV}
    gl_api_function<
      bool_type(uint_type, float_type, float_type),
      OGLPLUS_GL_STATIC_FUNC(IsPointInStrokePathNV)>
      IsPointInStrokePathNV{"IsPointInStrokePathNV", *this};

    /// @var PointAlongPathNV
    /// @glfuncwrap{PointAlongPathNV}
    gl_api_function<
      bool_type(
        uint_type,
        sizei_type,
        sizei_type,
        float_type,
        float_type*,
        float_type*,
        float_type*,
        float_type*),
      OGLPLUS_GL_STATIC_FUNC(PointAlongPathNV)>
      PointAlongPathNV{"PointAlongPathNV", *this};

    /// @var MaxShaderCompilerThreadsARB
    /// @glfuncwrap{MaxShaderCompilerThreadsARB}
    gl_api_function<
      void(uint_type),
      OGLPLUS_GL_STATIC_FUNC(MaxShaderCompilerThreadsARB)>
      MaxShaderCompilerThreadsARB{"MaxShaderCompilerThreadsARB", *this};

    /// @var Hint
    /// @glfuncwrap{Hint}
    gl_api_function<void(enum_type, enum_type), OGLPLUS_GL_STATIC_FUNC(Hint)>
      Hint{"Hint", *this};

    /// @var Flush
    /// @glfuncwrap{Flush}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(Flush)> Flush{"Flush", *this};

    /// @var Finish
    /// @glfuncwrap{Finish}
    gl_api_function<void(), OGLPLUS_GL_STATIC_FUNC(Finish)> Finish{
      "Finish",
      *this};

    basic_gl_c_api(api_traits& traits)
      : _traits{traits} {}

    auto traits() noexcept -> api_traits& {
        return _traits;
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
