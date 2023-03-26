/*
 *  Common OpenGL loader, based on glad 0.1.36
 *  (https://glad.dav1d.de/#profile=compatibility&language=c&specification=gl&loader=on&api=gl%3D2.0)
 *
 *  Copyright (c) 2023, Hypatia of Sva <hypatia dot sva at posteo dot eu>
 *  SPDX-License-Identifier: MIT
*/

#include <cgl/cgl.h>


/* something about glClearDepthf, glDepthRangef.. */

#ifndef __cplusplus
#define nullptr NULL
#endif


PFNGLACTIVETEXTUREPROC glad_glActiveTexture = nullptr;
PFNGLATTACHSHADERPROC glad_glAttachShader = nullptr;
PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation = nullptr;
PFNGLBINDBUFFERPROC glad_glBindBuffer = nullptr;
PFNGLBINDTEXTUREPROC glad_glBindTexture = nullptr;
PFNGLBLENDCOLORPROC glad_glBlendColor = nullptr;
PFNGLBUFFERDATAPROC glad_glBufferData = nullptr;
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData = nullptr;
PFNGLBLENDEQUATIONPROC glad_glBlendEquation = nullptr;
PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate = nullptr;
PFNGLBLENDFUNCPROC glad_glBlendFunc = nullptr;
PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate = nullptr;
PFNGLCLEARPROC glad_glClear = nullptr;
PFNGLCLEARCOLORPROC glad_glClearColor = nullptr;
PFNGLCLEARDEPTHPROC glad_glClearDepth = nullptr;
PFNGLCLEARSTENCILPROC glad_glClearStencil = nullptr;
PFNGLCOLORMASKPROC glad_glColorMask = nullptr;
PFNGLCOMPILESHADERPROC glad_glCompileShader = nullptr;
PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D = nullptr;
PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D = nullptr;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = nullptr;
PFNGLCREATESHADERPROC glad_glCreateShader = nullptr;
PFNGLCULLFACEPROC glad_glCullFace = nullptr;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = nullptr;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = nullptr;
PFNGLDELETESHADERPROC glad_glDeleteShader = nullptr;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = nullptr;
PFNGLDEPTHFUNCPROC glad_glDepthFunc = nullptr;
PFNGLDEPTHMASKPROC glad_glDepthMask = nullptr;
PFNGLDEPTHRANGEPROC glad_glDepthRange = nullptr;
PFNGLDETACHSHADERPROC glad_glDetachShader = nullptr;
PFNGLDISABLEPROC glad_glDisable = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray = nullptr;
PFNGLDRAWARRAYSPROC glad_glDrawArrays = nullptr;
PFNGLDRAWELEMENTSPROC glad_glDrawElements = nullptr;
PFNGLENABLEPROC glad_glEnable = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = nullptr;
PFNGLFINISHPROC glad_glFinish = nullptr;
PFNGLFLUSHPROC glad_glFlush = nullptr;
PFNGLFRONTFACEPROC glad_glFrontFace = nullptr;
PFNGLGENBUFFERSPROC glad_glGenBuffers = nullptr;
PFNGLGENTEXTURESPROC glad_glGenTextures = nullptr;
PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib = nullptr;
PFNGLGETBOOLEANVPROC glad_glGetBooleanv = nullptr;
PFNGLGETFLOATVPROC glad_glGetFloatv = nullptr;
PFNGLGETINTEGERVPROC glad_glGetIntegerv = nullptr;





void cglLoadGL(GLADloadproc loader) {
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC) load("glActiveTexture");


}











