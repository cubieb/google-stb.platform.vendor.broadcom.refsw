/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#ifndef KHRONOS_MANGLE_H
#if defined KHRONOS_NAME_MANGLING || defined REMOTE_API_LOGGING || defined BCG_MULTI_THREADED

/* Prevent mangled names from being visible outside the dll */
#undef EGLAPIENTRY
#define EGLAPIENTRY

#undef EGLAPI
#define EGLAPI

#undef GL_API
#define GL_API

#undef GL_APICALL
#define GL_APICALL

#undef GL_APIENTRY
#define GL_APIENTRY

#undef VG_API_CALL
#define VG_API_CALL

#undef VGU_API_CALL
#define VGU_API_CALL

#undef VG_API_ENTRY
#define VG_API_ENTRY

/* EGL Functions */

#define eglGetError mangled_eglGetError
#define eglGetDisplay mangled_eglGetDisplay
#define eglInitialize mangled_eglInitialize
#define eglTerminate mangled_eglTerminate
#define eglQueryString mangled_eglQueryString
#define eglGetConfigs mangled_eglGetConfigs
#define eglChooseConfig mangled_eglChooseConfig
#define eglGetConfigAttrib mangled_eglGetConfigAttrib
#define eglCreateWindowSurface mangled_eglCreateWindowSurface
#define eglCreatePbufferSurface mangled_eglCreatePbufferSurface
#define eglCreatePixmapSurface mangled_eglCreatePixmapSurface
#define eglDestroySurface mangled_eglDestroySurface
#define eglQuerySurface mangled_eglQuerySurface
#define eglBindAPI mangled_eglBindAPI
#define eglQueryAPI mangled_eglQueryAPI
#define eglWaitClient mangled_eglWaitClient
#define eglReleaseThread mangled_eglReleaseThread
#define eglCreatePbufferFromClientBuffer mangled_eglCreatePbufferFromClientBuffer
#define eglSurfaceAttrib mangled_eglSurfaceAttrib
#define eglBindTexImage mangled_eglBindTexImage
#define eglReleaseTexImage mangled_eglReleaseTexImage
#define eglSwapInterval mangled_eglSwapInterval
#define eglCreateContext mangled_eglCreateContext
#define eglDestroyContext mangled_eglDestroyContext
#define eglMakeCurrent mangled_eglMakeCurrent
#define eglGetCurrentContext mangled_eglGetCurrentContext
#define eglGetCurrentSurface mangled_eglGetCurrentSurface
#define eglGetCurrentDisplay mangled_eglGetCurrentDisplay
#define eglQueryContext mangled_eglQueryContext
#define eglWaitGL mangled_eglWaitGL
#define eglWaitNative mangled_eglWaitNative
#define eglSwapBuffers mangled_eglSwapBuffers
#define eglCopyBuffers mangled_eglCopyBuffers
#define eglGetProcAddress mangled_eglGetProcAddress
#define eglClientWaitSyncKHR mangled_eglClientWaitSyncKHR
#define eglCreateImageKHR mangled_eglCreateImageKHR
#define eglCreateSyncKHR mangled_eglCreateSyncKHR
#define eglDestroyImageKHR mangled_eglDestroyImageKHR
#define eglDestroySyncKHR mangled_eglDestroySyncKHR
#define eglGetSyncAttribKHR mangled_eglGetSyncAttribKHR
#define eglQueryProfilingDataNOK mangled_eglQueryProfilingDataNOK
#define eglLockSurfaceKHR mangled_eglLockSurfaceKHR
#define eglUnlockSurfaceKHR mangled_eglUnlockSurfaceKHR
#define glEGLImageTargetRenderbufferStorageOES mangled_glEGLImageTargetRenderbufferStorageOES
#define glEGLImageTargetTexture2DOES mangled_glEGLImageTargetTexture2DOES
#define eglAcquireGlobalImageBRCM mangled_eglAcquireGlobalImageBRCM
#define eglCreateCopyGlobalImageBRCM mangled_eglCreateCopyGlobalImageBRCM
#define eglCreateGlobalImageBRCM mangled_eglCreateGlobalImageBRCM
#define eglReleaseGlobalImageBRCM mangled_eglReleaseGlobalImageBRCM
#define eglInitGlobalImageBRCM mangled_eglInitGlobalImageBRCM
#define eglTermGlobalImageBRCM mangled_eglTermGlobalImageBRCM
#define eglImageUpdateParameterivBRCM mangled_eglImageUpdateParameterivBRCM
#define eglImageUpdateParameteriBRCM mangled_eglImageUpdateParameteriBRCM
#define eglGetPlatformDisplayEXT mangled_eglGetPlatformDisplayEXT
#define eglCreatePlatformWindowSurfaceEXT mangled_eglCreatePlatformWindowSurfaceEXT
#define eglCreatePlatformPixmapSurfaceEXT mangled_eglCreatePlatformPixmapSurfaceEXT
#define eglBindWaylandDisplayWL mangled_eglBindWaylandDisplayWL
#define eglUnbindWaylandDisplayWL mangled_eglUnbindWaylandDisplayWL
#define eglQueryWaylandBufferWL mangled_eglQueryWaylandBufferWL

