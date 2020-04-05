//
// Created by Novak on 29/03/2020.
//

#include <eagle/application/raytracer/RaytracerMaster.h>
#include <eagle/application/editor/ComputeDataEditor.h>
#include <eagle/application/renderer/TextureLoader.h>
#include <eagle/application/editor/EditorMaster.h>

EG_RAYTRACER_BEGIN

void RaytracerMaster::init() {

    context_init_callback = [&](){
        handle_context_init();
    };

    context_deinit_callback = [&](){
        handle_context_deinit();
    };

    frame_begin_callback = [&](){
        handle_frame_begin();
    };

    context_recreated_callback = [&](){
        init_render_target();
    };

    command_buffer_begin_callback = [&](const Reference<CommandBuffer>& commandBuffer){
        handle_command_buffer_begin(commandBuffer);
    };

    command_buffer_main_render_pass_callback = [&](const Reference<CommandBuffer>& commandBuffer){
        handle_command_buffer_main_render_pass(commandBuffer);
    };

    RenderMaster::handle_context_init += &context_init_callback;
    RenderMaster::handle_context_deinit += &context_deinit_callback;
    RenderMaster::handle_frame_begin += &frame_begin_callback;
    RenderMaster::handle_context_recreated += &context_recreated_callback;
    RenderMaster::handle_command_buffer_begin += &command_buffer_begin_callback;
    RenderMaster::handle_command_buffer_main_render_pass += &command_buffer_main_render_pass_callback;

    EditorMaster::add_window(std::make_shared<ComputeDataEditor>(m_computeData, [&](){
        init_spheres();
        m_spheresBuffer.lock()->set_data(m_spheres.data(), sizeof(Sphere) * MAX_SPHERES, 0);
        m_spheresBuffer.lock()->push();
        m_computeUbo.sampleCount = 0;
    }));


    Random::init();

    m_camera.init();
    m_computeData.light = Transform(glm::vec3(0), glm::quat(glm::radians(glm::vec3(-30, 90, 0))), glm::vec3(1));
    m_computeUbo.light = glm::vec4(m_computeData.light.front(), 1.0f);

    init_spheres();
}

void RaytracerMaster::deinit() {
    RenderMaster::handle_context_init -= &context_init_callback;
    RenderMaster::handle_context_deinit -= &context_deinit_callback;
    RenderMaster::handle_frame_begin -= &frame_begin_callback;
    RenderMaster::handle_context_recreated -= &context_recreated_callback;
    RenderMaster::handle_command_buffer_begin -= &command_buffer_begin_callback;
    RenderMaster::handle_command_buffer_main_render_pass -= &command_buffer_main_render_pass_callback;
}

void RaytracerMaster::update() {

    m_camera.update();
    m_computeUbo.view = m_camera.camera().view_matrix();
    m_computeUbo.position = m_camera.transform().position();
    m_computeUbo.pixelOffset = glm::vec2(Random::value(), Random::value());
    m_computeUbo.sampleCount++;
    m_computeUbo.sphereCount = m_spheres.size();

    if (m_computeData.light.hasChanged){
        m_computeUbo.light = glm::vec4(m_computeData.light.front(), 1.0f);
        m_computeUbo.sampleCount = 0;
        m_computeData.light.hasChanged = false;
    }

    if (m_camera.transform().hasChanged){
        m_computeUbo.sampleCount = 0;
        m_camera.transform().hasChanged = false;
    }

    auto buffer = m_cameraBuffer.lock();
    buffer->set_bytes(&m_computeUbo, buffer->size(), 0);
    buffer->update();
}

void RaytracerMaster::init_render_target() {
    if (m_computeTarget.lock()){
        RenderMaster::context().destroy_texture_2d(m_computeTarget.lock());
    }

    auto& window = Application::instance().window();

    TextureCreateInfo textureCreateInfo = {};
    textureCreateInfo.usage = TextureUsage::STORAGE;
    textureCreateInfo.width = window.get_width();
    textureCreateInfo.height = window.get_height();
    textureCreateInfo.filter = Filter::NEAREST;
    textureCreateInfo.layerCount = 1;
    textureCreateInfo.mipLevels = 1;
    textureCreateInfo.format = Format::R8G8B8A8_UNORM;


    m_camera.camera().set_aspect_ratio(window.get_width() / (float)window.get_height());
    m_computeUbo.view = m_camera.camera().view_matrix();
    m_computeUbo.position = m_camera.transform().position();
    m_computeUbo.inverseProjection = glm::inverse(m_camera.camera().projection_matrix());
    if (!m_cameraBuffer.lock()){
        m_cameraBuffer = RenderMaster::context().create_uniform_buffer(sizeof(m_computeUbo), &m_computeUbo);
    }
    else {
        auto buffer = m_cameraBuffer.lock();
        buffer->set_bytes(&m_computeUbo, buffer->size(), 0);
        buffer->update();
    }

    m_computeTarget = RenderMaster::context().create_texture(textureCreateInfo);
    m_computeShader.lock()->update_descriptor_items({m_computeTarget.lock()->get_image().lock(), m_cameraBuffer.lock(), m_spheresBuffer.lock(), m_skybox.lock()->get_image().lock()});

    if (m_quadDescriptorSet.lock()){
        m_quadDescriptorSet.lock()->update({m_computeTarget.lock()->get_image().lock()});
    }
    else {
        m_quadDescriptorSet = RenderMaster::context().create_descriptor_set(m_quadShader.lock()->get_descriptor_set_layout(0).lock(), {m_computeTarget.lock()->get_image().lock()});
    }
    m_computeUbo.sampleCount = 0;
}

