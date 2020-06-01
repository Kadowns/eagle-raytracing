//
// Created by Novak on 22/03/2020.
//

#include <eagle/application/editor/EditorLayer.h>
#include <eagle/application/renderer/RenderLayer.h>
#include <eagle/application/editor/EditorDockingWindow.h>
#include <eagle/application/editor/SceneWindow.h>
#include <eagle/application/editor/DebugSettingsWindow.h>

EG_RAYTRACER_BEGIN

EditorLayer::EditorLayer() {
    //EditorMaster::add_window(std::make_shared<EditorDockingWindow>());
    EditorMaster::add_window(std::make_shared<DebugSettingsWindow>());
}

EditorLayer::~EditorLayer() {

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

    m_editorMaster.init();

}

void EditorLayer::handle_deattach() {
    m_editorMaster.deinit();
}

void EditorLayer::handle_update() {
    m_editorMaster.update();
}

void EditorLayer::handle_event(Event &e) {
    m_dispatcher.dispatch(e);
}



EG_RAYTRACER_END