/* OpenGL ES 1.1 and 2.0 functions */

#define glAlphaFunc mangled_glAlphaFunc
#define glClearColor mangled_glClearColor
#define glClearDepthf mangled_glClearDepthf
#define glClipPlanef mangled_glClipPlanef
#define glColor4f mangled_glColor4f
#define glDepthRangef mangled_glDepthRangef
#define glFogf mangled_glFogf
#define glFogfv mangled_glFogfv
#define glFrustumf mangled_glFrustumf
#define glGetClipPlanef mangled_glGetClipPlanef
#define glGetFloatv mangled_glGetFloatv
#define glGetLightfv mangled_glGetLightfv
#define glGetMaterialfv mangled_glGetMaterialfv
#define glGetTexEnvfv mangled_glGetTexEnvfv
#define glGetTexParameterfv mangled_glGetTexParameterfv
#define glLightModelf mangled_glLightModelf
#define glLightModelfv mangled_glLightModelfv
#define glLightf mangled_glLightf
#define glLightfv mangled_glLightfv
#define glLineWidth mangled_glLineWidth
#define glLoadMatrixf mangled_glLoadMatrixf
#define glMaterialf mangled_glMaterialf
#define glMaterialfv mangled_glMaterialfv
#define glMultMatrixf mangled_glMultMatrixf
#define glMultiTexCoord4f mangled_glMultiTexCoord4f
#define glNormal3f mangled_glNormal3f
#define glOrthof mangled_glOrthof
#define glPointParameterf mangled_glPointParameterf
#define glPointParameterfv mangled_glPointParameterfv
#define glPointSize mangled_glPointSize
#define glPolygonOffset mangled_glPolygonOffset
#define glRotatef mangled_glRotatef
#define glScalef mangled_glScalef
#define glTexEnvf mangled_glTexEnvf
#define glTexEnvfv mangled_glTexEnvfv
#define glTexParameterf mangled_glTexParameterf
#define glTexParameterfv mangled_glTexParameterfv
#define glTranslatef mangled_glTranslatef

