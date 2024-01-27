#include "engine.h"
#include <iostream>

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
    scene.addObject("backpack");
    scene.addObject("backpack", glm::vec3(-8.0f, 0.0f, 0.0f));
    scene.addObject("backpack", glm::vec3(8.0f, 0.0f, 0.0f));

    lampPosition = glm::vec3(0.0f, 1.0f, 0.0f);
    scene.addObject("cube", lampPosition, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f), LAMP_SHADER);

    return true;
}

void Engine::run()
{
    float deltaTime = 0.0f;
    float lastTime = 0.0f;

    while (!windowManager.shouldClose())
    {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        deltaTime = std::min(deltaTime, 0.05f);
        lastTime = currentTime;

        update(deltaTime);
        render(lampPosition);
    }
}

void Engine::update(float deltaTime)
{
    // Variavel para mover objetos indepentente da taxa de atualização
    accumulatedTime += deltaTime;
    // Gerenciar a entrada de mouse e teclado
    inputManager.processInput(windowManager.getWindow(), deltaTime);

    // Mover a iluminacao da lâmpada ao redor das mochilas ao longo do tempo
    lampPosition.x = glm::sin(accumulatedTime) * 4;
    lampPosition.z = glm::cos(accumulatedTime) * 4;
}

void Engine::render(glm::vec3 lampPosition)
{
    // Atualizar posicao do modelo na cena
    scene.objects[3].setPosition(lampPosition); // Criar classe para gerenciar a iluminação
    scene.draw(renderer, lampPosition);

    windowManager.swapBuffers();
    windowManager.pollEvents();
}
