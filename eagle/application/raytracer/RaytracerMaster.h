//
// Created by Novak on 28/03/2020.
//

#ifndef EAGLE_RAYTRACERMASTER_H
#define EAGLE_RAYTRACERMASTER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/renderer/RenderMaster.h>
#include <eagle/application/raytracer/CameraController.h>

EG_RAYTRACER_BEGIN

class RaytracerMaster {
public:
    void init();
    void deinit();
    void update();
private:

    void init_render_target();

private:

    RenderMaster::Event::Listener frame_begin_callback;
    RenderMaster::Event::Listener context_recreated;
    RenderMaster::CommandBufferEvent::Listener command_buffer_begin_callback;

    struct{
        glm::mat4 view;
        glm::mat4 inverseProjection;
        glm::vec3 position;
    } m_cameraUbo;


    CameraController m_camera;
    Handle<UniformBuffer> m_cameraBuffer;
    Handle<ComputeShader> m_computeShader;
    Handle<Texture2D> m_target;

};

EG_RAYTRACER_END

#endif //EAGLE_RAYTRACERMASTER_H
