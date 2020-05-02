//
// Created by Novak on 4/24/2020.
//

#ifndef EAGLE_PHYSICSSYSTEM_H
#define EAGLE_PHYSICSSYSTEM_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/Sphere.h>
#include <eagle/application/components/Rigidbody.h>
#include <eagle/application/components/Box.h>

EG_RAYTRACER_BEGIN

class PhysicsSystem : public entityx::System<PhysicsSystem>, public entityx::Receiver<PhysicsSystem> {
public:
    virtual void configure(entityx::EntityManager &entities, entityx::EventManager &events) override;
    virtual void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    void receive(const entityx::ComponentAddedEvent<Rigidbody>& ev);
private:
    void update_physics(entityx::EntityManager &entities, entityx::EventManager &events, float dt);
};

EG_RAYTRACER_END

#endif //EAGLE_PHYSICSSYSTEM_H
