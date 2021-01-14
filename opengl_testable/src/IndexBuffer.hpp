//
// Created by crist on 21/12/2020.
//

#ifndef OPENGL_LEARN_INDEXBUFFER_HPP
#define OPENGL_LEARN_INDEXBUFFER_HPP

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};

#endif //OPENGL_LEARN_INDEXBUFFER_HPP
