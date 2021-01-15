//
// Created by crist on 14/01/2021.
//

#ifndef OPENGL_LEARN_TESTTEXTURE2D_HPP
#define OPENGL_LEARN_TESTTEXTURE2D_HPP

#include "Test.hpp"
#include "../vendor/glm/glm.hpp"
#include "../VertexArray.hpp"
#include "../IndexBuffer.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"

namespace Test
{
    class TestTexture2D : public Test
    {

    public:
        TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexBuffer> m_Vbo;
        std::unique_ptr<VertexArray> m_Vao;
        std::unique_ptr<IndexBuffer> m_Ibo;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj, m_InitialViewPos, m_InitialModelPos, m_InitialModel2Pos, m_CurrentModelPos{}, m_CurrentModel2Pos{};
        glm::vec3 m_ModelTranslation, m_Model2Translation, m_ViewTranslation;
    };
}


#endif //OPENGL_LEARN_TESTTEXTURE2D_HPP
