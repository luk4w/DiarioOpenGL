#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include <GLAD/glad.h>
#include "camera.h"
#include "model.h"

class RendererManager
{
public:
    RendererManager(Camera* camera, float width, float height);
    void initialize();
    void render();

private:
    void RendererManager::configureLighting(Shader& shader);
    Camera* camera;
    float width, height;
    std::vector<Model> models;
    Shader shaderModel;
    Shader shaderLamp;

    // Posição da lâmpada
    glm::vec3 lampPosition = glm::vec3(0.0f, 0.0f, 4.0f);
};

#endif