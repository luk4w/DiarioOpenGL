#include "light_object.h"

LightObject::LightObject(Model *model, glm::vec3 pos, glm::vec3 sc, glm::vec3 rot, bool isOn)
    : Object(model, pos, sc, rot), lightState(isOn) {}

void LightObject::toggle()
{
    lightState = !lightState;
}

bool LightObject::isOn() const
{
    return lightState;
}
