//
// Created by Novak on 5/4/2020.
//

#ifndef EAGLE_COLLISION_H
#define EAGLE_COLLISION_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/physics/Collider.h>

EG_RAYTRACER_BEGIN

struct Collision {

    struct Contact{
        glm::vec3 position, rA, rB;
        float penetration;
        float normalMass;
        float bias;
        float normalImpulse;

    };

    Collision(entityx::ComponentHandle<Collider> colA, entityx::ComponentHandle<Collider> colB,
              entityx::ComponentHandle<Rigidbody> rbA, entityx::ComponentHandle<Rigidbody> rbB) :
              colA(colA), colB(colB), rbA(rbA), rbB(rbB){}


    std::vector<Contact> contacts;
    entityx::ComponentHandle<Collider> colA, colB;
    entityx::ComponentHandle<Rigidbody> rbA, rbB;
    glm::vec3 normal;
    float restitution;

    inline operator bool() const {
        return !contacts.empty();
    }

    inline bool operator==(const Collision& rhs) const {
        return (this->colA == rhs.colA && this->colB == rhs.colB) || (this->colA == rhs.colB && this->colB == rhs.colA);
    }
};

EG_RAYTRACER_END

#endif //EAGLE_COLLISION_H
