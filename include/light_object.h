#ifndef LIGHT_OBJECT_H
#define LIGHT_OBJECT_H

#include "object.h"

class LightObject : public Object {
public:
    LightObject(Model* model, ShaderType type, glm::vec3 pos, glm::vec3 sc, glm::vec3 rot, bool isOn = true);
    void toggle();
    bool isOn() const;

private:
    bool lightState;
};

#endif // LIGHT_OBJECT_H