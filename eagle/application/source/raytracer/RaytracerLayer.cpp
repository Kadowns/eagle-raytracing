//
// Created by Novak on 28/03/2020.
//

#include <eagle/application/raytracer/RaytracerLayer.h>
#include <eagle/application/renderer/RenderMaster.h>

EG_RAYTRACER_BEGIN

RaytracerLayer::RaytracerLayer() {


}

RaytracerLayer::~RaytracerLayer() {


}

void RaytracerLayer::handle_attach() {
    m_raytracerMaster.init();
}

void RaytracerLayer::handle_deattach() {
    m_raytracerMaster.deinit();
}

void RaytracerLayer::handle_update() {
    m_raytracerMaster.update();
}

void RaytracerLayer::handle_event(Eagle::Event &e) {

}




EG_RAYTRACER_END

