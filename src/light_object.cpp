#include "light_object.h"

LightObject::LightObject(Model *model, ShaderType type, glm::vec3 pos, glm::vec3 sc, glm::vec3 rot, bool isOn)
    : Object(model, type, pos, sc, rot), lightState(isOn) {}

void LightObject::toggle()
{
    lightState = !lightState;
}

bool LightObject::isOn() const
{
    return lightState;
}
