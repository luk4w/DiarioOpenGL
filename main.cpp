#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "camera.h"
#include "model.h"

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

    // Inverter as texturas carregadas no eixo y
    stbi_set_flip_vertically_on_load(true);

    // Habilitar teste do buffer de profundidade
    glEnable(GL_DEPTH_TEST);

    Shader shaderModel("shaders/model_vertex.glsl", "shaders/model_fragment.glsl");
    Shader shaderLamp("shaders/lamp_vertex.glsl", "shaders/lamp_fragment.glsl");

    // Carregar os modelos
    Model backpack("models/backpack/backpack.obj");
    Model cube("models/cube/cube.obj");

    // Posição da lâmpada
    glm::vec3 lampPosition(0.0f, 0.0f, 4.0f);

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

        // Projection Matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        // View Matrix
        glm::mat4 view = camera.getViewMatrix();

        // Model Matrix
        glm::mat4 model = glm::mat4(1.0f);

        // Usar o Shader Program do modelo
        shaderModel.use();
        shaderModel.setVec3("viewPos", camera.position);
        shaderModel.setFloat("material.shininess", 32.0f);

        // Luz direcional
        shaderModel.setVec3("directionalLight.direction", -0.2f, -1.0f, -0.3f);
        shaderModel.setVec3("directionalLight.ambient", 0.05f, 0.05f, 0.05f);
        shaderModel.setVec3("directionalLight.diffuse", 0.4f, 0.4f, 0.4f);
        shaderModel.setVec3("directionalLight.specular", 0.5f, 0.5f, 0.5f);

        // Ponto de luz
        shaderModel.setVec3("pointLight.position", lampPosition);
        shaderModel.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
        shaderModel.setVec3("pointLight.diffuse", 1.0f, 1.0f, 1.0f);
        shaderModel.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
        shaderModel.setFloat("pointLight.constant", 1.0f);
        shaderModel.setFloat("pointLight.linear", 0.09f);
        shaderModel.setFloat("pointLight.quadratic", 0.032f);

        // Holofote
        shaderModel.setVec3("spotLight.position", camera.position);
        shaderModel.setVec3("spotLight.direction", camera.front);
        shaderModel.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        shaderModel.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        shaderModel.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        shaderModel.setFloat("spotLight.constant", 1.0f);
        shaderModel.setFloat("spotLight.linear", 0.09f);
        shaderModel.setFloat("spotLight.quadratic", 0.032f);
        shaderModel.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shaderModel.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // Desenhar a mochila
        shaderModel.setMat4("projection", projection);
        shaderModel.setMat4("view", view);
        shaderModel.setMat4("model", model);
        shaderModel.setMat3("normalMatrix", glm::transpose(glm::inverse(model)));
        backpack.draw(shaderModel);

        // Desenhar a lâmpada
        shaderLamp.use();
        shaderLamp.setMat4("projection", projection);
        shaderLamp.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        model = glm::translate(model, lampPosition);
        shaderLamp.setMat4("model", model);
        cube.draw(shaderLamp);
       
        // Trazer os "back buffers" para frente
        glfwSwapBuffers(window);
        // Processar todos os eventos pendentes
        glfwPollEvents();
    }

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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(UPWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.processKeyboard(DOWNWARD, deltaTime);
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