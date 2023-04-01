/*
 *  Common OpenGL header file, with loader based on glad 0.1.36
 *  (https://glad.dav1d.de/#profile=compatibility&language=c&specification=gl&loader=on&api=gl%3D2.0)
 *
 *  This loader loads the common subset of OpenGL 2.1, 4.5 core profile and GL ES 2.0, as described
 *  in the official reference documentation.
 *  The loader is modelled after glad.
 *
 *  Copyright (c) 2023, Hypatia of Sva <hypatia dot sva at posteo dot eu>
 *  SPDX-License-Identifier: MIT
*/


/* Explicit omissions:
 *
 * glCompressedTexImage2D, glCompressedTexSubImage2D
 *      since the only compressed formats allowed in GL ES 2.0 are extensions, hence
 *      are not a good fit for a "common" GL library.
 *      They are debatably part of the reference, but as reliant on extensions closer related
 *      to general functions like glEnable or glGet with non-standard values, since the enum
 *      values cannot be provided in a general portable manner, since there is no glGetEnumValue
 *      analogous to e.g. the alGetEnumValue in OpenAL.
 *
 *
 *
 *
 * Unclear cases:
 * glClearDepthf, glDepthRangef - as a macro, really? Or rather as a static wrapper function?
 * Or maybe even as an extern, that's defined in the implementation / function loader file?
 *
 * glEnableVertexAttribArray, glDisableVertexAttribArray: why does it need VAOs? is this an incompatibility
 * to GL 2.1 / GL ES 2.0?
 *
 *
 */


#ifndef CGLAD_H
#define CGLAD_H

#ifdef __gl_h_
#error OpenGL header already included, remove this include, the cgl header already provides it
#endif
#define __gl_h_

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#define APIENTRY __stdcall
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef GLAPIENTRY
#define GLAPIENTRY APIENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* fixed from glad: ISO C90 forbids cast from function to data pointer,
 * hence GLADproc, not void*, as return type of the function loader
 */
typedef void     (* GLADproc)(void);
typedef GLADproc (* GLADloadproc)(const char *name);

#ifndef GLAPI
# if defined(GLAD_GLAPI_EXPORT)
#  if defined(_WIN32) || defined(__CYGWIN__)
#   if defined(GLAD_GLAPI_EXPORT_BUILD)
#    if defined(__GNUC__)
#     define GLAPI __attribute__ ((dllexport)) extern
#    else
#     define GLAPI __declspec(dllexport) extern
#    endif
#   else
#    if defined(__GNUC__)
#     define GLAPI __attribute__ ((dllimport)) extern
#    else
#     define GLAPI __declspec(dllimport) extern
#    endif
#   endif
#  elif defined(__GNUC__) && defined(GLAD_GLAPI_EXPORT_BUILD)
#   define GLAPI __attribute__ ((visibility ("default"))) extern
#  else
#   define GLAPI extern
#  endif
# else
#  define GLAPI extern
# endif
#endif

/*! \brief loads the GL functions
 * this is the whole interface to cglad - since it only loads one version,
 * there is no necessity for a version struct or other options.
 * It only loads by a loader function, so e.g. one typically supplied by SDL or GLFW,
 * but if you need something more specific, load the DLL yourself and supply a loader function
 * for that.
 *
 * also, there is no return value since this is common GL, so the version information must
 * not be explicitly made clear, and, if something fails, the pointers will be NULL anyway,
 * so that's easy to check for the library user, and must be done regardless in case of loader
 * error / bugs.
 *
 * \param loader loader function that returns the function pointer
 */
GLAPI void cglLoadGL(GLADloadproc loader);


/* only those types that are actually used, also reduced from the khrplatform.h layer */
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef unsigned char GLubyte;
typedef int GLint;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef double GLdouble;
typedef char GLchar;
#if defined(_WIN64)
typedef signed   long long int GLsizeiptr;
#else
typedef signed   long  int     GLsizeiptr;
#endif
/* this is the only significant portion left from khrplatform.h: */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#if defined(__SIZEOF_LONG__) && defined(__SIZEOF_POINTER__)
#if __SIZEOF_POINTER__ > __SIZEOF_LONG__
#define CGLAD_USE_INTPTR_T
#endif
#endif
#endif
#ifdef CGLAD_USE_INTPTR_T
typedef intptr_t       GLintptr;
#else
typedef GLsizeiptr     GLintptr;
#endif




#define GL_FALSE 0
#define GL_TRUE 1

#define GL_NO_ERROR 0
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_VALUE 0x0501
#define GL_INVALID_OPERATION 0x0502
#define GL_OUT_OF_MEMORY 0x0505

#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
/* = GL_TEXTUREi = GL_TEXTURE0 + i
 maybe only have GL_TEXTURE0 as a fixed constant then? */


#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_MAX_VERTEX_ATTRIBS 0x8869

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_CUBE_MAP 0x8513

#define GL_FUNC_ADD 0x8006
#define GL_FUNC_REVERSE_SUBTRACT 0x800B
#define GL_FUNC_SUBTRACT 0x800A

#define GL_ZERO 0
#define GL_ONE 1
#define GL_SRC_COLOR 0x0300
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_DST_ALPHA 0x0304
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_DST_COLOR 0x0306
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_SRC_ALPHA_SATURATE 0x0308
#define GL_CONSTANT_COLOR 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#define GL_CONSTANT_ALPHA 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004

#define GL_STREAM_DRAW 0x88E0
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8

#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT 0x00004000

#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A

#define GL_RGB 0x1907
#define GL_RGBA 0x1908

#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31

#define GL_FRONT 0x0404
#define GL_BACK 0x0405
#define GL_FRONT_AND_BACK 0x0408

#define GL_NEVER 0x0200
#define GL_LESS 0x0201
#define GL_EQUAL 0x0202
#define GL_LEQUAL 0x0203
#define GL_GREATER 0x0204
#define GL_NOTEQUAL 0x0205
#define GL_GEQUAL 0x0206
#define GL_ALWAYS 0x0207

#define GL_BLEND 0x0BE2
#define GL_CULL_FACE 0x0B44
#define GL_DEPTH_TEST 0x0B71
#define GL_DITHER 0x0BD0
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#define GL_SAMPLE_COVERAGE 0x80A0
#define GL_SCISSOR_TEST 0x0C11
#define GL_STENCIL_TEST 0x0B90

#define GL_POINTS 0x0000
#define GL_LINES 0x0001
#define GL_LINE_LOOP 0x0002
#define GL_LINE_STRIP 0x0003
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN 0x0006

#define GL_UNSIGNED_BYTE 0x1401
#define GL_UNSIGNED_SHORT 0x1403

#define GL_CW 0x0900
#define GL_CCW 0x0901

