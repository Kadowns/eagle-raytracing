//
// Created by Novak on 27/05/2020.
//

#include <eagle/editor/window/DebugSettingsWindow.h>

using namespace Eagle::Engine;

EG_EDITOR_BEGIN

DebugSettingsWindow::DebugSettingsWindow() : EditorWindow("Physics Settings") {

}

DebugSettingsWindow::~DebugSettingsWindow() {

}

void DebugSettingsWindow::handle_window_update() {

    auto& settings = SingletonComponent::get<PhysicsSettings>();
    auto& sceneData = SingletonComponent::get<SceneData>();
    auto& scene = SceneManager::current_scene();

    ImGui::SliderFloat3("Gravity", &settings.gravity[0], -50, 50);
    float timeScale = Time::time_scale();
    if (ImGui::SliderFloat("Time Setp", &timeScale, 0.0f, 1.0f)){
        Time::set_time_scale(timeScale);
    }

    ImGui::InputFloat3("Cube rotation:", &sceneData.cubeRotation[0]);

    if (ImGui::Button("Reset scene")){
        for (auto e : scene.entities.entities_with_components<Transform, Box>()){
            e.destroy();
        }
        for (auto e : scene.entities.entities_with_components<Transform, Sphere>()){
            e.destroy();
        }

        auto plane = scene.entities.create();
        plane.assign<Transform>(glm::vec3(0), glm::quat(glm::radians(sceneData.cubeRotation)), glm::vec3(1));
        plane.assign<Rigidbody>(0.0f, 0.0f, 0.2f, 0.75f, Rigidbody::Mode::STATIC);
        plane.assign<Collider>(std::make_shared<BoxCollider>(glm::vec3(25.0f, 25.0f, 25.0f)));
        plane.assign<Box>(glm::vec3(25.0f, 25.0f, 25.0f), glm::vec3(0.12f), glm::vec3(0.245f));
    }

    for (auto e : scene.entities.entities_with_components<Spawner>()){
        auto spawner = e.component<Spawner>();
        ImGui::PushID(e.id().id());
        ImGui::InputFloat3("Spawner rotation", &spawner->rotation[0]);
        ImGui::InputFloat3("Spawner radius", &spawner->radius[0]);
        ImGui::PopID();
    }

}

EG_EDITOR_END