#define glActiveTexture mangled_glActiveTexture
#define glAlphaFuncx mangled_glAlphaFuncx
#define glBindBuffer mangled_glBindBuffer
#define glBindTexture mangled_glBindTexture
#define glBlendFunc mangled_glBlendFunc
#define glBlendColor mangled_glBlendColor
#define glBufferData mangled_glBufferData
#define glBlendEquation mangled_glBlendEquation
#define glBufferSubData mangled_glBufferSubData
#define glClear mangled_glClear
#define glClearColorx mangled_glClearColorx
#define glClearDepthx mangled_glClearDepthx
#define glClearStencil mangled_glClearStencil
#define glClientActiveTexture mangled_glClientActiveTexture
#define glClipPlanex mangled_glClipPlanex
#define glColor4ub mangled_glColor4ub
#define glColor4x mangled_glColor4x
#define glColorMask mangled_glColorMask
#define glColorPointer mangled_glColorPointer
#define glCompressedTexImage2D mangled_glCompressedTexImage2D
#define glCompressedTexSubImage2D mangled_glCompressedTexSubImage2D
#define glCopyTexImage2D mangled_glCopyTexImage2D
#define glCopyTexSubImage2D mangled_glCopyTexSubImage2D
#define glCullFace mangled_glCullFace
#define glDeleteBuffers mangled_glDeleteBuffers
#define glDeleteTextures mangled_glDeleteTextures
#define glDepthFunc mangled_glDepthFunc
#define glDepthMask mangled_glDepthMask
#define glDepthRangex mangled_glDepthRangex
#define glDisable mangled_glDisable
#define glDisableClientState mangled_glDisableClientState
#define glDrawArrays mangled_glDrawArrays
#define glDrawElements mangled_glDrawElements
#define glEnable mangled_glEnable
#define glEnableClientState mangled_glEnableClientState
#define glFinish mangled_glFinish
#define glFlush mangled_glFlush
#define glFogx mangled_glFogx
#define glFogxv mangled_glFogxv
#define glFrontFace mangled_glFrontFace
#define glFrustumx mangled_glFrustumx
#define glGetBooleanv mangled_glGetBooleanv
#define glGetBufferParameteriv mangled_glGetBufferParameteriv
#define glGetClipPlanex mangled_glGetClipPlanex
#define glGenBuffers mangled_glGenBuffers
#define glGenTextures mangled_glGenTextures
#define glGetError mangled_glGetError
#define glGetFixedv mangled_glGetFixedv
#define glGetIntegerv mangled_glGetIntegerv
#define glGetLightxv mangled_glGetLightxv
#define glGetMaterialxv mangled_glGetMaterialxv
#define glGetPointerv mangled_glGetPointerv
#define glGetString mangled_glGetString
#define glGetTexEnviv mangled_glGetTexEnviv
#define glGetTexEnvxv mangled_glGetTexEnvxv
#define glGetTexParameteriv mangled_glGetTexParameteriv
#define glGetTexParameterxv mangled_glGetTexParameterxv
#define glHint mangled_glHint
#define glIsBuffer mangled_glIsBuffer
#define glIsEnabled mangled_glIsEnabled
#define glIsTexture mangled_glIsTexture
#define glLightModelx mangled_glLightModelx
#define glLightModelxv mangled_glLightModelxv
#define glLightx mangled_glLightx
#define glLightxv mangled_glLightxv
#define glLineWidthx mangled_glLineWidthx
#define glLoadIdentity mangled_glLoadIdentity
#define glLoadMatrixx mangled_glLoadMatrixx
#define glLogicOp mangled_glLogicOp
#define glMaterialx mangled_glMaterialx
#define glMaterialxv mangled_glMaterialxv
#define glMatrixMode mangled_glMatrixMode
#define glMultMatrixx mangled_glMultMatrixx
#define glMultiTexCoord4x mangled_glMultiTexCoord4x
#define glNormal3x mangled_glNormal3x
#define glNormalPointer mangled_glNormalPointer
#define glOrthox mangled_glOrthox
#define glPixelStorei mangled_glPixelStorei
#define glPointParameterx mangled_glPointParameterx
#define glPointParameterxv mangled_glPointParameterxv
#define glPointSizex mangled_glPointSizex
#define glPolygonOffsetx mangled_glPolygonOffsetx
#define glPopMatrix mangled_glPopMatrix
#define glPushMatrix mangled_glPushMatrix
#define glReadPixels mangled_glReadPixels
#define glRotatex mangled_glRotatex
#define glSampleCoverage mangled_glSampleCoverage
#define glSampleCoveragex mangled_glSampleCoveragex
#define glScalex mangled_glScalex
#define glScissor mangled_glScissor
#define glShadeModel mangled_glShadeModel
#define glStencilFunc mangled_glStencilFunc
#define glStencilMask mangled_glStencilMask
#define glStencilOp mangled_glStencilOp
#define glTexCoordPointer mangled_glTexCoordPointer
#define glTexEnvi mangled_glTexEnvi
#define glTexEnvx mangled_glTexEnvx
#define glTexEnviv mangled_glTexEnviv
#define glTexEnvxv mangled_glTexEnvxv
#define glTexImage2D mangled_glTexImage2D
#define glTexParameteri mangled_glTexParameteri
#define glTexParameterx mangled_glTexParameterx
#define glTexParameteriv mangled_glTexParameteriv
#define glTexParameterxv mangled_glTexParameterxv
#define glTexSubImage2D mangled_glTexSubImage2D
#define glTranslatex mangled_glTranslatex
#define glVertexPointer mangled_glVertexPointer
#define glViewport mangled_glViewport