#define GL_ACTIVE_TEXTURE 0x84E0
#define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#define GL_ARRAY_BUFFER_BINDING 0x8894
#define GL_BLEND_COLOR 0x8005
#define GL_BLEND_DST_RGB 0x80C8
#define GL_BLEND_SRC_RGB 0x80C9
#define GL_BLEND_DST_ALPHA 0x80CA
#define GL_BLEND_SRC_ALPHA 0x80CB
#define GL_BLEND_EQUATION_RGB 0x8009
#define GL_BLEND_EQUATION_ALPHA 0x883D
#define GL_COLOR_CLEAR_VALUE 0x0C22
#define GL_COLOR_WRITEMASK 0x0C23
#define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#define GL_CULL_FACE_MODE 0x0B45
#define GL_CURRENT_PROGRAM 0x8B8D
#define GL_DEPTH_CLEAR_VALUE 0x0B73
#define GL_DEPTH_FUNC 0x0B74
#define GL_DEPTH_RANGE 0x0B70
#define GL_DEPTH_WRITEMASK 0x0B72
#define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#define GL_LINE_WIDTH 0x0B21
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851C
#define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_MAX_VERTEX_ATTRIBS 0x8869
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_VIEWPORT_DIMS 0x0D3A
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_PACK_ALIGNMENT 0x0D05
#define GL_POLYGON_OFFSET_FACTOR 0x8038
#define GL_POLYGON_OFFSET_UNITS 0x2A00
#define GL_SAMPLE_BUFFERS 0x80A8
#define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#define GL_SAMPLES 0x80A9
#define GL_SCISSOR_BOX 0x0C10
#define GL_STENCIL_BACK_FAIL 0x8801
#define GL_STENCIL_BACK_FUNC 0x8800
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#define GL_STENCIL_BACK_REF 0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK 0x8CA4
#define GL_STENCIL_BACK_WRITEMASK 0x8CA5
#define GL_STENCIL_CLEAR_VALUE 0x0B91
#define GL_STENCIL_FAIL 0x0B94
#define GL_STENCIL_FUNC 0x0B92
#define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#define GL_STENCIL_REF 0x0B97
#define GL_STENCIL_VALUE_MASK 0x0B93
#define GL_STENCIL_WRITEMASK 0x0B98
#define GL_SUBPIXEL_BITS 0x0D50
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_VIEWPORT 0x0BA2

#define GL_FLOAT 0x1406
#define GL_FLOAT_VEC2 0x8B50
#define GL_FLOAT_VEC3 0x8B51
#define GL_FLOAT_VEC4 0x8B52
#define GL_FLOAT_MAT2 0x8B5A
#define GL_FLOAT_MAT3 0x8B5B
#define GL_FLOAT_MAT4 0x8B5C



/*! \defgroup general General Utilities
 *  \brief general purpose functions and utilities
 *
 * general purpose functionality to get information, finish or flush,
 * clear current data, enable or disable features etc.
 */
/*! \defgroup framebuffer Framebuffer
 * \brief general framebuffer operations
 *
 * functions operating on the whole frame buffer, such as clearing the screen
 * or locking it from writing.
 */
/*! \defgroup buffer Buffers
 * \brief buffer object and target functions
 *
 * Functions that refer to buffer objects, their binding and use in different targets.
 */
/*! \defgroup texture Textures
 * \brief texture object and target functions
 *
 * Functions that refer to texture objects, their binding and use in different targets.
 */
/*! \defgroup shader Shaders and Programs
 * \brief shader objects and programs composed of them
 *
 * Functions that create and use shader programs, that is program objects linked together
 * from shader objects holding executables compiled from GLSL source code.
 */
/*! \defgroup postprocessing Postprocessing
 * \brief post-processing functions (blending, stencil ops etc.)
 *
 * Functions that create post processing operations like blending, stenceling,
 * depth tests, culling, scissoring etc.
 */



/*! \brief enable or disable server-side GL capabilities
 *
 * enables or disables certain features usually not enabled. only GL_DITHER is on by default:
 *  GL_BLEND                    blend incoming with old colors, see glBlendFunc
 *  GL_CULL_FACE                cull polygons based on winding direction, see glCullFace
 *  GL_DEPTH_TEST               do depth tests and update the depth buffer. See glDepthFunc/glDepthRange[f]
 *  GL_DITHER                   dither color components or indices before writing them in the color buffer
 *  GL_POLYGON_OFFSET_FILL      add an offset to filled polygons, see glPolygonOffset
 *  GL_SAMPLE_ALPHA_TO_COVERAGE take the alpha value at a sample location and &= it to the coverage value
 *  GL_SAMPLE_COVERAGE          calculate a temp. coverage value and &= or ~ &= it in. See glSampleCoverage
 *  GL_SCISSOR_TEST             discard fragments that are outside the scissor rectangle. See glScissor
 *  GL_STENCIL_TEST             stencil testing, update the stencil buffer. See glStencilFunc/glStencilOp
 *
 * \param cap the capability to enable/disable, must be GL_BLEND, GL_CULL_FACE, GL_DEPTH_TEST, GL_DITHER,
 *                          GL_POLYGON_OFFSET_FILL, GL_SAMPLE_ALPHA_TO_COVERAGE, GL_SAMPLE_COVERAGE,
 *                          GL_SCISSOR_TEST or GL_STENCIL_TEST
 *
 * \errors GL_INVALID_ENUM if \ref cap is not one of the accepted values
 *
 * \ingroup general
 */
typedef void (APIENTRYP PFNGLDISABLEPROC)(GLenum cap);
GLAPI PFNGLDISABLEPROC glad_glDisable;
#define glDisable glad_glDisable
typedef void (APIENTRYP PFNGLENABLEPROC)(GLenum cap);
GLAPI PFNGLENABLEPROC glad_glEnable;
#define glEnable glad_glEnable

/*! \brief block until all GL execution is complete
 *
 * wait until all previous GL commands are completed
 * this can take an undetermined amount of time
 *
 * \errors none
 *
 * \ingroup general
 */
typedef void (APIENTRYP PFNGLFINISHPROC)(void);
GLAPI PFNGLFINISHPROC glad_glFinish;
#define glFinish glad_glFinish

/*! \brief force execution of GL commands in finite time
 *
 * empty the various command buffers.
 * this _should_ be done, according to the reference, whenever the application expects the issued commands
 * to be done, like when waiting for user input, i.e. at the end of the rendering function.
 * However, glFlush can return immediately. It does not wait for the other commands to be done,
 * it merely issues that they _should_ be done about now.
 *
 * \errors none
 *
 * \ingroup general
 */
typedef void (APIENTRYP PFNGLFLUSHPROC)(void);
GLAPI PFNGLFLUSHPROC glad_glFlush;
#define glFlush glad_glFlush


