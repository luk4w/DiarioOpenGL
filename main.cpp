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
unsigned int loadTexture(char const *path);

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
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

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

    glm::vec3 pointLightPositions[] =
    {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribuir ponteiros para as normais do VBO do cubo
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Atribuir ponteiros para as posições de texturas do VBO do cubo
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Lamp Vertex Array Object
    unsigned int lampVAO;
    glGenVertexArrays(1, &lampVAO);
    // Vincular lampVAO
    glBindVertexArray(lampVAO);
    // Atribuir ponteiros para os vertices do VBO do cubo, e pular as normais e as posições de texturas
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Desvincular VBO e VAO para não modificar acidentalmente
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Habilitar teste do buffer de profundidade
    glEnable(GL_DEPTH_TEST);

    // Carregar texturas
    unsigned int diffuseMap = loadTexture("textures/container.png");
    unsigned int specularMap = loadTexture("textures/container_specular.png");
    shaderCube.use(); 
    shaderCube.setInt("material.diffuse", 0);
    shaderCube.setInt("material.specular", 1);

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

        // Definir a posição de visualização
        shaderCube.setVec3("viewPos", camera.position);

        // Definir o brilho do material
        shaderCube.setFloat("material.shininess", 32.0f);

        // Luz direcional
        shaderCube.setVec3("directionalLight.direction", -0.2f, -1.0f, -0.3f);
        shaderCube.setVec3("directionalLight.ambient", 0.05f, 0.05f, 0.05f);
        shaderCube.setVec3("directionalLight.diffuse", 0.4f, 0.4f, 0.4f);
        shaderCube.setVec3("directionalLight.specular", 0.5f, 0.5f, 0.5f);

        // Ponto de luz 1
        shaderCube.setVec3("pointLights[0].position", pointLightPositions[0]);
        shaderCube.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        shaderCube.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        shaderCube.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        shaderCube.setFloat("pointLights[0].constant", 1.0f);
        shaderCube.setFloat("pointLights[0].linear", 0.09f);
        shaderCube.setFloat("pointLights[0].quadratic", 0.032f);

        // Ponto de luz 2
        shaderCube.setVec3("pointLights[1].position", pointLightPositions[1]);
        shaderCube.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        shaderCube.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        shaderCube.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        shaderCube.setFloat("pointLights[1].constant", 1.0f);
        shaderCube.setFloat("pointLights[1].linear", 0.09f);
        shaderCube.setFloat("pointLights[1].quadratic", 0.032f);

        // Ponto de luz 3
        shaderCube.setVec3("pointLights[2].position", pointLightPositions[2]);
        shaderCube.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        shaderCube.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        shaderCube.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        shaderCube.setFloat("pointLights[2].constant", 1.0f);
        shaderCube.setFloat("pointLights[2].linear", 0.09f);
        shaderCube.setFloat("pointLights[2].quadratic", 0.032f);

        // Ponto de luz 4
        shaderCube.setVec3("pointLights[3].position", pointLightPositions[3]);
        shaderCube.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        shaderCube.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        shaderCube.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        shaderCube.setFloat("pointLights[3].constant", 1.0f);
        shaderCube.setFloat("pointLights[3].linear", 0.09f);
        shaderCube.setFloat("pointLights[3].quadratic", 0.032f);

        // Projection Matrix
        glm::mat4 projection = glm::mat4(1.0f);  
        projection = glm::perspective(glm::radians(camera.fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        shaderCube.setMat4("projection", projection);

        // View Matrix
        glm::mat4 view = camera.getViewMatrix();
        shaderCube.setMat4("view", view);

        // Model Matrix
        glm::mat4 model = glm::mat4(1.0f);

        // Vincular textura da iluminação difusa
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        // Vincular textura da iluminação especular
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        
        // Vincular Vertex Array Object
        glBindVertexArray(cubeVAO);

        // Desenhar os cubos
        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderCube.setMat4("model", model);
            shaderCube.setMat3("normalMatrix", glm::transpose(glm::inverse(model)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Desenhar a lâmpada
        shaderLamp.use();
        shaderLamp.setMat4("projection", projection);
        shaderLamp.setMat4("view", view);
        glBindVertexArray(lampVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
             model = glm::mat4(1.0f);
             model = glm::translate(model, pointLightPositions[i]);
             model = glm::scale(model, glm::vec3(0.2f));
             shaderLamp.setMat4("model", model);
             glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
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

unsigned int loadTexture(char const *path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        unsigned int format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Falha ao carregar textura " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}