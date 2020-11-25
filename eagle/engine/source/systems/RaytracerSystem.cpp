//
// Created by Novak on 09/04/2020.
//

#include <eagle/engine/systems/RaytracerSystem.h>
#include <eagle/engine/renderer/TextureLoader.h>
#include <eagle/engine/components/Camera.h>
#include <eagle/engine/components/Transform.h>
#include <eagle/engine/components/DirectionalLight.h>
#include <eagle/engine/components/SceneData.h>
#include <eagle/engine/components/RaytracerData.h>
#include <eagle/engine/components/SingletonComponent.h>

EG_ENGINE_BEGIN

RaytracerSystem::RaytracerSystem() {
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
}

RaytracerSystem::~RaytracerSystem() {
    RenderMaster::handle_context_init -= &context_init_callback;
    RenderMaster::handle_context_deinit -= &context_deinit_callback;
    RenderMaster::handle_frame_begin -= &frame_begin_callback;
    RenderMaster::handle_context_recreated -= &context_recreated_callback;
    RenderMaster::handle_command_buffer_begin -= &command_buffer_begin_callback;
    RenderMaster::handle_command_buffer_main_render_pass -= &command_buffer_main_render_pass_callback;
}

void RaytracerSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    events.subscribe<OnCameraUpdate>(*this);
    events.subscribe<OnLightUpdate>(*this);
    events.subscribe<entityx::ComponentAddedEvent<Sphere>>(*this);
    events.subscribe<entityx::ComponentAddedEvent<Box>>(*this);
    events.subscribe<entityx::ComponentRemovedEvent<Sphere>>(*this);
    events.subscribe<entityx::ComponentRemovedEvent<Box>>(*this);
    update_sphere_buffer(entities);
    update_box_buffer(entities);
}

void RaytracerSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {

    for (auto e : entities.entities_with_components<Transform, Sphere>()) {
        Transform &transform = *e.component<Transform>();
        if (transform.hasChanged) {
            m_updateSpheres = true;
            transform.hasChanged = false;
        }
    }

    if (m_updateSpheres) {
        update_sphere_buffer(entities);
        m_updateSpheres = false;
    }

    for (auto e : entities.entities_with_components<Transform, Box>()) {
        Transform &transform = *e.component<Transform>();
        if (transform.hasChanged) {
            m_updateBoxes = true;
            transform.hasChanged = false;
        }
    }

    if (m_updateBoxes) {
        update_box_buffer(entities);
        m_updateBoxes = false;
    }

    RaytracerData &data = SingletonComponent::get<RaytracerData>();
    data.ubo.pixelOffset = glm::vec2(Random::value(), Random::value());
    auto buffer = data.uniformBuffer.lock();
    buffer->set_data(&data.ubo, buffer->size(), 0);
    buffer->push();
    data.ubo.sampleCount++;
}

void RaytracerSystem::init_render_target() {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();

    EG_TRACE("BEGIN");

    if (data.compute.color.lock()){
        RenderMaster::context().destroy_texture_2d(data.compute.color.lock());
    }

    if (data.compute.depth.lock()){
        RenderMaster::context().destroy_texture_2d(data.compute.depth.lock());
    }

    auto& window = Application::instance().window();

    TextureCreateInfo textureCreateInfo = {};
    textureCreateInfo.filter = Filter::NEAREST;
    textureCreateInfo.imageCreateInfo.usages = {ImageUsage::STORAGE, ImageUsage::SAMPLED};
    textureCreateInfo.imageCreateInfo.layout = ImageLayout::GENERAL;
    textureCreateInfo.imageCreateInfo.aspects = {ImageAspect::COLOR};
    textureCreateInfo.imageCreateInfo.format = Format::R8G8B8A8_UNORM;
    textureCreateInfo.imageCreateInfo.memoryProperties = {MemoryProperty::DEVICE_LOCAL};
    textureCreateInfo.imageCreateInfo.tiling = ImageTiling::OPTIMAL;
    textureCreateInfo.imageCreateInfo.width = window.get_width();
    textureCreateInfo.imageCreateInfo.height = window.get_height();
    textureCreateInfo.imageCreateInfo.mipLevels = 1;
    textureCreateInfo.imageCreateInfo.arrayLayers = 1;

    data.compute.color = RenderMaster::context().create_texture(textureCreateInfo);


    textureCreateInfo.filter = Filter::NEAREST;
    textureCreateInfo.imageCreateInfo.usages = {ImageUsage::STORAGE, ImageUsage::DEPTH_STENCIL_ATTACHMENT};
    textureCreateInfo.imageCreateInfo.layout = ImageLayout::GENERAL;
    textureCreateInfo.imageCreateInfo.aspects = {ImageAspect::COLOR, ImageAspect::DEPTH};
    textureCreateInfo.imageCreateInfo.format = Format::D32_SFLOAT;
    textureCreateInfo.imageCreateInfo.memoryProperties = {MemoryProperty::DEVICE_LOCAL};
    textureCreateInfo.imageCreateInfo.tiling = ImageTiling::OPTIMAL;
    textureCreateInfo.imageCreateInfo.width = window.get_width();
    textureCreateInfo.imageCreateInfo.height = window.get_height();
    textureCreateInfo.imageCreateInfo.mipLevels = 1;
    textureCreateInfo.imageCreateInfo.arrayLayers = 1;

    data.compute.depth = RenderMaster::context().create_texture(textureCreateInfo);



    data.ubo.sampleCount = 0;
    if (!data.uniformBuffer.lock()){
        data.uniformBuffer= RenderMaster::context().create_uniform_buffer(sizeof(data.ubo), &data.ubo);
    }
    else {
        auto buffer = data.uniformBuffer.lock();
        buffer->set_data(&data.ubo, buffer->size(), 0);
        buffer->push();
    }
    if (!data.quad.descriptorSet.lock()){
        data.quad.descriptorSet = RenderMaster::context().create_descriptor_set(
                data.quad.shader.lock()->get_descriptor_set_layout(0).lock(),
                {
                    data.compute.color.lock(),
                    data.compute.depth.lock()
                }
                );
    }
    else{
        data.quad.descriptorSet.lock()->update({
            data.compute.color.lock(),
            data.compute.depth.lock()
        });
    }

    data.compute.shader.lock()->update_descriptor_items({
        data.compute.color.lock()->image(),
        data.compute.depth.lock()->image(),
        data.uniformBuffer.lock(),
        data.compute.spheresBuffer.lock(),
        data.compute.boxesBuffer.lock(),
        data.compute.skybox.lock()->image()
    });

    EventMaster::instance().emit(OnRaytracerTargetCreated(data.compute.color.lock()->image()));
    EG_TRACE("END");
}