#define glAttachShader mangled_glAttachShader
#define glBindAttribLocation mangled_glBindAttribLocation
#define glBlendEquationSeparate mangled_glBlendEquationSeparate
#define glBlendFuncSeparate mangled_glBlendFuncSeparate
#define glCreateProgram mangled_glCreateProgram
#define glCreateShader mangled_glCreateShader
#define glDeleteProgram mangled_glDeleteProgram
#define glDeleteShader mangled_glDeleteShader
#define glDetachShader mangled_glDetachShader
#define glDisableVertexAttribArray mangled_glDisableVertexAttribArray
#define glEnableVertexAttribArray mangled_glEnableVertexAttribArray
#define glGetActiveAttrib mangled_glGetActiveAttrib
#define glGetActiveUniform mangled_glGetActiveUniform
#define glGetAttachedShaders mangled_glGetAttachedShaders
#define glGetAttribLocation mangled_glGetAttribLocation
#define glGetProgramiv mangled_glGetProgramiv
#define glGetProgramInfoLog mangled_glGetProgramInfoLog
#define glGetUniformfv mangled_glGetUniformfv
#define glGetUniformiv mangled_glGetUniformiv
#define glGetUniformLocation mangled_glGetUniformLocation
#define glGetVertexAttribfv mangled_glGetVertexAttribfv
#define glGetVertexAttribiv mangled_glGetVertexAttribiv
#define glGetVertexAttribPointerv mangled_glGetVertexAttribPointerv
#define glIsProgram mangled_glIsProgram
#define glIsShader mangled_glIsShader
#define glLinkProgram mangled_glLinkProgram
#define glStencilFuncSeparate mangled_glStencilFuncSeparate
#define glStencilMaskSeparate mangled_glStencilMaskSeparate
#define glStencilOpSeparate mangled_glStencilOpSeparate
#define glUniform1i mangled_glUniform1i
#define glUniform2i mangled_glUniform2i
#define glUniform3i mangled_glUniform3i
#define glUniform4i mangled_glUniform4i
#define glUniform1f mangled_glUniform1f
#define glUniform2f mangled_glUniform2f
#define glUniform3f mangled_glUniform3f
#define glUniform4f mangled_glUniform4f
#define glUniform1iv mangled_glUniform1iv
#define glUniform2iv mangled_glUniform2iv
#define glUniform3iv mangled_glUniform3iv
#define glUniform4iv mangled_glUniform4iv
#define glUniform1fv mangled_glUniform1fv
#define glUniform2fv mangled_glUniform2fv
#define glUniform3fv mangled_glUniform3fv
#define glUniform4fv mangled_glUniform4fv
#define glUniformMatrix2fv mangled_glUniformMatrix2fv
#define glUniformMatrix3fv mangled_glUniformMatrix3fv
#define glUniformMatrix4fv mangled_glUniformMatrix4fv
#define glUseProgram mangled_glUseProgram
#define glValidateProgram mangled_glValidateProgram
#define glVertexAttrib1f mangled_glVertexAttrib1f
#define glVertexAttrib2f mangled_glVertexAttrib2f
#define glVertexAttrib3f mangled_glVertexAttrib3f
#define glVertexAttrib4f mangled_glVertexAttrib4f
#define glVertexAttrib1fv mangled_glVertexAttrib1fv
#define glVertexAttrib2fv mangled_glVertexAttrib2fv
#define glVertexAttrib3fv mangled_glVertexAttrib3fv
#define glVertexAttrib4fv mangled_glVertexAttrib4fv
#define glVertexAttribPointer mangled_glVertexAttribPointer
#define glCompileShader mangled_glCompileShader
#define glGetShaderiv mangled_glGetShaderiv
#define glGetShaderInfoLog mangled_glGetShaderInfoLog
#define glGetShaderSource mangled_glGetShaderSource
#define glReleaseShaderCompiler mangled_glReleaseShaderCompiler
#define glShaderSource mangled_glShaderSource
#define glShaderBinary mangled_glShaderBinary
#define glGetShaderPrecisionFormat mangled_glGetShaderPrecisionFormat
#define glIsRenderbuffer mangled_glIsRenderbuffer
#define glBindRenderbuffer mangled_glBindRenderbuffer
#define glDeleteRenderbuffers mangled_glDeleteRenderbuffers
#define glGenRenderbuffers mangled_glGenRenderbuffers
#define glRenderbufferStorage mangled_glRenderbufferStorage
#define glGetRenderbufferParameteriv mangled_glGetRenderbufferParameteriv
#define glIsFramebuffer mangled_glIsFramebuffer
#define glBindFramebuffer mangled_glBindFramebuffer
#define glDeleteFramebuffers mangled_glDeleteFramebuffers
#define glGenFramebuffers mangled_glGenFramebuffers
#define glCheckFramebufferStatus mangled_glCheckFramebufferStatus
#define glFramebufferTexture2D mangled_glFramebufferTexture2D
#define glFramebufferRenderbuffer mangled_glFramebufferRenderbuffer
#define glGetFramebufferAttachmentParameteriv mangled_glGetFramebufferAttachmentParameteriv
#define glGenerateMipmap mangled_glGenerateMipmap

