/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#ifndef KHRONOS_MANGLE_H
#if defined KHRONOS_NAME_MANGLING || defined REMOTE_API_LOGGING || defined BCG_MULTI_THREADED

#undef EGLAPIENTRY
#define EGLAPIENTRY KHRONOS_APIENTRY

#undef EGLAPI
#ifdef KHAPI
#define EGLAPI KHAPI
#else
#define EGLAPI extern
#endif

#undef GL_API
#define GL_API KHRONOS_APICALL

#undef GL_APICALL
#define GL_APICALL  KHRONOS_APICALL

#undef GL_APIENTRY
#define GL_APIENTRY KHRONOS_APIENTRY

#undef VG_API_CALL
#ifdef KHAPI
#define VG_API_CALL KHAPI
#else
#define VG_API_CALL extern
#endif

#undef VGU_API_CALL
#define VGU_API_CALL VG_API_CALL

#undef VG_API_ENTRY
#define VG_API_ENTRY

/* EGL Functions */

#undef eglGetError
#undef eglGetDisplay
#undef eglInitialize
#undef eglTerminate
#undef eglQueryString
#undef eglGetConfigs
#undef eglChooseConfig
#undef eglGetConfigAttrib
#undef eglCreateWindowSurface
#undef eglCreatePbufferSurface
#undef eglCreatePixmapSurface
#undef eglDestroySurface
#undef eglQuerySurface
#undef eglBindAPI
#undef eglQueryAPI
#undef eglWaitClient
#undef eglReleaseThread
#undef eglCreatePbufferFromClientBuffer
#undef eglSurfaceAttrib
#undef eglBindTexImage
#undef eglReleaseTexImage
#undef eglSwapInterval
#undef eglCreateContext
#undef eglDestroyContext
#undef eglMakeCurrent
#undef eglGetCurrentContext
#undef eglGetCurrentSurface
#undef eglGetCurrentDisplay
#undef eglQueryContext
#undef eglWaitGL
#undef eglWaitNative
#undef eglSwapBuffers
#undef eglCopyBuffers
#undef eglGetProcAddress
#undef eglClientWaitSyncKHR
#undef eglCreateImageKHR
#undef eglCreateSyncKHR
#undef eglDestroyImageKHR
#undef eglDestroySyncKHR
#undef eglGetSyncAttribKHR
#undef eglGetSyncAttribKHR
#undef eglQueryProfilingDataNOK
#undef eglLockSurfaceKHR
#undef eglUnlockSurfaceKHR
#undef glEGLImageTargetRenderbufferStorageOES
#undef glEGLImageTargetTexture2DOES
#undef eglAcquireGlobalImageBRCM
#undef eglCreateCopyGlobalImageBRCM
#undef eglCreateGlobalImageBRCM
#undef eglReleaseGlobalImageBRCM
#undef eglInitGlobalImageBRCM
#undef eglTermGlobalImageBRCM
#undef eglImageUpdateParameterivBRCM
#undef eglImageUpdateParameteriBRCM
#undef eglGetPlatformDisplayEXT
#undef eglCreatePlatformWindowSurfaceEXT
#undef eglCreatePlatformPixmapSurfaceEXT
#undef eglBindWaylandDisplayWL
#undef eglUnbindWaylandDisplayWL
#undef eglQueryWaylandBufferWL

/* OpenGL ES 1.1 and 2.0 functions */

#undef glAlphaFunc
#undef glClearColor
#undef glClearDepthf
#undef glClipPlanef
#undef glColor4f
#undef glDepthRangef
#undef glFogf
#undef glFogfv
#undef glFrustumf
#undef glGetClipPlanef
#undef glGetFloatv
#undef glGetLightfv
#undef glGetMaterialfv
#undef glGetTexEnvfv
#undef glGetTexParameterfv
#undef glLightModelf
#undef glLightModelfv
#undef glLightf
#undef glLightfv
#undef glLineWidth
#undef glLoadMatrixf
#undef glMaterialf
#undef glMaterialfv
#undef glMultMatrixf
#undef glMultiTexCoord4f
#undef glNormal3f
#undef glOrthof
#undef glPointParameterf
#undef glPointParameterfv
#undef glPointSize
#undef glPolygonOffset
#undef glRotatef
#undef glScalef
#undef glTexEnvf
#undef glTexEnvfv
#undef glTexParameterf
#undef glTexParameterfv
#undef glTranslatef

