#include "engine.h"
#include <iostream>
#include <sstream>

Engine::Engine(const std::string name, int width, int height)
    : camera(glm::vec3(0.0f, 0.0f, 8.0f)), windowManager(name, width, height),
      renderer(&camera, windowManager.getWidth(), windowManager.getHeight()),
      inputManager(&camera, &renderer)
{
}

bool Engine::initialize()
{
    if (!windowManager.initialize())
        return false;

    renderer.initialize();
    inputManager.configureCallbacks(windowManager.getWindow());
    scene.initialize();

    // Inserir objetos na cena
    scene.addObject("plane", glm::vec3(-4.0f, -2.0f, 0.0f));
    Rotation rot = {90.0f, glm::vec3(0.0f, 1.0f, 0.0f)};
    scene.addObject("backpack", glm::vec3(-6.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f), rot);

    scene.addObject("backpack", glm::vec3(0.0f, 2.0f, -6.0f));

    lampPosition = glm::vec3(0.0f, 1.0f, 0.0f);
    scene.addLight("cube", lampPosition, glm::vec3(0.2f));

    glm::vec3 lampPosition2 = glm::vec3(-10.0f, 0.0f, 0.0f);
    scene.addLight("cube", lampPosition2, glm::vec3(0.2f));

    return true;
}

void Engine::run()
{
    float deltaTime = 0.0f;
    float lastTime = 0.0f;

    int framesSinceLastFPS = 0;
    float timeSinceLastFPS = 0.0f;

    while (!windowManager.shouldClose())
    {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;

        framesSinceLastFPS++;
        timeSinceLastFPS += deltaTime;

        // Calcular o FPS a cada segundo
        if (timeSinceLastFPS >= 1.0f)
        {
            float fps = framesSinceLastFPS / timeSinceLastFPS;
            std::stringstream ss;
            ss << windowManager.getTitle() << " " << static_cast<int>(fps) << " FPS";
            glfwSetWindowTitle(windowManager.getWindow(), ss.str().c_str());

            framesSinceLastFPS = 0;
            timeSinceLastFPS = 0.0f;
        }
        
        lastTime = currentTime;

        update(&deltaTime);
        render();
    }
}

void Engine::update(const float *deltaTime)
{
    // Realizar processamento das entradas
    inputManager.processInput(windowManager.getWindow(), deltaTime);

    // Atualizar cena
    scene.update(deltaTime);
}

void Engine::render()
{
    // Atualizar posicao dos modelos na cena
    renderer.drawScene(scene);
    windowManager.swapBuffers();
    windowManager.pollEvents();
}
