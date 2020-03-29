//
// Created by Novak on 22/03/2020.
//

#include <eagle/raytracer/renderer/RenderMaster.h>
#include <eagle/core/renderer/Shader.h>

EG_RAYTRACER_BEGIN

RenderMaster::InitEvent RenderMaster::handle_render_init;
RenderMaster::DeinitEvent RenderMaster::handle_render_deinit;
RenderMaster::RenderPassDrawEvent RenderMaster::handle_main_render_pass_draw;

Reference<RenderingContext> RenderMaster::s_context;

void RenderMaster::init() {
    Window& window = Application::instance().window();

    screen.width = window.get_width();
    screen.height = window.get_height();

    s_context = std::make_shared<VulkanContext>();
    s_context->init(&window);
    s_context->set_recreation_callback([&](){
        init_compute_target();
        graphics.descriptorSet.lock()->update({compute.imageTarget.lock()->get_image().lock()});
    });

    init_compute();
    init_graphics();

    handle_render_init(s_context);
}

void RenderMaster::update() {
    if (!s_context->prepare_frame()){
        EG_WARNING("Failed to prepare frame!");
        return;
    }

    compute.shader.lock()->dispatch(screen.width / 16, screen.height / 16, 1);

    auto commandBuffer = s_context->create_command_buffer();
    commandBuffer->begin();

    commandBuffer->pipeline_barrier(compute.imageTarget.lock()->get_image().lock()->get_attachment().lock(), ShaderStage::COMPUTE, ShaderStage::FRAGMENT);

    commandBuffer->begin_render_pass(s_context->main_render_target());

    commandBuffer->bind_shader(graphics.shader.lock());
    commandBuffer->bind_vertex_buffer(graphics.vertexBuffer.lock());
    commandBuffer->bind_index_buffer(graphics.indexBuffer.lock());
    commandBuffer->bind_descriptor_sets(graphics.shader.lock(), graphics.descriptorSet.lock(), 0);
    commandBuffer->draw_indexed(graphics.indexBuffer.lock()->get_indices_count(), 0, 0);


    handle_main_render_pass_draw(commandBuffer);
    commandBuffer->end_render_pass();

    commandBuffer->finish();
    commandBuffer->submit();

    s_context->present_frame();
}

void RenderMaster::deinit() {
    handle_render_deinit();
    s_context->deinit();
}

void RenderMaster::handle_window_resized(uint32_t width, uint32_t height) {
    screen.width = width;
    screen.height = height;
    s_context->handle_window_resized(width, height);
}

void RenderMaster::init_compute() {
    compute.shader = s_context->create_compute_shader(ProjectRoot + "/shaders/compute.comp");
    init_compute_target();
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

    graphics.descriptorSet = s_context->create_descriptor_set(graphics.shader.lock()->get_descriptor_set_layout(0).lock(), {compute.imageTarget.lock()->get_image().lock()});


}

void RenderMaster::init_compute_target() {

    if (compute.imageTarget.lock()){
        s_context->destroy_texture_2d(compute.imageTarget.lock());
    }

    Texture2DCreateInfo textureCreateInfo = {};
    textureCreateInfo.usage = TextureUsage::STORAGE;
    textureCreateInfo.width = screen.width;
    textureCreateInfo.height = screen.height;
    textureCreateInfo.filter = Filter::NEAREST;
    textureCreateInfo.layerCount = 1;
    textureCreateInfo.mipLevels = 1;
    textureCreateInfo.format = Format::R8G8B8A8_UNORM;

    compute.imageTarget = s_context->create_texture_2d(textureCreateInfo);
    compute.shader.lock()->update_descriptor_items({compute.imageTarget.lock()->get_image().lock()});


}

EG_RAYTRACER_END
