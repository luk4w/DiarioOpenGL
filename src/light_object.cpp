#include "light_object.h"

LightObject::LightObject(Model *model, unsigned int id, glm::vec3 pos,
                         glm::vec3 sc, Rotation rot, bool isOn)
    : Object(model, id, pos, sc, rot), lightState(isOn)
{
}

void LightObject::toggle()
{
    lightState = !lightState;
}

bool LightObject::isOn() const
{
    return lightState;
}
