//
// Created by Novak on 28/03/2020.
//

#ifndef EAGLE_RAYTRACERLAYER_H
#define EAGLE_RAYTRACERLAYER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/raytracer/RaytracerMaster.h>

EG_RAYTRACER_BEGIN

class RaytracerLayer : public Layer{
public:

    RaytracerLayer();

    virtual ~RaytracerLayer() override;

    virtual void handle_attach() override;

    virtual void handle_deattach() override;

    virtual void handle_update() override;

    virtual void handle_event(Event &e) override;
private:
    RaytracerMaster m_raytracerMaster;

    RenderMaster::Event::Listener render_init_callback;
    RenderMaster::Event::Listener render_deinit_callback;



};

EG_RAYTRACER_END


#endif //EAGLE_RAYTRACERLAYER_H
