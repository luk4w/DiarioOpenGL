#include "object.h"

Object::Object(Model *model, glm::vec3 pos, glm::vec3 sc, Rotation rot) 
: position(pos), scale(sc), rotation(rot), model(model) 
{
}
