//
// Created by Novak on 22/03/2020.
//

#ifndef EAGLE_RENDERMASTER_H
#define EAGLE_RENDERMASTER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/EventMaster.h>

EG_RAYTRACER_BEGIN

class RenderMaster {
public:
    typedef ImmediateEvent<> Event;
    typedef ImmediateEvent<Reference<CommandBuffer>&> CommandBufferEvent;

public:

    void init();
    void update();
    void deinit();

    void handle_window_resized(uint32_t width, uint32_t height);

    inline static RenderingContext& context() { return *s_context; }
public:
    static Event handle_render_init;
    static Event handle_render_deinit;
    static Event handle_frame_begin;
    static Event handle_frame_end;
    static Event handle_context_recreated;
    static CommandBufferEvent handle_command_buffer_begin;
    static CommandBufferEvent handle_command_buffer_end;
    static CommandBufferEvent handle_command_buffer_main_render_pass;
private:
    void init_graphics();

private:
    static Reference<RenderingContext> s_context;

    std::function<void(const OnRaytracerTargetCreated&)> raytracer_target_created_callback;

    struct {
        uint32_t width, height;
    } screen;

    struct {
        Handle<Shader> shader;
        Handle<VertexBuffer> vertexBuffer;
        Handle<IndexBuffer> indexBuffer;
        Handle<DescriptorSet> descriptorSet;
    } graphics;
};

EG_RAYTRACER_END

#endif //EAGLE_RENDERMASTER_H
