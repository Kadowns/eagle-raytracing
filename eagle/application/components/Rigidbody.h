//
// Created by Novak on 4/24/2020.
//

#ifndef EAGLE_RIGIDBODY_H
#define EAGLE_RIGIDBODY_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

struct Rigidbody {
    struct Transform {
        glm::vec3 position;
        glm::quat rotation;
    };

    Rigidbody() : Rigidbody(1.0f, 0.4f, 0.7f){}
    Rigidbody(float mass, float drag, float restitution) : velocity(0), mass(mass), drag(drag), restitution(restitution) {}
    glm::vec3 velocity;
    glm::vec3 angularVelocity;
    float mass;
    float drag;
    float restitution;
    Transform previous, current;
};

EG_RAYTRACER_END

#endif //EAGLE_RIGIDBODY_H
