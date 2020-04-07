//
// Created by Novak on 06/04/2020.
//

#include <eagle/application/editor/SceneWindow.h>
#include <external/imgui/imgui/imgui.h>

EG_RAYTRACER_BEGIN

SceneWindow::SceneWindow() : EditorWindow("Scene") {
    raytracer_target_created_callback = [&](const OnRaytracerTargetCreated& ev){
        handle_raytracer_target_created(ev.target);
    };
    EventMaster::instance().subscribe<OnRaytracerTargetCreated>(&raytracer_target_created_callback);
}

SceneWindow::~SceneWindow() {
    EventMaster::instance().unsubscribe<OnRaytracerTargetCreated>(&raytracer_target_created_callback);
}

void SceneWindow::handle_window_update() {
    if (!m_descriptorSet.lock()){
        ImGui::Text("No target image set.");
        return;
    }

    ImGuiIO &io = ImGui::GetIO();
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    ImVec2 region(vMax.x - vMin.x, vMax.y - vMin.y);
    ImGui::Image((ImTextureID) &m_descriptorSet, region);

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
        bindingDescription.descriptorType = DescriptorType::SAMPLED_IMAGE;
        bindingDescription.shaderStage = ShaderStage::FRAGMENT;
        bindingDescription.binding = 0;
        bindingDescription.name = "uTexture";
        auto layout = RenderMaster::context().create_descriptor_set_layout({bindingDescription}).lock();
        m_descriptorSet = RenderMaster::context().create_descriptor_set(layout, {target});
    }
}




EG_RAYTRACER_END


