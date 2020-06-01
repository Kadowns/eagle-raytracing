//
// Created by Novak on 08/05/2020.
//

#include <eagle/application/systems/physics/collision/CollisionSolver.h>

EG_RAYTRACER_BEGIN

CollisionSolver::CollisionSolver(std::list<Collision> &collisions) : m_collisions(collisions) {

}

void CollisionSolver::pre_solve(float dt) {

    for (auto& collision : m_collisions) {

        glm::vec3 v1 = collision.rbA->velocity;
        glm::vec3 w1 = collision.rbA->angularVelocity;
        glm::vec3 v2 = collision.rbB->velocity;
        glm::vec3 w2 = collision.rbB->angularVelocity;

        for (auto& contact : collision.contacts) {
            // Precalculate JM^-1JT for contact and friction constraints
            glm::vec3 r1Cn = glm::cross( contact.rA, collision.normal );
            glm::vec3 r2Cn = glm::cross( contact.rB, collision.normal );
            float nm = collision.rbA->inverseMass + collision.rbB->inverseMass;
            float tm[ 2 ];
            tm[ 0 ] = nm;
            tm[ 1 ] = nm;

            nm += glm::dot(r1Cn, collision.rbA->inverseInertiaWorld * r1Cn) + glm::dot(r2Cn, collision.rbB->inverseInertiaWorld * r2Cn);
            contact.normalMass = nm != 0.0f ? 1 / nm : 0.0f;//inverse mass
            // Precalculate bias factor
            contact.bias = -0.2f * (1.0  / dt) * std::min(0.0f, contact.penetration + 0.05f );
            //adicionar prewarm (provavelmente precisa levar em consideração a colisão antiga)
            glm::vec3 P = collision.normal * contact.normalImpulse;


            if (collision.rbA->mode == Rigidbody::Mode::DYNAMIC){
                v1 -= P * collision.rbA->inverseMass;
                w1 -= collision.rbA->inverseInertiaWorld * glm::cross(contact.rA, P);
            }

            if (collision.rbB->mode == Rigidbody::Mode::DYNAMIC) {
                v2 += P * collision.rbB->inverseMass;
                w2 += collision.rbB->inverseInertiaWorld * glm::cross(contact.rB, P);
            }

            // Add in restitution bias
            float dv = glm::dot(v2 + glm::cross(w2, contact.rB) - v1 - glm::cross(w1, contact.rA), collision.normal);

            if (dv < -1.0f)
                contact.bias += -(collision.restitution) * dv;
        }
        collision.rbA->velocity = v1;
        collision.rbA->angularVelocity = w1;
        collision.rbB->velocity = v2;
        collision.rbB->angularVelocity = w2;
    }
}

void CollisionSolver::solve() {
    for (auto& collision : m_collisions) {

        glm::vec3 v1 = collision.rbA->velocity;
        glm::vec3 w1 = collision.rbA->angularVelocity;
        glm::vec3 v2 = collision.rbB->velocity;
        glm::vec3 w2 = collision.rbB->angularVelocity;

        for (auto& contact : collision.contacts) {

            // relative velocity at contact
            glm::vec dv = v2 + glm::cross(w2, contact.rB) - v1 - glm::cross(w1, contact.rA);

            // Normal impulse
            float vn = glm::dot(dv, collision.normal);

            // Factor in positional bias to calculate impulse scalar j
            float lambda = contact.normalMass * (-vn + contact.bias);

            // Clamp impulse
            float tempPN = contact.normalImpulse;
            contact.normalImpulse = std::max(tempPN + lambda, 0.0f);
            lambda = contact.normalImpulse - tempPN;

            glm::vec3 impulse = collision.normal * lambda;

            if (collision.rbA->mode == Rigidbody::Mode::DYNAMIC){
                v1 -= impulse * collision.rbA->inverseMass;
                w1 -= collision.rbA->inverseInertiaWorld * glm::cross(contact.rA, impulse);
            }

            if (collision.rbB->mode == Rigidbody::Mode::DYNAMIC) {
                v2 += impulse * collision.rbB->inverseMass;
                w2 += collision.rbB->inverseInertiaWorld * glm::cross(contact.rB, impulse);
            }
        }
        collision.rbA->velocity = v1;
        collision.rbA->angularVelocity = w1;
        collision.rbB->velocity = v2;
        collision.rbB->angularVelocity = w2;
    }
}

void CollisionSolver::finish() {

}

EG_RAYTRACER_END