/*! \brief return the value or values of a selected parameter
 *
 * reads bool, int and float values. casts them as:
 *      bool to int, float: keep GL_TRUE or GL_FALSE
 *      int, float to bool: return (value != 0) or (value != 0.0)
 *      int to float: standard casting
 *      float to int: normally round to nearest;
 *          but colors and normals map from [-1.0,1.0] to [MININT, MAXINT] in a linear mapping
 * the following values are univerally readable:
 * (the ones marked with + are not (directly) set by user operation, like glEnable or other)
 * GL_ACTIVE_TEXTURE                    active texture unit, default GL_TEXTURE0 (glActiveTexture)
 *+GL_ALIASED_LINE_WIDTH_RANGE          2 values: smallest and largest line width (glLineWidth)
 * GL_ARRAY_BUFFER_BINDING              buffer name currently bound to GL_ARRAY_BUFFER, or 0 (glBindBuffer)
 * GL_BLEND                             boolean if blending is enabled, default GL_FALSE (glBlendFunc)
 * GL_BLEND_COLOR                       4 values: blend color components (glBlendColor)
 * GL_BLEND_DST_ALPHA                   alpha-destination blend func, default GL_ZERO (glBlendFuncSeparate)
 * GL_BLEND_DST_RGB                     rgb-destination blend func, Default GL_ZERO (glBlendFuncSeparate)
 * GL_BLEND_EQUATION_ALPHA              alpha blend equation (glBlendEquationSeparate)
 * GL_BLEND_EQUATION_RGB                rgb blend equation (glBlendEquationSeparate)
 * GL_BLEND_SRC_ALPHA                   alpha-source blend func, default GL_ONE (glBlendFuncSeparate)
 * GL_BLEND_SRC_RGB                     rgb-source blend func, default GL_ONE (glBlendFuncSeparate)
 * GL_COLOR_CLEAR_VALUE                 4 values: clear color components (glClearColor)
 * GL_COLOR_WRITEMASK                   4 bools: color component masks (glColorMask)
 *+GL_COMPRESSED_TEXTURE_FORMATS        GL_NUM_COMPRESSED_TEXTURE_FORMATS values:
 *                                        enum values describing available formats (glCompressedTexImage2D)
 * GL_CULL_FACE                         boolean if culling is enabled, default GL_FALSE (glCullFace)
 * GL_CULL_FACE_MODE                    enum, which faces should be culled, default GL_BACK (glCullFace)
 * GL_CURRENT_PROGRAM                   currently active program name, or 0 (glUseProgram)
 * GL_DEPTH_CLEAR_VALUE                 depth buffer clear value, default 1 (glClearDepth[f])
 * GL_DEPTH_FUNC                        depth function, default GL_LESS (glDepthFunc)
 * GL_DEPTH_RANGE                       2 values: near/far mappings for depth buffer (glDepthRange[f])
 * GL_DEPTH_TEST                        boolean if depth testing is enabled, default GL_FALSE (glDepthFunc)
 * GL_DEPTH_WRITEMASK                   bool: depth mask value, default GL_TRUE (glDepthMask)
 * GL_DITHER                            boolean if dithering is enabled, default GL_TRUE
 * GL_ELEMENT_ARRAY_BUFFER_BINDING      buffer name bound to GL_ELEMENT_ARRAY_BUFFER, or 0 (glBindBuffer)
 * GL_LINE_WIDTH                        specified line width, default 1 (glLineWidth)
 *+GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS  nr of tex.-units usable by fragment+vertex shader (glActiveTexture)
 *+GL_MAX_CUBE_MAP_TEXTURE_SIZE         estimate of the largest supported cube-map texture (glTexImage2D)
 *+GL_MAX_TEXTURE_IMAGE_UNITS           nr of texture units usable by the fragment shader (glActiveTexture)
 *+GL_MAX_TEXTURE_SIZE                  estimate of the largest supported texture (glTexImage2D)
 *+GL_MAX_VERTEX_ATTRIBS                nr of vec4-attribs usable by the vertex shader (glVertexAttrib)
 *+GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS    nr of texture units usable by the vertex shader (glActiveTexture)
 *+GL_MAX_VIEWPORT_DIMS                 2 values: maximum width and height of viewport (glViewport)
 *+GL_NUM_COMPRESSED_TEXTURE_FORMATS    number of compressed formats, can be 0 (glCompressedTexImage2D)
 * GL_PACK_ALIGNMENT                    alignment for writing pixels to memory, default 4 (glPixelStore[i])
 * GL_POLYGON_OFFSET_FACTOR             scaling factor to calculate offset, default 0 (glPolygonOffset)
 * GL_POLYGON_OFFSET_FILL               boolean, if offset is enabled, default GL_FALSE (glPolygonOffset)
 * GL_POLYGON_OFFSET_UNITS              offset nr of units added, default 0 (glPolygonOffset)
 *+GL_SAMPLE_BUFFERS                    nr of sample buffers of the frame buffer (glSampleCoverage)
 * GL_SAMPLE_COVERAGE_INVERT            bool, if coverage is set to be inverted (glSampleCoverage)
 * GL_SAMPLE_COVERAGE_VALUE             current sample coverage value (glSampleCoverage)
 *+GL_SAMPLES                           int of the coverage mask size of the framebuffer (glSampleCoverage)
 * GL_SCISSOR_BOX                       4 values: x, y, width and height of scissor box (glScissor)
 * GL_SCISSOR_TEST                      boolean is scissoring is enabled, default GL_FALSE (glScissor)
 * GL_STENCIL_BACK_FAIL                 action sfail for GL_BACK (glStencilOpSeparate)
 * GL_STENCIL_BACK_FUNC                 function for stenctil test for GL_BACK (glStencilFuncSeparate)
 * GL_STENCIL_BACK_PASS_DEPTH_FAIL      action dpfail for GL_BACK (glStencilOpSeparate)
 * GL_STENCIL_BACK_PASS_DEPTH_PASS      action dppass for GL_BACK (glStencilOpSeparate)
 * GL_STENCIL_BACK_REF                  ref value for stencil test for GL_BACK (glStencilFuncSeparate)
 * GL_STENCIL_BACK_VALUE_MASK           value mask for stenctil test for GL_BACK (glStencilFuncSeparate)
 * GL_STENCIL_BACK_WRITEMASK            bit mask for stencil testing for GL_BACK (glStencilMaskSeparate)
 * GL_STENCIL_CLEAR_VALUE               stencil clear value, default 0 (glClearStencil)
 * GL_STENCIL_FAIL                      action sfail for GL_FRONT (glStencilOpSeparate)
 * GL_STENCIL_FUNC                      function for stenctil test for GL_FRONT (glStencilFuncSeparate)
 * GL_STENCIL_PASS_DEPTH_FAIL           action dpfail for GL_FRONT (glStencilOpSeparate)
 * GL_STENCIL_PASS_DEPTH_PASS           action dppass for GL_FRONT (glStencilOpSeparate)
 * GL_STENCIL_REF                       ref value for stencil test for GL_FRONT (glStencilFuncSeparate)
 * GL_STENCIL_TEST                      boolean if stenciling is enabled, default GL_FALSE (glStencilOp)
 * GL_STENCIL_VALUE_MASK                value mask for stenctil test for GL_FRONT (glStencilFuncSeparate)
 * GL_STENCIL_WRITEMASK                 bit mask for stencil testing for GL_FRONT (glStencilMaskSeparate)
 *+GL_SUBPIXEL_BITS                     estimated number of bits of subpixel resolution, at least 4
 * GL_TEXTURE_BINDING_2D                texture name currently bound to GL_TEXTURE_2D, or 0 (glBindTexture)
 * GL_TEXTURE_BINDING_CUBE_MAP          texture name bound to GL_TEXTURE_CUBE_MAP, or 0 (glBindTexture)
 * GL_UNPACK_ALIGNMENT                  alignment for reading pixels, default 4 (glPixelStore[i])
 * GL_VIEWPORT                          4 values: x, y, width and height of the viewport (glViewport)
 *
 * so the only values not also set by the user are:
 *  GL_ALIASED_LINE_WIDTH_RANGE, GL_COMPRESSED_TEXTURE_FORMATS, GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
 *  GL_MAX_CUBE_MAP_TEXTURE_SIZE, GL_MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_SIZE, GL_MAX_VERTEX_ATTRIBS,
 *  GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, GL_MAX_VIEWPORT_DIMS, GL_NUM_COMPRESSED_TEXTURE_FORMATS,
 *  GL_SAMPLE_BUFFERS, GL_SAMPLES, GL_SUBPIXEL_BITS
 * the others are more there to keep track of what you already have done.
 *
 * \param pname parameter value to be returned, one out of the table above
 * \param data returns value or values of the specified parameter by writing into the pointer
 *
 * \errors GL_INVALID_ENUM if \ref pname is not an accepted value
 *
 * \ingroup general
 */
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean *data);
GLAPI PFNGLGETBOOLEANVPROC glad_glGetBooleanv;
#define glGetBooleanv glad_glGetBooleanv
typedef void (APIENTRYP PFNGLGETFLOATVPROC)(GLenum pname, GLfloat *data);
GLAPI PFNGLGETFLOATVPROC glad_glGetFloatv;
#define glGetFloatv glad_glGetFloatv
typedef void (APIENTRYP PFNGLGETINTEGERVPROC)(GLenum pname, GLint *data);
GLAPI PFNGLGETINTEGERVPROC glad_glGetIntegerv;
#define glGetIntegerv glad_glGetIntegerv



