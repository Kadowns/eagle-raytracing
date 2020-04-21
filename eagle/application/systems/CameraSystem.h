//
// Created by Novak on 09/04/2020.
//

#ifndef EAGLE_CAMERASYSTEM_H
#define EAGLE_CAMERASYSTEM_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

class CameraSystem : public entityx::System<CameraSystem> {
public:
    virtual void configure(entityx::EntityManager &entities, entityx::EventManager &events) override;
    virtual void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
private:
    float clamp_angle(float angle, float min, float max);
};


EG_RAYTRACER_END

#endif //EAGLE_CAMERASYSTEM_H
