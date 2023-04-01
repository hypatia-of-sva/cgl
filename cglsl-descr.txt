Description of the common parts of GLSL
Referenced on https://registry.khronos.org/OpenGL/specs/gl/GLSLangSpec.1.10.pdf (1.1)
and https://registry.khronos.org/OpenGL/specs/es/2.0/GLSL_ES_Specification_1.00.pdf (ES1.0)
The wording has been reduced, but it keeps all the formally binding information.#





2 Overview:
- There are two types of languages described: Vertex and Fragment

3 Basics:

The character Set is /[a-zA-Z_0-9.+-/*%<>[](){}^|&~=!:;,?]/, # for preprocessor and space, tab, vtab, form feed, CR and LF (both just called new-line, if alone or in combination). Not part of it: \,', ", EOF.
The language is case sensitive.

Compilation process(based on c++): two arrays of strings get passed in for the vertex and fragment shader. For each do:
    1. concatenate into a single string (without inserting newlines)
    2. convert into a sequence of preprocessor tokens (pp-numbers, ids, and operators) with comments being replaced by a ' ' (but retaining newlines)
    3. preprocess (execute directives and expand macros)
    4. convert pp-tokens into tokens
    5. delete whitepace and line breaks
    6. analyze the syntax according to formal grammar (build AST)
    7. check according to semantics.
After this, the shaders are _compiled_. If there are any errors, the message reference the index into the array of strings + a line nr (= nr of newlines processed + 1) within that string. After this is done, and when now doing linking, any "varying" not used in both the vertex and fragment shaders may be discarded, and finally a binary gets created (not necessary for the "compilation" stage).


preprocessor directives: each have a nr sign #. There can only be ' ' or \t chars before and after the '#', they're ignored, all other characters produce errors. A line with only a '#' char gets ignored.

#define and #undef work like in C++ for constants and macros.

predefined macros:
__LINE__        nr of preceding newlines in the current string
__FILE__        index into the string array
__VERSION__     GLSL version being used. Has:
                    GLSL 1.10           110
                    GLSL ES 1.00        100
GL_ES           set to 1 if compiled in GLSL ES, otherwise undefined
reserved names: anything containing "__", and anything beginning with "GL_"

#if, #ifdef, #ifndef, #else, #elif, and #endif work and evaluate like in C++ (literals, operators etc), except
    a) only literal integer constants and identifiers consumed by the defined operator, no char constants
    b) undefined identifiers not used in the defined operator cause an error instead of defaulting to '0'
        except if as the second operand of an && or || expression that short circuits, then it's ignored
    c) no number sign based operators (no #, #@, ##, etc.) and no sizeof
Operator Table:
Precedence      Operator class          Operators           Associativity
1 (highest)     parenthetical grouping  ( )                 NA
2               unary                   defined             Right to Left
                                        + - ~ !
3               multiplicative          * / %               Left to Right
4               additive                + -                 Left to Right
5               bit-wise shift          << >>               Left to Right
6               relational              < > <= >=           Left to Right
7               equality                == !=               Left to Right
8               bit-wise and            &                   Left to Right
9               bit-wise exclusive or   ^                   Left to Right
10              bit-wise inclusive or   |                   Left to Right
11              logical and             &&                  Left to Right
12 (lowest)     logical inclusive or    ||                  Left to Right
The defined operator can written as "defined identifier" or "defined ( identifier )"

#error puts a diagnostic message into the shader object’s information log with the string after "#error" until the next newline. The implementation must then consider the shader to be ill-formed

#pragma is used to add compiler features, in #pragma there is no macro expansion and unknown pragmas must be ignored. Built in:
    STDGL       reserved. No implementation pragma may have STDGL as its first token
    optimize    turns optimization on/off. default: "#pragma optimize(on)", option: "#pragms optimize(off)"
    debug       turns debug annotations on/off. default: "#pragma debug(off)", option: "#pragma debug(on)"
optimize and debug #pragmas can only be used outside function definitions.

    [[removal for CGLSL altogether? Rather maybe automatically insert a string by a compatibility
    function, that passes the correct #version, and then don't use extensions or #line.
    Similarly, #pragma should be reduced to only optimize and debug.]]
"#version nr" declares a certain GLSL version to be used:
    #version 110            GLSL 1.10 (implicit on desktop GL)
    #version 100            GLSL ES 1.00 (implicit on GL ES)
issues an error if nr outside of supported range.
only white space or comments may procede #version. macro substitution isn't done here.

"#extension {name} : {behavior}" sets the rule {behavior} on the extension {name}, which can be one of:
    require   activate, and give an error if not supported
    enable    activate, and warn if not supported
    warn      like "enable", but also warn if its used in any way not otherwise activated;
    disable     disable the extensions, but also warn if it's not supported in the first place
There also is a special extension name "all"
    "#extension all : require" and "#extension all : enable" gives an error
    "#extension all : warn" warns on any usage of any extension
    "#extension all : disable" reverts back to the unextended language (thats set by default).
Later #extension directives override earlier ones, they generally should be written before any any non-preprocessor tokens, and can include both shaders. Macro expansion isn't done in #extension lines.

"#line linenr" sets __LINE__ and "#line linenr sourcenr" sets __LINE__ and __FILE__, for now and the following strings in the array. Macro expansion _is_ done here. GLSL 1.10 and GLSL ES 1.00 don't agree on the numbering though: GLSL 1.10 says, that the next line has __LINE__ == linenr+1, whereas GLSL ES 1.00 says that it has __LINE__ == linenr. Therfore, this preprocessor construct is _not_ portable and not to be used in CGLSL.

If a macro produces a preprocessor directive, the results are undefined. The compiler can report an error, but doesn't have to.


Comments are delimited by /* and */, or by // and a new-line. The begin comment delimiters (/* or //) are not recognized as comment delimiters inside of a comment, hence comments cannot be nested. If a comment resides entirely within a single line, it is treated syntactically as a single space. New-lines are not eliminated by comments by GLSL ES 1.00


The language is a sequence of tokens. A token can only be a keyword or other identifier, a number constant (integer or floating point) or an operator.

used keywords: [[attribute and uniform depends on the decision about #version / if another macro is added]]
    if else do for while break continue discard return const uniform in out inout struct
    float int void bool true false
    vec2 vec3 vec4 ivec2 ivec3 ivec4 bvec2 bvec3 bvec4 mat2 mat3 mat4 sampler2D samplerCube
    [attribute varying]
reserved keywords:
    asm class union enum typedef template this packed goto switch default
    inline noinline volatile public static extern external interface flat
    long short double half fixed unsigned superp input output
    hvec2 hvec3 hvec4 dvec2 dvec3 dvec4 fvec2 fvec3 fvec4
    sampler2DRect sampler3DRect sampler2DRectShadow
    sizeof cast namespace using
    sampler1D sampler3D sampler1DShadow sampler2DShadow
    lowp mediump highp precision invariant
and all identifiers containing "__"

identifiers: of the form /[_a-zA-Z] [_a-zA-Z0-9]+?/. usage splits between variables, functions, struct and field selectors. Identifiers starting with "gl_" are reserved for GLSL itself.



4 Variables and types:


Variables and functions must be declared with a (qualified) type (with possible assignment, see grammar). There is no default type. There are no implicit conversions.

Basic types: void bool int float vec2 vec3 vec4 ivec2 ivec3 ivec4 bvec2 bvec3 bvec4 mat2 mat3 mat4 sampler2D samplerCube. All other types are built with structs and arrays, there are no pointers.

void: only as a return type for functions not returning values, or an empty formal or actual parameter list

bool: boolean type with only the values "true" or "false". Condition expressions (as in: if, for, ?:, while, do-while) must evaluate to the type bool. Hardware is not expected to directly support it.

int: non portable type for indexing. GLSL 1.10 guarantees 16 bits of data + sign bit, GLSL ES 1.00 doesn't.
Can be implemented with floats instead of integer hardware, hence no portable wrapping.
Literals: /([1-9][0-9]+? | 0[0-7]+? | 0[xX][0-9a-fA-F]+)/ (decimal, octal and hexadecimal)
No white space allowed in literals, leading minus sign is taken as operator, not as part of the literal.

float: scalar floating point type. GLSL 1.10 says it should match IEEE in representation and GL 1.4 in precision of operations, GLSL 1.00 doesn't. Things like divide by 0 can lead to UB, but not to interrupts/exits. Literals: /(([0-9]+ '.' [0-9]+? | '.' [0-9]+) ([eE] [+-]? [0-9]+)? | [0-9]+ [eE] [+-]? [0-9]+)/

vectors: there are vectors 2-4 bools (bvec2 bvec3 bvec4), ints (ivec2 ivec3 ivec4) and floats (vec2 vec3 vec4) that allow mapping of hardware vectorization to these data types. However, no guarantees are made. Initialization with constructors.

matrices: 2×2, 3×3 and 4×4 float matrices (mat2 mat3 mat4), read from and written to in column major order. Initialization with constructors.

samplers: sampler2D and samplerCube are opaque handles to textures. can only be declared as "in" function parameters (passing on from existing handle variables _of the same type_) or uniforms (initialized from GL API calls), not as l-values, not used in expressions except the built-in texture functions, array indexing, structure field selection, and parentheses. This also applies to all structures containing samplers.

structs: type definition as per the grammar as ("struct" id? '{' (type <id ('['constant_expression']')?> ';')+ '}') where type is a basic type or the name of an already defined struct. Creates a new typedef under the name of the outermost id if present. Shadows variables, functions and other types with the same name. Must have at least one member, all without qualifiers, no bit fields Initializers, forward references etc, only basic types, already defined structs or arrays of those. The struct type defines its own namespace for member identifiers. Every member has a name / id. Structures can have constructors. Usage restructions of types or qualifies will be inherited by a structure from its elements recursively.

arrays: declared by a defined type and a size of integral constant expression > 0. It's illegal to index it with a constant expression, and UB (platform dependent, possibly unstable or not) to do with a non-constant expression, outside the range 0..size-1. Only one-dimensional arrays of basic types and structs allowed.


Scoping rules:
Kinds of scopes:
    - built-in functions             => outermost scope; no user defined functions here!
    - outside of function definition => glibal scope, i.e. to the end of the translation unit / shader
    - in while test / for statement  => to the end of the sub-statement of the loop
    - in compound statement          => to the end of the compound statement
    - function parameter             => to the end of the function definition
    - a function body is a scope
    - if statement: of form "if (e) s1 else s2 "; s1, s2 form scope, e doesn't
Names are visible after declaration, i.e. after }; for structs, after T a = x for vars, and after the prototype declaration for functions (not equal to C++; int a = 1, b = a; is allowed for example)

A variable can't be redeclared, but an inner scope can shadow an outer scope's storage, hiding the value and providing new storage, making the old variable inaccessible
A function can be declared at most twice with the same signature: once as a prototype, once as a definition
however: two functions with the same name and different arguments are allowed, thats called an overload
function names can only be declared in the global scope, no local prototypes.
Functions, variables and structs share a single name space per scope, i.e. they can't shadow each other
shared globals are only uniforms as per GLSL ES 1.00. They must share name, storage quaifiers, and equivalent types, as in: arrays the same base type and size; scalars the same type name and definition, structures the same name, and fields with the same name, type name and definition, recursively.

qualifiers:


