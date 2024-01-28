#ifndef LIGHT_OBJECT_H
#define LIGHT_OBJECT_H

#include "object.h"

class LightObject : public Object
{
public:
    LightObject(Model *model, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 sc = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f), bool isOn = true);
    void toggle();
    bool isOn() const;

private:
    bool lightState;
};

#endif // LIGHT_OBJECT_H