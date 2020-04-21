//
// Created by Novak on 11/04/2020.
//

#ifndef EAGLE_SPHERE_H
#define EAGLE_SPHERE_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

struct Sphere {
    float radius;
    glm::vec3 albedo;
    glm::vec3 specular;
};

EG_RAYTRACER_END

#endif //EAGLE_SPHERE_H
