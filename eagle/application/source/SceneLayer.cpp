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
#include <eagle/application/components/SingletonComponent.h>
#include <eagle/application/components/Sphere.h>

EG_RAYTRACER_BEGIN

void SceneLayer::handle_attach() {

    auto camera = m_scene.entities.create();
    camera.assign<Camera>();
    camera.assign<Transform>(glm::vec3(0, 10, -20), glm::quat(glm::vec3(0)), glm::vec3(1));
    camera.assign<CameraController>();

    auto light = m_scene.entities.create();
    light.assign<DirectionalLight>();
    light.assign<Transform>(glm::vec3(0), glm::quat(glm::radians(glm::vec3(-30, 0, 0))), glm::vec3(1))->hasChanged = true;

    generate_scene();

    m_scene.systems.add<CameraSystem>();
    m_scene.systems.add<LightSystem>();
    m_scene.systems.add<RaytracerSystem>();
    m_scene.systems.configure();
}

void SceneLayer::handle_deattach() {

}

void SceneLayer::handle_update() {
    m_scene.systems.update<CameraSystem>(Time::delta_time());
    m_scene.systems.update<LightSystem>(Time::delta_time());
    m_scene.systems.update<RaytracerSystem>(Time::delta_time());
}

void SceneLayer::handle_event(Event &e) {

}

void SceneLayer::generate_scene() {
    SceneData& scene = SingletonComponent::get<SceneData>();
    for (int i = 0; i < scene.maxSphereCount; i++) {
        auto e = m_scene.entities.create();
        auto sphere = e.assign<Sphere>();
        auto transform = e.assign<Transform>();
        // Radius and radius
        sphere->radius = scene.sphereSizes.x + Random::value() * (scene.sphereSizes.y - scene.sphereSizes.x);
        glm::vec2 randomPos = random_inside_unit_circle() * scene.spherePlacementRadius;
        transform->set_position(glm::vec3(randomPos.x, sphere->radius, randomPos.y));
        // Reject spheres that are intersecting others
        bool skipSphere = false;
        for (auto other : m_scene.entities.entities_with_components<Sphere, Transform>()) {
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


