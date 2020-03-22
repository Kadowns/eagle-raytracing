//
// Created by Novak on 17/03/2020.
//

#include <eagle/raytracer/RenderLayer.h>

EG_RAYTRACER_BEGIN

RenderLayer::RenderEvent RenderLayer::handle_render_event;
RenderLayer::RenderInitEvent RenderLayer::handle_render_init_event;
RenderLayer::RenderDeinitEvent RenderLayer::handle_render_deinit_event;

void RenderLayer::handle_attach() {
    m_context = std::make_shared<VulkanContext>();
    m_context->init(&Application::instance().window());

    handle_render_init_event(m_context);

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

void RenderLayer::handle_deattach() {
    handle_render_deinit_event(m_context);
    m_context->deinit();
}

void RenderLayer::handle_update() {

    m_context->prepare_frame();
    auto cmd = m_context->create_command_buffer();
    cmd->begin_render_pass(m_context->main_render_target());

    handle_render_event(cmd);

    cmd->end_render_pass();
    cmd->finish();
    m_context->submit_command_buffer(cmd);
    m_context->present_frame();
}

void RenderLayer::handle_event(Event &e) {
    m_dispatcher.dispatch(e);

}

EG_RAYTRACER_END