void RaytracerSystem::handle_context_init() {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    data.compute.shader = RenderMaster::context().create_compute_shader(ProjectRoot + "/shaders/compute.comp");
    data.compute.skybox = RenderMaster::context().create_texture(TextureLoader::load_pixels(ProjectRoot + "/textures/stars.hdr"));
    data.compute.spheresBuffer = RenderMaster::context().create_storage_buffer(sizeof(RaytracerData::SphereData) * data.spheresData.size(), data.spheresData.data(), BufferUsage::DYNAMIC);
    data.compute.boxesBuffer = RenderMaster::context().create_storage_buffer(sizeof(RaytracerData::BoxData) * data.boxesData.size(), data.boxesData.data(), BufferUsage::DYNAMIC);

    ShaderPipelineInfo pipelineInfo = {RenderMaster::context().main_render_pass()};
    data.quad.shader = RenderMaster::context().create_shader({
        {ShaderStage::VERTEX, ProjectRoot + "/shaders/quad.vert"},
        {ShaderStage::FRAGMENT, ProjectRoot + "/shaders/quad.frag"},
    }, pipelineInfo);

    std::vector<float> vertices = {
            -1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
    };

    auto vertexLayout = VertexLayout(3, {Format::R32G32B32_SFLOAT});

    data.offlineRenderpass.vertexBuffer = RenderMaster::context().create_vertex_buffer(vertices.data(), vertices.size(), vertexLayout, BufferUsage::CONSTANT);

    init_render_target();
    init_offline_render_pass();
}

void RaytracerSystem::handle_context_deinit() {

}

void RaytracerSystem::handle_frame_begin() {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    auto image = data.compute.color.lock()->image();
    data.compute.shader.lock()->dispatch(image->width() / 16, image->height() / 16, 1);
}

void RaytracerSystem::handle_command_buffer_begin(const Reference<CommandBuffer> &commandBuffer) {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    commandBuffer->pipeline_barrier(data.compute.color.lock()->image(), ShaderStage::COMPUTE, ShaderStage::FRAGMENT);
    commandBuffer->pipeline_barrier(data.compute.depth.lock()->image(), ShaderStage::COMPUTE, ShaderStage::FRAGMENT);

    commandBuffer->begin_render_pass(data.offlineRenderpass.renderPass.lock(), data.offlineRenderpass.framebuffer.lock());
    commandBuffer->bind_shader(data.offlineRenderpass.shader.lock());
    commandBuffer->bind_vertex_buffer(data.offlineRenderpass.vertexBuffer.lock());
    commandBuffer->draw(4);
    commandBuffer->end_render_pass();
}

void RaytracerSystem::handle_command_buffer_main_render_pass(const Reference<CommandBuffer> &commandBuffer) {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    commandBuffer->bind_shader(data.quad.shader.lock());
    commandBuffer->bind_descriptor_sets(data.quad.descriptorSet.lock(), 0);
    commandBuffer->draw(3);
}

void RaytracerSystem::receive(const OnCameraUpdate &ev) {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    data.ubo.sampleCount = 0;
    data.ubo.view = ev.camera.view_matrix();
    data.ubo.inverseProjection = glm::inverse(ev.camera.projection_matrix());
    data.ubo.position = ev.camera.position();
}

