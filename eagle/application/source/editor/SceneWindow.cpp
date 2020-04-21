//
// Created by Novak on 06/04/2020.
//

#include <eagle/application/editor/SceneWindow.h>
#include <external/imgui/imgui/imgui.h>
#include <eagle/application/renderer/RenderMaster.h>
#include <eagle/application/components/Camera.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/CameraController.h>
#include <eagle/application/components/DirectionalLight.h>
#include <eagle/application/systems/CameraSystem.h>
#include <eagle/application/systems/LightSystem.h>
#include <eagle/application/systems/RaytracerSystem.h>

EG_RAYTRACER_BEGIN

SceneWindow::SceneWindow() : EditorWindow("Scene") {
    raytracer_target_created_callback = [&](const OnRaytracerTargetCreated& ev){
        handle_raytracer_target_created(ev.target);
    };
    EventMaster::instance().subscribe<OnRaytracerTargetCreated>(&raytracer_target_created_callback);

    auto camera = m_scene.entities.create();
    camera.assign<Camera>();
    camera.assign<Transform>(glm::vec3(0, 10, -20), glm::quat(glm::vec3(0)), glm::vec3(1));
    camera.assign<CameraController>();

    auto light = m_scene.entities.create();
    light.assign<DirectionalLight>();
    light.assign<Transform>(glm::vec3(0), glm::quat(glm::radians(glm::vec3(-30, 0, 0))), glm::vec3(1))->hasChanged = true;

    m_scene.systems.add<CameraSystem>();
    m_scene.systems.add<LightSystem>();
    m_scene.systems.add<RaytracerSystem>();

}

SceneWindow::~SceneWindow() {
    EventMaster::instance().unsubscribe<OnRaytracerTargetCreated>(&raytracer_target_created_callback);
}

void SceneWindow::handle_window_update() {
    static bool configured = false;
    if (!configured){
        m_scene.systems.configure();
        configured = true;
    }

    m_scene.systems.update_all(Time::delta_time());
    if (!m_descriptorSet.lock()){
        ImGui::Text("No target image set.");
        return;
    }

    ImGui::GetWindowDrawList()->AddCallback(DisableBlending, nullptr);

    ImGuiIO &io = ImGui::GetIO();
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();
    ImVec2 region(vMax.x - vMin.x, vMax.y - vMin.y);

    ImGui::Image((ImTextureID) &m_descriptorSet, region);
    ImGui::GetWindowDrawList()->AddCallback(EnableBlending, nullptr);
}

void SceneWindow::handle_raytracer_target_created(const Reference<Image> &target) {
    if (!target){
        return;
    }

    if (m_descriptorSet.lock()){
        m_descriptorSet.lock()->update({target});
    }
    else {
        DescriptorBindingDescription bindingDescription = {};
        bindingDescription.name = "uTexture";
        bindingDescription.shaderStage = ShaderStage::FRAGMENT;
        bindingDescription.descriptorType = DescriptorType::SAMPLED_IMAGE;
        bindingDescription.binding = 0;
        auto layout = RenderMaster::context().create_descriptor_set_layout({bindingDescription});
        m_descriptorSet = RenderMaster::context().create_descriptor_set(layout.lock(), {target});
    }
}




EG_RAYTRACER_END


