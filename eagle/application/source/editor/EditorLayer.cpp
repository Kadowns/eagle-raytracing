//
// Created by Novak on 22/03/2020.
//

#include <eagle/application/editor/EditorLayer.h>
#include <eagle/application/editor/FooWindow.h>

#include <eagle/application/renderer/RenderLayer.h>

EG_RAYTRACER_BEGIN

EditorLayer::EditorLayer() {
    handle_render_init_callback = [&](){
        m_editorMaster.init(RenderMaster::context());
    };

    handle_render_deinit_callback = [&](){
        m_editorMaster.deinit();
    };

    handle_render_draw_callback = [&](Reference<CommandBuffer>& commandBuffer){
        m_editorMaster.render(commandBuffer);
    };

    RenderMaster::handle_render_init += &handle_render_init_callback;
    RenderMaster::handle_render_deinit += &handle_render_deinit_callback;
    RenderMaster::handle_command_buffer_main_render_pass += &handle_render_draw_callback;
}

EditorLayer::~EditorLayer() {
    RenderMaster::handle_render_init -= &handle_render_init_callback;
    RenderMaster::handle_render_deinit -= &handle_render_deinit_callback;
    RenderMaster::handle_command_buffer_main_render_pass -= &handle_render_draw_callback;
}

void EditorLayer::handle_attach() {

    m_dispatcher.add_listener<MouseMoveEvent>([&](Event &e) {
        return m_editorMaster.handle_mouse_moved(*(MouseMoveEvent*) &e);
    });
    m_dispatcher.add_listener<MouseButtonEvent>([&](Event &e) {
        return m_editorMaster.handle_mouse_button(*(MouseButtonEvent*) &e);
    });
    m_dispatcher.add_listener<MouseScrolledEvent>([&](Event &e) {
        return m_editorMaster.handle_mouse_scrolled(*(MouseScrolledEvent*) &e);
    });
    m_dispatcher.add_listener<KeyTypedEvent>([&](Event &e) {
        return m_editorMaster.handle_key_typed(*(KeyTypedEvent*) &e);
    });
    m_dispatcher.add_listener<KeyEvent>([&](Event &e) {
        return m_editorMaster.handle_key(*(KeyEvent*) &e);
    });
    m_dispatcher.add_listener<WindowResizedEvent>([&](Event &e) {
        return m_editorMaster.handle_window_resized(*(WindowResizedEvent*) &e);
    });

    m_editorMaster.add_window(std::make_shared<FooWindow>("Foo"));
}

void EditorLayer::handle_deattach() {

}

void EditorLayer::handle_update() {
    m_editorMaster.update();
}

void EditorLayer::handle_event(Event &e) {
    m_dispatcher.dispatch(e);
}



EG_RAYTRACER_END


