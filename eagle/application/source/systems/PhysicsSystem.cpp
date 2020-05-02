//
// Created by Novak on 4/24/2020.
//

#include <eagle/application/systems/PhysicsSystem.h>
#include <eagle/application/components/Rigidbody.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/Sphere.h>
#include <eagle/application/components/PhysicsSettings.h>
#include <eagle/application/components/SingletonComponent.h>

EG_RAYTRACER_BEGIN

void PhysicsSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    events.subscribe<entityx::ComponentAddedEvent<Rigidbody>>(*this);
    entityx::ComponentHandle<Transform> transform;
    entityx::ComponentHandle<Rigidbody> rigidbody;
    for (auto e : entities.entities_with_components<Transform, Rigidbody>(transform, rigidbody)){
        rigidbody->current.position = transform->position();
        rigidbody->current.rotation = transform->rotation();
        rigidbody->previous = rigidbody->current;
    }
}

void PhysicsSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    auto& settings = SingletonComponent::get<PhysicsSettings>();
    settings.accumulator += dt;
    settings.accumulator = std::min(settings.accumulator, 0.2f);
    while (settings.accumulator > settings.fixedStep){
        update_physics(entities, events, settings.fixedStep);
        settings.accumulator -= settings.fixedStep;
    }

    settings.alpha = settings.accumulator / settings.fixedStep;

    //transform interpolation
    entityx::ComponentHandle<Transform> transform;
    entityx::ComponentHandle<Rigidbody> rigidbody;
    for (auto e : entities.entities_with_components<Transform, Rigidbody>(transform, rigidbody)){
        transform->set_position(glm::mix(rigidbody->previous.position, rigidbody->current.position, settings.alpha));
        transform->set_rotation(glm::mix(rigidbody->previous.rotation, rigidbody->current.rotation, settings.alpha));
    }
}

void PhysicsSystem::update_physics(entityx::EntityManager &entities, entityx::EventManager &events, float dt) {

    events.emit<OnPhysicsUpdate>(entities, events, dt);

    entityx::ComponentHandle<Rigidbody> rigidbody;
    for (auto e : entities.entities_with_components<Rigidbody>(rigidbody)){
        rigidbody->previous = rigidbody->current;
        rigidbody->velocity += glm::vec3(0, -9.98f * dt, 0);
        rigidbody->velocity *= (1 - dt * rigidbody->drag);
        rigidbody->current.position += rigidbody->velocity * dt;
        rigidbody->current.rotation *= glm::quat(rigidbody->angularVelocity * dt);
        rigidbody->current.rotation = glm::normalize(rigidbody->current.rotation);
    }
}

void PhysicsSystem::receive(const entityx::ComponentAddedEvent<Rigidbody>& ev) {
    assert(ev.entity.has_component<Transform>());
    entityx::Entity e = ev.entity;
    entityx::ComponentHandle<Transform> transform = e.component<Transform>();
    entityx::ComponentHandle<Rigidbody> rigidbody = e.component<Rigidbody>();
    rigidbody->current.position = transform->position();
    rigidbody->current.rotation = transform->rotation();
    rigidbody->previous = rigidbody->current;
}

EG_RAYTRACER_END
