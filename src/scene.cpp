#include "scene.h"
#include <iostream>

Scene::Scene()
{
    objectManager.loadModels();
}

void Scene::addObject(const std::string &name,
    ShaderType shaderType, const glm::vec3 &position,
    const glm::vec3 &scale,const glm::vec3 &rotation)
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

void Scene::removeObject(const Object &obj)
{
    
}

void Scene::update()
{
   
}

void Scene::draw(RendererManager &renderer, glm::vec3 lightPosition)
{
    renderer.render(&objects, lightPosition);
}
