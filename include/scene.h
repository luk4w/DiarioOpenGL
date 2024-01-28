#ifndef SCENE_H
#define SCENE_H

#include "object_manager.h"
#include "object.h"
#include "light_object.h"

class Scene
{
private:
    ObjectManager objectManager;
    std::vector<Object> objects;
    std::vector<LightObject> lights;
public:
    Scene();
    void addObject(const std::string &name, const glm::vec3 &position, const glm::vec3 &scale = glm::vec3(1.0f, 1.0f, 1.0f), 
    const glm::vec3 &rotation = glm::vec3(0.0f, 0.0f, 0.0f), ShaderType shaderType = BASIC_SHADER);
    void addObject(const std::string &name);
    void removeObject(const Object &obj);
    void update();
    void initialize();
    const std::vector<Object>& getObjects() const { return objects; }
    const std::vector<LightObject>& getLights() const { return lights; }
};

#endif // SCENE_H
