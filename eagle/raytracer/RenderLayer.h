//
// Created by Novak on 17/03/2020.
//

#ifndef EAGLE_RENDERLAYER_H
#define EAGLE_RENDERLAYER_H

#include <eagle/raytracer/RaytracerGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

class RenderLayer : public Layer {
public:
    typedef ImmediateEvent<Reference<RenderingContext>&> RenderInitEvent;
    typedef ImmediateEvent<Reference<RenderingContext>&> RenderDeinitEvent;
    typedef ImmediateEvent<Scope<CommandBuffer>&> RenderEvent;
public:
    virtual void handle_attach() override;

    virtual void handle_deattach() override;

    virtual void handle_update() override;

    virtual void handle_event(Event &e) override;

    static RenderEvent handle_render_event;
    static RenderInitEvent handle_render_init_event;
    static RenderDeinitEvent handle_render_deinit_event;

private:
    Reference<RenderingContext> m_context;
    EventDispatcher m_dispatcher;
};


EG_RAYTRACER_END

#endif //EAGLE_RENDERLAYER_H