#define glRenderbufferStorageMultisampleEXT mangled_glRenderbufferStorageMultisampleEXT
#define glFramebufferTexture2DMultisampleEXT mangled_glFramebufferTexture2DMultisampleEXT

#define glPointSizePointerOES mangled_glPointSizePointerOES
#define glDiscardFramebufferEXT mangled_glDiscardFramebufferEXT
#define glInsertEventMarkerEXT mangled_glInsertEventMarkerEXT
#define glPushGroupMarkerEXT mangled_glPushGroupMarkerEXT
#define glPopGroupMarkerEXT mangled_glPopGroupMarkerEXT

#define glDrawTexfOES mangled_glDrawTexfOES
#define glDrawTexfvOES mangled_glDrawTexfvOES
#define glDrawTexiOES mangled_glDrawTexiOES
#define glDrawTexivOES mangled_glDrawTexivOES
#define glDrawTexsOES mangled_glDrawTexsOES
#define glDrawTexsvOES mangled_glDrawTexsvOES
#define glDrawTexxOES mangled_glDrawTexxOES
#define glDrawTexxvOES mangled_glDrawTexxvOES

#define glIsRenderbufferOES mangled_glIsRenderbufferOES
#define glBindRenderbufferOES mangled_glBindRenderbufferOES
#define glDeleteRenderbuffersOES mangled_glDeleteRenderbuffersOES
#define glGenRenderbuffersOES mangled_glGenRenderbuffersOES
#define glRenderbufferStorageOES mangled_glRenderbufferStorageOES
#define glGetRenderbufferParameterivOES mangled_glGetRenderbufferParameterivOES
#define glIsFramebufferOES mangled_glIsFramebufferOES
#define glBindFramebufferOES mangled_glBindFramebufferOES
#define glDeleteFramebuffersOES mangled_glDeleteFramebuffersOES
#define glGenFramebuffersOES mangled_glGenFramebuffersOES
#define glCheckFramebufferStatusOES mangled_glCheckFramebufferStatusOES
#define glFramebufferRenderbufferOES mangled_glFramebufferRenderbufferOES
#define glFramebufferTexture2DOES mangled_glFramebufferTexture2DOES
#define glGetFramebufferAttachmentParameterivOES mangled_glGetFramebufferAttachmentParameterivOES
#define glGenerateMipmapOES mangled_glGenerateMipmapOES

#endif

#if defined KHRONOS_NAME_MANGLING || defined BCG_MULTI_THREADED

#define vgCreateEGLImageTargetKHR mangled_vgCreateEGLImageTargetKHR

