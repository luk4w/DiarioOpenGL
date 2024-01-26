#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <map>
#include <string>
#include <model.h>

class ObjectManager
{
private:
    std::map<std::string, Model *> models;
public:
    ObjectManager(){};
    ~ObjectManager();
    void loadModels();
    Model * getModel(const std::string &name);
};

#endif