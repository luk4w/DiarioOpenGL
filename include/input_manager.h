#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "camera.h"
#include <GLFW/glfw3.h>

class InputManager
{
public:
    InputManager(Camera *camera) : camera(camera), firstMouse(true), lastX(0), lastY(0) {}

    void processInput(GLFWwindow *window, float deltaTime);
    void mouseCallback(GLFWwindow *window, double xpos, double ypos);
    void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

private:
    Camera *camera;
    bool firstMouse;
    float lastX, lastY;
};

#endif