//
// Created by crist on 21/12/2020.
//

#ifndef OPENGL_LEARN_VERTEXBUFFER_HPP
#define OPENGL_LEARN_VERTEXBUFFER_HPP

class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

#endif //OPENGL_LEARN_VERTEXBUFFER_HPP
