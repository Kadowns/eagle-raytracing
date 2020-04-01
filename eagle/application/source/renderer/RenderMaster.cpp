//
// Created by Novak on 22/03/2020.
//

#include <eagle/application/renderer/RenderMaster.h>



EG_RAYTRACER_BEGIN

RenderMaster::Event RenderMaster::handle_render_init;
RenderMaster::Event RenderMaster::handle_render_deinit;
RenderMaster::Event RenderMaster::handle_frame_begin;
RenderMaster::Event RenderMaster::handle_frame_end;
RenderMaster::Event RenderMaster::handle_context_recreated;
RenderMaster::CommandBufferEvent RenderMaster::handle_command_buffer_begin;
RenderMaster::CommandBufferEvent RenderMaster::handle_command_buffer_end;
RenderMaster::CommandBufferEvent RenderMaster::handle_command_buffer_main_render_pass;

Reference<RenderingContext> RenderMaster::s_context;

void RenderMaster::init() {
    Window& window = Application::instance().window();

    screen.width = window.get_width();
    screen.height = window.get_height();

    s_context = std::make_shared<VulkanContext>();
    s_context->init(&window);
    s_context->set_recreation_callback([&](){
        handle_context_recreated();
    });

    raytracer_target_created_callback = [&](const OnRaytracerTargetCreated& ev){
        if (graphics.descriptorSet.lock()){
            graphics.descriptorSet.lock()->update({ev.target->get_image().lock()});
        }
        else {
            graphics.descriptorSet = s_context->create_descriptor_set(graphics.shader.lock()->get_descriptor_set_layout(0).lock(), {ev.target->get_image().lock()});
        }
    };

    EventMaster::instance().subscribe<OnRaytracerTargetCreated>(&raytracer_target_created_callback);

    init_graphics();

    handle_render_init();
}

void RenderMaster::update() {
    if (!s_context->prepare_frame()){
        EG_WARNING("Failed to prepare frame!");
        return;
    }

    handle_frame_begin();

    auto commandBuffer = s_context->create_command_buffer();
    commandBuffer->begin();

    handle_command_buffer_begin(commandBuffer);

    commandBuffer->begin_render_pass(s_context->main_render_target());

    commandBuffer->bind_shader(graphics.shader.lock());
    commandBuffer->bind_descriptor_sets(graphics.shader.lock(), graphics.descriptorSet.lock(), 0);
    commandBuffer->bind_vertex_buffer(graphics.vertexBuffer.lock());
    commandBuffer->bind_index_buffer(graphics.indexBuffer.lock());
    commandBuffer->draw_indexed(graphics.indexBuffer.lock()->get_indices_count(), 0, 0);

    handle_command_buffer_main_render_pass(commandBuffer);

    commandBuffer->end_render_pass();

    handle_command_buffer_end(commandBuffer);

    commandBuffer->finish();
    commandBuffer->submit();

    handle_frame_end();

    s_context->present_frame();
}

void RenderMaster::deinit() {
    EventMaster::instance().unsubscribe<OnRaytracerTargetCreated>(&raytracer_target_created_callback);
    handle_render_deinit();
    s_context->deinit();
}

void RenderMaster::handle_window_resized(uint32_t width, uint32_t height) {
    screen.width = width;
    screen.height = height;
    s_context->handle_window_resized(width, height);
}

void RenderMaster::init_graphics() {

    VertexLayout vertexLayout(4, {
        Format::R32G32_SFLOAT,
        Format::R32G32_SFLOAT
    });

    ShaderPipelineInfo shaderInfo(vertexLayout);
    shaderInfo.dynamicStates = false;
    shaderInfo.blendEnable = false;
    shaderInfo.depthTesting = false;
    shaderInfo.offscreenRendering = false;

    graphics.shader = s_context->create_shader({
        {ShaderStage::VERTEX, ProjectRoot + "/shaders/quad.vert"},
        {ShaderStage::FRAGMENT, ProjectRoot + "/shaders/quad.frag"}
    },shaderInfo);

    std::vector<float> vertices = {
            1.0f, 1.0f,    1.0f, 1.0f,
            -1.0f, 1.0f,   0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,   1.0f, 0.0f
    };

    graphics.vertexBuffer = s_context->create_vertex_buffer(vertices.data(), vertices.size(), vertexLayout, BufferUsage::CONSTANT);

    std::vector<uint32_t> indices = {
            0, 1, 2,  2, 3, 0
    };

    graphics.indexBuffer = s_context->create_index_buffer(indices.data(), indices.size(), IndexBufferType::UINT_32, BufferUsage::CONSTANT);

}

EG_RAYTRACER_END
