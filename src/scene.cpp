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
    const glm::vec3 &scale,const glm::vec3 &rotation,ShaderType shaderType)
{
    Model *model = objectManager.getModel(name);
    if (model == nullptr)
    {
        std::cerr << "Erro ao adicionar model '" << name << "'." << std::endl;
        return;
    }
    else
    {
        Object obj(objectManager.getModel(name), shaderType, position, scale, rotation);
        objects.push_back(obj);
    }
}

void Scene::addObject(const std::string &name)
{
    Object obj(objectManager.getModel(name));
    objects.push_back(obj);
}

void Scene::addLight(const std::string &name, const glm::vec3 &position,
    const glm::vec3 &scale,const glm::vec3 &rotation,ShaderType shaderType,bool isOn)
{
    Model *model = objectManager.getModel(name);
    if (model == nullptr)
    {
        std::cerr << "Erro ao adicionar model '" << name << "'." << std::endl;
        return;
    }
    else
    {
        LightObject obj(objectManager.getModel(name), shaderType, position, scale, rotation, isOn);
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

void Scene::update()
{
   
}
