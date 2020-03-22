//
// Created by Novak on 22/03/2020.
//

#ifndef EAGLE_EDITORLAYER_H
#define EAGLE_EDITORLAYER_H

#include <eagle/raytracer/RaytracerGlobalDefinitions.h>
#include <eagle/raytracer/RenderLayer.h>

#include <eagle/raytracer/editor/EditorMaster.h>

EG_RAYTRACER_BEGIN

class EditorLayer : public Layer {
public:

    EditorLayer();
    ~EditorLayer();

    virtual void handle_attach() override;

    virtual void handle_deattach() override;

    virtual void handle_update() override;

    virtual void handle_event(Event &e) override;

private:
    RenderLayer::RenderEvent::Listener handle_render_event_callback;
    RenderLayer::RenderInitEvent::Listener handle_render_init_event_callback;
    RenderLayer::RenderDeinitEvent::Listener handle_render_deinit_event_callback;
private:
    EditorMaster m_editorMaster;
    EventDispatcher m_dispatcher;
};

EG_RAYTRACER_END

#endif //EAGLE_EDITORLAYER_H
