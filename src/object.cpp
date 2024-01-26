#include "object.h"

Object::Object(Model *model, ShaderType ShaderType, glm::vec3 pos, glm::vec3 sc, glm::vec3 rot) 
: shaderType(ShaderType), position(pos), scale(sc), rotation(rot), model(model) 
{
}
