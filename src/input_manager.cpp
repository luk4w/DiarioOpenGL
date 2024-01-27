#include "input_manager.h"

static void mouseCallbackInternal(GLFWwindow *window, double xpos, double ypos);
static void scrollCallbackInternal(GLFWwindow *window, double xoffset, double yoffset);

void InputManager::processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (camera)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->processKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->processKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->processKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->processKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera->processKeyboard(UPWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera->processKeyboard(DOWNWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            double currentTime = glfwGetTime();
            if (currentTime - lastToggleSpotlightTime >= toggleSpotlightDelay)
            {
                renderer->toggleSpotlight();
                lastToggleSpotlightTime = currentTime;
            }
        }
    }
}

void InputManager::mouseCallback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    if (camera)
        camera->processMouseMovement(xoffset, yoffset);
}

void InputManager::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (camera)
        camera->processMouseScroll(static_cast<float>(yoffset));
}


void InputManager::configureCallbacks(GLFWwindow* window)
{
        glfwSetWindowUserPointer(window, this);
        glfwSetCursorPosCallback(window, mouseCallbackInternal);
        glfwSetScrollCallback(window, scrollCallbackInternal);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

static void mouseCallbackInternal(GLFWwindow *window, double xpos, double ypos)
{
    auto inputManager = static_cast<InputManager *>(glfwGetWindowUserPointer(window));
    inputManager->mouseCallback(window, xpos, ypos); 
}

static void scrollCallbackInternal(GLFWwindow *window, double xoffset, double yoffset)
{
    auto inputManager = static_cast<InputManager *>(glfwGetWindowUserPointer(window));
    inputManager->scrollCallback(window, xoffset, yoffset);
}