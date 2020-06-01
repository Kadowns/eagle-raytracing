//
// Created by Novak on 5/2/2020.
//

#include <eagle/application/systems/physics/CollisionSystem.h>
#include <eagle/application/systems/physics/collision/Collision.h>
#include <eagle/application/systems/physics/collision/CollisionManager.h>
#include <eagle/application/systems/physics/collision/CollisionSolver.h>
#include <eagle/application/components/physics/Collider.h>
#include <eagle/application/components/physics/CollisionSettings.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/SingletonComponent.h>
#include <eagle/application/components/physics/PhysicsSettings.h>
#include <eagle/application/components/physics/Rigidbody.h>

EG_RAYTRACER_BEGIN

void CollisionSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    events.subscribe<OnPhysicsUpdate>(*this);
    events.subscribe<entityx::ComponentAddedEvent<Collider>>(*this);
    CollisionManager::configure();

    for (auto e : entities.entities_with_components<Collider, Rigidbody>()) {
        e.component<Collider>()->shape->compute_inertia(*e.component<Rigidbody>());
    }
}

void CollisionSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {

}

void CollisionSystem::receive(const entityx::ComponentAddedEvent<Collider> &ev) {
    assert(ev.entity.has_component<Rigidbody>());
    entityx::Entity e = ev.entity;
    e.component<Collider>()->shape->compute_inertia(*e.component<Rigidbody>());
}

void CollisionSystem::receive(const OnPhysicsUpdate& ev) {

    auto& settings = SingletonComponent::get<CollisionSettings>();

    settings.collisions.clear();

    for (auto e1 : ev.entities.entities_with_components<Collider, Rigidbody>()) {
        entityx::ComponentHandle<Collider> c1 = e1.component<Collider>();
        entityx::ComponentHandle<Rigidbody> rb1 = e1.component<Rigidbody>();
        for (auto e2 : ev.entities.entities_with_components<Collider, Rigidbody>()) {
            if (e1 == e2) {
                continue;
            }

            entityx::ComponentHandle<Collider> c2 = e2.component<Collider>();
            entityx::ComponentHandle<Rigidbody> rb2 = e2.component<Rigidbody>();

            if (!(c1->layer & c2->layer)){
                continue;
            }


            Collision collision(c1, c2, rb1, rb2);
            auto oldCollision = std::find(settings.collisions.begin(), settings.collisions.end(), collision);
            if (oldCollision != settings.collisions.end()){
                continue;
            }

            if (CollisionManager::test_collision(collision)){
                settings.collisions.push_back(collision);
            }
        }
    }

    CollisionSolver solver(settings.collisions);
    solver.pre_solve(ev.dt);
    for (int i = 0; i < 8; i++){
        solver.solve();
    }
}



EG_RAYTRACER_END
