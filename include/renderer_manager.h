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
    void render(std::vector<Model>* models);

private:
    void configureLighting(glm::vec3 lampPosition);
    Camera* camera;
    float width, height;
    Shader shaderModel;
    Shader shaderLamp;
};

#endif