//
// Created by Novak on 22/03/2020.
//

#include <eagle/raytracer/editor/FooWindow.h>
#include <imgui/imgui.h>

EG_RAYTRACER_BEGIN

FooWindow::FooWindow(const std::string &name) : EditorWindow(name) {

}

void FooWindow::handle_window_update() {

}

void FooWindow::handle_update()  {
    ImGui::ShowDemoWindow();
}

EG_RAYTRACER_END


