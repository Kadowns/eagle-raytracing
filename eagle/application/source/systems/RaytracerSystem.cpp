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
#include <eagle/application/components/Sphere.h>

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

    RenderMaster::handle_context_init += &context_init_callback;
    RenderMaster::handle_context_deinit += &context_deinit_callback;
    RenderMaster::handle_frame_begin += &frame_begin_callback;
    RenderMaster::handle_context_recreated += &context_recreated_callback;
    RenderMaster::handle_command_buffer_begin += &command_buffer_begin_callback;
}

RaytracerSystem::~RaytracerSystem() {
    RenderMaster::handle_context_init -= &context_init_callback;
    RenderMaster::handle_context_deinit -= &context_deinit_callback;
    RenderMaster::handle_frame_begin -= &frame_begin_callback;
    RenderMaster::handle_context_recreated -= &context_recreated_callback;
    RenderMaster::handle_command_buffer_begin -= &command_buffer_begin_callback;
}

void RaytracerSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    events.subscribe<OnCameraUpdate>(*this);
    events.subscribe<OnLightUpdate>(*this);
    generate_scene(entities);
}

void RaytracerSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
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


    data.spheresBuffer = RenderMaster::context().create_storage_buffer(sizeof(RaytracerData::SphereData) * MAX_SPHERES, data.spheresData.data(),
                                                                    BufferUsage::DYNAMIC);

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

void RaytracerSystem::generate_scene(entityx::EntityManager &entities) {
    for (auto e : entities.entities_with_components<Transform, Sphere>()){
        e.destroy();
    }

    SceneData& scene = SingletonComponent::get<SceneData>();
    RaytracerData& data = SingletonComponent::get<RaytracerData>();
    data.spheresData.clear();
    // Add a number of random spheres
    for (int i = 0; i < scene.maxSphereCount; i++) {
        auto e = entities.create();
        auto sphere = e.assign<Sphere>();
        auto transform = e.assign<Transform>();
        // Radius and radius
        sphere->radius = scene.sphereSizes.x + Random::value() * (scene.sphereSizes.y - scene.sphereSizes.x);
        glm::vec2 randomPos = random_inside_unit_circle() * scene.spherePlacementRadius;
        transform->set_position(glm::vec3(randomPos.x, sphere->radius, randomPos.y));
        // Reject spheres that are intersecting others
        bool skipSphere = false;
        for (auto other : entities.entities_with_components<Sphere, Transform>()) {
            if (e == other) continue;

            auto otherSphere = other.component<Sphere>();
            auto otherTransform = other.component<Transform>();
            float minDist = sphere->radius + otherSphere->radius;
            if (glm::length2(transform->position() - otherTransform->position()) < minDist * minDist){
                skipSphere = true;
                break;
            }
        }
        if (skipSphere){
            continue;
        }
        // Albedo and specular color
        glm::vec3 color = glm::vec3(Random::value(), Random::value(), Random::value());
        bool metal = Random::value() < scene.metalPercent;
        sphere->albedo = metal ? glm::vec3(0.01f) : glm::vec3(color.r, color.g, color.b);
        sphere->specular = metal ? glm::vec3(color.r, color.g, color.b) : glm::vec3(0.01f);

        //adds sphere to the buffer that will be uploaded to the gpu
        RaytracerData::SphereData sphereData = {};
        sphereData.position = transform->position();
        sphereData.radius = sphere->radius;
        sphereData.albedo = sphere->albedo;
        sphereData.specular = sphere->specular;
        data.spheresData.emplace_back(sphereData);
    }
    data.ubo.sphereCount = data.spheresData.size();

    if (data.spheresBuffer.lock()){
        data.spheresBuffer.lock()->set_data(data.spheresData.data(), sizeof(RaytracerData::SphereData) * data.spheresData.size(), 0);
        data.spheresBuffer.lock()->push();
        data.ubo.sampleCount = 0;
    }
}

glm::vec2 RaytracerSystem::random_inside_unit_circle() {
    return glm::normalize(glm::vec2(Random::range(-1.0f, 1.0f), Random::range(-1.0f, 1.0f))) * Random::value();
}

EG_RAYTRACER_END
