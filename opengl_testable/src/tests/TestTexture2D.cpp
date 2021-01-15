//
// Created by crist on 14/01/2021.
//

#include "TestTexture2D.hpp"
#include "../vendor/imgui/imgui.h"
#include "../VertexBufferLayout.hpp"
#include "../vendor/glm/ext.hpp"

namespace Test
{
    TestTexture2D::TestTexture2D()
        : m_Proj(glm::ortho(0.0f, 1080.0f, 0.0f, 720.0f, -1.0f, 1.0f)),
          m_InitialViewPos(glm::mat4(1.0f)), m_InitialModelPos(glm::mat4(1.0f)), m_InitialModel2Pos(glm::mat4(1.0f)),
          m_ModelTranslation(200.0f, 200.0f, 0.0f), m_Model2Translation(100.0f, 100.0f, 0.0f), m_ViewTranslation(0.0f, 0.0f, 0.0f)
    {
        float positions[] = {
                0.0f, 0.0f, 0.0f, 0.0f,
                160.0f, 0.0f, 1.0f, 0.0f,
                160.0f, 160.0f, 1.0f, 1.0f,
                0.0f, 160.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        m_Vbo = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;

        layout.Push<float>(2);
        layout.Push<float>(2);

        m_Vao = std::make_unique<VertexArray>();
        m_Vao->AddBuffer(*m_Vbo, layout);

        m_Ibo = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("../../../res/shaders/abst.shader");
        m_Shader->Bind();
        m_Shader->SetUniform1i("u_Texture", 0);

        m_Texture = std::make_unique<Texture>("../../../res/textures/brick.png");

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    void TestTexture2D::OnUpdate(float deltaTime)
    {
        glm::mat4 current_view_pos = glm::translate(m_InitialViewPos, -m_ViewTranslation);

        glm::mat4 current_model_pos = glm::translate(m_InitialModelPos, m_ModelTranslation);
        glm::mat4 current_model2_pos = glm::translate(m_InitialModel2Pos, m_Model2Translation);

        glm::mat4 currentMVP = m_Proj * current_view_pos;

        m_CurrentModelPos = currentMVP * current_model_pos;
        m_CurrentModel2Pos = currentMVP * current_model2_pos;
    }

    void TestTexture2D::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();
        m_Shader->Bind();

        m_Shader->SetUniformMat4f("u_MVP", m_CurrentModelPos);
        renderer.Draw(*m_Vao, *m_Ibo, *m_Shader);

        m_Shader->SetUniformMat4f("u_MVP", m_CurrentModel2Pos);
        renderer.Draw(*m_Vao, *m_Ibo, *m_Shader);
    }

    void TestTexture2D::OnImGuiRender()
    {
        ImGui::SliderFloat3("Model Translation", &m_ModelTranslation.x, 0.0f, 1080.0f);
        ImGui::SliderFloat3("Model2 Translation", &m_Model2Translation.x, 0.0f, 1080.0f);
        ImGui::SliderFloat3("View Translation", &m_ViewTranslation.x, 0.0f, 1080.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
