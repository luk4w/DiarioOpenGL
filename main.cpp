#include "window_manager.h"
#include "renderer_manager.h"
#include "camera.h"
#include "input_manager.h"
#include "scene.h"

#include <iostream>
using std::cout;
using std::endl;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
RendererManager renderer(&camera, WIDTH, HEIGHT);
InputManager input(&camera, &renderer);

// Temporizador
float deltaTime = 0.0f;
float lastTime = 0.0f;

int main()
{
    WindowManager windowManager("DiarioOpenGL", WIDTH, HEIGHT);
    if (!windowManager.initialize())
        return -1;

    renderer.initialize();

    glfwSetCursorPosCallback(windowManager.getWindow(), [](GLFWwindow *window, double xpos, double ypos) { input.mouseCallback(window, xpos, ypos); });
    glfwSetScrollCallback(windowManager.getWindow(), [](GLFWwindow *window, double xoffset, double yoffset) { input.scrollCallback(window, xoffset, yoffset); });
    glfwSetInputMode(windowManager.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Scene scene;
    scene.addObject("backpack");
    scene.addObject("backpack", glm::vec3(-8.0f, 0.0f, 0.0f));
    scene.addObject("backpack", glm::vec3(8.0f, 0.0f, 0.0f));
    
    glm::vec3 lampPosition =glm::vec3(0.0f, 1.0f, 0.0f);
    scene.addObject("cube", lampPosition, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f), LAMP_SHADER);

    while (!glfwWindowShouldClose(windowManager.getWindow()))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Mover a iluminacao da lâmpada ao redor das mochilas ao longo do tempo
        lampPosition.x = glm::sin(currentTime) * 4;
        lampPosition.z = glm::cos(currentTime) * 4;

        // Atualizar posicao do modelo na cena
        scene.objects[3].setPosition(lampPosition);
        input.processInput(windowManager.getWindow(), deltaTime);
        scene.draw(renderer, lampPosition);

        windowManager.swapBuffers();
        windowManager.pollEvents();
    }

    return 0;
}