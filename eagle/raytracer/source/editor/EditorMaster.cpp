//
// Created by Novak on 22/03/2020.
//

#include <eagle/raytracer/editor/EditorMaster.h>
#include <imgui/imgui.h>

EG_RAYTRACER_BEGIN

void EditorMaster::init(Reference<RenderingContext> &context) {

    ImGui::CreateContext();

    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.26f, 0.25f, 0.7f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.46f, 0.4f, 0.46f, 0.8f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.16f, 0.15f, 0.4f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.3f, 0.32f, 0.3f, 0.4f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.6f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.125f, 0.12f, 1.0f);
    style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.12f, 0.125f, 0.12f, 1.0f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.215f, 0.215f, 0.75f, 1.0f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.2f, 0.215f, 0.75f, 1.0f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.4f, 0.475f, 0.45f, 0.8f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.65f, 0.6f, 0.65f, 0.8f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.5f, 0.55f, 0.8f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.4f, 0.45f, 0.6f, 0.8f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.55f, 0.55f, 0.7f, 0.8f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.35f, 0.35f, 0.365f, 0.8f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.45f, 0.45f, 0.46f, 0.8f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.45f, 0.4f, 0.425f, 0.8f);
    style.ChildRounding = 2;
    style.FrameRounding = 2;
    style.GrabRounding = 2;
    style.PopupRounding = 1;
    style.WindowRounding = 2;
    style.WindowPadding = ImVec2(2, 2);

    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)

    io.KeyMap[ImGuiKey_Tab] = EG_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = EG_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = EG_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = EG_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = EG_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = EG_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = EG_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = EG_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = EG_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = EG_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = EG_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = EG_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = EG_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = EG_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = EG_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = EG_KEY_A;
    io.KeyMap[ImGuiKey_C] = EG_KEY_C;
    io.KeyMap[ImGuiKey_V] = EG_KEY_V;
    io.KeyMap[ImGuiKey_X] = EG_KEY_X;
    io.KeyMap[ImGuiKey_Y] = EG_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = EG_KEY_Z;


    io.DisplaySize = ImVec2(Application::instance().window().get_width(), Application::instance().window().get_height());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    Pixel *pixels;
    Texture2DCreateInfo fontCreateInfo = {};
    io.Fonts->GetTexDataAsRGBA32(&pixels, &fontCreateInfo.width, &fontCreateInfo.height);
    fontCreateInfo.format = Format::R8G8B8A8_UNORM;
    fontCreateInfo.filter = Filter::LINEAR;
    fontCreateInfo.layerCount = 1;
    fontCreateInfo.mipLevels = 1;
    fontCreateInfo.pixels = std::vector<Pixel>(pixels,
                                               pixels + fontCreateInfo.width * fontCreateInfo.height * 4);


    m_font = context->create_texture_2d(fontCreateInfo);


    VertexLayout vertexLayout = VertexLayout(5, {
            Format::R32G32_SFLOAT,
            Format::R32G32_SFLOAT,
            Format::R8G8B8A8_UNORM
    });


    DescriptorBindingDescription binding = {};
    binding.shaderStage = ShaderStage::FRAGMENT;
    binding.descriptorType = DescriptorType::SAMPLED_IMAGE_2D;
    binding.binding = 0;

    m_descriptorLayout = context->create_descriptor_set_layout({binding});


    ShaderPipelineInfo pipelineInfo = ShaderPipelineInfo(vertexLayout);
    pipelineInfo.blendEnable = true;
    pipelineInfo.dynamicStates = true;
    pipelineInfo.depthTesting = false;
    pipelineInfo.offscreenRendering = false;

    m_shader = context->create_shader({
                                       {ShaderStage::VERTEX, ProjectRoot + "/shaders/text.vert"},
                                       {ShaderStage::FRAGMENT, ProjectRoot + "/shaders/text.frag"},
                                     }, pipelineInfo);

    m_descriptor = context->create_descriptor_set(m_descriptorLayout.lock(), {m_font.lock()->get_image().lock()});

    io.Fonts->TexID = (ImTextureID)&m_descriptor;

    m_vertexBuffer = context->create_vertex_buffer(nullptr, 0, vertexLayout,
                                                  BufferUsage::DYNAMIC);
    m_indexBuffer = context->create_index_buffer(nullptr, 0, IndexBufferType::UINT_16,
                                                BufferUsage::DYNAMIC);


}

void EditorMaster::deinit() {
    ImGui::DestroyContext();
}

void EditorMaster::update() {
    if (m_updateWindows){
        ImGui::NewFrame();
        for (auto& window : m_windows){
            window->handle_update();
        }
        ImGui::EndFrame();
        ImGui::Render();
        update_mouse_cursor();
        update_buffers();
        m_updateWindows = false;
    }
}

