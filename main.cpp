#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#include <iostream>
using std::cout;
using std::endl;

void framebufferSizeCallback(GLFWwindow* window, int width, int height); // Protótipo de função
void processInput(GLFWwindow *window); // Protótipo de função

const unsigned int WIDTH = 800; 
const unsigned int HEIGHT = 600;

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Definir a posição dos cubos no espaço do mundo
    glm::vec3 cubePositions[] =
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Vincular VAO, VBO e EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copiar dados dos vertices para o VBO vinculado
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Atribuir ponteiros para os vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribuir ponteiros para as texuturas
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Textura
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Definir parâmetros de quebra de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Definir parâmetros de filtragem de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Inverter as texturas carregadas no eixo y
    stbi_set_flip_vertically_on_load(true);
    
    // Carregar textura
    int width, height, channels;
    unsigned char *data = stbi_load("textures/wall.jpg", &width, &height, &channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Falha ao carregar textura" << endl;
    }
    stbi_image_free(data);

    // Desvincular VBO e VAO para não modificar acidentalmente
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Habilitar teste do buffer de profundidade
    glEnable(GL_DEPTH_TEST);

    // Projection Matrix
    shaderProgram.use();
    glm::mat4 projection = glm::mat4(1.0f);  
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    shaderProgram.setMat4("projection", projection);

    // Loop de renderização principal
    while (!glfwWindowShouldClose(window))
    {   
        // Realizar comandos por meio do teclado e do mouse
        processInput(window);

        // Especificar os valores de vermelho, verde, azul e alfa, para limpar os buffers de cores
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Definir qual ou quais buffers precisam ser limpos
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Vincular textura
        glBindTexture(GL_TEXTURE_2D, texture);

        // Definir qual Shader Program o OpenGL deve usar
        shaderProgram.use();

        // View Matrix
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        shaderProgram.setMat4("view", view);

        // Vincular Vertex Array Object
        glBindVertexArray(VAO);

        for(unsigned int i = 0; i < 10; i++)
        {
            // Model Matrix
            glm::mat4 model = glm::mat4(1.0f);

            // Transformações
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            
            // Enviar Model Matrix para o Vertex Shader
            shaderProgram.setMat4("model", model);

            // Desenhar triângulos a partir dos vertices
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Trazer os "back buffers" para frente
        glfwSwapBuffers(window);

        // Processar todos os eventos pendentes
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO); // Opcional
    glDeleteBuffers(1, &VBO); // Opcional
    glfwDestroyWindow(window); // Opcional
    glfwTerminate(); // Terminar biblioteca GLFW

    return 0;
} 

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}