#include "scene.h"

#include <filesystem>

#include <iostream>

Scene::Scene()
{
}

void Scene::loadModels()
{
    // Carregar os modelos
    Model bp("models/backpack/backpack.obj");
    bp.setShaderType(BASIC_SHADER);
    models.push_back(bp);

    bp.setPosition(glm::vec3(0.0f, 4.0f, 0.0f));
    models.push_back(bp);

    bp.setPosition(glm::vec3(0.0f, 8.0f, 0.0f));
    models.push_back(bp);

    Model cube("models/cube/cube.obj");
    cube.setShaderType(LAMP_SHADER);
    cube.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
    cube.setScale(glm::vec3(0.2f, 0.2f, 0.2f));
    models.push_back(cube);
   
}

void Scene::addObject(const Model &model)
{
    models.push_back(model);
}

void Scene::removeObject(const Model &model)
{
    
}

void Scene::update(float deltaTime)
{
    // Atualize o estado de cada modelo, se necessário
    // Por exemplo, atualize animações, física, etc.
}

void Scene::drawModels(RendererManager &renderer)
{
    renderer.render(&models);
}