#define vgGetError mangled_vgGetError
#define vgFlush mangled_vgFlush
#define vgFinish mangled_vgFinish
#define vgSetf mangled_vgSetf
#define vgSeti mangled_vgSeti
#define vgSetfv mangled_vgSetfv
#define vgSetiv mangled_vgSetiv
#define vgGetf mangled_vgGetf
#define vgGeti mangled_vgGeti
#define vgGetVectorSize mangled_vgGetVectorSize
#define vgGetfv mangled_vgGetfv
#define vgGetiv mangled_vgGetiv
#define vgSetParameterf mangled_vgSetParameterf
#define vgSetParameteri mangled_vgSetParameteri
#define vgSetParameterfv mangled_vgSetParameterfv
#define vgSetParameteriv mangled_vgSetParameteriv
#define vgGetParameterf mangled_vgGetParameterf
#define vgGetParameteri mangled_vgGetParameteri
#define vgGetParameterVectorSize mangled_vgGetParameterVectorSize
#define vgGetParameterfv mangled_vgGetParameterfv
#define vgGetParameteriv mangled_vgGetParameteriv
#define vgLoadIdentity mangled_vgLoadIdentity
#define vgLoadMatrix mangled_vgLoadMatrix
#define vgGetMatrix mangled_vgGetMatrix
#define vgMultMatrix mangled_vgMultMatrix
#define vgTranslate mangled_vgTranslate
#define vgScale mangled_vgScale
#define vgShear mangled_vgShear
#define vgRotate mangled_vgRotate
#define vgMask mangled_vgMask
#define vgRenderToMask mangled_vgRenderToMask
#define vgCreateMaskLayer mangled_vgCreateMaskLayer
#define vgDestroyMaskLayer mangled_vgDestroyMaskLayer
#define vgFillMaskLayer mangled_vgFillMaskLayer
#define vgCopyMask mangled_vgCopyMask
#define vgClear mangled_vgClear
#define vgCreatePath mangled_vgCreatePath
#define vgClearPath mangled_vgClearPath
#define vgDestroyPath mangled_vgDestroyPath
#define vgRemovePathCapabilities mangled_vgRemovePathCapabilities
#define vgGetPathCapabilities mangled_vgGetPathCapabilities
#define vgAppendPath mangled_vgAppendPath
#define vgAppendPathData mangled_vgAppendPathData
#define vgModifyPathCoords mangled_vgModifyPathCoords
#define vgTransformPath mangled_vgTransformPath
#define vgInterpolatePath mangled_vgInterpolatePath
#define vgPathLength mangled_vgPathLength
#define vgPointAlongPath mangled_vgPointAlongPath
#define vgPathBounds mangled_vgPathBounds
#define vgPathTransformedBounds mangled_vgPathTransformedBounds
#define vgDrawPath mangled_vgDrawPath
#define vgCreatePaint mangled_vgCreatePaint
#define vgDestroyPaint mangled_vgDestroyPaint
#define vgSetPaint mangled_vgSetPaint
#define vgGetPaint mangled_vgGetPaint
#define vgSetColor mangled_vgSetColor
#define vgGetColor mangled_vgGetColor
#define vgPaintPattern mangled_vgPaintPattern
#define vgCreateImage mangled_vgCreateImage
#define vgDestroyImage mangled_vgDestroyImage
#define vgClearImage mangled_vgClearImage
#define vgImageSubData mangled_vgImageSubData
#define vgGetImageSubData mangled_vgGetImageSubData
#define vgChildImage mangled_vgChildImage
#define vgGetParent mangled_vgGetParent
#define vgCopyImage mangled_vgCopyImage
#define vgDrawImage mangled_vgDrawImage
#define vgSetPixels mangled_vgSetPixels
#define vgWritePixels mangled_vgWritePixels
#define vgGetPixels mangled_vgGetPixels
#define vgReadPixels mangled_vgReadPixels
#define vgCopyPixels mangled_vgCopyPixels
#define vgCreateFont mangled_vgCreateFont
#define vgDestroyFont mangled_vgDestroyFont
#define vgSetGlyphToPath mangled_vgSetGlyphToPath
#define vgSetGlyphToImage mangled_vgSetGlyphToImage
#define vgClearGlyph mangled_vgClearGlyph
#define vgDrawGlyph mangled_vgDrawGlyph
#define vgDrawGlyphs mangled_vgDrawGlyphs
#define vgColorMatrix mangled_vgColorMatrix
#define vgConvolve mangled_vgConvolve
#define vgSeparableConvolve mangled_vgSeparableConvolve
#define vgGaussianBlur mangled_vgGaussianBlur
#define vgLookup mangled_vgLookup
#define vgLookupSingle mangled_vgLookupSingle
#define vgHardwareQuery mangled_vgHardwareQuery
#define vgGetString mangled_vgGetString
#define vgCreateEGLImageTargetKHR mangled_vgCreateEGLImageTargetKHR

#define vguArc mangled_vguArc
#define vguComputeWarpQuadToQuad mangled_vguComputeWarpQuadToQuad
#define vguComputeWarpQuadToSquare mangled_vguComputeWarpQuadToSquare
#define vguComputeWarpSquareToQuad mangled_vguComputeWarpSquareToQuad
#define vguEllipse mangled_vguEllipse
#define vguLine mangled_vguLine
#define vguPolygon mangled_vguPolygon
#define vguRect mangled_vguRect
#define vguRoundRect mangled_vguRoundRect

#endif   //KHRONOS_NAME_MANGLING
#endif   //KHRONOS_MANGLED_H
