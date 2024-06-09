#include "scene.h"
#include <iostream>

Scene::Scene()
{
}

void Scene::initialize()
{
    objectManager.loadModels();
}

void Scene::addObject(const std::string &name, const glm::vec3 &position,
                      const glm::vec3 &scale, const Rotation &rotation)
{
    Model *model = objectManager.getModel(name);
    if (model == nullptr)
    {
        std::cerr << "Erro ao adicionar model '" << name << "'." << std::endl;
        return;
    }
    else
    {
        Object obj(objectManager.getModel(name), objects.size(), position, scale, rotation);
        objects.push_back(obj);
    }
}

void Scene::addObject(const std::string &name)
{
    Object obj(objectManager.getModel(name), objects.size());
    objects.push_back(obj);
}

void Scene::addLight(const std::string &name, const glm::vec3 &position,
                     const glm::vec3 &scale, const Rotation &rotation, bool isOn)
{
    Model *model = objectManager.getModel(name);
    if (model == nullptr)
    {
        std::cerr << "Erro ao adicionar model '" << name << "'." << std::endl;
        return;
    }
    else
    {
        LightObject obj(objectManager.getModel(name), lights.size(), position, scale, rotation, isOn);
        lights.push_back(obj);
    }
}

void Scene::addLight(const std::string &name)
{
    LightObject obj(objectManager.getModel(name), lights.size());
    lights.push_back(obj);
}

void Scene::remove(unsigned int id)
{
    objects.erase(objects.begin() + id);
    for (unsigned int i = id; i < objects.size(); i++)
    {
        objects[i].setId(i);
    }
}

void Scene::update(const float *deltaTime)
{
    this->accumulatedTime += *deltaTime;
    lights[0].setPosition(glm::sin(accumulatedTime) * 4, lights[0].getPosition().y, glm::cos(accumulatedTime) * 4);
}