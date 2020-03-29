//
// Created by Novak on 22/03/2020.
//

#ifndef EAGLE_FOOWINDOW_H
#define EAGLE_FOOWINDOW_H

#include <eagle/raytracer/editor/EditorWindow.h>

EG_RAYTRACER_BEGIN

class FooWindow : public EditorWindow {
public:
    FooWindow(const std::string &name);
    virtual void handle_window_update() override;
};

EG_RAYTRACER_END

#endif //EAGLE_FOOWINDOW_H
