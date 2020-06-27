//
// Created by Novak on 29/05/2020.
//

#ifndef EAGLE_SPAWNER_H
#define EAGLE_SPAWNER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

struct Spawner {
    glm::vec3 rotation;
    glm::vec3 radius = glm::vec3(1);
};

EG_RAYTRACER_END

#endif //EAGLE_SPAWNER_H
