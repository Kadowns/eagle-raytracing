//
// Created by Novak on 04/04/2020.
//

#ifndef EAGLE_SCENEDATA_H
#define EAGLE_SCENEDATA_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

#define MAX_SPHERES 256

struct OnSceneUpdate {
    OnSceneUpdate(entityx::EntityManager& entities) : entities(entities) {}
    entityx::EntityManager& entities;
};

struct SceneData {
    int maxSphereCount = 100;
    glm::vec2 sphereSizes = glm::vec2(2, 6);
    float spherePlacementRadius = 30.0f;
    float metalPercent = 0.5f;
};


EG_RAYTRACER_END

#endif //EAGLE_SCENEDATA_H
