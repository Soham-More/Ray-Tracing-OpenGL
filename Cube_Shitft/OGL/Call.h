#ifndef CALL_H
#define CALL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>

void glClearError();

bool GLLogCall(const char* fun, const char* fil, int line);

#define Call(x)  glClearError();\
        x;\
        assert(GLLogCall(#x, __FILE__, __LINE__));

#endif // CALL_H