/*! \brief render primitives from array data
 *
 * draws multiple primitives, starting from the index \ref first exactly \ref count elements long.
 * it uses all enabled arrarys, GL ES 2.0 references glEnableVertexAttribArray aligned
 * glVertexAttribPointer explicitly for that, GL 2 and 4 don't (probably because of methods not in CGL).
 *
 * (GL 2.1 says that GL_VERTEX_ARRAY needs to be enabled, but does not list it in glEnable)
 *
 * If vertex attributes get modified, they're undefined, otherwise they will stay the same.
 * If no shader is active, this produces undefined results in GL ES 2.0, but without throwing
 *
 * \param mode kind of primitive to render, must be GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
 *                  GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, or GL_TRIANGLES
 * \param first starting index in the enabled arrays
 * \param count number of indices to be rendered
 *
 * \errors GL_INVALID_ENUM      if \ref mode is not an accepted value
 *         GL_INVALID_VALUE     if \ref count < 0
 *         GL_INVALID_OPERATION (only when doing buffer mapping or geometry shading, both not in CGL)
 *         GL_INVALID_FRAMEBUFFER_OPERATION (also only by GL ES 2.0, and not achievable in CGL)
 *
 * \ingroup framebuffer
 */
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
GLAPI PFNGLDRAWARRAYSPROC glad_glDrawArrays;
#define glDrawArrays glad_glDrawArrays

/*! \brief render primitives from array data
 *
 * like glDrawArrays, but specifies a pointer to an index array instead of an starting index.
 * Also can use multiple arrays, also references glE and glVertexAttribPointer.
 *
 * (GL 2.1 says that GL_VERTEX_ARRAY needs to be enabled, but does not list it in glEnable)
 *
 * If vertex attributes get modified, they're undefined, otherwise they will stay the same.
 * If no shader is active, this produces undefined results in GL ES 2.0, but without throwing
 *
 * \param mode kind of primitive to render, must be GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
 *                  GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, or GL_TRIANGLES
 * \param count number of elements to be rendered
 * \param type type of values in \ref indices, must be GL_UNSIGNED_BYTE or GL_UNSIGNED_SHORT
 * \param indices pointer to the location where the indices are stored
 *
 * \errors GL_INVALID_ENUM      if \ref mode or \ref type is not an accepted value
 *         GL_INVALID_VALUE     if \ref count < 0
 *         GL_INVALID_OPERATION (only when doing buffer mapping or geometry shading, both not in CGL)
 *         GL_INVALID_FRAMEBUFFER_OPERATION (also only by GL ES 2.0, and not achievable in CGL)
 *
 * \ingroup framebuffer
 */
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices);
GLAPI PFNGLDRAWELEMENTSPROC glad_glDrawElements;
#define glDrawElements glad_glDrawElements








/*! \defgroup clearing clears the frame buffer
 *
 * clearing colors, depth and stencil data in parts of the frame buffer
 * \ingroup framebuffer
 * \{
 */

/*! \brief clear buffers to preset values
 *
 * fills color, depth and stencil buffers with constant values
 * fills within the scissor box, and is affected by pixel ownership test, dithering and write mask,
 * but not by blending, stenceling, depth-buffering and shading.
 *
 * can clear any combination of the three buffers, as indicated by a bitwise or of the flag bits.
 *
 * \param mask Bitwise OR of masks GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, or GL_STENCIL_BUFFER_BIT
 *
 * \errors GL_INVALID_VALUE if other bits in \param mask are set than the three allowed.
 */
typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield mask);
GLAPI PFNGLCLEARPROC glad_glClear;
#define glClear glad_glClear

/*! \brief specify clear values for the color buffers
 *
 * Set the constant value GL_COLOR_CLEAR_VALUE for glClear with GL_COLOR_BUFFER_BIT
 * Default value is (0,0,0,0).
 *
 * \param red   red   component of GL_COLOR_CLEAR_VALUE, clamped to [0,1]
 * \param green green component of GL_COLOR_CLEAR_VALUE, clamped to [0,1]
 * \param blue  blue  component of GL_COLOR_CLEAR_VALUE, clamped to [0,1]
 * \param alpha alpha component of GL_COLOR_CLEAR_VALUE, clamped to [0,1]
 *
 * \errors none
 */
typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI PFNGLCLEARCOLORPROC glad_glClearColor;
#define glClearColor glad_glClearColor

/*! \brief specify the clear value for the depth buffer
 *
 * Set the constant value GL_DEPTH_CLEAR_VALUE for glClear with GL_DEPTH_BUFFER_BIT
 * Note: this function does not in exist in GL ES 2.0, instead being replaced with
 * glClearDepthf! This means, that any value passed in here should fit in a float for compatibility.
 * Since this is a widening, not a narrowing cast, glClearDepthf is defined as an alias to glClearDepth,
 * if not otherwise available
 *
 * \param depth depth value used when the depth buffer is cleared
 *
 * \errors none
 */
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC)(GLdouble depth);
GLAPI PFNGLCLEARDEPTHPROC glad_glClearDepth;
#define glClearDepth glad_glClearDepth
/* ??? */
#define glClearDepthf glad_glClearDepth

/*! \brief specify the clear value for the stencil buffer
 *
 * Set the constant value GL_STENCIL_CLEAR_VALUE for glClear with GL_STENCIL_BUFFER_BIT
 * Will be masked to the size of the stencil bits (i.e. the effecive value is (s & (1<<GL_STENCIL_BITS -1)))
 * Default value is 0.
 *
 * \param s index used when the stencil buffer is cleared
 *
 * \errors none
 */
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC)(GLint s);
GLAPI PFNGLCLEARSTENCILPROC glad_glClearStencil;
#define glClearStencil glad_glClearStencil

/*! \} */





/*! \defgroup masking masking buffers of the frame buffer
 *
 * making certain buffers in the frame buffer, as the color, depth and stencil buffer, read only.
 * \ingroup framebuffer
 * \{
 */

/*! \brief enable and disable writing of frame buffer color components
 *
 * sets if the RGBA components of the frame buffer can be written to or not (on color, not bit level)
 * Default values are all GL_TRUE
 *
 * \param red   sets if the red   component of the color buffer can be written to (GL_TRUE or GL_FALSE)
 * \param green sets if the green component of the color buffer can be written to (GL_TRUE or GL_FALSE)
 * \param blue  sets if the blue  component of the color buffer can be written to (GL_TRUE or GL_FALSE)
 * \param alpha sets if the alpha component of the color buffer can be written to (GL_TRUE or GL_FALSE)
 *
 * \errors none
 */
