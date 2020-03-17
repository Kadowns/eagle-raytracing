//
// Created by Novak on 17/03/2020.
//

#ifndef EAGLE_RAYTRACERLAYER_H
#define EAGLE_RAYTRACERLAYER_H

#include <eagle/raytracer/RaytracerGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

class RaytracerLayer : public Layer {
public:
    virtual void handle_attach() override;

    virtual void handle_deattach() override;

    virtual void handle_update() override;

    virtual void handle_event(Event &e) override;

private:
    Reference<RenderingContext> m_context;
    EventDispatcher m_dispatcher;
};


EG_RAYTRACER_END

#endif //EAGLE_RAYTRACERLAYER_H
