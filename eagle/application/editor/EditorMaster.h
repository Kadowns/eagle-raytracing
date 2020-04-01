//
// Created by Novak on 21/03/2020.
//

#ifndef EAGLE_EDITORMASTER_H
#define EAGLE_EDITORMASTER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

#include <eagle/application/editor/EditorWindow.h>

EG_RAYTRACER_BEGIN

class EditorMaster {
public:
    struct PushConstBlock {
        glm::vec2 scale;
        glm::vec2 translate;
    } pushConstBlock;
public:
    void init(RenderingContext &context);
    void deinit();
    void update();
    void render(Reference <Eagle::CommandBuffer> &commandBuffer);

    void add_window(const Reference<EditorWindow>& window);
    void remove_window(const Reference<EditorWindow>& window);

    bool handle_window_resized(WindowResizedEvent &e);
    bool handle_mouse_moved(MouseMoveEvent& e);
    bool handle_mouse_button(MouseButtonEvent &e);
    bool handle_mouse_scrolled(MouseScrolledEvent& e);
    bool handle_key(KeyEvent &e);
    bool handle_key_typed(KeyTypedEvent& e);

private:
    void update_mouse_cursor();
    void update_buffers();

private:
    Handle<Texture2D> m_font;
    Handle<Shader> m_shader;
    Handle<DescriptorSetLayout> m_descriptorLayout;
    Handle<DescriptorSet> m_descriptor;
    Handle<IndexBuffer> m_indexBuffer;
    Handle<VertexBuffer> m_vertexBuffer;

    std::vector<Reference<EditorWindow>> m_windows;
    Reference<EditorWindow> m_activeWindow;

    bool m_updateWindows;
};

EG_RAYTRACER_END

#endif //EAGLE_EDITORMASTER_H
