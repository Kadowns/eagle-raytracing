//
// Created by Novak on 22/03/2020.
//

#ifndef EAGLE_EDITORLAYER_H
#define EAGLE_EDITORLAYER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/editor/EditorMaster.h>

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
    EditorMaster m_editorMaster;
    LayerEventDispatcher m_dispatcher;
};

EG_RAYTRACER_END

#endif //EAGLE_EDITORLAYER_H
