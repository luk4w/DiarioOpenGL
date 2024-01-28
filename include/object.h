#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <glm/glm.hpp>
#include "model.h"

struct Rotation
{
    float angle;
    glm::vec3 axis;
};

class Object
{
private:
    Rotation rotation;
    glm::vec3 position;
    glm::vec3 scale;
public:
    unsigned int id;
    Object(Model *model, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 sc = glm::vec3(1.0f, 1.0f, 1.0f), Rotation rot = {0.0f, glm::vec3(0.0f, 0.0f, 0.0f)});
    Model *model;
    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setScale(const glm::vec3 &sc) { scale = sc; }
    void setRotation(const Rotation rot) { rotation = rot; }
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getScale() const { return scale; }
    Rotation getRotation() const { return rotation; }
};

#endif