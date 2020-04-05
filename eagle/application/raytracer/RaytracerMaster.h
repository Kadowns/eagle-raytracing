//
// Created by Novak on 28/03/2020.
//

#ifndef EAGLE_RAYTRACERMASTER_H
#define EAGLE_RAYTRACERMASTER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/renderer/RenderMaster.h>
#include <eagle/application/raytracer/CameraController.h>
#include <eagle/application/raytracer/ComputeData.h>

EG_RAYTRACER_BEGIN

class RaytracerMaster {
public:
    void init();
    void deinit();
    void update();
private:

    void init_render_target();
    void handle_context_init();
    void handle_context_deinit();
    void handle_frame_begin();
    void handle_command_buffer_begin(const Reference<CommandBuffer>& commandBuffer);
    void handle_command_buffer_main_render_pass(const Reference<CommandBuffer>& commandBuffer);

    glm::vec2 random_inside_unit_circle();

private:

    RenderMaster::Event::Listener context_init_callback;
    RenderMaster::Event::Listener context_deinit_callback;
    RenderMaster::Event::Listener frame_begin_callback;
    RenderMaster::Event::Listener context_recreated_callback;
    RenderMaster::CommandBufferEvent::Listener command_buffer_begin_callback;
    RenderMaster::CommandBufferEvent::Listener command_buffer_main_render_pass_callback;

    struct{
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 inverseProjection;
        alignas(16) glm::vec3 position;
        alignas(8) glm::vec2 pixelOffset;
        alignas(16) glm::vec4 light;
        float sampleCount;
        int sphereCount;
    } m_computeUbo;

    struct Sphere{
        alignas(16) glm::vec3 position;
        alignas(4) float radius;
        alignas(16) glm::vec3 albedo;
        alignas(16) glm::vec3 specular;
    };

    ComputeData m_computeData;
    CameraController m_camera;
    std::vector<Sphere> m_spheres;
    Handle<UniformBuffer> m_cameraBuffer;
    Handle<ComputeShader> m_computeShader;
    Handle<StorageBuffer> m_spheresBuffer;
    Handle<Texture> m_computeTarget;
    Handle<Texture> m_skybox;
    Handle<Shader> m_quadShader;
    Handle<DescriptorSet> m_quadDescriptorSet;

    void init_spheres();
};

EG_RAYTRACER_END

#endif //EAGLE_RAYTRACERMASTER_H
