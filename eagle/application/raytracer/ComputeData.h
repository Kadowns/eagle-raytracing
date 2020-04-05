//
// Created by Novak on 04/04/2020.
//

#ifndef EAGLE_COMPUTEDATA_H
#define EAGLE_COMPUTEDATA_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include "Transform.h"

EG_RAYTRACER_BEGIN

#define MAX_SPHERES 256

struct ComputeData {
    Transform light;
    int maxSphereCount = 100;
    glm::vec2 sphereSizes = glm::vec2(2, 6);
    float spherePlacementRadius = 30.0f;
    float metalPercent = 0.5f;

};


EG_RAYTRACER_END

#endif //EAGLE_COMPUTEDATA_H