#undef glActiveTexture
#undef glAlphaFuncx
#undef glBindBuffer
#undef glBindTexture
#undef glBlendFunc
#undef glBlendColor
#undef glBufferData
#undef glBlendEquation
#undef glBufferSubData
#undef glClear
#undef glClearColorx
#undef glClearDepthx
#undef glClearStencil
#undef glClientActiveTexture
#undef glClipPlanex
#undef glColor4ub
#undef glColor4x
#undef glColorMask
#undef glColorPointer
#undef glCompressedTexImage2D
#undef glCompressedTexSubImage2D
#undef glCopyTexImage2D
#undef glCopyTexSubImage2D
#undef glCullFace
#undef glDeleteBuffers
#undef glDeleteTextures
#undef glDepthFunc
#undef glDepthMask
#undef glDepthRangex
#undef glDisable
#undef glDisableClientState
#undef glDrawArrays
#undef glDrawElements
#undef glEnable
#undef glEnableClientState
#undef glFinish
#undef glFlush
#undef glFogx
#undef glFogxv
#undef glFrontFace
#undef glFrustumx
#undef glGetBooleanv
#undef glGetBufferParameteriv
#undef glGetClipPlanex
#undef glGenBuffers
#undef glGenTextures
#undef glGetError
#undef glGetFixedv
#undef glGetIntegerv
#undef glGetLightxv
#undef glGetMaterialxv
#undef glGetPointerv
#undef glGetString
#undef glGetTexEnviv
#undef glGetTexEnvxv
#undef glGetTexParameteriv
#undef glGetTexParameterxv
#undef glHint
#undef glIsBuffer
#undef glIsEnabled
#undef glIsTexture
#undef glLightModelx
#undef glLightModelxv
#undef glLightx
#undef glLightxv
#undef glLineWidthx
#undef glLoadIdentity
#undef glLoadMatrixx
#undef glLogicOp
#undef glMaterialx
#undef glMaterialxv
#undef glMatrixMode
#undef glMultMatrixx
#undef glMultiTexCoord4x
#undef glNormal3x
#undef glNormalPointer
#undef glOrthox
#undef glPixelStorei
#undef glPointParameterx
#undef glPointParameterxv
#undef glPointSizex
#undef glPolygonOffsetx
#undef glPopMatrix
#undef glPushMatrix
#undef glReadPixels
#undef glRotatex
#undef glSampleCoverage
#undef glSampleCoveragex
#undef glScalex
#undef glScissor
#undef glShadeModel
#undef glStencilFunc
#undef glStencilMask
#undef glStencilOp
#undef glTexCoordPointer
#undef glTexEnvi
#undef glTexEnvx
#undef glTexEnviv
#undef glTexEnvxv
#undef glTexImage2D
#undef glTexParameteri
#undef glTexParameterx
#undef glTexParameteriv
#undef glTexParameterxv
#undef glTexSubImage2D
#undef glTranslatex
#undef glVertexPointer
#undef glViewport

#undef glAttachShader
#undef glBindAttribLocation
#undef glBlendEquationSeparate
#undef glBlendFuncSeparate
#undef glCreateProgram
#undef glCreateShader
#undef glDeleteProgram
#undef glDeleteShader
#undef glDetachShader
#undef glDisableVertexAttribArray
#undef glEnableVertexAttribArray
#undef glGetActiveAttrib
#undef glGetActiveUniform
#undef glGetAttachedShaders
#undef glGetAttribLocation
#undef glGetProgramiv
#undef glGetProgramInfoLog
#undef glGetUniformfv
#undef glGetUniformiv
#undef glGetUniformLocation
#undef glGetVertexAttribfv
#undef glGetVertexAttribiv
#undef glGetVertexAttribPointerv
#undef glIsProgram
#undef glIsShader
#undef glLinkProgram
#undef glStencilFuncSeparate
#undef glStencilMaskSeparate
#undef glStencilOpSeparate
#undef glUniform1i
#undef glUniform2i
#undef glUniform3i
#undef glUniform4i
#undef glUniform1f
#undef glUniform2f
#undef glUniform3f
#undef glUniform4f
#undef glUniform1iv
#undef glUniform2iv
#undef glUniform3iv
#undef glUniform4iv
#undef glUniform1fv
#undef glUniform2fv
#undef glUniform3fv
#undef glUniform4fv
#undef glUniformMatrix2fv
#undef glUniformMatrix3fv
#undef glUniformMatrix4fv
#undef glUseProgram
#undef glValidateProgram
#undef glVertexAttrib1f
#undef glVertexAttrib2f
#undef glVertexAttrib3f
#undef glVertexAttrib4f
#undef glVertexAttrib1fv
#undef glVertexAttrib2fv
#undef glVertexAttrib3fv
#undef glVertexAttrib4fv
#undef glVertexAttribPointer
#undef glCompileShader
#undef glGetShaderiv
#undef glGetShaderInfoLog
#undef glGetShaderSource
#undef glReleaseShaderCompiler
#undef glShaderSource
#undef glShaderBinary
#undef glGetShaderPrecisionFormat
#undef glIsRenderbuffer
#undef glBindRenderbuffer
#undef glDeleteRenderbuffers
#undef glGenRenderbuffers
#undef glRenderbufferStorage
#undef glGetRenderbufferParameteriv
#undef glIsFramebuffer
#undef glBindFramebuffer
#undef glDeleteFramebuffers
#undef glGenFramebuffers
#undef glCheckFramebufferStatus
#undef glFramebufferTexture2D
#undef glFramebufferRenderbuffer
#undef glGetFramebufferAttachmentParameteriv
#undef glGenerateMipmap

