//
// Created by Novak on 29/03/2020.
//

#include <eagle/application/raytracer/RaytracerMaster.h>
#include <eagle/application/EventMaster.h>

EG_RAYTRACER_BEGIN

void RaytracerMaster::init() {

    frame_begin_callback = [&](){
        auto image = m_target.lock()->get_image().lock();
        m_computeShader.lock()->dispatch(image->get_width() / 8, image->get_height() / 8, 1);
    };

    context_recreated = [&](){
        init_render_target();
    };

    command_buffer_begin_callback = [&](const Reference<CommandBuffer>& commandBuffer){
        commandBuffer->pipeline_barrier(m_target.lock()->get_image().lock()->get_attachment().lock(), ShaderStage::COMPUTE, ShaderStage::FRAGMENT);
    };

    RenderMaster::handle_frame_begin += &frame_begin_callback;
    RenderMaster::handle_context_recreated += &context_recreated;
    RenderMaster::handle_command_buffer_begin += &command_buffer_begin_callback;

    m_camera.init();

    m_computeShader = RenderMaster::context().create_compute_shader(ProjectRoot + "/shaders/compute.comp");

    init_render_target();
}

void RaytracerMaster::deinit() {
    RenderMaster::handle_frame_begin -= &frame_begin_callback;
    RenderMaster::handle_context_recreated -= &context_recreated;
    RenderMaster::handle_command_buffer_begin -= &command_buffer_begin_callback;
}

void RaytracerMaster::update() {
    m_camera.update();
    m_cameraUbo.view = m_camera.camera().view_matrix();
    m_cameraUbo.position = m_camera.transform().position;
    auto buffer = m_cameraBuffer.lock();
    buffer->set_bytes(&m_cameraUbo, buffer->size(), 0);
    buffer->update();
}

void RaytracerMaster::init_render_target() {
    if (m_target.lock()){
        RenderMaster::context().destroy_texture_2d(m_target.lock());
    }

    auto& window = Application::instance().window();

    Texture2DCreateInfo textureCreateInfo = {};
    textureCreateInfo.usage = TextureUsage::STORAGE;
    textureCreateInfo.width = window.get_width();
    textureCreateInfo.height = window.get_height();
    textureCreateInfo.filter = Filter::NEAREST;
    textureCreateInfo.layerCount = 1;
    textureCreateInfo.mipLevels = 1;
    textureCreateInfo.format = Format::R8G8B8A8_UNORM;

    m_cameraUbo.view = m_camera.camera().view_matrix();
    m_cameraUbo.position = m_camera.transform().position;
    m_cameraUbo.inverseProjection = glm::inverse(m_camera.camera().projection_matrix());
    if (!m_cameraBuffer.lock()){
        m_cameraBuffer = RenderMaster::context().create_uniform_buffer(sizeof(m_cameraUbo), &m_cameraUbo);
    }
    else{
        auto buffer = m_cameraBuffer.lock();
        buffer->set_bytes(&m_cameraUbo, buffer->size(), 0);
        buffer->update();
    }

    m_target = RenderMaster::context().create_texture_2d(textureCreateInfo);
    m_computeShader.lock()->update_descriptor_items({m_target.lock()->get_image().lock(), m_cameraBuffer.lock()});
    EventMaster::instance().emit(OnRaytracerTargetCreated(m_target.lock()));
}



EG_RAYTRACER_END
