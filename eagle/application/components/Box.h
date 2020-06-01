//
// Created by Novak on 4/25/2020.
//

#ifndef EAGLE_BOX_H
#define EAGLE_BOX_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

struct Box {
    Box(){}
    Box(const glm::vec3& radius, const glm::vec3& albedo, const glm::vec3& specular) : radius(radius), albedo(albedo), specular(specular) {}
    glm::vec3 radius;
    glm::vec3 albedo;
    glm::vec3 specular;
};

EG_RAYTRACER_END

#endif //EAGLE_BOX_H