#undef glRenderbufferStorageMultisampleEXT
#undef glFramebufferTexture2DMultisampleEXT

#undef glPointSizePointerOES
#undef glDiscardFramebufferEXT
#undef glInsertEventMarkerEXT
#undef glPushGroupMarkerEXT
#undef glPopGroupMarkerEXT

#undef glDrawTexfOES
#undef glDrawTexfvOES
#undef glDrawTexiOES
#undef glDrawTexivOES
#undef glDrawTexsOES
#undef glDrawTexsvOES
#undef glDrawTexxOES
#undef glDrawTexxvOES

#undef glIsRenderbufferOES
#undef glBindRenderbufferOES
#undef glDeleteRenderbuffersOES
#undef glGenRenderbuffersOES
#undef glRenderbufferStorageOES
#undef glGetRenderbufferParameterivOES
#undef glIsFramebufferOES
#undef glBindFramebufferOES
#undef glDeleteFramebuffersOES
#undef glGenFramebuffersOES
#undef glCheckFramebufferStatusOES
#undef glFramebufferRenderbufferOES
#undef glFramebufferTexture2DOES
#undef glGetFramebufferAttachmentParameterivOES
#undef glGenerateMipmapOES

#endif

#if defined KHRONOS_NAME_MANGLING || defined BCG_MULTI_THREADED

/* OpenVG functions */

#undef vgCreateEGLImageTargetKHR

#undef vgGetError
#undef vgFlush
#undef vgFinish
#undef vgSetf
#undef vgSeti
#undef vgSetfv
#undef vgSetiv
#undef vgGetf
#undef vgGeti
#undef vgGetVectorSize
#undef vgGetfv
#undef vgGetiv
#undef vgSetParameterf
#undef vgSetParameteri
#undef vgSetParameterfv
#undef vgSetParameteriv
#undef vgGetParameterf
#undef vgGetParameteri
#undef vgGetParameterVectorSize
#undef vgGetParameterfv
#undef vgGetParameteriv
#undef vgLoadIdentity
#undef vgLoadMatrix
#undef vgGetMatrix
#undef vgMultMatrix
#undef vgTranslate
#undef vgScale
#undef vgShear
#undef vgRotate
#undef vgMask
#undef vgRenderToMask
#undef vgCreateMaskLayer
#undef vgDestroyMaskLayer
#undef vgFillMaskLayer
#undef vgCopyMask
#undef vgClear
#undef vgCreatePath
#undef vgClearPath
#undef vgDestroyPath
#undef vgRemovePathCapabilities
#undef vgGetPathCapabilities
#undef vgAppendPath
#undef vgAppendPathData
#undef vgModifyPathCoords
#undef vgTransformPath
#undef vgInterpolatePath
#undef vgPathLength
#undef vgPointAlongPath
#undef vgPathBounds
#undef vgPathTransformedBounds
#undef vgDrawPath
#undef vgCreatePaint
#undef vgDestroyPaint
#undef vgSetPaint
#undef vgGetPaint
#undef vgSetColor
#undef vgGetColor
#undef vgPaintPattern
#undef vgCreateImage
#undef vgDestroyImage
#undef vgClearImage
#undef vgImageSubData
#undef vgGetImageSubData
#undef vgChildImage
#undef vgGetParent
#undef vgCopyImage
#undef vgDrawImage
#undef vgSetPixels
#undef vgWritePixels
#undef vgGetPixels
#undef vgReadPixels
#undef vgCopyPixels
#undef vgCreateFont
#undef vgDestroyFont
#undef vgSetGlyphToPath
#undef vgSetGlyphToImage
#undef vgClearGlyph
#undef vgDrawGlyph
#undef vgDrawGlyphs
#undef vgColorMatrix
#undef vgConvolve
#undef vgSeparableConvolve
#undef vgGaussianBlur
#undef vgLookup
#undef vgLookupSingle
#undef vgHardwareQuery
#undef vgGetString
#undef vgCreateEGLImageTargetKHR

#undef vguArc
#undef vguComputeWarpQuadToQuad
#undef vguComputeWarpQuadToSquare
#undef vguComputeWarpSquareToQuad
#undef vguEllipse
#undef vguLine
#undef vguPolygon
#undef vguRect
#undef vguRoundRect

#endif   //KHRONOS_NAME_MANGLING
#endif   //KHRONOS_MANGLED_H
