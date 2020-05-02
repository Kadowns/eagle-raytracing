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
#include <eagle/application/systems/PhysicsSystem.h>
#include <eagle/application/systems/CollisionSystem.h>
#include <eagle/application/components/SingletonComponent.h>
#include <eagle/application/components/Sphere.h>
#include <eagle/application/components/Rigidbody.h>

EG_RAYTRACER_BEGIN

SceneLayer::SceneLayer() :
    m_entities(m_events),
    m_systems(m_entities, m_events){

}

void SceneLayer::handle_attach() {

    auto camera = m_entities.create();
    camera.assign<Camera>();
    camera.assign<Transform>(glm::vec3(0, 10, -20), glm::quat(glm::vec3(0)), glm::vec3(1));
    camera.assign<CameraController>();

    auto light = m_entities.create();
    light.assign<DirectionalLight>();
    light.assign<Transform>(glm::vec3(0), glm::quat(glm::radians(glm::vec3(-30, 0, 0))), glm::vec3(1))->hasChanged = true;

    generate_scene();

    m_systems.add<CameraSystem>();
    m_systems.add<LightSystem>();
    m_systems.add<PhysicsSystem>();
    m_systems.add<CollisionSystem>();
    m_systems.add<RaytracerSystem>();
    m_systems.configure();
}

void SceneLayer::handle_deattach() {

}

void SceneLayer::handle_update() {
    m_systems.update_all(Time::delta_time());
}

void SceneLayer::handle_event(Event &e) {

}

void SceneLayer::generate_scene() {
    SceneData& scene = SingletonComponent::get<SceneData>();
    for (int i = 0; i < scene.maxSphereCount; i++) {
        auto e = m_entities.create();
        auto sphere = e.assign<Sphere>();
        auto transform = e.assign<Transform>();
        e.assign<Rigidbody>();
        // Radius and radius
        sphere->radius = scene.sphereSizes.x + Random::value() * (scene.sphereSizes.y - scene.sphereSizes.x);
        glm::vec2 randomPos = random_inside_unit_circle() * scene.spherePlacementRadius;
        transform->set_position(glm::vec3(randomPos.x, sphere->radius, randomPos.y));
        // Reject spheres that are intersecting others
        bool skipSphere = false;
        for (auto other : m_entities.entities_with_components<Sphere, Transform>()) {
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
        bool metal = Random::value() < scene.metalPercent;
        sphere->albedo = metal ? glm::vec3(0.01f) : glm::vec3(color.r, color.g, color.b);
        sphere->specular = metal ? glm::vec3(color.r, color.g, color.b) : glm::vec3(0.01f);
    }
}

glm::vec2 SceneLayer::random_inside_unit_circle() {
    return glm::normalize(glm::vec2(Random::range(-1.0f, 1.0f), Random::range(-1.0f, 1.0f))) * Random::value();
}

EG_RAYTRACER_END


