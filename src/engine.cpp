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
    scene.addObject("backpack", glm::vec3(0.0f, 0.0f, 4.0f));
    Rotation rot = {90.0f, glm::vec3(0.0f, 1.0f, 0.0f)};
    scene.addObject("backpack", glm::vec3(-6.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f), rot);

    scene.addObject("backpack", glm::vec3(0.0f, 2.0f, -6.0f));

    lampPosition = glm::vec3(0.0f, 1.0f, 0.0f);
    scene.addLight("cube", lampPosition, glm::vec3(0.2f));

    glm::vec3 lampPosition2 = glm::vec3(-10.0f, 0.0f, 0.0f);
    scene.addLight("cube", lampPosition2, glm::vec3(0.2f));

    // Remover objeto
    scene.remove(0);

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
        deltaTime = std::min(deltaTime, 0.05f);

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

        update(deltaTime);
        render();
    }
}

void Engine::update(float deltaTime)
{
    // Variavel para mover objetos indepentente da taxa de atualização
    accumulatedTime += deltaTime;
    // Gerenciar a entrada de mouse e teclado
    inputManager.processInput(windowManager.getWindow(), deltaTime);

    // Mover a lâmpada ao redor das mochilas ao longo do tempo
    lampPosition.x = glm::sin(accumulatedTime) * 4;
    lampPosition.z = glm::cos(accumulatedTime) * 4;

    // Atualizar a posicao da lampada
    scene.updateLight(0, lampPosition);
}

void Engine::render()
{
    // Atualizar posicao do modelo na cena
    renderer.drawScene(scene);

    windowManager.swapBuffers();
    windowManager.pollEvents();
}
