//
// Created by Novak on 17/03/2020.
//

#include <eagle/raytracer/RaytracerLayer.h>

EG_RAYTRACER_BEGIN

void RaytracerLayer::handle_attach() {
    m_context = std::make_shared<VulkanContext>();
    m_context->init(&Application::instance().window());


    m_dispatcher.add_listener<WindowResizedEvent>([&](Event& e){
        auto& resized = *(WindowResizedEvent*)&e;
        m_context->handle_window_resized(resized.get_width(), resized.get_height());
        return false;
    });

    m_dispatcher.add_listener<WindowCloseEvent>([&](Event& e){
        Application::instance().quit();
        return false;
    });
}

void RaytracerLayer::handle_deattach() {
    m_context->deinit();
}

void RaytracerLayer::handle_update() {
    m_context->prepare_frame();
    auto cmd = m_context->create_command_buffer();
    cmd->begin_render_pass(m_context->main_render_target());
    cmd->end_render_pass();
    cmd->finish();
    m_context->submit_command_buffer(cmd);
    m_context->present_frame();
}

void RaytracerLayer::handle_event(Event &e) {
    m_dispatcher.dispatch(e);
}

EG_RAYTRACER_END