void RaytracerMaster::handle_frame_begin() {
    auto image = m_computeTarget.lock()->get_image().lock();
    m_computeShader.lock()->dispatch(image->get_width() / 16, image->get_height() / 16, 1);

}

void RaytracerMaster::handle_command_buffer_begin(const Reference<CommandBuffer>& commandBuffer) {
    commandBuffer->pipeline_barrier(m_computeTarget.lock()->get_image().lock()->get_attachment().lock(), ShaderStage::COMPUTE, ShaderStage::FRAGMENT);
}

void RaytracerMaster::handle_command_buffer_main_render_pass(const Reference<CommandBuffer> &commandBuffer) {
    commandBuffer->bind_shader(m_quadShader.lock());
    commandBuffer->bind_descriptor_sets(m_quadShader.lock(), m_quadDescriptorSet.lock(), 0);
    commandBuffer->draw(3);
}

void RaytracerMaster::handle_context_init() {
    m_computeShader = RenderMaster::context().create_compute_shader(ProjectRoot + "/shaders/compute.comp");

    TextureCreateInfo skyboxCreateInfo = TextureLoader::load_pixels(ProjectRoot + "/textures/stars.hdr");
    skyboxCreateInfo.filter = Filter::LINEAR;
    skyboxCreateInfo.usage = TextureUsage::READ;
    m_skybox = RenderMaster::context().create_texture(skyboxCreateInfo);


    m_spheresBuffer = RenderMaster::context().create_storage_buffer(sizeof(Sphere) * MAX_SPHERES, m_spheres.data(),
                                                                    BufferUsage::DYNAMIC);

    ShaderPipelineInfo pipelineInfo = {};
    pipelineInfo.offscreenRendering = true;
    pipelineInfo.blendEnable = true;

    m_quadShader = RenderMaster::context().create_shader({
       {ShaderStage::VERTEX, ProjectRoot + "/shaders/quad.vert"},
       {ShaderStage::FRAGMENT, ProjectRoot + "/shaders/quad.frag"}
    }, pipelineInfo);

    init_render_target();
}

void RaytracerMaster::handle_context_deinit() {

}

void RaytracerMaster::init_spheres() {
    m_spheres.clear();
    // Add a number of random spheres
    for (int i = 0; i < m_computeData.maxSphereCount; i++) {
        Sphere sphere = {};
        // Radius and radius
        sphere.radius = m_computeData.sphereSizes.x + Random::value() * (m_computeData.sphereSizes.y - m_computeData.sphereSizes.x);
        glm::vec2 randomPos = random_inside_unit_circle() * m_computeData.spherePlacementRadius;
        sphere.position = glm::vec3(randomPos.x, sphere.radius, randomPos.y);
        // Reject spheres that are intersecting others
        bool skipSphere = false;
        for (auto& other : m_spheres) {
            float minDist = sphere.radius + other.radius;
            if (glm::length2(sphere.position - other.position) < minDist * minDist){
                skipSphere = true;
                break;
            }
        }
        if (skipSphere){
            continue;
        }
        // Albedo and specular color
        glm::vec3 color = glm::vec3(Random::value(), Random::value(), Random::value());
        bool metal = Random::value() < m_computeData.metalPercent;
        sphere.albedo = metal ? glm::vec3(0.01f) : glm::vec3(color.r, color.g, color.b);
        sphere.specular = metal ? glm::vec3(color.r, color.g, color.b) : glm::vec3(0.01f);
        // Add the sphere to the list
        m_spheres.emplace_back(sphere);
    }
}

glm::vec2 RaytracerMaster::random_inside_unit_circle() {
    return glm::normalize(glm::vec2(Random::range(-1.0f, 1.0f), Random::range(-1.0f, 1.0f))) * Random::value();
}


EG_RAYTRACER_END
