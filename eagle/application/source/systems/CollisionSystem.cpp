//
// Created by Novak on 5/2/2020.
//

#include <eagle/application/systems/CollisionSystem.h>
#include <eagle/application/components/Transform.h>

EG_RAYTRACER_BEGIN

void CollisionSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    events.subscribe<OnPhysicsUpdate>(*this);
}

void CollisionSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {

}

void CollisionSystem::receive(const OnPhysicsUpdate &ev) {
    for (auto e1 : ev.entities.entities_with_components<Rigidbody, Sphere>()) {
        Rigidbody &r1 = *e1.component<Rigidbody>();
        Sphere &s1 = *e1.component<Sphere>();
        SphereBody b1(r1, s1);
        collision_with_floor(b1);
        for (auto e2 : ev.entities.entities_with_components<Rigidbody, Sphere>()) {
            if (e1 == e2) {
                continue;
            }

            Rigidbody &r2 = *e2.component<Rigidbody>();
            Sphere &s2 = *e2.component<Sphere>();
            SphereBody b2(r2, s2);
            float penetration = collides(b1, b2);
            if (penetration > 0) {
                resolve_collision(b1, b2, penetration);
            }
        }
    }

    for (auto e : ev.entities.entities_with_components<Rigidbody, Box>()){
        Rigidbody &r1 = *e.component<Rigidbody>();
        Box &b1 = *e.component<Box>();
        BoxBody bb(r1, b1);
        collision_with_floor(bb);
    }
}

float CollisionSystem::collides(const CollisionSystem::SphereBody &b1, const CollisionSystem::SphereBody &b2) {
    float r = b1.sphere.radius + b2.sphere.radius;
    return r - glm::distance(b1.rigidbody.current.position, b2.rigidbody.current.position);
}

void CollisionSystem::resolve_collision(CollisionSystem::SphereBody &b1, CollisionSystem::SphereBody &b2, float penetration) {

    glm::vec3 normal = glm::normalize(b1.rigidbody.current.position - b2.rigidbody.current.position);

    glm::vec3 relativeVelocity = b1.rigidbody.velocity - b2.rigidbody.velocity;

    float velocityAlongNormal = glm::dot(relativeVelocity, normal);
    if (velocityAlongNormal > 0) {
        return;
    }

    float e = std::min(b1.rigidbody.restitution, b2.rigidbody.restitution);

    float inverseMassA = 1 / b1.rigidbody.mass;
    float inverseMassB = 1 / b2.rigidbody.mass;

    float massSum = inverseMassA + inverseMassB;

    float j = (-(1 + e) * velocityAlongNormal) / massSum;

    glm::vec3 impulse = j * normal;

    float ratio = inverseMassA / massSum;

    b1.rigidbody.velocity += ratio * b1.rigidbody.mass * impulse;
    positional_correction(b1.rigidbody, normal, penetration, inverseMassA, massSum);

    ratio = inverseMassB / massSum;
    b2.rigidbody.velocity += ratio * b2.rigidbody.mass * -impulse;
    positional_correction(b2.rigidbody, -normal, penetration, inverseMassB, massSum);
}

void CollisionSystem::collision_with_floor(const CollisionSystem::SphereBody &b) {
    float penetration = b.sphere.radius - b.rigidbody.current.position.y;
    if (penetration <= 0){
        return;
    }

    float velocityAlongNormal = glm::dot(b.rigidbody.velocity, glm::vec3(0, 1, 0));
    if (velocityAlongNormal > 0) {
        return;
    }

    float inverseMass = 1 / b.rigidbody.mass;
    float j = (-(1 + b.rigidbody.restitution) * velocityAlongNormal) / inverseMass;

    glm::vec3 impulse(0, j, 0);
    positional_correction(b.rigidbody, glm::vec3(0, 1, 0),penetration, inverseMass, inverseMass);
    b.rigidbody.velocity += b.rigidbody.mass * impulse;
}

void CollisionSystem::collision_with_floor(const CollisionSystem::BoxBody &b) {
    glm::vec3 r = b.box.radius;
    glm::vec3 p = b.rigidbody.current.position;
    glm::mat3 rot = glm::mat3_cast(b.rigidbody.current.rotation);

    std::array<glm::vec3, 8> vertices = {
            (glm::vec3( -r.x, -r.y, -r.z ) * rot) + p,
            (glm::vec3( -r.x, -r.y,  r.z ) * rot) + p,
            (glm::vec3( -r.x,  r.y, -r.z ) * rot) + p,
            (glm::vec3( -r.x,  r.y,  r.z ) * rot) + p,
            (glm::vec3(  r.x, -r.y, -r.z ) * rot) + p,
            (glm::vec3(  r.x, -r.y,  r.z ) * rot) + p,
            (glm::vec3(  r.x,  r.y, -r.z ) * rot) + p,
            (glm::vec3(  r.x,  r.y,  r.z ) * rot) + p
    };
    float lowestPosition = std::numeric_limits<float>::max();
    uint32_t contactPointIndex = -1;
    for (uint32_t i = 0; i < vertices.size(); i++){

        if (vertices[i].y <= 0 && vertices[i].y < lowestPosition){
            lowestPosition = vertices[i].y;
            contactPointIndex = i;
        }
    }

    if (contactPointIndex == -1){
        return;
    }

    float velocityAlongNormal = glm::dot(b.rigidbody.velocity, glm::vec3(0, 1, 0));
    if (velocityAlongNormal > 0) {
        return;
    }

    glm::vec3 ra = vertices[contactPointIndex] - p;
    glm::vec3 raCrossNormal = glm::cross(ra, glm::vec3(0, 1, 0));

    float inverseMass = 1 / b.rigidbody.mass;
    float inverseMassSum = inverseMass + glm::dot(raCrossNormal, raCrossNormal);
    float j = (-(1 + b.rigidbody.restitution) * velocityAlongNormal) / inverseMassSum;

    glm::vec3 impulse(0, j, 0);
    positional_correction(b.rigidbody, glm::vec3(0, 1, 0), -lowestPosition, inverseMass, inverseMass);
    apply_impulse(b.rigidbody, impulse, ra);
}

void CollisionSystem::positional_correction(Rigidbody &rigidbody, const glm::vec3& normal, float penetration, float invMass, float invMassSum) {
    const float percent = 0.2; // usually 20% to 80%
    const float slop = 0.01; // usually 0.01 to 0.1
    glm::vec3 correction = std::max( penetration - slop, 0.0f ) / invMassSum * percent * normal;
    rigidbody.current.position += invMass * correction;
}

void CollisionSystem::apply_impulse(Rigidbody &rigidbody, const glm::vec3 &impulse, const glm::vec3 &contactPoint) {
    rigidbody.velocity += 1.0f / rigidbody.mass * impulse;
    rigidbody.angularVelocity += glm::cross(contactPoint, -impulse);
}

EG_RAYTRACER_END


