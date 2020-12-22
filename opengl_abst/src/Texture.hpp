//
// Created by crist on 22/12/2020.
//

#ifndef OPENGL_LEARN_TEXTURE_HPP
#define OPENGL_LEARN_TEXTURE_HPP

#include "Renderer.hpp"

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_Filepah;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& filepath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
};


#endif //OPENGL_LEARN_TEXTURE_HPP
