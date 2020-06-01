//
// Created by Novak on 29/05/2020.
//

#include <eagle/application/systems/SpawnerSystem.h>
#include <eagle/application/components/Spawner.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/SceneData.h>
#include <eagle/application/components/SingletonComponent.h>
#include <eagle/application/components/Sphere.h>
#include <eagle/application/components/Box.h>

#include <eagle/application/components/physics/Rigidbody.h>
#include <eagle/application/components/physics/Collider.h>
#include <eagle/application/components/physics/shapes/SphereCollider.h>
#include <eagle/application/components/physics/shapes/BoxCollider.h>

EG_RAYTRACER_BEGIN

void SpawnerSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {

}

void SpawnerSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {

    entities.each<Transform, Spawner>([&entities](entityx::Entity e, Transform& transform, Spawner& spawner){

        if (Input::instance().key_pressed(EG_KEY_G)){
            SceneData& scene = SingletonComponent::get<SceneData>();
            glm::vec3 color = glm::vec3(Random::value(), Random::value(), Random::value());
            bool metal = Random::value() < scene.metalPercent;

            auto s = entities.create();
            auto sphere = s.assign<Sphere>();
            sphere->radius = Random::range(0.3, 8.0f);
            sphere->albedo = metal ? glm::vec3(0.01f) : glm::vec3(color.r, color.g, color.b);
            sphere->specular = metal ? glm::vec3(color.r, color.g, color.b) : glm::vec3(0.01f);
            auto tr = s.assign<Transform>(transform);
            tr->translate(transform.front() * sphere->radius * 2.0f);
            auto rb = s.assign<Rigidbody>();
            rb->velocity = transform.front() * 40.0f;
            s.assign<Collider>(std::make_shared<SphereCollider>(sphere->radius));
        }

        if (Input::instance().key_pressed(EG_KEY_B)){
            SceneData& scene = SingletonComponent::get<SceneData>();

            auto s = entities.create();
            auto tr = s.assign<Transform>();
            tr->set_position(transform.position());
            tr->set_rotation(glm::radians(spawner.rotation));

            auto box = s.assign<Box>();
            box->radius = glm::vec3(1.0f);
            box->albedo = glm::vec3(0.1f);
            box->specular = glm::vec3(0.8f);
            tr->translate(transform.front() * box->radius.z * 2.0f);
            auto rigidbody = s.assign<Rigidbody>();
            rigidbody->velocity = transform.front() * 15.0f;
            rigidbody->angularVelocity = glm::radians(glm::vec3(0, 0, 0));
            s.assign<Collider>(std::make_shared<BoxCollider>(box->radius));
        }
    });

}



EG_RAYTRACER_END

