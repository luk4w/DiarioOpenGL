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
    Engine();
    bool initialize();
    void run();

private:
    void update(float deltaTime);
    void render(glm::vec3 lampPosition);

    Camera camera;
    WindowManager windowManager;
    Renderer renderer;
    InputManager inputManager;
    Scene scene;
    glm::vec3 lampPosition;
    float accumulatedTime = 0.0f;
};

#endif