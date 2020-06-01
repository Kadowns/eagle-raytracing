//
// Created by Novak on 27/05/2020.
//

#include <eagle/application/editor/DebugSettingsWindow.h>

#include <eagle/application/components/SingletonComponent.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/Box.h>
#include <eagle/application/components/Sphere.h>

#include <eagle/application/components/physics/PhysicsSettings.h>
#include <eagle/application/components/physics/Rigidbody.h>
#include <eagle/application/components/physics/Collider.h>
#include <eagle/application/components/physics/shapes/BoxCollider.h>
#include <eagle/application/SceneManager.h>

#include <external/imgui/imgui/imgui.h>
#include <eagle/application/components/Spawner.h>

EG_RAYTRACER_BEGIN

DebugSettingsWindow::DebugSettingsWindow() : EditorWindow("Physics Settings") {

}

DebugSettingsWindow::~DebugSettingsWindow() {

}

void DebugSettingsWindow::handle_window_update() {

    auto& settings = SingletonComponent::get<PhysicsSettings>();
    auto& scene = SceneManager::current_scene();

    ImGui::SliderFloat3("Gravity", &settings.gravity[0], -50, 50);
    float timeScale = Time::time_scale();
    if (ImGui::SliderFloat("Time Setp", &timeScale, 0.0f, 1.0f)){
        Time::set_time_scale(timeScale);
    }

    if (ImGui::Button("Reset scene")){
        for (auto e : scene.entities.entities_with_components<Transform, Box>()){
            e.destroy();
        }
        for (auto e : scene.entities.entities_with_components<Transform, Sphere>()){
            e.destroy();
        }

        auto plane = scene.entities.create();
        plane.assign<Transform>(glm::vec3(0), glm::quat(glm::radians(glm::vec3(0, 45, 0))), glm::vec3(1));
        plane.assign<Rigidbody>(0.0f, 0.0f, 0.2f, Rigidbody::Mode::STATIC);
        plane.assign<Collider>(std::make_shared<BoxCollider>(glm::vec3(25.0f, 25.0f, 25.0f)));
        plane.assign<Box>(glm::vec3(25.0f, 25.0f, 25.0f), glm::vec3(0.12f), glm::vec3(0.245f));
    }

    for (auto e : scene.entities.entities_with_components<Spawner>()){
        auto spawner = e.component<Spawner>();
        ImGui::PushID(e.id().id());
        ImGui::InputFloat3("Spawner rotation", &spawner->rotation[0]);
        ImGui::PopID();
    }

}

EG_RAYTRACER_END



