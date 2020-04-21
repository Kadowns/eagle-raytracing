//
// Created by Novak on 04/04/2020.
//

#ifndef EAGLE_COMPUTEDATAEDITOR_H
#define EAGLE_COMPUTEDATAEDITOR_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/SceneData.h>
#include <eagle/application/editor/EditorWindow.h>

EG_RAYTRACER_BEGIN

class ComputeDataEditor : public EditorWindow {
public:
    ComputeDataEditor(SceneData &data, const std::function<void()> &recreateSpheresCallback);

    virtual void handle_window_update() override;

private:
    SceneData& m_data;
    std::function<void()> recreate_spheres;
};


EG_RAYTRACER_END

#endif //EAGLE_COMPUTEDATAEDITOR_H
