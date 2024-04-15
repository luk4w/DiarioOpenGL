#ifndef ENGINE_H
#define ENGINE_H

#include "window_manager.h"
#include "input_manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"

class Engine
{
public:
    Engine(const std::string name, int width, int height);
    bool initialize();
    void run();

private:
    void update(const float * deltaTime);
    void render();

    Camera camera;
    WindowManager windowManager;
    Renderer renderer;
    InputManager inputManager;
    Scene scene;
    glm::vec3 lampPosition;
    float accumulatedTime = 0.0f;
};

#endif