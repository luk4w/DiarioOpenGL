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
    float accumulatedTime = 0.0f;
public:
    Scene();

    void initialize();

    void addObject(const std::string &name, const glm::vec3 &position, const glm::vec3 &scale = glm::vec3(1.0f), 
    const Rotation &rotation = {0.0f, glm::vec3(0.0f, 0.0f, 0.0f)});
    void addObject(const std::string &name);

    void addLight(const std::string &name, const glm::vec3 &position, const glm::vec3 &scale = glm::vec3(1.0f), 
    const Rotation &rotation = {0.0f, glm::vec3(0.0f, 0.0f, 0.0f)}, bool isOn = true);
    void addLight(const std::string &name);

    void remove(unsigned int id);
    void update(const float *dt);

    std::vector<Object>& getObjects() { return objects; }
    std::vector<LightObject>& getLights() { return lights; }
};

#endif // SCENE_H
