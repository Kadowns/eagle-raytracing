//
// Created by Novak on 05/04/2020.
//

#ifndef EAGLE_EDITORDOCKINGWINDOW_H
#define EAGLE_EDITORDOCKINGWINDOW_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/editor/EditorWindow.h>

EG_RAYTRACER_BEGIN

class EditorDockingWindow : public EditorWindow {
public:
    EditorDockingWindow();

    virtual void handle_update() override;

    virtual void handle_window_update() override;
};

EG_RAYTRACER_END

#endif //EAGLE_EDITORDOCKINGWINDOW_H
