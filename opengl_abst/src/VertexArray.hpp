//
// Created by crist on 21/12/2020.
//

#ifndef OPENGL_LEARN_VERTEXARRAY_HPP
#define OPENGL_LEARN_VERTEXARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
private:
    unsigned int m_RendererId;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};


#endif //OPENGL_LEARN_VERTEXARRAY_HPP
