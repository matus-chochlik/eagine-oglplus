/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

namespace eagine::oglplus {
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_gl_c_api<ApiTraits>::basic_gl_c_api(api_traits& traits)
  : GetError{"GetError", traits, *this}
  , GetGraphicsResetStatus{"GetGraphicsResetStatus", traits, *this}
  , Enable{"Enable", traits, *this}
  , Enablei{"Enablei", traits, *this}
  , Disable{"Disable", traits, *this}
  , Disablei{"Disablei", traits, *this}
  , IsEnabled{"IsEnabled", traits, *this}
  , IsEnabledi{"IsEnabledi", traits, *this}
  , MemoryBarrier{"MemoryBarrier", traits, *this}
  , MemoryBarrierByRegion{"MemoryBarrierByRegion", traits, *this}
  , FenceSync{"FenceSync", traits, *this}
  , DeleteSync{"DeleteSync", traits, *this}
  , IsSync{"IsSync", traits, *this}
  , GetSynciv{"GetSynciv", traits, *this}
  , WaitSync{"WaitSync", traits, *this}
  , ClientWaitSync{"ClientWaitSync", traits, *this}
  , GenVertexArrays{"GenVertexArrays", traits, *this}
  , CreateVertexArrays{"CreateVertexArrays", traits, *this}
  , DeleteVertexArrays{"DeleteVertexArrays", traits, *this}
  , IsVertexArray{"IsVertexArray", traits, *this}
  , BindVertexArray{"BindVertexArray", traits, *this}
  , VertexArrayElementBuffer{"VertexArrayElementBuffer", traits, *this}
  , BindVertexBuffer{"BindVertexBuffer", traits, *this}
  , VertexArrayVertexBuffer{"VertexArrayVertexBuffer", traits, *this}
  , BindVertexBuffers{"BindVertexBuffers", traits, *this}
  , VertexArrayVertexBuffers{"VertexArrayVertexBuffers", traits, *this}
  , VertexAttribBinding{"VertexAttribBinding", traits, *this}
  , VertexArrayAttribBinding{"VertexArrayAttribBinding", traits, *this}
  , EnableVertexAttribArray{"EnableVertexAttribArray", traits, *this}
  , EnableVertexArrayAttrib{"EnableVertexArrayAttrib", traits, *this}
  , DisableVertexAttribArray{"DisableVertexAttribArray", traits, *this}
  , DisableVertexArrayAttrib{"DisableVertexArrayAttrib", traits, *this}
  , VertexBindingDivisor{"VertexBindingDivisor", traits, *this}
  , VertexArrayBindingDivisor{"VertexArrayBindingDivisor", traits, *this}
  , VertexAttribDivisor{"VertexAttribDivisor", traits, *this}
  , GenBuffers{"GenBuffers", traits, *this}
  , CreateBuffers{"CreateBuffers", traits, *this}
  , DeleteBuffers{"DeleteBuffers", traits, *this}
  , IsBuffer{"IsBuffer", traits, *this}
  , BindBuffer{"BindBuffer", traits, *this}
  , BindBufferBase{"BindBufferBase", traits, *this}
  , BindBufferRange{"BindBufferRange", traits, *this}
  , BufferStorage{"BufferStorage", traits, *this}
  , NamedBufferStorage{"NamedBufferStorage", traits, *this}
  , BufferData{"BufferData", traits, *this}
  , NamedBufferData{"NamedBufferData", traits, *this}
  , BufferSubData{"BufferSubData", traits, *this}
  , NamedBufferSubData{"NamedBufferSubData", traits, *this}
  , ClearBufferData{"ClearBufferData", traits, *this}
  , ClearNamedBufferData{"ClearNamedBufferData", traits, *this}
  , ClearBufferSubData{"ClearBufferSubData", traits, *this}
  , ClearNamedBufferSubData{"ClearNamedBufferSubData", traits, *this}
  , MapBuffer{"MapBuffer", traits, *this}
  , MapNamedBuffer{"MapNamedBuffer", traits, *this}
  , MapBufferRange{"MapBufferRange", traits, *this}
  , MapNamedBufferRange{"MapNamedBufferRange", traits, *this}
  , FlushMappedBufferRange{"FlushMappedBufferRange", traits, *this}
  , FlushMappedNamedBufferRange{"FlushMappedNamedBufferRange", traits, *this}
  , UnmapBuffer{"UnmapBuffer", traits, *this}
  , UnmapNamedBuffer{"UnmapNamedBuffer", traits, *this}
  , InvalidateBufferData{"InvalidateBufferData", traits, *this}
  , InvalidateBufferSubData{"InvalidateBufferSubData", traits, *this}
  , CopyBufferSubData{"CopyBufferSubData", traits, *this}
  , CopyNamedBufferSubData{"CopyNamedBufferSubData", traits, *this}
  , GetBufferParameteriv{"GetBufferParameteriv", traits, *this}
  , GetBufferParameteri64v{"GetBufferParameteri64v", traits, *this}
  , GetNamedBufferParameteriv{"GetNamedBufferParameteriv", traits, *this}
  , GetNamedBufferParameteri64v{"GetNamedBufferParameteri64v", traits, *this}
  , GetBufferSubData{"GetBufferSubData", traits, *this}
  , GetNamedBufferSubData{"GetNamedBufferSubData", traits, *this}
  , GenTextures{"GenTextures", traits, *this}
  , CreateTextures{"CreateTextures", traits, *this}
  , DeleteTextures{"DeleteTextures", traits, *this}
  , IsTexture{"IsTexture", traits, *this}
  , ActiveTexture{"ActiveTexture", traits, *this}
  , BindTexture{"BindTexture", traits, *this}
  , BindTextures{"BindTextures", traits, *this}
  , BindTextureUnit{"BindTextureUnit", traits, *this}
  , BindImageTexture{"BindImageTexture", traits, *this}
  , BindImageTextures{"BindImageTextures", traits, *this}
  , TexStorage3D{"TexStorage3D", traits, *this}
  , TexStorage2D{"TexStorage2D", traits, *this}
  , TexStorage1D{"TexStorage1D", traits, *this}
  , TexStorage3DMultisample{"TexStorage3DMultisample", traits, *this}
  , TexStorage2DMultisample{"TexStorage2DMultisample", traits, *this}
  , TexImage3D{"TexImage3D", traits, *this}
  , TexImage2D{"TexImage2D", traits, *this}
  , TexImage1D{"TexImage1D", traits, *this}
  , CopyTexImage2D{"CopyTexImage2D", traits, *this}
  , CopyTexImage1D{"CopyTexImage1D", traits, *this}
  , TexSubImage3D{"TexSubImage3D", traits, *this}
  , TexSubImage2D{"TexSubImage2D", traits, *this}
  , TexSubImage1D{"TexSubImage1D", traits, *this}
  , CopyTexSubImage3D{"CopyTexSubImage3D", traits, *this}
  , CopyTexSubImage2D{"CopyTexSubImage2D", traits, *this}
  , CopyTexSubImage1D{"CopyTexSubImage1D", traits, *this}
  , TextureStorage3D{"TextureStorage3D", traits, *this}
  , TextureStorage2D{"TextureStorage2D", traits, *this}
  , TextureStorage1D{"TextureStorage1D", traits, *this}
  , TextureStorage3DMultisample{"TextureStorage3DMultisample", traits, *this}
  , TextureStorage2DMultisample{"TextureStorage2DMultisample", traits, *this}
  , TextureSubImage3D{"TextureSubImage3D", traits, *this}
  , TextureSubImage2D{"TextureSubImage2D", traits, *this}
  , TextureSubImage1D{"TextureSubImage1D", traits, *this}
  , CopyTextureSubImage3D{"CopyTextureSubImage3D", traits, *this}
  , CopyTextureSubImage2D{"CopyTextureSubImage2D", traits, *this}
  , CopyTextureSubImage1D{"CopyTextureSubImage1D", traits, *this}
  , CompressedTexImage3D{"CompressedTexImage3D", traits, *this}
  , CompressedTexImage2D{"CompressedTexImage2D", traits, *this}
  , CompressedTexImage1D{"CompressedTexImage1D", traits, *this}
  , CompressedTexSubImage3D{"CompressedTexSubImage3D", traits, *this}
  , CompressedTexSubImage2D{"CompressedTexSubImage2D", traits, *this}
  , CompressedTexSubImage1D{"CompressedTexSubImage1D", traits, *this}
  , CompressedTextureSubImage3D{"CompressedTextureSubImage3D", traits, *this}
  , CompressedTextureSubImage2D{"CompressedTextureSubImage2D", traits, *this}
  , CompressedTextureSubImage1D{"CompressedTextureSubImage1D", traits, *this}
  , TexImage3DMultisample{"TexImage3DMultisample", traits, *this}
  , TexImage2DMultisample{"TexImage2DMultisample", traits, *this}
  , TexBuffer{"TexBuffer", traits, *this}
  , TexBufferRange{"TexBufferRange", traits, *this}
  , TextureBuffer{"TextureBuffer", traits, *this}
  , TextureBufferRange{"TextureBufferRange", traits, *this}
  , TexParameterf{"TexParameterf", traits, *this}
  , TexParameteri{"TexParameteri", traits, *this}
  , TexParameterfv{"TexParameterfv", traits, *this}
  , TexParameteriv{"TexParameteriv", traits, *this}
  , TexParameterIiv{"TexParameterIiv", traits, *this}
  , TexParameterIuiv{"TexParameterIuiv", traits, *this}
  , TextureParameterf{"TextureParameterf", traits, *this}
  , TextureParameteri{"TextureParameteri", traits, *this}
  , TextureParameterfv{"TextureParameterfv", traits, *this}
  , TextureParameteriv{"TextureParameteriv", traits, *this}
  , TextureParameterIiv{"TextureParameterIiv", traits, *this}
  , TextureParameterIuiv{"TextureParameterIuiv", traits, *this}
  , GetTexParameterfv{"GetTexParameterfv", traits, *this}
  , GetTexParameteriv{"GetTexParameteriv", traits, *this}
  , GetTexParameterIiv{"GetTexParameterIiv", traits, *this}
  , GetTexParameterIuiv{"GetTexParameterIuiv", traits, *this}
  , GetTexLevelParameterfv{"GetTexLevelParameterfv", traits, *this}
  , GetTexLevelParameteriv{"GetTexLevelParameteriv", traits, *this}
  , GetTexImage{"GetTexImage", traits, *this}
  , GetnTexImage{"GetnTexImage", traits, *this}
  , GetCompressedTexImage{"GetCompressedTexImage", traits, *this}
  , GetnCompressedTexImage{"GetnCompressedTexImage", traits, *this}
  , GetTextureParameterfv{"GetTextureParameterfv", traits, *this}
  , GetTextureParameteriv{"GetTextureParameteriv", traits, *this}
  , GetTextureParameterIiv{"GetTextureParameterIiv", traits, *this}
  , GetTextureParameterIuiv{"GetTextureParameterIuiv", traits, *this}
  , GetTextureLevelParameterfv{"GetTextureLevelParameterfv", traits, *this}
  , GetTextureLevelParameteriv{"GetTextureLevelParameteriv", traits, *this}
  , GetTextureImage{"GetTextureImage", traits, *this}
  , GetTextureSubImage{"GetTextureSubImage", traits, *this}
  , GetCompressedTextureImage{"GetCompressedTextureImage", traits, *this}
  , GetCompressedTextureSubImage{"GetCompressedTextureSubImage", traits, *this}
  , GenerateMipmap{"GenerateMipmap", traits, *this}
  , GenerateTextureMipmap{"GenerateTextureMipmap", traits, *this}
  , TextureView{"TextureView", traits, *this}
  , InvalidateTexSubImage{"InvalidateTexSubImage", traits, *this}
  , InvalidateTexImage{"InvalidateTexImage", traits, *this}
  , ClearTexSubImage{"ClearTexSubImage", traits, *this}
  , ClearTexImage{"ClearTexImage", traits, *this}
  , TextureBarrier{"TextureBarrier", traits, *this}
  , GenSamplers{"GenSamplers", traits, *this}
  , CreateSamplers{"CreateSamplers", traits, *this}
  , DeleteSamplers{"DeleteSamplers", traits, *this}
  , IsSampler{"IsSampler", traits, *this}
  , BindSampler{"BindSampler", traits, *this}
  , BindSamplers{"BindSamplers", traits, *this}
  , SamplerParameterf{"SamplerParameterf", traits, *this}
  , SamplerParameteri{"SamplerParameteri", traits, *this}
  , SamplerParameterfv{"SamplerParameterfv", traits, *this}
  , SamplerParameteriv{"SamplerParameteriv", traits, *this}
  , SamplerParameterIiv{"SamplerParameterIiv", traits, *this}
  , SamplerParameterIuiv{"SamplerParameterIuiv", traits, *this}
  , GetSamplerParameterfv{"GetSamplerParameterfv", traits, *this}
  , GetSamplerParameteriv{"GetSamplerParameteriv", traits, *this}
  , GetSamplerParameterIiv{"GetSamplerParameterIiv", traits, *this}
  , GetSamplerParameterIuiv{"GetSamplerParameterIuiv", traits, *this}
  , GenRenderbuffers{"GenRenderbuffers", traits, *this}
  , CreateRenderbuffers{"CreateRenderbuffers", traits, *this}
  , DeleteRenderbuffers{"DeleteRenderbuffers", traits, *this}
  , IsRenderbuffer{"IsRenderbuffer", traits, *this}
  , BindRenderbuffer{"BindRenderbuffer", traits, *this}
  , RenderbufferStorage{"RenderbufferStorage", traits, *this}
  , NamedRenderbufferStorage{"NamedRenderbufferStorage", traits, *this}
  , RenderbufferStorageMultisample{
      "RenderbufferStorageMultisample",
      traits,
      *this}
  , NamedRenderbufferStorageMultisample{
      "NamedRenderbufferStorageMultisample",
      traits,
      *this}
  , GetRenderbufferParameteriv{"GetRenderbufferParameteriv", traits, *this}
  , GetNamedRenderbufferParameteriv{
      "GetNamedRenderbufferParameteriv",
      traits,
      *this}
  , GenFramebuffers{"GenFramebuffers", traits, *this}
  , CreateFramebuffers{"CreateFramebuffers", traits, *this}
  , DeleteFramebuffers{"DeleteFramebuffers", traits, *this}
  , IsFramebuffer{"IsFramebuffer", traits, *this}
  , BindFramebuffer{"BindFramebuffer", traits, *this}
  , DrawBuffer{"DrawBuffer", traits, *this}
  , NamedFramebufferDrawBuffer{"NamedFramebufferDrawBuffer", traits, *this}
  , DrawBuffers{"DrawBuffers", traits, *this}
  , NamedFramebufferDrawBuffers{"NamedFramebufferDrawBuffers", traits, *this}
  , ClearBufferfv{"ClearBufferfv", traits, *this}
  , ClearBufferiv{"ClearBufferiv", traits, *this}
  , ClearBufferuiv{"ClearBufferuiv", traits, *this}
  , ClearBufferfi{"ClearBufferfi", traits, *this}
  , ClearNamedFramebufferfv{"ClearNamedFramebufferfv", traits, *this}
  , ClearNamedFramebufferiv{"ClearNamedFramebufferiv", traits, *this}
  , ClearNamedFramebufferuiv{"ClearNamedFramebufferuiv", traits, *this}
  , ClearNamedFramebufferfi{"ClearNamedFramebufferfi", traits, *this}
  , InvalidateFramebuffer{"InvalidateFramebuffer", traits, *this}
  , InvalidateSubFramebuffer{"InvalidateSubFramebuffer", traits, *this}
  , InvalidateNamedFramebufferData{
      "InvalidateNamedFramebufferData",
      traits,
      *this}
  , InvalidateNamedFramebufferSubData{
      "InvalidateNamedFramebufferSubData",
      traits,
      *this}
  , FramebufferParameteri{"FramebufferParameteri", traits, *this}
  , NamedFramebufferParameteri{"NamedFramebufferParameteri", traits, *this}
  , GetFramebufferParameteriv{"GetFramebufferParameteriv", traits, *this}
  , GetNamedFramebufferParameteriv{
      "GetNamedFramebufferParameteriv",
      traits,
      *this}
  , GetFramebufferAttachmentParameteriv{
      "GetFramebufferAttachmentParameteriv",
      traits,
      *this}
  , GetNamedFramebufferAttachmentParameteriv{
      "GetNamedFramebufferAttachmentParameteriv",
      traits,
      *this}
  , FramebufferRenderbuffer{"FramebufferRenderbuffer", traits, *this}
  , NamedFramebufferRenderbuffer{"NamedFramebufferRenderbuffer", traits, *this}
  , FramebufferTexture{"FramebufferTexture", traits, *this}
  , NamedFramebufferTexture{"NamedFramebufferTexture", traits, *this}
  , FramebufferTexture1D{"FramebufferTexture1D", traits, *this}
  , FramebufferTexture2D{"FramebufferTexture2D", traits, *this}
  , FramebufferTexture3D{"FramebufferTexture3D", traits, *this}
  , FramebufferTextureLayer{"FramebufferTextureLayer", traits, *this}
  , NamedFramebufferTextureLayer{"NamedFramebufferTextureLayer", traits, *this}
  , CheckFramebufferStatus{"CheckFramebufferStatus", traits, *this}
  , CheckNamedFramebufferStatus{"CheckNamedFramebufferStatus", traits, *this}
  , ReadBuffer{"ReadBuffer", traits, *this}
  , NamedFramebufferReadBuffer{"NamedFramebufferReadBuffer", traits, *this}
  , BlitFramebuffer{"BlitFramebuffer", traits, *this}
  , BlitNamedFramebuffer{"BlitNamedFramebuffer", traits, *this}
  , CopyImageSubData{"CopyImageSubData", traits, *this}
  , GenTransformFeedbacks{"GenTransformFeedbacks", traits, *this}
  , CreateTransformFeedbacks{"CreateTransformFeedbacks", traits, *this}
  , DeleteTransformFeedbacks{"DeleteTransformFeedbacks", traits, *this}
  , IsTransformFeedback{"IsTransformFeedback", traits, *this}
  , BindTransformFeedback{"BindTransformFeedback", traits, *this}
  , BeginTransformFeedback{"BeginTransformFeedback", traits, *this}
  , PauseTransformFeedback{"PauseTransformFeedback", traits, *this}
  , ResumeTransformFeedback{"ResumeTransformFeedback", traits, *this}
  , EndTransformFeedback{"EndTransformFeedback", traits, *this}
  , TransformFeedbackBufferBase{"TransformFeedbackBufferBase", traits, *this}
  , TransformFeedbackBufferRange{"TransformFeedbackBufferRange", traits, *this}
  , GetTransformFeedbackiv{"GetTransformFeedbackiv", traits, *this}
  , GetTransformFeedbacki_v{"GetTransformFeedbacki_v", traits, *this}
  , GetTransformFeedbacki64_v{"GetTransformFeedbacki64_v", traits, *this}
  , GenQueries{"GenQueries", traits, *this}
  , CreateQueries{"CreateQueries", traits, *this}
  , DeleteQueries{"DeleteQueries", traits, *this}
  , IsQuery{"IsQuery", traits, *this}
  , GetQueryiv{"GetQueryiv", traits, *this}
  , GetQueryIndexediv{"GetQueryIndexediv", traits, *this}
  , GetQueryObjectiv{"GetQueryObjectiv", traits, *this}
  , GetQueryObjectuiv{"GetQueryObjectuiv", traits, *this}
  , GetQueryObjecti64v{"GetQueryObjecti64v", traits, *this}
  , GetQueryObjectui64v{"GetQueryObjectui64v", traits, *this}
  , GetQueryBufferObjectiv{"GetQueryBufferObjectiv", traits, *this}
  , GetQueryBufferObjectuiv{"GetQueryBufferObjectuiv", traits, *this}
  , GetQueryBufferObjecti64v{"GetQueryBufferObjecti64v", traits, *this}
  , GetQueryBufferObjectui64v{"GetQueryBufferObjectui64v", traits, *this}
  , BeginQuery{"BeginQuery", traits, *this}
  , BeginQueryIndexed{"BeginQueryIndexed", traits, *this}
  , EndQuery{"EndQuery", traits, *this}
  , EndQueryIndexed{"EndQueryIndexed", traits, *this}
  , QueryCounter{"QueryCounter", traits, *this}
  , BeginConditionalRender{"BeginConditionalRender", traits, *this}
  , EndConditionalRender{"EndConditionalRender", traits, *this}
  , GenProgramPipelines{"GenProgramPipelines", traits, *this}
  , CreateProgramPipelines{"CreateProgramPipelines", traits, *this}
  , DeleteProgramPipelines{"DeleteProgramPipelines", traits, *this}
  , IsProgramPipeline{"IsProgramPipeline", traits, *this}
  , BindProgramPipeline{"BindProgramPipeline", traits, *this}
  , ValidateProgramPipeline{"ValidateProgramPipeline", traits, *this}
  , UseProgramStages{"UseProgramStages", traits, *this}
  , GetProgramStageiv{"GetProgramStageiv", traits, *this}
  , GetProgramPipelineiv{"GetProgramPipelineiv", traits, *this}
  , GetProgramPipelineInfoLog{"GetProgramPipelineInfoLog", traits, *this}
  , ActiveShaderProgram{"ActiveShaderProgram", traits, *this}
  , CreateShader{"CreateShader", traits, *this}
  , DeleteShader{"DeleteShader", traits, *this}
  , IsShader{"IsShader", traits, *this}
  , ShaderSource{"ShaderSource", traits, *this}
  , CompileShader{"CompileShader", traits, *this}
  , CompileShaderInclude{"CompileShaderIncludeARB", traits, *this}
  , ShaderBinary{"ShaderBinary", traits, *this}
  , SpecializeShader{"SpecializeShader", traits, *this}
  , GetShaderiv{"GetShaderiv", traits, *this}
  , GetShaderInfoLog{"GetShaderInfoLog", traits, *this}
  , GetShaderSource{"GetShaderSource", traits, *this}
  , GetShaderPrecisionFormat{"GetShaderPrecisionFormat", traits, *this}
  , ReleaseShaderCompiler{"ReleaseShaderCompiler", traits, *this}
  , CreateProgram{"CreateProgram", traits, *this}
  , CreateShaderProgramv{"CreateShaderProgramv", traits, *this}
  , DeleteProgram{"DeleteProgram", traits, *this}
  , IsProgram{"IsProgram", traits, *this}
  , AttachShader{"AttachShader", traits, *this}
  , DetachShader{"DetachShader", traits, *this}
  , GetAttachedShaders{"GetAttachedShaders", traits, *this}
  , ValidateProgram{"ValidateProgram", traits, *this}
  , LinkProgram{"LinkProgram", traits, *this}
  , UseProgram{"UseProgram", traits, *this}
  , ProgramBinary{"ProgramBinary", traits, *this}
  , GetProgramBinary{"GetProgramBinary", traits, *this}
  , GetProgramiv{"GetProgramiv", traits, *this}
  , GetProgramInfoLog{"GetProgramInfoLog", traits, *this}
  , GetProgramInterfaceiv{"GetProgramInterfaceiv", traits, *this}
  , GetProgramResourceIndex{"GetProgramResourceIndex", traits, *this}
  , GetProgramResourceName{"GetProgramResourceName", traits, *this}
  , GetProgramResourceLocation{"GetProgramResourceLocation", traits, *this}
  , GetProgramResourceLocationIndex{
      "GetProgramResourceLocationIndex",
      traits,
      *this}
  , GetProgramResourceiv{"GetProgramResourceiv", traits, *this}
  , GetProgramResourcefvNV{"GetProgramResourcefvNV", traits, *this}
  , BindAttribLocation{"BindAttribLocation", traits, *this}
  , GetAttribLocation{"GetAttribLocation", traits, *this}
  , GetActiveAttrib{"GetActiveAttrib", traits, *this}
  , GetUniformLocation{"GetUniformLocation", traits, *this}
  , GetUniformBlockIndex{"GetUniformBlockIndex", traits, *this}
  , GetActiveUniformName{"GetActiveUniformName", traits, *this}
  , GetSubroutineIndex{"GetSubroutineIndex", traits, *this}
  , GetActiveSubroutineName{"GetActiveSubroutineName", traits, *this}
  , GetActiveSubroutineUniformName{
      "GetActiveSubroutineUniformName",
      traits,
      *this}
  , GetSubroutineUniformLocation{"GetSubroutineUniformLocation", traits, *this}
  , GetActiveSubroutineUniformiv{"GetActiveSubroutineUniformiv", traits, *this}
  , TransformFeedbackVaryings{"TransformFeedbackVaryings", traits, *this}
  , GetTransformFeedbackVarying{"GetTransformFeedbackVarying", traits, *this}
  , BindFragDataLocation{"BindFragDataLocation", traits, *this}
  , BindFragDataLocationIndexed{"BindFragDataLocationIndexed", traits, *this}
  , GetFragDataLocation{"GetFragDataLocation", traits, *this}
  , GetFragDataIndex{"GetFragDataIndex", traits, *this}
  , UniformSubroutinesuiv{"UniformSubroutinesuiv", traits, *this}
  , GetUniformSubroutineuiv{"GetUniformSubroutineuiv", traits, *this}
  , Uniform1i{"Uniform1i", traits, *this}
  , Uniform2i{"Uniform2i", traits, *this}
  , Uniform3i{"Uniform3i", traits, *this}
  , Uniform4i{"Uniform4i", traits, *this}
  , Uniform1iv{"Uniform1iv", traits, *this}
  , Uniform2iv{"Uniform2iv", traits, *this}
  , Uniform3iv{"Uniform3iv", traits, *this}
  , Uniform4iv{"Uniform4iv", traits, *this}
  , Uniform1ui{"Uniform1ui", traits, *this}
  , Uniform2ui{"Uniform2ui", traits, *this}
  , Uniform3ui{"Uniform3ui", traits, *this}
  , Uniform4ui{"Uniform4ui", traits, *this}
  , Uniform1uiv{"Uniform1uiv", traits, *this}
  , Uniform2uiv{"Uniform2uiv", traits, *this}
  , Uniform3uiv{"Uniform3uiv", traits, *this}
  , Uniform4uiv{"Uniform4uiv", traits, *this}
  , Uniform1f{"Uniform1f", traits, *this}
  , Uniform2f{"Uniform2f", traits, *this}
  , Uniform3f{"Uniform3f", traits, *this}
  , Uniform4f{"Uniform4f", traits, *this}
  , Uniform1fv{"Uniform1fv", traits, *this}
  , Uniform2fv{"Uniform2fv", traits, *this}
  , Uniform3fv{"Uniform3fv", traits, *this}
  , Uniform4fv{"Uniform4fv", traits, *this}
  , UniformMatrix2fv{"UniformMatrix2fv", traits, *this}
  , UniformMatrix3fv{"UniformMatrix3fv", traits, *this}
  , UniformMatrix4fv{"UniformMatrix4fv", traits, *this}
  , UniformMatrix2x3fv{"UniformMatrix2x3fv", traits, *this}
  , UniformMatrix3x2fv{"UniformMatrix3x2fv", traits, *this}
  , UniformMatrix2x4fv{"UniformMatrix2x4fv", traits, *this}
  , UniformMatrix4x2fv{"UniformMatrix4x2fv", traits, *this}
  , UniformMatrix3x4fv{"UniformMatrix3x4fv", traits, *this}
  , UniformMatrix4x3fv{"UniformMatrix4x3fv", traits, *this}
  , GetUniformfv{"GetUniformfv", traits, *this}
  , GetUniformdv{"GetUniformdv", traits, *this}
  , GetUniformiv{"GetUniformiv", traits, *this}
  , GetUniformuiv{"GetUniformuiv", traits, *this}
  , GetnUniformfv{"GetnUniformfv", traits, *this}
  , GetnUniformdv{"GetnUniformdv", traits, *this}
  , GetnUniformiv{"GetnUniformiv", traits, *this}
  , GetnUniformuiv{"GetnUniformuiv", traits, *this}
  , ProgramUniform1i{"ProgramUniform1i", traits, *this}
  , ProgramUniform2i{"ProgramUniform2i", traits, *this}
  , ProgramUniform3i{"ProgramUniform3i", traits, *this}
  , ProgramUniform4i{"ProgramUniform4i", traits, *this}
  , ProgramUniform1iv{"ProgramUniform1iv", traits, *this}
  , ProgramUniform2iv{"ProgramUniform2iv", traits, *this}
  , ProgramUniform3iv{"ProgramUniform3iv", traits, *this}
  , ProgramUniform4iv{"ProgramUniform4iv", traits, *this}
  , ProgramUniform1ui{"ProgramUniform1ui", traits, *this}
  , ProgramUniform2ui{"ProgramUniform2ui", traits, *this}
  , ProgramUniform3ui{"ProgramUniform3ui", traits, *this}
  , ProgramUniform4ui{"ProgramUniform4ui", traits, *this}
  , ProgramUniform1uiv{"ProgramUniform1uiv", traits, *this}
  , ProgramUniform2uiv{"ProgramUniform2uiv", traits, *this}
  , ProgramUniform3uiv{"ProgramUniform3uiv", traits, *this}
  , ProgramUniform4uiv{"ProgramUniform4uiv", traits, *this}
  , ProgramUniform1f{"ProgramUniform1f", traits, *this}
  , ProgramUniform2f{"ProgramUniform2f", traits, *this}
  , ProgramUniform3f{"ProgramUniform3f", traits, *this}
  , ProgramUniform4f{"ProgramUniform4f", traits, *this}
  , ProgramUniform1fv{"ProgramUniform1fv", traits, *this}
  , ProgramUniform2fv{"ProgramUniform2fv", traits, *this}
  , ProgramUniform3fv{"ProgramUniform3fv", traits, *this}
  , ProgramUniform4fv{"ProgramUniform4fv", traits, *this}
  , ProgramUniformMatrix2fv{"ProgramUniformMatrix2fv", traits, *this}
  , ProgramUniformMatrix3fv{"ProgramUniformMatrix3fv", traits, *this}
  , ProgramUniformMatrix4fv{"ProgramUniformMatrix4fv", traits, *this}
  , ProgramUniformMatrix2x3fv{"ProgramUniformMatrix2x3fv", traits, *this}
  , ProgramUniformMatrix3x2fv{"ProgramUniformMatrix3x2fv", traits, *this}
  , ProgramUniformMatrix2x4fv{"ProgramUniformMatrix2x4fv", traits, *this}
  , ProgramUniformMatrix4x2fv{"ProgramUniformMatrix4x2fv", traits, *this}
  , ProgramUniformMatrix3x4fv{"ProgramUniformMatrix3x4fv", traits, *this}
  , ProgramUniformMatrix4x3fv{"ProgramUniformMatrix4x3fv", traits, *this}
  , UniformBlockBinding{"UniformBlockBinding", traits, *this}
  , ShaderStorageBlockBinding{"ShaderStorageBlockBinding", traits, *this}
  , VertexAttrib1f{"VertexAttrib1f", traits, *this}
  , VertexAttrib2f{"VertexAttrib2f", traits, *this}
  , VertexAttrib3f{"VertexAttrib3f", traits, *this}
  , VertexAttrib4f{"VertexAttrib4f", traits, *this}
  , VertexAttrib1fv{"VertexAttrib1fv", traits, *this}
  , VertexAttrib2fv{"VertexAttrib2fv", traits, *this}
  , VertexAttrib3fv{"VertexAttrib3fv", traits, *this}
  , VertexAttrib4fv{"VertexAttrib4fv", traits, *this}
  , VertexAttrib1d{"VertexAttrib1d", traits, *this}
  , VertexAttrib2d{"VertexAttrib2d", traits, *this}
  , VertexAttrib3d{"VertexAttrib3d", traits, *this}
  , VertexAttrib4d{"VertexAttrib4d", traits, *this}
  , VertexAttrib1dv{"VertexAttrib1dv", traits, *this}
  , VertexAttrib2dv{"VertexAttrib2dv", traits, *this}
  , VertexAttrib3dv{"VertexAttrib3dv", traits, *this}
  , VertexAttrib4dv{"VertexAttrib4dv", traits, *this}
  , VertexAttrib1s{"VertexAttrib1s", traits, *this}
  , VertexAttrib2s{"VertexAttrib2s", traits, *this}
  , VertexAttrib3s{"VertexAttrib3s", traits, *this}
  , VertexAttrib4s{"VertexAttrib4s", traits, *this}
  , VertexAttrib1sv{"VertexAttrib1sv", traits, *this}
  , VertexAttrib2sv{"VertexAttrib2sv", traits, *this}
  , VertexAttrib3sv{"VertexAttrib3sv", traits, *this}
  , VertexAttrib4sv{"VertexAttrib4sv", traits, *this}
  , VertexAttribI1i{"VertexAttribI1i", traits, *this}
  , VertexAttribI2i{"VertexAttribI2i", traits, *this}
  , VertexAttribI3i{"VertexAttribI3i", traits, *this}
  , VertexAttribI4i{"VertexAttribI4i", traits, *this}
  , VertexAttribI1iv{"VertexAttribI1iv", traits, *this}
  , VertexAttribI2iv{"VertexAttribI2iv", traits, *this}
  , VertexAttribI3iv{"VertexAttribI3iv", traits, *this}
  , VertexAttribI4iv{"VertexAttribI4iv", traits, *this}
  , VertexAttribI1ui{"VertexAttribI1ui", traits, *this}
  , VertexAttribI2ui{"VertexAttribI2ui", traits, *this}
  , VertexAttribI3ui{"VertexAttribI3ui", traits, *this}
  , VertexAttribI4ui{"VertexAttribI4ui", traits, *this}
  , VertexAttribI1uiv{"VertexAttribI1uiv", traits, *this}
  , VertexAttribI2uiv{"VertexAttribI2uiv", traits, *this}
  , VertexAttribI3uiv{"VertexAttribI3uiv", traits, *this}
  , VertexAttribI4uiv{"VertexAttribI4uiv", traits, *this}
  , VertexAttribI4bv{"VertexAttribI4bv", traits, *this}
  , VertexAttribI4ubv{"VertexAttribI4ubv", traits, *this}
  , VertexAttribI4sv{"VertexAttribI4sv", traits, *this}
  , VertexAttribI4usv{"VertexAttribI4usv", traits, *this}
  , VertexAttrib4bv{"VertexAttrib4bv", traits, *this}
  , VertexAttrib4ubv{"VertexAttrib4ubv", traits, *this}
  , VertexAttrib4usv{"VertexAttrib4usv", traits, *this}
  , VertexAttrib4iv{"VertexAttrib4iv", traits, *this}
  , VertexAttrib4uiv{"VertexAttrib4uiv", traits, *this}
  , VertexAttrib4Nub{"VertexAttrib4Nub", traits, *this}
  , VertexAttrib4Nbv{"VertexAttrib4Nbv", traits, *this}
  , VertexAttrib4Nubv{"VertexAttrib4Nubv", traits, *this}
  , VertexAttrib4Nsv{"VertexAttrib4Nsv", traits, *this}
  , VertexAttrib4Nusv{"VertexAttrib4Nusv", traits, *this}
  , VertexAttrib4Niv{"VertexAttrib4Niv", traits, *this}
  , VertexAttrib4Nuiv{"VertexAttrib4Nuiv", traits, *this}
  , VertexAttribL1d{"VertexAttribL1d", traits, *this}
  , VertexAttribL2d{"VertexAttribL2d", traits, *this}
  , VertexAttribL3d{"VertexAttribL3d", traits, *this}
  , VertexAttribL4d{"VertexAttribL4d", traits, *this}
  , VertexAttribL1dv{"VertexAttribL1dv", traits, *this}
  , VertexAttribL2dv{"VertexAttribL2dv", traits, *this}
  , VertexAttribL3dv{"VertexAttribL3dv", traits, *this}
  , VertexAttribL4dv{"VertexAttribL4dv", traits, *this}
  , VertexAttribP1ui{"VertexAttribP1ui", traits, *this}
  , VertexAttribP2ui{"VertexAttribP2ui", traits, *this}
  , VertexAttribP3ui{"VertexAttribP3ui", traits, *this}
  , VertexAttribP4ui{"VertexAttribP4ui", traits, *this}
  , VertexAttribP1uiv{"VertexAttribP1uiv", traits, *this}
  , VertexAttribP2uiv{"VertexAttribP2uiv", traits, *this}
  , VertexAttribP3uiv{"VertexAttribP3uiv", traits, *this}
  , VertexAttribP4uiv{"VertexAttribP4uiv", traits, *this}
  , VertexAttribFormat{"VertexAttribFormat", traits, *this}
  , VertexAttribIFormat{"VertexAttribIFormat", traits, *this}
  , VertexAttribLFormat{"VertexAttribLFormat", traits, *this}
  , VertexArrayAttribFormat{"VertexArrayAttribFormat", traits, *this}
  , VertexArrayAttribIFormat{"VertexArrayAttribIFormat", traits, *this}
  , VertexArrayAttribLFormat{"VertexArrayAttribLFormat", traits, *this}
  , VertexAttribPointer{"VertexAttribPointer", traits, *this}
  , VertexAttribIPointer{"VertexAttribIPointer", traits, *this}
  , VertexAttribLPointer{"VertexAttribLPointer", traits, *this}
  , GetVertexArrayiv{"GetVertexArrayiv", traits, *this}
  , GetVertexArrayIndexediv{"GetVertexArrayIndexediv", traits, *this}
  , GetVertexArrayIndexed64iv{"GetVertexArrayIndexed64iv", traits, *this}
  , GetVertexAttribdv{"GetVertexAttribdv", traits, *this}
  , GetVertexAttribfv{"GetVertexAttribfv", traits, *this}
  , GetVertexAttribiv{"GetVertexAttribiv", traits, *this}
  , GetVertexAttribIiv{"GetVertexAttribIiv", traits, *this}
  , GetVertexAttribIuiv{"GetVertexAttribIuiv", traits, *this}
  , GetVertexAttribLdv{"GetVertexAttribLdv", traits, *this}
  , GetVertexAttribPointerv{"GetVertexAttribPointerv", traits, *this}
  , ClipControl{"ClipControl", traits, *this}
  , DepthRange{"DepthRange", traits, *this}
  , DepthRangef{"DepthRangef", traits, *this}
  , DepthRangeArrayv{"DepthRangeArrayv", traits, *this}
  , DepthRangeIndexed{"DepthRangeIndexed", traits, *this}
  , Viewport{"Viewport", traits, *this}
  , ViewportArrayv{"ViewportArrayv", traits, *this}
  , ViewportIndexedf{"ViewportIndexedf", traits, *this}
  , ViewportIndexedfv{"ViewportIndexedfv", traits, *this}
  , Scissor{"Scissor", traits, *this}
  , ScissorArrayv{"ScissorArrayv", traits, *this}
  , ScissorIndexed{"ScissorIndexed", traits, *this}
  , ScissorIndexedv{"ScissorIndexedv", traits, *this}
  , StencilFunc{"StencilFunc", traits, *this}
  , StencilFuncSeparate{"StencilFuncSeparate", traits, *this}
  , StencilOp{"StencilOp", traits, *this}
  , StencilOpSeparate{"StencilOpSeparate", traits, *this}
  , DepthFunc{"DepthFunc", traits, *this}
  , ColorMask{"ColorMask", traits, *this}
  , ColorMaski{"ColorMaski", traits, *this}
  , DepthMask{"DepthMask", traits, *this}
  , StencilMask{"StencilMask", traits, *this}
  , StencilMaskSeparate{"StencilMaskSeparate", traits, *this}
  , ClearColor{"ClearColor", traits, *this}
  , ClearDepthf{"ClearDepthf", traits, *this}
  , ClearDepth{"ClearDepth", traits, *this}
  , ClearStencil{"ClearStencil", traits, *this}
  , Clear{"Clear", traits, *this}
  , PrimitiveRestartIndex{"PrimitiveRestartIndex", traits, *this}
  , ProvokingVertex{"ProvokingVertex", traits, *this}
  , LineWidth{"LineWidth", traits, *this}
  , PointSize{"PointSize", traits, *this}
  , PointParameteri{"PointParameteri", traits, *this}
  , PointParameterf{"PointParameterf", traits, *this}
  , PointParameteriv{"PointParameteriv", traits, *this}
  , PointParameterfv{"PointParameterfv", traits, *this}
  , PatchParameteri{"PatchParameteri", traits, *this}
  , PatchParameterfv{"PatchParameterfv", traits, *this}
  , FrontFace{"FrontFace", traits, *this}
  , CullFace{"CullFace", traits, *this}
  , PolygonMode{"PolygonMode", traits, *this}
  , PolygonOffset{"PolygonOffset", traits, *this}
  , PolygonOffsetClamp{"PolygonOffsetClamp", traits, *this}
  , SampleCoverage{"SampleCoverage", traits, *this}
  , SampleMaski{"SampleMaski", traits, *this}
  , MinSampleShading{"MinSampleShading", traits, *this}
  , GetMultisamplefv{"GetMultisamplefv", traits, *this}
  , BlendEquation{"BlendEquation", traits, *this}
  , BlendEquationSeparate{"BlendEquationSeparate", traits, *this}
  , BlendEquationi{"BlendEquationi", traits, *this}
  , BlendEquationSeparatei{"BlendEquationSeparatei", traits, *this}
  , BlendFunc{"BlendFunc", traits, *this}
  , BlendFuncSeparate{"BlendFuncSeparate", traits, *this}
  , BlendFunci{"BlendFunci", traits, *this}
  , BlendFuncSeparatei{"BlendFuncSeparatei", traits, *this}
  , BlendColor{"BlendColor", traits, *this}
  , LogicOp{"LogicOp", traits, *this}
  , DrawArrays{"DrawArrays", traits, *this}
  , DrawArraysInstancedBaseInstance{
      "DrawArraysInstancedBaseInstance",
      traits,
      *this}
  , DrawArraysInstanced{"DrawArraysInstanced", traits, *this}
  , DrawArraysIndirect{"DrawArraysIndirect", traits, *this}
  , MultiDrawArrays{"MultiDrawArrays", traits, *this}
  , MultiDrawArraysIndirect{"MultiDrawArraysIndirect", traits, *this}
  , MultiDrawArraysIndirectCount{"MultiDrawArraysIndirectCount", traits, *this}
  , DrawElements{"DrawElements", traits, *this}
  , DrawRangeElements{"DrawRangeElements", traits, *this}
  , DrawElementsInstancedBaseInstance{
      "DrawElementsInstancedBaseInstance",
      traits,
      *this}
  , DrawElementsInstanced{"DrawElementsInstanced", traits, *this}
  , DrawElementsBaseVertex{"DrawElementsBaseVertex", traits, *this}
  , DrawRangeElementsBaseVertex{"DrawRangeElementsBaseVertex", traits, *this}
  , DrawElementsInstancedBaseVertex{
      "DrawElementsInstancedBaseVertex",
      traits,
      *this}
  , DrawElementsInstancedBaseVertexBaseInstance{
      "DrawElementsInstancedBaseVertexBaseInstance",
      traits,
      *this}
  , DrawElementsIndirect{"DrawElementsIndirect", traits, *this}
  , MultiDrawElements{"MultiDrawElements", traits, *this}
  , MultiDrawElementsIndirect{"MultiDrawElementsIndirect", traits, *this}
  , MultiDrawElementsIndirectCount{
      "MultiDrawElementsIndirectCount",
      traits,
      *this}
  , MultiDrawElementsBaseVertex{"MultiDrawElementsBaseVertex", traits, *this}
  , DrawTransformFeedback{"DrawTransformFeedback", traits, *this}
  , DrawTransformFeedbackInstanced{
      "DrawTransformFeedbackInstanced",
      traits,
      *this}
  , DrawTransformFeedbackStream{"DrawTransformFeedbackStream", traits, *this}
  , DrawTransformFeedbackStreamInstanced{
      "DrawTransformFeedbackStreamInstanced",
      traits,
      *this}
  , DispatchCompute{"DispatchCompute", traits, *this}
  , DispatchComputeIndirect{"DispatchComputeIndirect", traits, *this}
  , ClampColor{"ClampColor", traits, *this}
  , ReadPixels{"ReadPixels", traits, *this}
  , ReadnPixels{"ReadnPixels", traits, *this}
  , GetBooleanv{"GetBooleanv", traits, *this}
  , GetBooleani_v{"GetBooleani_v", traits, *this}
  , GetIntegerv{"GetIntegerv", traits, *this}
  , GetIntegeri_v{"GetIntegeri_v", traits, *this}
  , GetInteger64v{"GetInteger64v", traits, *this}
  , GetInteger64i_v{"GetInteger64i_v", traits, *this}
  , GetFloatv{"GetFloatv", traits, *this}
  , GetFloati_v{"GetFloati_v", traits, *this}
  , GetDoublev{"GetDoublev", traits, *this}
  , GetDoublei_v{"GetDoublei_v", traits, *this}
  , GetInternalformativ{"GetInternalformativ", traits, *this}
  , GetInternalformati64v{"GetInternalformati64v", traits, *this}
  , GetPointerv{"GetPointerv", traits, *this}
  , GetString{"GetString", traits, *this}
  , GetStringi{"GetStringi", traits, *this}
  , NamedString{"NamedStringARB", traits, *this}
  , DeleteNamedString{"DeleteNamedStringARB", traits, *this}
  , IsNamedString{"IsNamedStringARB", traits, *this}
  , GetNamedStringiv{"GetNamedStringivARB", traits, *this}
  , GetNamedString{"GetNamedStringARB", traits, *this}
  , DebugMessageCallback{"DebugMessageCallback", traits, *this}
  , DebugMessageControl{"DebugMessageControl", traits, *this}
  , DebugMessageInsert{"DebugMessageInsert", traits, *this}
  , PushDebugGroup{"PushDebugGroup", traits, *this}
  , PopDebugGroup{"PopDebugGroup", traits, *this}
  , ObjectLabel{"ObjectLabel", traits, *this}
  , ObjectPtrLabel{"ObjectPtrLabel", traits, *this}
  , GetObjectLabel{"GetObjectLabel", traits, *this}
  , GetObjectPtrLabel{"GetObjectPtrLabel", traits, *this}
  , GetDebugMessageLog{"GetDebugMessageLog", traits, *this}
  , Begin{"Begin", traits, *this}
  , End{"End", traits, *this}
  , Vertex2i{"Vertex2i", traits, *this}
  , Vertex3i{"Vertex3i", traits, *this}
  , Vertex4i{"Vertex4i", traits, *this}
  , Vertex2f{"Vertex2f", traits, *this}
  , Vertex3f{"Vertex3f", traits, *this}
  , Vertex4f{"Vertex4f", traits, *this}
  , Color3i{"Color3i", traits, *this}
  , Color4i{"Color4i", traits, *this}
  , Color3f{"Color3f", traits, *this}
  , Color4f{"Color4f", traits, *this}
  , SecondaryColor3i{"SecondaryColor3i", traits, *this}
  , SecondaryColor4i{"SecondaryColor4i", traits, *this}
  , SecondaryColor3f{"SecondaryColor3f", traits, *this}
  , SecondaryColor4f{"SecondaryColor4f", traits, *this}
  , TexCoord1i{"TexCoord1i", traits, *this}
  , TexCoord2i{"TexCoord2i", traits, *this}
  , TexCoord3i{"TexCoord3i", traits, *this}
  , TexCoord4i{"TexCoord4i", traits, *this}
  , TexCoord1f{"TexCoord1f", traits, *this}
  , TexCoord2f{"TexCoord2f", traits, *this}
  , TexCoord3f{"TexCoord3f", traits, *this}
  , TexCoord4f{"TexCoord4f", traits, *this}
  , MultiTexCoord1i{"MultiTexCoord1i", traits, *this}
  , MultiTexCoord2i{"MultiTexCoord2i", traits, *this}
  , MultiTexCoord3i{"MultiTexCoord3i", traits, *this}
  , MultiTexCoord4i{"MultiTexCoord4i", traits, *this}
  , MultiTexCoord1f{"MultiTexCoord1f", traits, *this}
  , MultiTexCoord2f{"MultiTexCoord2f", traits, *this}
  , MultiTexCoord3f{"MultiTexCoord3f", traits, *this}
  , MultiTexCoord4f{"MultiTexCoord4f", traits, *this}
  , MatrixMode{"MatrixMode", traits, *this}
  , PushMatrix{"PushMatrix", traits, *this}
  , PopMatrix{"PopMatrix", traits, *this}
  , MatrixPushEXT{"MatrixPushEXT", traits, *this}
  , MatrixPopEXT{"MatrixPopEXT", traits, *this}
  , LoadIdentity{"LoadIdentity", traits, *this}
  , MatrixLoadIdentityEXT{"MatrixLoadIdentityEXT", traits, *this}
  , Translatef{"Translatef", traits, *this}
  , Translated{"Translated", traits, *this}
  , MatrixTranslatefEXT{"MatrixTranslatefEXT", traits, *this}
  , MatrixTranslatedEXT{"MatrixTranslatedEXT", traits, *this}
  , Rotatef{"Rotatef", traits, *this}
  , Rotated{"Rotated", traits, *this}
  , MatrixRotatefEXT{"MatrixRotatefEXT", traits, *this}
  , MatrixRotatedEXT{"MatrixRotatedEXT", traits, *this}
  , Scalef{"Scalef", traits, *this}
  , Scaled{"Scaled", traits, *this}
  , MatrixScalefEXT{"MatrixScalefEXT", traits, *this}
  , MatrixScaledEXT{"MatrixScaledEXT", traits, *this}
  , Frustum{"Frustum", traits, *this}
  , Ortho{"Ortho", traits, *this}
  , MatrixFrustumEXT{"MatrixFrustumEXT", traits, *this}
  , MatrixOrthoEXT{"MatrixOrthoEXT", traits, *this}
  , LoadMatrixf{"LoadMatrixf", traits, *this}
  , LoadMatrixd{"LoadMatrixd", traits, *this}
  , MatrixLoadfEXT{"MatrixLoadfEXT", traits, *this}
  , MatrixLoaddEXT{"MatrixLoaddEXT", traits, *this}
  , MultMatrixf{"MultMatrixf", traits, *this}
  , MultMatrixd{"MultMatrixd", traits, *this}
  , MatrixMultfEXT{"MatrixMultfEXT", traits, *this}
  , MatrixMultdEXT{"MatrixMultdEXT", traits, *this}
  , LoadTransposeMatrixf{"LoadTransposeMatrixf", traits, *this}
  , LoadTransposeMatrixd{"LoadTransposeMatrixd", traits, *this}
  , MatrixLoadTransposefEXT{"MatrixLoadTransposefEXT", traits, *this}
  , MatrixLoadTransposedEXT{"MatrixLoadTransposedEXT", traits, *this}
  , MultTransposeMatrixf{"MultTransposeMatrixf", traits, *this}
  , MultTransposeMatrixd{"MultTransposeMatrixd", traits, *this}
  , MatrixMultTransposefEXT{"MatrixMultTransposefEXT", traits, *this}
  , MatrixMultTransposedEXT{"MatrixMultTransposedEXT", traits, *this}
  , MatrixLoad3x2fNV{"MatrixLoad3x2fNV", traits, *this}
  , MatrixLoad3x3fNV{"MatrixLoad3x3fNV", traits, *this}
  , MatrixLoadTranspose3x3fNV{"MatrixLoadTranspose3x3fNV", traits, *this}
  , MatrixMult3x2fNV{"MatrixMult3x2fNV", traits, *this}
  , MatrixMult3x3fNV{"MatrixMult3x3fNV", traits, *this}
  , MatrixMultTranspose3x3fNV{"MatrixMultTranspose3x3fNV", traits, *this}
  , GenPathsNV{"GenPathsNV", traits, *this}
  , DeletePathsNV{"DeletePathsNV", traits, *this}
  , IsPathNV{"IsPathNV", traits, *this}
  , PathParameterivNV{"PathParameterivNV", traits, *this}
  , PathParameteriNV{"PathParameteriNV", traits, *this}
  , PathParameterfvNV{"PathParameterfvNV", traits, *this}
  , PathParameterfNV{"PathParameterfNV", traits, *this}
  , PathCommandsNV{"PathCommandsNV", traits, *this}
  , PathSubCommandsNV{"PathSubCommandsNV", traits, *this}
  , PathCoordsNV{"PathCoordsNV", traits, *this}
  , PathSubCoordsNV{"PathSubCoordsNV", traits, *this}
  , PathStringNV{"PathStringNV", traits, *this}
  , PathGlyphsNV{"PathGlyphsNV", traits, *this}
  , PathGlyphRangeNV{"PathGlyphRangeNV", traits, *this}
  , PathGlyphIndexArrayNV{"PathGlyphIndexArrayNV", traits, *this}
  , PathMemoryGlyphIndexArrayNV{"PathMemoryGlyphIndexArrayNV", traits, *this}
  , PathGlyphIndexRangeNV{"PathGlyphIndexRangeNV", traits, *this}
  , CopyPathNV{"CopyPathNV", traits, *this}
  , InterpolatePathsNV{"InterpolatePaths", traits, *this}
  , WeightPathsNV{"WeightPathsNV", traits, *this}
  , TransformPathNV{"TransformPathNV", traits, *this}
  , PathStencilFuncNV{"PathStencilFuncNV", traits, *this}
  , PathStencilDepthOffsetNV{"PathStencilDepthOffsetNV", traits, *this}
  , StencilFillPathNV{"StencilFillPathNV", traits, *this}
  , StencilStrokePathNV{"StencilStrokePathNV", traits, *this}
  , StencilFillPathInstancedNV{"StencilFillPathInstancedNV", traits, *this}
  , StencilStrokePathInstancedNV{"StencilStrokePathInstancedNV", traits, *this}
  , PathCoverDepthFuncNV{"PathCoverDepthFuncNV", traits, *this}
  , PathColorGenNV{"PathColorGenNV", traits, *this}
  , PathTexGenNV{"PathTexGenNV", traits, *this}
  , PathFogGenNV{"PathFogGenNV", traits, *this}
  , ProgramPathFragmentInputGenNV{"ProgramPathFragmentInputGenNV", traits, *this}
  , CoverFillPathNV{"CoverFillPathNV", traits, *this}
  , CoverStrokePathNV{"CoverStrokePathNV", traits, *this}
  , CoverFillPathInstancedNV{"CoverFillPathInstancedNV", traits, *this}
  , CoverStrokePathInstancedNV{"CoverStrokePathInstancedNV", traits, *this}
  , StencilThenCoverFillPathNV{"StencilThenCoverFillPathNV", traits, *this}
  , StencilThenCoverStrokePathNV{"StencilThenCoverStrokePathNV", traits, *this}
  , StencilThenCoverFillPathInstancedNV{
      "StencilThenCoverFillPathInstancedNV",
      traits,
      *this}
  , StencilThenCoverStrokePathInstancedNV{
      "StencilThenCoverStrokePathInstancedNV",
      traits,
      *this}
  , GetPathParameterivNV{"GetPathParameterivNV", traits, *this}
  , GetPathParameterfvNV{"GetPathParameterfvNV", traits, *this}
  , GetPathCommandsNV{"GetPathCommandsNV", traits, *this}
  , GetPathCoordsNV{"GetPathCoordsNV", traits, *this}
  , GetPathDashArrayNV{"GetPathDashArrayNV", traits, *this}
  , GetPathMetricsNV{"GetPathMetricsNV", traits, *this}
  , GetPathMetricRangeNV{"GetPathMetricRangeNV", traits, *this}
  , GetPathSpacingNV{"GetPathSpacingNV", traits, *this}
  , GetPathColorGenivNV{"GetPathColorGenivNV", traits, *this}
  , GetPathColorGenfvNV{"GetPathColorGenfvNV", traits, *this}
  , GetPathTexGenivNV{"GetPathTexGenivNV", traits, *this}
  , GetPathTexGenfvNV{"GetPathTexGenfvNV", traits, *this}
  , GetPathLengthNV{"GetPathLengthNV", traits, *this}
  , IsPointInFillPathNV{"IsPointInFillPathNV", traits, *this}
  , IsPointInStrokePathNV{"IsPointInStrokePathNV", traits, *this}
  , PointAlongPathNV{"PointAlongPathNV", traits, *this}
  , MaxShaderCompilerThreadsARB{"MaxShaderCompilerThreadsARB", traits, *this}
  , Hint{"Hint", traits, *this}
  , Flush{"Flush", traits, *this}
  , Finish{"Finish", traits, *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oglplus
