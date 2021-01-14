//
// Created by crist on 21/12/2020.
//

#ifndef OPENGL_LEARN_RENDERER_HPP
#define OPENGL_LEARN_RENDERER_HPP

#include <GL/glew.h>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(glFunc) GLClearError();\
glFunc;\
ASSERT(GLLogCall(#glFunc, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

#endif //OPENGL_LEARN_RENDERER_HPP
