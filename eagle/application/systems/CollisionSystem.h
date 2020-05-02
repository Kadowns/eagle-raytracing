//
// Created by Novak on 5/2/2020.
//

#ifndef EAGLE_COLLISIONSYSTEM_H
#define EAGLE_COLLISIONSYSTEM_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/PhysicsSettings.h>
#include <eagle/application/components/Rigidbody.h>
#include <eagle/application/components/Sphere.h>
#include <eagle/application/components/Box.h>

EG_RAYTRACER_BEGIN

class CollisionSystem : public entityx::System<CollisionSystem>, public entityx::Receiver<CollisionSystem> {
private:
    struct SphereBody {
        SphereBody(Rigidbody& rigidbody, Sphere& sphere) :  rigidbody(rigidbody), sphere(sphere) {}
        Rigidbody& rigidbody;
        Sphere& sphere;
    };
    struct BoxBody {
        BoxBody(Rigidbody& rigidbody, Box& box) :  rigidbody(rigidbody), box(box) {}
        Rigidbody& rigidbody;
        Box& box;
    };
public:
    virtual void configure(entityx::EntityManager &entities, entityx::EventManager &events) override;
    virtual void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    void receive(const OnPhysicsUpdate& ev);
private:
    void collision_with_floor(const SphereBody &b);
    void collision_with_floor(const BoxBody& b);
    float collides(const SphereBody& b1, const SphereBody& b2);
    void resolve_collision(SphereBody& b1, SphereBody&b2, float penetration);
    void positional_correction(Rigidbody &rigidbody, const glm::vec3& normal, float penetration, float invMass, float invMassSum);
    void apply_impulse(Rigidbody& rigidbody, const glm::vec3& impulse, const glm::vec3& contactPoint);
};

EG_RAYTRACER_END

#endif //EAGLE_COLLISIONSYSTEM_H