typedef void (APIENTRYP PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GLAPI PFNGLCOLORMASKPROC glad_glColorMask;
#define glColorMask glad_glColorMask

/*! \brief enable and disable writing of the frame buffers depth buffer
 *
 * sets if the depth buffer of the frame buffer can be written to or not
 * Default value is GL_TRUE (However, it has no effect without activating GL_DEPTH_TEST, see glDepthFunc)
 *
 * \param flag   sets if the depth buffer can be written to (GL_TRUE or GL_FALSE)
 *
 * \errors none
 */
typedef void (APIENTRYP PFNGLDEPTHMASKPROC)(GLboolean flag);
GLAPI PFNGLDEPTHMASKPROC glad_glDepthMask;
#define glDepthMask glad_glDepthMask

/*! \} */













/*! \defgroup blending color blending
 *
 * color blending operations of incoming onto old colors in the frame buffer
 * \ingroup postprocessing
 * \{
 */

/*! \brief set the blend color
 * Sets the parameter GL_BLEND_COLOR for use in blending functions,
 * see glBlendFunc for detailed usage. The default value is (0, 0, 0, 0).
 * All values are clamped to the range [0, 1] before being stored.
 *
 * \param red   red   component of GL_BLEND_COLOR, gets clamped to [0,1]
 * \param green green component of GL_BLEND_COLOR, gets clamped to [0,1]
 * \param blue  blue  component of GL_BLEND_COLOR, gets clamped to [0,1]
 * \param alpha alpha component of GL_BLEND_COLOR, gets clamped to [0,1]
 *
 * \errors none
 */
typedef void (APIENTRYP PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI PFNGLBLENDCOLORPROC glad_glBlendColor;
#define glBlendColor glad_glBlendColor

/*! \brief specify the equation used for both the RGB blend equation and the Alpha blend equation
 *
 * At the blending stage, first the blend factors for the existing color in the pixel ("destination")
 * and the new color coming from the fragment shader ("source") get attached factors, see glBendFunc,
 * and the RGBA values are then muliplied by those factors. However, they still must be combined. There
 * are three options:
 *      GL_FUNC_ADD                 new_color = source + destination
 *      GL_FUNC_SUBTRACT            new_color = source - destination
 *      GL_FUNC_REVERSE_SUBTRACT    new_color = destination - source
 *  where "source" and "destination" are, for example, source.r * source_factor.r (red component)
 *  _After adding_ the result is clamped to [0,1] (not after multiplying source*source_factor etc.!)
 * glBlendEquation sets this equation for both RGB and A. See glBlendEquationSeparate for details
 * Default value is GL_FUNC_ADD
 *
 * \param mode how source and destination colors are combined
 *              must be GL_FUNC_ADD, GL_FUNC_SUBTRACT or GL_FUNC_REVERSE_SUBTRACT
 *
 * \errors GL_INVALID_ENUM if \ref mode is not GL_FUNC_ADD, GL_FUNC_SUBTRACT or GL_FUNC_REVERSE_SUBTRACT
 */
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC)(GLenum mode);
GLAPI PFNGLBLENDEQUATIONPROC glad_glBlendEquation;
#define glBlendEquation glad_glBlendEquation

/*! \brief set the RGB blend equation and the alpha blend equation separately
 *
 * Like glBlendEquation, but you can set different equations for RGB and Alpha blending.
 * See glBlendEquation for details.
 *
 * \param modeRGB RGB blend equation. must be GL_FUNC_ADD, GL_FUNC_SUBTRACT or GL_FUNC_REVERSE_SUBTRACT
 * \param modeAlpha alpha blend equation. must be GL_FUNC_ADD, GL_FUNC_SUBTRACT or GL_FUNC_REVERSE_SUBTRACT
 *
 * \errors GL_INVALID_ENUM if \ref modeRGB or \ref modeAlpha aren't
 *                              GL_FUNC_ADD, GL_FUNC_SUBTRACT or GL_FUNC_REVERSE_SUBTRACT
 */
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
GLAPI PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;
#define glBlendEquationSeparate glad_glBlendEquationSeparate

/*! \brief specify pixel arithmetic
 *
 * defines the blend factors to be used in the blend equation.
 * glBlendFunc sets these for both RGB and A. See glBlendFuncSeparate for details
 * factors can be set for the scaling of the new color through \ref sfactor and
 * the old color through \ref dfactor with the follwing parameters:
 *          enum value              color scale factor for color c (can stand in for r, g, b, a)
 *          GL_ZERO                         0
 *          GL_ONE                          1
 *          GL_SRC_COLOR                    source.c/csize
 *          GL_ONE_MINUS_SRC_COLOR          1 - source.c/csize
 *          GL_DST_COLOR                    destination.c/csize
 *          GL_ONE_MINUS_DST_COLOR          1 - destination.c/csize
 *          GL_SRC_ALPHA                    source.alpha/alphasize
 *          GL_ONE_MINUS_SRC_ALPHA          1 - source.alpha/alphasize
 *          GL_DST_ALPHA                    destination.alpha/alphasize
 *          GL_ONE_MINUS_DST_ALPHA          1 - destination.alpha/alphasize
 *          GL_CONSTANT_COLOR               GL_BLEND_COLOR.c
 *          GL_ONE_MINUS_CONSTANT_COLOR     1 - GL_BLEND_COLOR.c
 *          GL_CONSTANT_ALPHA               GL_BLEND_COLOR.alphs
 *          GL_ONE_MINUS_CONSTANT_ALPHA     1 - GL_BLEND_COLOR.alphs
 *      where alphsize, .alpha refers to the a-component of RGBA (but can set it for other
 *      components as well), and csize = 2^(m_c)-1, where m_c is the number of c-bitplanes
 * For the new color (the "source") there is an additional option:
 *      GL_SRC_ALPHA_SATURATE      set alpha factor = 1, and set all color component factors to
 *                                      min(source.alpha, alphasize - destination.alpha)/alphasize
 * Important: GL does not guarantee accuracy for all those calculations, including the multiplication
 * of these factors with destination and source color values. However, if the equation symbolically
 * reduces to factors equal to 1 or 0, then it is guaranteed that the colors aren't changed / are set to 0,
 * and that no inaccuracies take place there.
 *
 * The default values are: GL_ONE for the source and GL_ZERO for the destination (= overriding old colors)
 *
 * \param sfactor how the source blending factors are computed. Must be one of
 *                  GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
 *                  GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
 *                  GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR,
 *                  GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA, GL_SRC_ALPHA_SATURATE
 *
 * \param dfactor how the destination blending factors are computed. Must be one of
 *                  GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
 *                  GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
 *                  GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR,
 *                  GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA.
 *
 * \errors GL_INVALID_ENUM if \ref sfactor or \ref dfactor are not from the list, or
 *                              GL_SRC_ALPHA_SATURATE is used for the destination
 */
typedef void (APIENTRYP PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
GLAPI PFNGLBLENDFUNCPROC glad_glBlendFunc;
#define glBlendFunc glad_glBlendFunc

/*! \brief specify pixel arithmetic for RGB and alpha components separately
 *
 * the same as glBlendFunc, but you can give different calculations for the RGB and alpha factors.
 * see glBlendFunc for the calculation
 *
 * \param sfactorRGB source RGB blending factors, see \ref sfactor in glBlendFunc
 * \param dfactorRGB destination RGB blending factors, see \ref dfactor in glBlendFunc
 * \param sfactorAlpha source alpha blending factors, see \ref sfactor in glBlendFunc
 * \param dfactorAlpha source alpha blending factors, see \ref dfactor in glBlendFunc
 *
 * \errors GL_INVALID_ENUM if one of the enums are wrong
 *                              (desktop GL does specify only warnings on RGB, not alpha factors)
 */
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GLAPI PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;
#define glBlendFuncSeparate glad_glBlendFuncSeparate

/*! \} */


/*! \brief specify the value used for depth buffer comparisons
 *
 * when GL_DEPTH_TEST is enabled and new pixels generated, this test will determine if they're drwan:
 *  GL_NEVER        never draw the new pixel
 *  GL_LESS         draw if new.depth <  old.depth at that pixel
 *  GL_EQUAL        draw if new.depth == old.depth at that pixel
 *  GL_LEQUAL       draw if new.depth <= old.depth at that pixel
 *  GL_GREATER      draw if new.depth >  old.depth at that pixel
 *  GL_NOTEQUAL     draw if new.depth != old.depth at that pixel
 *  GL_GEQUAL       draw if new.depth >= old.depth at that pixel
 *  GL_ALWAYS       always draw the new pixel
 * the default is GL_LESS, however by default GL_DEPTH_TEST is off, so this has no effect until turnt on
 * also, until GL_DEPTH_TEST is on, the depth buffer will not be updated at all.
 * To write to it use GL_ALWAYS
 *
 * \param funct new depth comparison function. must be GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL,
 *                          GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, or GL_ALWAYS
 *
 * \error GL_INVALID_ENUM if \ref funct is not one of the accepted values
 *
 * \ingroup postprocessing
 */
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC)(GLenum func);
GLAPI PFNGLDEPTHFUNCPROC glad_glDepthFunc;
#define glDepthFunc glad_glDepthFunc

/*! \brief specify mapping of depth values from normalized device coordinates to window coordinates
 *
 * the fragment shader returns depth values in [-1, 1], but they must be specified to land in [0, 1]
 * this is done by a linear transformation of [-1, 1] to an interval in [0, 1], in the following way:
 *      x in [-1, 1] is mapped to n + ((x+1)/2)*(f - n)
 * where n and f are any values in [0, 1]. If n < f, this produces a positive, and if n > f a negative
 * mapping, and f = n maps everything to a single value.
 *
 * Note: this function does not in exist in GL ES 2.0, instead being replaced with
 * glDepthRangef! This means, that any value passed in here should fit in a float for compatibility.
 * Since this is a widening, not a narrowing cast, glDepthRangef is defined as an alias to glDepthRange,
 * if not otherwise available
 *
 * \param n mapping of the near clipping plane to window coordinates = mapping of -1. Default is 0.
 * \param f mapping of the far clipping plane to window coordinates = mapping of 1. Default is 1.
 *
 * \errors none
 *
 * \ingroup postprocessing
 */
typedef void (APIENTRYP PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
GLAPI PFNGLDEPTHRANGEPROC glad_glDepthRange;
#define glDepthRange glad_glDepthRange
/* ??? */
#define glDepthRangef glad_glDepthRange


/*! \brief specify whether front- or back-facing facets can be culled
 *
 * specifies which side of facets/polygons are drawn, if any.
 *      GL_FRONT          front faces (as specified by glFrontFace) are culled if GL_CULL_FACE is enabled
 *      GL_BACK           back faces (the opposite of front faces) are culled if GL_CULL_FACE is enabled
 *      GL_FRONT_AND_BACK all faces are culled if GL_CULL_FACE is enabled; only points and lines are drawn
 *
 * \param mode selection of culling faces, must be GL_FRONT, GL_BACK or GL_FRONT_AND_BACK
 *
 * \errors GL_INVALID_ENUM if \ref mode is not GL_FRONT, GL_BACK or GL_FRONT_AND_BACK
 *
 * \ingroup postprocessing
 */
typedef void (APIENTRYP PFNGLCULLFACEPROC)(GLenum mode);
GLAPI PFNGLCULLFACEPROC glad_glCullFace;
#define glCullFace glad_glCullFace

/*! \brief define front- and back-facing polygons
 *
 * defines which side of a polygon is called front facing. A projection is said to have clockwise winding,
 * if the projection of the path from the first to the last vertex moves clockwise around its interior.
 * therefore, there are two modes: GL_CW: clockwise being front-facing
 *                                 GL_CCW: clockwise begin back-facing, i.e. counter-clockwise being front
 * the default is GL_CCW.
 *
 * \param mode orientation of front-facing polygons, must be GL_CW or GL_CCW
 *
 * \errors GL_INVALID_ENUM if \ref mode is not GL_CW or GL_CCW
 *
 * \ingroup postprocessing
 */
typedef void (APIENTRYP PFNGLFRONTFACEPROC)(GLenum mode);
GLAPI PFNGLFRONTFACEPROC glad_glFrontFace;
#define glFrontFace glad_glFrontFace










/*! \brief bind a named buffer object
 *
 * Binds a buffer object to the GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER target.
 * GL 4.5 and GL ES 3.2 guarantee that a new buffer with the "name" (= id) \ref buffer
 * will be created if it not already exists; however, GL 2.1 doesn't guarantee it,
 * and GL 4.5 even states that new names must be obtained by glGenBuffers, which
 * appears therefore to be the safer option.
 *
 * Breaks the previous binding.
 * Supplying the buffer name 0 unbinds the previously bound buffer without setting a new one.
 * Bindings persist until another is done on \ref target or glDeleteBuffers is called on \ref buffer
 * buffers can be reused for different targets, but that may be inefficient, as the driver
 * can optimize for a specific target. Therefore the best order of operation is
 * first glGenBuffers, then glBindBuffer and after that everything else.
 *
 * \ref buffer will be affected by operations on \ref target, except if buffer == 0, then
 * it will generate GL_INVALID_OPERATION on attempted operations.
 *
 * Use of the targets:
 * GL_ARRAY_BUFFER is used as a replacement of the old "client side memory" of suppliying
 *      fixed data by glNormal etc, instead reading vertex data out of the bound buffer.
 *      used primarily by glVertexAttribPointer to supply vertex attributes
 * GL_ELEMENT_ARRAY_BUFFER is used as a replacement for the "client side memory" to load
 *      index parameters. It is used primarily by glDrawElements to supply vertex array indices
 *
 * \param target target to which the buffer object is bound
 *                  must be GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
 * \param buffer name (id) of a buffer object
 *
 * \errors GL_INVALID_ENUM  if \ref target not GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
 *         GL_INVALID_VALUE if \ref buffer not returned from glGenBuffers (in GL 4.5)
 *
 * \ingroup buffer
 */
typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
GLAPI PFNGLBINDBUFFERPROC glad_glBindBuffer;
#define glBindBuffer glad_glBindBuffer

/*! \brief create and initialize a buffer object's data store
 *
 * creates a _new_ data store of the buffer object bound to \ref target, deletes the old one if it exists.
 * Size can be specified, as well as a pointer to copy out of (remains uninitialized if data == NULL)
 *
 * usage is a hint of how the data is used (only cnstraints initialization, not use), namely:
 *      GL_STREAM_DRAW      modified once and used a few times
 *      GL_STATIC_DRAW      modified once and used many times
 *      GL_DYNAMIC_DRAW     modified repeatedly and used many times
 * data will always be modified by the application, but used for GL drawing / imaging command (hence _DRAW)
 *
 * data elements must be aligned so that for a datum x with sizeof(x) = N bytes holds:
 *      offset of x in buffer is a multiple of N.
 *
 * \param target target buffer object, must be GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
 * \param size size in bytes of the buffer object's new data store
 * \param data pointer to data that will be copied for initialization, or NULL if no data is to be copied
 * \param usage expected usage pattern of the data store (hint).
 *              must be GL_STREAM_DRAW, GL_STATIC_DRAW, or GL_DYNAMIC_DRAW
 *
 * \errors GL_INVALID_ENUM      if \ref target or \ref usage is not an allowed value
 *         GL_INVALID_VALUE     if \ref size is negative
 *         GL_INVALID_OPERATION if reserved buffer object name 0 is bound to target
 *         GL_OUT_OF_MEMORY     if GL can't allocate the necessary memory
 *
 * \ingroup buffer
 *
 */
typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
GLAPI PFNGLBUFFERDATAPROC glad_glBufferData;
#define glBufferData glad_glBufferData

/*! \brief update a subset of a buffer object's data store
 *
 * updates data in the data store of the buffer object bound to \ref target.
 * Copies from data at data[0]..data[size-1] to data_store[offset]..data_store[offset+size-1]
 * Can be more efficient than creating new buffers with glBufferData due to lack of allocation.
 * Will wait on rendering still done with the data before replacing it
 *  (only written in a Note, so there is probably no guarantee for that)
 *
 * Alignment rules as in glBufferData: offset of x in buffer is a multiple of sizeof(x).
 *
 * \param target target buffer object, must be GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
 * \param offset offset in bytes into the buffer object's data store where data replacement will begin
 * \param size size in bytes of the data store region being replaced
 * \param data pointer to the new data that will be copied into the data store
 *
 * \errors GL_INVALID_ENUM      if \ref target isn't GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
 *         GL_INVALID_VALUE     if \ref offset, \ref size negative, or offset+size > GL_BUFFER_SIZE
 *                                  of the buffer currently bound to \ref target
 *         GL_INVALID_OPERATION if reserved buffer object name 0 is bound to target
 *                                  only on GL 2.1 if the buffer is mapped, and on GL 4 if it's immutable
 *
 * \ingroup buffer
 */
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
GLAPI PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
#define glBufferSubData glad_glBufferSubData

/*! \brief delete named buffer objects
 *
 * deletes buffer objects named by the elements of an array of buffer names. Those names then
 * can be reused for new buffers, currently bound buffers are also deleted and the binding reverts to 0.
 * any other elements in the array, being 0 or just not a buffer name at all, are ignored without error.
 *
 * \param n number of buffer objects to be deleted.
 * \param buffers array of buffer objects to be deleted.
 *
 * \errors GL_INVALID_VALUE if n < 0
 *
 * \ingroup buffer
 */
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
GLAPI PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
#define glDeleteBuffers glad_glDeleteBuffers

/*! \brief generate buffer object names
 *
 * returns n new _names_ for buffers. They still must be created by glBindBuffer
 *
 * \param n number of buffer object names to be generated
 * \param buffers array in which the generated buffer object names are stored
 *
 * \errors GL_INVALID_VALUE if \ref n < 0
 *
 * \ingroup buffer
 */
typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
GLAPI PFNGLGENBUFFERSPROC glad_glGenBuffers;
#define glGenBuffers glad_glGenBuffers




/*! \brief select active texture unit
 *
 * selects which texture unit subsequent texture state calls will affect.
 * The number of texture units is implementation dependent,
 * but must be at least:
 *      2 per GL 2.1    reference pages
 *      8 per GL ES 2.0 reference pages
 *     32 per GL ES 3.2 reference pages
 *     80 per GL 4.5    reference pages
 * That number can be queried by the enum GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS.
 * Texture units are represented by the enum values GL_TEXTUREi,
 * where i ranges from 0 to (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1).
 * The header includes definitions up to GL_TEXTURE31
 * The general rule is: GL_TEXTUREi = GL_TEXTURE0 + i.
 *
 * The initial value for the active texture is GL_TEXTURE0
 *
 * \param texture texture unit to be made active.
 *      must be a valid GL_TEXTUREi
 *
 * \errors GL_INVALID_ENUM on wrong input enum parameter
 *
 * \ingroup texture
 */
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
GLAPI PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
#define glActiveTexture glad_glActiveTexture

/*! \brief bind a named texture to a texturing target
 *
 * After generating a name with glGenTextures (necessary since GL 4.5), it can be
 * bound to a certain target. The texture than cen be operated on until it is unbound
 * or destroyed with glDeleteTextures.
 * \ref texture == 0 means the default target.
 *
 * binding a new texture name initializes it's memory for the appropriate use, it then
 * can be supplied with data (e.g. via glTexImage2D). It can be rebound to _the same_ target
 * multiple times; it can also be loaded with data multiple times. However, it's faster to switch
 * between different textures by name rather then by reloading the data associated to them.
 *
 * Therfore, it's best to generate as many names as necessary with glGenTextures, then
 * bind them all succesively to \ref target with glBindTexture, and fill them up with
 * the necessary data in between, and then use glBindTexture again to later switch between
 * them, and only call glDeleteTextures when the data behind them is unneeded.
 *
 * GL ES also specifies that the target refers to "the active texture unit". This indicates a
 * possibility to also switch between various textures with glActiveTexture in combination with
 * glBindTexture, as to have multiple textures bound (not just loaded with inactive names) at once.
 *
 * \param target  the target to which the texture is bound.
 *                  must be GL_TEXTURE_2D or GL_TEXTURE_CUBE_MAP
 * \param texture name (id) of a texture
 *
 * \errors GL_INVALID_ENUM      if \ref target is not GL_TEXTURE_2D or GL_TEXTURE_CUBE_MAP
 *         GL_INVALID_VALUE     if \ref texture is not returned from glGenTextures (in GL 4.5)
 *         GL_INVALID_OPERATION if \ref texture was loaded with a different target then it's first one
 *
 * \ingroup texture
 */
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
GLAPI PFNGLBINDTEXTUREPROC glad_glBindTexture;
#define glBindTexture glad_glBindTexture

/*! \brief copy pixels into a 2D texture image
 *
 * Copies pixels from the framebuffer into a texture. first works like glReadPixels with format GL_RGBA,
 * with conversion of the screen data to RGBA, but then works more like glTexImage2D for these pixel data
 * as input, i.e. with clamping to [0,1] and conversion to the texture format (i.e. throwing away the
 * alpha channel if RGB instead of RGBA is selected)
 *
 * A box is selected from (x,y) as the lower left corner with specified height and width.
 * The pixel ordering is transferred from lower x, y coord.s of the framebuffer to lower s, t of the texture
 * If the box is bigger than the window / framebuffer, values are undefined.
 * height == 0 and width == 0 indicates a NULL texture
 * The target GL_TEXTURE_2D supports at least 64x64, and GL_TEXTURE_CUBE_MAP faces at least 16x16 textures
 * GL 2.1 without extensions requires width and height to be a power of two.
 *
 * The data will be written into the _current texture unit_. See glActiveTexture.
 *
 * \param target target of the active unit to write to, must be GL_TEXTURE_2D or one of the faces of
 *                GL_TEXTURE_CUBE_MAP: GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
 *                                     GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
 *                                     GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
 * \param level level-of-detail image to override on the texture. 0 is base, n is nth mipmap reduction image
 * \param internalformat internal format of texture storage, must be GL_RGB or GL_RGBA
 * \param x the x coordinate of the lower left corner
 * \param y the y coordinate of the lower left corner
 * \param width  the width  of the copy region, must be a power of two for GL 2.1 compatibility
 * \param height the height of the copy region, must be a power of two for GL 2.1 compatibility
 * \param border must be 0, not used after GL 2.1
 *
 * \errors GL_INVALID_ENUM  if \ref target or \ref internalformat is not one of the accepted values
 *         GL_INVALID_VALUE     if \ref target is a cube map face and width != height (only GL ES 2.0)
 *                              or if level < 0, or width and height outside of range 0..GL_MAX_TEXTURE_SIZE
 *                                              or 0..GL_MAX_CUBE_MAP_TEXTURE_SIZE for GL ES 2.0,
 *                              or if border != 0, or if \ref height or \ref width no power of two (GL 2.1),
 *                              or in GL 2.1 if \ref internalformat is not one of the accepted values
 *                              or (maybe?) if level > log_2 GL_MAX_TEXTURE_SIZE
 *         GL_INVALID_OPERATION if the framebuffer is wrongly configured (not achievable in the
 *                                  common subset, similar with the GL_INVALID_FRAMEBUFFER_OPERATION error)
 *
 * \ingroup texture
 */
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GLAPI PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;
#define glCopyTexImage2D glad_glCopyTexImage2D

/*! \brief copy a two-dimensional texture subimage
 *
 * replaces part of an existing texture image with data from the frame buffer.
 * inserts into the rectangle from (xoffset, yoffset) in the lower left to with height and width specified
 * rectangle must lie inside the texture, but the data rectangle can lie outside of the frame buffer, then
 * undefined values are copied. width == height == 0 means a no-op.
 *
 * \param target  like in glCopyTexImage2D
 * \param level   like in glCopyTexImage2D
 * \param xoffset the x coordinate of the lower left corner within the texture, where data will be inserted
 * \param yoffset the y coordinate of the lower left corner within the texture, where data will be inserted
 * \param x       like in glCopyTexImage2D
 * \param y       like in glCopyTexImage2D
 * \param width   like in glCopyTexImage2D
 * \param height  like in glCopyTexImage2D
 *
 * \errors GL_INVALID_ENUM      if \ref target is not one of the accepted values
 *         GL_INVALID_VALUE     if level < 0, width, height, xoffset, yoffset < 0, or
 *                              xoffset + width > w or yoffset + height > h
 *                                  with w, h width and height of the texture copied into
 *                              or (maybe?) if level > log_2 GL_MAX_TEXTURE_SIZE
 *         GL_INVALID_OPERATION if the texure was not defined with glTexImage2D or glCopyTexImage2D
 *                              or if the framebuffer is wrongly configured (impossible in
 *                              common GL, alongside with the GL_INVALID_FRAMEBUFFER_OPERATION error)
 *
 * \ingroup texture
 */
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;
#define glCopyTexSubImage2D glad_glCopyTexSubImage2D

/*! \brief delete named textures
 *
 * deletes textures named by the elements of an array of texture names. Those names then
 * can be reused for new textures, currently bound textures are also deleted and the binding reverts to 0.
 * any other elements in the array, being 0 or just not a textures name at all, are ignored without error.
 *
 * \param n number of textures to be deleted.
 * \param buffers array of textures to be deleted.
 *
 * \errors GL_INVALID_VALUE if n < 0
 *
 * \ingroup texture
 */
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint *textures);
GLAPI PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
#define glDeleteTextures glad_glDeleteTextures

/*! \brief generate texture names
 *
 * returns n new _names_ for texture. They still must be initialized by glBindTexture
 *
 * \param n number of texture names to be generated
 * \param buffers array in which the generated texture names are stored
 *
 * \errors GL_INVALID_VALUE if \ref n < 0
 *
 * \ingroup texture
 */
typedef void (APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);
GLAPI PFNGLGENTEXTURESPROC glad_glGenTextures;
#define glGenTextures glad_glGenTextures








/*! \brief attach a shader object to a program object
 *
 * add a shader object to the list of shaders to be linked to a
 * program object. It only marks them to be linked later, doesn't
 * link them itself. It can even have source etc. loaded later,
 * since this function only connects the two handles, not their content.
 *
 * GL ES compatibility demands that only one shader per shader type
 * is attached to a program object. A single shader can be used in multiple
 * programs.
 *
 * Even if deleted, the shader will not be detached automatically
 * if attached, it needs to be detached manually with glDetachShader.
 *
 * \param program program object to which a shader object will be attached
 * \param shader shader object to be attached
 *
 * \errors GL_INVALID_VALUE     if program or shader are not generated by GL
 *         GL_INVALID_OPERATION if program isn't a program, shader isn't a shader,
 *                                  the shader is already attached or, specifically
 *                                  in GL ES, if there is another shader of the same
 *                                  type already attached
 *
 * \ingroup shader
 */
typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
GLAPI PFNGLATTACHSHADERPROC glad_glAttachShader;
#define glAttachShader glad_glAttachShader

/*! \brief compile a shader object
 *
 * Compiles the source code stored in \ref shader to a shader binary then stored in \ref shader
 * Compilation can fail for various reasons, however, that doesn't produce a GL error and must
 * be queried by the shader property GL_COMPILE_STATUS (see glGetShaderiv) and glGetShaderInfoLog
 *
 * \param shader shader object to be compiled
 *
 * \errors  GL_INVALID_OPERATION if \ref shader isn't a shader or there is no shader compiler in GL ES 2.0
 *          GL_INVALID_VALUE     if \ref shader is not a value generated by OpenGL
 *
 * \ingroup shader
 */
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);
GLAPI PFNGLCOMPILESHADERPROC glad_glCompileShader;
#define glCompileShader glad_glCompileShader

