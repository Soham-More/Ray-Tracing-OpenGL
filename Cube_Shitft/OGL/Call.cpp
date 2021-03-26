#include "Call.h"

void glClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* fun, const char* fil, int line)
{
    while(GLenum err = glGetError())
    {
        std::cout << "OpenGL Error:" << err << ":" << fun << " in " << fil <<
        " On Line:" << line << std::endl;
        return false;
    }
    return true;
}
