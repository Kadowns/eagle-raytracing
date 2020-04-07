//
// Created by Novak on 04/04/2020.
//

#include <eagle/application/editor/ComputeDataEditor.h>
#include <external/imgui/imgui/imgui.h>

EG_RAYTRACER_BEGIN

ComputeDataEditor::ComputeDataEditor(ComputeData &data, const std::function<void()> &recreateSpheresCallback) :
    EditorWindow("Settings"), m_data(data), recreate_spheres(recreateSpheresCallback) {

}

void ComputeDataEditor::handle_window_update() {

    glm::vec3 eulerRotation = glm::degrees(glm::eulerAngles(m_data.light.rotation()));
    if (ImGui::DragFloat3("Light rotation", &eulerRotation[0])){
        m_data.light.set_rotation(glm::quat(glm::radians(eulerRotation)));
    }

    bool recreateSpheres = false;
    if (ImGui::InputInt("Max sphere count", &m_data.maxSphereCount)){
        if (m_data.maxSphereCount > MAX_SPHERES){
            m_data.maxSphereCount = MAX_SPHERES;
        }
        recreateSpheres = true;
    }

    if (ImGui::InputFloat("Sphere placement radius", &m_data.spherePlacementRadius)){
        recreateSpheres = true;
    }

    if (ImGui::InputFloat2("Spheres sizes", &m_data.sphereSizes[0])){
        if (m_data.sphereSizes.x <= 0){
            m_data.sphereSizes.x = 0.1f;
        }
        if (m_data.sphereSizes.y < m_data.sphereSizes.x){
            m_data.sphereSizes.y = m_data.sphereSizes.x;
        }
        recreateSpheres = true;
    }

    if (ImGui::SliderFloat("Metal percent", &m_data.metalPercent, 0.0f, 1.0f)){
        recreateSpheres = true;
    }

    if (recreateSpheres){
        recreate_spheres();
    }
}


EG_RAYTRACER_END