void EditorMaster::render(Reference<CommandBuffer> &commandBuffer) {

    ImGuiIO &io = ImGui::GetIO();
    ImDrawData *imDrawData = ImGui::GetDrawData();
    // Render commands
    if (imDrawData->CmdListsCount > 0) {
        commandBuffer->bind_shader(m_shader.lock());

        commandBuffer->set_viewport(io.DisplaySize.x, io.DisplaySize.y, 0, 0, 0, 1);

        pushConstBlock.scale = glm::vec2(2.0f / io.DisplaySize.x, 2.0f / io.DisplaySize.y);
        pushConstBlock.translate = glm::vec2(-1.0f);

        commandBuffer->push_constants(m_shader.lock(), ShaderStage::VERTEX, 0,
                                      sizeof(pushConstBlock), &pushConstBlock);

        int32_t vertexOffset = 0;
        int32_t indexOffset = 0;

        commandBuffer->bind_vertex_buffer(m_vertexBuffer.lock());
        commandBuffer->bind_index_buffer(m_indexBuffer.lock());

        for (int32_t i = 0; i < imDrawData->CmdListsCount; i++) {

            const ImDrawList *cmdList = imDrawData->CmdLists[i];
            for (int32_t j = 0; j < cmdList->CmdBuffer.Size; j++) {

                const ImDrawCmd *cmd = &cmdList->CmdBuffer[j];
                uint32_t x = std::max((int32_t) (cmd->ClipRect.x), 0);
                uint32_t y = std::max((int32_t) (cmd->ClipRect.y), 0);
                uint32_t w = (uint32_t) (cmd->ClipRect.z - cmd->ClipRect.x);
                uint32_t h = (uint32_t) (cmd->ClipRect.w - cmd->ClipRect.y);
                commandBuffer->set_scissor(w, h, x, y);

                commandBuffer->bind_descriptor_sets(m_shader.lock(), static_cast<Handle<DescriptorSet>*>(cmd->TextureId)->lock(), 0);

                commandBuffer->draw_indexed(cmd->ElemCount, indexOffset, vertexOffset);

                indexOffset += cmd->ElemCount;
            }
            vertexOffset += cmdList->VtxBuffer.Size;
        }
    }
}

bool EditorMaster::handle_window_resized(WindowResizedEvent &e) {
    m_updateWindows = true;
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.get_width(), e.get_height());
    return false;
}

bool EditorMaster::handle_mouse_moved(MouseMoveEvent &e) {
    m_updateWindows = true;
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2(e.get_x(), e.get_y());
    return false;
}

bool EditorMaster::handle_mouse_button(MouseButtonEvent &e) {
    m_updateWindows = true;
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.get_key()] = e.get_action() == EG_PRESS || e.get_action() == EG_REPEAT;
    return false;
}

bool EditorMaster::handle_mouse_scrolled(MouseScrolledEvent &e) {
    m_updateWindows = true;
    ImGuiIO &io = ImGui::GetIO();
    io.MouseWheel = e.get_y();
    io.MouseWheelH = e.get_x();
    return false;
}

bool EditorMaster::handle_key(KeyEvent &e) {
    m_updateWindows = true;
    ImGuiIO &io = ImGui::GetIO();

    io.KeysDown[e.get_key()] = e.get_action() == EG_PRESS || e.get_action() == EG_REPEAT;

    // Modifiers are not reliable across m_systems
    io.KeyCtrl = io.KeysDown[EG_KEY_LEFT_CONTROL] || io.KeysDown[EG_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[EG_KEY_LEFT_SHIFT] || io.KeysDown[EG_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[EG_KEY_LEFT_ALT] || io.KeysDown[EG_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[EG_KEY_LEFT_SUPER] || io.KeysDown[EG_KEY_RIGHT_SUPER];
    return false;
}

bool EditorMaster::handle_key_typed(KeyTypedEvent &e) {
    m_updateWindows = true;
    ImGuiIO &io = ImGui::GetIO();
    io.AddInputCharacter(e.get_key());
    return false;
}

void EditorMaster::add_window(const Reference<EditorWindow> &window) {
    m_updateWindows = true;
    m_windows.emplace_back(window);
}

void EditorMaster::remove_window(const Reference<EditorWindow> &window) {
    m_updateWindows = true;
    m_windows.erase(std::find(m_windows.begin(), m_windows.end(), window));
}

void EditorMaster::update_buffers() {
    ImDrawData *imDrawData = ImGui::GetDrawData();

    if ((imDrawData->TotalVtxCount == 0) || (imDrawData->TotalIdxCount == 0)) {
        return;
    }

    ImDrawVert *vtxDst = new ImDrawVert[imDrawData->TotalVtxCount];
    ImDrawIdx *idxDst = new ImDrawIdx[imDrawData->TotalIdxCount];

    ImDrawVert *vtxOffset = vtxDst;
    ImDrawIdx *idxOffset = idxDst;


    for (int i = 0; i < imDrawData->CmdListsCount; i++) {
        const ImDrawList *cmdList = imDrawData->CmdLists[i];
        memcpy(vtxOffset, cmdList->VtxBuffer.Data, cmdList->VtxBuffer.Size * sizeof(ImDrawVert));
        memcpy(idxOffset, cmdList->IdxBuffer.Data, cmdList->IdxBuffer.Size * sizeof(ImDrawIdx));
        vtxOffset += cmdList->VtxBuffer.Size;
        idxOffset += cmdList->IdxBuffer.Size;
    }

    m_vertexBuffer.lock()->upload(vtxDst, imDrawData->TotalVtxCount);
    m_indexBuffer.lock()->upload(idxDst, imDrawData->TotalIdxCount);

    delete[] vtxDst;
    delete[] idxDst;
}

void EditorMaster::update_mouse_cursor() {
    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();

    Cursor cursorType;
    switch (imgui_cursor) {
        case ImGuiMouseCursor_TextInput:
            cursorType = Cursor::TEXT;
            break;
        case ImGuiMouseCursor_ResizeNS:
            cursorType = Cursor::VERT_RESIZE;
            break;
        case ImGuiMouseCursor_ResizeEW:
            cursorType = Cursor::HORI_RESIZE;
            break;
        case ImGuiMouseCursor_Hand:
            cursorType = Cursor::HAND;
            break;
        default:
            cursorType = Cursor::ARROW;
            break;
    }
    Application::instance().window().set_cursor_shape(cursorType);
}


EG_RAYTRACER_END
