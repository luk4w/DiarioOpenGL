#ifndef SCENE_H
#define SCENE_H

#include "renderer_manager.h"
#include "object_manager.h"
#include "object.h"

class Scene
{
private:
    ObjectManager objectManager;

public:
    Scene();
    void addObject(const std::string &name, ShaderType shaderType,
        const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation);
    void addObject(const std::string &name);
    void removeObject(const Object &obj);
    void draw(RendererManager &renderer, glm::vec3 lightPosition);
    void update();
    std::vector<Object> objects;
};

#endif // SCENE_H
