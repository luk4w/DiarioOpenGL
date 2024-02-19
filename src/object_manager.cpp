#include "object_manager.h"

#include <iostream>

void ObjectManager::loadModels()
{
    // Carregar os modelos
    models["backpack"] = new Model("models/backpack/backpack.obj");
    models["cube"] = new Model("models/cube/cube.obj");
    models["plane"] = new Model("models/metal_plane/metal_plane.obj");
}

ObjectManager::~ObjectManager()
{
    // Percorrer todos os elementos no mapa e deletar os objetos Model
    for (auto &pair : models)
    {
        delete pair.second;
    }
    models.clear();
}

Model *ObjectManager::getModel(const std::string &name)
{
    auto it = models.find(name);
    if (it != models.end())
        return it->second;
    else
        return nullptr;
}