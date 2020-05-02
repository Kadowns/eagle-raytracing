//
// Created by Novak on 09/04/2020.
//

#ifndef EAGLE_RAYTRACERSYSTEM_H
#define EAGLE_RAYTRACERSYSTEM_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/renderer/RenderMaster.h>
#include <eagle/application/components/Camera.h>
#include <eagle/application/components/DirectionalLight.h>
#include <eagle/application/components/SceneData.h>
#include <eagle/application/components/Sphere.h>
#include <eagle/application/components/Box.h>

EG_RAYTRACER_BEGIN

class RaytracerSystem : public entityx::System<RaytracerSystem>, public entityx::Receiver<RaytracerSystem> {
public:
    RaytracerSystem();
    virtual ~RaytracerSystem() override;

    virtual void configure(entityx::EntityManager &entities, entityx::EventManager &events) override;
    virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    void receive(const OnCameraUpdate& ev);
    void receive(const OnLightUpdate& ev);
    void receive(const entityx::ComponentAddedEvent<Sphere>& ev);
    void receive(const entityx::ComponentAddedEvent<Box>& ev);
    void receive(const entityx::ComponentRemovedEvent<Sphere>& ev);
    void receive(const entityx::ComponentRemovedEvent<Box>& ev);
private:
    void init_render_target();
    void handle_context_init();
    void handle_context_deinit();
    void handle_frame_begin();
    void handle_command_buffer_begin(const Reference<CommandBuffer>& commandBuffer);
    void handle_command_buffer_main_render_pass(const Reference<CommandBuffer>& commandBuffer);

    void update_sphere_buffer(entityx::EntityManager &entities);
    void update_box_buffer(entityx::EntityManager &entities);

private:
    RenderMaster::Event::Listener context_init_callback;
    RenderMaster::Event::Listener context_deinit_callback;
    RenderMaster::Event::Listener frame_begin_callback;
    RenderMaster::Event::Listener context_recreated_callback;
    RenderMaster::CommandBufferEvent::Listener command_buffer_begin_callback;
    RenderMaster::CommandBufferEvent::Listener command_buffer_main_render_pass_callback;
    bool m_updateSpheres;
    bool m_updateBoxes;
};


EG_RAYTRACER_END

#endif //EAGLE_RAYTRACERSYSTEM_H
