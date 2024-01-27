#include "window_manager.h"
#include "renderer.h"
#include "camera.h"
#include "input_manager.h"
#include "scene.h"

#include <iostream>
using std::cout;
using std::endl;

// Temporizador
float deltaTime = 0.0f;
float lastTime = 0.0f;

int main()
{
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    WindowManager wm("DiarioOpenGL", 1280, 720);
    if (!wm.initialize())
        return -1;

    Renderer renderer(&camera, wm.getWidth(), wm.getHeight());
    renderer.initialize();

    InputManager input(&camera, &renderer);
    input.configureCallbacks(wm.getWindow());

    Scene scene;
    scene.addObject("backpack");
    scene.addObject("backpack", glm::vec3(-8.0f, 0.0f, 0.0f));
    scene.addObject("backpack", glm::vec3(8.0f, 0.0f, 0.0f));
    
    glm::vec3 lampPosition =glm::vec3(0.0f, 1.0f, 0.0f);
    scene.addObject("cube", lampPosition, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f), LAMP_SHADER);

    while (!glfwWindowShouldClose(wm.getWindow()))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Mover a iluminacao da lâmpada ao redor das mochilas ao longo do tempo
        lampPosition.x = glm::sin(currentTime) * 4;
        lampPosition.z = glm::cos(currentTime) * 4;

        // Atualizar posicao do modelo na cena
        scene.objects[3].setPosition(lampPosition);
        input.processInput(wm.getWindow(), deltaTime);
        scene.draw(renderer, lampPosition);

        wm.swapBuffers();
        wm.pollEvents();
    }

    return 0;
}