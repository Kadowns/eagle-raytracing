//
// Created by Novak on 5/2/2020.
//

#ifndef EAGLE_COLLISIONSYSTEM_H
#define EAGLE_COLLISIONSYSTEM_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/physics/PhysicsSettings.h>
#include <eagle/application/components/physics/Rigidbody.h>
#include <eagle/application/components/physics/Collider.h>
#include <eagle/application/systems/physics/collision/Collision.h>

EG_RAYTRACER_BEGIN

class CollisionSystem : public entityx::System<CollisionSystem>, public entityx::Receiver<CollisionSystem> {
public:
    struct Body {
        Body(Rigidbody& rigidbody, Collider& collider) :  rigidbody(rigidbody), collider(collider) {}
        Rigidbody& rigidbody;
        Collider& collider;
    };
public:
    virtual void configure(entityx::EntityManager &entities, entityx::EventManager &events) override;
    virtual void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    void receive(const OnPhysicsUpdate& ev);
    void receive(const entityx::ComponentAddedEvent<Collider> &ev);
};

EG_RAYTRACER_END

#endif //EAGLE_COLLISIONSYSTEM_H
