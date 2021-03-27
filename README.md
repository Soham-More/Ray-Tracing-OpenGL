# Ray-Tracing-OpenGL

This Project is a Ray Tracer made in C++ using OpenGL Compute Shaders.

The Compute Shaders are in Shaders/Compute_Shaders/

> NOTE: These Compute Shaders contain include statements like #include "...", 
> This is **NOT** a feature of OpenGL, it is parsed by **OGL::Shader** to be able to include.
> The parsed file is stored in Cube_Shitft directory.

The Project uses the following Libraries:
 - OpenGL
 - SFML
 - glm

The Project Contains the following Self-Made Libraries:
 - GL: A library to handle OpenGL code.
 - RT: The Ray-Tracing Lib.
