//
// Created by Novak on 28/03/2020.
//

#include <eagle/application/raytracer/RaytracerLayer.h>
#include <eagle/application/renderer/RenderMaster.h>

EG_RAYTRACER_BEGIN

RaytracerLayer::RaytracerLayer() {

    render_init_callback = [&](){
        m_raytracerMaster.init();
    };

    render_deinit_callback = [&](){
        m_raytracerMaster.deinit();
    };
}

RaytracerLayer::~RaytracerLayer() {


}

void RaytracerLayer::handle_attach() {
    RenderMaster::handle_render_init += &render_init_callback;
    RenderMaster::handle_render_deinit += &render_deinit_callback;
}

void RaytracerLayer::handle_deattach() {
    RenderMaster::handle_render_init -= &render_init_callback;
    RenderMaster::handle_render_deinit -= &render_deinit_callback;
}

void RaytracerLayer::handle_update() {
    m_raytracerMaster.update();
}

void RaytracerLayer::handle_event(Eagle::Event &e) {

}




EG_RAYTRACER_END

