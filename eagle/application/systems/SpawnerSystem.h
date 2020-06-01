//
// Created by Novak on 29/05/2020.
//

#ifndef EAGLE_SPAWNERSYSTEM_H
#define EAGLE_SPAWNERSYSTEM_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

class SpawnerSystem : public entityx::System<SpawnerSystem> {
public:
    virtual void configure(entityx::EntityManager &entities, entityx::EventManager &events) override;

    virtual void
    update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


EG_RAYTRACER_END


#endif //EAGLE_SPAWNERSYSTEM_H
