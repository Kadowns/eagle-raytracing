//
// Created by Novak on 22/03/2020.
//

#ifndef EAGLE_RENDERMASTER_H
#define EAGLE_RENDERMASTER_H

#include <eagle/raytracer/RaytracerGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

class RenderMaster {
public:
    typedef ImmediateEvent<Reference<RenderingContext>&> InitEvent;
    typedef ImmediateEvent<Reference<CommandBuffer>&> RenderPassDrawEvent;
    typedef ImmediateEvent<> DeinitEvent;
public:

    void init();
    void update();
    void deinit();

    void handle_window_resized(uint32_t width, uint32_t height);

    inline static RenderingContext& context() { return *s_context; }
public:
    static InitEvent handle_render_init;
    static DeinitEvent handle_render_deinit;
    static RenderPassDrawEvent handle_main_render_pass_draw;
private:
    void init_compute();
    void init_graphics();

    void init_compute_target();

private:
    static Reference<RenderingContext> s_context;
    struct {
        uint32_t width, height;
    } screen;

    struct {
        Handle<ComputeShader> shader;
        Handle<Texture2D> imageTarget;
    } compute;


    struct {
        Handle<Shader> shader;
        Handle<VertexBuffer> vertexBuffer;
        Handle<IndexBuffer> indexBuffer;
        Handle<DescriptorSet> descriptorSet;
    } graphics;
};

EG_RAYTRACER_END

#endif //EAGLE_RENDERMASTER_H
