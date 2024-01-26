#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <glm/glm.hpp>
#include "model.h"

enum ShaderType
{
    BASIC_SHADER,
    LAMP_SHADER,
};


class Object
{
private:
    ShaderType shaderType;
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
public:
    unsigned int id;
    Object(Model *model, ShaderType type = BASIC_SHADER, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 sc = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f));
    
    Model *model;   
    void setShaderType(ShaderType type = BASIC_SHADER) { shaderType = type; }
    ShaderType getShaderType() const { return shaderType; }
    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setScale(const glm::vec3 &sc) { scale = sc; }
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getScale() const { return scale; }
};

#endif