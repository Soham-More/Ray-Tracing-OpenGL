#ifndef WRAPPERR_H
#define WRAPPERR_H

#include <iostream>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGL
{
    class Init
    {
        public:

            Init()
            {
                if(!glfwInit())
                {
					std::cerr << "GLFW failed to initialize!\n";
                }

                if(glewInit() != GLEW_OK)
                {
					std::cerr << "GLEW failed to initialize!\n";
                }
            }
    };
}

#endif // WRAPPER_OGL_H
