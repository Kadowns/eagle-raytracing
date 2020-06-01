//
// Created by Novak on 4/21/2020.
//

#include <eagle/application/SceneLayer.h>
#include <eagle/application/components/Camera.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/CameraController.h>
#include <eagle/application/components/DirectionalLight.h>
#include <eagle/application/systems/RaytracerSystem.h>
#include <eagle/application/systems/LightSystem.h>
#include <eagle/application/systems/CameraSystem.h>
#include <eagle/application/systems/physics/PhysicsSystem.h>
#include <eagle/application/systems/physics/CollisionSystem.h>
#include <eagle/application/components/SingletonComponent.h>
#include <eagle/application/components/Sphere.h>
#include <eagle/application/components/physics/Rigidbody.h>
#include <eagle/application/components/physics/shapes/PlaneCollider.h>
#include <eagle/application/components/physics/shapes/SphereCollider.h>
#include <eagle/application/components/physics/shapes/BoxCollider.h>
#include <eagle/application/systems/SpawnerSystem.h>
#include <eagle/application/components/Spawner.h>
#include <eagle/application/SceneManager.h>

EG_RAYTRACER_BEGIN

SceneLayer::SceneLayer() {

}

void SceneLayer::handle_attach() {

    Scene& scene = SceneManager::current_scene();

    auto camera = scene.entities.create();
    camera.assign<Camera>();
    camera.assign<Transform>(glm::vec3(0, 10, 0), glm::quat(glm::vec3(0)), glm::vec3(1));
    camera.assign<CameraController>();
    camera.assign<Spawner>();

    auto light = scene.entities.create();
    light.assign<DirectionalLight>();
    light.assign<Transform>(glm::vec3(0), glm::quat(glm::radians(glm::vec3(-30, 0, 0))), glm::vec3(1))->hasChanged = true;

    auto plane = scene.entities.create();
    plane.assign<Transform>(glm::vec3(0), glm::quat(glm::radians(glm::vec3(0, 45, 0))), glm::vec3(1));
    plane.assign<Rigidbody>(0.0f, 0.0f, 0.2f, Rigidbody::Mode::STATIC);
    //plane.assign<Collider>(std::make_shared<PlaneCollider>(glm::vec3(0, 1, 0), 0));
    plane.assign<Collider>(std::make_shared<BoxCollider>(glm::vec3(25.0f, 25.0f, 25.0f)));
    plane.assign<Box>(glm::vec3(25.0f, 25.0f, 25.0f), glm::vec3(0.12f), glm::vec3(0.245f));

   // generate_scene();

    scene.systems.add<CameraSystem>();
    scene.systems.add<SpawnerSystem>();
    scene.systems.add<LightSystem>();
    scene.systems.add<PhysicsSystem>();
    scene.systems.add<CollisionSystem>();
    scene.systems.add<RaytracerSystem>();
    scene.systems.configure();
}

void SceneLayer::handle_deattach() {

}

void SceneLayer::handle_update() {
    SceneManager::current_scene().systems.update_all(Time::delta_time());
}

void SceneLayer::handle_event(Event &e) {

}

void SceneLayer::generate_scene() {
    SceneData& sceneSettings = SingletonComponent::get<SceneData>();
    Scene& scene = SceneManager::current_scene();
    for (int i = 0; i < sceneSettings.maxSphereCount; i++) {
        auto e = scene.entities.create();
        auto sphere = e.assign<Sphere>();
        auto transform = e.assign<Transform>();
        e.assign<Rigidbody>();
        // Radius and radius
        sphere->radius = sceneSettings.sphereSizes.x + Random::value() * (sceneSettings.sphereSizes.y - sceneSettings.sphereSizes.x);
        glm::vec2 randomPos = random_inside_unit_circle() * sceneSettings.spherePlacementRadius;
        transform->set_position(glm::vec3(randomPos.x, sphere->radius, randomPos.y));
        // Reject spheres that are intersecting others
        bool skipSphere = false;
        for (auto other : scene.entities.entities_with_components<Sphere, Transform>()) {
            if (e == other) continue;

            auto otherSphere = other.component<Sphere>();
            auto otherTransform = other.component<Transform>();
            float minDist = sphere->radius + otherSphere->radius;
            if (glm::length2(transform->position() - otherTransform->position()) < minDist * minDist){
                e.destroy();
                skipSphere = true;
                break;
            }
        }
        if (skipSphere){
            continue;
        }
        // Albedo and specular color
        glm::vec3 color = glm::vec3(Random::value(), Random::value(), Random::value());
        bool metal = Random::value() < sceneSettings.metalPercent;
        sphere->albedo = metal ? glm::vec3(0.01f) : glm::vec3(color.r, color.g, color.b);
        sphere->specular = metal ? glm::vec3(color.r, color.g, color.b) : glm::vec3(0.01f);
        e.assign<Collider>(std::make_shared<SphereCollider>(sphere->radius));

    }
}

glm::vec2 SceneLayer::random_inside_unit_circle() {
    return glm::normalize(glm::vec2(Random::range(-1.0f, 1.0f), Random::range(-1.0f, 1.0f))) * Random::value();
}

EG_RAYTRACER_END