void RaytracerSystem::receive(const OnLightUpdate &ev) {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    data.ubo.sampleCount = 0;
    data.ubo.light = glm::vec4(ev.light.direction, ev.light.intensity);
}

void RaytracerSystem::update_sphere_buffer(entityx::EntityManager &entities) {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    entityx::ComponentHandle<Transform> transform;
    entityx::ComponentHandle<Sphere> sphere;
    auto it = data.spheresData.begin();
    for (auto e : entities.entities_with_components<Transform, Sphere>(transform, sphere)){
        it->radius = sphere->radius;
        it->albedo = sphere->albedo;
        it->specular = sphere->specular;
        it->position = transform->position();
        it++;
        if (it == data.spheresData.end()){
            EG_WARNING("Maximum sphere capacity reached!");
            break;
        }
    }
    data.ubo.sphereCount = it - data.spheresData.begin();
    if (auto buffer = data.compute.spheresBuffer.lock()){
        buffer->set_data(data.spheresData.data(), sizeof(RaytracerData::SphereData) * data.ubo.sphereCount, 0);
        buffer->push();
        data.ubo.sampleCount = 0;
    }
}

void RaytracerSystem::update_box_buffer(entityx::EntityManager &entities) {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    entityx::ComponentHandle<Transform> transform;
    entityx::ComponentHandle<Box> box;
    auto it = data.boxesData.begin();
    for (auto e : entities.entities_with_components<Transform, Box>(transform, box)){
        it->radius = box->radius;
        it->albedo = box->albedo;
        it->specular = box->specular;
        it->center = transform->position();
        it->rotation = glm::mat4_cast(transform->rotation());
        it->inverseRotation = glm::inverse(it->rotation);
        it++;
        if (it == data.boxesData.end()){
            EG_WARNING("Maximum box capacity reached!");
            break;
        }
    }
    data.ubo.boxCount = it - data.boxesData.begin();
    if (auto buffer = data.compute.boxesBuffer.lock()){
        buffer->set_data(data.boxesData.data(), sizeof(RaytracerData::BoxData) * data.ubo.boxCount, 0);
        buffer->push();
        data.ubo.sampleCount = 0;
    }
}


void RaytracerSystem::receive(const entityx::ComponentAddedEvent<Sphere> &ev) {
    m_updateSpheres = true;
}

void RaytracerSystem::receive(const entityx::ComponentRemovedEvent<Sphere> &ev) {
    m_updateSpheres = true;
}

void RaytracerSystem::receive(const entityx::ComponentAddedEvent<Box> &ev) {
    m_updateBoxes = true;
}

void RaytracerSystem::receive(const entityx::ComponentRemovedEvent<Box> &ev) {
    m_updateBoxes = true;
}

void RaytracerSystem::init_offline_render_pass() {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();

    RenderAttachmentDescription colorAttachment = {};
    colorAttachment.format = Format::R8G8B8A8_UNORM;
    colorAttachment.loadOp = AttachmentLoadOperator::LOAD;
    colorAttachment.storeOp = AttachmentStoreOperator::STORE;
    colorAttachment.initialLayout = ImageLayout::UNDEFINED;
    colorAttachment.finalLayout = ImageLayout::SHADER_READ_ONLY_OPTIMAL;

    RenderAttachmentDescription depthAttachment = {};
    depthAttachment.format = Format::D32_SFLOAT;
    depthAttachment.loadOp = AttachmentLoadOperator::LOAD;
    depthAttachment.storeOp = AttachmentStoreOperator::DONT_CARE;
    depthAttachment.initialLayout = ImageLayout::GENERAL;
    depthAttachment.finalLayout = ImageLayout::DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    data.offlineRenderpass.renderPass = RenderMaster::context().create_render_pass({colorAttachment}, depthAttachment);


    auto& window = Application::instance().window();


    FramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.renderPass = data.offlineRenderpass.renderPass.lock();
    framebufferCreateInfo.width = window.get_width();
    framebufferCreateInfo.height = window.get_height();
    framebufferCreateInfo.attachments = {data.compute.color.lock()->image(), data.compute.depth.lock()->image()};

    data.offlineRenderpass.framebuffer = RenderMaster::context().create_framebuffer(framebufferCreateInfo);

    ShaderPipelineInfo pipelineInfo = {data.offlineRenderpass.renderPass.lock()};
    pipelineInfo.primitiveTopology = PrimitiveTopology::LINE_LIST;
    pipelineInfo.depthTesting = true;
    pipelineInfo.blendEnable = true;
    pipelineInfo.vertexLayout = VertexLayout(3, {Format::R32G32B32_SFLOAT});
    data.offlineRenderpass.shader = RenderMaster::context().create_shader({
        {ShaderStage::VERTEX, ProjectRoot + "/shaders/gizmos.vert"},
        {ShaderStage::FRAGMENT, ProjectRoot + "/shaders/gizmos.frag"},
        }, pipelineInfo);
}


EG_ENGINE_END
