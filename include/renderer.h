#ifndef RENDERER_H
#define RENDERER_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "scene.h"

class Renderer
{
public:
    Renderer(Camera* camera, int width, int height);
    void initialize();
    void drawScene(Scene& scene);
    void toggleSpotlight();

private:
    void setLighting(std::vector<glm::vec3> & lightPositions);
    Camera* camera;
    bool spotlightState = false;
    int width, height;
    Shader shaderModel;
    Shader shaderLamp;

};

#endif