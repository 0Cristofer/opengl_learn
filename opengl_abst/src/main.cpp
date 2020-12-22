//
// Created by crist on 21/12/2020.
//

#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.hpp"
#include "VertexBufferLayout.hpp"

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

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    {
        // Data
        float positions[] = {
                -0.5f, -0.5f,
                0.5f, -0.5f,
                0.5f, 0.5f,
                -0.5f, 0.5f
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;

        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("../../../opengl_basic/res/shaders/basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        // Limpa os estados
        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            renderer.Clear();

            // Início da configuração da geometria que será desenhada nesse frame. todos os binds são aplicados ao draw call atual

            shader.Bind();
            shader.SetUniform4f("u_Color", UpdateColor(), 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader);

            // Fim

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}