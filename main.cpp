#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#include <iostream>
using std::cout;
using std::endl;

void framebufferSizeCallback(GLFWwindow* window, int width, int height); // Protótipo de função

const unsigned int WIDTH = 800; 
const unsigned int HEIGHT = 600;

int main()
{
    // Inicializar biblioteca GLFW
    glfwInit();

    // Especificar versão do OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Instanciar GLFWwindow
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "DiarioOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Falha ao criar GLFWwindow!" << endl;
        return -1;
    }
    // Definir window como contexto atual da thread de chamada
    glfwMakeContextCurrent(window);
    // Definir função de retorno de chamada para redimensionamento de janela
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Verificar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Nao foi possivel carregar o contexto OpenGL!" << endl;
        return -1;
    }

    Shader shaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // Vertices dos triângulos
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f, // A
        -0.5, 0.5f, 0.0f, // B
        0.5f, 0.5f, 0.0f,  // C 
        0.5f, -0.5f, 0.0f // D
    };

    unsigned int indices[] =
    {
        0, 1, 3,  // Primeiro triângulo
        1, 2, 3   // Segundo triângulo
    };

    // Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Element Buffer Object
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // Vincular VAO, VBO e EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Copiar dados dos vertices para o VBO vinculado
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Copiar dados dos indices para o EBO vinculado
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atribuir ponteiros para os vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Desvincular VBO e VAO para não modificar acidentalmente
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Loop de renderização principal
    while (!glfwWindowShouldClose(window))
    {
        // Especificar os valores de vermelho, verde, azul e alfa, para limpar os buffers de cores
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Definir qual ou quais buffers precisam ser limpos
        glClear(GL_COLOR_BUFFER_BIT);

        // Definir qual Shader Program o OpenGL deve usar
        shaderProgram.use();
        // Vincular Vertex Array Object
        glBindVertexArray(VAO);
        // Desenhar triângulos a partir dos indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Trazer os "back buffers" para frente
        glfwSwapBuffers(window);

        // Processar todos os eventos pendentes
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO); // Opcional
    glDeleteBuffers(1, &VBO); // Opcional
    glDeleteBuffers(1, &EBO); // Opcional
    glfwDestroyWindow(window); // Opcional
    glfwTerminate(); // Terminar biblioteca GLFW

    return 0;
} 

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}