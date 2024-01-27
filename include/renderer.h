#ifndef RENDERER_H
#define RENDERER_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "object.h"

class Renderer
{
public:
    Renderer(Camera* camera, float width, float height);
    void initialize();
    void render(std::vector<Object>* objs, glm::vec3 lightPos);
    void toggleSpotlight();

private:
    void setLighting(glm::vec3 lightPosition);
    Camera* camera;
    bool spotlightState = false;
    float width, height;
    Shader shaderModel;
    Shader shaderLamp;

};

#endif