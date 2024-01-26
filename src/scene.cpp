#include "scene.h"

#include <iostream>

Scene::Scene()
{
}

void Scene::loadModels()
{
    // Carregar os modelos
    Model bp("models/backpack/backpack.obj");
    bp.setShaderType(BASIC_SHADER);
    addObject(bp);

    bp.setPosition(glm::vec3(0.0f, 4.0f, 0.0f));
    addObject(bp);

    bp.setPosition(glm::vec3(0.0f, 8.0f, 0.0f));
    addObject(bp);

    Model cube("models/cube/cube.obj");
    cube.setShaderType(LAMP_SHADER);
    cube.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
    cube.setScale(glm::vec3(0.2f, 0.2f, 0.2f));
    addObject(cube);
   
}

void Scene::addObject(const Model &model)
{
    models.push_back(model);
}

void Scene::removeObject(const Model &model)
{
    
}

void Scene::update()
{
   
}

void Scene::draw(RendererManager &renderer, glm::vec3 lightPosition)
{
    renderer.render(&models, lightPosition);
}
