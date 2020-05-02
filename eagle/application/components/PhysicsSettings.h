//
// Created by Novak on 5/2/2020.
//

#ifndef EAGLE_PHYSICSSETTINGS_H
#define EAGLE_PHYSICSSETTINGS_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

struct PhysicsSettings {
    float accumulator = 0;
    float alpha = 0;
    float fixedStep = 0.01f;
};

struct OnPhysicsUpdate {
    OnPhysicsUpdate(entityx::EntityManager& entities, entityx::EventManager& events, float dt) : entities(entities), events(events), dt(dt) {}
    entityx::EntityManager& entities;
    entityx::EventManager& events;
    float dt;
};

EG_RAYTRACER_END

#endif //EAGLE_PHYSICSSETTINGS_H
