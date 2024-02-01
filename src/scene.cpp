#include "scene.h"
#include <iostream>

Scene::Scene()
{
}

void Scene::initialize()
{
    objectManager.loadModels();
}

void Scene:: addObject(const std::string &name, const glm::vec3 &position,
    const glm::vec3 &scale,const Rotation &rotation)
{
    Model *model = objectManager.getModel(name);
    if (model == nullptr)
    {
        std::cerr << "Erro ao adicionar model '" << name << "'." << std::endl;
        return;
    }
    else
    {
        Object obj(objectManager.getModel(name), position, scale, rotation);
        objects.push_back(obj);
    }
}

void Scene::addObject(const std::string &name)
{
    Object obj(objectManager.getModel(name));
    objects.push_back(obj);
}

void Scene::addLight(const std::string &name, const glm::vec3 &position,
    const glm::vec3 &scale,const Rotation &rotation, bool isOn)
{
    Model *model = objectManager.getModel(name);
    if (model == nullptr)
    {
        std::cerr << "Erro ao adicionar model '" << name << "'." << std::endl;
        return;
    }
    else
    {
        LightObject obj(objectManager.getModel(name), position, scale, rotation, isOn);
        lights.push_back(obj);
    }
}

void Scene::addLight(const std::string &name)
{
    LightObject obj(objectManager.getModel(name));
    lights.push_back(obj);
}

void Scene::remove(const Object &obj)
{
}

void Scene::update(LightObject &light, glm::vec3 position)
{
    light.setPosition(position);
}