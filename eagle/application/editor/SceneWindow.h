//
// Created by Novak on 06/04/2020.
//

#ifndef EAGLE_SCENEWINDOW_H
#define EAGLE_SCENEWINDOW_H

#include <eagle/application/editor/EditorWindow.h>
#include <eagle/application/EventMaster.h>
#include <eagle/application/renderer/RenderMaster.h>

EG_RAYTRACER_BEGIN

class SceneWindow : public EditorWindow {
public:
    SceneWindow();
    virtual ~SceneWindow();

    virtual void handle_window_update() override;
private:
    void handle_raytracer_target_created(const Reference<Image>& target);

private:

    std::function<void(const OnRaytracerTargetCreated&)> raytracer_target_created_callback;
    Handle<DescriptorSet> m_descriptorSet;
    entityx::EntityX m_scene;
};

EG_RAYTRACER_END


#endif //EAGLE_SCENEWINDOW_H
