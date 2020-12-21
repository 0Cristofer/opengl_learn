#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        char* message;

        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);

        const char* shaderTypeName = type == GL_VERTEX_SHADER ? "Vertex shader" : "Fragment shader";
        std::cout << "Failed to compile "<< shaderTypeName << ": " << message << std::endl;

        glDeleteShader(id);
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
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) //Glew init precisa ser chamado depois de criar o contexto
        return -1;

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {
            -0.5f, -0.5,
            0.0f, 0.5f,
            0.5f, -0.5f
    };

    // buffer id é o "ponteiro" para a memória requisitada na GPU
    unsigned int buffer_id;
    // Cria o buffer e seta o id
    glGenBuffers(1, &buffer_id);
    // seta o estado do opengl para utilizar o id criado e o tipo dessa memória (buffer array).
    // dar bind significa que toda operação daqui pra frente utilizará esse id, ou seja, estamos "ativando" esse id
    // A partir daqui, a ordem dessas instruções não importa de verdade, pois estamos num estado definido
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    // envia os dados para a gpu, especificando a quantidade e a maneira que esse dado será utilizado.
    // static é colocado uma vez e não é mais alterado
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // especifica os atributos de cada vértice que serão utilizados pelo shader
    // índice do atributo, quantidade de elementos, se é normalizado, tipo do atributo, tamanho em bytes do atributo
    // tamanho em bytes de cada vértice, distância em bytes para chegar neste atributo a partir do começo do vertice
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    // Habilita um atributo, baseado no seu índice
    glEnableVertexAttribArray(0);

    ShaderProgramSource src = ParseShader("../../../opengl_proj/res/shaders/basic.shader"); // caminho começa no .exe dentro de build/bin
    unsigned int shader = CreateShader(src.VertexSource, src.FragmentSource);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3); // desenha o estado atual do opengl, que nesse caso é o buffer (por causa do bind)

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}