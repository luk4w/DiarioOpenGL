#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class WindowManager
{
public:
    WindowManager(const std::string &title, int width, int height);
    ~WindowManager();

    bool initialize();
    GLFWwindow *getWindow() const;
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    GLFWwindow *window;
    int width;
    int height;
    std::string title;

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};

#endif // WINDOW_MANAGER_H