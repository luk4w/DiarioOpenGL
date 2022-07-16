#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"

#include <iostream>
using std::cout;
using std::endl;

// Protótipos de função
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int WIDTH = 800; 
const unsigned int HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouseInput = true;
float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;

// Temporizador
float deltaTime = 0.0f;
float lastTime = 0.0f;

// Posição da lâmpada
glm::vec3 lampPosition(1.2f, 1.0f, 2.0f);

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
        glfwTerminate();
        return -1;
    }
    // Definir window como contexto atual da thread de chamada
    glfwMakeContextCurrent(window);
    // Definir função de retorno de chamada para redimensionamento de janela
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    // Definir função de retorno de chamada para o mouse
    glfwSetCursorPosCallback(window, mouseCallback);
    // Definir função de rertorno de chamada para o scroll
    glfwSetScrollCallback(window, scrollCallback);

    // Ativar a captura do mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Verificar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Nao foi possivel carregar o contexto OpenGL!" << endl;
        glfwTerminate();
        return -1;
    }

    Shader shaderCube("shaders/cube_vertex.glsl", "shaders/cube_fragment.glsl");
    Shader shaderLamp("shaders/lamp_vertex.glsl", "shaders/lamp_fragment.glsl");

    // Dados dos vertices dos triângulos
    float vertices[] =
    {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Cube Vertex Array Object
    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);

    // Vincular cubeVAO e VBO
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copiar dados dos vertices para o VBO vinculado
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Atribuir ponteiros para os vertices do VBO do cubo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribuir ponteiros para as normais do VBO do cubo
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Lamp Vertex Array Object
    unsigned int lampVAO;
    glGenVertexArrays(1, &lampVAO);
    // Vincular lampVAO
    glBindVertexArray(lampVAO);
    // Atribuir ponteiros para os vertices do VBO do cubo, e pular as normais
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Desvincular VBO e VAO para não modificar acidentalmente
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Habilitar teste do buffer de profundidade
    glEnable(GL_DEPTH_TEST);

    // Loop de renderização principal
    while (!glfwWindowShouldClose(window))
    {   
        // Lógica do tempo por quadro
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Realizar comandos por meio do teclado e do mouse
        processInput(window);

        // Especificar os valores de vermelho, verde, azul e alfa, para limpar os buffers de cores
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Definir qual ou quais buffers precisam ser limpos
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Definir qual Shader Program o OpenGL deve usar
        shaderCube.use();

        // Definir a cor do cubo e a cor da luz incidente
        shaderCube.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        shaderCube.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
        // Definir a posição da fonte de luz
        shaderCube.setVec3("lightPos", lampPosition);
        // Definir a posição do visualização
        shaderCube.setVec3("viewPos", camera.position); 

        // Projection Matrix
        glm::mat4 projection = glm::mat4(1.0f);  
        projection = glm::perspective(glm::radians(camera.fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        shaderCube.setMat4("projection", projection);

        // View Matrix
        glm::mat4 view = camera.getViewMatrix();
        shaderCube.setMat4("view", view);

        // Vincular Vertex Array Object
        glBindVertexArray(cubeVAO);

        // Model Matrix
        glm::mat4 model = glm::mat4(1.0f);
        shaderCube.setMat4("model", model);
        shaderCube.setMat3("normalMatrix", glm::transpose(glm::inverse(model)));

        // Desenhar cubo
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Definir qual Shader Program o OpenGL deve usar
        shaderLamp.use();
        // Reutilizar Projection e View Matrix
        shaderLamp.setMat4("projection", projection);
        shaderLamp.setMat4("view", view);
        // Definir Model Matrix
        model = glm::mat4(1.0f);
        model = glm::translate(model, lampPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        shaderLamp.setMat4("model", model);
        // Vincular lampVAO
        glBindVertexArray(lampVAO);
        // Desenhar a lâmpada
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Trazer os "back buffers" para frente
        glfwSwapBuffers(window);

        // Processar todos os eventos pendentes
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO); // Opcional
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

    const float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouseInput)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouseInput = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(static_cast<float>(yoffset));
}