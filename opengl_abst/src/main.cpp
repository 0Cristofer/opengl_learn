//
// Created by crist on 21/12/2020.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};


static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;
    while (std::getline(stream, line))
    {
        if (line.find("shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                shaderType = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                shaderType = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)shaderType] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

// Compila um único shader genérico
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        char* message;

        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        message = new char[length];
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        const char* shaderTypeName = type == GL_VERTEX_SHADER ? "Vertex shader" : "Fragment shader";
        std::cout << "Failed to compile "<< shaderTypeName << ": " << message << std::endl;

        GLCall(glDeleteShader(id));
        delete message;
        return 0;
    }

    return id;
}

/**
 * Compila os dois shaders e linka eles em um único programa. Esse processo é feito pelo opengl
 * @param vertexShader String contendo o código cru do shader
 * @param fragmentShader
 * @return
 */
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
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
    window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Ativa VSync
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) //Glew init precisa ser chamado depois de criar o contexto
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

        // VAO é vertex array object e ele armazena as informações de layout (vertex attributes) do vertex buffer
        // e as informações dos índices (ibo) assim, só precisamos vincular (bind) o VAO quando fazer o draw call
        unsigned int vao;
        // Cria um VAO
        GLCall(glGenVertexArrays(1, &vao));
        // Vincula esse VAO
        GLCall(glBindVertexArray(vao));

        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        // Habilita um atributo, baseado no seu índice no VAO
        GLCall(glEnableVertexAttribArray(0));
        // especifica os atributos de cada vértice que serão utilizados pelo shader
        // índice do atributo no VAO, quantidade de elementos, se é normalizado, tipo do atributo, tamanho em bytes do atributo
        // tamanho em bytes de cada vértice, distância em bytes para chegar neste atributo a partir do começo do vertice
        // é também nesse momento que o VAO é ligado ao array buffer atual
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        IndexBuffer ib(indices, 6);

        ShaderProgramSource src = ParseShader(
                "../../../opengl_basic/res/shaders/basic.shader"); // caminho começa no .exe dentro de build/bin
        unsigned int shader = CreateShader(src.VertexSource, src.FragmentSource);
        GLCall(glUseProgram(shader));

        // Configura um uniform, passando o shader que será utilizado e o nome do uniform dentro do shader
        GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        ASSERT(location != -1);
        GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

        // Limpa os estados
        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        float r = 0.0f;
        float increment = 0.05;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            // Início da configuração da geometria que será desenhada nesse frame. todos os binds são aplicados ao draw call atual

            // Ativa o shader
            GLCall(glUseProgram(shader));
            // Uniforms são passados por draw call e são aplicados ao draw call inteiro
            GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

            // Ativa o VAO
            GLCall(glBindVertexArray(vao));
            ib.Bind();

            // desenha os elementos (index buffer); tipo do draw, quantidade de índices, tipo do índice, ponteiro para os índices. Como os índices
            // atuais já estão vinculados, não precisa ser passado
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05;

            r += increment;

            // Fim

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        GLCall(glDeleteProgram(shader));
    }

    glfwTerminate();
    return 0;
}