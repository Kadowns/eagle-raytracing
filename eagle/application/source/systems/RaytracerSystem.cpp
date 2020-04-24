//
// Created by Novak on 09/04/2020.
//

#include <eagle/application/systems/RaytracerSystem.h>
#include <eagle/application/renderer/TextureLoader.h>
#include <eagle/application/components/Camera.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/DirectionalLight.h>
#include <eagle/application/components/SceneData.h>
#include <eagle/application/components/RaytracerData.h>
#include <eagle/application/components/SingletonComponent.h>

EG_RAYTRACER_BEGIN

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
    events.subscribe<entityx::ComponentRemovedEvent<Sphere>>(*this);
    update_sphere_buffer(entities);
}

void RaytracerSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    if (m_updateSpheres){
        update_sphere_buffer(entities);
        m_updateSpheres = false;
    }

    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    data.ubo.pixelOffset = glm::vec2(Random::value(), Random::value());
    auto buffer = data.uniformBuffer.lock();
    buffer->set_data(&data.ubo, buffer->size(), 0);
    buffer->push();
    data.ubo.sampleCount++;
}

void RaytracerSystem::init_render_target() {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();

    if (data.computeTarget.lock()){
        RenderMaster::context().destroy_texture_2d(data.computeTarget.lock());
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

    data.computeTarget = RenderMaster::context().create_texture(textureCreateInfo);

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
        data.quad.descriptorSet = RenderMaster::context().create_descriptor_set(data.quad.shader.lock()->get_descriptor_set_layout(0).lock(), {data.computeTarget.lock()->get_image().lock()});
    }
    else{
        data.quad.descriptorSet.lock()->update({data.computeTarget.lock()->get_image().lock()});
    }

    data.computeShader.lock()->update_descriptor_items({data.computeTarget.lock()->get_image().lock(), data.uniformBuffer.lock(), data.spheresBuffer.lock(), data.skybox.lock()->get_image().lock()});

    EventMaster::instance().emit(OnRaytracerTargetCreated(data.computeTarget.lock()->get_image().lock()));
}

void RaytracerSystem::handle_context_init() {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    data.computeShader = RenderMaster::context().create_compute_shader(ProjectRoot + "/shaders/compute.comp");

    TextureCreateInfo skyboxCreateInfo = TextureLoader::load_pixels(ProjectRoot + "/textures/stars.hdr");
    skyboxCreateInfo.filter = Filter::LINEAR;
    skyboxCreateInfo.usage = TextureUsage::READ;
    data.skybox = RenderMaster::context().create_texture(skyboxCreateInfo);

    data.spheresBuffer = RenderMaster::context().create_storage_buffer(sizeof(RaytracerData::SphereData) * data.spheresData.size(), data.spheresData.data(),
                                                                    BufferUsage::DYNAMIC);

    ShaderPipelineInfo pipelineInfo = {};
    data.quad.shader = RenderMaster::context().create_shader({
        {ShaderStage::VERTEX, ProjectRoot + "/shaders/quad.vert"},
        {ShaderStage::FRAGMENT, ProjectRoot + "/shaders/quad.frag"},
    }, pipelineInfo);


    init_render_target();
}

void RaytracerSystem::handle_context_deinit() {

}

void RaytracerSystem::handle_frame_begin() {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    auto image = data.computeTarget.lock()->get_image().lock();
    data.computeShader.lock()->dispatch(image->get_width() / 16, image->get_height() / 16, 1);
}

void RaytracerSystem::handle_command_buffer_begin(const Reference<CommandBuffer> &commandBuffer) {
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    commandBuffer->pipeline_barrier(data.computeTarget.lock()->get_image().lock()->get_attachment().lock(), ShaderStage::COMPUTE, ShaderStage::FRAGMENT);
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
    if (auto buffer = data.spheresBuffer.lock()){
        buffer->set_data(data.spheresData.data(), sizeof(RaytracerData::SphereData) * data.ubo.sphereCount, 0);
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

EG_RAYTRACER_END