/*! \brief create a program object
 *
 * creates an empty program object and returns its name / id.
 *
 * \return the program name (id), or 0 if an error occurs creating the program object
 *
 * \errors none
 *
 * \ingroup shader
 */
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)(void);
GLAPI PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
#define glCreateProgram glad_glCreateProgram

/*! \brief create a shader object
 *
 * creates an empty shader object of a given type and returns its name / id
 *
 * \param type type of shader to be created, must be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 *
 * \return the shader name (id), or 0 if an error occurs creating the shader object
 *
 * \errors GL_INVALID_ENUM if type is not GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 *
 * \ingroup shader
 */
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
GLAPI PFNGLCREATESHADERPROC glad_glCreateShader;
#define glCreateShader glad_glCreateShader

/*! \brief delete a program object
 *
 * deletes and deallocates a program object and all that belongs to it.
 * If the program is currently running, it will only be deleted after it no longer is
 * shader objects will be detached, but not deleted.
 * \ref program == 0 will be ignored.
 * It will also set GL_DELETE_STATUS to GL_TRUE (see glGetProgramiv)
 *
 * \param program the program object to be deleted
 *
 * \errors GL_INVALID_VALUE if \ref program is not a value generated by OpenGL
 *
 * \ingroup shader
 */
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint program);
GLAPI PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
#define glDeleteProgram glad_glDeleteProgram

