//
// Created by Novak on 21/03/2020.
//

#ifndef EAGLE_EDITORMASTER_H
#define EAGLE_EDITORMASTER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/editor/EditorWindow.h>
#include <eagle/application/renderer/RenderMaster.h>

EG_RAYTRACER_BEGIN

class EditorMaster {
public:
    struct PushConstBlock {
        glm::vec2 scale;
        glm::vec2 translate;
    } pushConstBlock;
public:
    EditorMaster();
    ~EditorMaster();

    void init();
    void deinit();
    void update();

    static void add_window(const Reference<EditorWindow>& window);
    static void remove_window(const Reference<EditorWindow>& window);

    bool handle_window_resized(WindowResizedEvent &e);
    bool handle_mouse_moved(MouseMoveEvent& e);
    bool handle_mouse_button(MouseButtonEvent &e);
    bool handle_mouse_scrolled(MouseScrolledEvent& e);
    bool handle_key(KeyEvent &e);
    bool handle_key_typed(KeyTypedEvent& e);

private:
    void init_imgui();
    void handle_context_init(RenderingContext &context);
    void handle_command_buffer_main_render_pass(Reference<CommandBuffer> &commandBuffer);
    void update_mouse_cursor();
    void update_buffers();

private:
    RenderMaster::CommandBufferEvent::Listener handle_command_buffer_main_render_pass_callback;
    RenderMaster::Event::Listener handle_context_init_callback;

    Handle<Texture> m_font;
    Handle<Shader> m_shader;
    Handle<DescriptorSetLayout> m_descriptorLayout;
    Handle<DescriptorSet> m_descriptor;
    Handle<IndexBuffer> m_indexBuffer;
    Handle<VertexBuffer> m_vertexBuffer;

    static std::vector<Reference<EditorWindow>> m_windows;
    static bool m_updateWindows;
    Reference<EditorWindow> m_activeWindow;


};

EG_RAYTRACER_END

#endif //EAGLE_EDITORMASTER_H
