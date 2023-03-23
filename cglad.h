

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


#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_MAX_VERTEX_ATTRIBS 0x8869

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_CUBE_MAP 0x8513



/*! @defgroup buffer Buffers
 * @brief buffer object and target functions
 *
 * Functions that refer to buffer objects, their binding and use in different targets.
 */

/*! @defgroup texture Textures
 * @brief texture object and target functions
 *
 * Functions that refer to texture objects, their binding and use in different targets.
 */

/*! @defgroup shader Shaders and Programs
 * @brief shader objects and programs composed of them
 *
 * Functions that create and use shader programs, that is program objects linked together
 * from shader objects, holding executables compiled from GLSL source code.
 */








/*! @brief bind a named buffer object
 *
 * Binds a buffer object to the GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER target.
 * GL 4.5 and GL ES 3.2 guarantee that a new buffer with the "name" (= id) @ref buffer
 * will be created if it not already exists; however, GL 2.1 doesn't guarantee it,
 * and GL 4.5 even states that new names must be obtained by glGenBuffers, which
 * appears therefore to be the safer option.
 *
 * Breaks the previous binding.
 * Supplying the buffer name 0 unbinds the previously bound buffer without setting a new one.
 * Bindings persist until another is done on @ref target or glDeleteBuffers is called on @ref buffer
 * buffers can be reused for different targets, but that may be inefficient, as the driver
 * can optimize for a specific target. Therefore the best order of operation is
 * first glGenBuffers, then glBindBuffer and after that everything else.
 *
 * @ref buffer will be affected by operations on @ref target, except if buffer == 0, then
 * it will generate GL_INVALID_OPERATION on attempted operations.
 *
 * Use of the targets:
 * GL_ARRAY_BUFFER is used as a replacement of the old "client side memory" of suppliying
 *      fixed data by glNormal etc, instead reading vertex data out of the bound buffer.
 *      used primarily by glVertexAttribPointer to supply vertex attributes
 * GL_ELEMENT_ARRAY_BUFFER is used as a replacement for the "client side memory" to load
 *      index parameters. It is used primarily by glDrawElements to supply vertex array indices
 *
 * @param target target to which the buffer object is bound
 *                  must be GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
 * @param buffer name (id) of a buffer object
 *
 * @errors GL_INVALID_ENUM  if @ref target not GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
 *         GL_INVALID_VALUE if @ref buffer not returned from glGenBuffers (in GL 4.5)
 *
 * @ingroup buffer
 */
typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
GLAPI PFNGLBINDBUFFERPROC glad_glBindBuffer;
#define glBindBuffer glad_glBindBuffer






/*! @brief bind a named texture to a texturing target
 *
 * After generating a name with glGenTextures (necessary since GL 4.5), it can be
 * bound to a certain target. The texture than cen be operated on until it is unbound
 * or destroyed with glDeleteTextures.
 * @ref texture == 0 means the default target.
 *
 * binding a new texture name initializes it's memory for the appropriate use, it then
 * can be supplied with data (e.g. via glTexImage2D). It can be rebound to _the same_ target
 * multiple times; it can also be loaded with data multiple times. However, it's faster to switch
 * between different textures by name rather then by reloading the data associated to them.
 *
 * Therfore, it's best to generate as many names as necessary with glGenTextures, then
 * bind them all succesively to @ref target with glBindTexture, and fill them up with
 * the necessary data in between, and then use glBindTexture again to later switch between
 * them, and only call glDeleteTextures when the data behind them is unneeded.
 *
 * GL ES also specifies that the target refers to "the active texture unit". This indicates a
 * possibility to also switch between various textures with glActiveTexture in combination with
 * glBindTexture, as to have multiple textures bound (not just loaded with inactive names) at once.
 *
 * @param target  the target to which the texture is bound.
 *                  must be GL_TEXTURE_2D or GL_TEXTURE_CUBE_MAP
 * @param texture name (id) of a texture
 *
 * @errors GL_INVALID_ENUM      if @ref target is not GL_TEXTURE_2D or GL_TEXTURE_CUBE_MAP
 *         GL_INVALID_VALUE     if @ref texture is not returned from glGenTextures (in GL 4.5)
 *         GL_INVALID_OPERATION if @ref texture was loaded with a different target then it's first one
 *
 * @ingroup texture
 */
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
GLAPI PFNGLBINDTEXTUREPROC glad_glBindTexture;
#define glBindTexture glad_glBindTexture


/*! @brief select active texture unit
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
 *
 * The initial value for the active texture is GL_TEXTURE0
 *
 * @param texture texture unit to be made active.
 *      must be a valid GL_TEXTUREi
 *
 * @errors GL_INVALID_ENUM on wrong input enum parameter
 *
 * @ingroup texture
 */
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
GLAPI PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
#define glActiveTexture glad_glActiveTexture










/*! @brief attach a shader object to a program object
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
 * @param program program object to which a shader object will be attached
 * @param shader shader object to be attached
 *
 * @errors GL_INVALID_VALUE     if program or shader are not generated by GL
 *         GL_INVALID_OPERATION if program isn't a program, shader isn't a shader,
 *                                  the shader is already attached or, specifically
 *                                  in GL ES, if there is another shader of the same
 *                                  type already attached
 *
 * @ingroup shader
 */
typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
GLAPI PFNGLATTACHSHADERPROC glad_glAttachShader;
#define glAttachShader glad_glAttachShader





/*! @brief associate a generic vertex attribute index with a named attribute variable
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
 * the string @ref name can be freed after call, since it is copied.
 *
 * @param program handle of the program object in which the association is to be made
 * @param index index of the generic vertex attribute to be bound
 * @param name null terminated string containing the name of the vertex shader attribute variable
 * to which index is to be bound
 *
 * @errors GL_INVALID_VALUE         if index is not in [0,GL_MAX_VERTEX_ATTRIBS-1]
 *                                  or program isn't generated by GL
 *         GL_INVALID_OPERATION     if name starts with "gl_" or program isn't a program
 *
 * @ingroup shader
 */
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar *name);
GLAPI PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;
#define glBindAttribLocation glad_glBindAttribLocation


