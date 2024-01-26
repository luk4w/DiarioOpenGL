#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "camera.h"
#include "renderer_manager.h"
#include <GLFW/glfw3.h>

class InputManager
{
public:
    InputManager(Camera *camera, RendererManager *renderer) : camera(camera), renderer(renderer), firstMouse(true), lastX(0), lastY(0) {}
    void processInput(GLFWwindow *window, float deltaTime);
    void mouseCallback(GLFWwindow *window, double xpos, double ypos);
    void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

private:
    Camera *camera;
    RendererManager *renderer;
    bool firstMouse;
    float lastX, lastY;
    double lastToggleTime;
    const double toggleDelay = 0.5;
};

#endif