/*! \brief delete a shader object
 *
 * deletes and deallocates a shader object and all that belongs to it.
 * If the shader is currently attached to a program, it will only be deleted after it no longer is
 * \ref shader == 0 will be ignored.
 * It will also set GL_DELETE_STATUS to GL_TRUE (see glGetShaderiv)
 *
 * \param shader the shader object to be deleted
 *
 * \errors GL_INVALID_VALUE if \ref shader is not a value generated by OpenGL
 *
 * \ingroup shader
 */
typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);
GLAPI PFNGLDELETESHADERPROC glad_glDeleteShader;
#define glDeleteShader glad_glDeleteShader

/*! \brief detach a shader object from a program object (to which it is attached)
 *
 * undoes glAttachShader by detaching the shader from the program object
 * if called afer glDeleteShader and \ref shader is no longer attached to any program, it will be deleted
 *
 * \param program program object from which to detach the shader object
 * \param shader shader object to be detached
 *
 * \errors GL_INVALID_VALUE     if \ref program or \ref shader is a value that was not generated by OpenGL
 *         GL_INVALID_OPERATION if \ref program isn't a program object, \ref shader isn't a shader object
 *                              or wasn't attached to \ref program
 *
 * \ingroup shader
 */
typedef void (APIENTRYP PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
GLAPI PFNGLDETACHSHADERPROC glad_glDetachShader;
#define glDetachShader glad_glDetachShader


/*! \brief associate a generic vertex attribute index with a named attribute variable
 *
 * Creates an association between the input attribute indices 0..GL_MAX_VERTEX_ATTRIBS-1,
 * (of which 0 is the generic attribute), which stay the same between
 * different calls to glUseProgram for different programs,
 * and the variable names used in vertex shaders as "in" parameters.
 *
 * Takes effect only after the next linking of the program. Default names can't be bound except to 0.
 * Can be called before vertex shader is attached or even if the variable is never used.
 *
 * Matrices get multiple numbers, one per column.
 *
 * One index can be bound to many names, but only one index can be used per name.
 * However, only one of those aliasing variables can be used at each codepath, as the optimizer
 * can assume so and mistakes are generally not detected.
 *
 * Without calling glBindAttribLocation, the varible will get assigned an index you can query with
 * glGetAttribLocation.
 *
 * the string \ref name can be freed after call, since it is copied.
 *
 * \param program handle of the program object in which the association is to be made
 * \param index index of the generic vertex attribute to be bound
 * \param name null terminated string containing the name of the vertex shader attribute variable
 * to which index is to be bound
 *
 * \errors GL_INVALID_VALUE         if index is not in [0,GL_MAX_VERTEX_ATTRIBS-1]
 *                                  or program isn't generated by GL
 *         GL_INVALID_OPERATION     if name starts with "gl_" or program isn't a program
 *
 * \ingroup shader
 */
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar *name);
GLAPI PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;
#define glBindAttribLocation glad_glBindAttribLocation

/*! \brief enable or disable a generic vertex attribute array
 *
 * enables/disables vertex attribute arrays used in draw calls, since they're disabled by default.
 *
 * \param index index of the generic vertex attribute to be enabled or disabled
 *
 * \errors GL_INVALID_VALUE     if index >= GL_MAX_VERTEX_ATTRIBS
 *         GL_INVALID_OPERATION if no vertex array object is bound only in GL 4
 *
 * \ingroup shader
 */
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
GLAPI PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
#define glDisableVertexAttribArray glad_glDisableVertexAttribArray
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray

/*! \brief return information about an active attribute variable (for the specified program object)
 *
 *
 */
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GLAPI PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib;
#define glGetActiveAttrib glad_glGetActiveAttrib


#ifdef __cplusplus
}
#endif

#endif
