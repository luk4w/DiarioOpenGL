#include "window_manager.h"
#include "renderer_manager.h"
#include "camera.h"
#include "input_manager.h"

#include <iostream>
using std::cout;
using std::endl;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
InputManager inputManager(&camera);

// Temporizador
float deltaTime = 0.0f;
float lastTime = 0.0f;

int main()
{
    WindowManager windowManager("DiarioOpenGL", WIDTH, HEIGHT);
    if (!windowManager.initialize())
        return -1;

    RendererManager renderer(&camera, WIDTH, HEIGHT);
    renderer.initialize();

    glfwSetCursorPosCallback(windowManager.getWindow(), [](GLFWwindow *window, double xpos, double ypos) { inputManager.mouseCallback(window, xpos, ypos); });
    glfwSetScrollCallback(windowManager.getWindow(), [](GLFWwindow *window, double xoffset, double yoffset) { inputManager.scrollCallback(window, xoffset, yoffset); });
    glfwSetInputMode(windowManager.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(windowManager.getWindow()))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        inputManager.processInput(windowManager.getWindow(), deltaTime);

        renderer.render();

        windowManager.swapBuffers();
        windowManager.pollEvents();
    }

    return 0;
}