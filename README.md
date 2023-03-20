# Common OpenGL (CGL)
Common OpenGL (CGL) - Description of the commen subset of OpenGL 2.1, OpenGL ES 2.0 and and OpenGL 4.5 core profile, with tools and tutorials for using it in C and C++.

## Motivation

One of the main problems with using OpenGL is the version difference between various OpenGL distributions, between older OpenGL 2 iGPUs
and modern OpenGL 4.X / Vulkan graphics cards for PC and console, as well as mobile and embedded systems, that are usually addressed with OpenGL ES and sometimes still only have OpenGL ES 2.0.

This, however, is mostly a problem of tools and documentation, not of the API itself. Moreover, for smaller projects, OpenGL 2 is quite usable and usually
fast enough.

The problem is, that if you search for OpenGL information, you will usually block yourself into a certain version, when really that is not necessary at
all. For example: Using Framebuffers and Renderbuffers works in GL ES 2.0, but not in OpenGL 2.1. 1D and 3D Textures are available even before OpenGL 2.0,
but are entirely missing in GL ES 2.0. And obviously there are many features of modern OpenGL, such as 3.2+ core profile, like VAO and UBO, or location parameters in GLSL, that are not
available on older platforms, and legacy features in OpenGL 2.1, such as glLight, that are not available in modern OpenGL core profile, and also not in
GL ES 2.0.

But those are only the obvious differences visible from the header file. The smaller differences, like: the possible modes of glBindBuffer etc., are very
relevant for porting, but not usually explained together.

This site tries to give documentation of the shared subset, to encourage development of games and application in that shared, simpler API. What are the
reasons for me encouraging this? There are at least two different ones:

- On the one hand, the technical reason of compatibility, portability and, even when only wanting to write for desktop, performance (in comparison to
using a compatibility context).
- On the other hand the aesthetical reason of reduced complexity. Even if you really don't need broad compatibility, and using Vulkan would be just as good,
you can't beat old OpenGL in its simplicity with the newer APIs. There are just a lot more moving pieces in Vulkan: Command Buffers, Descriptor Sets,
Pipelines, Device Handles etc. etc. Common OpenGL really only has shaders/programs, with uniforms and vertex attributes, and buffers and textures to bind
to them, plus a few fixed functions for blend and stencil operations and things like `glCullFace`. Being under 150 functions, it's easier to learn and master,
and gives a lot more space for the actual decision making. Simplicity breeds creativity, and for a creative endeavour such as computer graphics I think
this might be the better choice than a more low level API like Vulkan, especially for not as advanced applications.

This was my motivation for starting the CGL project, after trying and failing to learn to use Vulkan, due to it's complexity, and also being quite
disappointed by the lack of documentation and the complexity of Modern OpenGL, and the way it's being taught.


## Current status and future direction of the project

I'm currently still working at getting this up and running, and learning myself a lot in the process. Currently I work on synthesizing the OpenGL 2.1, 4.5
and ES 2.0 reference pages (as per Khronos) into a single CGL reference page. This is still a work in progress, but it should result in a kind of
manpages for CGL. I also plan to do the same for the offical API spec and (more importantly) for the respective descriptions of GLSL (being #version 110, 460 and 100).

After that, I plan to write demos for both my own understanding and as tutorials, and also a kind of CGL loader (like glad), that should
also load the GLenum values at runtime if possible.
