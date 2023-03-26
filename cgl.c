/*
 *  Common OpenGL loader, based on glad 0.1.36
 *  (https://glad.dav1d.de/#profile=compatibility&language=c&specification=gl&loader=on&api=gl%3D2.0)
 *
 *  Copyright (c) 2023, Hypatia of Sva <hypatia dot sva at posteo dot eu>
 *  SPDX-License-Identifier: MIT
*/

#include <cgl/cgl.h>


/* something about glClearDepthf, glDepthRangef.. */



PFNGLACTIVETEXTUREPROC glad_glActiveTexture = NULL;
/*
GLAPI PFNGLATTACHSHADERPROC glad_glAttachShader;
GLAPI PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;
GLAPI PFNGLBINDBUFFERPROC glad_glBindBuffer;
GLAPI PFNGLBINDTEXTUREPROC glad_glBindTexture;
GLAPI PFNGLBLENDCOLORPROC glad_glBlendColor;
GLAPI PFNGLBUFFERDATAPROC glad_glBufferData;
GLAPI PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
GLAPI PFNGLBLENDEQUATIONPROC glad_glBlendEquation;
GLAPI PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;
GLAPI PFNGLBLENDFUNCPROC glad_glBlendFunc;
GLAPI PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;
GLAPI PFNGLCLEARPROC glad_glClear;
GLAPI PFNGLCLEARCOLORPROC glad_glClearColor;
GLAPI PFNGLCLEARDEPTHPROC glad_glClearDepth;
GLAPI PFNGLCLEARSTENCILPROC glad_glClearStencil;
GLAPI PFNGLCOLORMASKPROC glad_glColorMask;
GLAPI PFNGLCOMPILESHADERPROC glad_glCompileShader;
GLAPI PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;
GLAPI PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;
GLAPI PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
GLAPI PFNGLCREATESHADERPROC glad_glCreateShader;
GLAPI PFNGLCULLFACEPROC glad_glCullFace;
GLAPI PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
GLAPI PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
GLAPI PFNGLDELETESHADERPROC glad_glDeleteShader;
GLAPI PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
GLAPI PFNGLDEPTHFUNCPROC glad_glDepthFunc;
GLAPI PFNGLDEPTHMASKPROC glad_glDepthMask;
GLAPI PFNGLDEPTHRANGEPROC glad_glDepthRange;
GLAPI PFNGLDETACHSHADERPROC glad_glDetachShader;
GLAPI PFNGLDISABLEPROC glad_glDisable;
GLAPI PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
GLAPI PFNGLDRAWARRAYSPROC glad_glDrawArrays;
GLAPI PFNGLDRAWELEMENTSPROC glad_glDrawElements;
GLAPI PFNGLENABLEPROC glad_glEnable;
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
GLAPI PFNGLFINISHPROC glad_glFinish;
GLAPI PFNGLFLUSHPROC glad_glFlush;
GLAPI PFNGLFRONTFACEPROC glad_glFrontFace;
GLAPI PFNGLGENBUFFERSPROC glad_glGenBuffers;
GLAPI PFNGLGENTEXTURESPROC glad_glGenTextures;
GLAPI PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib;
GLAPI PFNGLGETBOOLEANVPROC glad_glGetBooleanv;
GLAPI PFNGLGETFLOATVPROC glad_glGetFloatv;
GLAPI PFNGLGETINTEGERVPROC glad_glGetIntegerv;



*/



void cglLoadGL(GLADloadproc loader) {
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC) load("glActiveTexture");


}











