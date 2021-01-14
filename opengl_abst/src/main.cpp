//
// Created by crist on 21/12/2020.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "Renderer.hpp"
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"

float UpdateColor()
{
    static float r = 0.0f;
    static float increment = 0.05;

    if (r > 1.0f)
        increment = -0.05f;
    else if (r < 0.0f)
        increment = 0.05;

    r += increment;

    return r;
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 720, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Ativa VSync
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) // Glew init precisa ser chamado depois de criar o contexto
        return -1;

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    {
        // Data
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

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;

        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 1080.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::mat4 initial_view_pos = glm::mat4(1.0f);
        glm::mat4 initial_model_pos = glm::mat4(1.0f);
        glm::mat4 initial_model2_pos = glm::mat4(1.0f);

        Shader shader("../../../opengl_basic/res/shaders/basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        Texture texture("../../../opengl_basic/res/textures/brick.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        // Limpa os estados
        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        glm::vec3 model_translation(200, 200, 0);
        glm::vec3 model2_translation(100, 100, 0);
        glm::vec3 view_translation(0, 0, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            renderer.Clear();

            // Início da configuração da geometria que será desenhada nesse frame. todos os binds são aplicados ao draw call atual

            glm::mat4 current_view_pos = glm::translate(initial_view_pos, -view_translation);

            glm::mat4 current_model_pos = glm::translate(initial_model_pos, model_translation);
            glm::mat4 current_model2_pos = glm::translate(initial_model2_pos, model2_translation);

            glm::mat4 mvp = proj * current_view_pos * current_model_pos;
            glm::mat4 mvp2 = proj * current_view_pos * current_model2_pos;

            shader.Bind();
            shader.SetUniform4f("u_Color", UpdateColor(), 0.3f, 0.8f, 1.0f);

            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);

            shader.SetUniformMat4f("u_MVP", mvp2);
            renderer.Draw(va, ib, shader);

            {

                ImGui::SliderFloat3("Model Translation", &model_translation.x, 0.0f, 1080.0f);
                ImGui::SliderFloat3("Model2 Translation", &model2_translation.x, 0.0f, 1080.0f);
                ImGui::SliderFloat3("View Translation", &view_translation.x, 0.0f, 1080.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}