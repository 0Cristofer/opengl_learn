//
// Created by crist on 21/12/2020.
//

#include <iostream>

#include "Renderer.hpp"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR); // get error retorna um código de erro até não haver mais erros armazenados
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;

        return false;
    }

    return true;
}