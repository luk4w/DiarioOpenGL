#ifndef SCENE_H
#define SCENE_H

#include "renderer_manager.h"

class Scene
{
public:
    Scene();
    void addObject(const Model &model);
    void removeObject(const Model &model);
    void draw(RendererManager &renderer, glm::vec3 lightPosition);
    void update();
    void loadModels();
    std::vector<Model> models;
};

#endif // SCENE_H

// posso colocar ID no model e usar um map pra guardar os models
// reutilizar o código do renderer manager
