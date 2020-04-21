//
// Created by Novak on 09/04/2020.
//

#ifndef EAGLE_DIRECTIONALLIGHT_H
#define EAGLE_DIRECTIONALLIGHT_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

struct DirectionalLight {
    glm::vec3 direction;
    float intensity = 1.0f;
};

struct OnLightUpdate {
    OnLightUpdate(const DirectionalLight& light) : light(light) {}
    const DirectionalLight& light;
};

EG_RAYTRACER_END

#endif //EAGLE_DIRECTIONALLIGHT_H
