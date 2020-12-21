//
// Created by crist on 21/12/2020.
//

#ifndef OPENGL_LEARN_RENDERER_HPP
#define OPENGL_LEARN_RENDERER_HPP

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(glFunc) GLClearError();\
glFunc;\
ASSERT(GLLogCall(#glFunc, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif //OPENGL_LEARN_RENDERER_HPP
